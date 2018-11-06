/*
 * GPIO_wrapper.hpp
 *
 *  Created on: Jul 28, 2018
 *      Author: tamas
 */

#ifndef INC_GPIO_WRAPPER_HPP_
#define INC_GPIO_WRAPPER_HPP_
#include "HAL_Driver/Inc/stm32l0xx_hal.h"

// This class handles the Output pins, such as LEDs, power toggles, etc..
class OutputPin {
	uint16_t Pin;
	GPIO_TypeDef * Port;

	public:
	OutputPin();
	OutputPin(uint16_t pin, GPIO_TypeDef * port);
	void set();
	void reset();
	void set(const GPIO_PinState & StateValue);
};

#endif  // INC_GPIO_WRAPPER_HPP_
