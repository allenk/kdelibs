/*
    Copyright 2011 Mario Bensi <mbensi@ipsquad.net>

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

#include "networkshare.h"
#include "networkshare_p.h"

#include "soliddefs_p.h"
#include <solid/ifaces/networkshare.h>

Solid::NetworkShare::NetworkShare(QObject *backendObject)
    : DeviceInterface(*new NetworkSharePrivate(), backendObject)
{
}

Solid::NetworkShare::~NetworkShare()
{

}

Solid::NetworkShare::ShareType Solid::NetworkShare::type() const
{
    Q_D(const NetworkShare);
    return_SOLID_CALL(Ifaces::NetworkShare *, d->backendObject(), Solid::NetworkShare::Unknown, type());
}

QUrl Solid::NetworkShare::url() const
{
    Q_D(const NetworkShare);
    return_SOLID_CALL(Ifaces::NetworkShare *, d->backendObject(), QUrl(), url());
}

#include "networkshare.moc"

