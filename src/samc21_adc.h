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
#include "Arduino.h"

#include <inttypes.h>
#include <string.h>

typedef void (*samc21_adc_callback)(int32_t);

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

enum samc21_adc_mux_pos
{
    SAMC21_ADC_MUXPOS_0       = 0x00,
    SAMC21_ADC_MUXPOS_1       = 0x01,
    SAMC21_ADC_MUXPOS_2       = 0x02,
    SAMC21_ADC_MUXPOS_3       = 0x03,
    SAMC21_ADC_MUXPOS_4       = 0x04,
    SAMC21_ADC_MUXPOS_5       = 0x05,
    SAMC21_ADC_MUXPOS_6       = 0x06,
    SAMC21_ADC_MUXPOS_7       = 0x07,
    SAMC21_ADC_MUXPOS_8       = 0x08,
    SAMC21_ADC_MUXPOS_9       = 0x09,
    SAMC21_ADC_MUXPOS_10      = 0x0A,
    SAMC21_ADC_MUXPOS_11      = 0x0B,
    SAMC21_ADC_MUXPOS_BANDGAP = 0x19,
    SAMC21_ADC_MUXPOS_DAC     = 0x1C,
};


enum samc21_adc_mux_neg
{
    SAMC21_ADC_MUXNEG_0   = 0x00,
    SAMC21_ADC_MUXNEG_1   = 0x01,
    SAMC21_ADC_MUXNEG_2   = 0x02,
    SAMC21_ADC_MUXNEG_3   = 0x03,
    SAMC21_ADC_MUXNEG_4   = 0x04,
    SAMC21_ADC_MUXNEG_5   = 0x05,
    SAMC21_ADC_MUXNEG_GND = 0x18,
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

    /**
    * @brief Sets the mux and sets up the pin
    * 
    * @param pos The positive pin
    * @param neg The negative pin
    *
    * @return void
    */
    void mux(samc21_adc_mux_pos pos = SAMC21_ADC_MUXPOS_0, samc21_adc_mux_neg neg = SAMC21_ADC_MUXNEG_GND);

    /**
    * @brief Blocking read of the pin
    * 
    * @param pos The positive pin
    * @param neg The negative pin
    *
    * @return void
    */
    int32_t read(samc21_adc_mux_pos pos = SAMC21_ADC_MUXPOS_0, samc21_adc_mux_neg neg = SAMC21_ADC_MUXNEG_GND);

    /**
    * @brief Gets the current reading
    * 
    * @return The current reading
    */
    int32_t value(void);

    /**
    * @brief Sets the callback function
    * 
    * @param cb The callback function
    * 
    * @return The current reading
    */
    void callback(samc21_adc_callback cb)
    {
        _callback = cb;
        _enable_irq();
    }
    
    
private:
    Adc* _adc;             //!< ADC Pointer
    volatile bool _new;    //!< Flag to say we have a new reading
    volatile int32_t _val; //!< The value of the last ADC read
    samc21_adc_callback _callback; //!< The callback function

    void _sync_adc(void);


    void _enable_irq() {
        IRQn_Type irq = ADC0_IRQn;
        if (_adc != NULL) {
            if (_adc == ADC0) {
                irq = ADC0_IRQn;
            } else if (_adc == ADC1) {
                irq = ADC1_IRQn;
            }
            NVIC_DisableIRQ(irq);
            NVIC_ClearPendingIRQ(irq);
            NVIC_SetPriority(irq, 1);
            NVIC_EnableIRQ(irq);

            _sync_adc();
            _adc->INTENSET.reg = ADC_INTENSET_RESRDY;
        }
    };
    
    bool _wait(uint32_t timeout = 100)
    {
        unsigned long late = millis() + timeout;
        do {
            // Only retrieve the value if the interrupt is not enabled.
            if (_adc->INTENSET.bit.RESRDY == 0) {
                value();
            }
        } while (!_new and (millis() < late));
        return _new;
    }
    
};


#endif //define _SAMC_ADC_H_
