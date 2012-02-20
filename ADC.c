#include "ADC.h"


void ADC_Init(void)
{ // initialize the Analog-To-Digital converter.
    
    ADCON1 = 0B00001101;
    ADCON2 = 0b10111001;
    ADCON0 = 0b00000101;

}

unsigned int ADC_Convert(void)
{ // start an ADC conversion and return the 8 most-significant bits of the result
    unsigned int result;
    ADCON0bits.GO_DONE = 1;             // start conversion
    while (ADCON0bits.GO_DONE == 1);    // wait for it to complete

    result = ADRESL;
    result += ADRESH*256;
    result = result*1.4663;
    
    return result;                      // return high byte of result
}
