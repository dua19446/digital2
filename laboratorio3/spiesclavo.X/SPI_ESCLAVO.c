/*
 * File:   SPI_ESCLAVO.c
 * Author: duart
 *
 * Created on 31 de julio de 2021, 04:41 PM
 */

//*****************************************************************************
// bits de configuración
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "S_I_P.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

char var1 = 0;
char var2 = 0;
uint8_t GUARDADO = 0;
uint8_t GUARDADO2 = 0;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
//*****************************************************************************
// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
   if(SSPIF == 1){
        var1 = spiRead();//se guarda en una variable lo que viene del maestro
        spiWrite(GUARDADO);//Se envia el valor del potenciometro 2 al maestro
        var2 = spiRead();//se guarda en una variable lo que viene del maestro
        spiWrite(GUARDADO2);//Se envia el valor del potenciometro 1 al maestro
        SSPIF = 0;
    }
   if (PIR1bits.ADIF == 1)//Interrupcion del ADC 
    {
        if (ADCON0bits.CHS == 1)//si se esta en este canal que haga lo siguiente
        {
            ADCON0bits.CHS = 0;//Se cambia el valor del canal
            GUARDADO = ADRESH;// Se guarda el valor de ADRESH en una variable.
        }                     // para luego realizar la division. 
        else {
            ADCON0bits.CHS = 1;//Se cambia el valor de canal 
            GUARDADO2 = ADRESH;}// Se guarda el valor de ADRESH en el puerto B
                            // para que se muestre en los 8 leds
        __delay_us(50);//tiempo necesario para el cambio de canal 
        PIR1bits.ADIF = 0;//Se apaga el valor de la bandera de interrupcion ADC
    }
}
//*****************************************************************************
// Código Principal
//*****************************************************************************
void main(void) {
    setup();
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
        ADCON0bits.GO = 1; //para empezar de nuevo la ejecucion del ADC
        __delay_ms(100);
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0b00000011; //setea AN0 y AN1
    ANSELH = 0X00;//se establecen los pines como entras y salidas digitales
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;//Se ponen como entradas los primeros pines del puertoA
    
    PORTA = 0X00;
    
    // configuracion del oscilador 
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0; //Se configura el oscilador a una frecuencia de 4MHz
    OSCCONbits.SCS = 1;
    
    // CONFIGURACION DEL ADC
    ADCON0bits.CHS = 0; // CANAL AN0
    
    ADCON0bits.ADCS1 = 1;
    ADCON0bits.ADCS0 = 1; //Frc que trabaja con el oscilador interno
    
    ADCON0bits.ADON = 1; //Activa el modulo ADC
    
    ADCON1bits.ADFM = 0; // justificacion a la izquierda.
    ADCON1bits.VCFG0 = 0;
    ADCON1bits.VCFG1 = 0;  //Vss y Vcc
    
    //INTERRUPCIONES
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    PIR1bits.ADIF = 0;          // BANDERA de interrupcion del ADC
    PIE1bits.ADIE = 1;          // Habilita la interrupcion del ADC
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, 
            SPI_IDLE_2_ACTIVE);// Se pone un SPI esclavo
   
}
