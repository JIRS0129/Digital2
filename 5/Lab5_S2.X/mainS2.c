/*
 * File:   mainS1.c
 * Author: JIRS0129
 *
 * Created on February 21, 2020, 10:55 AM
 */

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
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include <xc.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000
uint8_t z;
uint8_t dato;
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);

uint8_t counter, counted1, counted2;
uint8_t btn1, btn2, counterbtn1, counterbtn2 = 0;
//*****************************************************************************
// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
   if(PIR1bits.SSPIF == 1){ 

        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            PORTD = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            SSPBUF = PORTA;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
       
        PIR1bits.SSPIF = 0;    
    }
}
//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    PORTDbits.RD2 = 1;
    while(1){
        if(PORTBbits.RB0 && btn1 == 0){ //If button is pressed and hasn't been pressed before
            btn1 = 1;
        }

        if (counterbtn1 <= 150) {       //count 100 times for the anti-bounce
            counterbtn1 = counterbtn1 + btn1;
        }

        else {                          //when done counting
            if(PORTBbits.RB0 == 1 && btn1 == 1 && counted1 == 0){   //check if button is still pressed.

                if(PORTA == 15){
                    PORTA = 0;
                }else{
                    PORTA++;
                }

                counted1 = 1;                 //variable for code to only run once.
            }
            else if(PORTBbits.RB0 == 0){                   // If it was released befor the 100'th count or after the increment in PORTA
                counterbtn1 = 0;              //reset variables for next push
                btn1 = 0;
                counted1 = 0;
            }
        }

        if(PORTBbits.RB6 && btn2 == 0){ //If button is pressed and hasn't been pressed before
            btn2 = 1;
        }
        if (counterbtn2 <= 150) {       //count 100 times for the anti-bounce
          counterbtn2 = counterbtn2 + btn2;
        }else{                          //when done counting
            if(PORTBbits.RB6 == 1 && btn2 == 1 && counted2 == 0){   //check if button is still pressed.

                if(PORTA == 0){
                    PORTA = 15;
                }else{
                    PORTA--;
                }
                counted2 = 1;                 //variable for code to only run once.
            }else if(PORTBbits.RB6 == 0){                   // If it was released befor the 100'th count or after the increment in PORTA
                counterbtn2 = 0;              //reset variables for next push
                btn2 = 0;
                counted2 = 0;
            }
        }
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    
    TRISA = 0;
    TRISB = 0b01000001;
    TRISD = 0;
    
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    I2C_Slave_Init(0x60);   
}