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
        rng = getEnvir()->getRNG(0); //
        delayParameter = &par("delay");
        bitrateParameter = &par("bitrate");

//        // Initialize the cHistogram object
//        delayStats = new cHistogram("delayStats");
//        delayStats->setRange(-0.000004, 0.000004);
//        delayStats->setNumBinsHint(100);
//        delayStats->setNumPrecollectedValues(200);
    }
}

/* ---------------------------- Random Delay Time ---------------------------- */
//double PKDelayer::ArbitraryDelayTime(double mean, double stddev) const
//{
////    cRNG *rng = getEnvir()->getRNG(0);
//    double ADT = omnetpp::normal(rng, mean, stddev);
//
//    // ---- Simulation delay time ----
//    simtime_t delay = ADT;
//    delayStats->collect(delay);
//    // -------------------------------
//
//    return ADT;
//}

clocktime_t PKDelayer::computeDelay(Packet *packet) const
{
    return delayParameter->doubleValue();
}

clocktime_t PKDelayer::Static(clocktime_t mean, clocktime_t stddev) const
{
    double mean_time = mean.dbl(); // convert to double
    double stddev_time = stddev.dbl(); // convert to double
    delayTime = omnetpp::truncnormal(rng, mean_time, stddev_time);
    return delayParameter->doubleValue() + clocktime_t(delayTime);
}

cNEDValue PKDelayer::ned_Static(cComponent *context, cNEDValue argv[], int argc)
{
    PKDelayer *instance = dynamic_cast<PKDelayer *>(context);
    if (!instance)
        throw cRuntimeError("The ned_Static function can only be called in the context of a PKDelayer object");

    double arg0 = argv[0].doubleValueInUnit("us"); // convert to double
    double arg1 = argv[1].doubleValueInUnit("us"); // convert to double

    clocktime_t arg0_time = clocktime_t(arg0); // convert to clocktime_t
    clocktime_t arg1_time = clocktime_t(arg1); // convert to clocktime_t

    clocktime_t delay = instance->Static(arg0_time, arg1_time);
    return cNEDValue(delay.dbl(), "us"); // specify unit
}

Define_NED_Function(PKDelayer::ned_Static, "any Static(any m, any stddev)");

//// record as a histogram -------------------
//void PKDelayer::finish()
//{
//    // Record the histogram
//    delayStats->recordAs("histogram");
//}
//
//PKDelayer::~PKDelayer()
//{
//    // Delete cHistogram object
//    delete delayStats;
//}
//// ----------------------------------------

} // namespace PKDelayer
