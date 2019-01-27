#ifndef REMOTE_H
#define	REMOTE_H

#include "Globals.h"

unsigned long ir_input = 0;

void start_receive(void);
void handle_remote(void);

#endif	/* REMOTE_H */

