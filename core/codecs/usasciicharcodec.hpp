/*
    This file is part of the Okteta Core library, made within the KDE community.

    Copyright 2014 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef OKTETA_USASCIICHARCODEC_HPP
#define OKTETA_USASCIICHARCODEC_HPP

// lib
#include <charcodec.hpp>

namespace Okteta {

//
class USASCIICharCodec : public CharCodec
{
protected:
    USASCIICharCodec();

public: // CharCodec API
    Character decode(Byte byte) const override;
    bool encode(Byte* byte, QChar _char) const override;
    bool canEncode(QChar _char) const override;
    QString name() const override;

public:
    static USASCIICharCodec* create();
    static const QString& codecName();
};

inline USASCIICharCodec::USASCIICharCodec() = default;

inline USASCIICharCodec* USASCIICharCodec::create() { return new USASCIICharCodec(); }

}

#endif
