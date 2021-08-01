//*****************************************************************************
/*
 * File:   main.c
 * Author: Pablo
 * Ejemplo de implementación de la comunicación SPI 
 * Código Maestro
 * Created on 10 de febrero de 2020, 03:32 PM
 */
//*****************************************************************************
//*****************************************************************************
// Palabra de configuración
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
#include "SPI.h"
#include <stdio.h>// Libreria para poder usar printf junto a la funcion putch.
#include <stdlib.h>
#include <string.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

uint8_t VOLTAJE1;
uint8_t VOLTAJE2;
char centenas; //Paraa que el valor este en valores ASCII
char decenas;
char unidades;
uint8_t CENTENA;
uint8_t DECENA;
uint8_t UNIDAD;
char v1[20];
char v2[20];
char v3[20];

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
void division(uint8_t variable);

//*****************************************************************************
// Código Principal
//*****************************************************************************
void main(void) {
    setup();
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
       PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
     
       spiWrite(0X0A);
       VOLTAJE1 = spiRead();
       __delay_ms(1);
       spiWrite(0X0A);
       VOLTAJE2 = spiRead();
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
      
    division(VOLTAJE1);
       if(TXIF == 1){
    __delay_ms(50);
     printf("VALOR DE POT1: \r");//SE ENVIA CANDENA DE CARACTERES
     __delay_ms(50);
    if(TXIF == 1){
        TXREG = centenas; 
       }
    __delay_ms(50);
    if(TXIF == 1){// SE ENVIA UN PUNTO 
        TXREG = 46; 
       }
    __delay_ms(50);
    if(TXIF == 1){
        TXREG = decenas; 
       }
    __delay_ms(50);
    if(TXIF == 1){
        TXREG = unidades; 
       }
    __delay_ms(50);
    if(TXIF == 1){// EN ENVIA UN SALTO 
        TXREG = 13; 
       }
    __delay_ms(50);
    }    
     
    division(VOLTAJE2);
    if(TXIF == 1){
    __delay_ms(50);
     printf("VALOR DE POT2: \r");//SE ENVIA CANDENA DE CARACTERES
     __delay_ms(50);    
    if(TXIF == 1){
        TXREG = centenas; 
       }
    __delay_ms(50);
    if(TXIF == 1){  // SE ENVIA UN PUNTO 
        TXREG = 46; 
       }
    __delay_ms(50);
    if(TXIF == 1){
        TXREG = decenas; 
       }
    __delay_ms(50);
    if(TXIF == 1){
        TXREG = unidades; 
       }
    __delay_ms(50);
    if(TXIF == 1){ // EN ENVIA UN SALTO 
        TXREG = 13; 
    }
    __delay_ms(50);
    }     
       
    while (RCIF == 0);
    CENTENA = RCREG - 48;
    while (RCIF == 0);
    DECENA = RCREG - 48;        
    while (RCIF == 0);
    UNIDAD = RCREG - 48; 
    sprintf(v1, "%d", CENTENA);
    sprintf(v2, "%d", DECENA);
    sprintf(v3, "%d", UNIDAD);
    strcat(v1, v2);
    strcat(v1, v3);
    int com = atoi(v1);
    PORTB = com;
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISC2 = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    
    // configuracion del oscilador 
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0; //Se configura el oscilador a una frecuencia de 4MHz
    OSCCONbits.SCS = 1;
    
    //Configuracion TX y RX 
    TXSTAbits.BRGH = 1;  // Para alta velocidad.
    BAUDCTLbits.BRG16 = 0; // Se usan los 16 bits
    
    TXSTAbits.SYNC = 0; // transmision asincrona
    RCSTAbits.SPEN = 1; // Se enciende el modulo 
    RCSTAbits.CREN = 1; // Se abilita la recepcion 
    
    TXSTAbits.TXEN = 1; // Se abilita la transmision 
    
    RCSTAbits.RX9 = 0; // Se determina que no se quieren 9 bits
    
    SPBRG = 25; 
    SPBRGH = 1;
    
    PORTCbits.RC2 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}
void division(uint8_t variable){
    uint8_t val;
    val = variable;              //Se guarda en valor la variable que entra
    centenas = ((val * 1.963)/100) ;       //SE OBTIENE EL VALOR DE CENTRENAS
    val = (val - (centenas*100));
    decenas = (val/10);         //SE OBTIENE EL VALOR DE DECENAS
    val = (val - (decenas*10));
    unidades = (val);         //SE OBTIENE EL VALOR DE UNIDADES
    
    centenas = centenas + 48; //Paraa que el valor este en valores ASCII
    decenas = decenas + 48;
    unidades = unidades + 48;
}
void putch(char info){//Se transmite la cadena de caracteres a esta funcion 
                      // por el printf
    while (TXIF == 0);// Se espera algo que haya que transmitir
    TXREG = info;// lo que hay en data se pasa al registro de transmision para 
                 // para que se depliegue en la terminal virtual.
}