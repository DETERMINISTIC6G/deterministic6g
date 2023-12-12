// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

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

// 
// This is still work in progress, not working yet.
// Might need more discussion.
//
network TimeSyncNetwork extends TsnNetworkBase
{
    submodules:
        timeTransmitter: TsnClock {
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
          timeTransmitter.ethg++ <--> EthernetLink <--> detcom.ethg++;
          detcom.ueg++ <--> UEChannel <--> tsnDevice1.ueg++;
          detcom.ueg++ <--> UEChannel <--> tsnDevice2.ueg++;

}
