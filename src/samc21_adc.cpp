/**
 * @file
 * @author     Scott Price <prices@hugllc.com>
 * @copyright  © 2017 Hunt Utilities Group, LLC
 * @brief      The main class for HUGnetCANLib.
 * @details
 */

#include "samc21_adc.h"
#include "Arduino.h"

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

uint8_t SAMC21_ADC::begin(void)
{
    
    return 0;
};
/**
 * The handler for ADC0
 * 
 * @return void
 */
void ADC0_Handler(void)
{
}


/**
 * The handler for ADC1
 * 
 * @return void
 */
void ADC1_Handler(void)
{
}

/**
 * The handler for SDADC
 * 
 * @return void
 */
void SDADC_Handler(void)
{
}
