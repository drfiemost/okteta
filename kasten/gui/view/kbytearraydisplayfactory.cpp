/*
    This file is part of the Okteta Kasten module, part of the KDE project.

    Copyright 2006,2009 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "kbytearraydisplayfactory.h"

// lib
#include "kbytearraydisplay.h"
#include <kbytearraydocument.h>


namespace Kasten
{

AbstractView* KByteArrayDisplayFactory::createViewFor( AbstractDocument* _document )
{
    KByteArrayDisplay* result = 0;

    KByteArrayDocument* document = static_cast<KByteArrayDocument*>( _document );
    if( document )
        result = new KByteArrayDisplay( document );

    return result;
}

AbstractView* KByteArrayDisplayFactory::createCopyOfView( AbstractView* _view, Qt::Alignment alignment )
{
    KByteArrayDisplay* result = 0;

    KByteArrayDisplay* view = qobject_cast<KByteArrayDisplay*>( _view );
    if( view )
        result = new KByteArrayDisplay( view, alignment );

    return result;
}

}
