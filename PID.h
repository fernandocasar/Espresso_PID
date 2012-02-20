#ifndef PID_H
#define PID_H

#include <p18f4520.h>
#include "ADC.h"

#define STEAM PORTAbits.RA4
#define OUTPUT LATCbits.LATC1
#define TRIS_OUTPUT TRISCbits.RC1

#define AERRMAX 200
#define AERRMIN -200
#define REF_WATER 450     //93°C x 10 for resolution sake using int
#define REF_STEAM 1200    //120°C x 10 for resolution sake using int

extern signed int error;
extern signed int aerror;
extern signed int derror;
extern signed int perror;
extern unsigned char kp;
extern unsigned char ki;
extern unsigned char kd;
extern signed int proportional;
extern signed int integral;
extern signed int derivative;
extern signed int pid_out;
extern unsigned char deriv_count;
extern unsigned char integral_count;
extern unsigned int ADC_result;


//Function Prototypes
void pid_init(void);
signed int get_error( void );
signed int get_aerror( void );
signed int get_derror( void );
signed int calc_pterm( void );
signed int calc_iterm( void );
signed int calc_dterm( void );
signed int calc_output( void );


#endif