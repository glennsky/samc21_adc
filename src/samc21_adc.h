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

#define REF_OFFSET 8
#define SAMC21_ADC_MAX 4095
#define SAMC21_ADC_AVG_MAX 65535

#define DEFAULT_GAIN      0x800
#define DEFAULT_OFFSET    0

class SAMC21_ADC;

typedef void (*samc21_adc_callback)(SAMC21_ADC *, int32_t, uint8_t, void *);

enum samc21_adc_ref {
    SAMC21_ADC_REF_INTVCC0 = 1,
    SAMC21_ADC_REF_INTVCC1 = 2,
    SAMC21_ADC_REF_VREFA   = 3,
    SAMC21_ADC_REF_DAC     = 4,
    SAMC21_ADC_REF_INTVCC2 = 5,
    SAMC21_ADC_REF_1024    = (0 + REF_OFFSET),
    SAMC21_ADC_REF_2048    = (2 + REF_OFFSET),
    SAMC21_ADC_REF_4096    = (3 + REF_OFFSET),
};

enum samc21_adc_avg_samples {
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

enum samc21_adc_avg_divisor {
    SAMC21_ADC_AVGDIV_0   = ADC_AVGCTRL_ADJRES(0),
    SAMC21_ADC_AVGDIV_2   = ADC_AVGCTRL_ADJRES(1),
    SAMC21_ADC_AVGDIV_4   = ADC_AVGCTRL_ADJRES(2),
    SAMC21_ADC_AVGDIV_8   = ADC_AVGCTRL_ADJRES(3),
    SAMC21_ADC_AVGDIV_16  = ADC_AVGCTRL_ADJRES(4),
    SAMC21_ADC_AVGDIV_32  = ADC_AVGCTRL_ADJRES(5),
    SAMC21_ADC_AVGDIV_64  = ADC_AVGCTRL_ADJRES(6),
    SAMC21_ADC_AVGDIV_128 = ADC_AVGCTRL_ADJRES(7),
};

enum samc21_adc_mux_pos {
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


enum samc21_adc_mux_neg {
    SAMC21_ADC_MUXNEG_0   = 0x00,
    SAMC21_ADC_MUXNEG_1   = 0x01,
    SAMC21_ADC_MUXNEG_2   = 0x02,
    SAMC21_ADC_MUXNEG_3   = 0x03,
    SAMC21_ADC_MUXNEG_4   = 0x04,
    SAMC21_ADC_MUXNEG_5   = 0x05,
    SAMC21_ADC_MUXNEG_GND = 0x18,
};

enum samc21_adc_win_mode {
    SAMC21_ADC_WINMODE_DISABLE  = 0x00,
    SAMC21_ADC_WINMODE_GT_LOWER = 0x01,
    SAMC21_ADC_WINMODE_LT_UPPER = 0x02,
    SAMC21_ADC_WINMODE_INSIDE   = 0x03,
    SAMC21_ADC_WINMODE_OUTSIDE  = 0x04,
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
    * @param vref The voltage reference to use
    *
    * @return void
    */
    uint8_t begin(samc21_adc_ref vref = SAMC21_ADC_REF_1024);
    /**
     * @brief Stops the ADC
     *
     * @return void
     */
    uint8_t end(void);
    /**
    * @brief Sets the reference
    *
    * @param vref The reference to use.
    *
    * @return true on success
    */
    bool ref(samc21_adc_ref vref);
    /**
    * @brief Sets the averager
    *
    *
    *
    * @param samples The number of samples.
    * @param div     This is EXTRA right shift that will happen.
    *
    * @return true on success
    */
    bool average(samc21_adc_avg_samples samples = SAMC21_ADC_AVGSAMPLES_1, samc21_adc_avg_divisor div = SAMC21_ADC_AVGDIV_0);

    /**
    * @brief Sets the mux
    *
    * @param pos The positive pin
    * @param neg The negative pin
    *
    * @return true on success
    */
    bool mux(samc21_adc_mux_pos pos = SAMC21_ADC_MUXPOS_0, samc21_adc_mux_neg neg = SAMC21_ADC_MUXNEG_GND);
    /**
    * @brief Sets the input pins
    *
    * @param pos The positive pin
    * @param neg The negative pin
    *
    * @return true on success
    */
    bool pins(samc21_adc_mux_pos pos = SAMC21_ADC_MUXPOS_0, samc21_adc_mux_neg neg = SAMC21_ADC_MUXNEG_GND);

