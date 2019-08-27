/*
    This file is part of the Okteta Core library, made within the KDE community.

    Copyright 2004,2011 Friedrich W. H. Kossebau <kossebau@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#include "charcodec.hpp"

// lib
#include "textcharcodec.hpp"
#include "ebcdic1047charcodec.hpp"
#include "jisx0201charcodec.hpp"
#include "usasciicharcodec.hpp"
// Qt
#include <QStringList>

namespace Okteta {

QStringList CharCodec::codecNames()
{
    static QStringList codecNames;
    // first call?
    if (codecNames.isEmpty()) {
        codecNames = TextCharCodec::codecNames();
        codecNames.reserve(codecNames.size() + 3);
        codecNames.append(USASCIICharCodec::codecName());
        codecNames.append(EBCDIC1047CharCodec::codecName());
        codecNames.append(JISX0201CharCodec::codecName());
    }

    return codecNames;
}

CharCodec* CharCodec::createCodec(const QString& name)
{
    CharCodec* result;

    if (TextCharCodec::codecNames().indexOf(name) != -1) {
        result = TextCharCodec::createCodec(name);
    } else if (USASCIICharCodec::codecName() == name) {
        result = USASCIICharCodec::create();
    } else if (EBCDIC1047CharCodec::codecName() == name) {
        result = EBCDIC1047CharCodec::create();
    } else if (JISX0201CharCodec::codecName() == name) {
        result = JISX0201CharCodec::create();
    } else {
        result = nullptr;
    }

    // ensure at least a codec
    if (!result) {
        result = TextCharCodec::createLocalCodec();
    }

    return result;
}

CharCodec* CharCodec::createCodec(CharCoding charCoding)
{
    CharCodec* result;

    if (charCoding == EBCDIC1047Encoding) {
        result = EBCDIC1047CharCodec::create();
    } else if (charCoding == ISO8859_1Encoding) {
        result = TextCharCodec::createCodec(QStringLiteral("ISO-8859-1"));
    }
    // LocalEncoding
    else {
        result = nullptr;
    }

    // ensure at least a codec
    if (!result) {
        result = TextCharCodec::createLocalCodec();
    }

    return result;
}

}
