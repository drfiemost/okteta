/*
    This file is part of the Okteta Kasten module, part of the KDE project.

    Copyright 2010 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "bytearrayuuencodingstreamencoder.h"

// lib
#include "bytearraybase64streamencoder.h"
// Okteta core
#include <abstractbytearraymodel.h>
// KDE
#include <KLocale>
// Qt
#include <QtCore/QTextStream>


namespace Kasten
{

static const char xxencodeMap[64] =
{
    '+', '-', '0', '1', '2', '3', '4', '5',
    '6', '7', '8', '9', 'A', 'B', 'C', 'D',
    'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
    'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

static const int defaultInputLineLength = 45;
static const int inputLineLength = defaultInputLineLength;
static const int inputGroupLength = 3;
static const int maxInputGroupsPerLine = inputLineLength/inputGroupLength;

enum InputByteIndex { FirstByte, SecondByte, ThirdByte };

static inline char uumapByteHistorical( char byte ) { return (byte > 0) ? (byte + 32) : '`'; }
static inline char xxmapByte( char byte )           { return xxencodeMap[(int)byte]; }
static inline char uumapByteBase64( char byte )     { return base64EncodeMap[(int)byte]; }

struct UumapEncodeData
{
    char (*mapByte)( char );
    const char* header;
    const char* footer;
    const char* paddingData[2];
    bool hasLength;

    inline const char* padding( InputByteIndex index ) const
    {
        return paddingData[(int)(index) - 1];
    }
};

static const UumapEncodeData historicalUumapEncodeData =
{
    &uumapByteHistorical,
    "begin",
    "\n`\nend\n",
    {"``","`"},
    true
};

static const UumapEncodeData xxmapEncodeData =
{
    &xxmapByte,
    "begin",
    "\n+\nend\n",
    {"++","+"},
    true
};

static const UumapEncodeData base64UumapEncodeData =
{
    &uumapByteBase64,
    "begin-base64",
    "\n====\n",
    {"==","="},
    false
};


UuencodingStreamEncoderSettings::UuencodingStreamEncoderSettings()
 : fileName( QString::fromLatin1("okteta-export")), algorithmId( Base64Id )
{}

ByteArrayUuEncodingStreamEncoder::ByteArrayUuEncodingStreamEncoder()
  : AbstractByteArrayStreamEncoder( i18nc("name of the encoding target","Uuencoding..."), QString::fromLatin1("text/plain") )
{}


bool ByteArrayUuEncodingStreamEncoder::encodeDataToStream( QIODevice* device,
                                                           const ByteArrayView* byteArrayView,
                                                           const Okteta::AbstractByteArrayModel* byteArrayModel,
                                                           const Okteta::AddressRange& range )
{
    Q_UNUSED( byteArrayView );

    bool success = true;

    // encode
    QTextStream textStream( device );

    // prepare
    InputByteIndex inputByteIndex = FirstByte;
    int inputGroupsPerLine = 0;
    unsigned char bitsFromLastByte;

    const UumapEncodeData* encodeData =
        (mSettings.algorithmId == UuencodingStreamEncoderSettings::HistoricalId ) ?
            &historicalUumapEncodeData :
        (mSettings.algorithmId == UuencodingStreamEncoderSettings::XxencodingId ) ?
            &xxmapEncodeData :
        /* else */
            &base64UumapEncodeData;

    // header
    textStream << encodeData->header << " 644 " << mSettings.fileName.toAscii();

    const int firstLineLength = qMin( range.width(), inputLineLength );
    if( firstLineLength > 0 )
    {
        textStream << '\n';
        if( encodeData->hasLength )
            textStream << encodeData->mapByte( firstLineLength );
    }

    for( Okteta::Address i=range.start(); i<=range.end(); ++i )
    {
        const Okteta::Byte byte = byteArrayModel->byte( i );

        switch( inputByteIndex )
        {
        case FirstByte:
            // bits 7..2
            textStream << encodeData->mapByte( byte >> 2 );
            // bits 1..0 -> 5..4 for next
            bitsFromLastByte = (byte & 0x3) << 4;
            inputByteIndex = SecondByte;
            break;
        case SecondByte:
            // from last and bits 7..4 as 3..0 from this
            textStream << encodeData->mapByte( bitsFromLastByte | byte >> 4 );
            // bits 3..0 -> 5..2 for next
            bitsFromLastByte = (byte & 0xf) << 2;
            inputByteIndex = ThirdByte;
            break;
        case ThirdByte:
            // from last and bits 7..6 as 1..0 from this
            textStream << encodeData->mapByte( bitsFromLastByte | byte >> 6 );
            // bits 5..0
            textStream << encodeData->mapByte( byte & 0x3F );
            inputByteIndex = FirstByte;
            ++inputGroupsPerLine;
            if( inputGroupsPerLine >= maxInputGroupsPerLine && i<range.end() )
            {
                const int remainsCount = range.end() - i;
                const int nextLineLength = qMin( remainsCount, inputLineLength );
                textStream << '\n';
                if( encodeData->hasLength )
                    textStream << encodeData->mapByte( nextLineLength );
                inputGroupsPerLine = 0;
            }
            break;
        }
    }
    const bool hasBitsLeft = ( inputByteIndex != FirstByte );
    if( hasBitsLeft )
        textStream << encodeData->mapByte(bitsFromLastByte)
                   << encodeData->padding(inputByteIndex);
    // footer
    textStream << encodeData->footer;

    return success;
}

ByteArrayUuEncodingStreamEncoder::~ByteArrayUuEncodingStreamEncoder() {}

}