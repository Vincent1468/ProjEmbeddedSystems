#ifndef _DISPLAY_
#define _DISPLAY_
#include <stdio.h> // For sprintf

#include "Globals.h"
#include "Font.h"

char _selectedDisplay;
int lastVolume;
unsigned short lastInput;

void display_init(void);

void update_volume(void);
void update_input(void);

void write_space(int count);
void write_text(char* text);
void write_int(int number);
void write_char(char c);
void write_font(int fontPos);

void display_write_start(void);
void display_write_end(void);

void spiWrite(char data);


#endif