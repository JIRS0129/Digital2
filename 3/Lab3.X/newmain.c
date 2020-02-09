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

#define _XTAL_FREQ 4000000


uint8_t contADC, sensor1, sensor2 = 0;

void setup(void);



void __interrupt() ISR(void){
    if(ADCON0bits.GO_DONE == 0){   
        adc = 1;
        PIR1bits.ADIF = 0;
    }
}

void main(void) {
    
    setup();
    configADC(1);
    configCanal(10);
    configCanal(12);
    initLCD();
    clcLCD();
    setCursorLCD(1, 1);
    
    writeStrLCD("S1");// lcd_write_string ("POT01");
    
    //writeCharLCD("s");
    /*initLCD();
    lcd_clr();
    lcd_set_cursor(1,1);
    lcd_write_string ("POT01");
    lcd_set_cursor(7,1);
    lcd_write_string ("POT02");
    lcd_set_cursor(14,1);
    lcd_write_string ("TTL");*/
    
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
        if(PORTBbits.RB7){
            PORTD = sensor1;
        }else{
            PORTD = sensor2;
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