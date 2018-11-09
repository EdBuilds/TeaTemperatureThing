/*
 * ADC_driver.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: tamas
 */

#include <error_handler.hpp>
#include <thermometer_driver.hpp>
#include "HAL_Driver/Inc/stm32l0xx_hal.h"

/**
 * Initializes the hardware layer of the ADC
 */
Thermometer::Thermometer(): reference_enable_(THERMOMETER_REFERENCE_PIN,THERMOMETER_REFERENCE_PORT){
	    __HAL_RCC_ADC1_CLK_ENABLE();
		GPIO_InitTypeDef gpio_init;
	    gpio_init.Pin = THERMOMETER_PIN;
	    gpio_init.Mode = GPIO_MODE_ANALOG;
	    gpio_init.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(THERMOMETER_PORT, &gpio_init);

	    adc_handle_=ADC_HandleTypeDef();
	    adc_channel_=ADC_ChannelConfTypeDef();

	    adc_handle_.Instance = THERMOMETER_ADC_INSTANCE;
	    adc_handle_.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	    adc_handle_.Init.Resolution = ADC_RESOLUTION_12B;
	    adc_handle_.Init.ScanConvMode = DISABLE;
	    adc_handle_.Init.ContinuousConvMode = ENABLE;
	    adc_handle_.Init.DiscontinuousConvMode = DISABLE;
	    adc_handle_.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	    adc_handle_.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	    adc_handle_.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	    adc_handle_.Init.DMAContinuousRequests = ENABLE;
	    adc_handle_.Init.EOCSelection = DISABLE;

	    HAL_ADC_Init(&adc_handle_);

	    adc_channel_.Channel = THERMOMETER_ADC_CHANNEL;
	    adc_channel_.Rank = 1;

	    if (HAL_ADC_ConfigChannel(&adc_handle_, &adc_channel_) != HAL_OK)
	    {
	    	FatalError(__FILE__, __LINE__);
	    }
	    //Initialize reference pin
	   //ReferenceEnable.reset();
	}

/**
 * @brief Measures the voltage on the ADC1 pin
 * @return The result of the ADC conversion
 */
uint16_t Thermometer::Measure(){
	uint16_t return_value=0;
    //ReferenceEnable.set();
    //It takes around 4 us for the voltage to stabilize, It would be a good idea to put a 5 us delay here.
	HAL_ADC_Start(&adc_handle_);
	if (HAL_ADC_PollForConversion(&adc_handle_, 1000) == HAL_OK)
	{
	     return_value=HAL_ADC_GetValue(&adc_handle_);
	}
	HAL_ADC_Stop(&adc_handle_);
    //ReferenceEnable.reset();
return return_value;
}
