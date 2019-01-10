#ifndef REMOTE_H
#define	REMOTE_H

#include "Globals.h"

unsigned long ir_input = 0;
char ignore_poll = 0;

void init_remote(void);

void poll_receiver(void);

void handle_remote(void);

#endif	/* REMOTE_H */

