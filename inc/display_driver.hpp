/*
 * display_driver.hpp
 *
 *  Created on: Jul 27, 2018
 *      Author: tamas
 */

#ifndef DISPLAY_DRIVER_HPP_
#define DISPLAY_DRIVER_HPP_
#include "stm32l0xx_hal.h"
#include "GPIO_wrapper.hpp"
#include "pinout_definitions.hpp"
class Display {
	static const uint8_t SevenSegmentASCII[96];
	struct segmentBlock {
	public:
		OutputPin EnablePin;
		OutputPin Pins[SEGMENT_NUMBER_IN_BLOCK];
		GPIO_PinState PinSetting[SEGMENT_NUMBER_IN_BLOCK];
		void set(const uint8_t & segment);
		void set(const uint8_t & segment, GPIO_PinState state);
		void reset(const uint8_t & segment);
		void setAll();
		void setAsbinary(const uint8_t & binaryList);
		void resetAll();
		void on();
		void off();
		void update();
		segmentBlock();
		segmentBlock(uint16_t * segmentPins, GPIO_TypeDef ** segmentPorts,
				uint16_t enablePin, GPIO_TypeDef * enablePort);
	};
	static segmentBlock Blocks[CONNECTED_BLOCKS];
	static int activeBlock;
public:
	static TIM_HandleTypeDef htim21;
	void Init();
	Display();
	static void TimerCallback();
//I know this is a terrible varable naming, I take any suggestions
	void Print(char* stringToPrint);
	void Clear();
	void All();
};

#endif /* DISPLAY_DRIVER_HPP_ */
