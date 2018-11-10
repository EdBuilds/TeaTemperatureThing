/*
 * Button_driver.hpp
 *
 *  Created on: Oct 2, 2018
 *      Author: tamas
 */

#ifndef INC_BUTTON_DRIVER_HPP_
#define INC_BUTTON_DRIVER_HPP_
#include "inc/signal_definition.hpp"
#include "HAL_Driver/Inc/stm32l0xx_hal.h"

typedef enum {
	BUTTON_1, BUTTON_2
} ButtonID;

/**
 * @brief handles the interaction of the buttons based on rising/falling edge interrupt  on
 * input pins
 */
class Button {
	public:
	static SignalCallback button_callback_;
	void Init(SignalCallback button_callback);
	GPIO_PinState Read(ButtonID button);
	static void Disable(IRQn_Type interrupt_routine);
	static void Enable(IRQn_Type interrupt_routine);
};

#endif  // INC_BUTTON_DRIVER_HPP_
