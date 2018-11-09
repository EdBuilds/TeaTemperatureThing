/*
 * display_driver.hpp
 *
 *  Created on: Jul 27, 2018
 *      Author: tamas
 */

#ifndef INC_DISPLAY_DRIVER_HPP_
#define INC_DISPLAY_DRIVER_HPP_
#include <inc/gpio_wrapper.hpp>
#include "HAL_Driver/Inc/stm32l0xx_hal.h"
#include "inc/pinout_definitions.hpp"

class Display {
	static const uint8_t kSevenSegmentASCII[96];
	class SegmentBlock {
		OutputPin enable_pin_;
		OutputPin pins_[SEGMENT_NUMBER_IN_BLOCK];
		GPIO_PinState pin_setting_[SEGMENT_NUMBER_IN_BLOCK];
		public:
		void Set(const uint8_t & segment);
		void Set(const uint8_t & segment, GPIO_PinState state);
		void Reset(const uint8_t & segment);
		void SetAll();
		void SetAsBinary(const uint8_t & binary_list);
		void ResetAll();
		void On();
		void Off();
		void Update();
		SegmentBlock();
		SegmentBlock(uint16_t * segment_pins, GPIO_TypeDef ** segment_ports,
				uint16_t enable_pin, GPIO_TypeDef * enable_port);
	};
	static int active_block_;


	public:
	static TIM_HandleTypeDef htim21;
	static SegmentBlock blocks[CONNECTED_BLOCKS];
	void Init();
	Display();
	static void TimerCallback();
	// I know this is a terrible varable naming, I take any suggestions
	void Print(char* string_to_print);
	void Print(int8_t number_to_print);
	void Clear();
	void Enable();
	void Disable();
	void All();
};

#endif  // INC_DISPLAY_DRIVER_HPP_
