#ifndef VOLUME_H
#define	VOLUME_H
#include "Globals.h"

const int step_size = MAX_ADC / VOL_STEPS;
unsigned int _lastAdcResult;

void init_adc(void);

void handle_potmeter(void);

int is_deadzone(int currentStep, int adcResult);

#endif	/* VOLUME_H */

