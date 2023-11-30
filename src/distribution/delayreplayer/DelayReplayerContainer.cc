//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "DelayReplayerContainer.h"

#include <omnetpp.h>
#include "inet/common/XMLUtils.h"
#include "inet/networklayer/configurator/base/L3NetworkConfiguratorBase.h"
#include "fstream"

namespace d6g {

Define_Module(DelayReplayerContainer);

void DelayReplayerContainer::initialize(int stage) {
    if (stage == INITSTAGE_LOCAL) {
        delayreplayers.clear();

        auto delayreplayersMap = check_and_cast<cValueMap *>(par("delayreplayers").objectValue());
        auto delayreplayersFields = delayreplayersMap->getFields();

        for(auto &delayreplayersField: delayreplayersFields){
            auto streamName = delayreplayersField.first;
            auto csvFile = delayreplayersField.second.stringValue();
            delayreplayers[streamName] = loadDelayReplayerFromFile(csvFile);
        }
    }
}

DelayReplayer* DelayReplayerContainer::loadDelayReplayerFromFile(const char* fileName){
    auto* delayreplayer = new DelayReplayer();
    delayreplayer->readCSV(fileName);

    return delayreplayer;
}

DelayReplayer *DelayReplayerContainer::getDelayreplayer(std::string key) const {
    auto it = delayreplayers.find(key);
    if (it == delayreplayers.end()) {
        throw cRuntimeError("DelayReplayer '%s' not found", key.c_str());
    }
    return it->second;
}

cValue DelayReplayerContainer::getRand(std::string key) {
    auto delayreplayer = getDelayreplayer(key);
    return delayreplayer->getRand();
}

DelayReplayerContainer::~DelayReplayerContainer() {
    for (auto &delayreplayer: delayreplayers) {
        delete delayreplayer.second;
    }
}

} /* namespace d6g */
