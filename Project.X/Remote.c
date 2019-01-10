#include "Remote.h"

void init_remote()
{
    // Configure timer2 to run at 38kHz
    T2CONbits.TOUTPS = 0b0000; // 1:1 postscale
    T2CONbits.T2CKPS = 0b00; // 1:1 prescaler
    
    PR2 = 25; // Set TMR2 value
    
    
    PIR1bits.TMR2IF = 0; // Clear T2 IF
    PIE1bits.TMR2IE = 1; // Enable T2 interrupt


}

void start_receive(void)
{
    poll_receiver();
    T2CONbits.TMR2ON = 1; // Enable timer 2

}

void poll_receiver()
{
   
    ir_input = ir_input << 1;
    ir_input = ir_input | !PORTBbits.RB0;
    
    receive_count++;
    
    if (receive_count > 24) {
                T2CONbits.TMR2ON = 0; // Enable timer 2
                receive_count = 0;
    }
    
}

void handle_remote()
{
    char found = 0;
    //unsigned int code = ir_input >> 9; // Get the fixed code that the transmitter sends
    
    //if (code != 0b010)
  //      return; // Code not found
 
//    ignore_poll = 1;
    
    
    if (ir_input == 0xC01) {
                    _selectedInput = 0;
            _inputUpdateRequired = 1;
            
            ir_input = 0;
    }
    
    return;
    
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
    if (found) {
        T2CONbits.TMR2ON = 0; // Enable timer 2

        ir_input = 0;    
    }
    
    //ignore_poll = 0;
}
