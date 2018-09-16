/*
 * Persistent_storage.hpp
 *
 *  Created on: Sep 16, 2018
 *      Author: tamas
 */

#ifndef PERSISTENT_STORAGE_HPP_
#define PERSISTENT_STORAGE_HPP_
#include "inttypes.h"
// This class handles the communication to the EEPROM. I named this way,
//because I didn't know whether I wanted to use flash, or EEPROM for this.
class PersistentStorage{
	PersistentStorage();

};
typedef struct __attribute__ ((packed))calibrationData{
	uint8_t Header;
	uint16_t Offset;
	uint16_t multiplier;
};


#endif /* PERSISTENT_STORAGE_HPP_ */
