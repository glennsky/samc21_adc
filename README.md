Main Page
================

Introduction
----------------

This library is for using the ADC and SDADC on the SAMC21 mpu using the Arduino or 
PlatformIO build environments.

Requirements
----------------

SAMC support is still not in the mainline samd (Arduino or platformio).  SAMC support
is available for Arduino here:

https://github.com/prices/ArduinoCore-samd


For platformio it is available here:

https://github.com/prices/platform-atmelsam



Using the Library
----------------

### Platformio ###

#### Installing ####
```sh
platformio platform install https://github.com/prices/platform-atmelsam
```

#### platformio.ini Example ####

```ini
[platformio]
env_default = samc21

[env:samc21]
platform = atmelsam
framework = arduino
board = samc21_xpro

lib_deps = https://github.com/hugllc/samc21_adc.git

```


#### Code ####

Then for the code


```cpp
#include <samc21_adc.h>

SAMC21_CAN can(0);

SAMC21_ADC adc(ADC0);

void setup()
{
    adc.begin();
    adc.freerun(SAMC21_ADC_MUXPOS_3);

}

void loop()
{
    int32_t adc_read;
    if (adc.newReading()) {
        adc_read = adc.value();
        Serial.print("ADC: ");
        Serial.print(adc_read);
        Serial.println();
    }
    
}


```


License
-----------------
GPL V3


Acknowledgements
-----------------
Little bits of code (generally single lines) here and there were copied from the Arduino core.
