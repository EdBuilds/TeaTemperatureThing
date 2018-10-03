/*
 * Button_driver.cpp
 *
 *  Created on: Oct 2, 2018
 *      Author: tamas
 */
#include "Button_driver.hpp"
#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_it.h"
#include "pinout_definitions.hpp"
 SignalCallback Button::ButtonCallback;
void Button::Init(SignalCallback buttonCallback){
	ButtonCallback=buttonCallback;
	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  GPIO_InitTypeDef GPIO_InitStruct;
	  GPIO_InitStruct.Pin = BUTTON_1_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(BUTTON_1_PORT, &GPIO_InitStruct);

	  HAL_NVIC_SetPriority(BUTTON_1_ITn, 0, 0);
	  HAL_NVIC_EnableIRQ(BUTTON_1_ITn);

	  GPIO_InitStruct.Pin = BUTTON_2_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(BUTTON_2_PORT, &GPIO_InitStruct);

	  HAL_NVIC_SetPriority(BUTTON_2_ITn, 0, 0);
	  HAL_NVIC_EnableIRQ(BUTTON_2_ITn);

}


void EXTI0_1_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(BUTTON_1_PIN);

	if(HAL_GPIO_ReadPin(BUTTON_1_PORT,BUTTON_1_PIN)==GPIO_PIN_SET){
		Button::ButtonCallback(SIG_BUTTON_1_DN);
	}else{
		Button::ButtonCallback(SIG_BUTTON_1_UP);
	}
}


void EXTI2_3_IRQHandler(void)
{
	HAL_Delay(5);
    HAL_GPIO_EXTI_IRQHandler(BUTTON_2_PIN);
	if(HAL_GPIO_ReadPin(BUTTON_2_PORT,BUTTON_2_PIN)==GPIO_PIN_SET){
		Button::ButtonCallback(SIG_BUTTON_2_DN);
	}else{
		Button::ButtonCallback(SIG_BUTTON_2_UP);
	}

}