package d6g.simulations.training_day.tutorial3;

import inet.networks.base.TsnNetworkBase;
import inet.node.ethernet.EthernetLink;
import inet.node.tsn.TsnClock;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;


network NetworkTutorial3 extends TsnNetworkBase
{
    submodules:
        tsnClock: TsnClock {
            @display("p=500,150");
        }
        tsnSwitch: TsnSwitch {
            @display("p=500,300");
        }
        tsnDevice1: TsnDevice {
            @display("p=400,450");
        }
        tsnDevice2: TsnDevice {
            @display("p=600,450");
        }
    connections:
        tsnClock.ethg++ <--> EthernetLink <--> tsnSwitch.ethg++;
        tsnSwitch.ethg++ <--> EthernetLink <--> tsnDevice1.ethg++;
        tsnSwitch.ethg++ <--> EthernetLink <--> tsnDevice2.ethg++;
}
