#include <pic16f887.h>

#include "SEGHEX.h"

void initTMR(unsigned char PreS){
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = PreS;
    INTCONbits.GIE = 1;
    INTCONbits.T0IF = 0;
    TMR0 = 99;
    INTCONbits.T0IE = 1;
}

void displayFunc(unsigned char disp, unsigned char num1, unsigned char num2){
    if(disp%2){
        PORTBbits.RB6 = 0;
        PORTBbits.RB5 = 1;
        PORTC = display[num1];
    }else{
        PORTBbits.RB5 = 0;
        PORTBbits.RB6 = 1;
        PORTC = display[num2];
    }
}
