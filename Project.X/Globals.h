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


#define _XTAL_FREQ 4000000                               // Used by the XC8 delay_ms(x) macro

// INPUT
#define INPUT_MAX 3
#define INPUT_MIN 0
char _inputUpdateRequired = 0;
unsigned short _selectedInput;
unsigned short _lastA, _lastB;


// VOLUME
#define MAX_ADC (1023 * 0.8)            // PIC16 has a 10-bit ADC, 2^10 - 1023. Potmeter with 20% tolerance, 1023 * .8
#define DEADZONE (MAX_ADC * 0.01)       // Deadzone between turnpoint, 1% of the MAX_ADC
#define STEPS 40                        // Total amound of volume steps 
#define STEP_SIZE (MAX_ADC / STEPS)     // Define size of each step

int volume = 0;



#endif	/* GLOBALS_H */

