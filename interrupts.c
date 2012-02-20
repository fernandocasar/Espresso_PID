#include "interrupts.h"


void Timer0_Init(void)
{
    RCONbits.IPEN = 1;              // Enable interrupt priority

    // Set up Interrupts for timer
    INTCONbits.TMR0IF = 0;          // clear roll-over interrupt flag
    INTCON2bits.TMR0IP = 0;         // Timer0 is low priority interrupt
    INTCONbits.TMR0IE = 0;          // disable the Timer0 interrupt.

    // Set up timer itself
    T0CON = 0b00000011;             // prescale 1:4 - about 1 second maximum delay.
    TMR0H = 0;                      // clear timer - always write upper byte first
    TMR0L = 0;
    T0CONbits.TMR0ON = 0;           // don't start timer
    INTCONbits.GIEL = 0;            // disable all low priority interrupts
}

void INT0_Init(void)
{
    INTCON2bits.RBPU = 0;		// enable PORTB internal pullups
    INTCON2bits.INTEDG0 = 1;    // interrupt on falling edge of INT0 (switch pressed)
    INTCONbits.INT0IF = 0;      // ensure flag is cleared
    INTCONbits.INT0IE = 1;      // enable INT0 interrupt
    INTCONbits.GIEH = 1;            // enable all high priority interrupts
}



#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh (void)
{
  _asm
    goto InterruptServiceHigh //jump to interrupt routine
  _endasm
}

//----------------------------------------------------------------------------
// Low priority interrupt vector

#pragma code InterruptVectorLow = 0x18
void InterruptVectorLow (void)
{
  _asm
    goto InterruptServiceLow //jump to interrupt routine
  _endasm
}

// -------------------- Iterrupt Service Routines --------------------------
#pragma interrupt InterruptServiceHigh  // "interrupt" pragma also for high priority
void InterruptServiceHigh(void)
{
    // Check to see what caused the interrupt
    // (Necessary when more than 1 interrupt at a priority level)

    // Check for INT0 interrupt
    if (INTCONbits.INT0IF)
    {

        // clear (reset) flag
        INTCONbits.INT0IF = 0;

        //insert code here
        if( cycle_counter % 64 == 0 )
        {
            refresh_LCD();
            calc_output();
        }

        time_counter_int++;
        if( time_counter_int >= integral_count)
        {
            time_counter_int = 0;
            get_aerror();
        }

        time_counter_der++;
        if( time_counter_der >= deriv_count)
        {
            time_counter_der = 0;
            get_derror();
        }


        if( cycle_counter == 0)
        {
            printf("interrupt\n");
            printf("P: %i\nI: %i\nD: %i\nPID: %i\n",proportional, integral, derivative, pid_out);
            cycle_counter = 255;   
        }

        if( cycle_counter < pid_out)
        {
            OUTPUT = 1;
        }
        else
        {
            OUTPUT = 0;
        }
        cycle_counter--;
    }

    // Check for another interrupt, examples:
    // if (PIR1bits.TMR1IF)     // Timer 1
    // if (PIR1bits.ADIF)       // ADC

}  // return from high-priority interrupt

#pragma interruptlow InterruptServiceLow// "interruptlow" pragma for low priority
void InterruptServiceLow(void)
{
    // Check to see what caused the interrupt
    // (Necessary when more than 1 interrupt at a priority level)

    // Check for Timer0 Interrupt
    if  (INTCONbits.TMR0IF)
    {
        INTCONbits.TMR0IF = 0;          // clear (reset) flag   
        

    }

    // Check for another interrupt, examples:
    // if (PIR1bits.TMR1IF)     // Timer 1
    // if (PIR1bits.ADIF)       // ADC
}

///use parts of this routine when needed

            /*
            

            //error = get_error();

            //calc_output();

            //refresh_LCD();

            //printf("P: %i\nI: %i\nD: %i\nPID: %i\n",proportional, integral, derivative, pid_out);

            time_counter_int++;
            if( time_counter_int >= integral_count)
            {
                time_counter_int = 0;
                get_aerror();

                time_counter_der++;
                if( time_counter_der >= deriv_count)
                {
                    time_counter_der = 0;
                    get_derror();
                }


            }

            */