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


#define EEPROM_BASE_ADDRESS 0x08080010
#define EEPROM_HEADER_ADDRESS (EEPROM_BASE_ADDRESS+0x0)
#define EEPROM_CALIBRATION_ADDRESS (EEPROM_BASE_ADDRESS+sizeof(HeaderData))
#define EEPROM_SETPOINT_ADDRESS (EEPROM_BASE_ADDRESS+sizeof(HeaderData)+sizeof(calibrationData))
#define EEPROM_HEADER 0xA0

#define EEPROM_SETPOINT_HEADER 0xA3
typedef uint8_t HeaderData;
typedef struct __attribute__ ((packed)){
	uint16_t Offset;
	uint16_t multiplier;
}calibrationData;
typedef uint8_t setpointData;


template <class T>
class EepromItem{
	typedef union {
		uint8_t Serialized[sizeof(T)];
		T Deserialized;
	}SerializedTemplate;
	const uint32_t _startAddress;
	static uint32_t _globalAddress;

  public:
EepromItem();
uint32_t size() const;
T Read() const;
void Write(const T &value) const;
};

#endif /* PERSISTENT_STORAGE_HPP_ */
