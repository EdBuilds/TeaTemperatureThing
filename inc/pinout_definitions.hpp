/*
 * pinout_definitions.hpp
 *
 *  Created on: Sep 15, 2018
 *      Author: tamas
 */

#ifndef PINOUT_DEFINITIONS_HPP_
#define PINOUT_DEFINITIONS_HPP_
#include "stm32l0xx.h"
//Buzzer pin definitions
#define BUZZER_TIMER_CHANNEL TIM_CHANNEL_1
#define BUZZER_TIMER TIM2
#define BUZZER_GPIO_PORT GPIOA
#define BUZZER_GPIO_PIN GPIO_PIN_0

//Display pin definitions
#define SEGMENT_NUMBER_IN_BLOCK 8	//I made a define for this, just to make a define
#define CONNECTED_BLOCKS 1 			//these defines are really not necessary, what am I doing?
#define BLOCK_1_PIN_A GPIO_PIN_12
#define BLOCK_1_PIN_B GPIO_PIN_0
#define BLOCK_1_PIN_C GPIO_PIN_7
#define BLOCK_1_PIN_D GPIO_PIN_6
#define BLOCK_1_PIN_E GPIO_PIN_1
#define BLOCK_1_PIN_F GPIO_PIN_8
#define BLOCK_1_PIN_G GPIO_PIN_11
#define BLOCK_1_PIN_SP GPIO_PIN_5

#define BLOCK_1_PORT_A GPIOA
#define BLOCK_1_PORT_B GPIOB
#define BLOCK_1_PORT_C GPIOB
#define BLOCK_1_PORT_D GPIOB
#define BLOCK_1_PORT_E GPIOB
#define BLOCK_1_PORT_F GPIOA
#define BLOCK_1_PORT_G GPIOA
#define BLOCK_1_PORT_SP GPIOB

#define BLOCK_1_ENABLE_PIN GPIO_PIN_4
#define BLOCK_1_ENABLE_PORT GPIOB

#define BLOCK_2_ENABLE_PIN GPIO_PIN_3
#define BLOCK_2_ENABLE_PORT GPIOA

//Button pin definitions
#define BUTTON_1_PIN GPIO_PIN_0
#define BUTTON_2_PIN GPIO_PIN_2
#define BUTTON_1_PORT GPIOA
#define BUTTON_2_PORT GPIOA
#define BUTTON_1_ITn EXTI0_1_IRQn
#define BUTTON_2_ITn EXTI2_3_IRQn


//state definitions I put it here instead of the StateMachine header, to prevent circular dependencies
typedef uint8_t Signal;
typedef void(*SignalCallback)(Signal);
enum
{
	SIG_NONE,
	SIG_ALARM_A,
	SIG_ALARM_B,
	SIG_BUTTON_1_DN,
	SIG_BUTTON_1_UP,
	SIG_BUTTON_2_DN,
	SIG_BUTTON_2_UP,
	SIG_ENTRY,
	SIG_EXIT
};
#endif /* PINOUT_DEFINITIONS_HPP_ */
