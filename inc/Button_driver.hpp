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
class Button {
public:
	static SignalCallback ButtonCallback;
	void Init(SignalCallback buttonCallback);
	GPIO_PinState Read(ButtonID button);
	static void Disable(IRQn_Type InterruptRoutine);
	static void Enable(IRQn_Type InterruptRoutine);
};

#endif  // INC_BUTTON_DRIVER_HPP_
