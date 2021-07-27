/*
 * File:   lab2.c
 * Author: duart
 *
 * Created on 25 de julio de 2021, 10:36 PM
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>//Libreria para usar la funcion SWAP
#include "ADC.h"  // Libreria para conf. del ADC y lectura del adresh
#include "BITS_8.h" 
#include <stdio.h>// Libreria para poder usar printf junto a la funcion putch.

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

#define RS PORTEbits.RE0
#define EN PORTEbits.RE2
#define D0 PORTDbits.RD0
#define D1 PORTDbits.RD1
#define D2 PORTDbits.RD2
#define D3 PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7
//------------------------------------------------------------------------------
//                                VARIABLES
//------------------------------------------------------------------------------
uint8_t calculo;
uint8_t calculo2;
uint8_t varUART;
uint8_t GUARDADO;
uint8_t GUARDADO2;
uint8_t sensor3 = 0;
char unidades;
char decenas;
char centenas;
//------------------------------------------------------------------------------
//                          PROTOTIPOS FUNCIONES 
//------------------------------------------------------------------------------
void setup(void); 
void division(uint8_t variable);
void putch(char info);

// Se establece el vector de interrupcion
void __interrupt() isr(void){
 
    if (PIR1bits.ADIF == 1)//Interrupcion del ADC 
    {
        if (ADCON0bits.CHS == 1)//si se esta en este canal que haga lo siguiente
        {
            ADCON0bits.CHS = 0;//Se cambia el valor del canal
            GUARDADO = read_ADC();// Se guarda el valor de ADRESH en una variable.
        }                     // para luego realizar la division. 
        else {
            ADCON0bits.CHS = 1;//Se cambia el valor de canal 
            GUARDADO2 = read_ADC();}// Se guarda el valor de ADRESH en el puerto B
                            // para que se muestre en los 8 leds
        __delay_us(50);//tiempo necesario para el cambio de canal 
        PIR1bits.ADIF = 0;//Se apaga el valor de la bandera de interrupcion ADC
    }
}

//------------------------------------------------------------------------------
//                             CICLO PRINCIPAL 
//------------------------------------------------------------------------------
void main(void) {
    setup();// Se llama a la funcion setup para configuracion de I/O
    Lcd_Init();
    Lcd_Clear();  //Para limpiar el LCD
    Lcd_Set_Cursor(1,1); //Para poner el cursor en fila uno y primera posicion 
    Lcd_Write_String(" S1:   S2:   S3:");
    while (1) // Se implemta el loop
    {
    ADCON0bits.GO = 1; //para empezar de nuevo la ejecucion del AD
    
    division(GUARDADO2);
    Lcd_Set_Cursor(2,1);
    Lcd_Write_Char(centenas);//SE ENVIA VALOR DEL POTENCIOMETRO 1 AL LCD
    Lcd_Write_String(".");
    Lcd_Write_Char(decenas);
    Lcd_Write_Char(unidades);
    
    Lcd_Write_String("V ");
    
    if(TXIF == 1){
    __delay_ms(150);
     printf("VALOR DE POT1: \r");//SE ENVIA CANDENA DE CARACTERES
     __delay_ms(150);
    if(TXIF == 1){
        TXREG = centenas; 
       }
    __delay_ms(150);
    if(TXIF == 1){// SE ENVIA UN PUNTO 
        TXREG = 46; 
       }
    __delay_ms(150);
    if(TXIF == 1){
        TXREG = decenas; 
       }
    __delay_ms(150);
    if(TXIF == 1){
        TXREG = unidades; 
       }
    __delay_ms(100);
    if(TXIF == 1){// EN ENVIA UN SALTO 
        TXREG = 13; 
       }
    __delay_ms(150);
    }    
    
    division(GUARDADO);
    Lcd_Write_Char(centenas);//SE ENVIA VALOR DEL POTENCIOMETRO 2 AL LCD
    Lcd_Write_String(".");
    Lcd_Write_Char(decenas);
    Lcd_Write_Char(unidades);
    Lcd_Write_String("V");
    Lcd_Write_String("  ");
    
    if(TXIF == 1){
    __delay_ms(150);
     printf("VALOR DE POT2: \r");//SE ENVIA CANDENA DE CARACTERES
     __delay_ms(150);    
    if(TXIF == 1){
        TXREG = centenas; 
       }
    __delay_ms(150);
    if(TXIF == 1){  // SE ENVIA UN PUNTO 
        TXREG = 46; 
       }
    __delay_ms(150);
    if(TXIF == 1){
        TXREG = decenas; 
       }
    __delay_ms(150);
    if(TXIF == 1){
        TXREG = unidades; 
       }
    __delay_ms(100);
    if(TXIF == 1){ // EN ENVIA UN SALTO 
        TXREG = 13; 
    }
    __delay_ms(150);
    }  
    
    division(sensor3);// se despliega el valor del contador en el LCD
    Lcd_Write_Char(centenas);
    Lcd_Write_Char(decenas);
    Lcd_Write_Char(unidades);
    
    
    __delay_ms(50);
     printf("\rSi desea incrementar el sensor3 apache +\r");
     __delay_ms(50);
     printf("\rSi desea decrementar el sensor3 apache -\r");
    while(RCIF == 0); //Se espera algo que recibir (CARACTER).
    char entregado = RCREG;//Se crea un variable local que equivale al registro 
                           // de recepcion para usarlo en las condicionales if.
    
    if (entregado == '+'){//si la opcion que se recibe es + se hace lo siguiente
        sensor3++;
    } 
    else if (entregado == '-'){//si la opcion que se recibe es - se hace lo siguiente
        sensor3--;
    }
    }
}
//------------------------------------------------------------------------------
//                             CONFIGURACIONES
//------------------------------------------------------------------------------
void setup(void){
    // configuracion de puertos 
    ANSEL = 0b00000011; //setea AN0 y AN1
    ANSELH = 0X00;//se establecen los pines como entras y salidas digitales
    
    TRISD = 0X00;
    TRISE = 0X00;// Se establecen los puertos A, C y E como salidas 
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;//Se ponen como entradas los primeros pines del puertoB
    
    PORTD = 0X00;
    PORTA = 0X00;
    PORTE = 0X00;//Se limpian los puertos utilizados
    
    // configuracion del oscilador 
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0; //Se configura el oscilador a una frecuencia de 4MHz
    OSCCONbits.SCS = 1;
    
    // configuracion del ADC
  
    configuracion_ADC();// funcion de libreria adc para configurarlo.
    
     //Configuracion TX y RX 
    TXSTAbits.BRGH = 1;  // Para alta velocidad.
    BAUDCTLbits.BRG16 = 0; // Se usan los 16 bits
    
    TXSTAbits.SYNC = 0; // transmision asincrona
    RCSTAbits.SPEN = 1; // Se enciende el modulo 
    RCSTAbits.CREN = 1; // Se abilita la recepcion 
    
    TXSTAbits.TXEN = 1; // Se abilita la transmision 
    
    RCSTAbits.RX9 = 0; // Se determina que no se quieren 9 bits
    
    SPBRG = 25; //BAUD RATE de 9600
    SPBRGH = 1;
    
    // configuracion de interrupciones 
    INTCONbits.GIE = 1;
    PIR1bits.ADIF = 0; // BANDERA de interrupcion del ADC
    PIE1bits.ADIE = 1; // Habilita la interrupcion del ADC
    INTCONbits.PEIE = 1; // Interrupcion de los perifericos
}
void division(uint8_t variable){
    uint8_t val;
    val = variable;              //Se guarda en valor la variable que entra
    centenas = (val/100) ;       //SE OBTIENE EL VALOR DE CENTRENAS
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