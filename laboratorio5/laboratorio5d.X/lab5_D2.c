/*
 * File:   lab5_D2.c
 * Author: duart
 *
 * Created on 12 de agosto de 2021, 11:31 AM
 */
#include <xc.h>
#include <stdint.h>
#include <stdio.h>// Libreria para poder usar printf junto a la funcion putch.
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
//                         BITS DE CONFIGURACION
//------------------------------------------------------------------------------
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO 
                                   //oscillator: I/O function on RA6/OSC2/CLKOUT
                                   //pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR 
                                //pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code 
                                //protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code
                                //protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit 
                                //(Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit 
                                //(Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3/PGM 
                                //pin has PGM function, low voltage programming 
                                //enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out 
                                //Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
                                //(Write protection off)

#define _XTAL_FREQ 8000000//Para usar la funcion de 'delay'

//------------------------------------------------------------------------------
//                                VARIABLES
//------------------------------------------------------------------------------
unsigned char CONT;
char centenas; //Paraa que el valor este en valores ASCII
char decenas;
char unidades;
char centenas1; //Paraa que el valor este en valores ASCII
char decenas1;
char unidades1;
char v1[20];
char v2[20];
char v3[20];
char puerto;

//------------------------------------------------------------------------------
//                          PROTOTIPOS FUNCIONES 
//------------------------------------------------------------------------------
void setup(void); 
void putch(char data);
void division(uint8_t variable);
//void def(void);
//void def1(void);
//void def2(void);
// Se establece la funcion de interrupcion
void __interrupt() isr(void){
if (RBIF == 1)// Interrupcion por la bandera del puerto B
    {
        if (PORTBbits.RB0 == 0)
        {
            CONT = CONT + 1;// Si se apacha el primer boton se incrementa el 
        }                     // el puerto D
        if (PORTBbits.RB1 == 0)
        {
            CONT = CONT - 1;// Si se apacha el segundo boton se decrementa el 
        }                     // el puerto D
        INTCONbits.RBIF = 0;// Se limpia la bandera de la interrupcion del 
    }                       // puerto B
}
//------------------------------------------------------------------------------
//                             CICLO PRINCIPAL 
//------------------------------------------------------------------------------
void main(void) {
    setup();// Se llama a la funcion setup para configuracion de I/O
    
    while (1) // Se implemta el loop
    {
        division(CONT);
        
     if (RCREG == 'a'){   
       if(TXIF == 1){
//    __delay_ms(50);
//     printf("\rVALOR DE CONTADOR DE BOTONES: \r");//SE ENVIA CANDENA DE CARACTERES
     __delay_ms(50);
    if(TXIF == 1){
        TXREG = centenas; 
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
    }    
     }
    
        
        
    while (RCIF == 0);
    centenas1 = RCREG - 48;
    RCIF = 0;
    while (RCIF == 0);
    decenas1 = RCREG - 48;
    RCIF = 0;
    while (RCIF == 0);
    unidades1 = RCREG - 48;
    RCIF = 0;
    
    PORTD = ((centenas1*100)+(decenas1*10)+ unidades1);
    
//    sprintf(v1, "%d", centenas1);
//    sprintf(v2, "%d", decenas1);
//    sprintf(v3, "%d", unidades1);
//    strcat(v1, v2);
//    strcat(v1, v3);
//    int com = atoi(v1);// Se convierten los datos a numeros decimales 
//    PORTD = com;//Se pone dicho numero en el puerto B
    }
        
        
    }            

//------------------------------------------------------------------------------
//                             CONFIGURACIONES
//------------------------------------------------------------------------------
void setup(void){
    // configuracion de puertos 
    ANSEL = 0X00; 
    ANSELH = 0X00;//se establecen los pines como entras y salidas digitales
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISD = 0x00;
    
    PORTA = 0X00;
    PORTD = 0X00;//Se limpian los puertos utilizados
   
    // configuracion del oscilador 
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1; //Se configura el oscilador a una frecuencia de 8 MHz
    OSCCONbits.SCS = 1;

    //CONFIGURACION DE LOS PULL UP
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0b00000011;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    
    //Configuracion TX y RX 
    TXSTAbits.BRGH = 1;  // Para alta velocidad.
    BAUDCTLbits.BRG16 = 1; // Se usan los 16 bits
    
    TXSTAbits.SYNC = 0; // transmision asincrona
    RCSTAbits.SPEN = 1; // Se enciende el modulo 
    RCSTAbits.CREN = 1; // Se abilita la recepcion 
    
    TXSTAbits.TXEN = 1; // Se abilita la transmision 
    
    RCSTAbits.RX9 = 0; // Se determina que no se quieren 9 bits
    
    SPBRG = 207; //BAUD RATE de 9600
    SPBRGH = 0;
    
    // configuracion de interrupciones 
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.RBIF = 1;
    INTCONbits.RBIE = 1;
}
//------------------------------------------------------------------------------
//                               FUNCIONES
//------------------------------------------------------------------------------
void putch(char info){//Se transmite la cadena de caracteres a esta funcion 
                      // por el printf
    while (TXIF == 0);// Se espera algo que haya que transmitir
    TXREG = info;// lo que hay en data se pasa al registro de transmision para 
}            // para que se depliegue en la terminal virtual.
void division(uint8_t variable){
    uint8_t val;
    val = (variable);              //Se guarda en valor la variable que entra
    centenas = (val/100);       //SE OBTIENE EL VALOR DE CENTRENAS
    val = (val - (centenas*100));
    decenas = (val/10);         //SE OBTIENE EL VALOR DE DECENAS
    val = (val - (decenas*10));
    unidades = (val);         //SE OBTIENE EL VALOR DE UNIDADES
    
    centenas = centenas + 48; //Paraa que el valor este en valores ASCII
    decenas = decenas + 48;
    unidades = unidades + 48;
}
