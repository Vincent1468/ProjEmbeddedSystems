#ifndef SELECTEDRELAY
#define SELECTEDRELAY
void activateSelectedRelay()
{    if (!_inputUpdateRequired) return;
    
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

#endif