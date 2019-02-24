/*
    This file is part of the Okteta Gui library, made within the KDE community.

    Copyright 2003,2008,2019 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef OKTETA_VALUEBYTEARRAYCOLUMNRENDERER_HPP
#define OKTETA_VALUEBYTEARRAYCOLUMNRENDERER_HPP

// lib
#include <okteta/abstractbytearraycolumnrenderer.hpp>
// Okteta core
#include <Okteta/Byte>

namespace Okteta {

class ValueCodec;

class ValueByteArrayColumnRendererPrivate;

/** buffer column which displays the numerical values of the bytes
 *
 * @author Friedrich W. H. Kossebau
 */
class OKTETAGUI_EXPORT ValueByteArrayColumnRenderer : public AbstractByteArrayColumnRenderer
{
public:
    ValueByteArrayColumnRenderer(AbstractColumnStylist* stylist,
                                 AbstractByteArrayModel* byteArrayModel, ByteArrayTableLayout* layout, ByteArrayTableRanges* ranges);
    ValueByteArrayColumnRenderer() = delete;

    ~ValueByteArrayColumnRenderer() override;

public:
    void renderEditedByte(QPainter* painter, Byte byte, const QString& editBuffer);

public: // modification access
    void setValueCodec(ValueCoding valueCoding, const ValueCodec* valueCodec);
    /** sets the spacing in the middle of a binary byte in the value column
     * @param binaryGapWidth spacing in the middle of a binary in pixels
     * returns true if there was a change
     */
    bool setBinaryGapWidth(PixelX binaryGapWidth);

public: // value access
    PixelX binaryGapWidth() const;

private:
    Q_DECLARE_PRIVATE(ValueByteArrayColumnRenderer)
};

}

#endif
