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

#include "UdpEdgeCloudApp.h"
#include "inet/common/Simsignals.h"
#include "inet/networklayer/common/L3AddressResolver.h"

namespace d6g {
using namespace inet;

Define_Module(UdpEdgeCloudApp)

void UdpEdgeCloudApp::socketDataArrived(UdpSocket *socket, Packet *pk) {
    // determine its source address/port
    pk->clearTags();
    pk->trim();

    emit(packetSentSignal, pk);

    // Delay
    simtime_t delay = delayParameter->doubleValue();
    if (delay != 0) {
        scheduleAfter(delay, pk);
    } else {
        socket->sendTo(pk, destAddress, destPort);
    }

}

void UdpEdgeCloudApp::handleStartOperation(LifecycleOperation *operation) {
    UdpEchoApp::handleStartOperation(operation);

    const char *destAddr = par("destAddress");

    L3Address result;
    L3AddressResolver().tryResolve(destAddr, result);

    if (result.isUnspecified())
        EV_ERROR << "cannot resolve destination address: " << destAddr << endl;
    this->destAddress = result;
}

void UdpEdgeCloudApp::initialize(int stage) {
    UdpEchoApp::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        this->destPort = par("destPort");
        this->delayParameter = &par("delay");
    }
}

void UdpEdgeCloudApp::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        auto packet = check_and_cast<Packet *>(msg);
        socket.sendTo(packet, destAddress, destPort);
    } else {
        UdpEchoApp::handleMessage(msg);
    }
}

} //namespace
