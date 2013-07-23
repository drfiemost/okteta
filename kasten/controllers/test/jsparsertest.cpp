/*
 *  This file is part of the Okteta Kasten module, made within the KDE community.
 *
 *  Copyright 2013  Alex Richardson <alex.richardson@gmx.de>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include <QtTest/QtTest>
#include <QScriptEngine>
#include <KGlobal>
#include <KStandardDirs>
#include "view/structures/script/scriptengineinitializer.h"
#include "view/structures/parsers/scriptvalueconverter.h"
#include "testutils.h"

struct JsTestData {
    JsTestData() {}
    JsTestData(const char* tag, const char* constructor, Utils::DataInformationCheck* check)
            : tag(tag), constructorCall(QString::fromUtf8(constructor)), check(check) {}
    QByteArray tag;
    QString constructorCall;
    QSharedPointer<Utils::DataInformationCheck> check;
};

class JsParserTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase();
    void testValidationFunc();
    void testValidationFunc_data();
    void testUpdateFunc();
    void testUpdateFunc_data();
    void testByteOrder();
    void testByteOrder_data();
    void testName();
    void testName_data();
    void testCustomTypeName();
    void testCustomTypeName_data();
    void testImport();
    void testImportPathTraversal();
private:
    /** data gets set to the parsed result.
     * This is needed since functions with QVERIFY/QCOMPARE must return void */
    void testCommon(DataInformation** data);
private:
    QScriptEngine engine;
    QVector<JsTestData> primitiveData;
    QVector<JsTestData> bitfieldData;
    QVector<JsTestData> allData;
};

Q_DECLARE_METATYPE(JsTestData)

void JsParserTest::initTestCase()
{
    ScriptEngineInitializer::addFuctionsToScriptEngine(&engine);

    primitiveData
        << JsTestData("float", "float()", new Utils::PrimitiveTypeCheck(Type_Float))
        << JsTestData("double", "double()", new Utils::PrimitiveTypeCheck(Type_Double))
        << JsTestData("char", "char()", new Utils::PrimitiveTypeCheck(Type_Char))

        << JsTestData("uint8", "uint8()", new Utils::PrimitiveTypeCheck(Type_UInt8))
        << JsTestData("uint16", "uint16()", new Utils::PrimitiveTypeCheck(Type_UInt16))
        << JsTestData("uint32", "uint32()", new Utils::PrimitiveTypeCheck(Type_UInt32))
        << JsTestData("uint64", "uint64()", new Utils::PrimitiveTypeCheck(Type_UInt64))

        << JsTestData("int8", "int8()", new Utils::PrimitiveTypeCheck(Type_Int8))
        << JsTestData("int16", "int16()", new Utils::PrimitiveTypeCheck(Type_Int16))
        << JsTestData("int32", "int32()", new Utils::PrimitiveTypeCheck(Type_Int32))
        << JsTestData("int64", "int64()", new Utils::PrimitiveTypeCheck(Type_Int64))

        << JsTestData("bool8", "bool8()", new Utils::PrimitiveTypeCheck(Type_Bool8))
        << JsTestData("bool16", "bool16()", new Utils::PrimitiveTypeCheck(Type_Bool16))
        << JsTestData("bool32", "bool32()", new Utils::PrimitiveTypeCheck(Type_Bool32))
        << JsTestData("bool64", "bool64()", new Utils::PrimitiveTypeCheck(Type_Bool64));

    bitfieldData
        << JsTestData("signed bitfield", "bitfield(\"signed\", 5)", new Utils::SignedBitfieldCheck())
        << JsTestData("unsigned bitfield", "bitfield(\"unsigned\", 5)", new Utils::UnsignedBitfieldCheck())
        << JsTestData("bool bitfield", "bitfield(\"bool\", 5)", new Utils::BoolBitfieldCheck());

    allData << primitiveData << bitfieldData;
    //TODO struct, union, taggedUnion, pointer, flags, enum, array, string

    //needed so that imports can be resolved
    QVERIFY(KGlobal::dirs()->addResourceDir("data", QStringLiteral(SRCDIR "/test/resources")));
    QVERIFY(KGlobal::dirs()->addResourceDir("data", QStringLiteral(SRCDIR "/view/structures/examples")));
}

//#pragma message(SRCDIR)

