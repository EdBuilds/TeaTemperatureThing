/*
 * States.hpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */

#ifndef STATES_HPP_
#define STATES_HPP_

#include "StateMachine.hpp"

class Machine;

class AbstractState {
    public:
         void sell(Machine& machine, unsigned int quantity);
         void refill(Machine& machine, unsigned int quantity);
         ~AbstractState();
    protected:
        void setState(Machine& machine, AbstractState* st);
        void updateStock(Machine& machine, unsigned int quantity);
};

class Normal {
    public:
         void sell(Machine& machine, unsigned int quantity);
         void refill(Machine& machine, unsigned int quantity);
         ~Normal();
};





#endif /* STATES_HPP_ */
