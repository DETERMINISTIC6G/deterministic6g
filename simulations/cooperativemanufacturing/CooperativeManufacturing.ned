// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.simulations.cooperativemanufacturing;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;
import d6g.devices.sixg.DetCom;
import d6g.devices.sixg.UEChannel;
import d6g.networks.DetComNetworkBase;

//
// This network focuses on a cooperative manufacturing environment.
// The network simulates communication between AGVs (Automated Guided Vehicles) and a processing cell
// via a DetCom (Deterministic Communication) module to ensure reliable and timely data transmission.
//
network CooperativeManufacturing extends DetComNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps); // Default bitrate for Ethernet interfaces
    submodules:
        agv1: AGV { // AGV (Automated Guided Vehicle) 1
            @display("p=350,200");
        }
        agv2: AGV { // AGV (Automated Guided Vehicle) 2
            @display("p=350,300");
        }
        detcom: DetCom { // DetCom module for deterministic communication
            @display("p=450,250");
        }
        processingCell: ProcessingCell { // Processing cell in the manufacturing setup
            @display("p=550,250");
        }
    connections:
        agv1.adapterGate <--> UEChannel <--> detcom.ueg++;
        agv2.adapterGate <--> UEChannel <--> detcom.ueg++;
        processingCell.adapterGate <--> EthernetLink <--> detcom.ethg++;
}

