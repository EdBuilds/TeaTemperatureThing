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
#define BLOCK_1_PIN_A GPIO_PIN_10
#define BLOCK_1_PIN_B GPIO_PIN_9
#define BLOCK_1_PIN_C GPIO_PIN_12
#define BLOCK_1_PIN_D GPIO_PIN_0
#define BLOCK_1_PIN_E GPIO_PIN_7
#define BLOCK_1_PIN_F GPIO_PIN_6
#define BLOCK_1_PIN_G GPIO_PIN_1
#define BLOCK_1_PIN_SP GPIO_PIN_8
#define BLOCK_2_PIN_A
#define BLOCK_2_PIN_B
#define BLOCK_2_PIN_C
#define BLOCK_2_PIN_D
#define BLOCK_2_PIN_E
#define BLOCK_2_PIN_F
#define BLOCK_2_PIN_G
#define BLOCK_2_PIN_SP

#define BLOCK_1_PORT_A GPIOA
#define BLOCK_1_PORT_B GPIOA
#define BLOCK_1_PORT_C GPIOA
#define BLOCK_1_PORT_D GPIOB
#define BLOCK_1_PORT_E GPIOB
#define BLOCK_1_PORT_F GPIOB
#define BLOCK_1_PORT_G GPIOB
#define BLOCK_1_PORT_SP GPIOA
#define BLOCK_2_PORT_A
#define BLOCK_2_PORT_B
#define BLOCK_2_PORT_C
#define BLOCK_2_PORT_D
#define BLOCK_2_PORT_E
#define BLOCK_2_PORT_F
#define BLOCK_2_PORT_G
#define BLOCK_2_PORT_SP

#endif /* PINOUT_DEFINITIONS_HPP_ */
