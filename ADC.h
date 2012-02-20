#ifndef ADC_H
#define ADC_H

#include <p18f4520.h>

/** D E F I N I T I O N S ****************************************************/


/** E X T E R N S ************************************************************/
// declare variables accessible by other files.

/** P R O T O T Y P E S ******************************************************/

void ADC_Init(void);
unsigned int ADC_Convert(void);

#endif