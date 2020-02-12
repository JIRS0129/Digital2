/* 
 * File:   LCD_Init.h
 * Author: jorge
 *
 * Created on 5 de febrero de 2020, 01:39 PM
 */

/*#ifndef LCD_INIT_H
#define	LCD_INIT_H

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000

void initLCD (void);
void lcd_cmd (uint8_t command);
void lcd_clr (void);
void lcd_set_cursor(uint8_t posy, uint8_t posx);
void lcd_write_char(char var);
void lcd_write_string(char *var);
void lcd_write_int(uint8_t numero);

#endif	/* LCD_INIT_H */

/* 
 * File:   LCD.h
 * Author: JIRS0129
 *
 * Created on February 8, 2020, 7:39 AM
 */
#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000

#ifndef LCD_H
#define	LCD_H

#define RS RC0
#define RW RC2
#define E RC1
#define dataPort PORTA

uint8_t cursor = 0;

void initLCD(void);
void setCursorLCD(uint8_t y, uint8_t x);
void clcLCD(void);
void writeStrLCD(uint8_t *a);
void writeCharLCD(uint8_t character);
void cmdLCD(uint8_t cmd);
void nmbLCD(uint8_t number);
void writeIntLCD(uint8_t numero);

#endif	/* LCD_H */

