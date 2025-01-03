/*
 *   This file is part of the Okteta Kasten Framework, made within the KDE community.
 *
 *   Copyright 2009 Alex Richardson <alex.richardson@gmx.de>
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) version 3, or any
 *   later version accepted by the membership of KDE e.V. (or its
 *   successor approved by the membership of KDE e.V.), which shall
 *   act as a proxy defined in Section 6 of version 3 of the license.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public
 *   License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef STRUCTVIEWDISPLAYSETTINGSWIDGET_H_
#define STRUCTVIEWDISPLAYSETTINGSWIDGET_H_
#include "ui_structviewdisplaysettingswidget.h"
#include <QtGui/QWidget>

class KConfigSkeletonItem;

class StructViewDisplaySettingsWidget: public QWidget
{
Q_OBJECT
public:
    explicit StructViewDisplaySettingsWidget();
    ~StructViewDisplaySettingsWidget();
private:
    void setupBasesCombo(QComboBox* box, KConfigSkeletonItem* configItem,
            int currentValue, const char* slot);
    void handleMapping(int index, QComboBox* box, QSpinBox* spin);
private:
    Ui_StructViewSettings ui;
private slots:
    void setCharDisplay(int index);
    void setSignedDisplay(int index);
    void setUnsignedDisplay(int index);
};

#endif /* STRUCTVIEWDISPLAYSETTINGSWIDGET_H_ */
