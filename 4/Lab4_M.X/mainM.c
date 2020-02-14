//*****************************************************************************
/*
 * File:   mainM.c
 * Author: JIRS0129
 *
 * Created on February 14, 2020, 10:55 AM
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
#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#include "USART.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************

uint8_t sensor1 = 103;
uint8_t sensor2 = 89;

void setup(void);

void __interrupt() ISR(void){
    /*if(PIR1bits.RCIF == 1){         //If data received by USART
        PORTA = RCREG;      //Read
    }*/
}

//*****************************************************************************
// Código Principal
//*****************************************************************************
void main(void) {
    setup();
    //initUSART(9600, 1, 1, 0);
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
        
        if(PORTAbits.RA7){
           PORTB = sensor1;
        }else{
           PORTB = sensor2;
        }
       
       spiWrite(1);
       sensor1 = spiRead();
       
       __delay_ms(10);
       
       
       spiWrite(2);
       sensor2 = spiRead();
       
       __delay_ms(10);
       
       
       /*//Potentiometer's processing
        sensorF1 = (float) sensor1 * 5/255; //Conversion from 0 to 5V
        entero1 = (int) sensorF1;           //Takes only the integer from convertion
        float1 = (sensorF1 - entero1)*100;  //Subtraction and multiplication to leave the 2 decimals as integers
        dec1 = (int) float1;                //Takes the integer (which is the 2 decimals from convertion)
        //Same as prior pot
        sensorF2 = (float) sensor2 * 5/255;
        entero2 = (int) sensorF2;
        float2 = (sensorF2 - entero2) * 100;
        dec2 = (int) float2;*/
       
       
       
       __delay_ms(250);
       //PORTB++;
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
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISA = 0b10000000;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    PORTCbits.RC2 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}