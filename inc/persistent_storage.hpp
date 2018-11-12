/*
 * Persistent_storage.hpp
 *
 *  Created on: Sep 16, 2018
 *      Author: tamas
 */
// This class handles the communication to the EEPROM. I named this way,
// because I didn't know whether I wanted to use flash, or EEPROM for this.
#ifndef INC_PERSISTENT_STORAGE_HPP_
#define INC_PERSISTENT_STORAGE_HPP_
#include <inttypes.h>

#define EEPROM_BASE_ADDRESS 0x08080010 // Memory address where the EEPROM field starts

// Typedefs for the eeprom storage
typedef uint8_t HeaderData;
typedef struct	__attribute__((packed)) {
	uint16_t offset;
	uint16_t multiplier;
} CalibrationData;
typedef uint8_t SetpointData;
/*
 * @brief Manages the read and write functions to the eeprom
 */
template<class T>
class EepromItem {
	typedef union {
		uint8_t serialized[sizeof(T)];
		T deserialized;
	} SerializedTemplate;
	const uint32_t start_address_;
	static uint32_t global_address_;

	public:
	EepromItem();
	uint32_t Size() const;
	T Read() const;
	void Write(const T &value) const;
};

#endif  // INC_PERSISTENT_STORAGE_HPP_
