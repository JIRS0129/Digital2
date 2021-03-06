
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "SEGHEX.h"
#include "ADC.h"

#define _XTAL_FREQ 4000000

unsigned char contar, counted1, counted2, disp, intTMR, disp1, disp2 = 0;
unsigned int contador1, contador2 = 0;

void __interrupt() ISR(){

    if(INTCONbits.RBIF){

        if(PORTBbits.RB0){
            contar = 1;
        }if(PORTBbits.RB1){
            contar = 2;
        }
        INTCONbits.RBIF = 0;

    }
    if(INTCONbits.T0IF){

        disp++;
        TMR0 = 99;
        intTMR = 1;
        INTCONbits.T0IF = 0;

    }

    if(ADCON0bits.GO_DONE == 0){
        
        adc = 1;
        PIR1bits.ADIF = 0;
    }
}

void setup(){
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    TRISA = 1;
    TRISB = 0b00000011;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;

    IOCB = 0b00000011;
    INTCON = 0b10001000;
    ANSELH = 0;


}


void main(void) {

    setup();
    initTMR(0b00000100);
    configuracionADC(1, 0);

    while (1)
    {
        //Botones
        if(contar == 1){

            if(contador1 <= 100){
                contador1++;

            }else{
                if(PORTBbits.RB0 && counted1 == 0){
                    PORTD++;
                    counted1 = 1;
                }else if(PORTBbits.RB0 == 0){
                    counted1 = 0;
                    contador1 = 0;
                    contar = 0;
                }
            }
        }if(contar == 2){
            if(contador2 <= 100){
                contador2++;
            }else{
                if(PORTBbits.RB1 && counted2 == 0){
                    PORTD--;
                    counted2 = 1;
                }else if(PORTBbits.RB1 == 0){
                    counted2 = 0;
                    contador2 = 0;
                    contar = 0;
                }
            }
        }

        if(adc){
            readADC();
            adc = 0;
            //ADCON0bits.GO_DONE = 1;
            disp2 = adcValue & 0b00001111;
            disp1 = (adcValue & 0b11110000)/16;
        }

        if(PORTD >= adcValue){
            PORTBbits.RB7 = 0;
        }else{
            PORTBbits.RB7 = 1;
        }

        if(intTMR){
            ADCON0bits.GO_DONE = 1;
            displayFunc(disp, disp1, disp2);
            __delay_ms(2);
            intTMR = 0;
        }


    }


}
