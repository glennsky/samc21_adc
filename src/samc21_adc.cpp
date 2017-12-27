/**
 * @file
 * @author     Scott Price <prices@hugllc.com>
 * @copyright  © 2017 Hunt Utilities Group, LLC
 * @brief      The main class for HUGnetCANLib.
 * @details
 */

#include "samc21_adc.h"
#include "Arduino.h"

SAMC21_ADC *use_object;


/**
* @brief Checks for the presence of a connector id
*
* This function never returns if there is no connector id.
*
* @return void
*/
SAMC21_ADC::SAMC21_ADC(Adc* Conv)
: _adc(Conv)
{
};

uint8_t SAMC21_ADC::begin(uint8_t idmodeset, uint32_t speedset, uint8_t clockset)
{
    
    
};
void ADC0_Handler(void)
{
}


void ADC1_Handler(void)
{
}

void ADC2_Handler(void)
{
}
