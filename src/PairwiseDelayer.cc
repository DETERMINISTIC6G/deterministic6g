/*
 * pkDelay.cc
 *
 *  Created on: Jun 22, 2023
 *      Author: dan
 */

#include "PairwiseDelayer.h"

#include <omnetpp.h>

namespace pkdelay {

using namespace inet;
using namespace queueing;

Define_Module(PairwiseDelayer);

void PairwiseDelayer::initialize(int stage)
{
    PacketDelayerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        delayParameter = &par("delay");
        bitrateParameter = &par("bitrate");
    }
}

clocktime_t PairwiseDelayer::computeDelay(Packet *packet) const
{
   // if (packet->getSenderGate()->getIndex()==100 && packet->getArrivalGate()->getIndex()==100){
//get the sender gate and arrival gate
   cGate* senderGate=packet->getSenderGate();
   cGate* arrivalGate=packet->getArrivalGate();
   if(senderGate && senderGate->getIndex()==100 &&arrivalGate && arrivalGate->getIndex()==101)
   {
       EV<<"In address is 100 and 101"<<endl;
   }


    return delayParameter->doubleValue() + s(packet->getDataLength() / bps(bitrateParameter->doubleValue())).get();
}
}//namespace pairwisedelayer




