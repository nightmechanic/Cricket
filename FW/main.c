#include <msp430.h> 
#include "cricket.h"
#include "rand.h"
#include "utils.h"

/*
 * main.c
 */
int main(void) {
	unsigned int prand_state;
	unsigned int VLO_count, VLO_50m, max_VLO_50m, max_VLO, wait_time;
	unsigned int play_counter = 0;
	unsigned int loop_counter = 0;
	unsigned int outer_loop_counter = 0;
	unsigned int Vbat = 0;

	program_state prog_state = INIT;

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	// Initialization
	P1REN = 0x1B;                             // Terminate unavailable Port1 pins (P1.0/1/3/4) properly
	P1DIR |= BIT2;                            // P1.2 output
	P1OUT &= ~BIT2;							// P1.2 output 0
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
    // generating the random seed
	prand_state = rand();

	prog_state = START_PLAYING;
	while(1)		//Yes, finally the main loop...
	{

		switch (prog_state)
		{
		case START_PLAYING:
			play_counter = 0;
			P1SEL |= BIT2;                            // P1.2 TA1 options
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
			TACTL = 0x0;
			P1SEL &= ~BIT2;                            // P1.2 back to output (0)
			wait_time = IDLE_TIME;

			while (wait_time > 0){
				if (wait_time >= max_VLO_50m){
					TA0CCR0 = max_VLO;
					wait_time = wait_time - max_VLO_50m;
				} else {
					TA0CCR0 = (wait_time * VLO_50m) ;
					wait_time = 0;
				}
				TA0CCTL0 = CCIE;
				TA0CTL = TACLR;
				TA0CTL = TASSEL_1 | MC_1;                 // ACLK, up mode
				__bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
			}
			TACTL = 0x0;
			prog_state = START_PLAYING;
			break;

		case GOTOSLEEP:
			TACTL = 0x0;
			P1SEL &= ~BIT2;                            // P1.2 back to output (0)
			prand_state = prand(prand_state);
			wait_time = prand_state >> BITS_PRAND;
			wait_time = (wait_time << 2) + MIN_SLEEP;
			while (wait_time > 0){
				if (wait_time >= max_VLO_50m){
					TA0CCR0 = max_VLO;
					wait_time = wait_time - max_VLO_50m;
				} else {
					TA0CCR0 = (wait_time * VLO_50m) ;
					wait_time = 0;
				}
				TA0CCTL0 = CCIE;
				TA0CTL = TACLR;
				TA0CTL = TASSEL_1 | MC_1;                 // ACLK, up mode
				__bis_SR_register(LPM3_bits + GIE);       // Enter LPM3 w/ interrupt
			}
			//Done sleeping
			TACTL = 0x0;
			prog_state = EXITSLEEP;
			break;

		case EXITSLEEP:
			// measure VBAT
			Vbat = measure_Vbat(0);
			if (Vbat < 3056){
				prog_state = LOW_BAT;
				break;
			}
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

// Timer A0 interrupt service routine

#pragma vector=TIMERA0_VECTOR
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
