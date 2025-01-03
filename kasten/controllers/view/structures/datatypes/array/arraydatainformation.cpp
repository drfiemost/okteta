/*
 *   This file is part of the Okteta Kasten Framework, made within the KDE community.
 *
 *   Copyright 2009, 2010, 2011, 2012 Alex Richardson <alex.richardson@gmx.de>
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
#include "arraydatainformation.h"

#include <KDebug>

#include "../primitivefactory.h"
#include "../dummydatainformation.h"
#include "../../parsers/scriptvalueconverter.h"
#include "../../script/classes/arrayscriptclass.h"
#include "../../script/scripthandlerinfo.h"
#include "../../script/scriptlogger.h"

#include "complexarraydata.h"
#include "primitivearraydata.h"

ArrayDataInformation::ArrayDataInformation(const QString& name, uint length, DataInformation* childType,
        DataInformation* parent, const QScriptValue& lengthFunction)
        : DataInformationWithDummyChildren(name, parent)
{
    if (lengthFunction.isValid())
    {
        Q_ASSERT(lengthFunction.isFunction());
        setLengthFunction(lengthFunction);
    }
    if (length > MAX_LEN)
    {
        logWarn() << length << "exceeds maximum length of" << MAX_LEN
                << ". Setting it to" << MAX_LEN << "instead";
        length = MAX_LEN;
    }
    Q_CHECK_PTR(childType);
    childType->setParent(this);
    mData.reset(AbstractArrayData::newArrayData(length, childType, this));
}

ArrayDataInformation::ArrayDataInformation(const ArrayDataInformation& d)
        : DataInformationWithDummyChildren(d), mData(0)
{
    uint length = d.mData->length();
    DataInformation* childType = d.mData.data()->childType();
    mData.reset(AbstractArrayData::newArrayData(length, childType->clone(), this));
}

ArrayDataInformation::~ArrayDataInformation()
{
}

bool ArrayDataInformation::setArrayLength(uint newLength)
{
    if (newLength > MAX_LEN)
    {
        logWarn() << QString(QLatin1String("new array length is too large (%1), limiting to (%2)"))
                .arg(QString::number(newLength), QString::number(MAX_LEN));
        newLength = MAX_LEN;
    }
    uint oldLength = mData->length();
    topLevelDataInformation()->_childCountAboutToChange(this, oldLength, newLength);
    mData->setLength(newLength);
    topLevelDataInformation()->_childCountChanged(this, oldLength, newLength);
    return true;
}

void ArrayDataInformation::setArrayType(DataInformation* newChildType)
{
    Q_CHECK_PTR(newChildType);
    if (newChildType->isPrimitive() && newChildType->asPrimitive()->type() == mData->primitiveType())
    {
        //there is no need to change the type
        logInfo() << "New and old child type are identical, skipping: " << mData->primitiveType();
        delete newChildType;
        return;
    }
    newChildType->setParent(this);
    uint len = mData->length();
    TopLevelDataInformation* topLevel = topLevelDataInformation();
    if (len > 0)
    {
        //first create with length of 0, then change length to actual length (to ensure model is correct)
        topLevel->_childCountAboutToChange(this, len, 0);
        mData.reset(AbstractArrayData::newArrayData(0, newChildType, this));
        topLevel->_childCountChanged(this, len, 0);

        topLevel->_childCountAboutToChange(this, 0, len);
        mData->setLength(len);
        topLevel->_childCountChanged(this, 0, len);
    }
    else
    {
        //no need to emit the signals, which cause expensive model update
        mData.reset(AbstractArrayData::newArrayData(len, newChildType, this));
        //only the type of the array changed -> emit that this has changed data
        topLevel->setChildDataChanged();
    }
}

QScriptValue ArrayDataInformation::childType() const
{
    return mData->typeName().toLower();
}

QVariant ArrayDataInformation::childData(int row, int column, int role) const
{
    Q_ASSERT(uint(row) < mData->length());
    return mData->dataAt(row, column, role);
}

QWidget* ArrayDataInformation::createEditWidget(QWidget*) const
{
    Q_ASSERT_X(false, "ArrayDataInformation::createEditWidget", "this should never happen!");
    return 0;
}

QVariant ArrayDataInformation::dataFromWidget(const QWidget*) const
{
    Q_ASSERT_X(false, "ArrayDataInformation::dataFromWidget", "this should never happen!");
    return QVariant();
}

void ArrayDataInformation::setWidgetData(QWidget*) const
{
    Q_ASSERT_X(false, "ArrayDataInformation::setWidgetData", "this should never happen!");
}

BitCount64 ArrayDataInformation::childPosition(const DataInformation* child, Okteta::Address start) const
{
    if (mParent->isTopLevel())
        return start * 8 + mData->offset(child);
    else
        return mParent->asDataInformation()->childPosition(this, start) + mData->offset(child);
}

qint64 ArrayDataInformation::readData(Okteta::AbstractByteArrayModel* input, Okteta::Address address,
        BitCount64 bitsRemaining, quint8* bitOffset)
{
    if (*bitOffset != 0)
    {
        //TODO remove this, it will probably cause issues
        logWarn() << "bit offset != 0 (" << *bitOffset << "), adding padding,"
                " arrays always start at full bytes";
        bitsRemaining &= BitCount64(~7); //unset lower 3 bits to make it divisible by 8
        address++;
    }

    //update the length of the array
    topLevelDataInformation()->scriptHandler()->updateLength(this);

    //FIXME do not add this padding
    qint64 ret = mData->readData(input, address, bitsRemaining);
    mWasAbleToRead = ret >= 0; //if ret is -1 reading failed
    return ret;
}

bool ArrayDataInformation::setChildData(uint row, const QVariant& value, Okteta::AbstractByteArrayModel* out,
        Okteta::Address address, BitCount64 bitsRemaining, quint8 bitOffset)
{
    if (bitOffset != 0)
    {
        logWarn() << "bit offset != 0 (" << bitOffset << "), adding padding,"
                " arrays always start at full bytes";
        bitsRemaining -= bitOffset;
        address++;
    }
    return mData->setChildData(row, value, out, address, bitsRemaining);
}

bool ArrayDataInformation::setData(const QVariant&, Okteta::AbstractByteArrayModel*,
        Okteta::Address, BitCount64, quint8)
{
    Q_ASSERT_X(false, "ArrayDataInformation::setData()", "this should never be called");
    return false;
}

QScriptClass* ArrayDataInformation::scriptClass(ScriptHandlerInfo* handlerInfo) const
{
    return handlerInfo->mArrayClass.data();
}

QScriptValue ArrayDataInformation::childToScriptValue(uint index, QScriptEngine* engine,
        ScriptHandlerInfo* handlerInfo) const
{
    return mData->toScriptValue(index, engine, handlerInfo);
}
