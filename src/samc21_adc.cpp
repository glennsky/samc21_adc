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

SAMC21_ADC *samc21_adc_obj[3] = {NULL, NULL, NULL};

const uint8_t ADC0_pins[]  = {2, 3, 8, 9, 4, 5, 6, 7, 8, 9,10,11};
const uint8_t ADC0_group[] = {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
const uint8_t ADC1_pins[]  = {0, 1, 2, 3, 8, 9, 4, 5, 6, 7, 8, 9};
const uint8_t ADC1_group[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};

SAMC21_ADC::SAMC21_ADC(Adc* Conv)
: _adc(Conv), _new(false), _val(INT32_MIN)
{
};

uint8_t SAMC21_ADC::begin(samc21_adc_ref vref)
{
    uint32_t biasrefbuf = 0;
    uint32_t biascomp = 0;
    
    if (_adc != NULL) {

        _sync();
        _adc->CTRLA.bit.SWRST;

        if (_adc == ADC0) {
            MCLK->APBCMASK.reg |= MCLK_APBCMASK_ADC0;
            biasrefbuf = (*((uint32_t *) ADC0_FUSES_BIASREFBUF_ADDR) & ADC0_FUSES_BIASREFBUF_Msk) >> ADC0_FUSES_BIASREFBUF_Pos;
            biascomp   = (*((uint32_t *) ADC0_FUSES_BIASCOMP_ADDR) & ADC0_FUSES_BIASCOMP_Msk) >> ADC0_FUSES_BIASCOMP_Pos;
            samc21_adc_obj[0] = this;
        } else if (_adc == ADC1) {
            MCLK->APBCMASK.reg |= MCLK_APBCMASK_ADC1;
            biasrefbuf = (*((uint32_t *) ADC1_FUSES_BIASREFBUF_ADDR) & ADC1_FUSES_BIASREFBUF_Msk) >> ADC1_FUSES_BIASREFBUF_Pos;
            biascomp   = (*((uint32_t *) ADC1_FUSES_BIASCOMP_ADDR) & ADC1_FUSES_BIASCOMP_Msk) >> ADC1_FUSES_BIASCOMP_Pos;
            samc21_adc_obj[1] = this;
        }
        
        _sync();
        _adc->CTRLA.bit.ENABLE = 1;             // Enable ADC
        _sync();
        _adc->CALIB.reg = ADC_CALIB_BIASREFBUF(biasrefbuf) | ADC_CALIB_BIASCOMP(biascomp);

        _adc->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV256;
        _adc->CTRLC.reg = ADC_CTRLC_RESSEL_12BIT | ADC_CTRLC_R2R;

        _sync();
        _adc->SAMPCTRL.reg = (ADC_SAMPCTRL_SAMPLEN(0x0) | ADC_SAMPCTRL_OFFCOMP);

        mux();
        average();
        ref(vref);

        _enable_irq();
        
    } else {
        return 1;
    }

    return 0;
};

void SAMC21_ADC::average(samc21_adc_avg_samples samples, samc21_adc_avg_divisor div)
{
    if (_adc != NULL) {
        _sync();
        _adc->AVGCTRL.reg = samples | div;
    }
}

void SAMC21_ADC::ref(samc21_adc_ref vref)
{
    if (_adc != NULL) {
        _sync();
        switch (vref) {
            case 0:
            case 2:
            case 3:
                SUPC->VREF.reg &= ~SUPC_VREF_SEL_Msk;
                SUPC->VREF.reg |= SUPC_VREF_SEL(vref);
                _adc->REFCTRL.reg &= ~ADC_REFCTRL_REFSEL_Msk;
        }
    }
};
void SAMC21_ADC::mux(samc21_adc_mux_pos pos, samc21_adc_mux_neg neg)
{
    if (_adc != NULL) {
        _sync();
        _adc->INPUTCTRL.bit.MUXPOS = pos;
        _adc->INPUTCTRL.bit.MUXNEG = neg;
        uint8_t pgroup = 0xFF, ngroup = 0xFF;
        uint8_t ppin = 0xFF, npin = 0xFF;
        uint8_t mux;
        if (_adc == ADC0) {
            if (pos < sizeof(ADC0_pins)) {
                ppin   = ADC0_pins[pos];
                pgroup = ADC0_group[pos];
            }
            if (neg < sizeof(ADC0_pins)) {
                npin   = ADC0_pins[neg];
                ngroup = ADC0_group[neg];
            }
        } else if (_adc == ADC1) {
            if (pos < sizeof(ADC1_pins)) {
                ppin   = ADC1_pins[pos];
                pgroup = ADC1_group[pos];
            }
            if (neg < sizeof(ADC1_pins)) {
                npin   = ADC1_pins[neg];
                ngroup = ADC1_group[neg];
            }
        }
        if (ppin != 0xFF) {
            PORT->Group[pgroup].DIRCLR.reg = 1<<ppin;
            PORT->Group[pgroup].PINCFG[ppin].reg = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
            mux = PORT->Group[pgroup].PMUX[ppin / 2].reg;
            if (ppin%2 == 0) {
                // Even pin 
                mux &= PORT_PMUX_PMUXO(0xF);
            } else {
                // Odd pin
                mux &= PORT_PMUX_PMUXE(0xF);
            }
            PORT->Group[pgroup].PMUX[ppin / 2].reg = mux;
        }
        if (npin != 0xFF) {
            PORT->Group[ngroup].DIRCLR.reg = 1<<npin;
            PORT->Group[ngroup].PINCFG[npin].reg = PORT_PINCFG_INEN | PORT_PINCFG_PMUXEN;
            mux = PORT->Group[ngroup].PMUX[npin / 2].reg;
            if (npin%2 == 0) {
                // Even pin AND off the even part (mux setting 0)
                mux &= ~PORT_PMUX_PMUXE(0xF);
            } else {
                // Odd pin AND off the odd part (mux setting 0)
                mux &= ~PORT_PMUX_PMUXO(0xF);
            }
            PORT->Group[ngroup].PMUX[npin / 2].reg = mux;
        }
    }
}
int32_t SAMC21_ADC::read(samc21_adc_mux_pos pos, samc21_adc_mux_neg neg)
{
    if (_adc != NULL) {
        mux(pos, neg);

        _sync();
        _adc->SWTRIG.bit.START = 1;

        // Clear the Data Ready flag
        _adc->INTFLAG.reg = ADC_INTFLAG_RESRDY;

        // Start conversion again, since The first conversion after the reference is changed must not be used.
        _sync();
        _adc->SWTRIG.bit.START = 1;

        // Store the value
        //while (_adc->INTFLAG.bit.RESRDY == 0);   // Waiting for conversion to complete
    //    value((int32_t)_adc->RESULT.reg);
    
        while (!_new);
        
        return value();
    }
    return INT32_MIN;
}

void SAMC21_ADC::value(int32_t val)
{
    _val = val;
    _new = true;
}

int32_t SAMC21_ADC::value(void)
{
    _new = false;
    return _val;
}


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
    if ((samc21_adc_obj[0] != NULL) && ADC0->INTFLAG.bit.RESRDY) {
        samc21_adc_obj[0]->value((int32_t)ADC0->RESULT.reg);
    }
    ADC0->INTFLAG.reg = ADC0->INTFLAG.reg;
}


/**
 * The handler for ADC1
 * 
 * @return void
 */
void ADC1_Handler(void)
{
    if ((samc21_adc_obj[1] != NULL) && ADC1->INTFLAG.bit.RESRDY) {
        samc21_adc_obj[1]->value((int32_t)ADC1->RESULT.reg);
    }
    ADC1->INTFLAG.reg = ADC1->INTFLAG.reg;
}

/**
 * The handler for SDADC
 * 
 * @return void
 */
void SDADC_Handler(void)
{
}
