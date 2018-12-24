#ifndef SPIWRITE
#define SPIWRITE

void spiWrite(char data) // Write data to SPI bus
{
    SSPBUF = data; // write var data todisplay
    
    
    while(!SSPSTATbits.BF) // check if register is empty from bits
    {
    
    }
    
    
}

#endif