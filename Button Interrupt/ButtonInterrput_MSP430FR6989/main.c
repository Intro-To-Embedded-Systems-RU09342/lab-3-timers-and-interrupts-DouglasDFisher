#include <msp430.h> 


/**
 *  Button Interrupt MSP430G2553
 */

int main(void)
{
  PM5CTL0 &= ~LOCKLPM5;                     //Disables the GPIO power-on default high-impedance mode

  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1IE |=  BIT3;                            // P1.3 interrupt enabled
  P1IES |= BIT3;                            // P1.3 Hi/lo edge
  P1REN |= BIT3;                            // Enable Pull Up on SW2 (P1.3)
  P1IFG &= ~BIT3;                           // P1.3 IFG cleared
                                            //BIT3 on Port 1 can be used as Switch2

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;                             //Toggles LED
    P1IFG &= ~0xFB;                            //Clears P1.3 IFG
}
