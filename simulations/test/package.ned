package d6g.simulations.test;

@license(LGPL);

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;

import d6g.distribution.histogram.Histogram;

//
// An extension of the TsnNetworkBase from the INET framework.
// The network consists of a client, a switch, and a server.
// A Histogram submodule is also included for statistical analysis, with data sourced from example-hist.xml.
//
network TsnTestNetworkTest extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps); // Default bitrate for all Ethernet interfaces is set to 100Mbps.
    submodules:
        // Histogram for capturing statistical data.
        histogram: Histogram {
            @display("p=100,400;is=s");
        }
        
        // Client node in the network, likely generating TSN traffic.
        client: <default("TsnDevice")> like IEthernetNetworkNode {
            numEthInterfaces = 1;
            @display("p=350,200");
        }
        
        // Switch node for routing and handling TSN traffic.
        switch: <default("TsnSwitch")> like IEthernetNetworkNode {
            numEthInterfaces = 2;
            @display("p=550,200");
        }
        
        // Server node in the network, typically a recipient of TSN traffic.
        server: <default("TsnDevice")> like IEthernetNetworkNode {
            numEthInterfaces = 1;
            @display("p=750,200");
        }
    connections:
        client.ethg$o[0] --> EthernetLink --> switch.ethg$i[0];
        client.ethg$i[0] <-- EthernetLink <-- switch.ethg$o[0];
        switch.ethg++ <--> EthernetLink <--> server.ethg++;
}
