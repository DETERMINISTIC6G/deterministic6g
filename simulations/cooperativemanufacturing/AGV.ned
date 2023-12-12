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
            @display("p=50,100");
        }

        // For communication to a processing cell
        interToCell: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=250,100");
        }
    connections:
        detComAdapter.ethg++ <--> EthernetLink <--> interAgv.ethg++;
        detComAdapter.ethg++ <--> EthernetLink <--> interToCell.ethg++;
}
