/**
 * @file
 * @author     Scott Price <prices@hugllc.com>
 * @copyright  © 2017 Hunt Utilities Group, LLC
 * @brief      The include file for using the SAMC
 * @details
 */
#ifndef _SAMC_ADC_H_
#define _SAMC_ADC_H_

#include "sam.h"

#include <inttypes.h>
#include <string.h>


class SAMC21_ADC
{

public:
    /**
    * @brief Checks for the presence of a connector id
    *
    * This function never returns if there is no connector id.
    *
    * @return void
    */
    SAMC21_ADC(Adc *Conv);
    uint8_t begin();

private:
    Adc* _adc;
    
};


#endif //define _SAMC_ADC_H_