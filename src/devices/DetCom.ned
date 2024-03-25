// This file is part of Deliverable D4.1 DetCom Simulator Framework Release 1
// of the DETERMINISTIC6G project receiving funding from the
// European Union’s Horizon Europe research and innovation programme
// under Grant Agreement No. 101096504.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

package d6g.devices;



import d6g.devices.tsntranslator.TTChannel;
import d6g.devices.tsntranslator.TsnTranslator;


// The DetCom node is used to simulate 6G behavior by providing a given delay distribution (e.g. from real world measurements)
// This behavior is implemented in the DetComDelayer module, which is already included in the DetComBridgingLayer.
//
// Besides the delay distribution, the DetCom node provides the same functionality as a TsnSwitch.
module DetCom
{
    parameters:
        @display("i=device/antennatower");
        int numUEs = default(0);
        xml delayConfig = default(xml("<delays></delays>")); // XML delay configuration
        @class(DetCom);
    gates:
        inout dsttg[numUEs];
        inout nwttg;
    submodules:
        dstt[sizeof(dsttg)]: TsnTranslator {
            isDstt = default(true);
            @display("p=100,100,col,150;");
        }
        nwtt: TsnTranslator {
            @display("p=550,100;");
        }
    connections:
        nwttg <--> nwtt.ethg++;
        for i=0..sizeof(dsttg)-1 {
            dsttg[i] <--> dstt[i].ethg++;
            dstt[i].ttg++ <--> TTChannel <--> nwtt.ttg++;
        }

        for i=0..sizeof(dsttg)-1, for j=i+1..sizeof(dsttg)-1 {
            dstt[i].ttg++ <--> TTChannel <--> dstt[j].ttg++;
        }
}
