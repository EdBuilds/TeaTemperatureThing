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
#define CONNECTED_BLOCKS 2 			//these defines are really not necessary, what am I doing?
class Display{
	struct segmentBlock{
		uint8_t SevenSegmentASCII;
	OutputPin Pins[SEGMENT_NUMBER_IN_BLOCK];
	GPIO_PinState PinSetting[SEGMENT_NUMBER_IN_BLOCK];
	void set(const uint8_t & segment);
	void reset(const uint8_t & segment);
	void setAll();
	void resetAll();
	void update();
	};
	segmentBlock Blocks[CONNECTED_BLOCKS];
	public:

//I know this is a terrible varable naming, I take any suggestions
void Print(char* stringToPrint);
void Clear();
};


#endif /* DISPLAY_DRIVER_HPP_ */
