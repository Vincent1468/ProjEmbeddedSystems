#ifndef CONFIG
#define CONFIG

void config()
{
        char _inputUpdateRequired;
        unsigned short _selectedInput;
        unsigned short _lastA, _lastB;

        unsigned char data = 0xFF;
        char display = 1;

        void spiWrite(char);
        void white_space(char);
        void write_volume(char);
        
    OSCCON = 0b00111000;      // 500KHz clock speed, change if needed

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
    TRISEbits.TRISE0 = 1; // Set potmeter as input
    ANSELbits.ANS5 = 1; // ANALOG input
    
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
    
    
    
    // PORTD = 0x00; // Set all display to OFF
    //PORTC = 0x00; // ^
    
    
    //
    // INTERRUPTS
    //   
    
    INTCONbits.RBIE = 1; // Enable PORTB interrupts

    IOCBbits.IOCB4 = 1; // Enable interrupt on RB4
    IOCBbits.IOCB5 = 1; // Enable interrupt on RB5
    
    INTCONbits.GIE = 1; // Enable global interrupts


    
    //
    // Default values
    //
    
    _inputUpdateRequired = 1;
    _selectedInput = 0;
    _lastA = PORTBbits.RB4;
    _lastB = PORTBbits.RB5;
}

#endif