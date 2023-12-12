// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "DelayReplayer.h"

#include <omnetpp.h>
#include "fstream"
#include "inet/common/XMLUtils.h"
#include "inet/networklayer/configurator/base/L3NetworkConfiguratorBase.h"

namespace d6g {

Define_Module(DelayReplayer);

void DelayReplayer::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        delays.clear();
        const char *csvfile = par("csvFilename").stringValue();
        readCSV(csvfile);
    }
}

void DelayReplayer::readCSV(const char *filename) {
    std::string line, word;
    std::ifstream infile(filename);
    cDynamicExpression delayExpr;
    cValue value;
    if (!infile) {
        throw cRuntimeError("File '%s' not found", filename);
    }
    while (getline(infile, line)) {
        std::stringstream str(line);

        while (getline(str, word, ',')) {
            delayExpr.parse(word.c_str());
            value = delayExpr.evaluate(this);
            delays.push_back(value);
        }
    }
    delayIterator = delays.begin();
}

cValue DelayReplayer::getRand() {
    if (delayIterator == delays.end()) {
        delayIterator = delays.begin();
    }
    cValue value = *delayIterator;
    EV << value.str() << endl;
    ++delayIterator;
    return value;
}


DelayReplayer::DelayReplayer() {
}

DelayReplayer::~DelayReplayer() {
}

} /* namespace d6g */
