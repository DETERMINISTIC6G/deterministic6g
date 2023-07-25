//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package d6g.simulations.cooperativemanufacturing;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;
import d6g.devices.DetCom;



network CooperativeManufacturing extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps);
    submodules:
        agv1: AGV {
            @display("p=350,200");
        }
        agv2: AGV {
            @display("p=350,300");
        }
        detcom: DetCom {
            @display("p=450,250");
        }
        processingCell: ProcessingCell {
            @display("p=550,250");
        }
    connections:
        agv1.bridgeAdapter <--> EthernetLink <--> detcom.ethg++;
        agv2.bridgeAdapter <--> EthernetLink <--> detcom.ethg++;
        processingCell.bridgeAdapter <--> EthernetLink <--> detcom.ethg++;
}

