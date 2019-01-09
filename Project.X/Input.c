#include "Input.h"

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

void handle_rotary()
{
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
}