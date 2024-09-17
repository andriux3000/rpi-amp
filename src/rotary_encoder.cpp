#include "rotary_encoder.h"

void* re_decoder::buttonPressFunc_wrapper(void* arg) {
	reinterpret_cast<re_decoder*>(arg)->buttonPressFunc();
	return 0;
}

void re_decoder::buttonPressFunc() {
	usleep(DOUBLE_PRESS_TIME*1000+20);
	(mycallback)(BUTTON_PRESS);
}

void re_decoder::_pulse(int gpio, int level, uint32_t tick)
{
	//Button section
	if (gpio == myButton && currentTime()-lastButtonEvent > DEBOUNCE_TIME) {
		if (level == 0) {
			if (pButtonPressFunc) {
				gpioStopThread(pButtonPressFunc);
				pButtonPressFunc = NULL;
			}
			lastButtonPress = currentTime();
		}
		else if (level == 1 && (currentTime()-lastButtonRelease > DEBOUNCE_TIME)){
			if (currentTime()-lastButtonPress > LONG_PRESS_TIME) {
				(mycallback)(LONG_PRESS);
			}
			else if (currentTime()-lastButtonRelease < DOUBLE_PRESS_TIME) {
				(mycallback)(DOUBLE_PRESS);
			}
			else {
				pButtonPressFunc = gpioStartThread(&buttonPressFunc_wrapper, this);
			}
			lastButtonRelease = currentTime();
		}
		lastButtonEvent = currentTime();
	}

	//Rotary encoder section
	if (gpio == mygpioA) {
		levA = level;
	} 
	else if (gpio == mygpioB) {
		levB = level;
	}

	levC = levA ^ levB;
	
	int new_state = levA * 4 + levB * 2 + levC * 1;
	int delta = (new_state - last_state) % 4;
	
	if (gpio != lastGpio) {
		lastGpio = gpio;
		if (levC == 1) {
			if (delta == 3 || delta == -1) {
				(mycallback)(CLOCKWISE);
			}
			else if (delta == -3 || delta == 1) {
				(mycallback)(COUNTERCLOCKWISE);
			}
		}
	}
	last_state = new_state;
}

void re_decoder::_pulseEx(int gpio, int level, uint32_t tick, void *user)
{
	/*
	   Need a static callback to link with C.
	*/
	
	re_decoder *mySelf = (re_decoder *) user;
	
	mySelf->_pulse(gpio, level, tick); /* Call the instance callback. */
}

uint64_t re_decoder::currentTime() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

re_decoder::re_decoder(int gpioA, int gpioB, int button, re_decoderCB_t callback)
{
	lastButtonPress = currentTime();
	lastButtonRelease = currentTime();
	lastButtonEvent = currentTime();

	pButtonPressFunc = NULL;

	mygpioA = gpioA;
	mygpioB = gpioB;
	myButton = button;
	
	mycallback = callback;
	
	levA=0;
	levB=0;
	levC=0;
	
	lastGpio = -1;
	
	last_state = 0;
	
	gpioSetMode(gpioA, PI_INPUT);
	gpioSetMode(gpioB, PI_INPUT);
	gpioSetMode(button, PI_INPUT);
	
	/* pull up is needed as encoder common is grounded */
	
	gpioSetPullUpDown(gpioA, PI_PUD_UP);
	gpioSetPullUpDown(gpioB, PI_PUD_UP);
	gpioSetPullUpDown(button, PI_PUD_UP);
	
	/* monitor encoder level changes */
	
	gpioSetAlertFuncEx(gpioA, _pulseEx, this);
	gpioSetAlertFuncEx(gpioB, _pulseEx, this);
	gpioSetAlertFuncEx(button, _pulseEx, this);
}

void re_decoder::re_cancel(void)
{
	gpioSetAlertFuncEx(mygpioA, 0, this);
	gpioSetAlertFuncEx(mygpioB, 0, this);
	gpioSetAlertFuncEx(myButton, 0, this);
}

