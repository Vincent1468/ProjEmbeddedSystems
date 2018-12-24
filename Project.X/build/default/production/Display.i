# 1 "Display.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "Display.c" 2
# 1 "./Display.h" 1



void white_space(char aantal_spaces);

void write_volume(char volume);

void spiWrite(char data);
# 1 "Display.c" 2


void white_space(char aantal_spaces) {

    for(int kolom = 0; kolom < aantal_spaces; kolom++)
    {
        for(int rij = 0; rij < 5; rij++)
        {
            spiWrite(font[0][rij]);
        }
    }
}



void write_volume(char volume)
{
    if (volume < 10)
    {
        white_space(7);

        for(int x=0; x < 5; x++)
            {
                spiWrite(font[36][x]);
            }


    }

    if (volume >= 10)

        white_space(6);

            for(int x=0; x < 5; x++)
            {
                spiWrite(font[1][x]);
            }

    PORTCbits.RC4 = 1;
}



void spiWrite(char data)
{
    SSPBUF = data;


    while(!SSPSTATbits.BF)
    {

    }


}
