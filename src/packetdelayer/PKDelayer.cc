/*
 * PKDelayer.cc
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#include <omnetpp.h>
#include "PKDelayer.h"
#include "../distribution/DistributionBase.h"

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

double PKDelayer::GetRandNum(double LowerBound, double UpperBound) const
{
    cRNG *rng = getEnvir()->getRNG(0);
    double rand_num = omnetpp::uniform(rng, LowerBound, UpperBound);
    return rand_num;
}

clocktime_t PKDelayer::computeDelay(Packet *packet) const
{
    double cur_rand =PKDelayer::GetRandNum(delayLB->doubleValue(), delayUB->doubleValue());
    double dataLength = packet->getDataLength().get(); // data length in bits
    double bitrate = bitrateParameter->doubleValue(); // bitrate in bps
    delayTime = delayTime + s(cur_rand + (dataLength/bitrate)).get();

    if (delayTime <= 0){
        delayTime = 0;
    }

    return delayParameter->doubleValue() + clocktime_t(delayTime);
}

} // namespace PKDelayer


