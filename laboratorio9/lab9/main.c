/*
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "grlib/grlib.h"

#define XTAL 16000000

//**************************************************************************************************************
// Variables Globales
//**************************************************************************************************************
uint32_t i = 0;
uint32_t ui32Period;

//**************************************************************************************************************
// Prototipos
//**************************************************************************************************************
void delay(uint32_t msec);
void delay1ms(void);
void Timer0IntHandler(void);
//----------------------------------FUNCION BASE--------------------------------------
int main(void)
{
    //SE ESTABLECE UN RELOJ DE 40MHZ CON UN OSILADOR
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    //SE ASIGNA EL RELOJ AL PUERTO F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    //SE ESTABLECEN COMO SALIDA LAS LEDS DEL PUERTO F
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    // Se habilita el reloj para el temporizador
      SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

      // Configuracion del Timer 0 como temporizador periodico
      TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

      // Se calcula el perodo para el temporizador (1 seg)
      ui32Period = (SysCtlClockGet()) / 2;
      // Establecer el periodo del temporizador
      TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period - 1);

      // Se habilita la interrupcion por el TIMER0A
      IntEnable(INT_TIMER0A);
      // Se establece que exista la interrupcion por Timeout
      TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
      // Se habilitan las interrupciones Globales
      IntMasterEnable();
      // Se habilita el Timer
      TimerEnable(TIMER0_BASE, TIMER_A);
      // Se estavblece pin de entrada
      GPIOPadConfigSet(GPIO_PORTF_BASE,
              GPIO_PIN_4,
              GPIO_STRENGTH_2MA,
              GPIO_PIN_TYPE_STD_WPU);


    while (1){
        uint8_t inicio = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
                if (inicio == 0){
                    TimerDisable(TIMER0_BASE, TIMER_A);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
                    delay(2000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                    delay(1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
                    delay(1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                    delay(1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x08);
                    delay(1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                    delay(1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x0A);
                    delay(2000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                    delay(1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x02);
                    delay(2000);
                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
                    TimerEnable(TIMER0_BASE, TIMER_A);
                }

        }
}

//**************************************************************************************************************
// Funcion para hacer delay en milisegundos
//**************************************************************************************************************
void delay(uint32_t msec)
{
    for (i = 0; i < msec; i++)
    {
        delay1ms();
    }

}
//**************************************************************************************************************
// Funcion para hacer delay de 1 milisegundos
//**************************************************************************************************************
void delay1ms(void)
{
    SysTickDisable();
    SysTickPeriodSet(16000);
    SysTickEnable();

    while ((NVIC_ST_CTRL_R & NVIC_ST_CTRL_COUNT) == 0); //Pg. 138

}
//**************************************************************************************************************
// Handler de la interrupcion del TIMER 0 - Recordar modificar el archivo tm4c123ght6pm_startup_css.c
//**************************************************************************************************************
void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    // Read the current state of the GPIO pin and
    // write back the opposite state
    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
    }
}
