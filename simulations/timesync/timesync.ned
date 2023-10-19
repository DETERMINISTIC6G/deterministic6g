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

package d6g.simulations.timesync;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;
import d6g.devices.sixg.DetCom;
import d6g.devices.sixg.DetComAdapter;
import d6g.networks.DetComNetworkBase;
import inet.node.tsn.TsnClock;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;
import d6g.distribution.histogram.Histogram;

// 
// The module extends from DetComNetworkBase. This network is meant to simulate deterministic communications in an edge cloud setting. 
// 
network timesyncshowcase extends TsnNetworkBase
{
    @display("bgb=1388.9,812.098");
    submodules:
        tsnClock1: TsnClock {
            @display("p=500,150");
        }
        detcom: DetCom {
            @display("p=500,300");
        }
        talker: TsnDevice {
            @display("p=400,450");
        }
        receiver: TsnDevice {
            @display("p=600,450");
        }


    connections:
          tsnClock1.ethg++ <--> EthernetLink <--> detcom.ethg++;
          detcom.ethg++ <--> EthernetLink <--> talker.ethg++;
          detcom.ethg++ <--> EthernetLink <--> receiver.ethg++;
}
