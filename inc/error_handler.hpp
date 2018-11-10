/*
 * ErrorHandler.hpp
 *
 *  Created on: Oct 14, 2018
 *      Author: tamas
 */

#ifndef INC_ERROR_HANDLER_HPP_
#define INC_ERROR_HANDLER_HPP_

/**
 * @brief This function enters an infinite loop to prevent any undetermined behaviour
 */
inline void FatalError(char *file, int line) {
	while (true) {
		// The program enters an infinite loop in case of an error
	}
}

#endif  // INC_ERROR_HANDLER_HPP_
