//
// Created by haugls on 7/28/23.
//

#ifndef DETERMINISTIC6G_IRANDOMNUMBERGENERATOR_H
#define DETERMINISTIC6G_IRANDOMNUMBERGENERATOR_H

namespace d6g {
using namespace inet;
class IRandomNumberGenerator {
    virtual cValue getRand() const = 0;
};
}

#endif
