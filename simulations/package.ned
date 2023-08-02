package d6g.simulations;

@license(LGPL);

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;

import d6g.distribution.histogram.Histogram;

network TsnTestNetwork extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps);
    submodules:
        histogram: Histogram;
        client: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=350,200");
        }
        switch: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=550,200");
        }
        server: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=750,200");
        }
    connections:
        client.ethg++ <--> EthernetLink <--> switch.ethg++;
        switch.ethg++ <--> EthernetLink <--> server.ethg++;
}
