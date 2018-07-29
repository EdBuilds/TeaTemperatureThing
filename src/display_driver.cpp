/*
 * display_driver.cpp
 *
 *  Created on: Jul 27, 2018
 *      Author: tamas
 */
#include "display_driver.hpp"
void Display::segmentBlock::set(const uint8_t & segment){
	//when the pin is set low, the LED turns on, because of the lame common anode 7 segment display
PinSetting[segment]=GPIO_PIN_RESET;
}
void Display::segmentBlock::reset(const uint8_t & segment){
	//when the pin is set high, the LED turns off, because of the lame common anode 7 segment display
PinSetting[segment]=GPIO_PIN_SET;

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
void Display::segmentBlock::update(){
	for(int i=0;i<SEGMENT_NUMBER_IN_BLOCK; i++){
		Pins[i].set(PinSetting[i]);
	}
}
void Display::Print(char* stringToPrint){}
void Display::Clear(){
for(int i=0; i<CONNECTED_BLOCKS; i++){
	Blocks[i].resetAll();
	Blocks[i].update();

}
}
