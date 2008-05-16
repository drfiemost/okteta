/*
    This file is part of the Kakao Framework, part of the KDE project.

    Copyright 2007-2008 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#ifndef ABSTRACTMODELEXPORTER_H
#define ABSTRACTMODELEXPORTER_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QString>

class AbstractModel;
class AbstractModelSelection;
class KUrl;

class AbstractModelExporter : public QObject
{
  Q_OBJECT

  protected:
    AbstractModelExporter( const QString &remoteTypeName, const QString &remoteMimeType );
  public:
    virtual ~AbstractModelExporter();

  public: // API to be implemented
    virtual bool doExport( AbstractModel *model, const AbstractModelSelection *selection, const KUrl &url ) = 0;
    virtual QString modelTypeName( AbstractModel *model, const AbstractModelSelection *selection ) const
 { Q_UNUSED(model); Q_UNUSED(selection); return QString(); }//= 0;

  public:
    QString remoteTypeName() const;
    QString remoteMimeType() const;

  protected:
    class Private;
    Private * const d;
};

#endif