    /**
    * @brief Blocking read of the pin
    *
    * @param pos The positive pin
    * @param neg The negative pin
    *
    * @return the read
    */
    int32_t read(samc21_adc_mux_pos pos = SAMC21_ADC_MUXPOS_0, samc21_adc_mux_neg neg = SAMC21_ADC_MUXNEG_GND);

    /**
    * @brief Starts continuous reading
    *
    * @param pos The positive pin
    * @param neg The negative pin
    *
    * @return true on success
    */
    bool freerun(samc21_adc_mux_pos pos = SAMC21_ADC_MUXPOS_0, samc21_adc_mux_neg neg = SAMC21_ADC_MUXNEG_GND);

    /**
    * @brief Starts single read or sequence then returns
    *
    * @return true on success
    */
    bool run(void);

    /**
    * @brief Says if the sequence is busy
    *
    * @return void
    */
    bool busy()
    {
        if (_adc != NULL) {
            if (_adc->SEQCTRL.reg != 0) {
                return _adc->SEQSTATUS.bit.SEQBUSY == 1;
            } else {
            }
        }
        return false;
    }

    /**
    * @brief Gets the current reading
    *
    * @return The current reading
    */
    int32_t value(void);

    /**
    * @brief Sets the callback function
    *
    * @param cb   The callback function
    * @param *ptr An extra pointer that will be the third argument to the callback function
    *
    * @return The current reading
    */
    void callback(samc21_adc_callback cb, void *ptr = NULL)
    {
        if (_adc != NULL) {
            _callback = cb;
            _callback_ptr = ptr;
            _enable_irq();
        }
    };

    /**
    * @brief Sets the callback function for the window for the function
    *
    * @param cb    The callback function
    * @param lower The lower limit
    * @param upper The upper limit
    *
    * @return void
    */
    void window(
        samc21_adc_win_mode mode,
        samc21_adc_callback cb,
        uint16_t lower = 0,
        uint16_t upper = UINT16_MAX,
        void *ptr = NULL
    )
    {
        if (_adc != NULL) {
            if (mode == SAMC21_ADC_WINMODE_DISABLE) {
                _sync_wait();
                _adc->INTENCLR.reg = ADC_INTENSET_WINMON;
                _sync_wait();
                _adc->CTRLC.bit.WINMODE = mode;
                _window = NULL;
            } else if (cb != NULL) {
                _window = cb;
                _window_ptr = ptr;
                _enable_irq();
                _sync_wait();
                _adc->WINLT.reg = (uint16_t)lower;
                _sync_wait();
                _adc->WINUT.reg = (uint16_t)upper;
                _sync_wait();
                _adc->CTRLC.bit.WINMODE = mode;
                _sync_wait();
                _adc->INTENSET.reg = ADC_INTENSET_WINMON;
            }
        }
    };
    /**
    * @brief Calls the window function if there is one.
    *
    * @return void
    */
    void window(void)
    {
        if (_window != NULL) {
            _window(this, value(), (uint8_t)_adc->SEQSTATUS.bit.SEQBUSY, _window_ptr);
        }
    }

    /**
    * @brief Enables a pin in the sequence
    *
    * @param pos The positive mux pin
    *
    * @return void
    */
    void seqEnable(samc21_adc_mux_pos pos)
    {
        if (_started()) {
            if (_adc != NULL) {
                if (pos < 32) {
                    _adc->SEQCTRL.reg |= 1 << pos;
                    pins(pos);
                }
            }
        }
    }
    /**
    * @brief Disables a pin in the sequence
    *
    * @param pos The positive mux pin
    *
    * @return void
    */
    void seqDisable(samc21_adc_mux_pos pos)
    {
        if (_started()) {
            if (_adc != NULL) {
                _adc->SEQCTRL.reg &= ~(1 << pos);
            }
        }
    }
    /**
    * @brief Disables all pins in the sequence
    *
    * @return void
    */
    void seqDisable(void)
    {
        if (_started()) {
            if (_adc != NULL) {
                _adc->SEQCTRL.reg = 0;
            }
        }
    }

