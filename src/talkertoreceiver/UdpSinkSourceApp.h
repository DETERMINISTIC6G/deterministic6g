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

#ifndef TALKERTORECEIVER_UDPSINKSOURCEAPP_H_
#define TALKERTORECEIVER_UDPSINKSOURCEAPP_H_

#include <inet/applications/udpapp/UdpBasicApp.h>
#include <inet/networklayer/common/L3AddressResolver.h>

namespace d6g {

using namespace inet;

class UdpSinkSourceApp : public UdpBasicApp
{
  protected:
    virtual void processPacket(Packet *msg) override;
    void sendPacket(Packet *msg);  // You might need to implement this function

};

}
#endif /* TALKERTORECEIVER_UDPSINKSOURCEAPP_H_ */
