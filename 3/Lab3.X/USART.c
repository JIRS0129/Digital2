#include <stdint.h>
#include <xc.h>

void initUSART(uint16_t baudrate, uint8_t txint, uint8_t rcint, uint8_t syncrono){ //Inicializacion del USART
    TRISC = 0x80; //Configuracion del puerto c
    
    PIE1bits.RCIE = 0; //Interrupcion del RX
    
    RCSTAbits.SPEN = 1;
    TXSTAbits.SYNC = syncrono;
    
    if(rcint){
        RCSTAbits.CREN = 1;
        PIE1bits.RCIE = 1;
        PIR1bits.RCIF = 0;
    }
    if(txint){
        TXSTAbits.TXEN = 1;
    }
    
    BAUDCTLbits.BRG16 = 1; //BaudrateHigh
    TXSTAbits.BRGH = 0;
    
    if(baudrate == 300){ //casos del baudrate
        SPBRG = 0x40;
        SPBRGH = 0x03;
    } else if (baudrate == 1200){
        SPBRG = 207;
    } else if (baudrate == 2400){
        SPBRG = 103;
    } else if (baudrate == 9600){
        SPBRG = 25;
    } else if (baudrate == 10417){
        SPBRG = 23;
    } else if (baudrate == 19200){
        SPBRG = 12;
    }
}

void sendUSART (uint8_t data){ //funcion enviar enteros
    while (TXSTAbits.TRMT == 0){}
    TXREG = data;//enviar datos
}
