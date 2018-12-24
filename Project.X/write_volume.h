#ifndef WRITEVOLUME
#define WRITEVOLUME

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
                spiWrite(font[1][x]);
            }
    
    PORTCbits.RC4 = 1; // latch naar register
}

#endif