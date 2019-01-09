#ifndef REMOTE_H
#define	REMOTE_H

#include "Globals.h"

unsigned int ir_input = 0;
char ignore_poll = 0;

void init_remote();

void poll_receiver();

void handle_remote();

#endif	/* REMOTE_H */

