#ifndef ROTARY_ENCODER_HPP
#define ROTARY_ENCODER_HPP

#include <chrono>
#include <iostream>
#include <pigpio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

#define DEBOUNCE_TIME 5
#define LONG_PRESS_TIME 500
#define DOUBLE_PRESS_TIME 250

#define CLOCKWISE 1
#define COUNTERCLOCKWISE 2
#define BUTTON_PRESS 3
#define BUTTON_RELEASE 4
#define DOUBLE_PRESS 5
#define TRIPLE_PRESS 6
#define LONG_PRESS 7

typedef void (*re_decoderCB_t)(int);

class re_decoder
{
	int mygpioA, mygpioB, myButton, levA, levB, levC, last_state, lastGpio;
	uint64_t lastButtonPress, lastButtonRelease, lastButtonEvent;
	pthread_t *pButtonPressFunc;
	uint64_t currentTime();

	re_decoderCB_t mycallback;
	
	void _pulse(int gpio, int level, uint32_t tick);
	
	/* Need a static callback to link with C. */
	static void _pulseEx(int gpio, int level, uint32_t tick, void *user);
	static void* buttonPressFunc_wrapper(void *arg);
	void buttonPressFunc();
	
	public:

		re_decoder(int gpioA, int gpioB, int button, re_decoderCB_t callback);
		void re_cancel(void);
};

#endif
