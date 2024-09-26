#include "display.h"
#include "codec.h"
#include <bcm2835.h>
#include "ST7789_TFT_LCD_RDL.hpp"

int main() {
	Display display;
	MAX98090 codec;
	/*if (display.setupHWSPI() != 0) return -1;
	display.helloWorld();
	display.endTest();*/
	return 0;
}
