// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "UdpEdgeCloudApp.h"
#include "inet/common/Simsignals.h"
#include "inet/networklayer/common/L3AddressResolver.h"

namespace d6g {
using namespace inet;

Define_Module(UdpEdgeCloudApp)

void UdpEdgeCloudApp::socketDataArrived(UdpSocket *socket, Packet *pk) {
    // determine its src address/port
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
