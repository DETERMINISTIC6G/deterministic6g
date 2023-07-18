/*
 * UniformDistribution.cc
 *
 *  Created on: Jul 5, 2023
 *      Author: dan
 */

#include "DistributionBase.h"

#include <omnetpp.h>
#include "inet/clock/contract/ClockTime.h"

namespace pkdelay {
using namespace inet;

clocktime_t DistributionBase::Static(clocktime_t mean, clocktime_t stddev) const
{
    cRNG *rng = getEnvir()->getRNG(0);
    double distri = omnetpp::truncnormal(rng, mean.dbl(), stddev.dbl());
    return clocktime_t(distri);
}

//cNEDValue DistributionBase::ned_Static(cComponent *context, cNEDValue argv[], int argc)
//{
//    DistributionBase *instance = dynamic_cast<DistributionBase *>(context);
//    if (!instance)
//        throw cRuntimeError("The ned_Static function can only be called in the context of a DistributionBase object");
//
//    return instance->Static(argv[0].doubleValue(), argv[1].doubleValue());
//}
//
//Define_NED_Function(DistributionBase::ned_Static, "default(double mean, double stddev)");

}
