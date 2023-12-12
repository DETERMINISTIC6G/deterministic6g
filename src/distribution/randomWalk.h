// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef DETERMINISTIC6G_RANDOMWALK_H_
#define DETERMINISTIC6G_RANDOMWALK_H_

#include "inet/queueing/base/PacketDelayerBase.h"

namespace d6g {

using namespace inet;

/**
 * RandomWalk provides a NED function implementing a random walk.
 *
 * It uses an initial parameter and a function generating random numbers.
 *
 * TODO: Shall we use our IRandomNumberProvider interface?
 */
class randomWalk {
public:
//    static double cur_delay;
//    static int count;

    static std::map<std::string, cValue> lastDelays;  ///< key for different modules which call the randomWalk

public:
//    double return_delay;
//    double cur_delay;
//    int count = 0;
    static cNEDValue ned_randomWalk(cComponent *context, cNEDValue argv[], int argc);
};

} /* namespace d6g */

#endif
