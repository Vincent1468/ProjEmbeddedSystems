#ifndef VOLUME_H
#define	VOLUME_H
#include "Globals.h"

void init_adc();

void handle_potmeter();

int is_deadzone(int currentStep, int adcResult);

#endif	/* VOLUME_H */

