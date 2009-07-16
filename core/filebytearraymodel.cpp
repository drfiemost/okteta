/*
    This file is part of the Okteta Core library, part of the KDE project.

    Copyright 2003,2007 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "filebytearraymodel.h"

// lib
#include "filebytearraymodel_p.h"
// C
#include <stdlib.h>


namespace Okteta
{

FileByteArrayModel::FileByteArrayModel( int pageNumber, int pageSize )
 : d( new FileByteArrayModelPrivate(pageNumber,pageSize) )
{
}

int FileByteArrayModel::size()        const { return d->size(); }
bool FileByteArrayModel::isReadOnly() const { return d->isReadOnly(); }
bool FileByteArrayModel::isModified() const { return false; }
bool FileByteArrayModel::isOpen()     const { return d->isOpen(); }

void FileByteArrayModel::setReadOnly( bool readOnly ) { d->setReadOnly( readOnly ); }
void FileByteArrayModel::setModified( bool )  {}
void FileByteArrayModel::setDatum( unsigned int, const char )  {}
char FileByteArrayModel::datum( unsigned int datumOffset ) const { return d->datum( datumOffset ); }

int FileByteArrayModel::insert( int /*Pos*/, const char*, int /*Length*/ ) {  return 0; }
int FileByteArrayModel::remove( const Section &/*Section*/ ) {  return 0; }
unsigned int FileByteArrayModel::replace( const Section &/*Section*/, const char*, unsigned int /*Length*/ ) {  return 0; }
int FileByteArrayModel::fill( char /*FillChar*/, unsigned int /*Pos*/, int /*Length*/ ) {  return 0; }
bool FileByteArrayModel::swap( int /*DestPos*/, const Section &/*SourceSection*/ ) { return false; }

bool FileByteArrayModel::open( const QString &fileName ) { return d->open( fileName ); }
bool FileByteArrayModel::close() { return d->close(); }

FileByteArrayModel::~FileByteArrayModel()
{
    delete d;
}

}
