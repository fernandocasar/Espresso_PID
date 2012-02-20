#ifndef _MAIN_H
#define _MAIN_H

/** C O N F I G U R A T I O N   B I T S ******************************/

#pragma config OSC = INTIO67, FCMEN = OFF, IESO = OFF                       // CONFIG1H
#pragma config PWRT = OFF, BOREN = SBORDIS, BORV = 3                        // CONFIG2L
#pragma config WDT = OFF, WDTPS = 32768                                     // CONFIG2H
#pragma config MCLRE = OFF, LPT1OSC = OFF, PBADEN = ON, CCP2MX = PORTC       // CONFIG3H
#pragma config STVREN = ON, LVP = OFF, XINST = OFF                          // CONFIG4L
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF                   // CONFIG5L
#pragma config CPB = OFF, CPD = OFF                                         // CONFIG5H
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF               // CONFIG6L
#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF                           // CONFIG6H
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF           // CONFIG7L
#pragma config EBTRB = OFF                                                  // CONFIG7H


/** I N C L U D E S **************************************************/
#include <p18f4520.h>
#include <delays.h>
#include <usart.h>
#include <string.h>
#include <stdio.h>
#include <xlcd.h>
#include "LCD.h"
#include "ADC.h"
#include "interrupts.h"
#include "EEPROM.h"



//==================================
// Declare EEPROM data
// Note that EEPROM is mapped to program memory address 0xF00000
/*
#pragma romdata dataEEPROM=0xF00000
rom unsigned char FirstByte = 0x55;
rom unsigned char SecondByte;
rom unsigned char FirstArray[] = {0x00, 0x01, 0x02};
rom unsigned char SecondArray[3];
*/


/** V A R I A B L E S *************************************************/
#pragma udata // declare statically allocated uninitialized variables

char data[33];
unsigned char counter;
//unsigned char time_counter;
unsigned int ADC_result;
static unsigned char cursor;

signed int error;
signed int aerror;
signed int derror;
signed int perror;
unsigned char kp;
unsigned char ki;
unsigned char kd;
signed int proportional;
signed int integral;
signed int derivative;
signed int pid_out;
unsigned char deriv_count;
unsigned char integral_count;


/** D E C L A R A T I O N S *******************************************/
// declare constant data in program memory starting at address 0x180

#endif