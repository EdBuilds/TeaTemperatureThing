/*
 * signal_definition.hpp
 *
 *  Created on: Nov 5, 2018
 *      Author: tamas
 *      Description: This file defines the signals which gets passed to to the
 *      state machine. These definition were moved here to avid circular dependencies
 */

#ifndef INC_SIGNAL_DEFINITION_HPP_
#define INC_SIGNAL_DEFINITION_HPP_
#include <inttypes.h>

// Typedefs for the callback functions of the hardware interrupt layer
typedef uint8_t Signal;
typedef void (*SignalCallback)(Signal);
typedef void (*State)(Signal);

/**
 * @brief Defines the signals that can be passed to the state machine to process
 */
enum {
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
#endif  // INC_SIGNAL_DEFINITION_HPP_
