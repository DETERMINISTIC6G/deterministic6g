package d6g.simulations.training_day.tutorial1;

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;
import inet.node.tsn.TsnDevice;
import inet.node.tsn.TsnSwitch;

network NetworkTask2 extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps);
        @display("bgb=919,863");
    submodules:
        talker: TsnDevice {
            @display("p=400,300");
        }
        babblingTalker: TsnDevice {
            @display("p=400,500");
        }
        bridge: TsnSwitch {
            @display("p=600,400");
        }
        listener: TsnDevice {
            @display("p=800,400");
        }

    connections:
        talker.ethg++ <--> EthernetLink <--> bridge.ethg++;
        babblingTalker.ethg++ <--> EthernetLink <--> bridge.ethg++;
        bridge.ethg++ <--> EthernetLink <--> listener.ethg++;
}
