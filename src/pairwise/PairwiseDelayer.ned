//
// Copyright (C) 2023 Deterministic 6G.
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

package d6g.pairwise;

import inet.queueing.base.PacketDelayerBase;
import inet.queueing.contract.IPacketDelayer;

//
// The module is designed to delay packets based on pairwise configurations. 
// This module works by accepting packets and applying a delay according to the specified 
// delayConfig. This can be particularly useful in scenarios where varying delays are required 
// for different packet pairs or flows. It's an extension of PacketDelayerBase and adheres to 
// the IPacketDelayer contract. Users can provide custom delay configurations using the 
// delayConfig XML parameter.
//
simple PairwiseDelayer extends PacketDelayerBase like IPacketDelayer
{
    parameters:
        xml delayConfig = default(xml("<delays></delays>")); // XML configuration definition for delay
        @class(PairwiseDelayer);
}

