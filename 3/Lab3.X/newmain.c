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
    if(ADCON0bits.GO_DONE == 0){   
        adc = 1;
        PIR1bits.ADIF = 0;
    }
    if(PIR1bits.RCIF == 1){
        interrupcionUSART = 1;
        receivingData = RCREG;
    }
}

void main(void) {
    
    setup();
    initUSART(9600, 1, 1, 0);
    configADC(1);
    configCanal(10);
    configCanal(12);
    initLCD();
    clcLCD();
    setCursorLCD(1, 1);
    
    writeStrLCD("S1");// lcd_write_string
    setCursorLCD(1, 7);
    writeStrLCD("S2");// lcd_write_string
    setCursorLCD(1, 13);
    writeStrLCD("COM");// lcd_write_string
    setCursorLCD(2, 1);
    
    while(1){
        
        if(adc){
            contADC++;
            if(contADC%2){
                selCanal(10);
                sensor1 = readADC();
            }else{
                selCanal(12);
                
                sensor2 = readADC();
            }
            adc = 0;
        }
        /*if(PORTBbits.RB7){
            PORTD = sensor1;
        }else{
            PORTD = sensor2;
        }*/
        
        //Procesamiento de pots
        
        sensorF1 = (float) sensor1 * 5/255;
        entero1 = (int) sensorF1;
        float1 = (sensorF1 - entero1)*100;
        dec1 = (int) float1;
        
        sensorF2 = (float) sensor2 * 5/255;
        entero2 = (int) sensorF2;
        float2 = (sensorF2 - entero2) * 100;
        dec2 = (int) float2;
        
        
        writeFloat(entero1, dec1, 1);
        writeFloat(entero2, dec2, 7);
        setCursorLCD(2, 13);
        writeIntLCD(cont);
        writeStrLCD("  ");
        
        sendUSART(sensor1);
        sendUSART(sensor2);
        sendUSART(255);
        
        if(interrupcionUSART){
            if(receivingData == 43){
                cont++;
            }else if(receivingData == 45){
                cont--;
            }
            interrupcionUSART = 0;
        }
        
        if(ADCON0bits.GO_DONE == 0){
            ADCON0bits.GO_DONE = 1;
        }
        
    }
    //return;
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