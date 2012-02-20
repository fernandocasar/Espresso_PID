#ifndef _EEPROM_H
#define _EEPROM_H

#include <p18f4520.h>

void EEPROM_Write( unsigned char, unsigned char );
unsigned char EEPROM_Read( unsigned char );

#endif