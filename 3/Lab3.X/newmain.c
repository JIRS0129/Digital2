/*
 * File:   newmain.c
 * Author: JIRS0129
 *
 * Created on February 7, 2020, 10:50 AM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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

#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#include "LCD.h"
#include "USART.h"

#define _XTAL_FREQ 4000000


uint8_t contADC, sensor1, sensor2, cont = 0;
uint8_t entero1, dec1, entero2, dec2 = 0;
uint8_t receivingData, interrupcionUSART = 0;
float sensorF1, sensorF2, float1, float2 = 0;

void setup(void);

void __interrupt() ISR(void){
    if(ADCON0bits.GO_DONE == 0){   //If ADC interrupt
        adc = 1;                    //Activate flag
        PIR1bits.ADIF = 0;          //Clear ADC flag
    }
    if(PIR1bits.RCIF == 1){         //If data received by USART
        interrupcionUSART = 1;      //Activate flag
        receivingData = RCREG;      //Read
    }
}

void main(void) {
    
    //Configs
    setup();
    initUSART(9600, 1, 1, 0);
    configADC(1);
    configCanal(10);
    configCanal(12);
    initLCD();
    clcLCD();
    
    //Write first row that won't be modified
    setCursorLCD(1, 1);
    writeStrLCD("S1");
    setCursorLCD(1, 7);
    writeStrLCD("S2");
    setCursorLCD(1, 13);
    writeStrLCD("COM");
    setCursorLCD(2, 1);
    
    while(1){ //Main Loop
        
        if(adc){        //If there was an ADC interrupt
            contADC++;      //Increase ADC counter
            if(contADC%2){  //Check counter as a multiplexing variable
                selCanal(10);   //Change channel
                sensor1 = readADC();    //Read sensor
            }else{
                selCanal(12);       //Change channel
                
                sensor2 = readADC();    //Read sensor
            }
            adc = 0;    //Clear adc flag
        }
        
        //Potentiometer's processing
        sensorF1 = (float) sensor1 * 5/255; //Conversion from 0 to 5V
        entero1 = (int) sensorF1;           //Takes only the integer from convertion
        float1 = (sensorF1 - entero1)*100;  //Subtraction and multiplication to leave the 2 decimals as integers
        dec1 = (int) float1;                //Takes the integer (which is the 2 decimals from convertion)
        //Same as prior pot
        sensorF2 = (float) sensor2 * 5/255;
        entero2 = (int) sensorF2;
        float2 = (sensorF2 - entero2) * 100;
        dec2 = (int) float2;
        
        //LCD write
        writeFloat(entero1, dec1, 1);       //Writes first number starting from position 1
        writeFloat(entero2, dec2, 7);       //Writes first number starting from position 7
        setCursorLCD(2, 13);                //Moves to position 13 to write PC counter
        writeIntLCD(cont);
        writeStrLCD("  ");                  //Writes empty spaces to clear prior numbers in case there's any
        
        sendUSART(sensor1);                 //Writes sensor's value to PC
        sendUSART(sensor2);
        sendUSART(255);                     //Stop Byte
        
        if(interrupcionUSART){              //If there was an interrupt on serial
            if(receivingData == 43){        //If it was a '+'
                cont++;                     //Increment
            }else if(receivingData == 45){  //If a '-'
                cont--;                     //Decrease
            }
            interrupcionUSART = 0;          //Clear flag
        }
        
        if(ADCON0bits.GO_DONE == 0){        //If no convertion is going on
            ADCON0bits.GO_DONE = 1;         //Start a new one
        }
        
    }
}


void setup(void){
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    TRISA = 0;
    TRISB = 0b10000000;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
}