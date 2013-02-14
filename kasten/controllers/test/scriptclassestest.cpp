/*
 *    This file is part of the Okteta Kasten module, made within the KDE community.
 *
 *    Copyright 2012  Alex Richardson <alex.richardson@gmx.de>
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 2.1 of the License, or (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <QtTest>

#include <QObject>
#include <QScriptValueIterator>
#include <QScriptEngine>

#include "view/structures/datatypes/primitive/primitivetemplateinfo.h"
#include "view/structures/datatypes/primitive/primitivedatainformation.h"
#include "view/structures/datatypes/primitive/bitfield/signedbitfielddatainformation.h"
#include "view/structures/datatypes/primitive/bitfield/unsignedbitfielddatainformation.h"
#include "view/structures/datatypes/primitive/bitfield/boolbitfielddatainformation.h"
#include "view/structures/datatypes/primitive/enumdatainformation.h"
#include "view/structures/datatypes/primitive/flagdatainformation.h"
#include "view/structures/datatypes/primitive/pointerdatainformation.h"
#include "view/structures/datatypes/primitive/bitfield/boolbitfielddatainformation.h"
#include "view/structures/datatypes/primitive/bitfield/unsignedbitfielddatainformation.h"
#include "view/structures/datatypes/primitive/bitfield/signedbitfielddatainformation.h"
#include "view/structures/datatypes/primitivefactory.h"
#include "view/structures/datatypes/topleveldatainformation.h"
#include "view/structures/datatypes/strings/stringdatainformation.h"
#include "view/structures/datatypes/array/arraydatainformation.h"
#include "view/structures/datatypes/structuredatainformation.h"
#include "view/structures/datatypes/uniondatainformation.h"
#include "view/structures/script/scripthandler.h"
#include "view/structures/script/scriptengineinitializer.h"
#include "view/structures/parsers/scriptvalueconverter.h"

class ScriptClassesTest : public QObject
{
Q_OBJECT

    typedef QPair<QString, QScriptValue::PropertyFlags> PropertyPair;

private:
    static void checkProperties(const QVector<PropertyPair>& expected, DataInformation* data,
            const char* tag);
    static PropertyPair pair(const char* name,
            QScriptValue::PropertyFlags flags = QScriptValue::Undeletable | QScriptValue::ReadOnly)
    {
        return PropertyPair(QLatin1String(name), flags);
    }
private Q_SLOTS:
    void initTestCase();
    //check that all properties are available in the iterator
    void checkIterators();
    void testReplaceObject(); //check replacing datatype
    void cleanupTestCase();

private:
    QVector<PropertyPair> commonProperties;
    QVector<PropertyPair> primitiveProperties;
    QVector<TopLevelDataInformation*> primitives;

    QVector<PropertyPair> enumProperties;
    EnumDataInformation* enumData;
    QScopedPointer<TopLevelDataInformation> enumDataTop;
    FlagDataInformation* flagData;
    QScopedPointer<TopLevelDataInformation> flagDataTop;

    QVector<PropertyPair> bitfieldProperties;
    SignedBitfieldDataInformation* signedBitfield;
    QScopedPointer<TopLevelDataInformation> signedBitfieldTop;
    UnsignedBitfieldDataInformation* unsignedBitfield;
    QScopedPointer<TopLevelDataInformation> unsignedBitfieldTop;
    BoolBitfieldDataInformation* boolBitfield;
    QScopedPointer<TopLevelDataInformation> boolBitfieldTop;

    QVector<PropertyPair> structUnionProperties; //without children
    StructureDataInformation* structData;
    QScopedPointer<TopLevelDataInformation> structDataTop;
    UnionDataInformation* unionData;
    QScopedPointer<TopLevelDataInformation> unionDataTop;

    QVector<PropertyPair> arrayProperties; //without children
    ArrayDataInformation* arrayData;
    QScopedPointer<TopLevelDataInformation> arrayDataTop;

    QVector<PropertyPair> stringProperties; //without children
    StringDataInformation* stringData;
    QScopedPointer<TopLevelDataInformation> stringDataTop;

};

void ScriptClassesTest::initTestCase()
{
    //we are only testing properties when updating
    //TODO fix this
    commonProperties << pair("name", QScriptValue::Undeletable)
            << pair("wasAbleToRead") << pair("parent")
            << pair("valid")
            << pair("validationError")
            << pair("byteOrder", QScriptValue::Undeletable)
            << pair("updateFunc", QScriptValue::Undeletable)
            << pair("validationFunc", QScriptValue::Undeletable)
            << pair("datatype", QScriptValue::Undeletable);

    primitiveProperties << commonProperties << pair("value") << pair("char") << pair("int")
            << pair("int8") << pair("int16") << pair("int32") << pair("int64") << pair("uint")
            << pair("uint8") << pair("uint16") << pair("uint32") << pair("uint64") << pair("bool")
            << pair("float") << pair("double") << pair("int64high32") << pair("int64low32")
            << pair("uint64high32") << pair("uint64low32") << pair("type");
    qSort(primitiveProperties);
    LoggerWithContext lwc(0, QString());
    for (int i = Type_START; i < Type_Bitfield; ++i)
    {
        PrimitiveDataInformation* prim = PrimitiveFactory::newInstance(
                QLatin1String("prim"), static_cast<PrimitiveDataTypeEnum>(i), lwc);
        prim->setValue(10);
        primitives.append(
                new TopLevelDataInformation(prim, 0, ScriptEngineInitializer::newEngine()));
    }

    enumProperties << primitiveProperties << pair("enumValues", QScriptValue::Undeletable);
    //TODO valueString property (i.e. the current value as enumerator name)
    //XXX enumName
    qSort(enumProperties);

    QMap<AllPrimitiveTypes, QString> enumValues;
    enumValues.insert(1, QLatin1String("one"));
    enumValues.insert(2, QLatin1String("tow"));
    enumValues.insert(4, QLatin1String("four"));
    EnumDefinition::Ptr enumDef(new EnumDefinition(enumValues,
            QLatin1String("theEnum"), Type_Int32));
    enumData = new EnumDataInformation(QLatin1String("enumData"),
            PrimitiveFactory::newInstance(QLatin1String("dummy"), Type_Int32, lwc), enumDef);
    enumDataTop.reset(
            new TopLevelDataInformation(enumData, 0, ScriptEngineInitializer::newEngine()));
    flagData = new FlagDataInformation(QLatin1String("flagData"),
            PrimitiveFactory::newInstance(QLatin1String("dummy"), Type_Int32, lwc), enumDef);
    flagDataTop.reset(
            new TopLevelDataInformation(flagData, 0, ScriptEngineInitializer::newEngine()));

    bitfieldProperties << primitiveProperties << pair("width", QScriptValue::Undeletable);
    qSort(bitfieldProperties);
    unsignedBitfield = new UnsignedBitfieldDataInformation(QLatin1String("unsignedBit"), 42);
    unsignedBitfieldTop.reset(
            new TopLevelDataInformation(unsignedBitfield, 0, ScriptEngineInitializer::newEngine()));
    signedBitfield = new SignedBitfieldDataInformation(QLatin1String("signedBit"), 42);
    signedBitfieldTop.reset(
            new TopLevelDataInformation(signedBitfield, 0, ScriptEngineInitializer::newEngine()));
    boolBitfield = new BoolBitfieldDataInformation(QLatin1String("boolBit"), 42);
    boolBitfieldTop.reset(
            new TopLevelDataInformation(boolBitfield, 0, ScriptEngineInitializer::newEngine()));

    stringProperties << commonProperties << pair("terminatedBy", QScriptValue::Undeletable)
            << pair("byteCount") << pair("maxCharCount", QScriptValue::Undeletable)
            << pair("charCount") << pair("encoding", QScriptValue::Undeletable)
            << pair("maxByteCount", QScriptValue::Undeletable);
    qSort(stringProperties);
    stringData = new StringDataInformation(QLatin1String("string"), StringDataInformation::Latin1);
    stringDataTop.reset(
            new TopLevelDataInformation(stringData, 0, ScriptEngineInitializer::newEngine()));

    arrayProperties << commonProperties << pair("length", QScriptValue::Undeletable)
            << pair("type", QScriptValue::Undeletable);
    qSort(arrayProperties);
    arrayData = new ArrayDataInformation(QLatin1String("array"), 20,
            PrimitiveFactory::newInstance(QLatin1String("inner"), Type_Int32, lwc));
    arrayDataTop.reset(
            new TopLevelDataInformation(arrayData, 0, ScriptEngineInitializer::newEngine()));

    structUnionProperties << commonProperties << pair("childCount");
    //property children is only writable -> it is not in the iterator
    structData = new StructureDataInformation(QLatin1String("struct"));
    structDataTop.reset(
            new TopLevelDataInformation(structData, 0, ScriptEngineInitializer::newEngine()));
    unionData = new UnionDataInformation(QLatin1String("union"));
    unionDataTop.reset(
            new TopLevelDataInformation(unionData, 0, ScriptEngineInitializer::newEngine()));
    qSort(structUnionProperties);

}

void ScriptClassesTest::checkProperties(const QVector<PropertyPair>& expected,
        DataInformation* data, const char* tag)
{
    //check in updating mode
    //TODO check also in other modes
    data->topLevelDataInformation()->scriptHandler()->handlerInfo()->setMode(ScriptHandlerInfo::Updating);
    QScriptValue value = data->toScriptValue(data->topLevelDataInformation()->scriptEngine(),
            data->topLevelDataInformation()->scriptHandler()->handlerInfo());

    QScriptValueIterator it(value);
    QList<PropertyPair> foundProperties;
    while (it.hasNext())
    {
        it.next();
        foundProperties.append(qMakePair(it.name(), it.flags()));
    }
    data->topLevelDataInformation()->scriptHandler()->handlerInfo()->setMode(ScriptHandlerInfo::None);
    qSort(foundProperties);
    if (foundProperties.size() != expected.size()) {
        for (int i = 0; i < qMin(foundProperties.size(), expected.size()); ++i)
        {
            if (foundProperties.at(i) != expected.at(i))
                qWarning() << tag << ":" << foundProperties.at(i) << "!=" << expected.at(i);
            QCOMPARE(foundProperties.at(i).first, expected.at(i).first);
            QCOMPARE(foundProperties.at(i).second, expected.at(i).second);
        }
    }
    for (int i = 0; i < foundProperties.size(); ++i)
    {
        if (foundProperties.at(i) != expected.at(i))
            qWarning() << tag << ":" << foundProperties.at(i) << "!=" << expected.at(i);
        QCOMPARE(foundProperties.at(i).first, expected.at(i).first);
        QCOMPARE(foundProperties.at(i).second, expected.at(i).second);
    }
    QCOMPARE(foundProperties.size(), expected.size());
}

void ScriptClassesTest::checkIterators()
{

    for (int i = 0; i < primitives.size(); ++i)
    {
        TopLevelDataInformation* top = primitives.at(i);
        checkProperties(primitiveProperties, top->actualDataInformation(), "primitives");
    }
    checkProperties(enumProperties, enumData, "enum");
    checkProperties(enumProperties, flagData, "flag");

    checkProperties(bitfieldProperties, boolBitfield, "bool bitfield");
    checkProperties(bitfieldProperties, signedBitfield, "signed bitfield");
    checkProperties(bitfieldProperties, unsignedBitfield, "unsignedBitfield");

    checkProperties(stringProperties, stringData, "string");

    checkProperties(arrayProperties, arrayData, "array");

    checkProperties(structUnionProperties, structData, "struct");
    checkProperties(structUnionProperties, unionData, "union");
}

void ScriptClassesTest::testReplaceObject()
{
    QScriptEngine* eng = ScriptEngineInitializer::newEngine();
    ScriptLogger* logger = new ScriptLogger();
    logger->setLogToStdOut(true);
    QString unionDef = QLatin1String(
            "union({\n"
            "    innerStruct : struct({ first : uint8(), second : uint16() }),\n"
            "    innerArray : array(uint8(), 5),\n"
            "    innerPointer : pointer(uint8(), double())\n"
            "});\n");
    QScriptValue val = eng->evaluate(unionDef);
    QVERIFY(val.isObject());
    DataInformation* main = ScriptValueConverter::convert(val, QLatin1String("container"), logger, 0);
    QVERIFY(main);
    QCOMPARE(logger->rowCount(), 0);
    TopLevelDataInformation top(main, logger, eng);

    //first we read the struct, which changes the type of the first child
    //access it again after changing to ensure it was set properly
    QScriptValue structUpdate = eng->evaluate(QLatin1String(
            "(function() { this.first.datatype = int32(); this.first.name = \"changed\"; })"));
    QVERIFY(structUpdate.isFunction());
    StructureDataInformation* structData = main->childAt(0)->asStruct();
    QVERIFY(structData);
    structData->setUpdateFunc(structUpdate);
    QCOMPARE(structData->name(), QString(QLatin1String("innerStruct")));

    // array changes its own type, this is the critical one
    //access it again after changing to ensure it was set properly
    QScriptValue arrayUpdate = eng->evaluate(QLatin1String(
            "(function() { this.datatype = float(); this.name = \"changedToFloat\"; })"));
    ArrayDataInformation* arrayData = main->childAt(1)->asArray();
    arrayData->setUpdateFunc(arrayUpdate);

    QVERIFY(arrayData);
    QScriptValue pointerTargetUpdate = eng->evaluate(QLatin1String(
            "(function() { this.datatype = array(int8(), 5); this.parent.name = \"changedToArrayPointer\"; })"));
    PointerDataInformation* ptrData = main->childAt(2)->asPointer();
    QVERIFY(ptrData);
    ptrData->pointerTarget()->setUpdateFunc(pointerTargetUpdate);

    QScriptValue unionUpdate = eng->evaluate(QLatin1String(
                "(function() { this.datatype = ") + unionDef + QLatin1String(" this.name = \"newContainer\"; })"));
    main->setUpdateFunc(unionUpdate);

    //now just call update
    QCOMPARE(structData->childCount(), 2u);
    QCOMPARE((int)structData->childAt(0)->asPrimitive()->type().value, (int)Type_UInt8);
    QCOMPARE(structData->childAt(0)->name(), QString(QLatin1String("first")));
    QCOMPARE(structData->childAt(1)->name(), QString(QLatin1String("second")));
    top.scriptHandler()->updateDataInformation(structData);
    //now structdata should have different children
    QCOMPARE(structData->childCount(), 2u);
    QCOMPARE((int)structData->childAt(0)->asPrimitive()->type().value, (int)Type_Int32); //different now
    QCOMPARE(structData->childAt(0)->name(), QString(QLatin1String("changed"))); //different now
    QCOMPARE(structData->childAt(1)->name(), QString(QLatin1String("second"))); //still the same

    QCOMPARE(arrayData->name(), QString(QLatin1String("innerArray")));
    top.scriptHandler()->updateDataInformation(arrayData);
    QVERIFY(main->childAt(1)->hasBeenUpdated());
    QVERIFY(main->childAt(1)->isPrimitive());
    QCOMPARE(main->childAt(1)->name(), QString(QLatin1String("changedToFloat")));

    QCOMPARE(ptrData->name(), QString(QLatin1String("innerPointer")));
    QVERIFY(main->childAt(2)->isPointer());
    QVERIFY(main->childAt(2)->asPointer()->pointerTarget()->isPrimitive());
    top.scriptHandler()->updateDataInformation(ptrData->pointerTarget());
    QVERIFY(main->childAt(2)->isPointer());
    QVERIFY(main->childAt(2)->asPointer()->pointerTarget()->isArray());
    QCOMPARE(main->childAt(2)->name(), QString(QLatin1String("changedToArrayPointer")));


    //now reset to state before
    QCOMPARE(main->name(), QString(QLatin1String("container")));
    top.scriptHandler()->updateDataInformation(main);
    //main is now a dangling pointer
    main = top.actualDataInformation();
    QString nnnname = QString(QLatin1String("newContainer"));
    QCOMPARE(main->name(), nnnname);
    QVERIFY(main->childAt(0)->isStruct());
    QCOMPARE(main->childAt(0)->name(), QString(QLatin1String("innerStruct")));
    QCOMPARE(main->childAt(1)->name(), QString(QLatin1String("innerArray")));
    QCOMPARE(main->childAt(2)->name(), QString(QLatin1String("innerPointer")));


}


void ScriptClassesTest::cleanupTestCase()
{
    qDeleteAll(primitives);
}

QTEST_MAIN(ScriptClassesTest)

#include "scriptclassestest.moc"
