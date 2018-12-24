#ifndef _CONFIG_
#define _CONFIG_


extern char _inputUpdateRequired;
extern unsigned short _selectedInput;
extern unsigned short _lastA, _lastB;

extern unsigned char data;
extern char display;

extern void spiWrite(char);
extern void white_space(char);
extern void write_volume(char);
        
void config(void);

#endif