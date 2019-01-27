#include "Remote.h"

// a=(1/fosc)×192
// 1a = (1/455000) * 192 = 421us
// 2a = 842us
// 3a = 1263us
// 4a = 1684us

void start_receive(void)
{    
    ir_input = 0;
    
    // Wacht 1.5a
    __delay_us(631);
    for (int i = 0; i < 12; i++) {
        ir_input = (ir_input << 1) | !PORTBbits.RB0;
        // Wacht 2a
        __delay_us(842);
    }

    handle_remote();
}


void handle_remote()
{
    char found = 0;
    
    unsigned int mask = 0b0000000111111111; // First 3 = code, last 9 = data;
    
    unsigned int data = ir_input & mask;
        
    switch (data) {
        case 72: // INPUT1
            _selectedInput = 0;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 264: // INPUT2
            _selectedInput = 1;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 160: // INPUT3
            _selectedInput = 2;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 136: // INPUT4
            _selectedInput = 3;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 288: // VOL+
            volume++;
            found = 1;
            break;
        case 272: // VOL-
            volume--;
            found = 1;
            break;
    }

    ir_input = 0;    
    
}