/*
    Copyright 2006-2007 Will Stephenson <wstephenson@kde.org>
    Copyright 2006-2007 Kevin Ottens <ervin@kde.org>

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

#ifndef SOLID_NETWORKING
#define SOLID_NETWORKING

#include <QtCore/QObject>

#include <solid/solid_export.h>

namespace Solid
{
    /**
     * This namespace contains all the network-related high-level methods:
     * querying the underlying system for network availability,
     * being notified when network availability changes
     * (e.g. due to interfaces appearing or disappearing).
     *
     * It also allows application to specify the connection and disconnection policies
     * that it would like to use, for the network.
     */
    namespace Networking
    {
        /**
         * Describes the state of the networking system
         */
        enum Status {
            Unknown, /**< the networking system is not active or unable to report its status - proceed with caution */
            Unconnected,/**< the system is not connected to any network */
            Disconnecting, /**< the system is breaking the connection */
            Connecting, /**< the system is not connected to any network */
            Connected /**< the system is currently connected to a network */
        };

        /**
         * This defines application policy in response to networking connect/disconnect events
         */
        enum ManagementPolicy {
            Manual, /**< Manual - the app should only disconnect when the user does so manually */
            OnNextStatusChange, /**< the app should connect or disconnect the next time the network changes status, thereafter Manual */
            Managed /**< the app should connect or disconnect whenever the KConnectionManager reports a state change */
        };

        /**
         * Get the current networking status
         * If the result is Unknown, the backend may be unconfigured or otherwise in a state where
         * it cannot report useful networking status @ref Solid::Networking::Status.
         */
        SOLID_EXPORT Status status();

        /**
         * Set a policy to manage the application's connect behaviour
         * @param policy the new connection policy
         */
        SOLID_EXPORT void setConnectPolicy( ManagementPolicy policy );

        /**
         * Retrieve a policy managing the application's connect behaviour
         * @return the connection policy in use
         */
        SOLID_EXPORT ManagementPolicy connectPolicy();

        /**
         * Set a policy to manage the application's disconnect behaviour
         * @param policy the new disconnection policy
         */
        SOLID_EXPORT void setDisconnectPolicy( ManagementPolicy policy );

        /**
         * Retrieve a policy managing the application's disconnect behaviour
         * @return the disconnection policy in use
         */
        SOLID_EXPORT ManagementPolicy disconnectPolicy();

        /**
         * This object emits signals, for use if your application requires notification
         * of changes to networking.
         */
        class SOLID_EXPORT Notifier : public QObject
        {
        Q_OBJECT
        Q_SIGNALS:
        /**
         * Signals that the network status has changed
         * @param status the new status of the network status service
         */
        void statusChanged( Solid::Networking::Status status );
        /**
         * Signals that the system's network has become connected, so receivers
         * should connect their sockets, ioslaves etc.
         *
         * This signal is emitted according to the active connectPolicy.
         */
        void shouldConnect();
        /**
         * Signals that the system's network has become disconnected,
         * so receivers should adjust application state appropriately.
         *
         * This signal is emitted according to the active disconnectPolicy.
         */
        void shouldDisconnect();

        protected:
        Notifier();
        };

        SOLID_EXPORT Notifier *notifier();
    }

} // Solid

#endif
