/*
 * UniformDistribution.h
 *
 *  Created on: Jul 5, 2023
 *      Author: dan
 */

#ifndef DISTRIBUTIONBASE_H_
#define DISTRIBUTIONBASE_H_

#include "inet/common/INETDefs.h"


namespace pkdelay{

class DistributionBase{
protected:
    virtual double GetRandNum(double LowerBound, double UpperBound) const;
};

}

#endif /* DISTRIBUTIONBASE_H_ */
