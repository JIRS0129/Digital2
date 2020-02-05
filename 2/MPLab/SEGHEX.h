/*
 * File:   7SEGHEX.h
 * Author: Home
 *
 * Created on 2 de febrero de 2020, 10:51 PM
 */

#ifndef SEGHEX_H
#define	SEGHEX_H

unsigned char display[16] = {0x88, 0xBE, 0xC4, 0x94, 0xB2, 0x91, 0x83, 0x0BC, 0x80, 0xB0, 0xA0, 0x03, 0xC9, 0x86, 0xC1, 0xE1}; //TABLA DE DISPLAY

void displayFunc(unsigned char disp, unsigned char num1, unsigned char num2);
void initTMR(unsigned char PreS);

#endif	/* NEWFILE_H */
