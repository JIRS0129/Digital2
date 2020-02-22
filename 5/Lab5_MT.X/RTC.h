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

uint8_t sec, min, hour, date, month, year = 0;

//Prototypes
int  BCD_2_DEC(int to_convert);
int DEC_2_BCD (int to_convert);
void Config_Time_Date(void);
void Update_Current_Date_Time(void);


#endif	/* LCD_H */

