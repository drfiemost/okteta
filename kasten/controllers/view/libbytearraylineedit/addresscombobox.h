/*
    This file is part of the Okteta Kasten module, part of the KDE project.

    Copyright 2009 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef ADDRESSCOMBOBOX_H
#define ADDRESSCOMBOBOX_H

// Qt
#include <QtGui/QWidget>

class AddressComboBoxPrivate;
class QString;
class QByteArray;


class AddressComboBox : public QWidget
{
  Q_OBJECT

  public:
    // TODO: same as in kbytearrayvalidator.h, we need a global enum containing both value and char codings...
    // matching Okteta::ValueCoding
    // TODO: turn into flags, so the codings to be used can be defined
    enum Coding { InvalidCoding = -1, HexadecimalCoding=0, DecimalCoding=1, OctalCoding=2, BinaryCoding=3, CharCoding=4 };

  public:
    explicit AddressComboBox( QWidget* parent = 0 );
    virtual ~AddressComboBox();

  public: // set
    void addAddress();

  public: // get
    qint32 address() const;
    int format() const;

  Q_SIGNALS:
    void addressChanged( qint32 address );
    void formatChanged( int index );

  protected:
    AddressComboBoxPrivate* const d_ptr;
  private:
    Q_DECLARE_PRIVATE( AddressComboBox )
    Q_PRIVATE_SLOT( d_func(), void onFormatChanged( int index ) )
    Q_PRIVATE_SLOT( d_func(), void onValueChanged( const QString& value ) )
};

#endif
