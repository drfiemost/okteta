/*
    This file is part of the Kasten Framework, made within the KDE community.

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

#ifndef KASTEN_MODELSTREAMENCODETHREAD_HPP
#define KASTEN_MODELSTREAMENCODETHREAD_HPP

// lib
#include <kasten/kastencore_export.hpp>
// Qt
#include <QThread>

class QIODevice;

namespace Kasten {

class AbstractModelStreamEncoder;
class AbstractModel;
class AbstractModelSelection;

// TODO: instead of doubling all data just read them from the job?
class KASTENCORE_EXPORT ModelStreamEncodeThread : public QThread
{
    Q_OBJECT

public:
    ModelStreamEncodeThread(QObject* parent,
                            QIODevice* ioDevice,
                            AbstractModel* model, const AbstractModelSelection* selection,
                            AbstractModelStreamEncoder* encoder);
    ModelStreamEncodeThread() = delete;

    ~ModelStreamEncodeThread() override;

public: // QThread API
    void run() override;

public:
    bool success() const;

Q_SIGNALS:
    void modelExported(bool success);

private:
    QIODevice* mIODevice;
    AbstractModel* mModel;
    const AbstractModelSelection* mSelection;
    AbstractModelStreamEncoder* mEncoder;

    bool mSuccess = false;
};

inline ModelStreamEncodeThread::ModelStreamEncodeThread(QObject* parent,
                                                        QIODevice* ioDevice,
                                                        AbstractModel* model, const AbstractModelSelection* selection,
                                                        AbstractModelStreamEncoder* encoder)
    : QThread(parent)
    , mIODevice(ioDevice)
    , mModel(model)
    , mSelection(selection)
    , mEncoder(encoder)
{}

inline bool ModelStreamEncodeThread::success() const { return mSuccess; }

}

#endif
