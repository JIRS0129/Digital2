/*
 * File:   main.c
 * Author: JIRS0129
 *
 * Created on January 24, 2020, 12:44 PM
 */


#include <xc.h>

//Global variables
unsigned int start = 0;
unsigned int btn1 = 0;
unsigned int btn2 = 0;
unsigned int counterbtn1 = 0;
unsigned int counterbtn2 = 0;

//Function prototypes
void setup (void);
void disp_table(unsigned int number);
unsigned int playercounter(unsigned int prior);

//Interruption function
interrupt butttons(void){
  //if start button pressed and race hasn't started, start race
  if (PORTBbits.RB0 && start == 0) {
    if(start == 0){
      start = 1;
    }
  }else if(PORTBbits.RB1){  //If J1's button pressed
    if(start == 2){ //If start routine started
      btn1 = 1;
    }
  }else if(PORTBbits.RB2){  //If J2's button pressed
    if (start == 2) {
      btn2 = 1;
    }
  }
}

void main(void) {

  setup();
  disp_table(3);  //Setup and place the 3 on display
  while (1) {     //infinite loop
    if(start){    //If start button pressed
      //Race start routine
      __delay_ms(500);
      PORTBbits.RB2 = 1;
      disp_table(2);
      __delay_ms(500);
      PORTBbits.RB2 = 0;
      PORTBbits.RB1 = 1;
      disp_table(1);
      __delay_ms(500);
      PORTBbits.RB1 = 0;
      PORTBbits.RB0 = 1;
      disp_table(0);
      __delay_ms(5);
      start = 2;  //Allow players to press buttons
    }else if(btn1){
      if (counterbtn1 <= 100) {
        counterbtn1++;
      }else{
        PORTA = playercounter(PORTA);
        if(PORTA == 8b'10000000'){
          PORTBbits.RB6 = 1;
          start = 0;
        }
        counterbtn1 = 0;
        btn1 = 0;
      }
    }else if (btn2) {
      if (counterbtn2 <= 100) {
        counterbtn2++;
      }else{
        PORTD = playercounter(PORTD);
        if(PORTA == 8b'10000000'){
          PORTBbits.RB7 = 1;
          start = 0;
        }
        counterbtn2 = 0;
        btn2 = 0;
      }
    }
  }

}

unsigned int playercounter(unsigned int prior){
  switch (prior) {
    case 0:
      return 8b'00000001';
    case 1:
      return 8b'00000010';
    case 8b'00000010':
      return 8b'00000100';
    case 8b'000000100':
      return 8b'00001000';
    case 8b'00001000':
      return 8b'00010000';
    case 8b'00010000':
      return 8b'00100000';
    case 8b'00100000':
      return 8b'01000000';
    case 8b'01000000':
      return 8b'10000000';
  }
}

void disp_table(unsigned int number){
  switch (number) {
    case 0:
      PORTC = 8b'00010001';
    case 1:
      PORTC = 8b'01111101';
    case 2:
      PORTC = 8b'00100011';
    case 3:
      PORTC = 8b'00101001';
  }
}

void setup(void){
    // PIC16F887 Configuration Bit Settings

    // 'C' source line config statements

    // CONFIG1
    #pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
    #pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
    #pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
    #pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
    #pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
    #pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
    #pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
    #pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
    #pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
    #pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

    // CONFIG2
    #pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
    #pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

    // #pragma config statements should precede project file includes.
    // Use project enums instead of #define for ON and OFF.

    //PORTB interrupt on change enable.
    INTCONbits.GIE = 1;
    INTCONbits.RBIE = 1;
    INTCONbits.INTE = 1;
    INTCONbits.INTF = 0;
    INTCONbits.RBIF = 0;
    //PORTB (0:2 buttons, 3:5 RGY, 6:7 winners' LEDs) initialization
    ANSELH = 0;
    PORTB = 0;
    TRISB = b'00000111';
    WPUB = b'00000111';
    IOCB = b'00000111';

    //PORTA (J1) initialization
    TRISA = 0;
    ANSEL = 0;
    PORTA = 0;

    //PORTC (display) initialization
    TRISC = 0;
    PORTC = 0;

    //PORTD (J2) initialization
    TRISD = 0;
    PORTD = 0;

    return

}
