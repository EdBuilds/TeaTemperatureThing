/*
 * GPIO_wrapper.hpp
 *
 *  Created on: Jul 28, 2018
 *      Author: tamas
 */

#ifndef INC_GPIO_WRAPPER_HPP_
#define INC_GPIO_WRAPPER_HPP_
#include "HAL_Driver/Inc/stm32l0xx_hal.h"

/**
 * @brief  This class handles the Output pins, such as LEDs, power toggles, etc..
 */
class OutputPin {
	uint16_t pin_;
	GPIO_TypeDef * port_;

	public:
	OutputPin();
	OutputPin(uint16_t pin, GPIO_TypeDef * port);
	void Set();
	void Reset();
	void Set(const GPIO_PinState & state);
};

#endif  // INC_GPIO_WRAPPER_HPP_