void JsParserTest::testByteOrder_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<Utils::DataInformationCheck*>("checkPtr");
    QTest::addColumn<int>("expectedByteOrder");
    //verify that default is inherit
    QString codeStr = QStringLiteral("%1");
    Q_FOREACH(const JsTestData& data, allData) {
        //default should be inherit
        QString codeStr = QStringLiteral("%1;");
        QTest::newRow(data.tag.constData()) << codeStr.arg(data.constructorCall)
            << data.check.data() << (int)DataInformation::EndianessInherit;

        //use set() function to specify byteOrder
        codeStr = QStringLiteral("%1.set({byteOrder: \"inherit\"})");
        QTest::newRow((data.tag + " set() inherit").constData()) << codeStr.arg(data.constructorCall)
            << data.check.data() << (int)DataInformation::EndianessInherit;
        codeStr = QStringLiteral("%1.set({byteOrder: \"littleEndian\"})");
        QTest::newRow((data.tag + " set() little endian").constData()) << codeStr.arg(data.constructorCall)
            << data.check.data() << (int)DataInformation::EndianessLittle;
        codeStr = QStringLiteral("%1.set({byteOrder: \"bigEndian\"})");
        QTest::newRow((data.tag + " set() big endian").constData()) << codeStr.arg(data.constructorCall)
            << data.check.data() << (int)DataInformation::EndianessBig;
        codeStr = QStringLiteral("%1.set({byteOrder: \"fromSettings\"})");
        QTest::newRow((data.tag + " set() from settings").constData()) << codeStr.arg(data.constructorCall)
            << data.check.data() << (int)DataInformation::EndianessFromSettings;

        //direct property access to specify byteOrder
        codeStr = QStringLiteral("var obj = %1; obj.byteOrder = \"inherit\"; obj;");
        QTest::newRow((data.tag + " property assign inherit").constData()) << codeStr.arg(data.constructorCall)
            << data.check.data() << (int)DataInformation::EndianessInherit;
        codeStr = QStringLiteral("var obj = %1; obj.byteOrder = \"little-endian\"; obj;");
        QTest::newRow((data.tag + " property assign little endian").constData()) << codeStr.arg(data.constructorCall)
            << data.check.data() << (int)DataInformation::EndianessLittle;
        codeStr = QStringLiteral("var obj = %1; obj.byteOrder = \"big-endian\"; obj;");
        QTest::newRow((data.tag + " property assign big endian").constData()) << codeStr.arg(data.constructorCall)
            << data.check.data() << (int)DataInformation::EndianessBig;
        codeStr = QStringLiteral("var obj = %1; obj.byteOrder = \"from-settings\"; obj;");
        QTest::newRow((data.tag + " property assign from settings").constData()) << codeStr.arg(data.constructorCall)
            << data.check.data() << (int)DataInformation::EndianessFromSettings;
    }
}

void JsParserTest::testCommon(DataInformation** dataPtr) {
    QFETCH(QString, code);
    QFETCH(Utils::DataInformationCheck*, checkPtr);
    QScriptValue value = engine.evaluate(code);
    QVERIFY(value.isValid());
    QVERIFY(!value.isError());
    QVERIFY(value.isObject());
    ScriptLogger logger;
    QScopedPointer<DataInformation> data
            (ScriptValueConverter::convert(value, QStringLiteral("converted"), &logger));
    QVERIFY(logger.rowCount() == 0);
    QVERIFY(data);
    checkPtr->check(data.data());
    *dataPtr = data.take();
}

void JsParserTest::testByteOrder()
{
    DataInformation* data = 0;
    testCommon(&data);
    if (QTest::currentTestFailed())
        return; //Qt doesn't use exceptions, we must manually check after each call
    QFETCH(int, expectedByteOrder);
    QCOMPARE((int)data->byteOrder(), expectedByteOrder);
}

static const QString updateFunction = QStringLiteral("function () { /* do nothing*/; }");

