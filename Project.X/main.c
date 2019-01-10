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


#include "Globals.h"
#include "Config.h"
#include "Input.h"
#include "Display.h"
#include "Volume.h"
#include "Remote.h"


void main(void) 
{   
    config();

    
    while(1)  
    {
     
        
        if (!ADCON0bits.GO) // Start ADC 
            ADCON0bits.GO = 1;
        
        update_volume();
        update_input();
        activateSelectedRelay();
        handle_remote();
        
        __delay_ms(10);
    
    }

}

void __interrupt() isr()
{    
    if (INTCONbits.RBIF) {
       
        handle_rotary();
        
        if (PORTBbits.RB0 == 0) {
            start_receive();
        }
        
        INTCONbits.RBIF = 0;
    }
    
    if (PIR1bits.ADIF) {
        
        handle_potmeter();
        
        PIR1bits.ADIF = 0;
    }
    
    if (PIR1bits.TMR2IF) {
        PR2 = 25; // Set TMR2 value TODO: Check if this can be removed

        poll_receiver();
        
        PIR1bits.TMR2IF = 0;

    }
}
 