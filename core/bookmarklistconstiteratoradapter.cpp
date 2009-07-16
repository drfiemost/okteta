/*
    This file is part of the Okteta Core library, part of the KDE project.

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

#include "bookmarklistconstiteratoradapter.h"

// lib
#include "bookmarklist.h"


namespace Okteta
{

BookmarkListConstIteratorAdapter::BookmarkListConstIteratorAdapter( const BookmarkList& list )
 : mIterator( list )
{
}

bool BookmarkListConstIteratorAdapter::hasNext() const     { return mIterator.hasNext(); }
bool BookmarkListConstIteratorAdapter::hasPrevious() const { return mIterator.hasPrevious(); }
const Okteta::Bookmark& BookmarkListConstIteratorAdapter::peekNext() const     { return mIterator.peekNext(); }
const Okteta::Bookmark& BookmarkListConstIteratorAdapter::peekPrevious() const { return mIterator.peekPrevious(); }

bool BookmarkListConstIteratorAdapter::findNext( const Okteta::Bookmark& bookmark )     { return mIterator.findNext( bookmark ); }
bool BookmarkListConstIteratorAdapter::findPrevious( const Okteta::Bookmark& bookmark ) { return mIterator.findPrevious( bookmark ); }

bool BookmarkListConstIteratorAdapter::findNextFrom( unsigned int offset )
{
    bool result = false;

    mIterator.toFront();
    while( mIterator.hasNext() )
    {
        if( (int)offset <= mIterator.peekNext().offset() )
        {
            result = true;
            break;
        }
        next();
    }

    return result;
}

bool BookmarkListConstIteratorAdapter::findPreviousFrom( unsigned int offset )
{
    bool result = false;

    mIterator.toBack();
    while( mIterator.hasPrevious() )
    {
        if( mIterator.peekPrevious().offset() <= (int)offset )
        {
            result = true;
            break;
        }
        previous();
    }

    return result;
}

const Okteta::Bookmark& BookmarkListConstIteratorAdapter::next()     { return mIterator.next(); }
const Okteta::Bookmark& BookmarkListConstIteratorAdapter::previous() { return mIterator.previous(); }

void BookmarkListConstIteratorAdapter::toBack()  { mIterator.toBack(); }
void BookmarkListConstIteratorAdapter::toFront() { mIterator.toFront(); }


BookmarkListConstIteratorAdapter::~BookmarkListConstIteratorAdapter() {}

}
