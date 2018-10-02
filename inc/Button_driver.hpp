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
	static State *ButtonCallback;
void Init(State *buttonCallback);
private:

};




#endif /* BUTTON_DRIVER_HPP_ */
