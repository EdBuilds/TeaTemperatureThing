/*
 * StateMachine.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */
#include "StateMachine.hpp"
Machine::Machine(unsigned int inStockQuantity){
}

Machine::~Machine() {
    delete mState;
}

void Machine::sell(unsigned int quantity) {
    mState->sell(*this, quantity);
}

void Machine::refill(unsigned int quantity) {
    mState->refill(*this, quantity);
}

unsigned int Machine::getCurrentStock() {
    return mStockQuantity;
}
