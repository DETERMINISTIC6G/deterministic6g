//
// Copyright (C) 2023 Deterministic 6G.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.apps.edgecloud;

import inet.applications.udpapp.UdpEchoApp;

//
// The module is designed to simulate a UDP-based application in edge cloud scenarios.
// This module builds upon the UdpEchoApp with the following additional features:<br>
// - Forward the packet to a new host<br>
// - Add delay to the packet
simple UdpEdgeCloudApp extends UdpEchoApp {
    parameters:
        @class(UdpEdgeCloudApp);
        string destAddress = default(""); // destination IP address to forward the UDP packets to
        int destPort; // destination port number for the UDP packets
        volatile double delay @unit(s) = default(0s); // specifies delay per UDP packets
}
