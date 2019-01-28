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

void update_vol_motor()
{
    if (!vol_motor) return;
    
    // Motor left: RC0 (min))
    // Motor right: RC1 (plus)
    
    // while AD result != volume
   
    GIE = 0;
    
    int curPotmeterVol = VOL_STEPS+1; // Init to a value that is impossible to reach
     

    while (volume != curPotmeterVol) {
        ADCON0bits.GO = 1; // Start ADC
        while (ADCON0bits.GO); // Wait for ADC to complete
        unsigned int ad_result = (ADRESH << 8) + ADRESL;   
        
        curPotmeterVol = get_volume(ad_result);
        
        if (curPotmeterVol < 0) continue;
        
        if (volume > curPotmeterVol) { // Min
            PORTCbits.RC0 = 1;
            PORTCbits.RC1 = 0;
        } else if (volume < curPotmeterVol) { // Plus
            PORTCbits.RC0 = 0;
            PORTCbits.RC1 = 1;
        }
    }
    
    vol_motor = 0;
    RC0 = RC1 = 0;
    GIE = 1;
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
    
    
    int newVol = get_volume(ad_result);
    
    
    
    if (newVol >= 0) {
        volume = newVol;
 
    }
    _lastAdcResult = ad_result;
}

int get_volume(unsigned int ad_result)
{            
    if (ad_result == 0 || ad_result < step_size) { // If ADC is 0 OR result < 1 step, set ledCount to 0
            return 0;
    } else {
        unsigned int currentStep = ad_result / step_size; // Calculate the current step
            
        if (!is_deadzone(currentStep, ad_result))  // if NOT in a deadzone
            return currentStep;     // Set the ledCount
    }
    
    return -1; // In deadzone, ignore
}