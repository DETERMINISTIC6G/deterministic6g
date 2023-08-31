//
// Copyright (C) 2023 Deterministic 6G.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.apps.edgecloud;

import inet.applications.udpapp.UdpEchoApp;

// The UdpEdgeCloudApp module is designed to simulate a UDP-based application in edge cloud scenarios.
// This module builds upon the UdpEchoApp, inheriting its functionalities and adding the capability
// to introduce specific delays and instead of echoing a UDP Packet forwarding it to another host.
// Such delays might be used to simulate various network conditions or service latencies in edge cloud settings.
// Users can specify destination addresses, destination, ports, and custom delays to simulate application behavior in
// edge cloud environments.
simple UdpEdgeCloudApp extends UdpEchoApp {
    parameters:
        @class(UdpEdgeCloudApp);
        string destAddress = default(""); // destination IP address to forward the UDP packets to
        int destPort; // destination port number for the UDP packets
        volatile double delay @unit(s) = default(0s); // specifies delay per UDP packets
}
