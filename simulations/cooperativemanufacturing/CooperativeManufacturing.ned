// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.simulations.cooperativemanufacturing;

import d6g.devices.DetCom;
import d6g.networks.DetComNetworkBase;
import inet.node.ethernet.EthernetLink;
import inet.node.tsn.TsnDevice;


//
// This network focuses on a cooperative manufacturing environment.
// The network simulates communication between AGV (Automated Guided Vehicles) and a processing cell
// via our DetCom module.
//
network CooperativeManufacturing extends DetComNetworkBase
{
    parameters:
        **.eth[*].bitrate = default(100Mbps); // Default bitrate for Ethernet interfaces
    submodules:
        agv1: TsnDevice { // AGV (Automated Guided Vehicle) 1
            @display("p=350,200");
        }
        agv2: TsnDevice { // AGV (Automated Guided Vehicle) 2
            @display("p=350,300");
        }
        detCom: DetCom { // DetCom module for deterministic communication
            @display("p=450,250");
        }
        processingCell: ProcessingCell { // Processing cell in the manufacturing setup
            @display("p=550,250");
        }
    connections:
        agv1.ethg++ <--> EthernetLink <--> detCom.dsttg++;
        agv2.ethg++ <--> EthernetLink <--> detCom.dsttg++;
        processingCell.detComConnection <--> EthernetLink <--> detCom.nwttg;
}

