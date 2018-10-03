/*
 * Button_driver.hpp
 *
 *  Created on: Oct 2, 2018
 *      Author: tamas
 */

#ifndef BUTTON_DRIVER_HPP_
#define BUTTON_DRIVER_HPP_
#include "pinout_definitions.hpp"
class Button{
public:
	static SignalCallback ButtonCallback;
void Init(SignalCallback buttonCallback);
static void Disable(IRQn_Type InterruptRoutine);
static void Enable(IRQn_Type InterruptRoutine);
private:

};




#endif /* BUTTON_DRIVER_HPP_ */
