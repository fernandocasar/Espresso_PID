#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <p18f4520.h>
#include <string.h>
#include <usart.h>
#include "LCD.h"
#include "ADC.h"
#include "PID.h"


/** D E F I N I T I O N S ****************************************************/
static unsigned char time_counter_int;
static unsigned char time_counter_der;

static unsigned char cycle_counter = 255;


/** E X T E R N S ************************************************************/
// declare variables accessible by other files.
//extern unsigned char time_counter;
extern unsigned int ADC_result;
extern unsigned char integral_count;
extern unsigned char deriv_count;

extern signed int proportional;
extern signed int integral;
extern signed int derivative;



/** P R O T O T Y P E S ******************************************************/
void INT0_Init(void);
void Timer0_Init(void);
void InterruptServiceHigh(void);
void InterruptServiceLow(void);


#endif