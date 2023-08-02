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

module ProcessingCell extends UnitWithAdapter
{
    parameters:
        isWireless = false;
    	@display("i=status/execute");
        *.eth[*].bitrate = default(100Mbps);
    submodules:
        bridge: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=350,100");
        }
        swarmStatus: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=250,100");
        }
        swarmControl: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=250,200");
        }
    connections:
        swarmControl.ethg++ <--> EthernetLink <--> detComAdapter.ethg++;
        swarmStatus.ethg++ <--> EthernetLink <--> bridge.ethg++;
        bridge.ethg++ <--> EthernetLink <--> detComAdapter.ethg++;
}