//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

//package src.PKDelay;
//
//import inet.queueing.base.PacketDelayerBase;
//import inet.queueing.contract.IPacketDelayer;
//
////import inet.queueing.base.PacketDelayerBase;
////import inet.queueing.contract.IPacketDelayer;
//
//simple PKDelay extends PacketDelayerBase like IPacketDelayer
//{
//    parameters:
//        volatile double delay @unit(s) = default(uniform(-1s, 1s)); // specifies delay per packet
//        volatile double bitrate @unit(bps) = default(inf bps); // determines additional delay per bit
//        @class(PKDelay);
//}

package pkdelay.pairwise;

import inet.queueing.base.PacketDelayerBase;
import inet.queueing.contract.IPacketDelayer;

simple PairwiseDelayer extends PacketDelayerBase like IPacketDelayer
{
    parameters:
      
        volatile double delay @unit(s) = default(uniform(-1s, 1s)); // specifies delay per packet
        volatile double bitrate @unit(bps) = default(inf bps); // determines additional delay per bit
        @class(PairwiseDelayer);
}

