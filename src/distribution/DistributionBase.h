/*
 * UniformDistribution.h
 *
 *  Created on: Jul 5, 2023
 *      Author: dan
 */

#ifndef DISTRIBUTIONBASE_H_
#define DISTRIBUTIONBASE_H_

#include "inet/common/INETDefs.h"
#include "inet/clock/contract/ClockTime.h"

namespace pkdelay{
using namespace inet;

class DistributionBase {
protected:
    virtual clocktime_t Static(clocktime_t mean, clocktime_t stddev) const;
//    static cNEDValue ned_Static(cComponent *context, cNEDValue argv[], int argc);
};


}

#endif /* DISTRIBUTIONBASE_H_ */
