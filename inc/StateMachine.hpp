/*
 * StateMachine.hpp
 *
 *  Created on: Sep 30, 2018
 *      Author: tamas
 */

#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_
#include "States.hpp"

class AbstractState;
class Machine {
    public:
        Machine(unsigned int inStockQuantity);
        void sell(unsigned int quantity);
        void refill(unsigned int quantity);
        unsigned int getCurrentStock();
        ~Machine();
        AbstractState* mState;
    private:
        unsigned int mStockQuantity;
};

#endif /* STATEMACHINE_HPP_ */
