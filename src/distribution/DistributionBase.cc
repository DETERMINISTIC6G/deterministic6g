/*
 * UniformDistribution.cc
 *
 *  Created on: Jul 5, 2023
 *      Author: dan
 */

#include "DistributionBase.h"

#include <omnetpp.h>

using namespace inet;

namespace pkdelay{

double DistributionBase::GetRandNum(double LowerBound, double UpperBound) const
{
    cRNG *rng = getEnvir()->getRNG(0);
    double rand_num = omnetpp::uniform(rng, LowerBound, UpperBound);
    return rand_num;
}

double DistributionBase::ArbitraryDelayTime(double mean, double stddev) const
{
    cRNG *rng = getEnvir()->getRNG(0);
    double ADT = omnetpp::normal(rng, mean, stddev);
    return ADT;
}

}



