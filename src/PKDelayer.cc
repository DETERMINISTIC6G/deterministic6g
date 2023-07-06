/*
 * pkDelay.cc
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#include "PKDelayer.h"

#include <omnetpp.h>
#include "UniformDistribution.h"

namespace pkdelay {

using namespace inet;
using namespace queueing;

Define_Module(PKDelayer);

void PKDelayer::initialize(int stage)
{
    PacketDelayerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        delayParameter = &par("delay");
        delayLB = &par("delay_lowerBound");
        delayUB = &par("delay_upperBound");
        bitrateParameter = &par("bitrate");
    }
}

clocktime_t PKDelayer::computeDelay(Packet *packet) const
{
    double cur_rand = GetRandNum(delayLB->doubleValue(), delayUB->doubleValue());
    double dataLength = packet->getDataLength().get(); // data length in bits
    double bitrate = bitrateParameter->doubleValue(); // bitrate in bps
    tmp_rand = tmp_rand + s(cur_rand + (dataLength/bitrate)).get();

    if (tmp_rand <= 0){
        tmp_rand = 0;
    }

    return delayParameter->doubleValue() + clocktime_t(tmp_rand);

    //    return clocktime_t(tmp_rand);// or + s(cur_rand).get();
}

} // namespace PKDelayer


