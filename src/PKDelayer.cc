/*
 * pkDelay.cc
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#include "PKDelayer.h"

#include <omnetpp.h>

namespace pkdelay {

using namespace inet;
using namespace queueing;

Define_Module(PKDelayer);

void PKDelayer::initialize(int stage)
{
    PacketDelayerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        delayParameter = &par("delay");
        bitrateParameter = &par("bitrate");
    }
}

clocktime_t PKDelayer::computeDelay(Packet *packet) const
{
//    srand(time(0));
    double a = 1.0; // delayParameter
    double b = 5.0;
    cRNG *rng = getEnvir()->getRNG(0);
    double cur_rand = omnetpp::uniform(rng, a, b);// random value between a and b
//    double cur_rand = omnetpp::normal(rng, a, b); // normal distribution
    double dataLength = packet->getDataLength().get(); // data length in bits
    double bitrate = bitrateParameter->doubleValue(); // bitrate in bps
    tmp_rand = tmp_rand + s(cur_rand + (dataLength/bitrate)).get();

    if (tmp_rand <= 0){
        tmp_rand = 0;
    }

    return clocktime_t(tmp_rand);// or + s(cur_rand).get();
}

} // namespace PKDelayer


