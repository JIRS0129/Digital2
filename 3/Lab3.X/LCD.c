#include <stdint.h>
#include <pic16f887.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "LCD.h"

void setCursorLCD(uint8_t y, uint8_t x){
    if(y == 1){
        cursor = 0x80 + x - 1;
    }else{
        cursor = 0xC0 + x - 1;
    }
    cmdLCD(cursor);
}

void clcLCD(void){
    cmdLCD(0x01);
}

void writeStrLCD(uint8_t *string){
	int cont;
	for(cont=0;string[cont]!='\0';cont++){
        writeCharLCD(string[cont]);
    }
}

void writeCharLCD(uint8_t character){
   RS = 1;
   PORTA = character;
   E = 1;
   __delay_us(40);
   E = 0;
}



void initLCD(void){
     __delay_ms(15);
    cmdLCD(0x030);
    cmdLCD(0x030);
    cmdLCD(0x030);
  /////////////////////////////////////////////////////
    cmdLCD(0x38);
    cmdLCD(0x10);
    cmdLCD(0x01);
    cmdLCD(0x06);
    cmdLCD(0x0E);
}

void cmdLCD(uint8_t cmd){
    RS = 0;
	dataPort = cmd;
	E  = 1;
    __delay_ms(4);
    E  = 0;
}

void writeIntLCD(uint8_t numero){
    char buffer [4];
    sprintf (buffer, "%d", numero); //Convierte el int en string
    writeStrLCD(buffer);
}