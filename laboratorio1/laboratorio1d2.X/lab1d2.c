/*
 * File:   lab1d2.c
 * Author: duart
 *
 * Created on 15 de julio de 2021, 12:13 PM
 */
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "libreria_ADC.h" // Libreria para conf. del ADC y lectura del adresh
#include "Tabla_DIS.h"//tabla para hacer traduccion de los valores del adresh
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

#define _XTAL_FREQ 4000000//Para usar la funcion de 'delay'


//------------------------------------------------------------------------------
//                                VARIABLES
//------------------------------------------------------------------------------
int MULTIPLEXADO; //bandera para hacer el cambio de displays
unsigned char GUARDADO;//variable para guardar el valor de adresh
char VAR1;//variable para guardar el nibble menos significativo de adresh
char VAR2;//variable para guardar el nibble mas significativo de adresh
//------------------------------------------------------------------------------
//                          PROTOTIPOS FUNCIONES 
//------------------------------------------------------------------------------
void setup(void); 
unsigned  char  swapTwoNibbles ( unsigned  char n);

// Se establece el vector de interrupcion
void __interrupt() isr(void){

    if (T0IF == 1) // Interrupcion por la bandera del timer0
    {   if (MULTIPLEXADO == 0b00000000) 
        {
            PORTEbits.RE1 = 0;//Se apaga el tercer display de 7 seg 
            PORTEbits.RE0 = 1;//Se activa el primer display de 7 seg
            PORTC = 0;//Se pone en o para evitar ghosting
            PORTC = TABLA(VAR2);//Se despliega el valor de centena traducido
            MULTIPLEXADO = 0b00000001;//se cambia el valor de bandera para pasar
        }                           //al siguiente display
        
        else if (MULTIPLEXADO == 0b00000001) // si la bandera tiene este valor se dan
        {                               // la siguientes instrucciones
            PORTEbits.RE0 = 0;//Se apaga el primer display
            PORTEbits.RE1 = 1;// Se enciende el segundo display
            PORTC = 0;//Se pone en o para evitar ghosting
            PORTC = TABLA(VAR1);//despliega el valor de decena traducido  
            MULTIPLEXADO = 0b00000000;// se cambia el valor de bandera para 
        }                             // pasar al siguiente display  
        INTCONbits.T0IF = 0;// Se limpia la bandera del timer0
        TMR0 = 10;//Se carga valor al timer0 para que trabaje a 5ms
    }
    
    if (RBIF == 1)// Interrupcion por la bandera del puerto B
    {
        if (PORTBbits.RB0 == 0)
        {
            PORTD = PORTD + 1;// Si se apacha el primer boton se incrementa el 
        }                     // el puerto D
        if (PORTBbits.RB1 == 0)
        {
            PORTD = PORTD - 1;// Si se apacha el segundo boton se decrementa el 
        }                     // el puerto D
        INTCONbits.RBIF = 0;// Se limpia la bandera de la interrupcion del 
    }                       // puerto B
    if (PIR1bits.ADIF == 1)//Interrupcion del ADC 
    {
        if (ADCON0bits.CHS == 0)//si se esta en este canal que haga lo siguiente
        {
//            ADCON0bits.CHS = 0;//Se cambia el valor del canal
            GUARDADO = read_ADC();// Se guarda el valor de ADRESH en una variable.
        }                     // para luego realizar la division. 
        __delay_us(50);//tiempo necesario para el cambio de canal 
        PIR1bits.ADIF = 0;//Se apaga el valor de la bandera de interrupcion ADC
    }
}
//------------------------------------------------------------------------------
//                             CICLO PRINCIPAL 
//------------------------------------------------------------------------------
void main(void){
    
    setup();// Se llama a la funcion setup para configuracion de I/O
    while (1) // Se implemta el loop
    {
        ADCON0bits.GO = 1;
        VAR1 = GUARDADO & 0b00001111;
        VAR2 = swapTwoNibbles(GUARDADO)& 0b00001111;
        if (PORTD < read_ADC())
        {
            PORTBbits.RB7 = 1;
        }
        else
            PORTBbits.RB7 = 0;
    }              
}
//------------------------------------------------------------------------------
//                             CONFIGURACIONES
//------------------------------------------------------------------------------
void setup(void){
    // configuracion de puertos 
    ANSEL = 0b00000001; //setea AN0
    ANSELH = 0X00;//se establecen los pines como entras y salidas digitales
    
    TRISA = 0xff; // Se pone todo el puerto A como entrada.
    TRISC = 0X00;
    TRISD = 0X00;        
    TRISE = 0X00;// Se establecen los puertos A, C, D y E como salidas 
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB7 = 0;//Se ponen como entradas los primeros pines del puertoB
    
    PORTA = 0X00;
    PORTC = 0X00;
    PORTD = 0X00;
    PORTB = 0X00;
    PORTE = 0X00;//Se limpian los puertos utilizados
    
    // configuracion del oscilador 
    OSCCONbits.IRCF2 = 0;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1; //Se configura el oscilador a una frecuencia de 250kHz
    OSCCONbits.SCS = 1;
    
    // configuracion del timer 0 y pull-up internos
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS0 = 0;
    
    
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0b00000011;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    
    // configuracion del ADC
    conf_ADC();
    
    // configuracion de interrupciones 
    INTCONbits.GIE = 1;
    INTCONbits.RBIF = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;
    PIR1bits.ADIF = 0; // BANDERA de interrupcion del ADC
    PIE1bits.ADIE = 1; // Habilita la interrupcion del ADC
    INTCONbits.PEIE = 1; // Interrupcion de los perifericos
}
unsigned  char  swapTwoNibbles ( unsigned  char n)
{
    unsigned  char num;
    num = (((n &  0x0F ) <<  4)  | ((n &  0xF0 ) >>  4));
    return num;
}