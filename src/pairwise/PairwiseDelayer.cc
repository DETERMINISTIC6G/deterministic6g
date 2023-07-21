/*
 * pkDelay.cc
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#include "PairwiseDelayer.h"
#include "inet/linklayer/common/InterfaceTag_m.h"

#include <omnetpp.h>

namespace pkdelay {

using namespace inet;
using namespace queueing;

Define_Module(PairwiseDelayer);

void PairwiseDelayer::initialize(int stage) {
    PacketDelayerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        delayParameter = &par("delay");
        bitrateParameter = &par("bitrate");
    }
}

clocktime_t PairwiseDelayer::computeDelay(Packet *packet) const {
    auto inInterface = packet->findTag<InterfaceInd>();
    int inInterfaceID = -1;
    if (inInterface != nullptr)
        inInterfaceID = inInterface->getInterfaceId();

    auto outInterface = packet->findTag<InterfaceReq>();
    int outInterfaceID = -1;
    if (outInterface != nullptr)
        outInterfaceID = outInterface->getInterfaceId();

    EV << "Incoming interface id is " << inInterfaceID << "; outgoing interface id is " << outInterfaceID << endl;

    // TODO: implement pairwise delay

    return delayParameter->doubleValue() + s(packet->getDataLength() / bps(bitrateParameter->doubleValue())).get();
}
}//namespace pairwisedelayer
