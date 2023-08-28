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

import inet.node.tsn.TsnSwitch;
import inet.linklayer.contract.IEthernetInterface;

/// The module DetComAdapter extends a TsnSwitch, presenting a configurable network scenario that models 
/// Ethernet communication with varying MAC and PHY layer behaviors, influenced by parameters such as frame preemption,
/// egress traffic shaping, and cut-through switching.
module DetComAdapter extends TsnSwitch
{
    parameters:
        int numUeInterfaces = default(0);  /// minimum number of ethernet interfaces
        ue[*].macLayer.typename = default(hasFramePreemption ? "EthernetPreemptingMacLayer" : "EthernetMacLayer");
        ue[*].macLayer.queue.typename = default(hasEgressTrafficShaping ? "Ieee8021qTimeAwareShaper" : "PacketQueue"); /// use compound priority queue having multiple subqueues controlled by separate gates when egress traffic shaping is enabled
        ue[*].phyLayer.typename = default(hasCutthroughSwitching ? "EthernetStreamThroughPhyLayer" : (hasFramePreemption ? "EthernetPreemptingPhyLayer" : "EthernetPhyLayer")); /// use packet streaming when cut-through switching is enabled
    gates:
        inout ueg[numUeInterfaces] @labels(EtherFrame-conn);
    submodules:
        ue[sizeof(ueg)]: <default("UE")> like IEthernetInterface {
            @display("p=325,900,row,150;q=txQueue");
        }
    connections:
        for i=0..sizeof(ueg)-1 {
            li.out++ --> ue[i].upperLayerIn;
            li.in++ <-- ue[i].upperLayerOut;
            ue[i].phys <--> { @display("m=s"); } <--> ueg[i];
        }
}
