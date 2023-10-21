// 
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.devices.sixg;

import inet.node.tsn.TsnSwitch;
import inet.node.contract.IEthernetNetworkNode;

//
// This module provides a network communication scenarios based on whether the communication is wireless.
// It configures the necessary submodules ,connections,and gates to facilitate dynamic communication pattern.
//
module UnitWithAdapter {
    parameters:
        bool isWireless = default(true); //indicates whether the scenario is wireless
    gates:
        inout adapterGate; //interface for adapter's functionality
    submodules:
        detComAdapter: UETsnSwitch {
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