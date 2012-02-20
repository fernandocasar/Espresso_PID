/*
 * File:   main.c
 * Author: fernando
 * PID Controller for espresso maker boiler
 * including 16x2 LCD display of temperature
 * Created on January 26, 2012, 9:48 AM
 */

#include "main.h"

#pragma code    // declare executable instructions


void main (void)
{
    // configure internal oscillator
    OSCCON = 0x60;          // IRCFx = 110, 4 MHz
    OSCTUNEbits.PLLEN = 1;  // x4, PLL enabled = 16 MHz
    time_counter_int = 0;
    time_counter_der = 0;

    // configure USART
    OpenUSART(  USART_TX_INT_OFF &
                USART_RX_INT_OFF &
                USART_ASYNCH_MODE&
                USART_EIGHT_BIT  &
                USART_CONT_RX    &
                USART_BRGH_LOW,
                25 );

    // configure external LCD
    OpenXLCD( FOUR_BIT & LINES_5X7 );   
    DelayXLCD();
    Load_Char();
    Delay100TCYx(2);
    WriteCmdXLCD( CURSOR_OFF & BLINK_OFF );
    Delay100TCYx(2);
    WriteCmdXLCD( INCREMENT );

    //Initializations
    Timer0_Init();
    pid_init();

    //PORT initialization
    TRISB = 0b10001111;
    TRISA = 0b11111111;
    TRIS_OUTPUT = 0;
    cursor = 0;

    //INT0 initialization
    INT0_Init();


    while( cursor < 33 )
    {
        data[cursor] = 0x20;
        cursor++;
    }
    ADC_Init();

    counter = 0;
    cursor=0;
    ADC_result = ADC_Convert();
    
    Draw_cup();

    while(1)
    {
        
        //while( !DataRdyUSART() );  //wait for data
        //data[cursor] = ReadUSART();      //read data
        //printf( "%c", data[cursor] );
        //WriteDataXLCD(data[cursor]);     //write to LCD
        

        //refresh_LCD();
        //LATD = cursor;
        cursor++;

        if( cursor == 26 )
            cursor = 0;

    }

    CloseUSART();

    return;
}