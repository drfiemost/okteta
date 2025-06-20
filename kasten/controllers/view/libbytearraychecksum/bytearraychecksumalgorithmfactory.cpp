/*
    This file is part of the Okteta Kasten module, made within the KDE community.

    Copyright 2009,2011 Friedrich W. H. Kossebau <kossebau@kde.org>

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

#include "bytearraychecksumalgorithmfactory.h"

// lib
#include "algorithm/crc32bytearraychecksumalgorithm.h"
#include "algorithm/adler32bytearraychecksumalgorithm.h"
#include "algorithm/modsum8bytearraychecksumalgorithm.h"
#include "algorithm/modsum16bytearraychecksumalgorithm.h"
#include "algorithm/modsum32bytearraychecksumalgorithm.h"
#include "algorithm/modsum64bytearraychecksumalgorithm.h"
// NEWCHECKSUM(start)
// Here add the name of your header file of your checksum algorithm,
// e.g.
// #include "algorithm/mybytearraychecksumalgorithm.h"
// NEWCHECKSUM(end)
// KDE
#include <KLocale>


QList<AbstractByteArrayChecksumAlgorithm*> ByteArrayChecksumAlgorithmFactory::createAlgorithms()
{
    QList<AbstractByteArrayChecksumAlgorithm*> result;

    result
        << new ModSum8ByteArrayChecksumAlgorithm()
        << new ModSum16ByteArrayChecksumAlgorithm()
        << new ModSum32ByteArrayChecksumAlgorithm()
        << new ModSum64ByteArrayChecksumAlgorithm()
        << new Adler32ByteArrayChecksumAlgorithm()
        << new Crc32ByteArrayChecksumAlgorithm();
// NEWCHECKSUM(start)
// Here add the creation of an object of your checksum algorithm class and add it to the list,
// e.g.
//     result
//         << new MyByteArrayChecksumAlgorithm();
// NEWCHECKSUM(end)

    return result;
}
