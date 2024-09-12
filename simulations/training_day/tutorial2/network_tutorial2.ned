package d6g.simulations.training_day.tutorial2;

import inet.networks.base.TsnNetworkBase;
import inet.node.ethernet.EthernetLink;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;


network NetworkTutorial2 extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps);
        detCom.*.eth[*].bitrate = default(100Mbps);
    submodules:
        talker1: TsnDevice {
            @display("p=400,300");
        }
        talker2: TsnDevice {
            @display("p=400,500");
        }
        detCom: TsnSwitch {
            @display("p=550,400");
        }
        bridge: TsnSwitch {
            @display("p=700,400");
        }
        listener: TsnDevice {
            @display("p=850,400");
        }
    connections:
        talker1.ethg++ <--> EthernetLink <--> detCom.ethg++;
        talker2.ethg++ <--> EthernetLink <--> detCom.ethg++;
        detCom.ethg++ <--> EthernetLink <--> bridge.ethg++;
        bridge.ethg++ <--> EthernetLink <--> listener.ethg++;
}
