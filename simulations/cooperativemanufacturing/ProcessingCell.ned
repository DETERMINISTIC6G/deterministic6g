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

package d6g.simulations.cooperativemanufacturing;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;
import d6g.devices.sixg.UnitWithAdapter;

//
// The module is designed to simulate a processing unit in a cooperative manufacturing environment. 
// It extends UnitWithAdapter, adding specific configurations like Ethernet bitrate and submodules 
// for controlling swarm operations and status.
//
module ProcessingCell extends UnitWithAdapter
{
    parameters:
        isWireless = false; // Specifies that the module does not use wireless communication
    	@display("i=status/execute");
        *.eth[*].bitrate = default(100Mbps); // Default bitrate for Ethernet interfaces
    submodules:
        // Bridge for Ethernet frames
        bridge: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=350,100");
        }
        
        // Device for monitoring the status of the swarm
        swarmStatus: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=250,100");
        }
        
        // Device for controlling the swarm
        swarmControl: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=250,200");
        }
    connections:
        swarmControl.ethg++ <--> EthernetLink <--> detComAdapter.ethg++;
        swarmStatus.ethg++ <--> EthernetLink <--> bridge.ethg++;
        bridge.ethg++ <--> EthernetLink <--> detComAdapter.ethg++;
}
