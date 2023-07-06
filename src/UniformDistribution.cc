/*
 * UniformDistribution.cc
 *
 *  Created on: Jul 5, 2023
 *      Author: dan
 */

#include "UniformDistribution.h"
#include <omnetpp.h>

namespace pkdelay{
using namespace inet;

double GetRandNum(double LowerBound, double UpperBound){
    cRNG *rng = getEnvir()->getRNG(0);

    double rand_num = omnetpp::uniform(rng, LowerBound, UpperBound);
    return rand_num;
    }
}



