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
#define _XTAL_FREQ 500000                               // Used by the XC8 delay_ms(x) macro

#define INPUT_MAX 3
#define INPUT_MIN 0
/*
#define 0 font[0][5]
#define 1 font[1][5]
#define 2 font[2][5]
#define 3 font[3][5]
#define 4 font[4][5]
#define 5 font[5][5]
#define 6 font[6][5]
#define 7 font[7][5]
#define 8 font[8][5]
#define 9 font[9][5]
*/
const char lookupofz[10][2][5] = {
    {{0}, {0x3E, 0x51, 0x49, 0x45, 0x3E}},  // 0
    {{1}, {0x00, 0x42, 0x7F, 0x40, 0x00}},  // 1
    {{2}, {0x42, 0x61, 0x51, 0x49, 0x46}},  // 2
    {{3}, {0x21, 0x41, 0x45, 0x4B, 0x31}},  // 3
    {{4}, {0x18, 0x14, 0x12, 0x7F, 0x10}},  // 4
    {{5}, {0x27, 0x45, 0x45, 0x45, 0x39}},  // 5
    {{6}, {0x3C, 0x4A, 0x49, 0x49, 0x30}},  // 6
    {{7}, {0x01, 0x71, 0x09, 0x05, 0x03}},  // 7
    {{8}, {0x36, 0x49, 0x49, 0x49, 0x36}},  // 8
    {{9}, {0x06, 0x49, 0x49, 0x29, 0x1E}},  // 9
};

const int font[][5] = {
    {0x3E, 0x51, 0x49, 0x45, 0x3E},// 0
    {0x00, 0x42, 0x7F, 0x40, 0x00},// 1
    {0x42, 0x61, 0x51, 0x49, 0x46},// 2
    {0x21, 0x41, 0x45, 0x4B, 0x31},// 3
    {0x18, 0x14, 0x12, 0x7F, 0x10},// 4
    {0x27, 0x45, 0x45, 0x45, 0x39},// 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30},// 6
    {0x01, 0x71, 0x09, 0x05, 0x03},// 7
    {0x36, 0x49, 0x49, 0x49, 0x36},// 8
    {0x06, 0x49, 0x49, 0x29, 0x1E},// 9
    {0x7E, 0x11, 0x11, 0x11, 0x7E},// A
    {0x7F, 0x49, 0x49, 0x49, 0x36},// B
    {0x3E, 0x41, 0x41, 0x41, 0x22},// C
    {0x7F, 0x41, 0x41, 0x22, 0x1C},// D
    {0x7F, 0x49, 0x49, 0x49, 0x41},// E
    {0x7F, 0x09, 0x09, 0x01, 0x01},// F
    {0x3E, 0x41, 0x41, 0x51, 0x32},// G
    {0x7F, 0x08, 0x08, 0x08, 0x7F},// H
    {0x00, 0x41, 0x7F, 0x41, 0x00},// I
    {0x20, 0x40, 0x41, 0x3F, 0x01},// J
    {0x7F, 0x08, 0x14, 0x22, 0x41},// K
    {0x7F, 0x40, 0x40, 0x40, 0x40},// L
    {0x7F, 0x02, 0x04, 0x02, 0x7F},// M
    {0x7F, 0x04, 0x08, 0x10, 0x7F},// N
    {0x3E, 0x41, 0x41, 0x41, 0x3E},// O
    {0x7F, 0x09, 0x09, 0x09, 0x06},// P
    {0x3E, 0x41, 0x51, 0x21, 0x5E},// Q
    {0x7F, 0x09, 0x19, 0x29, 0x46},// R
    {0x46, 0x49, 0x49, 0x49, 0x31},// S
    {0x01, 0x01, 0x7F, 0x01, 0x01},// T
    {0x3F, 0x40, 0x40, 0x40, 0x3F},// U
    {0x1F, 0x20, 0x40, 0x20, 0x1F},// V
    {0x7F, 0x20, 0x18, 0x20, 0x7F},// W
    {0x63, 0x14, 0x08, 0x14, 0x63},// X
    {0x03, 0x04, 0x78, 0x04, 0x03},// Y
    {0x61, 0x51, 0x49, 0x45, 0x43},// Z
    {0x00, 0x00, 0x00, 0x00, 0x00}, //NOOPES
 }; 


char _inputUpdateRequired;
unsigned short _selectedInput;
unsigned short _lastA, _lastB;

unsigned char data = 0xFF;
char display = 1;

void spiWrite(char);
void white_space(char);
void write_volume(char);
// Set registers and stuff
void config()
{
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


void activateSelectedRelay()
{
    if (!_inputUpdateRequired) return;
    
    PORTA = 0x0F; // Clear port A

    
    switch (_selectedInput) {
        case 0:
            PORTA = ~0x01;
            break;        
        case 1:
            PORTA = ~0x02;
            break;
        case 2:
            PORTA = ~0x04;
            break;
        case 3:
            PORTA = ~0x08;
            break;
        default:
            PORTA = ~0x01; // RA0 (relay 1) default
            break;
    }
    
    _inputUpdateRequired = 0;
}


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
   
    
    while(1){
    PORTCbits.RC7 = 0; // write to dot register
    PORTCbits.RC4 = 0; // set in luistermodus
    write_volume(0);
    
    
    PORTCbits.RC4 = 1;
    __delay_ms(2000);
    
    volume++;
   
    
    }
   
    return;
}

void white_space(char aantal_spaces) {

    for(int kolom = 0; kolom < aantal_spaces; kolom++)
    {
        for(int rij = 0; rij < 5; rij++)
        {  
            spiWrite(font[0][rij]);
        }
    } 
}

void write_volume(char volume)
{
    if (volume < 10)
    {
        white_space(7);
        
        for(int x=0; x < 5; x++)
            {  
                spiWrite(font[36][x]);
            }
        
        // PORTCbits.RC4 = 1; // latch naar register
    }
    
    if (volume >= 10)
        
        white_space(6);
               
            for(int x=0; x < 5; x++)
            {  
                spiWrite(lookupofz[volume][volume][x]);
            }
    
    PORTCbits.RC4 = 1; // latch naar register
}

void spiWrite(char data) // Write data to SPI bus
{
    SSPBUF = data; // write var data todisplay
    
    
    while(!SSPSTATbits.BF) // check if register is empty from bits
    {
    
    }
    
    
}