    /**
    * @brief Returns true if there has been a reading since the last time it was called
    *
    * @return True if there is a reading since the last call
    */
    bool newReading(void)
    {
        if (_new != _count) {
            _new = _count;
            return true;
        }
        return false;
    }
    /**
    * @brief Turns on and off the digital correction (@see gain() and @see offset() funcitons)
    *
    * @param value True causes the digital correction to be enabled
    *
    * @return True if enabled, false otherwise
    */
    bool digitalCorrection(bool value)
    {
        if (value) {
            _adc->CTRLC.bits.CORREN = 1;
        } else {
            _adc->CTRLC.bits.CORREN = 0;
        }
        return digitalCorrection();
    }
    /**
    * @brief  Returns true if digital correction is enabled (@see gain() and @see offset() funcitons)
    *
    * @return True if enabled, false otherwise
    */
    bool digitalCorrection(void)
    {
        return (bool)_adc->CTRLC.bits.CORREN;
    }

    /**
    * @brief Sets the offset correction value for the ADC
    *
    * @param value The new offset correction value (12 bits)
    *
    * @return The new offset correction value
    */
    uint16_t offset(uint16_t value)
    {
        _adc->OFFSETCORR.reg = value & ADC_OFFSETCORR_OFFSETCORR_Msk;
        return offset();
    }
    /**
    * @brief Sets the offset correction value for the ADC
    *
    * @return The offset correction value
    */
    uint16_t offset(void)
    {
        return _adc->OFFSETCORR.reg & ADC_OFFSETCORR_OFFSETCORR_Msk;
    }
    /**
    * @brief Sets the gain correction value for the ADC
    *
    * @note: The gain correction is a fractional value, a 1-bit integer plus an
    *       11-bit fraction, and therefore 1⁄2 <= GAINCORR < 2. GAINCORR values
    *       range from 0.10000000000 to 1.11111111111.
    *
    * @param value The new offset correction value (12 bits)
    *
    * @return The new gain correction value
    */
    uint16_t gain(uint16_t value)
    {
        _adc->GAINCORR.reg = value & ADC_GAINCORR_OFFSETCORR_Msk;
        return gain();
    }
    /**
    * @brief Gets the gain correction value for the ADC
    *
    * @note: The gain correction is a fractional value, a 1-bit integer plus an
    *       11-bit fraction, and therefore 1⁄2 <= GAINCORR < 2. GAINCORR values
    *       range from 0.10000000000 to 1.11111111111.
    *
    * @return The gain correction value
    */
    uint16_t gain(void)
    {
        return _adc->GAINCORR.reg & ADC_GAINCORR_OFFSETCORR_Msk;
    };

private:
    Adc *_adc;                     //!< ADC Pointer
    volatile uint32_t _count;      //!< Flag to say we have a new reading
    volatile int32_t _val;         //!< The value of the last ADC read
    samc21_adc_callback _callback; //!< The callback function
    samc21_adc_callback _window;   //!< The callback function for the windowing
    uint32_t _new;                 //!< This is a container for the new function
    bool _int;                     //!< 1 if we are in interrupt mode
    void *_callback_ptr;           //!< Extra pointer for _callback
    void *_window_ptr;             //!< Extra pointer for _window
    bool _begun;

    /**
    * This checks the clock sync
    *
    * @return void
    */
    bool _sync(uint16_t mask = ADC_SYNCBUSY_MASK)
    {
        return (_adc->SYNCBUSY.reg & mask) != 0;
    }
    /**
    * This synchronizes the clocks.
    *
    * @return void
    */
    void _sync_wait(uint16_t mask = ADC_SYNCBUSY_MASK)
    {
        while (_sync());
    }


    /**
     * @brief Enables the interrupts
     *
     * @return void
     */
    void _enable_irq(void)
    {
        IRQn_Type irq = ADC0_IRQn;
        if (_started()) {
            if (_adc != NULL) {
                if (_int == 0) {
                    _int = 1;
                    if (_adc == ADC0) {
                        irq = ADC0_IRQn;
                    } else if (_adc == ADC1) {
                        irq = ADC1_IRQn;
                    }
                    NVIC_DisableIRQ(irq);
                    NVIC_ClearPendingIRQ(irq);
                    NVIC_SetPriority(irq, 1);
                    NVIC_EnableIRQ(irq);
                    _sync_wait();
                    _adc->INTENSET.reg = ADC_INTENSET_RESRDY;
                }
            }
        }
    };
    /**
     * @brief Enables the interrupts
     *
     * @return void
     */
    void _disable_irq(void)
    {
        IRQn_Type irq = ADC0_IRQn;
        if (_adc != NULL) {
            if (_int == 1) {
                _int = 0;
                if (_adc == ADC0) {
                    irq = ADC0_IRQn;
                } else if (_adc == ADC1) {
                    irq = ADC1_IRQn;
                }
                _adc->INTENCLR.reg = ADC_INTENSET_RESRDY;
                NVIC_DisableIRQ(irq);
                NVIC_ClearPendingIRQ(irq);
                _sync_wait();
            }
        }
    };

