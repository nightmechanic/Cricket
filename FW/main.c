/*
Main file for MSP430G2230 based annoying cricket project
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


#include <msp430.h> 
#include "cricket.h"
#include "rand.h"
#include "utils.h"

unsigned int VLO_50m, max_VLO_50m, max_VLO;

/*
 * main.c
 */
int main(void) {
	unsigned int prand_state;
	unsigned int VLO_count, wait_time;
	unsigned int play_counter = 0;
	unsigned int loop_counter = 0;
	unsigned int outer_loop_counter = 0;
//	unsigned int Vbat = 0;

	program_state prog_state = INIT;

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	// Initialization
	P1REN = 0x1B;                             // Terminate unavailable Port1 pins (P1.0/1/3/4) properly

	P1DIR |= (LED_PIN | PWM_PIN);                            // Set functional pins as output output
	P1OUT &= ~(LED_PIN | PWM_PIN);							// Set functional pins to be 0


	// clocks
	 BCSCTL3 |= LFXT1S_2;                      // Select VLO as low freq clock

	if (CALBC1_1MHZ != 0xFF)					// If calibration constant are valid erased
	  {
		DCOCTL = 0;                               // Select lowest DCOx and MODx settings
		BCSCTL1 = CALBC1_1MHZ;                    // Set range
		DCOCTL = CALDCO_1MHZ;                     // Set DCO step + modulation
	  }

	// calibrate VLO
	VLO_count = calibrate_VLO();
	VLO_50m = (unsigned int)50000 / VLO_count;  	//number of VLO cycles in a 50msec period
	max_VLO_50m = (unsigned int)65000 / VLO_50m;	//longest time TA can count
	max_VLO = max_VLO_50m * VLO_50m;

	// generate the random seed
	prand_state = rand();

	display_Vbat();

	prog_state = GOTOSLEEP;
	while(1)		//Yes, finally the main loop...
	{

		switch (prog_state)
		{
		case START_PLAYING:
			play_counter = 0;
			P1SEL |= PWM_PIN;                            // P1.2 TA1 options
			TA0CCR0 = PLAY_CYCLE-1;                   // PWM Period/2
			TA0CCTL0 = CCIE;						// enable interrupt
			TA0CCTL1 = OUTMOD_3;                      // TA0CCR1 set/reset
			TA0CCR1 = PLAY_DC;                             // TA0CCR1 PWM duty cycle
			TA0CTL = TACLR;
			TA0CTL = TASSEL_2 | MC_1;                 // SMCLK, up mode
			prog_state = PLAYING;
			 __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
			break;

		case PLAYING:
			play_counter++;
			if (play_counter >= PLAY_PERIOD)
			{
				play_counter = 0;
				TA0CCTL1 =  OUTMOD_0;                      // TA0CCR1 OUTx (OUT=0)
				loop_counter++;
				prog_state = PAUSE;
			}
			if (loop_counter >= PLAY_LOOPS)
			{
				loop_counter = 0;
				outer_loop_counter++;
				if (outer_loop_counter >= OUTER_LOOPS){
					outer_loop_counter = 0;
					prog_state = GOTOSLEEP;
				} else {
					prog_state = IDLE;
				}
			} else {
				__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
			}
			break;

		case PAUSE:
			play_counter++;
			if (play_counter >= PAUSE_PERIOD)
			{
				play_counter = 0;
				TA0CCTL1 = OUTMOD_3;                      // PWM out
				prog_state = PLAYING;
			}
			__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
			break;

		case IDLE:
			TA0CTL = 0x0;
			P1SEL &= ~PWM_PIN;                            // P1.2 back to output (0)
			wait_time = IDLE_TIME;
			ACLK_50m_sleep(wait_time);
			TA0CTL = 0x0;
			prog_state = START_PLAYING;
			break;

		case GOTOSLEEP:
			TA0CTL = 0x0;
			P1SEL &= ~PWM_PIN;                            // P1.2 back to output (0)
			prand_state = prand(prand_state);
			wait_time = prand_state >> BITS_PRAND;
			wait_time = (wait_time << 2) + MIN_SLEEP;
			ACLK_50m_sleep(wait_time);
			//Done sleeping
			TA0CTL = 0x0;
			prog_state = EXITSLEEP;
			break;

		case EXITSLEEP:
			// measure VBAT
//			Vbat = measure_Vbat(0);
//			if (Vbat < 3056){
//				prog_state = LOW_BAT;
//				break;
//			}

			// recal VLO
			VLO_count = calibrate_VLO();
			VLO_50m = (unsigned int)50000 / VLO_count;  	//number of VLO cycles in a 50msec period
			max_VLO_50m = (unsigned int)65000 / VLO_50m;	//longest time TA can count
			max_VLO = max_VLO_50m * VLO_50m;
			// ready to go
			prog_state = START_PLAYING;
			break;

		case LOW_BAT:
			__bis_SR_register(LPM4_bits);       // All done, please replace battery
			break;

		default:
			break;

		} // switch

	} //main loop

}

