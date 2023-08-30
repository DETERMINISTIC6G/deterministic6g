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
// The module extends UnitWithAdapter to represent an AGV in a cooperative manufacturing environment. 
// It has the ability to communicate wirelessly and has two Ethernet submodules: one for communication 
// between AGVs (interAgv) and another for communication to a processing cell (interToCell).
//
module AGV extends UnitWithAdapter
{
    parameters:
    	@display("i=device/cellphone");
    	isWireless = true; // Indicates that the AGV can communicate wirelessly
        *.eth[*].bitrate = default(100Mbps); // Default bitrate for Ethernet interfaces
    submodules:
        // For communication between AGVs
        interAgv: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=300,100");
        }
        
        // For communication to a processing cell
        interToCell: <default("TsnDevice")> like IEthernetNetworkNode { 
            @display("p=400,100");
        }
    connections:
        detComAdapter.ethg++ <--> EthernetLink <--> interAgv.ethg++;
        detComAdapter.ethg++ <--> EthernetLink <--> interToCell.ethg++;
}
