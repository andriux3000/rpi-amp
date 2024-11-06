#include "display.h"
#include "codec.h"
#include <bcm2835.h>
#include "ST7789_TFT_LCD_RDL.hpp"
#include "rotary_encoder.h"
#include <stdio.h>
#include <pigpio.h>
#include "control.h"

void callback(int way){
	//static int pos = 0;
	//pos += way;
	//printf("pos=%d\n", pos);
	if (way == CLOCKWISE) printf("CLOCKWISE\n");
	if (way == COUNTERCLOCKWISE) printf("COUNTERCLOCKWISE\n");
	if (way == BUTTON_PRESS) printf("BUTTON_PRESS\n");
	if (way == BUTTON_RELEASE) printf("BUTTON_RELEASE\n");
	if (way == LONG_PRESS) printf("LONG_PRESS\n");
	if (way == DOUBLE_PRESS) printf("DOUBLE_PRESS\n");
	if (way == TRIPLE_PRESS) printf("TRIPLE_PRESS\n");
}

int main() {
	//Display display;
	//MAX98090 codec;
	/*if (display.setupHWSPI() != 0) return -1;
	display.helloWorld();
	display.endTest();*/
	
	//if (gpioInitialise() < 0) return 1;
	//re_decoder decoder(17, 22, 27, callback);
	//sleep(3000);
	//decoder.re_cancel();
	//gpioTerminate();
	
	//const std::string card = "hw:0";
	Control control;
	//control.testFunc(card);


	return 0;
}
