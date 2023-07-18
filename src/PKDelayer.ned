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

package pkdelay;

import inet.queueing.base.PacketDelayerBase;
import inet.queueing.contract.IPacketDelayer;

simple PKDelayer extends PacketDelayerBase like IPacketDelayer
{
    parameters:
        volatile double delay @unit(s); // specifies delay per packet
        
        // ----- specify the lower and upper bound of delay time -----
//        volatile double delay_lowerBound @unit(s) = default(-1s);
//        volatile double delay_upperBound @unit(s) = default(1s);
        
//        volatile double mean_delaytime @unit(s);
//        volatile double stddev @unit(s);
        
        volatile double bitrate @unit(bps) = default(inf bps); // determines additional delay per bit
        @class(PKDelayer);
}

