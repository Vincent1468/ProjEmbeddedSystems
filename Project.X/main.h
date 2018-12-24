#ifndef _MAIN_
#define _MAIN_

extern int portA;

extern int portB;

extern unsigned short _selectedInput;

extern unsigned short _lastA, _lastB;

void __interrupt() isr();

#endif