/**
 * @file
 * @author     Scott Price <prices@hugllc.com>
 * @copyright  © 2017 Hunt Utilities Group, LLC
 * @brief      The main class for HUGnetCANLib.
 * @details
 */

#include "samc21_adc.h"
#include "Arduino.h"

#ifndef ADC_INPUTCTRL_MUXNEG_GND
#define ADC_INPUTCTRL_MUXNEG_GND (0x18ul << ADC_INPUTCTRL_MUXNEG_Pos)
#endif

SAMC21_ADC::SAMC21_ADC(Adc* Conv)
: _adc(Conv)
{
};

uint8_t SAMC21_ADC::begin(samc21_adc_ref vref)
{
    uint32_t biasrefbuf = 0;
    uint32_t biascomp = 0;
    if (_adc != NULL) {
        if (_adc == ADC0) {
            MCLK->APBCMASK.reg |= MCLK_APBCMASK_ADC0;
            biasrefbuf = (*((uint32_t *) ADC0_FUSES_BIASREFBUF_ADDR) & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;
            biascomp   = (*((uint32_t *) ADC0_FUSES_BIASCOMP_ADDR) & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
        } else if (_adc == ADC1) {
            MCLK->APBCMASK.reg |= MCLK_APBCMASK_ADC1;
            biasrefbuf = (*((uint32_t *) ADC1_FUSES_BIASREFBUF_ADDR) & ADC1_FUSES_BIASREFBUF_Msk) >> ADC1_FUSES_BIASREFBUF_Pos;
            biascomp   = (*((uint32_t *) ADC1_FUSES_BIASCOMP_ADDR) & ADC1_FUSES_BIASCOMP_Msk) >> ADC1_FUSES_BIASCOMP_Pos;
        }
    
        _adc->CALIB.reg = ADC_CALIB_BIASREFBUF(biasrefbuf) | ADC_CALIB_BIASCOMP(biascomp);

        _adc->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV256;
        _adc->CTRLC.reg = ADC_CTRLC_RESSEL_12BIT | ADC_CTRLC_R2R;

        _adc->SAMPCTRL.reg = (ADC_SAMPCTRL_SAMPLEN(0x0) | ADC_SAMPCTRL_OFFCOMP);
        _sync();

        _adc->INPUTCTRL.reg = ADC_INPUTCTRL_MUXNEG_GND;
        _sync();

        average();
        ref(vref);
    } else {
        return 1;
    }

    return 0;
};

void SAMC21_ADC::average(samc21_adc_avg_samples samples, samc21_adc_avg_divisor div)
{
    _sync();
    _adc->AVGCTRL.reg = samples | div;
}

void SAMC21_ADC::ref(samc21_adc_ref vref)
{
    _sync();
    switch (vref) {
        case 0:
        case 2:
        case 3:
            SUPC->VREF.reg &= ~SUPC_VREF_SEL_Msk;
            SUPC->VREF.reg |= SUPC_VREF_SEL(vref);
            _adc->REFCTRL.reg &= ~ADC_REFCTRL_REFSEL_Msk;
    }
};


/**
 * This synchronizes the clocks.
 * 
 * @return void
 */
void SAMC21_ADC::_sync(void)
{
  while ( _adc->SYNCBUSY.reg & ADC_SYNCBUSY_MASK );
}

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
