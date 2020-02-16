//*****************************************************************************
/*
 * File:   mainS.c
 * Author: JIRS0129
 *
 * Created on February 14, 2020, 10:56 AM
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
#include "ADC.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);

uint8_t sensor1, sensor2 = 0;
uint8_t contADC = 0;
uint8_t dataIn;
//*****************************************************************************
// Código de Interrupción 
//*****************************************************************************
void __interrupt() isr(void){
    if(ADCON0bits.GO_DONE == 0){   //If ADC interrupt
        adc = 1;                    //Activate flag
        PIR1bits.ADIF = 0;          //Clear ADC flag
    }
    
    if(SSPIF == 1){
        
        dataIn = spiRead();
        if(dataIn == 1){
            spiWrite(sensor1);
        }else if(dataIn == 2){
            spiWrite(sensor2);
        }
        SSPIF = 0;
    }
}
//*****************************************************************************
// Código Principal
//*****************************************************************************
void main(void) {
    setup();
    configADC(1);
    configCanal(0);
    configCanal(1);
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
        
        if(adc){        //If there was an ADC interrupt
            contADC++;      //Increase ADC counter
            if(contADC%2){  //Check counter as a multiplexing variable
                selCanal(0);   //Change channel
                sensor1 = readADC();    //Read sensor
            }else{
                selCanal(1);       //Change channel
                sensor2 = readADC();    //Read sensor
            }
            adc = 0;    //Clear adc flag
        }
        
        if(ADCON0bits.GO_DONE == 0){        //If no convertion is going on
            ADCON0bits.GO_DONE = 1;         //Start a new one
        }
        
        /*if(PORTAbits.RA7){
            PORTB = sensor1;
        }else{
            PORTB = sensor2;
        }*/
       
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    TRISA = 0b10000000;
    TRISB = 0;
    TRISC = 0;
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC4 = 1;
    TRISD = 0;
    TRISE = 0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}