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
import inet.node.contract.IEthernetNetworkNode;

module UnitWithAdapter {
    parameters:
        bool isWireless = default(true);
    gates:
        inout adapterGate;
    submodules:
        detComAdapter: DetComAdapter {
            @display("p=350,200");
        }
    connections:
        if (isWireless) {
        	detComAdapter.ueg++ <--> {@display("ls=,,da");} <--> adapterGate;
        }
        if (!isWireless) {
            detComAdapter.ethg++ <--> {@display("ls=,,da");} <--> adapterGate;
        }
}