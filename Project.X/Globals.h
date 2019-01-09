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


#define _XTAL_FREQ 500000                               // Used by the XC8 delay_ms(x) macro

// INPUT
#define INPUT_MAX 3
#define INPUT_MIN 0
char _inputUpdateRequired = 0;
unsigned short _selectedInput;
unsigned short _lastA, _lastB;


// VOLUME
int volume = 0;



#endif	/* GLOBALS_H */

