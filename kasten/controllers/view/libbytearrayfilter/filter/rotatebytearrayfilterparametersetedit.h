/*
    This file is part of the Okteta Kasten module, part of the KDE project.

    Copyright 2008 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef ROTATEBYTEARRAYFILTERPARAMETERSETEDIT_H
#define ROTATEBYTEARRAYFILTERPARAMETERSETEDIT_H

// lib
#include "abstractbytearrayfilterparametersetedit.h"

class KIntNumInput;

class RotateByteArrayFilterParameterSetEdit : public AbstractByteArrayFilterParameterSetEdit
{
  Q_OBJECT

  public:
    RotateByteArrayFilterParameterSetEdit( QWidget* parent = 0 );
    virtual ~RotateByteArrayFilterParameterSetEdit();

  public: // AbstractByteArrayFilterParameterSetEdit API
    virtual void setValues( const AbstractByteArrayFilterParameterSet *parameterSet );
    virtual void getParameterSet( AbstractByteArrayFilterParameterSet *parameterSet ) const;
    virtual bool isValid() const;

  protected Q_SLOTS:
    void onValueChanged( int value );

  protected:
    KIntNumInput* mGroupSizeEdit;
    KIntNumInput* mMoveBitWidthEdit;
};

#endif
