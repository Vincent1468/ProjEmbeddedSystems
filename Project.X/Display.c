#include "Display.h"
#include <xc.h>
#include "pic16f887.h"
#include "Font.h"

void white_space(char aantal_spaces) {

    for(int kolom = 0; kolom < aantal_spaces; kolom++)
    {
        for(int rij = 0; rij < 5; rij++)
        {  
            spiWrite(font[1][rij]);
        }
      
    } 
}

void write_volume(char volume)
{
    if (volume <= 9)
    {
        white_space(7);
        
        
         
        for(int rij=0; rij < 5; rij++)
            {  
                spiWrite(font[volume][rij]);
            }
        __delay_ms(5);
        // PORTCbits.RC4 = 1; // latch naar register
    }
    
    if (volume >= 10)
        
        white_space(6);
               
            for(int x=0; x < 5; x++)
            {  
                spiWrite(font[1][x]);
            }
    __delay_ms(5);
    
}

void spiWrite(char data) // Write data to SPI bus
{
    SSPBUF = data; // write var data todisplay
      
    while(!SSPSTATbits.BF) // check if register is empty from bits
    {
    
    }
    
    
}
