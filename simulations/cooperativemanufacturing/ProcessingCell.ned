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
// The module is designed to simulate a processing unit in a cooperative manufacturing environment. 
// It extends UnitWithAdapter, and has two modules for communication with the swarm:
// - swarmStatus: receives information from AGV
// - swarmControl: sends commands to AGV
module ProcessingCell extends UnitWithAdapter
{
    parameters:
        isWireless = false; // Specifies that the module does not use wireless communication
    	@display("i=status/execute");
        *.eth[*].bitrate = default(100Mbps); // Default bitrate for Ethernet interfaces
    submodules:
        // Bridge for Ethernet frames
        bridge: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=150,100");
        }
        
        // Device for monitoring the status of the swarm
        swarmStatus: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=250,100");
        }
        
        // Device for controlling the swarm
        swarmControl: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=250,200");
        }
    connections:
        swarmControl.ethg++ <--> EthernetLink <--> detComAdapter.ethg++;
        swarmStatus.ethg++ <--> EthernetLink <--> bridge.ethg++;
        bridge.ethg++ <--> EthernetLink <--> detComAdapter.ethg++;
}
