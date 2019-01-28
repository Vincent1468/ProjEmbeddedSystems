#include "Display.h"

void display_init()
{
    // SPI config
    // TODO: Explain what these mean
    SSPCON = 0b00100000;
    SSPSTAT = 0b01000000;
    
    // Set display ports as OUTPUT
    TRISD = 0x00;
    TRISC = 0x00;
    
    //DISPLAY 1
    PORTDbits.RD2 = 1; // set reset display on logic 1
    PORTDbits.RD6 = 0; // set blank display 1 on logic 1 is for brightness
    PORTDbits.RD4 = 1; // chip enable display 1 logic low to write data
    PORTCbits.RC3 = 0; // sck?? is de clock, is laag dan wordt data gelatcht
    
    // Set control word 1
    PORTDbits.RD7 = 1; // select control register
    PORTDbits.RD4 = 0; // chip enable @luisteren@
    spiWrite(0b01001111); // control word 0, wake up from sleep and set brightness
    PORTDbits.RD4 = 1;  // latch control word to register
 
    // Set control word 2
    PORTDbits.RD7 = 1; // select control register
    PORTDbits.RD4 = 0; // chip enable @luisteren@ 
    spiWrite(0b10000011); // control word 1, wake up from sleep and set brightness
    PORTDbits.RD4 = 1;  // latch control word to register
    
    
    // Display 1 config done! Back to dot register
    PORTDbits.RD7 = 0; // select dot register

    
    // DISPLAY 2     
    PORTCbits.RC2 = 1; // set reset display on logic 1
    PORTCbits.RC6 = 0; // set blank display 1 on logic 1 is for brightness
    PORTCbits.RC4 = 1; // chip enable display 1 logic low to write data
    PORTCbits.RC3 = 0; // sck?? is de clock, is laag dan wordt data gelatcht
    
    PORTCbits.RC7 = 1; // select control register
    PORTCbits.RC4 = 0; // chip enable @luisteren@
    spiWrite(0b01001111); // control word 0, wake up from sleep and set brightness
    
    PORTCbits.RC4 = 1;  // latch control word to register
    
    PORTCbits.RC7 = 1; // select control register
    PORTCbits.RC4 = 0; // chip enable @luisteren@
   
    spiWrite(0b10000011); // control word 1, wake up from sleep and set brightness
    PORTCbits.RC4 = 1;  // latch control word to register
    
    // Display 2 config done! Back to dot register
    PORTCbits.RC7 = 0; // select dot register
    
    
    _selectedDisplay = 0; // Default to display 1
    lastVolume = 99; // Set to high number
    lastInput = 99;
    
}

void update_input(void)
{
    if (lastInput == _selectedInput) return; // Do not update if no change
    
    _selectedDisplay = 0; // Display 1
    display_write_start();

    write_text("INPUT");
        
    write_space(2);

    write_int(_selectedInput+1); // Plus 1 because the input is zero-based
    display_write_end();    

    lastInput = _selectedInput;
    
}

void update_volume()
{
    if (lastVolume == volume) return; // Do not update if no change
  
    _selectedDisplay = 0; // Display 0
    display_write_start();

    write_text("VOL"); // First 3
    
    // Determine the amount of spaces    
    int spaces = 3;
    if (volume < 10)
        spaces = 4;
    
    // Write spaces
    write_space(spaces);
  
    write_int(volume);
    display_write_end();    

    lastVolume = volume;
   
}

void write_space(int count)
{
    for (int i = 0; i < count; i++) {        

        for (int x = 0; x < 5; x++) {
            
            spiWrite(0x00);
            
        }
    }   
}

void write_text(char* text) 
{
    char* c;
    
    for (c = text; *c != '\0'; c++) {        
        write_char(*c);        
    }
    
}

void write_int(int number)
{
    if (number < 10) {
        write_char(number + 48);
        return;
    }
    
    char num[2];
    sprintf(num, "%d", number);

    write_text(num);  
}

void write_char(char c)
{
    int pos;
    
    // Is number? (ASCII 48 - 57)
    if (c >= 48 && c <= 57) {
        pos = c - 48; // Calculate font position based on ASCII numbering
        write_font(pos);
    } else if (c >= 65 && c <= 90) { // Is it a capital letter? (ASCII 65 - 90)
        pos = (c - 65) + 10; // Add 10, because the letters in the font start at index 10
        write_font(pos);
    } else if (c >= 97 && c <= 122) { // Is it a lowercase letter? (ASCII 97 - 122)
        pos = (c - 97) + 10; // Add 10, because the letters in the font start at index 10
        write_font(pos);
    } else {
        // Special char etc 
        // Can be implemented here
    }
}

void write_font(int fontPos)
{
    for(int x=0; x < 5; x++){
        spiWrite(font[fontPos][x]);  
    }     
}

// Set the selected display in listen mode
void display_write_start()
{
    if (_selectedDisplay == 0) {
        PORTCbits.RC4 = 0; // Set display 1 in listen mode
        return;
    }
    
    PORTDbits.RD4 = 0; // Set display 2 in listen mode
}

// Latch the data
void display_write_end()
{
    if (_selectedDisplay == 0) {
        PORTCbits.RC4 = 1; // Latch data display 1
        return;
    }
    
    PORTDbits.RD4 = 1; // Latch data display 2    
}

// Write data to SPI bus
void spiWrite(char data) 
{
    SSPBUF = data; // write var data todisplay
      
    while(!SSPSTATbits.BF); // check if register is empty from bits 
}
