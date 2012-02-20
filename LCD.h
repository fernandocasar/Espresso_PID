#ifndef __LCD_H
#define __LCD_H

#include <p18f4520.h>
#include <xlcd.h>
#include <usart.h>
#include <delays.h>
#include <string.h>
#include <stdio.h>


extern char data[33];
extern unsigned char counter;
extern unsigned int ADC_result;
extern signed int error;
extern signed int pid_out;
extern signed int aerror;
extern signed int derror;
extern signed int proportional;
extern signed int integral;
extern signed int derivativel;


void refresh_LCD( void );
void Load_Char( void );
void Draw_cup( void ) ;


#endif