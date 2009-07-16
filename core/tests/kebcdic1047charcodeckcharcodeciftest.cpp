/*
    This file is part of the Okteta Core library, part of the KDE project.

    Copyright 2006 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "kebcdic1047charcodeckcharcodeciftest.h"

// test object
#include <codecs/kebcdic1047charcodec.h>
// Qt
#include <QtTest/QtTest>


using namespace Okteta;


Okteta::CharCodec *KEBCDIC1047CharCodecKCharCodecIfTest::createCodec()
{
  return KEBCDIC1047CharCodec::create();
}


void KEBCDIC1047CharCodecKCharCodecIfTest::deleteCodec( Okteta::CharCodec *Codec )
{
  delete Codec;
}


QTEST_MAIN( KEBCDIC1047CharCodecKCharCodecIfTest )
