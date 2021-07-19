/*
 * File:   lab0.c
 * Author: duart
 *
 * Created on 12 de julio de 2021, 07:21 PM
 */

#include <xc.h>
#include <stdint.h>
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
//matriz realizada para la traduccion de los valores del contador para display
char DISPLAY[4] = {0b00111111,0b00000110,0b01011011,0b01001111};

//------------------------------------------------------------------------------
//                                VARIABLES
//------------------------------------------------------------------------------
char SALIDA = 3; 
int flag;
char J1;
char J2;
char UNIDAD; //variable para la asignacion de la unidad del contador

// Se establece el vector de interrupcion
void __interrupt() isr(void)
{
    
    if (RBIF == 1)// Interrupcion por la bandera del puerto B
    {
        if (PORTBbits.RB0 == 0)
        {
            __delay_ms(100);
            SALIDA = SALIDA - 1;
            __delay_ms(100);
            SALIDA = SALIDA - 1;
            __delay_ms(100);
            SALIDA = SALIDA - 1;
            flag = 1;
        }         
        
       if (flag == 1)
       {
          
            if (PORTBbits.RB1 == 0)
            {
                PORTC = J1; 
                J1 <<= 1;
            }      
            if (PORTBbits.RB2 == 0)
            {
                PORTD = J2;
                J2 <<= 1;
            }
           // flag = 0;
       }
        
        INTCONbits.RBIF = 0;// Se limpia la bandera de la interrupcion del 
    }                       // puerto B
}
//------------------------------------------------------------------------------
//                          PROTOTIPOS FUNCIONES 
//------------------------------------------------------------------------------
void setup(void); 
char division(void);//se mencionan las funciones que se tienen

void main(void) {
    
    setup();// Se llama a la funcion setup para configuracion de I/O
    while (1) // Se implemta el loop
    {
        division();// se llama la subrrutina para hacer la division de centena,
        PORTA = (DISPLAY[UNIDAD]);
        switch (SALIDA)
        {
            case 3:
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTEbits.RE2 = 0;
                break;
                
            case 2:
                PORTEbits.RE0 = 1;
                PORTEbits.RE1 = 0;
                PORTEbits.RE2 = 0;
                break;
                
            case 1:
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 1;
                PORTEbits.RE2 = 0;
                break;
                
            case 0:
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 0;
                PORTEbits.RE2 = 1;
                break;
        } 
        if (PORTCbits.RC7 == 1)
        {
            __delay_ms(10);
            break;
        }
        else if (PORTDbits.RD7 == 1)
        {
            __delay_ms(10);
            break;
        }    
    }             
}
//------------------------------------------------------------------------------
//                             CONFIGURACIONES
//------------------------------------------------------------------------------
void setup(void){
    // configuracion de puertos 
    ANSEL = 0X00;
    ANSELH = 0X00;//se establecen los pines como entras y salidas digitales
    
    TRISA = 0X00;
    TRISB = 0X00;
    TRISC = 0X00;
    TRISD = 0X00;
    TRISE = 0X00;// Se establecen los puertos A, C y E como salidas 
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;//Se ponen como entradas los primeros pines del puertoB
    
    PORTA = 0X00;
    PORTB = 0X00;
    PORTC = 0X00;
    PORTD = 0X00;
    PORTE = 0X00;//Se limpian los puertos utilizados
    
    // configuracion del oscilador 
    OSCCONbits.IRCF2 = 0;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0; //Se configura el oscilador a una frecuencia de 250kHz
    OSCCONbits.SCS = 1;
    
    // configuracion del timer 0 y pull-up internos
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0b00000111;
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    IOCBbits.IOCB2 = 1;
    
    // configuracion de interrupciones 
    INTCONbits.GIE = 1;
    INTCONbits.RBIF = 1;
    INTCONbits.RBIE = 1;
    
    //INICIO DE VARIABLES
    J1 = 0b00000001;
    J2 = 0b00000001;
}
char division(void){
    UNIDAD = SALIDA%10;//Se guarda el residuo de la division entre 10
}