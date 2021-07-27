#include <stdint.h>
#include <pic16f887.h>
#include "ADC.h"

// esta funcion es para hacer que lea el valor del ADC
uint8_t read_ADC()
{
    return ADRESH;
}// funcion para leer el valor de adresh
void configuracion_ADC(void)
{
    ADCON0bits.CHS = 0; // CANAL AN0
    
    ADCON0bits.ADCS1 = 1;
    ADCON0bits.ADCS0 = 1; //Frc que trabaja con el oscilador interno
    
    ADCON0bits.ADON = 1; //Activa el modulo ADC
    
    ADCON1bits.ADFM = 0; // justificacion a la izquierda.
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;  //Vss y Vcc
}// Configuracion del ADC con justificacion a la izquierda.