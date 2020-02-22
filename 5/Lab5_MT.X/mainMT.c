/*
 * File:   mainMT.c
 * Author: JIRS0129
 *
 * Created on February 22, 2020, 12:22 PM
 */

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
#include <stdint.h>
#include <pic16f887.h>
#include "I2C.h"
#include <xc.h>
#include "LCD.h"
//#include "RTC.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000

//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
int  BCD_2_DEC(int to_convert);
int DEC_2_BCD (int to_convert);
void Config_Time_Date(void);
void Update_Current_Date_Time(void);

uint8_t adc, entero1, dec1, counter;
uint8_t entero2, dec2;
float sensorF1, float1;
float sensorF2, float2;
uint8_t s3;
float lux;
uint8_t sec, min, hour, date, month, year = 0;

//*****************************************************************************
// Main
//*****************************************************************************
void main(void) {
    setup();
    Config_Time_Date();
    while(1){
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        adc = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10); 
        
        I2C_Master_Start();
        I2C_Master_Write(0x61);
        counter = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
        
        I2C_Master_Start();
        I2C_Master_Write(0x41);
        s3 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
        
        //Potentiometer's processing
        sensorF1 = (float) adc * 5/255; //Conversion from 0 to 5V
        entero1 = (int) sensorF1;           //Takes only the integer from convertion
        float1 = (sensorF1 - entero1)*100;  //Subtraction and multiplication to leave the 2 decimals as integers
        dec1 = (int) float1;                //Takes the integer (which is the 2 decimals from convertion)
        
        writeFloat(entero1, dec1, 1);       //Writes first number starting from position 1
        setCursorLCD(2, 7);
        writeIntLCD(counter);
        writeCharLCD(' ');
        setCursorLCD(2, 10);
        Update_Current_Date_Time();
        if(min<10){
            writeCharLCD('0');
        }
        writeIntLCD(min);
        writeCharLCD(':');
        writeIntLCD(sec);
        writeStrLCD("  ");
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    //Configs
    ANSEL = 0;
    ANSELH = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;
    PORTD = 0;
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
    
    initLCD();
    clcLCD();
    
    //Write first row that won't be modified
    setCursorLCD(1, 1);
    writeStrLCD("S1");
    setCursorLCD(1, 7);
    writeStrLCD("S2");
    setCursorLCD(1, 10);
    writeStrLCD("S3");
    
    date = 22;
    month = 2;
    year = 20;
    sec = 0;
    min = 59;
    hour = 11;
}

int  BCD_2_DEC(int to_convert)
{
   return (to_convert >> 4) * 10 + (to_convert & 0x0F); 
}

int DEC_2_BCD (int to_convert)
{
   return ((to_convert / 10) << 4) + (to_convert % 10);
}

void Config_Time_Date(void)
{
   I2C_Master_Start();       
   I2C_Master_Write(0xD0); 
   I2C_Master_Write(0);  
   I2C_Master_Write(DEC_2_BCD(sec)); //update sec
   I2C_Master_Write(DEC_2_BCD(min)); //update min
   I2C_Master_Write(DEC_2_BCD(hour)); //update hour
   I2C_Master_Write(1); //ignore updating day
   I2C_Master_Write(DEC_2_BCD(date)); //update date
   I2C_Master_Write(DEC_2_BCD(month)); //update month
   I2C_Master_Write(DEC_2_BCD(year)); //update year
   I2C_Master_Stop();
}

void Update_Current_Date_Time(void)
{
   //START to Read
   I2C_Master_Start();       
   I2C_Master_Write(0xD0); 
   I2C_Master_Write(0);    
   I2C_Master_Stop(); 
   
  //READ
   I2C_Master_Start();
   I2C_Master_Write(0xD1);                              // Initialize data read
   sec = BCD_2_DEC(I2C_Master_Read(0));    
   I2C_Master_Stop(); 
   
   I2C_Master_Start();
   I2C_Master_Write(0xD1);                              // Initialize data read
   min = BCD_2_DEC(I2C_Master_Read(0));   // Read sec from register 
   I2C_Master_Stop(); 
   
   I2C_Master_Start();
   I2C_Master_Write(0xD1);                              // Initialize data read
   hour = BCD_2_DEC(I2C_Master_Read(0));  
   I2C_Master_Stop(); 
   
   I2C_Master_Start();
   I2C_Master_Write(0xD1);                              // Initialize data read
   hour = BCD_2_DEC(I2C_Master_Read(0));  
   I2C_Master_Stop(); 
   
   I2C_Master_Start();
   I2C_Master_Write(0xD1);                              // Initialize data read
   date = BCD_2_DEC(I2C_Master_Read(0));  
   I2C_Master_Stop(); 
   
   I2C_Master_Start();
   I2C_Master_Write(0xD1);                              // Initialize data read
   month = BCD_2_DEC(I2C_Master_Read(0));  
   I2C_Master_Stop(); 
   
   I2C_Master_Start();
   I2C_Master_Write(0xD1);                              // Initialize data read
   year = BCD_2_DEC(I2C_Master_Read(0));  
   I2C_Master_Stop(); 
    
  //END Reading  
    I2C_Master_Start();
    I2C_Master_Write(0xD1);                              // Initialize data read
    I2C_Master_Read(0);    
    I2C_Master_Stop(); 

}