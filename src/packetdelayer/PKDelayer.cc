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
//        delayLB = &par("delay_lowerBound");
//        delayUB = &par("delay_upperBound");
        mean = &par("mean_delaytime");
        stddev = &par("stddev");
        bitrateParameter = &par("bitrate");

        // Initialize the cHistogram object
        delayStats = new cHistogram("delayStats");
        delayStats->setRange(-0.000004, 0.000004);
        delayStats->setNumBinsHint(100);
        delayStats->setNumPrecollectedValues(200);
    }
}

/* ---------------------------- Random Delay Time ---------------------------- */
// Method 1
double PKDelayer::GetRandNum(double LowerBound, double UpperBound) const
{
    cRNG *rng = getEnvir()->getRNG(0);
    double rand_num = omnetpp::uniform(rng, LowerBound, UpperBound);
    return rand_num;
}

// Method 2
double PKDelayer::ArbitraryDelayTime(double mean, double stddev) const
{
    cRNG *rng = getEnvir()->getRNG(0);
    double ADT = omnetpp::normal(rng, mean, stddev);

    // ---- Simulation delay time ----
    simtime_t delay = ADT;
    delayStats->collect(delay);
    // -------------------------------

    return ADT;
}
/* -------------------------------------------------------------------------- */

clocktime_t PKDelayer::computeDelay(Packet *packet) const
{
//    double cur_rand = PKDelayer::GetRandNum(delayLB->doubleValue(), delayUB->doubleValue());
    double cur_rand = PKDelayer::ArbitraryDelayTime(mean->doubleValue(), stddev->doubleValue());

    double dataLength = packet->getDataLength().get(); // data length in bits
    double bitrate = bitrateParameter->doubleValue(); // bitrate in bps
    delayTime = delayTime + s(cur_rand + (dataLength/bitrate)).get();

    if (delayTime <= 0){delayTime = 0;}

    return delayParameter->doubleValue() + clocktime_t(delayTime);
}


// record as a histogram -------------------
void PKDelayer::finish()
{
    // Record the histogram
    delayStats->recordAs("histogram");
}

PKDelayer::~PKDelayer()
{
    // Delete cHistogram object
    delete delayStats;
}
// ----------------------------------------

} // namespace PKDelayer


