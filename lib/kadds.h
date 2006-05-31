/***************************************************************************
                          kadds.h  -  description
                             -------------------
    begin                : Die Mai 20 2003
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

 
#ifndef KHE_KADDS_H
#define KHE_KADDS_H

namespace KHE {
class KSection;
}

namespace KHEUI
{
// some possibly useful additions to KDE

// these are to emphasize that measuring unit is pixel and which direction
typedef int KPixelX;
typedef int KPixelY;

typedef KHE::KSection KPixelXs;
typedef KHE::KSection KPixelYs;
}

#endif
