#include "codec.h"

MAX98090::MAX98090() {
	gpioInitialise();
	MAX98090::init();
	gpioTerminate();
}

uint8_t MAX98090::init() {
	int handle = i2cOpen(1, 0x10, 0);

	/*Set SHDN = 0
	//			0x45 (default POR state?????)
	//
	//Configure clocks 
	//			0x1B-0x21
	//
	//Configure DAI 
	//			0x22-0x25
	//
	//Configure DSP 
	//			0x17-0x1A, 0x26-0x28, 0x33-0x36, 0x41
	//
	//Load coefficients 
	//			0x46-0xBD
	//
	//Configure power and bias mode 
	//			0x42-0x44
	//
	//Configure analog mixers 
	//			0x0D, 0x15, 0x16, 0x29, 0x2A, 0x2B, 0x2E, 0x2F, 0x37, 0x3A
	//
	//Configure Analog Gain and Volume Controls. To Minimize Click 
	//and Pop for Analog Outputs, Enable Mute and Set the Output 
	//PGAs to the minimum gain setting, Enable DAC/ADC.
	//			0x0E-0x11, 0x2B-0x2D, 0x30-0x32, 0x38, 0x39, 0x3B-0x3F
	//
	//Configure misc
	//			0x03, 0x12, 0x13, 0x14, 0x40
	//
	//Set SHDN = 1 (Power up)
	//			0x45
	//
	//Disable mute on analog output
	//			0x2C, 0x2D, 0x31, 0x32, 0x39, 0x3C
	//
	//For all Analog Output Drivers, if Gain Smoothing is Disabled
	//Ramp the Gain up One Volume Step per Write until the
	//DesiredGain is Reached. If it is Enabled, Program the 
	//Desired Gain in aSingle Step.
	//			0x30-0x32, 0x38, 0x39, 0x3B, 0x3C
	//
	*/
	int byte = i2cReadByteData(handle, 0x03);
	std::cout << "Read byte: " << byte << std::endl;
	i2cClose(handle);
	return 1;
}

uint8_t MAX98090::setSingleAddress(uint8_t address, uint8_t value) {
	
	return 1;
}

uint8_t MAX98090::mainConfig(void) {
	return 1;
}
