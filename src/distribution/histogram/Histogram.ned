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

package d6g.distribution.histogram;

/// This module groups the delays based on the bins assigned as per histogram xml. 
/// It reads histogram configuration, calculates accumulated bin counts,
/// generates random values within bins, and implements binary search for bin selection. 
///
simple Histogram
{
    parameters:
        xml histogramConfig = default(xml("<bin></bin>"));
        @class(Histogram);
        @display("i=block/delay");
}
