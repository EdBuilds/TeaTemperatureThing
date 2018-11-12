/*
 * GPIO_wrapper.cpp
 *
 *  Created on: Jul 28, 2018
 *      Author: tamas
 */
#include <gpio_wrapper.hpp>
OutputPin::OutputPin() {
}

/**
 * Sets up the hardware layer for the output pin
 * @param pin the GPIO pin to use
 * @param port the GPIO ports to use
 */
OutputPin::OutputPin(uint16_t pin, GPIO_TypeDef * port) {
	port_ = port;
	pin_ = pin;
	// GPIO Ports Clock Enable
	switch (reinterpret_cast<uint32_t>(port_)) {
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

	GPIO_InitTypeDef gpio_init_struct;
	gpio_init_struct.Pin = pin_;
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_struct.Speed = GPIO_SPEED_LOW;
	HAL_GPIO_Init(port_, &gpio_init_struct);
}
/**
 * Sets the GPIO pin logical high
 */
void OutputPin::Set() {
	HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_SET);
}
/**
 * Sets the GPIO pin logical low
 */
void OutputPin::Reset() {
	HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_RESET);
}
/**
 * Sets the GPIO pin output to the
 */
void OutputPin::Set(const GPIO_PinState & state) {
	HAL_GPIO_WritePin(port_, pin_, state);
}

