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


#define EEPROM_BASE_ADDRESS 0x08080000
#define EEPROM_CALIBRATION_ADDRESS (EEPROM_BASE_ADDRESS+0x0)
typedef struct __attribute__ ((packed)){
	uint8_t Header;
	uint16_t Offset;
	uint16_t multiplier;
}calibrationData;
typedef union {
	uint8_t Serialized[sizeof(calibrationData)];
	calibrationData Deserialized;
}serialCalibrationData;

class PersistentStorage{
public:
	PersistentStorage();
	calibrationData CalibrationData;
	void readCalibration();
	void writeCalibration();
};

#endif /* PERSISTENT_STORAGE_HPP_ */
