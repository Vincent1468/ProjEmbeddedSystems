#ifndef VOLUME_H
#define	VOLUME_H
#include "Globals.h"

const int step_size = MAX_ADC / VOL_STEPS;
unsigned int _lastAdcResult;

void init_adc(void);

void update_vol_motor(void);

void handle_potmeter(void);
int get_volume(unsigned int);

int is_deadzone(int currentStep, int adcResult);

#endif	/* VOLUME_H */

