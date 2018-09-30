/*
 * States.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */

#include "States.hpp"

AbstractState::~AbstractState() {
}

void AbstractState::setState(Machine& machine, AbstractState* state) {
    AbstractState* aux = machine.mState;
    machine.mState = state;
    delete aux;
}

void AbstractState::updateStock(Machine& machine, unsigned int quantity) {

}

Normal::~Normal() {
}

void Normal::sell(Machine& machine, unsigned int quantity) {

}

void Normal::refill(Machine& machine, unsigned int quantity) {

}


