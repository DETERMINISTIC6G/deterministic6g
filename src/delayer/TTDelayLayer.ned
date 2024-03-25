//
// Copyright (C) 2020 OpenSim Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//


package d6g.delayer;

import inet.protocolelement.processing.IProcessingDelayLayer;
import inet.protocolelement.processing.ProcessingDelayLayer;


module TTDelayLayer extends ProcessingDelayLayer like IProcessingDelayLayer
{
    parameters:
        volatile double delayUplink @mutable @unit(s) = default(0s); // Uplink Delay
        volatile double delayDownlink @mutable @unit(s) = default(0s); // Downlink Delay

        // Ingress for downlink
        // Arrives at tt (ingress, from other UE or NWTT) --> delay --> bridging logic --> eth (egress)
        ingress.typename = default("TTDelayer");
         // We do not know the egress interface at the ingress delayer, so only use indInterfaceType
        ingress.indInterfaceTypes = ["tt"];
        ingress.delay = default(this.delayDownlink);

        // Egress for uplink
        // Arrives at eth (ingress) --> bridging logic --> delay --> tt (egress, to other UE or NWTT)
        egress.typename = default("TTDelayer");
        egress.indInterfaceTypes = ["eth"];
         // Normally there should only be one eth interface, so if ind is eth, egress should always be tt
         // However, we don't want to mess up things if someone adds another eth interface, so specify reqInterfaceType regardless
        egress.reqInterfaceTypes = ["tt"];
        egress.delay = default(this.delayUplink);
}
