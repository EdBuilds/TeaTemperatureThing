/*
 * ADC_driver.hpp
 *
 *  Created on: Aug 10, 2018
 *      Author: tamas
 */

#ifndef INC_THERMOMETER_DRIVER_HPP_
#define INC_THERMOMETER_DRIVER_HPP_
#include <inc/gpio_wrapper.hpp>
#include "HAL_Driver/Inc/stm32l0xx_hal.h"
#include "inc/pinout_definitions.hpp"

/**
 * @brief Wraps the ADC conversion of the thermometer in a class form
 */
class Thermometer {
	OutputPin reference_enable_;
	ADC_HandleTypeDef adc_handle_;
	ADC_ChannelConfTypeDef adc_channel_;

	public:
	uint16_t Measure();
	Thermometer();
};

#endif  // INC_THERMOMETER_DRIVER_HPP_
