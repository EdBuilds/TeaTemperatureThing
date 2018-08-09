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
#define SEGMENT_NUMBER_IN_BLOCK 8	//I made a define for this, just to make a define
#define CONNECTED_BLOCKS 1 			//these defines are really not necessary, what am I doing?
class Display{
		static const uint8_t SevenSegmentASCII[96];
	struct segmentBlock{
	public:
		OutputPin Pins[SEGMENT_NUMBER_IN_BLOCK];
		GPIO_PinState PinSetting[SEGMENT_NUMBER_IN_BLOCK];
		void set(const uint8_t & segment);
		void set(const uint8_t & segment,GPIO_PinState state);
		void reset(const uint8_t & segment);
		void setAll();
		void setAsbinary(const uint8_t & binaryList);
		void resetAll();
		void update();
		segmentBlock();
		segmentBlock(uint16_t * pins,GPIO_TypeDef ** ports);
	};
	segmentBlock Blocks[CONNECTED_BLOCKS];
	public:
	Display();
//I know this is a terrible varable naming, I take any suggestions
void Print(char* stringToPrint);
void Clear();
void All();
};


#endif /* DISPLAY_DRIVER_HPP_ */
