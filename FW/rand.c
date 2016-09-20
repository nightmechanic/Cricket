/*
Based on: https://github.com/0/msp430-rng by Dmitri Iouchtchenko
Authors license:
The MIT License (MIT)

Copyright (c) 2011, 2015 Dmitri Iouchtchenko

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

Modified for the cricket project by Nightmechanic
*/

#include <msp430.h>

#include "rand.h"



/**
 * Random number generator.
 *
 * It is recommended that this function is run during setup, before any clocks
 * or timers have been set and before interrupts have been enabled. While it
 * does restore all used control registers to their original values, it also
 * expects that nothing interesting will happen when it modifies them.
 *
 * Algorithm from TI SLAA338:
 * http://www.ti.com/sc/docs/psheets/abstract/apps/slaa338.htm
 *
 * @return 16 random bits generated from a hardware source.
 */



unsigned int rand(void) {
	int i, j;
	unsigned int result = 0;

	/* Save state */
	unsigned int BCSCTL3_old = BCSCTL3;
	unsigned int TACCTL0_old = TA0CCTL0;
	unsigned int TACTL_old = TA0CTL;

	/* Halt timer */
	TA0CTL = 0x0;

	/* Set up timer */
	BCSCTL3 = (~LFXT1S_3 & BCSCTL3) | LFXT1S_2; // Source ACLK from VLO
	TA0CCTL0 = CAP | CM_1 | CCIS_1 | CCIE;            // Capture mode, positive edge
	TA0CTL = TASSEL_2 | MC_2;                  // SMCLK, continuous up

	/* Generate bits */
	for (i = 16; i > 0; i--) {
		unsigned int ones = 0;

		for (j = 5; j > 0; j--) {

			__bis_SR_register(LPM0_bits + GIE);  // Wait for interrupt

			if (1 & TA0CCR0)                   // If LSb set, count it
				ones++;
		}

		result >>= 1;                         // Save previous bits

		if (ones >= 3)                        // Best out of 5
			result |= 0x8000;                 // Set MSb
	}

	/* Restore state */
	BCSCTL3 = BCSCTL3_old;
	TA0CCTL0 = TACCTL0_old;
	TA0CTL = TACTL_old;

	return result;
}

/**
 * Pseudo-random number generator.
 *
 * Implemented by a 16-bit linear congruential generator.
 * NOTE: Only treat the MSB of the return value as random.
 *
 * @param state Previous state of the generator.
 * @return Next state of the generator.
 */
unsigned int prand(unsigned int state) {
	/* LCG constants */
	static const unsigned int M = 49381;                               // Multiplier
	static const unsigned int I = 8643;                                // Increment

	return M * state + I;                     // Generate the next state of the LCG
}
