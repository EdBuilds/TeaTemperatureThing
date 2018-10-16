/*
 * display_driver.cpp
 *
 *  Created on: Jul 27, 2018
 *      Author: tamas
 */
#include "display_driver.hpp"
#include "stm32l011xx.h"
#include "stm32l0xx_it.h"
#include "stm32l0xx_hal.h"
#include "stdlib.h"
#define ASCII_OFFSET 32
TIM_HandleTypeDef Display::htim21;
int Display::activeBlock=0;
Display::segmentBlock Display::Blocks[CONNECTED_BLOCKS];
void Display::segmentBlock::set(const uint8_t & segment){
	//when the pin is set low, the LED turns on, because of the lame common anode 7 segment display
PinSetting[segment]=GPIO_PIN_RESET;
}
void Display::segmentBlock::reset(const uint8_t & segment){
	//when the pin is set high, the LED turns off, because of the lame common anode 7 segment display
PinSetting[segment]=GPIO_PIN_SET;

}


void Display::segmentBlock::set(const uint8_t & segment,GPIO_PinState state){
	Pins[segment].set(state);
}
void Display::segmentBlock::setAll(){
for(int i=0;i<SEGMENT_NUMBER_IN_BLOCK; i++){
	//when the pin is set low, the LED turns on, because of the lame common anode 7 segment display
	PinSetting[i]=GPIO_PIN_RESET;
	}
}
void Display::segmentBlock::resetAll(){
for(int i=0;i<SEGMENT_NUMBER_IN_BLOCK; i++){
	//I wont paste this comment for the fourth time
	PinSetting[i]=GPIO_PIN_SET;
	}
}

void Display::segmentBlock::on(){
EnablePin.set();
}
void Display::segmentBlock::off(){
EnablePin.reset();
}

void Display::segmentBlock::update(){
	for(int i=0;i<SEGMENT_NUMBER_IN_BLOCK; i++){
		Pins[i].set(PinSetting[i]);
	}
}
void Display::Print(char* stringToPrint){
	for(int i=0; i<CONNECTED_BLOCKS; i++){
		Blocks[i].setAsbinary(SevenSegmentASCII[uint8_t(stringToPrint[i])-ASCII_OFFSET]);
		//Blocks[i].update();
	}
}
void Display::Print(int8_t numberToPrint){
	  itoa(numberToPrint,buffer,10);
	  Print(buffer);

}
void Display::Clear(){
for(int i=0; i<CONNECTED_BLOCKS; i++){
	Blocks[i].resetAll();
	//Blocks[i].update();

}
}
void Display::All(){
for(int i=0; i<CONNECTED_BLOCKS; i++){
	Blocks[i].setAll();
	//Blocks[i].update();

}
}

void Display::segmentBlock::setAsbinary(const uint8_t & binaryList){
		for( int i=0; i<SEGMENT_NUMBER_IN_BLOCK; i++){
			if((binaryList >> i) & 1){		//checking each bit of the input
				set(i);
			}else{
				reset(i);
			}
		}
	}
Display::segmentBlock::segmentBlock(){}


Display::segmentBlock::segmentBlock(uint16_t * segmentPins,GPIO_TypeDef ** segmentPorts, uint16_t enablePin, GPIO_TypeDef * enablePort){
		for(int i=0 ; i<SEGMENT_NUMBER_IN_BLOCK;i++){
			Pins[i]=OutputPin(segmentPins[i],segmentPorts[i]);
		}
EnablePin=OutputPin(enablePin,enablePort);
	}
Display::Display(){
uint16_t Block1Pins[]={BLOCK_1_PIN_A,
		BLOCK_1_PIN_B,
		BLOCK_1_PIN_C,
		BLOCK_1_PIN_D,
		BLOCK_1_PIN_E,
		BLOCK_1_PIN_F,
		BLOCK_1_PIN_G,
		BLOCK_1_PIN_SP};
GPIO_TypeDef* Block1Ports[]={BLOCK_1_PORT_A,
		BLOCK_1_PORT_B,
		 BLOCK_1_PORT_C,
		 BLOCK_1_PORT_D,
		 BLOCK_1_PORT_E,
		 BLOCK_1_PORT_F,
		 BLOCK_1_PORT_G,
		 BLOCK_1_PORT_SP};
	Blocks[0]=segmentBlock(Block1Pins,Block1Ports,BLOCK_1_ENABLE_PIN, BLOCK_1_ENABLE_PORT);
	Blocks[1]=segmentBlock(Block1Pins,Block1Ports,BLOCK_2_ENABLE_PIN, BLOCK_2_ENABLE_PORT);
}

