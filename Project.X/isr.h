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
    