void display_Vbat(void){
	unsigned int Vbat;
	unsigned int Vref = 0;
	unsigned int Vbat_1V, Vbat_0v1V;
	unsigned char V_int = 0;
	unsigned char V_frac = 0;

	Vbat = measure_Vbat(Vref);
	Vbat_1V = ADCx4_1v5_1v0V;
	Vbat_0v1V =  ADCx4_1v5_0v1V;

	if (Vbat >  ADCx4_1v5_2v8V) {
		Vref=1;
		Vbat = measure_Vbat(Vref);
		Vbat_1V = ADCx4_2v5_1v0V;
		Vbat_0v1V =  ADCx4_2v5_0v1V;
	}

	Vbat = 2 * Vbat;

	V_int = (unsigned char)(Vbat / Vbat_1V) ;

	Vbat = Vbat - (V_int * Vbat_1V);
	if (Vbat > 0) {
		Vbat = Vbat + (Vbat_0v1V >> 1); // for more accurate rounding
		V_frac = (unsigned char)(Vbat / Vbat_0v1V);
		if (V_frac >= 10){
			V_frac = 0;
			V_int = V_int + 1;
		}
	}

	while (V_int > 0){
		P1OUT |= LED_PIN;		// led on
		ACLK_50m_sleep(LED_on_time);
		P1OUT &= ~LED_PIN;		//led off
		ACLK_50m_sleep(LED_off_time);
		V_int--;
	}

	ACLK_50m_sleep(LED_off_time); //gap between integer and fractional blonks

	while (V_frac > 0){
			P1OUT |= LED_PIN;		// led on
			ACLK_50m_sleep(LED_on_time);
			P1OUT &= ~LED_PIN;		//led off
			ACLK_50m_sleep(LED_off_time);
			V_frac--;
		}
	return;
}

void ACLK_50m_sleep(unsigned int sleep_time){
	//halt timer
	TA0CTL = 0x0;
	while (sleep_time > 0){
		if (sleep_time >= max_VLO_50m){
			TA0CCR0 = max_VLO;
			sleep_time =sleep_time - max_VLO_50m;
		} else {
			TA0CCR0 = (sleep_time * VLO_50m) ;
			sleep_time = 0;
		}
		TA0CCTL0 = CCIE;
		TA0CTL = TACLR;
		TA0CTL = TASSEL_1 | MC_1;                 // ACLK, up mode
		__bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
	}

	return;
}
// Timer A0 interrupt service routine

//#pragma vector=TIMERA0_VECTOR
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A_ISR (void)
{
	 __bic_SR_register_on_exit(LPM3_bits);                   // Clear LPM3 bits from 0(SR)
}

// ADC10 interrupt service routine

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)

{
	 __bic_SR_register_on_exit(LPM0_bits);                   // Clear LPM0 bits from 0(SR)
}
