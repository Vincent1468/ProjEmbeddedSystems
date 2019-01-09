#include "Volume.h"

// RE2 / AN7

void init_adc()
{
    ADCON0bits.CHS = 0b0111; // Enable AN7 for ADC
    ADCON0bits.ADCS = 0b001; // Focs / 8 (Datasheet table 9-1)
    ADCON1bits.ADFM = 1; // Right justify AD result
    
    PIR1bits.ADIF = 0; // Clear AD interrupt flag
    PIE1bits.ADIE = 1; // Enable ADC interrupts
    INTCONbits.PEIE = 1; // Enable peripheral interrupts
    INTCONbits.GIE = 1; // Enable global interrupts
    
    ADCON0bits.ADON = 1; // Enable ADC module
}

/*
 * Check if we're in a deadzone
 */
int is_deadzone(int currentStep, int adcResult) 
{    
    int turnPoint = STEP_SIZE * currentStep;    // Calculate the turning point
        
    int deadzoneLow = turnPoint - DEADZONE;     // Calculate low point
    int deadzoneHigh = turnPoint + DEADZONE;    // Calculate high point
        
    return adcResult > deadzoneLow && adcResult < deadzoneHigh; // Return true if in deadzone     
}

void handle_potmeter()
{
    unsigned int ad_result = (ADRESH << 8) + ADRESL;
    
    if (ad_result == 0 || ad_result < STEP_SIZE) { // If ADC is 0 OR result < 1 step, set ledCount to 0
            volume = 0;
    } else {
        unsigned int currentStep = ad_result / STEP_SIZE; // Calculate the current step
            
        if (!is_deadzone(currentStep))  // if NOT in a deadzone
            volume = currentStep;     // Set the ledCount
    }
    
}



