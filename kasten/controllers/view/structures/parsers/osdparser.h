/*
 *   This file is part of the Okteta Kasten Framework, made within the KDE community.
 *
 *   Copyright 2010, 2011, 2012 Alex Richardson <alex.richardson@gmx.de>
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

#ifndef OSDPARSER_H_
#define OSDPARSER_H_

#include "abstractstructureparser.h"
#include "parserutils.h"
#include "../datatypes/primitive/enumdefinition.h"

class QDomElement;
class QDomDocument;

class StringDataInformation;
class ArrayDataInformation;
class AbstractBitfieldDataInformation;
class EnumDataInformation;
class DataInformation;
class StructureDataInformation;
class UnionDataInformation;
class PrimitiveDataInformation;
class ScriptLogger;

class OsdParser : public AbstractStructureParser
{
    Q_DISABLE_COPY(OsdParser)
public:
    /** construct a parser which opens parses @p absolutePath */
    OsdParser(const QString& pluginName, const QString& absolutePath);
    /** construct a parser from an in-memory string */
    OsdParser(const QString& xml);
    virtual ~OsdParser();

    virtual QStringList parseStructureNames() const;
    virtual QVector<TopLevelDataInformation*> parseStructures() const;

private:
    struct OsdParserInfo : public ParserInfo {
        inline OsdParserInfo(const QString& name, ScriptLogger* logger, DataInformation* parent,
                QScriptEngine* engine, QVector<EnumDefinition::Ptr> enums)
            : ParserInfo(name, logger, parent), engine(engine), enums(enums) {}
        inline OsdParserInfo(const OsdParserInfo& i) : ParserInfo(i), engine(i.engine), enums(i.enums) {}
        inline ~OsdParserInfo() {}
        /** OSD parser only since QScriptValue::engine() exists */
        QScriptEngine* engine;
        QVector<EnumDefinition::Ptr> enums;
    };

    PrimitiveDataInformation* primitiveFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const;
    PointerDataInformation* pointerFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const;
    AbstractBitfieldDataInformation* bitfieldFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const;
    EnumDataInformation* enumFromXML(const QDomElement& xmlElem, bool isFlags,
            const OsdParserInfo& info) const;
    StringDataInformation* stringFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const;

    template<class T> T* structOrUnionFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const;
    UnionDataInformation* unionFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const;
    StructureDataInformation* structFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const;

    ArrayDataInformation* arrayFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const;

    DataInformation* parseElement(const QDomElement& node, const OsdParserInfo& info) const;

    EnumDefinition::Ptr findEnum(const QString& defName, const OsdParserInfo& info) const;

    QVector<EnumDefinition::Ptr> parseEnums(const QDomElement& rootElem, ScriptLogger* logger) const;

    QDomDocument openDoc(ScriptLogger* logger) const;
    QDomDocument openDocFromFile(ScriptLogger* logger) const;
    QDomDocument openDocFromString(ScriptLogger* logger) const;

    /** Reads an property of the QDomElement. First it is checked whether an attribute exists, if this is not the case
     * the inner text of an element with tag equal to @p attrib is returned*/
    static QString readProperty(const QDomElement& elem, const QString& attrib, const QString& defaultVal = QString());

    /** This essentially calls engine->evaluate(str), but ensures it can be a function (QTBUG-5757)  */
    static QScriptValue functionSafeEval(QScriptEngine* engine, const QString& str);

private:
    /** Generate a length function referencing @p elemName
     *  This is needed to support the old way of defining dynamic arrays */
    static QString generateLengthFunction(DataInformation* current, DataInformation* last, QString elemName,
            QString currentString, const ParserInfo& info);

    /** if not empty construct the document from this, instead of opening file */
    const QString mXmlString;
};

inline UnionDataInformation* OsdParser::unionFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const
{
    return structOrUnionFromXML<UnionDataInformation>(xmlElem, info);
}

inline StructureDataInformation* OsdParser::structFromXML(const QDomElement& xmlElem, const OsdParserInfo& info) const
{
    return structOrUnionFromXML<StructureDataInformation>(xmlElem, info);
}


#endif /* OSDPARSER_H_ */
