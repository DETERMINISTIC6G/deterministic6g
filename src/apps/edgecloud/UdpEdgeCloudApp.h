//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef DETERMINISTIC6G_UDPEDGECLOUDAPP_H_
#define DETERMINISTIC6G_UDPEDGECLOUDAPP_H_

#include <omnetpp.h>
#include "inet/applications/udpapp/UdpEchoApp.h"

using namespace omnetpp;
using namespace inet;
namespace d6g {

/**
 * UDPEdgeCloudApp is based on the UdpEchoApp. It is used to forward packets to another node (or back) and delay them.
 * See the NED file for more info.
 */
class INET_API UdpEdgeCloudApp : public UdpEchoApp {
protected:
    virtual void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;

protected:
    L3Address destAddress;
    int destPort;
    cPar *delayParameter = nullptr;
};

} //namespace

#endif
