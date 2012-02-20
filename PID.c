#include "PID.h"

void pid_init( void )
{
    error = 0;
    aerror = 0;
    derror = 0;
    perror = 0;
    kp = 50;
    ki = 3;
    kd = 3;
    proportional = 0;
    integral = 0;
    derivative = 0;
    pid_out = 0;
    integral_count = 100;
    deriv_count = 100;

}

signed int get_error( void )
{

    ADC_result = ADC_Convert();
    if( STEAM )
    {
        error = REF_STEAM - ADC_result;
    }
    else
    {
        error = REF_WATER - ADC_result;
    }


    return error;
}
signed int get_aerror( void )
{
    aerror += get_error();
    if( aerror < AERRMIN )
        aerror = AERRMIN;
    if( aerror > AERRMAX )
        aerror = AERRMAX;
    return aerror;
}

signed int get_derror( void )
{
    derror = get_error()-perror;
    perror = error;
    return derror;
}

signed int calc_pterm( void )
{
    proportional = 0.05 * kp * error;
    return proportional;
}

signed int calc_iterm( void )
{
    integral = 0.05 * ki * aerror;
    return integral;
}

signed int calc_dterm( void )
{
    derivative = 0.05 * kd * derror;
    return derivative;
}

signed int calc_output( void )
{
    error = get_error();

    pid_out = calc_pterm() + calc_iterm() + calc_dterm();
    
    return pid_out;
}
