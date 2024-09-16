#ifndef DISPLAY_H
#define DISPLAY_H
#include <bcm2835.h>
#include "ST7789_TFT_LCD_RDL.hpp"

class Display {
	public:
		Display();
	private:
		uint8_t setupHWSPI();
		void helloWorld(void);
		void endTest(void);
};

#endif
