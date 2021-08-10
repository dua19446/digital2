/*
 * File:   I2CMAESTRO.c
 * Author: duart
 *
 * Created on 8 de agosto de 2021, 01:18 AM
 */
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
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include "LCD.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RB5
#define D6 RD6
#define D7 RD7

uint16_t temp;
float data1;
uint8_t CONT;
uint8_t POT;
char unidades;
char decenas;
char centenas;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
void division(uint8_t variable);
//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    unsigned int a;
    setup();
    Lcd_Init();
    Lcd_Clear();
    while(1){
        
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        POT = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0x61);
        CONT = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0x80); //seleccionar el sensor y se escribe
        I2C_Master_Write(0xF3); //read temperature
        I2C_Master_Stop();
        __delay_ms(200);

        I2C_Master_Start();
        I2C_Master_Write(0x81); //para que ahora lea
        temp = (I2C_Master_Read(0))<<8;
        temp += I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
        data1 = ((175.72*temp)/65536)-46.85;
       
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String(" S1:   S2:   S3:");
        Lcd_Set_Cursor(2,2);
        division(POT);
        Lcd_Write_Char(centenas);//SE ENVIA VALOR DEL POTENCIOMETRO 1 AL LCD
        Lcd_Write_Char(decenas);
        Lcd_Write_Char(unidades);
        Lcd_Set_Cursor(2,9);
        division(CONT);
        Lcd_Write_Char(decenas);
        Lcd_Write_Char(unidades);
             
        if (data1 < 0)
        {
            data1 *= -1;
            Lcd_Set_Cursor(2,13);
            Lcd_Write_Char(45);
        }
        else if (data1 >= 0)
        {
            Lcd_Set_Cursor(2,13);
            Lcd_Write_Char(' ');
        }    
        Lcd_Set_Cursor(2,14);
        division(data1);
        Lcd_Write_Char(centenas);//SE ENVIA VALOR DEL POTENCIOMETRO 1 AL LCD
        Lcd_Write_Char(decenas);
        Lcd_Write_Char(unidades);  
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISA = 0;
    TRISD = 0;
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    // configuracion del oscilador 
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1; //Se configura el oscilador a una frecuencia de 8MHz
    OSCCONbits.SCS = 1;
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
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