void Display::Init(){
    __HAL_RCC_TIM21_CLK_ENABLE();

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  htim21=TIM_HandleTypeDef();
  htim21.Instance = TIM21;
  htim21.Init.Prescaler = 16-1;
  htim21.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim21.Init.Period = 1000;
  htim21.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim21) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim21, &sClockSourceConfig) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim21, &sMasterConfig) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }

    /* TIM21 interrupt Init */
    HAL_NVIC_SetPriority(TIM21_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM21_IRQn);
}



void Display::Enable(){
	Blocks[activeBlock].on();
if (HAL_TIM_Base_Start_IT(&htim21) != HAL_OK)
{
    //_Error_Handler(__FILE__, __LINE__);
}
}
void Display::Disable(){
if (HAL_TIM_Base_Stop_IT(&htim21) != HAL_OK)
{
    //_Error_Handler(__FILE__, __LINE__);
}
Blocks[activeBlock].off();
}


void Display::TimerCallback(){
	Blocks[activeBlock].off();
	activeBlock=(++activeBlock)%CONNECTED_BLOCKS;
	Blocks[activeBlock].update();
	Blocks[activeBlock].on();
}

void TIM21_IRQHandler(void)
{
  /* USER CODE BEGIN TIM21_IRQn 0 */

  /* USER CODE END TIM21_IRQn 0 */
  HAL_TIM_IRQHandler(&Display::htim21);
  /* USER CODE BEGIN TIM21_IRQn 1 */
  Display::TimerCallback();
  /* USER CODE END TIM21_IRQn 1 */
}







//Defining ASCII to 7 segments here, not to clutter the .h
//all credits to dmadison.
//nothing interesting after this point move along citizen.
const uint8_t Display::SevenSegmentASCII[96] = {
	0b00000000, /* (space) */
	0b10000110, /* ! */
	0b00100010, /* " */
	0b01111110, /* # */
	0b01101101, /* $ */
	0b11010010, /* % */
	0b01000110, /* & */
	0b00100000, /* ' */
	0b00101001, /* ( */
	0b00001011, /* ) */
	0b00100001, /* * */
	0b01110000, /* + */
	0b00010000, /* , */
	0b01000000, /* - */
	0b10000000, /* . */
	0b01010010, /* / */
	0b00111111, /* 0 */
	0b00000110, /* 1 */
	0b01011011, /* 2 */
	0b01001111, /* 3 */
	0b01100110, /* 4 */
	0b01101101, /* 5 */
	0b01111101, /* 6 */
	0b00000111, /* 7 */
	0b01111111, /* 8 */
	0b01101111, /* 9 */
	0b00001001, /* : */
	0b00001101, /* ; */
	0b01100001, /* < */
	0b01001000, /* = */
	0b01000011, /* > */
	0b11010011, /* ? */
	0b01011111, /* @ */
	0b01110111, /* A */
	0b01111100, /* B */
	0b00111001, /* C */
	0b01011110, /* D */
	0b01111001, /* E */
	0b01110001, /* F */
	0b00111101, /* G */
	0b01110110, /* H */
	0b00110000, /* I */
	0b00011110, /* J */
	0b01110101, /* K */
	0b00111000, /* L */
	0b00010101, /* M */
	0b00110111, /* N */
	0b00111111, /* O */
	0b01110011, /* P */
	0b01101011, /* Q */
	0b00110011, /* R */
	0b01101101, /* S */
	0b01111000, /* T */
	0b00111110, /* U */
	0b00111110, /* V */
	0b00101010, /* W */
	0b01110110, /* X */
	0b01101110, /* Y */
	0b01011011, /* Z */
	0b00111001, /* [ */
	0b01100100, /* \ */
	0b00001111, /* ] */
	0b00100011, /* ^ */
	0b00001000, /* _ */
	0b00000010, /* ` */
	0b01011111, /* a */
	0b01111100, /* b */
	0b01011000, /* c */
	0b01011110, /* d */
	0b01111011, /* e */
	0b01110001, /* f */
	0b01101111, /* g */
	0b01110100, /* h */
	0b00010000, /* i */
	0b00001100, /* j */
	0b01110101, /* k */
	0b00110000, /* l */
	0b00010100, /* m */
	0b01010100, /* n */
	0b01011100, /* o */
	0b01110011, /* p */
	0b01100111, /* q */
	0b01010000, /* r */
	0b01101101, /* s */
	0b01111000, /* t */
	0b00011100, /* u */
	0b00011100, /* v */
	0b00010100, /* w */
	0b01110110, /* x */
	0b01101110, /* y */
	0b01011011, /* z */
	0b01000110, /* { */
	0b00110000, /* | */
	0b01110000, /* } */
	0b00000001, /* ~ */
	0b00000000, /* (del) */
};
