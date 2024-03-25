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

//
// The module is designed to simulate a processing unit in a cooperative manufacturing environment. 
// It extends UnitWithAdapter, and has two modules for communication with the swarm:
// - swarmStatus: receives information from AGV
// - swarmControl: sends commands to AGV
network ProcessingCell
{
    parameters:
    	@display("i=status/execute");
    gates:
        inout detComConnection;
    submodules:
        // Bridge for Ethernet frames
        bridge1: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=150,200");
        }
        
        bridge2: <default("TsnSwitch")> like IEthernetNetworkNode {
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
        swarmControl.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        swarmStatus.ethg++ <--> EthernetLink <--> bridge2.ethg++;
        bridge2.ethg++ <--> EthernetLink <--> bridge1.ethg++;
        bridge1.ethg++ <--> detComConnection;
}
