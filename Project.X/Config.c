#include "Config.h"

void config()
{        
    OSCCONbits.IRCF = 0b110; // 4MHz clock
    OSCCONbits.OSTS = 0;
    
    //
    // OUTPUTS
    //
    
    // Set relays as output 
    TRISAbits.TRISA0 = 0; // Set relay 1 (RA0) as output
    TRISAbits.TRISA1 = 0; // Set relay 2 (RA1) as output
    TRISAbits.TRISA2 = 0; // Set relay 3 (RA2) as output
    TRISAbits.TRISA3 = 0; // Set relay 4 (RA3) as output       
    
    PORTA = 0x0F; // Clear port A
       
    //
    // ENCODER
    //
    
    // Set encoder as input
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB5 = 1;
    // Set as DIGITAL input
    ANSELHbits.ANS11 = 0;
    ANSELHbits.ANS13 = 0;
       
    
    //
    // POTMETER
    //
    TRISEbits.TRISE2 = 1; // Set potmeter as input
    ANSELbits.ANS7 = 1; // ANALOG input
    
    //
    // IR RECEIVER
    //
    TRISBbits.TRISB0 = 1; // Set as input
    ANSELHbits.ANS11 = 0; // DIGITAL input
    
    //
    // VOLUME MOTOR
    //
    
    TRISCbits.TRISC0 = 0; // Output
    TRISCbits.TRISC1 = 0; // Output
    
    PORTC = 0x00; // Set motor OFF
        
    
    //
    // INTERRUPTS
    //   
    
    INTCONbits.RBIE = 1; // Enable PORTB interrupts

    IOCBbits.IOCB4 = 1; // Enable interrupt on RB4
    IOCBbits.IOCB5 = 1; // Enable interrupt on RB5
    
    INTCONbits.GIE = 1; // Enable global interrupts

    
    //
    // DISPLAYS
    //      
    display_init();
    
    // ADC
    init_adc();
    
    //
    // Default values
    //
    
    _inputUpdateRequired = 1;
    _selectedInput = 0;
    _lastA = PORTBbits.RB4;
    _lastB = PORTBbits.RB5;
}
