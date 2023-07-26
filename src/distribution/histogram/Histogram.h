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

#ifndef __PKDELAY_HISTOGRAM_H_
#define __PKDELAY_HISTOGRAM_H_

#include <omnetpp.h>

using namespace omnetpp;

namespace d6g {

/**
 * TODO - Generated class
 */
class Histogram : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  public:
    // Get Total count of elements in all bins
    // Get Number of bins
    // Get a random bin with the probability corresponding to the count


   // SUBCLASS BIN
    // left boundary
    // right boundary
    // count of elements in bin
};

} //namespace

#endif
