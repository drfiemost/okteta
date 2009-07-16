/*
    This file is part of the Okteta Core library, part of the KDE project.

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

#include "revertablepiecetabletest.h"

// test object
#include <piecetable/revertablepiecetable.h>
// Qt
#include <QtTest/QtTest>

using namespace KDE;
// local variables
static const int Start = 15;
static const int End = 27;
static const int HalfSize = 50;
static const int Size = 2 * HalfSize;

static const int Width = End - Start + 1;

static const int ChangeStart = 0;
static const int ChangeEnd = ChangeStart + Width - 1;

namespace KPieceTable
{

void RevertablePieceTableTest::testSimpleConstructor()
{
    RevertablePieceTable pieceTable;
    QCOMPARE( pieceTable.size(), 0 );
    QCOMPARE( pieceTable.changesCount(), 0 );
    QCOMPARE( pieceTable.appliedChangesCount(), 0 );
}


void RevertablePieceTableTest::testInit()
{
    RevertablePieceTable pieceTable;

    pieceTable.init( Size );
    int storageId;
    int storageOffset;

        QCOMPARE( pieceTable.size(), Size );
        QCOMPARE( pieceTable.changesCount(), 0 );
        QCOMPARE( pieceTable.appliedChangesCount(), 0 );

        bool result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( result );
        QCOMPARE( storageOffset, 0 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, End );
        QVERIFY( result );
        QCOMPARE( storageOffset, End );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Size-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size );
        QVERIFY( !result );
}

static void fillWithSize( RevertablePieceTable *pieceTable, int count )
{
    int dummy;
    pieceTable->init( 0 );
    for( int i=0; i<count; ++i )
        pieceTable->insert( 0, Size, &dummy );
}

void RevertablePieceTableTest::testInsert()
{
    RevertablePieceTable pieceTable;

    int storageId;
    int storageOffset;
    bool result;

    //inserting to empty
    pieceTable.init( 0 );
    pieceTable.insert( 0, Width, &storageOffset );

        QCOMPARE( pieceTable.size(), Width );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );
        QCOMPARE( storageOffset, ChangeStart );

        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( result );
        QCOMPARE( storageOffset, ChangeStart );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Width-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, ChangeEnd );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Width );
        QVERIFY( !result );

    // inserting one at the begin
    pieceTable.init( Size );
    pieceTable.insert( 0, Width, &storageOffset );

        QCOMPARE( pieceTable.size(), Size+Width );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );
        QCOMPARE( storageOffset, ChangeStart );

        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( result );
        QCOMPARE( storageOffset, ChangeStart );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Width-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, ChangeEnd );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Width );
        QVERIFY( result );
        QCOMPARE( storageOffset, 0 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size+Width-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Size-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size+Width );
        QVERIFY( !result );

    // inserting one in the middle
    pieceTable.init( Size );
    pieceTable.insert( Start, Width, &storageOffset );

        QCOMPARE( pieceTable.size(), Size+Width );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );
        QCOMPARE( storageOffset, ChangeStart );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start );
        QVERIFY( result );
        QCOMPARE( storageOffset, ChangeStart );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, End );
        QVERIFY( result );
        QCOMPARE( storageOffset, ChangeEnd );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, End+1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size+Width-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Size-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size+Width );
        QVERIFY( !result );

    // inserting one at the end
    pieceTable.init( Size );
    pieceTable.insert( Size, Width, &storageOffset );

        QCOMPARE( pieceTable.size(), Size+Width );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );
        QCOMPARE( storageOffset, ChangeStart );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Size-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size );
        QVERIFY( result );
        QCOMPARE( storageOffset, ChangeStart );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size+Width-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, ChangeEnd );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size+Width );
        QVERIFY( !result );

    // inserting a lot:
    // inserting before, after and in another inserted section, two recursions
    // 121110  8 7 6  4 3 2
    // \/\/\/ \/\/\/ \/\/\/
    //  |-9-|  |-5-|  |-1-|
    //  \  /   \  /   \  /
    //   \/     \/     \/
    //    |-----0-------|
    // TODO: do this also in forward sequences
    pieceTable.init( Size ); // 0
    const int Mid = Size/2;
    int changeStarts[13];
    pieceTable.insert( Size, Size, &storageOffset ); // 1
    changeStarts[1] = storageOffset;
    pieceTable.insert( Size+Size, Size, &storageOffset ); // 2
    changeStarts[2] = storageOffset;
    pieceTable.insert( Size+Mid, Size, &storageOffset ); // 3
    changeStarts[3] = storageOffset;
    pieceTable.insert( Size, Size, &storageOffset ); // 4
    changeStarts[4] = storageOffset;

    pieceTable.insert( Mid, Size, &storageOffset ); // 5
    changeStarts[5] = storageOffset;
    pieceTable.insert( Mid+Size, Size, &storageOffset ); // 6
    changeStarts[6] = storageOffset;
    pieceTable.insert( Mid+Mid, Size, &storageOffset ); // 7
    changeStarts[7] = storageOffset;
    pieceTable.insert( Mid, Size, &storageOffset ); // 8
    changeStarts[8] = storageOffset;

    pieceTable.insert( 0, Size, &storageOffset ); // 9
    changeStarts[9] = storageOffset;
    pieceTable.insert( Size, Size, &storageOffset ); // 10
    changeStarts[10] = storageOffset;
    pieceTable.insert( Mid, Size, &storageOffset ); // 11
    changeStarts[11] = storageOffset;
    pieceTable.insert( 0, Size, &storageOffset ); // 12
    changeStarts[12] = storageOffset;

    // test
    QCOMPARE( pieceTable.size(), Size+12*Size );
    QCOMPARE( pieceTable.changesCount(), 9 ); // 9+10, 5+6, 1+2 are merged
    QCOMPARE( pieceTable.appliedChangesCount(), 9 );
    QCOMPARE( storageOffset, 11*Size );

    // all borders
    // 12: begin
    int byteArrayOffset = 0;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[12] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 12: end
    byteArrayOffset += Size;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[12]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[9] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 11: begin
    byteArrayOffset += HalfSize;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[9]+HalfSize-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[11] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 11: end
    byteArrayOffset += Size;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[11]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[9]+HalfSize );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 10: begin
    byteArrayOffset += HalfSize;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[9]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[10] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 10: end
    byteArrayOffset += Size;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[10]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, 0 );
    QCOMPARE( storageId, (int)Piece::OriginalStorage );

    // 8: begin
    byteArrayOffset += HalfSize;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, HalfSize-1 );
    QCOMPARE( storageId, (int)Piece::OriginalStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[8] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 8: end
    byteArrayOffset += Size;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[8]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[5] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 7: begin
    byteArrayOffset += HalfSize;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[5]+HalfSize-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[7] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 7: end
    byteArrayOffset += Size;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[7]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[5]+HalfSize );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 6: begin
    byteArrayOffset += HalfSize;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[5]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[6] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 6: end
    byteArrayOffset += Size;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[6]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, HalfSize );
    QCOMPARE( storageId, (int)Piece::OriginalStorage );

    // 4: begin
    byteArrayOffset += HalfSize;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, Size-1 );
    QCOMPARE( storageId, (int)Piece::OriginalStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[4] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 4: end
    byteArrayOffset += Size;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[4]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[1] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 3: begin
    byteArrayOffset += HalfSize;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[1]+HalfSize-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[3] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 3: end
    byteArrayOffset += Size;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[3]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[1]+HalfSize );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 2: begin
    byteArrayOffset += HalfSize;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[1]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[2] );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    // 2: end
    byteArrayOffset += Size;
    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset-1 );
    QVERIFY( result );
    QCOMPARE( storageOffset, changeStarts[2]+Size-1 );
    QCOMPARE( storageId, (int)Piece::ChangeStorage );

    result = pieceTable.getStorageData( &storageId, &storageOffset, byteArrayOffset );
    QVERIFY( !result );
}

void RevertablePieceTableTest::testRemove()
{
    RevertablePieceTable pieceTable;

    int changeStarts[6];
    int storageId;
    int storageOffset;
    bool result;

    // removing at begin
    pieceTable.init( Size );
    pieceTable.remove( KDE::Section(0, Start-1) );

        QCOMPARE( pieceTable.size(), Size-Start );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Size-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-Start );
        QVERIFY( !result );

    // removing at middle
    pieceTable.init( Size );
    pieceTable.remove( KDE::Section(Start, End) );

        QCOMPARE( pieceTable.size(), Size-Width );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start );
        QVERIFY( result );
        QCOMPARE( storageOffset, End+1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-Width-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Size-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-Width );
        QVERIFY( !result );

    // removing at end
    pieceTable.init( Size );
    pieceTable.remove( KDE::Section(End+1, Size-1) );

        QCOMPARE( pieceTable.size(), End+1 );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, End );
        QVERIFY( result );
        QCOMPARE( storageOffset, End );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, End+1 );
        QVERIFY( !result );

    // removing all
    pieceTable.init( Size );
    pieceTable.remove( KDE::Section::fromWidth(Size) );

        QCOMPARE( pieceTable.size(), 0 );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( !result );


    // removing a lot:
    const int pieceCount = 5;
    const int mid = (pieceCount+1)/2;
    const int midPieceOffset = Size * (mid-1);
    const int fullSize = pieceCount * Size;
    // for this five equally sized pieces are inserted, reverse to offset in ChangeStore
    for( int i=0; i<pieceCount; ++i ) changeStarts[pieceCount-i] = Size*i;

    // removing inside a piece in the middle
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(midPieceOffset+Start, Width) );

        QCOMPARE( pieceTable.size(), fullSize-Width );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset+Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid]+Start-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset+Start );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid]+End+1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Width-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Width );
        QVERIFY( !result );

    // removing start of a piece in the middle
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(midPieceOffset, Start) );

        QCOMPARE( pieceTable.size(), fullSize-Start );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid-1]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid]+Start );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Start );
        QVERIFY( !result );

    // removing end of a piece in the middle
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(midPieceOffset+End+1, Size-(End+1)) );

        QCOMPARE( pieceTable.size(), fullSize-(Size-End-1) );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset+End );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid]+End );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset+End+1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid+1] );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-(Size-End-1)-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-(Size-End-1) );
        QVERIFY( !result );

    // removing whole piece in the middle
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(midPieceOffset, Size) );

        QCOMPARE( pieceTable.size(), fullSize-Size );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid-1]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid+1] );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size );
        QVERIFY( !result );

    // removing whole piece and start of next in the middke
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(midPieceOffset, Size+Start) );

        QCOMPARE( pieceTable.size(), fullSize-Size-Start );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid-1]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid+1]+Start );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-Start );
        QVERIFY( !result );

    // removing whole piece and end of previous in the middle
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(midPieceOffset-(Size-End-1), Size+Size-(End+1)) );

        QCOMPARE( pieceTable.size(), fullSize-Size-(Size-End-1) );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset-(Size-End-1)-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid-1]+End );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset-(Size-End-1) );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid+1] );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-(Size-End-1)-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-(Size-End-1) );
        QVERIFY( !result );

    // removing end of previous, whole and start of next in the middle
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(midPieceOffset-(Size-End-1), Start+Size+Size-(End+1)) );

        QCOMPARE( pieceTable.size(), fullSize-Size-(Size-End-1)-Start );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset-(Size-End-1)-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid-1]+Size-(Size-End-1)-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, midPieceOffset-(Size-End-1) );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[mid+1]+Start );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-(Size-End-1)-Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-(Size-End-1)-Start );
        QVERIFY( !result );

    // removing start of piece at start
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(Start) );

        QCOMPARE( pieceTable.size(), fullSize-Start );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[1]+Start );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Start );
        QVERIFY( !result );

    // removing whole piece at start
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(Size) );

        QCOMPARE( pieceTable.size(), fullSize-Size );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[2] );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size );
        QVERIFY( !result );

    // removing whole piece and start of next at start
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(Size+Start) );

        QCOMPARE( pieceTable.size(), fullSize-Size-Start );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[2]+Start );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-Start );
        QVERIFY( !result );

    // removing end of piece at end
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(fullSize-Size+End+1, Size-(End+1)) );

        QCOMPARE( pieceTable.size(), fullSize-(Size-End-1) );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size+End );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount]+End );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-(Size-End-1) );
        QVERIFY( !result );

    // removing whole piece at end
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(fullSize-Size, Size) );

        QCOMPARE( pieceTable.size(), fullSize-Size );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount-1]+Size-1 );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size );
        QVERIFY( !result );

    // removing whole piece and end of previous at end
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(fullSize-Size-(Size-End-1), Size+Size-(End+1)) );

        QCOMPARE( pieceTable.size(), fullSize-Size-(Size-End-1) );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-(Size-End-1)-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, changeStarts[pieceCount-1]+End );
        QCOMPARE( storageId, (int)Piece::ChangeStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, fullSize-Size-(Size-End-1) );
        QVERIFY( !result );

    // removing all 
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.remove( KDE::Section::fromWidth(fullSize) );

        QCOMPARE( pieceTable.size(), 0 );
        QCOMPARE( pieceTable.changesCount(), pieceCount+1 );
        QCOMPARE( pieceTable.appliedChangesCount(), pieceCount+1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( !result );
}

void RevertablePieceTableTest::testSwap()
{
    RevertablePieceTable pieceTable;

    int storageId;
    int storageOffset;
    bool result;

    // moving end at begin
    pieceTable.init( Size );
    pieceTable.swap( 0, KDE::Section::fromWidth(End+1, Size-(End+1)) );

        QCOMPARE( pieceTable.size(), Size );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( result );
        QCOMPARE( storageOffset, End+1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-End-2 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Size-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-End-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, 0 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, End );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size );
        QVERIFY( !result );

    // moving end at mid
    pieceTable.init( Size );
    pieceTable.swap( Start, KDE::Section::fromWidth(End+1, Size-(End+1)) );

        QCOMPARE( pieceTable.size(), Size );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        QCOMPARE( pieceTable.size(), Size );
        result = pieceTable.getStorageData( &storageId, &storageOffset, Start );
        QVERIFY( result );
        QCOMPARE( storageOffset, End+1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start+Size-End-2 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Size-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start+Size-End-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, End );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Size );
        QVERIFY( !result );

    // moving mid at begin
    pieceTable.init( Size );
    pieceTable.swap( 0, KDE::Section::fromWidth(Start, Width) );

        QCOMPARE( pieceTable.size(), Size );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );

        QCOMPARE( pieceTable.size(), Size );
        result = pieceTable.getStorageData( &storageId, &storageOffset, 0 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Width-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, End );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Width );
        QVERIFY( result );
        QCOMPARE( storageOffset, 0 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, End );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, End+1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, End+1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

    // moving mid at mid
    pieceTable.init( Size );
    int mid = (End+Start)/2;
    pieceTable.swap( Start, KDE::Section::fromWidth(mid, End-mid+1) );

        QCOMPARE( pieceTable.size(), Size );
        QCOMPARE( pieceTable.changesCount(), 1 );
        QCOMPARE( pieceTable.appliedChangesCount(), 1 );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start-1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start );
        QVERIFY( result );
        QCOMPARE( storageOffset, mid );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start+End-mid );
        QVERIFY( result );
        QCOMPARE( storageOffset, End );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, Start+End-mid+1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, Start );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, End );
        QVERIFY( result );
        QCOMPARE( storageOffset, mid-1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

        result = pieceTable.getStorageData( &storageId, &storageOffset, End+1 );
        QVERIFY( result );
        QCOMPARE( storageOffset, End+1 );
        QCOMPARE( storageId, (int)Piece::OriginalStorage );

    // moving a lot:
    const int pieceCount = 5;
    const int fullSize = pieceCount * Size;
    const int midPiece = (pieceCount+1)/2;
    const int midPieceOffset = Size * (midPiece-1);
    int changeStarts[6];
    for( int i=0; i<pieceCount; ++i ) changeStarts[pieceCount-i] = Size*i;

    // moving start of piece at start
    fillWithSize( &pieceTable, pieceCount );
    pieceTable.swap( Start, KDE::Section::fromWidth(mid, End-mid+1) );

        QCOMPARE( pieceTable.size(), fullSize );
    //TODO: add other tests
}

}

QTEST_MAIN( KPieceTable::RevertablePieceTableTest )
