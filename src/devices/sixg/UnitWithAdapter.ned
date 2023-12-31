// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

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
            @display("p=150,200");
        }
    connections:
        if (isWireless) {
        	detComAdapter.ueg++ <--> {@display("ls=,,da");} <--> adapterGate;
        }
        if (!isWireless) {
            detComAdapter.ethg++ <--> adapterGate;
        }
}