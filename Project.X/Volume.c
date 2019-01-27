#include "Volume.h"

void init_adc()
{
    ADCON0bits.CHS = 0b0111; // Enable AN7 for ADC
    ADCON0bits.ADCS = 0b001; // Focs / 8 (Datasheet table 9-1)
    ADCON1bits.ADFM = 1; // Right justify AD result
    
    PIR1bits.ADIF = 0; // Clear AD interrupt flag
    PIE1bits.ADIE = 1; // Enable ADC interrupts
    
    ADCON0bits.ADON = 1; // Enable ADC module
}

/*
 * Check if we're in a deadzone
 */
int is_deadzone(int currentStep, int adcResult) 
{    
    int turnPoint = step_size * currentStep;    // Calculate the turning point
        
    int deadzoneLow = turnPoint - DEADZONE;     // Calculate low point
    int deadzoneHigh = turnPoint + DEADZONE;    // Calculate high point
        
    return adcResult > deadzoneLow && adcResult < deadzoneHigh; // Return true if in deadzone     
}

void handle_potmeter()
{
    unsigned int ad_result = (ADRESH << 8) + ADRESL;    
 
    if (ad_result == _lastAdcResult)
        return;
            
    if (ad_result == 0 || ad_result < step_size) { // If ADC is 0 OR result < 1 step, set ledCount to 0
            volume = 0;
    } else {
        unsigned int currentStep = ad_result / step_size; // Calculate the current step
            
        if (!is_deadzone(currentStep, ad_result))  // if NOT in a deadzone
            volume = currentStep;     // Set the ledCount
    }
    
    _lastAdcResult = ad_result;
    
}



