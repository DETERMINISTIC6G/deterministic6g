/*
 * pkDelay.cc
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#include "PairwiseDelayer.h"

#include <omnetpp.h>

namespace pkdelay {

using namespace inet;
using namespace queueing;

Define_Module(PairwiseDelayer);

void PairwiseDelayer::initialize(int stage)
{
    PacketDelayerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        delayParameter = &par("delay");
        bitrateParameter = &par("bitrate");
    }
}

clocktime_t PairwiseDelayer::computeDelay(Packet *packet) const
{
    int incInterface = 100;
    int outInterface = 101;


    return delayParameter->doubleValue() + s(packet->getDataLength() / bps(bitrateParameter->doubleValue())).get();
}

} // namespace PKDelayer


