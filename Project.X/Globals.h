/* 
 * File:   Globals.h
 * Author: Vincent
 *
 * Created on January 9, 2019, 8:05 PM
 */

#ifndef GLOBALS_H
#define	GLOBALS_H

// Global includes
#include <xc.h>
#include "pic16f887.h"

#define _XTAL_FREQ 4000000 // Used by the XC8 delay_ms(x) macro

// INPUT
#define INPUT_MAX 3
#define INPUT_MIN 0
char _inputUpdateRequired = 0;
unsigned short _selectedInput;
unsigned short _lastA, _lastB;


// VOLUME
#define MAX_ADC (1023)             // PIC16 has a 10-bit ADC, 2^10 = 1023.
#define DEADZONE (MAX_ADC * 0.01)  // Deadzone between turnpoint, 1% of the MAX_ADC (1023 * 0.01 = 10)
#define VOL_STEPS 40               // Total amount of volume steps 

int volume = 0;


#endif	/* GLOBALS_H */

