/***************************************************************************
                          kbyteseditwidget.cpp  -  description
                             -------------------
    begin                : Fri Aug 29 2003
    copyright            : (C) 2003 by Friedrich W. H. Kossebau
    email                : Friedrich.W.H@Kossebau.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License version 2 as published by the Free Software Foundation.       *
 *                                                                         *
 ***************************************************************************/


// qt specific
#include <qlayout.h>
// kde specific
#include <klocale.h>
#include <kgenericfactory.h>
#include <kapplication.h>
// app specific
#include "kbyteseditwidget.h"
#include "kbytesedit.h"


KBytesEditWidget::KBytesEditWidget( QWidget *parent, const char *name, const QStringList & )
  : QWidget( parent, name)
{
  QHBoxLayout* Layout = new QHBoxLayout( this );
  BytesEdit = new KHE::KBytesEdit( this, "BytesEdit" );
  Layout->addWidget( BytesEdit );
//   connect( _editor, SIGNAL( canUndo(bool) ), this, SIGNAL( canUndo(bool) ) );
}



void KBytesEditWidget::setData( char *D, int S, int RS, bool KM )
{
  BytesEdit->setData( D, S, RS, KM );
}


void KBytesEditWidget::setReadOnly( bool RO )
{
  BytesEdit->setReadOnly( RO );
}

void KBytesEditWidget::setMaxDataSize( int MS )
{
  BytesEdit->setMaxDataSize( MS );
}

void KBytesEditWidget::setAutoDelete( bool AD )
{
  BytesEdit->setAutoDelete( AD );
}


void KBytesEditWidget::setKeepsMemory( bool KM )
{
  BytesEdit->setKeepsMemory( KM );
}


void KBytesEditWidget::setCursorPosition( int Index )
{
  BytesEdit->setCursorPosition( Index );
}

void KBytesEditWidget::setCoding( KCoding C )
{
  BytesEdit->setCoding( (KHE::KHexEdit::KCoding) C );
}
void KBytesEditWidget::setResizeStyle( KResizeStyle Style )
{
  BytesEdit->setResizeStyle( (KHE::KHexEdit::KResizeStyle) Style );
}



void KBytesEditWidget::setOverwriteOnly( bool b )
{
  BytesEdit->setOverwriteOnly( b );
}


void KBytesEditWidget::setOverwriteMode( bool b )
{
  BytesEdit->setOverwriteMode( b );
}


void KBytesEditWidget::setModified( bool b )
{
  BytesEdit->setModified( b );
}

void KBytesEditWidget::setNoOfBytesPerLine( int NoCpL )
{
  BytesEdit->setNoOfBytesPerLine( NoCpL );
}

void KBytesEditWidget::setByteSpacingWidth( int BSW )
{
  BytesEdit->setByteSpacingWidth( BSW );
}

void KBytesEditWidget::setNoOfGroupedBytes( int NoGB )
{
  BytesEdit->setNoOfGroupedBytes( NoGB );
}

void KBytesEditWidget::setGroupSpacingWidth( int GSW )
{
  BytesEdit->setGroupSpacingWidth( GSW );
}

void KBytesEditWidget::setBinaryGapWidth( int BGW )
{
  BytesEdit->setBinaryGapWidth( BGW );
}


char *KBytesEditWidget::data() const
{
  return BytesEdit->data();
}

int KBytesEditWidget::dataSize() const
{
  return BytesEdit->dataSize();
}
int KBytesEditWidget::maxDataSize () const
{
  return BytesEdit->maxDataSize();
}
bool KBytesEditWidget::isAutoDelete() const
{
  return BytesEdit->isAutoDelete();
}

bool KBytesEditWidget::keepsMemory() const
{
  return BytesEdit->keepsMemory();
}

bool KBytesEditWidget::isOverwriteMode() const
{
  return BytesEdit->isOverwriteMode();
}

bool KBytesEditWidget::isOverwriteOnly() const
{
  return BytesEdit->isOverwriteOnly();
}

bool KBytesEditWidget::isModified() const
{
  return BytesEdit->isModified();
}

bool KBytesEditWidget::isReadOnly() const
{
  return BytesEdit->isReadOnly();
}


// bool KBytesEditWidget::tabChangesFocus() const
// {
// }


int KBytesEditWidget::noOfBytesPerLine() const
{
  return BytesEdit->noOfBytesPerLine();
}

KBytesEditWidget::KResizeStyle KBytesEditWidget::resizeStyle() const
{
  return (KResizeStyle)BytesEdit->resizeStyle();
}

KBytesEditWidget::KCoding KBytesEditWidget::coding() const
{
  return (KCoding)BytesEdit->coding();
}

int KBytesEditWidget::byteSpacingWidth() const
{
  return BytesEdit->byteSpacingWidth();
}

int KBytesEditWidget::noOfGroupedBytes() const
{
  return BytesEdit->noOfGroupedBytes();
}

int KBytesEditWidget::groupSpacingWidth() const
{
  return BytesEdit->groupSpacingWidth();
}

int KBytesEditWidget::binaryGapWidth() const
{
  return BytesEdit->binaryGapWidth();
}


bool KBytesEditWidget::hasSelectedData() const
{
  return BytesEdit->hasSelectedData();
}

void KBytesEditWidget::resetData( char *D, int S, bool Repaint )
{
  BytesEdit->resetData( D, S, Repaint );
}


void KBytesEditWidget::repaintRange( int i1, int i2 )
{
  BytesEdit->repaintRange( i1, i2 );
}


void KBytesEditWidget::insert( const QByteArray &D )
{
  BytesEdit->insert( D );
}


void KBytesEditWidget::selectAll( bool Select )
{
  BytesEdit->selectAll( Select );
}

  // clipboard interaction
void KBytesEditWidget::copy()
{
  BytesEdit->copy();
}

void KBytesEditWidget::cut()
{
  BytesEdit->cut();
}

void KBytesEditWidget::paste()
{
  BytesEdit->paste();
}

typedef K_TYPELIST_1( KBytesEditWidget ) Product;
K_EXPORT_COMPONENT_FACTORY( libkbyteseditwidget, KGenericFactory<Product>( "khexedit" ) )

#include "kbyteseditwidget.moc"
