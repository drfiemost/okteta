/***************************************************************************
                          khebrowserextension.cpp  -  description
                             -------------------
    begin                : Di Nov 16 2004
    copyright            : (C) 2004 by Friedrich W. H. Kossebau
    email                : Friedrich.W.H@Kossebau.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License version 2 as published by the Free Software Foundation.       *
 *                                                                         *
 ***************************************************************************/


// app specific
#include "khexedit.h"
#include "khepart.h"
#include "khebrowserextension.h"

using namespace KHE;


KHexEditBrowserExtension::KHexEditBrowserExtension( KHexEditPart *P, KHexEdit* HE )
  : KParts::BrowserExtension( P, "khexeditpartbrowserextension" ),
  HexEdit( HE )
{
  connect( HexEdit, SIGNAL( selectionChanged() ), this, SLOT( slotSelectionChanged() ) );
}

void KHexEditBrowserExtension::copy()
{
  HexEdit->copy();
}


void KHexEditBrowserExtension::slotSelectionChanged()
{
  emit enableAction( "copy", HexEdit->hasSelectedData() );
}


void KHexEditBrowserExtension::saveState( QDataStream &stream )
{
  KParts::BrowserExtension::saveState( stream );

  stream << (int)HexEdit->resizeStyle() << (int)HexEdit->coding() 
      << (int)HexEdit->encoding() << (int)HexEdit->showUnprintable()
      << HexEdit->contentsX() << HexEdit->contentsY()
      << HexEdit->cursorPosition() << (int)HexEdit->isCursorBehind();
}


void KHexEditBrowserExtension::restoreState( QDataStream &stream )
{
  KParts::BrowserExtension::restoreState( stream );

  int ResizeStyle;
  int Coding;
  int Encoding;
  int ShowUnprintable;
  int x, y;
  int Position;
  int CursorBehind;

  stream >> ResizeStyle >> Coding >> Encoding >> ShowUnprintable >> x >> y >> Position >> CursorBehind;

  HexEdit->setResizeStyle( (KHE::KHexEdit::KResizeStyle)ResizeStyle );
  HexEdit->setCoding( (KHE::KHexEdit::KCoding)Coding );
  HexEdit->setEncoding( (KHE::KHexEdit::KEncoding)Encoding );
  HexEdit->setShowUnprintable( ShowUnprintable );
  HexEdit->setContentsPos( x, y );
  HexEdit->setCursorPosition( Position, CursorBehind );
}
