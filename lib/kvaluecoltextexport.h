/***************************************************************************
                          kvaluecoltextexport.h  -  description
                             -------------------
    begin                : Sam Aug 30 2003
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


#ifndef KHE_UI_KVALUECOLTEXTEXPORT_H
#define KHE_UI_KVALUECOLTEXTEXPORT_H

// corelib specific
#include "kbytecodec.h"
// lib specific
#include "kbuffercoltextexport.h"


namespace KHEUI
{

class KValueColumn;


class KValueColTextExport : public KBufferColTextExport
{
  public:
    KValueColTextExport( const KValueColumn* BF, const char *D, const KCoordRange &CR );
    virtual ~KValueColTextExport();

  protected:
    virtual void print( QString *T ) const;


  protected:
    KHECore::KByteCodec *ByteCodec;
};

}

#endif
