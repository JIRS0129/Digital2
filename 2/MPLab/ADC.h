/* 
 * File:   ADC.h
 * Author: JIRS0129
 *
 * Created on February 4, 2020, 8:05 AM
 */

#ifndef ADC_H
#define	ADC_H

unsigned char adc = 0;

unsigned int configuracionADC(unsigned char FOSC, unsigned char channel);
void readADC(void);

#endif	/* ADC_H */

