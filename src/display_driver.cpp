/*
 * display_driver.cpp
 *
 *  Created on: Jul 27, 2018
 *      Author: tamas
 */
#include "inc/display_driver.hpp"
//#include "stm32l011xx.h"
#include "inc/stm32l0xx_it.h"
#include "HAL_Driver/Inc/stm32l0xx_hal.h"
#include "stdlib.h"
#define ASCII_OFFSET 32
TIM_HandleTypeDef Display::htim21;
int Display::active_block_ = 0;
Display::SegmentBlock Display::blocks[CONNECTED_BLOCKS];

/**
 * @brief sets the selected segment in the segment buffer
 * @param segment the segment to ligt up later
 */
void Display::SegmentBlock::Set(const uint8_t & segment) {
	//when the pin is set low, the LED turns on, because of the lame common anode 7 segment display
	pin_setting_[segment] = GPIO_PIN_RESET;
}

/**
 * @brief resets the selected segment in the segment buffer
 * @param segment the segment to turn off later
 */
void Display::SegmentBlock::Reset(const uint8_t & segment) {
	//when the pin is set high, the LED turns off, because of the lame common anode 7 segment display
	pin_setting_[segment] = GPIO_PIN_SET;

}

/**
 * @brief sets the given segment to the given state in the buffer
 * @param segment the segment to set to state
 * @param state the state to set to segment
 */
void Display::SegmentBlock::Set(const uint8_t & segment, GPIO_PinState state) {
	pins_[segment].Set(state);
}

/**
 * @brief sets all the segemnts in the segment buffer
 */
void Display::SegmentBlock::SetAll() {
	for (int i = 0; i < SEGMENT_NUMBER_IN_BLOCK; i++) {
		//when the pin is set low, the LED turns on, because of the lame common anode 7 segment display
		pin_setting_[i] = GPIO_PIN_RESET;
	}
}

/**
 * @brief resets all the segments in the segment buffer
 */
void Display::SegmentBlock::ResetAll() {
	for (int i = 0; i < SEGMENT_NUMBER_IN_BLOCK; i++) {
		//I wont paste this comment for the fourth time
		pin_setting_[i] = GPIO_PIN_SET;
	}
}
/**
 * @brief enables the 7 segment block
 */
void Display::SegmentBlock::On() {
	enable_pin_.Set();
}
/**
 * @brief disables the 7 segment block
 */
void Display::SegmentBlock::Off() {
	enable_pin_.Reset();
}

/**
 * @brief sets the pins according to the segment buffer
 */
void Display::SegmentBlock::Update() {
	for (int i = 0; i < SEGMENT_NUMBER_IN_BLOCK; i++) {
		pins_[i].Set(pin_setting_[i]);
	}
}

/**
 * @brief Prints a string to the display
 * @param string_to_print the string to display
 */
void Display::Print(char* string_to_print) {
	for (int i = 0; i < CONNECTED_BLOCKS; i++) {
		blocks[i].SetAsBinary(
				kSevenSegmentASCII[uint8_t(string_to_print[i]) - ASCII_OFFSET]);
		//Blocks[i].update();
	}
}

/**
 * @brief Prints a number to the display
 * @param number_to_print the number to print
 */
void Display::Print(int8_t number_to_print) {
	char buffer[5];
	itoa(number_to_print, buffer, 10);
	Print(buffer);

}

/**
 * @brief Clears the display
 */
void Display::Clear() {
	for (int i = 0; i < CONNECTED_BLOCKS; i++) {
		blocks[i].ResetAll();
	}
}
/**
 * @brief Turns on all the segments
 */
void Display::All() {
	for (int i = 0; i < CONNECTED_BLOCKS; i++) {
		blocks[i].SetAll();
	}
}

/**
 * @brief Sets segmenst according to the binary list
 * @param binary_list the bytes to set the segments
 */
void Display::SegmentBlock::SetAsBinary(const uint8_t & binary_list) {
	for (int i = 0; i < SEGMENT_NUMBER_IN_BLOCK; i++) {
		if ((binary_list >> i) & 1) {		//checking each bit of the input
			Set(i);
		} else {
			Reset(i);
		}
	}
}

Display::SegmentBlock::SegmentBlock() {
}

