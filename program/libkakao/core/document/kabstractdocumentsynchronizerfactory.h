/***************************************************************************
                          kabstractdocumentsynchronizerfactory.h  -  description
                             -------------------
    begin                : Mon Nov 19 2007
    copyright            : 2007 by Friedrich W. H. Kossebau
    email                : kossebau@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU General Public License           *
 *   version 2 as published by the Free Software Foundation.               *
 *                                                                         *
 ***************************************************************************/


#ifndef KABSTRACTDOCUMENTSYNCHRONIZERFACTORY_H
#define KABSTRACTDOCUMENTSYNCHRONIZERFACTORY_H

// lib
#include "kabstractdocumentsynchronizer.h"
// Qt
#include <QtCore/QObject>

class KUrl;

// not really a classic factory, functions do some more, instead it is what?
// TODO: improve the whole vodoo, especially linking document and synchronizer
// make it foolproof
// make a simple tutorial with an example program
class KAbstractDocumentSynchronizerFactory : public QObject
{
  Q_OBJECT

  public:
    virtual ~KAbstractDocumentSynchronizerFactory();

  public: // API to be implemented
    virtual KAbstractDocument *loadNewDocument( const KUrl &originUrl ) const = 0;
    // TODO: better name than connect: bind?
    virtual bool connectDocument( KAbstractDocument *document, const KUrl &originUrl,
                                  KAbstractDocumentSynchronizer::ConnectOption option ) const = 0;
    virtual bool exportDocument( KAbstractDocument *document, const KUrl &originUrl ) const = 0;

    /** returns the id of the work model type */
    // TODO: is QByteArray enough?
    virtual QString supportedWorkType() const = 0;
    /** returns the id of the remote model type */
    virtual QString supportedRemoteType() const = 0;
};

#endif
