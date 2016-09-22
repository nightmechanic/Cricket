/*
utils.c file for MSP430G2230 based annoying cricket project
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

unsigned int calibrate_VLO(void)
{
	unsigned int j;
	unsigned int count = 0;
	unsigned int cap_cnt1 = 0;                           // First capture counter
	unsigned int cap_cnt2 = 0;                           // Second capture counter
	unsigned int BCSCTL1_old = BCSCTL1;
	unsigned int phase = 0;


	BCSCTL1 |= DIVA_3;						// divide VLO by 8

	/* Halt timer */
	TA0CTL = 0x0;

	/* Set up timer */
	TA0CCTL0 = CAP | CM_1 | CCIS_1 | CCIE;            // Capture mode, positive edge
	TA0CTL = TASSEL_2 | MC_2;                  // SMCLK, continuous up

	for (j = 16; j > 0; j--) {

		__bis_SR_register(LPM0_bits + GIE);  // Wait for interrupt

		if (phase == 0) {
			cap_cnt1 = TA0CCR0;
			phase = 1;
		} else {
			cap_cnt2 = TA0CCR0;
			count += (cap_cnt2-cap_cnt1);
			phase = 0;
		}
	}



	TA0CTL = 0x0;
	BCSCTL1 = BCSCTL1_old;
	if ((count & 0x003F) > 0x20){
		count >>= 6;
		count += 1;
	} else {
		count >>= 6;
	}

	return count;
}

unsigned int measure_Vbat(unsigned char ADC_REF_2_5V)
{
	unsigned int j;
	unsigned int Vbat = 0;
	ADC10CTL1 = INCH_11;                      // AVcc/2

	if (ADC_REF_2_5V == 0){						// REF 1.5V
		ADC10CTL0 = SREF_1 | ADC10SHT_2 | REFON | ADC10ON | ADC10IE;
	}
	else{										// REF 2.5V
		ADC10CTL0 = SREF_1 | ADC10SHT_2 | REF2_5V | REFON | ADC10ON | ADC10IE;
	}
	TA0CCR0 = 30;                             // Delay to allow Ref to settle
	TA0CCTL0 |= CCIE;                         // Compare-mode interrupt.
	TA0CTL = TACLR;
	TA0CTL = TASSEL_2 | MC_1;                 // TACLK = SMCLK, Up mode.
	__bis_SR_register(LPM0_bits + GIE); 		 // Wait for interrupt (ref to settle)
	TA0CTL = 0;

	for (j = 4; j > 0; j--) {
		ADC10CTL0 |= ENC | ADC10SC;
		__bis_SR_register(LPM0_bits + GIE); 		 // Wait for interrupt (ADC done)
		Vbat += ADC10MEM;

	}
	ADC10CTL0 = 0;
	return Vbat;
}