/**
 * @brief 7 segmnet display block constructor
 * @param segment_pins the GPIO pins that are connected to the segments
 * @param segment_ports the GPIO ports that are connected to the segments
 * @param enable_pin the GPIO pin that is connected to the enable pin of the display
 * @param enable_port the GPIO port that is connected to the enable pin of the display
 */
Display::SegmentBlock::SegmentBlock(uint16_t * segment_pins,
		GPIO_TypeDef ** segment_ports, uint16_t enable_pin,
		GPIO_TypeDef * enable_port) {
	for (int i = 0; i < SEGMENT_NUMBER_IN_BLOCK; i++) {
		pins_[i] = OutputPin(segment_pins[i], segment_ports[i]);
	}
	enable_pin_ = OutputPin(enable_pin, enable_port);
}

Display::Display() {
	uint16_t Block1Pins[] = { BLOCK_1_PIN_A,
	BLOCK_1_PIN_B,
	BLOCK_1_PIN_C,
	BLOCK_1_PIN_D,
	BLOCK_1_PIN_E,
	BLOCK_1_PIN_F,
	BLOCK_1_PIN_G,
	BLOCK_1_PIN_SP };
	GPIO_TypeDef* Block1Ports[] = { BLOCK_1_PORT_A,
	BLOCK_1_PORT_B,
	BLOCK_1_PORT_C,
	BLOCK_1_PORT_D,
	BLOCK_1_PORT_E,
	BLOCK_1_PORT_F,
	BLOCK_1_PORT_G,
	BLOCK_1_PORT_SP };
	blocks[0] = SegmentBlock(Block1Pins, Block1Ports, BLOCK_1_ENABLE_PIN,
			BLOCK_1_ENABLE_PORT);
	blocks[1] = SegmentBlock(Block1Pins, Block1Ports, BLOCK_2_ENABLE_PIN,
			BLOCK_2_ENABLE_PORT);
}

/**
 * @brief Initializes the hardware layer of the display
 */
void Display::Init() {
	__HAL_RCC_TIM21_CLK_ENABLE();

	TIM_ClockConfigTypeDef clock_source_config;
	TIM_MasterConfigTypeDef master_config;
	htim21 = TIM_HandleTypeDef();
	htim21.Instance = TIM21;
	htim21.Init.Prescaler = 16 - 1;
	htim21.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim21.Init.Period = 1000;
	htim21.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	if (HAL_TIM_Base_Init(&htim21) != HAL_OK) {
		//_Error_Handler(__FILE__, __LINE__);
	}

	clock_source_config.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim21, &clock_source_config) != HAL_OK) {
		//_Error_Handler(__FILE__, __LINE__);
	}

	master_config.MasterOutputTrigger = TIM_TRGO_RESET;
	master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim21, &master_config)
			!= HAL_OK) {
		//_Error_Handler(__FILE__, __LINE__);
	}

	/* TIM21 interrupt Init */
	HAL_NVIC_SetPriority(TIM21_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM21_IRQn);
}

/**
 * @brief Turns on the display
 */
void Display::Enable() {
	blocks[active_block_].On();
	if (HAL_TIM_Base_Start_IT(&htim21) != HAL_OK) {
		//_Error_Handler(__FILE__, __LINE__);
	}
}
/**
 * @brief Turns off the display
 */
void Display::Disable() {
	if (HAL_TIM_Base_Stop_IT(&htim21) != HAL_OK) {
		//_Error_Handler(__FILE__, __LINE__);
	}
	blocks[active_block_].Off();
}

/**
 * @brief Callback function for the timer
 */
void Display::TimerCallback() {
	blocks[active_block_].Off();
	active_block_ = (++active_block_) % CONNECTED_BLOCKS;
	blocks[active_block_].Update();
	blocks[active_block_].On();
}

/**
 * @brief Interrupt handler of the timer
 */
void TIM21_IRQHandler(void) {
	HAL_TIM_IRQHandler(&Display::htim21);
	Display::TimerCallback();
}


//Defining ASCII to 7 segments here, not to clutter the .h
//all credits to dmadison.
//nothing interesting after this point move along citizen.
const uint8_t Display::kSevenSegmentASCII[96] = { 0b00000000, /* (space) */
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
