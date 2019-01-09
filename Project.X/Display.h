#ifndef _DISPLAY_
#define _DISPLAY_
#include <stdio.h> // For sprintf

#include "Globals.h"
#include "Font.h"

char _selectedDisplay;

void display_init();

// BEGIN NIEK CODE
void white_space(char aantal_spaces);

void write_volume(char volume);
// END NIEK CODE

void update_volume();


void write_text(char* text);
void write_char(char c);
void write_font(int fontPos);

void display_write_start();
void display_write_end();

void spiWrite(char data);


#endif