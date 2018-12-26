#ifndef _DISPLAY_
#define _DISPLAY_

#define _XTAL_FREQ 500000 
extern const int font[][5]; 

void white_space(char aantal_spaces);

void write_volume(char volume);

void spiWrite(char data);

#endif