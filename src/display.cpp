#include "display.h"

ST7789_TFT myTFT;

Display::Display() {
	Display::setupHWSPI();
	Display::helloWorld();
	Display::endTest();
}

uint8_t Display::setupHWSPI() {
	if (!bcm2835_init()){
		std::cout << "Error 1201 Problem with BCM2835 library" << std::endl;
		return 2;
	}

	int8_t RST_TFT  = 24;
	int8_t DC_TFT   = 25;
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT);

	uint8_t OFFSET_COL = 0;
	uint8_t OFFSET_ROW = 0;
	uint16_t TFT_WIDTH = 240;
	uint16_t TFT_HEIGHT = 320;
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW, TFT_WIDTH, TFT_HEIGHT);

	uint32_t SCLK_FREQ = 8000000;
	uint8_t SPI_CE_PIN = 0;
	if (myTFT.TFTInitSPI(SCLK_FREQ, SPI_CE_PIN) != rpiDisplay_Success) {
		bcm2835_close();
		return 3;
	}
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_90);
	delayMilliSecRDL(100);
	return 0;
}

void Display::helloWorld(void) {
	std::cout << "Hello world!" << std::endl;
	myTFT.fillScreen(RDLC_BLACK);
	myTFT.setCursor(30, 60);
	myTFT.setTextColor(RDLC_GREEN, RDLC_BLACK);
	myTFT.setFont(font_arialBold);
	myTFT.print("Hello world!");
	myTFT.drawRoundRect(10, 10, 210, 225, 15, RDLC_RED);
	delayMilliSecRDL(7000);
}

void Display::endTest(void) {
	myTFT.fillScreen(RDLC_BLACK);
	myTFT.TFTPowerDown();
	bcm2835_close();
	std::cout << "Test end!" << std::endl;
}
