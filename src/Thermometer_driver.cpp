/*
 * ADC_driver.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: tamas
 */

#include <Thermometer_driver.hpp>

#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_hal_tim.h"
#include "stm32l0xx_hal_gpio.h"
#include "stm32l0xx_nucleo_32.h"
Thermometer::Thermometer(): ReferenceEnable(THERMOMETER_REFERENCE_PIN,THERMOMETER_REFERENCE_PORT){
	GPIO_InitTypeDef gpioInit;

	    __GPIOC_CLK_ENABLE();
	    __HAL_RCC_ADC1_CLK_ENABLE();

	    gpioInit.Pin = THERMOMETER_PIN;
	    gpioInit.Mode = GPIO_MODE_ANALOG;
	    gpioInit.Pull = GPIO_NOPULL;
	    HAL_GPIO_Init(THERMOMETER_PORT, &gpioInit);

	    HAL_NVIC_SetPriority(ADC1_COMP_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(ADC1_COMP_IRQn);
	    AdcHandle=ADC_HandleTypeDef();
	    AdcChannel=ADC_ChannelConfTypeDef();

	    AdcHandle.Instance = THERMOMETER_ADC_INSTANCE;

	    AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
	    AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
	    AdcHandle.Init.ScanConvMode = DISABLE;
	    AdcHandle.Init.ContinuousConvMode = ENABLE;
	    AdcHandle.Init.DiscontinuousConvMode = DISABLE;
	    AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	    AdcHandle.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	    AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	    AdcHandle.Init.DMAContinuousRequests = ENABLE;
	    AdcHandle.Init.EOCSelection = DISABLE;

	    HAL_ADC_Init(&AdcHandle);

	    AdcChannel.Channel = THERMOMETER_ADC_CHANNEL;
	    AdcChannel.Rank = 1;

	    if (HAL_ADC_ConfigChannel(&AdcHandle, &AdcChannel) != HAL_OK)
	    {
	        asm("bkpt 255");
	    }
	    //Initialize reference pin
	   ReferenceEnable.reset();
	}
uint16_t Thermometer::measure(){
	uint16_t returnValue=0;
    ReferenceEnable.set();
    //It takes around 4 us for the voltage to stabilize, It would be a good idea to put a 5 us delay here.
	HAL_ADC_Start(&AdcHandle);
	if (HAL_ADC_PollForConversion(&AdcHandle, 1000000) == HAL_OK)
	{
	     returnValue=HAL_ADC_GetValue(&AdcHandle);
	}
    ReferenceEnable.reset();
return returnValue;
}



