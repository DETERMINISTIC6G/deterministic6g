package d6g.simulations.test;

@license(LGPL);

import inet.networks.base.TsnNetworkBase;
import inet.node.contract.IEthernetNetworkNode;
import inet.node.ethernet.EthernetLink;

import d6g.distribution.histogram.HistogramContainer;

//
// An extension of the TsnNetworkBase from the INET framework.
// The network consists of a client, a switch, and a server.
// A Histogram submodule is also included for statistical analysis, with data sourced from example-hist.xml.
//
network TsnTestNetwork extends TsnNetworkBase
{
    parameters:
        *.eth[*].bitrate = default(100Mbps); // Default bitrate for all Ethernet interfaces is set to 100Mbps.
    submodules:
        // Histogram for capturing statistical data.
        histogramContainer: HistogramContainer {
            @display("p=100,400;is=s");
        }

        // Client node in the network, likely generating TSN traffic.
        client: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=350,200");
        }

        // Switch node for routing and handling TSN traffic.
        switch: <default("TsnSwitch")> like IEthernetNetworkNode {
            @display("p=550,200");
        }

        // Server node in the network, typically a recipient of TSN traffic.
        server: <default("TsnDevice")> like IEthernetNetworkNode {
            @display("p=750,200");
        }
    connections:
        client.ethg++ <--> EthernetLink <--> switch.ethg++;
        switch.ethg++ <--> EthernetLink <--> server.ethg++;
}
