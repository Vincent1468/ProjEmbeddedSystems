#ifndef WHITESPACE
#define WHITESPACE

void white_space(char aantal_spaces) {

    for(int kolom = 0; kolom < aantal_spaces; kolom++)
    {
        for(int rij = 0; rij < 5; rij++)
        {  
            spiWrite(font[0][rij]);
        }
    } 
}

#endif