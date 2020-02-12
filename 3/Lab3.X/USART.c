#include <xc.h>
#include <stdint.h>
#include "USART.h"

void configUSART(uint8_t intRC, uint8_t intTX, uint8_t sync, uint8_t bits){
    TRISC = 0x80; //RX como I, TX como O
    
    RCSTAbits.SPEN = 1; //Habilitar serial
    TXSTAbits.SYNC = sync;  //Sincrono/Asincrono
    
    if(intTX){  //Si se desea transmitir
        PIE1bits.TXIE = 1;  //Habilitar interrupciones de transmision
        PIR1bits.TXIF = 0;  //Limpiar bandera
        TXSTAbits.TXEN = 1; //Habilitar TX
        if(bits == 9){  //9 Bits
            TXSTAbits.TX9 = 1;
        }else{
            TXSTAbits.TX9 = 0;
        }
    }
    if(intRC){  //Si se desea recibir
        PIE1bits.RCIE = 1;  //Habilitar interrupciones de recepcion
        PIR1bits.RCIF = 0;  //Limpiar bandera
        RCSTAbits.CREN = 1; //Habilitar RX
        if(bits == 9){  //9 Bits
            RCSTAbits.RC9 = 1;
        }else{
            RCSTAbits.RC9 = 0;
        }
    }
    
}

void sendUSART (uint8_t dataOut){
    while (TXSTAbits.TRMT == 0)//Hasta que no hallan datos
    TXREG = dataOut;//enviar data
}