    /**
     * @brief Wait for a new reading
     *
     * @param timeout The timeout in ms
     *
     * @return true if there is a new reading
     */
    bool _wait(uint32_t timeout = 100)
    {
        unsigned long late = millis() + timeout;
        bool newRead = false;
        if (_started()) {
            if (_adc != NULL) {
                do {
                    // Only retrieve the value if the interrupt is not enabled.
                    if (_adc->INTENSET.bit.RESRDY == 0) {
                        value();
                    }
                    newRead = newReading();
                } while (!newRead and (millis() < late));
            }
        }
        return newRead;
    }

    /**
     * @brief Checks for a new reading and loads it
     *
     * @return true if there is a new reading
     */
    bool _checkNew(void)
    {
        if (_started()) {
            if (_adc != NULL) {  // Check to see if there is something newer.
                if (_adc->INTFLAG.bit.RESRDY) {
                    _val = _adc->RESULT.reg;
                    _count++;
                    _adc->INTFLAG.bit.RESRDY = 1;   // Clear the flag
                    if (_callback != NULL) {
                        _callback(this, _val, (uint8_t)_adc->SEQSTATUS.bit.SEQSTATE, _callback_ptr);
                    }
                    return true;
                }
            }
        }
        return false;
    }
    /**
     * @brief Checks if we have started the ADC
     *
     * @return true if it has started.
     */
    bool _started(void)
    {
        return _begun;
    }
    /**
    * @brief Sets the mux and sets up the pin
    *
    * @param pos The positive pin
    * @param neg The negative pin
    *
    * @return void
    */
    void _mux(samc21_adc_mux_pos pos, samc21_adc_mux_neg neg)
    {
        if (_adc != NULL) {
            _adc->INPUTCTRL.reg = ((uint16_t)pos << ADC_INPUTCTRL_MUXPOS_Pos) | ((uint16_t)neg << ADC_INPUTCTRL_MUXNEG_Pos);
        }
    }
    /**
    * @brief Starts the ADC
    *
    * @return void
    */
    bool _start(void)
    {
        if ((_adc != NULL) && !_sync()) {
            if (!_enabled()) {
                _enable();
            }
            _adc->SWTRIG.bit.START = 1;
            return true;
        }
        return false;
    }

    /**
    * @brief Starts the ADC
    *
    * @return void
    */
    void _enable(void)
    {
        if (_adc != NULL) {
            if ((_adc == ADC1) && (ADC0->CTRLA.bit.ENABLE == 0)) {
                // Can't enable ADC1 when ADC0 is disabled
                return;
            }
            _sync_wait(ADC_SYNCBUSY_ENABLE);
            _adc->CTRLA.bit.ENABLE = 1;             // enable the ADC
            _sync_wait(ADC_SYNCBUSY_ENABLE);
        }
    }
    /**
    * @brief Starts the ADC
    *
    * @return void
    */
    bool _enabled(void)
    {
        if (_adc != NULL) {
            return _adc->CTRLA.bit.ENABLE == 1;             // enable the ADC
        }
        return false;
    }
    /**
    * @brief Starts the ADC
    *
    * @return void
    */
    void _disable(void)
    {
        if (_adc != NULL) {
            if ((_adc == ADC0) && (ADC1->CTRLA.bit.ENABLE == 1)) {
                // Can't disable ADC0 when ADC1 is enabled
                return;
            }
            _sync_wait(ADC_SYNCBUSY_ENABLE);
            _adc->CTRLA.bit.ENABLE = 0;             // enable the ADC
            _sync_wait(ADC_SYNCBUSY_ENABLE);
        }
    }


};


#endif //define _SAMC_ADC_H_
