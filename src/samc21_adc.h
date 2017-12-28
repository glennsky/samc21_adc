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

enum samc21_adc_ref
{
    SAMC21_ADC_REF_1024 = 0,
    SAMC21_ADC_REF_2048 = 2,
    SAMC21_ADC_REF_4096 = 3,
};

enum samc21_adc_avg_samples
{
    SAMC21_ADC_AVGSAMPLES_1    = ADC_AVGCTRL_SAMPLENUM_1,
    SAMC21_ADC_AVGSAMPLES_2    = ADC_AVGCTRL_SAMPLENUM_2,
    SAMC21_ADC_AVGSAMPLES_4    = ADC_AVGCTRL_SAMPLENUM_4,
    SAMC21_ADC_AVGSAMPLES_8    = ADC_AVGCTRL_SAMPLENUM_8,
    SAMC21_ADC_AVGSAMPLES_16   = ADC_AVGCTRL_SAMPLENUM_16,
    SAMC21_ADC_AVGSAMPLES_32   = ADC_AVGCTRL_SAMPLENUM_32,
    SAMC21_ADC_AVGSAMPLES_64   = ADC_AVGCTRL_SAMPLENUM_64,
    SAMC21_ADC_AVGSAMPLES_128  = ADC_AVGCTRL_SAMPLENUM_128,
    SAMC21_ADC_AVGSAMPLES_256  = ADC_AVGCTRL_SAMPLENUM_256,
    SAMC21_ADC_AVGSAMPLES_512  = ADC_AVGCTRL_SAMPLENUM_512,
    SAMC21_ADC_AVGSAMPLES_1024 = ADC_AVGCTRL_SAMPLENUM_1024,
};

enum samc21_adc_avg_divisor
{
    SAMC21_ADC_AVGDIV_1   = ADC_AVGCTRL_ADJRES(0),
    SAMC21_ADC_AVGDIV_2   = ADC_AVGCTRL_ADJRES(1),
    SAMC21_ADC_AVGDIV_4   = ADC_AVGCTRL_ADJRES(2),
    SAMC21_ADC_AVGDIV_8   = ADC_AVGCTRL_ADJRES(3),
    SAMC21_ADC_AVGDIV_16  = ADC_AVGCTRL_ADJRES(4),
    SAMC21_ADC_AVGDIV_32  = ADC_AVGCTRL_ADJRES(5),
    SAMC21_ADC_AVGDIV_64  = ADC_AVGCTRL_ADJRES(6),
    SAMC21_ADC_AVGDIV_128 = ADC_AVGCTRL_ADJRES(7),
};

class SAMC21_ADC
{

public:
    /**
    * @brief Creates the ADC object.
    * 
    * @param *Conv The ADC pointer to use.  Should be ADC0 or ADC1.
    *
    * @return void
    */
    SAMC21_ADC(Adc *Conv);
    /**
    * @brief Sets up the ADC
    * 
    * @param *Conv The ADC pointer to use.  Should be ADC0 or ADC1.
    *
    * @return void
    */
    uint8_t begin(samc21_adc_ref vref = SAMC21_ADC_REF_1024);
    /**
    * @brief Sets the reference
    * 
    * @param vref The reference to use.
    *
    * @return void
    */
    void ref(samc21_adc_ref vref);
    /**
    * @brief Sets the averager
    * 
    * @param samples The number of samples.
    * @param div     The divisor.
    *
    * @return void
    */
    void average(samc21_adc_avg_samples samples = SAMC21_ADC_AVGSAMPLES_1, samc21_adc_avg_divisor div = SAMC21_ADC_AVGDIV_1);


private:
    Adc* _adc;
    
    void _sync(void);

};


#endif //define _SAMC_ADC_H_