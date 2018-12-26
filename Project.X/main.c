// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.

#include <xc.h>
#include "pic16f887.h"
#include "main.h"
#include "Config.h"
#include "Input.h"
#include "Display.h"
#define _XTAL_FREQ 500000                               // Used by the XC8 delay_ms(x) macro

#define INPUT_MAX 3
#define INPUT_MIN 0


void main(void) 
{   
    config();
    SSPCON = 0b00100000;
    SSPSTAT = 0b01000000;
    
    // DISPLAYS
    TRISD = 0x00;
    TRISC = 0x00;
    
    /*
    //DISPLAY 1
    PORTDbits.RD2 = 1; // set reset display on logic 1
    PORTDbits.RD6 = 0; // set blank display 1 on logic 1 is for brightness
    PORTDbits.RD4 = 1; // chip enable display 1 logic low to write data
    PORTCbits.RC3 = 0;// sck?? is de clock, is laag dan wordt data gelatcht
    
    
    PORTDbits.RD7 = 1; // select control register
    PORTDbits.RD4 = 0; // chip enable @luisteren@
    spiWrite(0b01001111); // control word 0, wake up from sleep and set brightness
    PORTDbits.RD4 = 1;  // latch control word to register
    
    
    int i;
    int x;
    int long nummer = 11;
    PORTDbits.RD7 = 0; // write to dot register
    PORTDbits.RD4 = 0; // set in luistermodus
    
    for(i = 0; i < 8; i++)
    {
        for(x=0; x < 5; x++){
        spiWrite(font_5x7[nummer][x]);
        
        }
        __delay_ms(5);
        nummer++;
    }
   
    
    //PORTDbits.RD4 = 1; // latch naar register
    
    __delay_ms(100);*/
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // DISPLAY 2
   
    
    PORTCbits.RC2 = 1; // set reset display on logic 1
    PORTCbits.RC6 = 0; // set blank display 1 on logic 1 is for brightness
    PORTCbits.RC4 = 1; // chip enable display 1 logic low to write data
    PORTCbits.RC3 = 0; // sck?? is de clock, is laag dan wordt data gelatcht
    PORTCbits.RC7 = 0; //
    
    
    PORTCbits.RC7 = 1; // select control register
    PORTCbits.RC4 = 0; // chip enable @luisteren@
    spiWrite(0b01001010); // control word 0, wake up from sleep and set brightness
    
    PORTCbits.RC4 = 1;  // latch control word to register
    
    PORTCbits.RC7 = 1; // select control register
    PORTCbits.RC4 = 0; // chip enable @luisteren@
   
    spiWrite(0b10000001); // control word 1, wake up from sleep and set brightness
    PORTCbits.RC4 = 1;  // latch control word to register
    
    PORTCbits.RC7 = 0; // write to dot register
    PORTCbits.RC4 = 0; // set in luistermodus
    
    
    
    char volume = 1;
    
    __delay_ms(3000);
    
     white_space(1);
     
     //PORTCbits.RC4 = 1; // latch naar register
     
    while(1)
        
    {
   
    
    }
   
    return;
}
/*
void __interrupt() isr()
{    
    if (INTCONbits.RBIF) {
       
        int portA = PORTBbits.RB4;
        int portB = PORTBbits.RB5;

        if (_lastA != portA) { // Interrupt rotary port A
            if (_lastA == _lastB) {
                if (_selectedInput < INPUT_MAX) {
                    _selectedInput++;
                } else {
                    _selectedInput = INPUT_MIN;
                }
            }
        }

        if (_lastB != portB) { // Interrupt rotary port B
            if (_lastA == _lastB) {
                if (_selectedInput > INPUT_MIN) {
                    _selectedInput--;
                } else {
                    _selectedInput = INPUT_MAX;
                }
            }
        }
        
        _lastA = portA;
        _lastB = portB;
        _inputUpdateRequired = 1;
        INTCONbits.RBIF = 0;
    }
}
 */