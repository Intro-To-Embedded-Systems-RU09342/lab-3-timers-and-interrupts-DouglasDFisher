/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * --/COPYRIGHT--*/
//******************************************************************************

/*
 * Timer A Blink
 * Author: Douglas Fisher
 */

#include <msp430.h> //msp identifiers

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; //stop watchdog timer

    P1DIR |= 0x01;                            //Set P1.0 as an output
    P1DIR |= 0x40;                            //Set P1.7 as an output
    TA0CTL |= TASSEL_2;                       //select SMCLK as clk src
    TA0CTL |= ID_3;                           //set clk division to 8
    TA0CTL |= MC_1;                           //set to up mode
    TA0CCR0 = 0xC468;                         //set value timer will reset at
    TA0CTL |= TAIE;                           //enable timer interrupts
    TA0IV = 0x00;                             //resets interrupt vector
    TA1CTL |= TASSEL_2;                       //select SMCLK as clk src
    TA1CTL |= ID_3;                           //set clk division to 8
    TA1CTL |= MC_1;                           //set to up mode
    TA1CCR0 = 0x3234;                         //set value timer will reset at; defines blink period
    TA1CTL |= TAIE;                           //enable timer interrupts
    TA1IV = 0x00;                             //resets interrupt vector

    __bis_SR_register(LPM0_bits + GIE);       //enter low power mode and enable interrupt

    while(1);
}

//interrupt vector for timerA0
void __attribute__((interrupt(TIMER0_A1_VECTOR))) Timer_A0 (void)
{
    if(TA0IV == 0x0A)       //Interrupt caused by an verflow
        P1OUT ^= 0x01;      //Toggle P1.0
}

//interrupt vector for timerA1
void __attribute__((interrupt(TIMER1_A1_VECTOR))) Timer_A1 (void)
{
    if(TA1IV == 0x0A)       //Interrupt caused by an overflow
        P1OUT ^= 0x40;      // Toggle P1.7
}
