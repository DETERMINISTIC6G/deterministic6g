//
// Created by haugls on 7/28/23.
//

#ifndef DETERMINISTIC6G_IRANDOMNUMBERPROVIDER_H
#define DETERMINISTIC6G_IRANDOMNUMBERPROVIDER_H

namespace d6g {
using namespace inet;
class IRandomNumberProvider {
public:
    virtual cValue getRand() const = 0;
};
}

#endif
