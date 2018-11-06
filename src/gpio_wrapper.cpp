/*
 * GPIO_wrapper.cpp
 *
 *  Created on: Jul 28, 2018
 *      Author: tamas
 */
#include <gpio_wrapper.hpp>
OutputPin::OutputPin() {
}
OutputPin::OutputPin(uint16_t pin, GPIO_TypeDef * port) {
	Port = port;
	Pin = pin;
	// GPIO Ports Clock Enable
	switch (reinterpret_cast<uint32_t>(Port)) {
	case GPIOA_BASE:
		__GPIOA_CLK_ENABLE()
		;
		break;
	case GPIOB_BASE:
		__GPIOB_CLK_ENABLE()
		;
		break;
	case GPIOC_BASE:
		__GPIOC_CLK_ENABLE()
		;
		break;
	}

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(Port, &GPIO_InitStruct);
}
/**
 * Sets the GPIO pin logical high
 */
void OutputPin::set() {
	HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_SET);
}
/**
 * Sets the GPIO pin logical low
 */
void OutputPin::reset() {
	HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_RESET);
}
/**
 * Sets the GPIO pin output to the
 */
void OutputPin::set(const GPIO_PinState & StateValue) {
	HAL_GPIO_WritePin(Port, Pin, StateValue);
}

