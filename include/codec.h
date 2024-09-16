#ifndef CODEC_H
#define CODEC_H

#include <iostream>
#include <pigpio.h>

class MAX98090 {
	public:
		MAX98090();
	private:
		uint8_t init();
		uint8_t setSingleAddress(uint8_t address, uint8_t value);
		uint8_t mainConfig(void);
};

#endif
