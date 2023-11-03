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
import inet.linklayer.ieee8021as.GptpMaster;
import inet.node.tsn.TsnClock;
import d6g.devices.sixg.DetCom;
import d6g.devices.sixg.UEChannel;
import d6g.devices.sixg.UETsnDevice;
import d6g.devices.sixg.UETsnSwitch;
import d6g.networks.DetComNetworkBase;
import d6g.distribution.histogram.Histogram;

// 
// This is still work in progress, not working yet.
// Might need more discussion.
//
network TimeSyncNetwork extends TsnNetworkBase
{
    submodules:
        masterClock: TsnClock {
            @display("p=500,150");
        }
        detcom: DetCom {
            @display("p=500,300");
        }
        tsnDevice1: UETsnDevice {
            @display("p=400,450");
        }
        tsnDevice2: UETsnDevice {
            @display("p=600,450");
        }


    connections:
          masterClock.ethg++ <--> EthernetLink <--> detcom.ethg++;
          detcom.ueg++ <--> UEChannel <--> tsnDevice1.ueg++;
          detcom.ueg++ <--> UEChannel <--> tsnDevice2.ueg++;

}
