/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "currentCalculation.h"

//Nedenstående funktioner er taget fra BatteriDriver, sat til 30000 samples og tilpasset to andre Current Hall Sensor
//Sensorne er tilsluttet så strømmen løber fra minus til plus fra solcellen gennem sensoren
//Da vi nu skal bruge at strømmen løber den ene vej, og derved kan sparre at skulle bruge externe referance for større måleområde

float currentWAM()
{
    float sum = 0;
    
    for (int i = 0; i < 30000; i++)
    {
        int16_t result = ADC_SAR_1_CountsTo_mVolts(ADC_SAR_1_GetResult16());
        float convToAmps = ((result-2500)/0.3339);  
        
        sum = sum + convToAmps;
    }
    return -(sum/30000);
}
float currentSolar()
{
    float sum = 0;
    
    for (int i = 0; i < 30000; i++)
    {
        int16_t result = ADC_SAR_2_CountsTo_mVolts(ADC_SAR_2_GetResult16());
        float convToAmps = ((result-2500)/0.3339);
        
        sum = sum + convToAmps;
    }
    return -(sum/30000);
}
/* [] END OF FILE */
