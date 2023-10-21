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

package d6g.devices.sixg;

import inet.node.tsn.TsnDevice;
import inet.linklayer.contract.IEthernetInterface;

//
// The module extends the TsnSwitch module to offer advanced Ethernet communication capabilities.
// It provides a variety of configurable parameters to simulate different networking behaviors at both the MAC
// and PHY layers. These parameters include options for frame preemption, egress traffic shaping, and 
// cut-through switching, thus allowing a flexible setup to emulate real-world networking scenarios.
//
module UETsnDevice extends TsnDevice
{
    parameters:
        int numUeInterfaces = default(0); // Specifies the minimum number of user equipment (UE) Ethernet interfaces that the adapter supports.
        
        ue[*].typename = default("UE"); // switch to modular Ethernet interface
        ue[*].macLayer.typename = default(hasFramePreemption ? "EthernetPreemptingMacLayer" : "EthernetMacLayer");
        ue[*].macLayer.queue.typename = default(hasEgressTrafficShaping ? "Ieee8021qTimeAwareShaper" : (hasFramePreemption ? "" : "PacketQueue")); // use priority queue having multiple subqueues controlled by separate gates
        ue[*].phyLayer.typename = default(hasCutthroughSwitching ? "EthernetStreamingPhyLayer" : (hasFramePreemption ? "EthernetPreemptingPhyLayer" : "EthernetPhyLayer")); // use packet streaming when cut-through switching is enabled
    gates:
        inout ueg[numUeInterfaces] @labels(EtherFrame-conn);
    submodules:
        ue[sizeof(ueg)]: <default("UE")> like IEthernetInterface {
            @display("p=825,1025,row,150;q=txQueue");
        }
    connections:
        for i=0..sizeof(ueg)-1 {
            li.out++ --> ue[i].upperLayerIn;
            li.in++ <-- ue[i].upperLayerOut;
            ue[i].phys <--> { @display("m=s"); } <--> ueg[i];
        }
}