void JsParserTest::testUpdateFunc_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<Utils::DataInformationCheck*>("checkPtr");

    Q_FOREACH(const JsTestData& data, allData) {
        QString codeStr = QStringLiteral("%1.setUpdate(") + updateFunction + QStringLiteral(");");
        QTest::newRow((data.tag + "-setUpdate()").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();

        codeStr = QStringLiteral("%1.set({updateFunc: ") + updateFunction + QStringLiteral("});");
        QTest::newRow((data.tag + "-set()").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();

        codeStr = QStringLiteral("var obj = %1; obj.updateFunc = ") + updateFunction + QStringLiteral("; obj;");
        QTest::newRow((data.tag + "-property assign").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();
    }
}

void JsParserTest::testUpdateFunc()
{
    DataInformation* data = 0;
    testCommon(&data);
    if (QTest::currentTestFailed())
        return; //Qt doesn't use exceptions, we must manually check after each call
    QVERIFY(data);
    QScriptValue update = data->updateFunc();
    QVERIFY(update.isValid());
    QVERIFY(update.isFunction());
    QCOMPARE(update.toString(), updateFunction);
}

static const QString validationFunction = QStringLiteral("function () { return true; }");

void JsParserTest::testValidationFunc_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<Utils::DataInformationCheck*>("checkPtr");

    Q_FOREACH(const JsTestData& data, allData) {
        QString codeStr = QStringLiteral("%1.setValidation(") + validationFunction + QStringLiteral(");");
        QTest::newRow((data.tag + "-setUpdate()").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();

        codeStr = QStringLiteral("%1.set({validationFunc: ") + validationFunction + QStringLiteral("});");
        QTest::newRow((data.tag + "-set()").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();

        codeStr = QStringLiteral("var obj = %1; obj.validationFunc = ") + validationFunction + QStringLiteral("; obj;");
        QTest::newRow((data.tag + "-property assign").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();
    }
}

void JsParserTest::testValidationFunc()
{
    DataInformation* data = 0;
    testCommon(&data);
    if (QTest::currentTestFailed())
        return; //Qt doesn't use exceptions, we must manually check after each call

    QScriptValue validation = data->validationFunc();
    QVERIFY(validation.isValid());
    QVERIFY(validation.isFunction());
    QCOMPARE(validation.toString(), validationFunction);
}

void JsParserTest::testName_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<Utils::DataInformationCheck*>("checkPtr");

    Q_FOREACH(const JsTestData& data, allData) {
        QString codeStr = QStringLiteral("%1.set({name: \"expectedName\"});");
        QTest::newRow((data.tag + "-set()").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();

        codeStr = QStringLiteral("var obj = %1;obj.name = \"expectedName\"; obj;");
        QTest::newRow((data.tag + "-property assignment").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();
    }
}

void JsParserTest::testName()
{
    DataInformation* data = 0;
    testCommon(&data);
    if (QTest::currentTestFailed())
        return; //Qt doesn't use exceptions, we must manually check after each call

    QCOMPARE(data->name(), QString(QStringLiteral("expectedName")));
}

void JsParserTest::testCustomTypeName_data()
{
    QTest::addColumn<QString>("code");
    QTest::addColumn<Utils::DataInformationCheck*>("checkPtr");

    Q_FOREACH(const JsTestData& data, allData) {
        QString codeStr = QStringLiteral("%1.set({typeName: 'myCustomType'});");
        QTest::newRow((data.tag + "-set()").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();

        codeStr = QStringLiteral("var obj = %1;obj.typeName = 'myCustomType'; obj;");
        QTest::newRow((data.tag + "-property assignment").constData())
            << codeStr.arg(data.constructorCall) << data.check.data();
    }
}

void JsParserTest::testCustomTypeName()
{
    DataInformation* data = 0;
    testCommon(&data);
    if (QTest::currentTestFailed())
        return; //Qt doesn't use exceptions, we must manually check after each call

    QCOMPARE(data->typeName(), QString(QStringLiteral("myCustomType")));
}

void JsParserTest::testImport()
{
    QScopedPointer<QScriptEngine> eng(ScriptEngineInitializer::newEngine());
    QScriptValue val = eng->evaluate(QStringLiteral("s = importScript('simpleImport.js');s.foo()"));
    QCOMPARE(val.toString(), QString(QStringLiteral("100")));
}

void JsParserTest::testImportPathTraversal()
{
    QScopedPointer<QScriptEngine> eng(ScriptEngineInitializer::newEngine());
    QScriptValue val = eng->evaluate(QStringLiteral("s = importScript('../../pathtraversal.js');s.foo()"));
    QVERIFY(val.isError());
    QCOMPARE(val.toString(), QString(QStringLiteral("Error: importScript(): You may only access installed structure files! Path traversal detected.")));
}



QTEST_GUILESS_MAIN(JsParserTest)

#include "jsparsertest.moc"
