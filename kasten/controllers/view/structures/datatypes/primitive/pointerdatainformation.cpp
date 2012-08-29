/*
 *   This file is part of the Okteta Kasten Framework, made within the KDE community.
 *
 *   Copyright 2012 Alessandro Di Federico <ale@clearmind.me>
 *   Copyright 2012 Alex Richardson <alex.richardosn@gmx.de>
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) version 3, or any
 *   later version accepted by the membership of KDE e.V. (or its
 *   successor approved by the membership of KDE e.V.), which shall
 *   act as a proxy defined in Section 6 of version 3 of the license.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "pointerdatainformation.h"
#include "../topleveldatainformation.h"
#include "../primitivedatatype.h"
#include "../../allprimitivetypes.h"
#include "../../script/scripthandlerinfo.h"
#include "../../script/classes/structunionscriptclass.h" //TODO FIXME!!!
#include "../../script/scriptlogger.h"

#include <QScriptEngine>
#include <KLocalizedString>


PointerDataInformation::PointerDataInformation(QString name, DataInformation* childType,
        PrimitiveDataInformation* valueType, DataInformation* parent)
        : PrimitiveDataInformation(name, parent), mValue(valueType), mPointerTarget(childType)
{
    Q_CHECK_PTR(valueType);
    Q_CHECK_PTR(childType);

    //currently only absolute unsigned pointers are allowed
    const PrimitiveDataType pdt = mValue->type();
    Q_ASSERT(pdt == Type_UInt8 || pdt == Type_UInt16 || pdt == Type_UInt32 || pdt == Type_UInt64);
    Q_UNUSED(pdt)
    mValue->setParent(this);
    mPointerTarget->setParent(this);
}

PointerDataInformation::PointerDataInformation(QString name, PrimitiveDataInformation* type, DataInformation* parent)
        : PrimitiveDataInformation(name, parent), mValue(type)
{
    Q_CHECK_PTR(type);
    type->setParent(this);
}

PointerDataInformation::~PointerDataInformation()
{
}

PointerDataInformation::PointerDataInformation(const PointerDataInformation& d)
        : PrimitiveDataInformation(d), mValue(d.mValue->clone()), mPointerTarget(d.mPointerTarget->clone())
{
    mValue->setParent(this);
    mPointerTarget->setParent(this);
}

QScriptValue PointerDataInformation::toScriptValue(QScriptEngine* engine, ScriptHandlerInfo* handlerInfo)
{
    QScriptValue ret = engine->newObject(handlerInfo->mStructUnionClass.data());
    ret.setData(engine->toScriptValue(static_cast<DataInformation*>(this)));
    return ret;
}

bool PointerDataInformation::setChildData(uint /*row*/, const QVariant& /*value*/, Okteta::AbstractByteArrayModel* /*out*/, Okteta::Address /*address*/, BitCount64 /*bitsRemaining*/, quint8 /*bitOffset*/)
{
    Q_ASSERT_X(false, "PointerDataInformation::setChildData()", "this should never be called!!");
    return false;
}

bool PointerDataInformation::setData(const QVariant& value, Okteta::AbstractByteArrayModel* out, Okteta::Address address, BitCount64 bitsRemaining, quint8 bitOffset)
{
    return mValue->setData(value, out, address, bitsRemaining, bitOffset);
}

qint64 PointerDataInformation::readData(Okteta::AbstractByteArrayModel* input, Okteta::Address address, BitCount64 bitsRemaining, quint8* bitOffset)
{
    //update enum first (it is possible to change the enum definition this enum uses
    topLevelDataInformation()->updateElement(this);
    qint64 retVal = mValue->readData(input, address, bitsRemaining, bitOffset);
    mWasAbleToRead = retVal >= 0; //not able to read if mValue->readData returns -1

    // If the pointer it's outside the boundaries of the input simply ignore it
    if (mValue->value().uintValue < input->size())
    {
        // Enqueue for later reading of the destination
        topLevelDataInformation()->enqueueReadData(this);
    }

    return retVal;
}

qint64 PointerDataInformation::delayedReadData(Okteta::AbstractByteArrayModel *input, Okteta::Address address)
{
    quint8 childBitOffset;
    // Compute the destination offset
    Okteta::Address newAddress(mValue->value().uintValue + address);

    //TODO std::numeric_limits
    // If the computed destination it's outside the boundaries of the input
    // ignore it
    if (newAddress < 0 || newAddress >= input->size())
        return 0;

    // Let the child do the work
    return mPointerTarget->readData(input, newAddress, (input->size() - newAddress) * 8, &childBitOffset);
}

BitCount32 PointerDataInformation::size() const
{
    return mValue->size();
}

void PointerDataInformation::setWidgetData(QWidget* w) const
{
    return mValue->setWidgetData(w);
}

QVariant PointerDataInformation::dataFromWidget(const QWidget* w) const
{
    return mValue->dataFromWidget(w);
}

QWidget* PointerDataInformation::createEditWidget(QWidget* parent) const
{
    return mValue->createEditWidget(parent);
}

QString PointerDataInformation::typeName() const
{
    return i18nc("memory pointer with underlying type", "%1 pointer", mValue->typeName());
}

BitCount32 PointerDataInformation::positionRelativeToRoot(int row) const
{
    //TODO fix this
    // Two cases position of the pointer itself or position
    // from which calculate the position of the children
    if (row < 0)
        return mValue->value().uintValue;
    else
        return DataInformation::positionRelativeToRoot(row);
}

QString PointerDataInformation::valueString() const
{
    return mValue->valueString();
}

Qt::ItemFlags PointerDataInformation::flags(int column, bool fileLoaded) const
{
    if (column == (int)DataInformation::ColumnValue && fileLoaded)
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
    else
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

uint PointerDataInformation::childCount() const
{
    return mWasAbleToRead ? 1 : 0;
}

AllPrimitiveTypes PointerDataInformation::value() const
{
    return mValue->value();
}

void PointerDataInformation::setValue(AllPrimitiveTypes newValue)
{
    mValue->setValue(newValue);
}

DataInformation* PointerDataInformation::childAt(uint index) const
{
    Q_ASSERT(index == 0);
    return index == 0 ? mPointerTarget.data() : 0;
}

QScriptValue PointerDataInformation::valueAsQScriptValue() const
{
    return mValue->valueAsQScriptValue();
}
