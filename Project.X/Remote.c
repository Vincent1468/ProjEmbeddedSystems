#include "Remote.h"

// a=(1/fosc)×192
// 1a = (1/455000) * 192 = 421,978us  +/- 422
// 1,5a = 633us
// 2a = 844us
// 3a = 1266us
// 4a = 1688us
// 60a = 25,31868ms
// 80a = 33,758ms
// 128a = 54,013ms 

void start_receive(void)
{    
    ir_input = 0;
    
    // Wacht 3a 
    __delay_us(633);
    for (int i = 0; i < 12; i++) {
        ir_input = (ir_input << 1) | !PORTBbits.RB0;
        // Wacht 4a
        __delay_us(1266);
    }

    handle_remote();
}


void handle_remote()
{
    char found = 0;

    switch (ir_input) {
        case 0x0665: // INPUT1 
            _selectedInput = 0;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 0x06A3: // INPUT2 
            _selectedInput = 1;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 0x0669: // INPUT3 
            _selectedInput = 2;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 0x0663: // INPUT4
            _selectedInput = 3;
            _inputUpdateRequired = 1;
            found = 1;
            break;
        case 0x06A9: // VOL+ 
            volume++;
            found = 1;
            break;
        case 0x06A5: // VOL- 
            volume--;
            found = 1;
            break;
    }

    ir_input = 0;    
    
}