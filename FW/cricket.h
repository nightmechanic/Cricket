/*
cricket.h file for the cricket project
The MIT License (MIT)

Copyright (c) 2016 Ran Katz (Nightmechanic)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

//#include <msp430.h>

//HW platform:

#if defined (__MSP430G2230__)   //cricket board
#define PWM_PIN BIT2
#define LED_PIN BIT7
#elif defined (__MSP430G2553__) //lauchpad
#define PWM_PIN BIT2
#define LED_PIN BIT6
#endif  //cricket vs. launchpad

//main consts:
const unsigned int PLAY_CYCLE = 	500; //in 1 MHz cycles
const unsigned int PLAY_DC = 		250; //in 1MHz cycles
const unsigned int PLAY_PERIOD = 	10;  //in play cycles
const unsigned int PAUSE_PERIOD =	10;  //in play cycles
const unsigned int PLAY_LOOPS =		100;
const unsigned int IDLE_TIME =		20; //in 50msec units
const unsigned int OUTER_LOOPS =	2; // number of cricket chirps
const unsigned int MIN_SLEEP =		60*20; //in 50msec units (60 seconds)

//Battery measurement:
const unsigned int ADCx4_1v5_2v8V  =    3822; //measure_Vbat result when ref=1.5 and vbat = 2.8
const unsigned int ADCx4_1v5_1v0V =     2731;
const unsigned int ADCx4_1v5_0v1V =     273;
const unsigned int ADCx4_2v5_1v0V =     1638;
const unsigned int ADCx4_2v5_0v1V =     164;

const unsigned int LED_on_time =        10;  //in 50msec units
const unsigned int LED_off_time =       10;  //in 50msec units
const unsigned int LED_gap_time =       20;  //in 50msec units

typedef enum {
	INIT,
	START_PLAYING,
	PLAYING,
	PAUSE,
	IDLE,
	GOTOSLEEP,
	EXITSLEEP,
	LOW_BAT
} program_state;

//Functions
void display_Vbat(void);
void ACLK_50m_sleep(unsigned int sleep_time);

