#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#define gpio 18


int main(){
    gpioInitialise();


    // Construct and send a 30 microsecond square wave.

    gpioSetMode(gpio, PI_OUTPUT);

    gpioPulse_t pulse[2];

    pulse[0].gpioOn = (1<<gpio);
    pulse[0].gpioOff = 0;
    pulse[0].usDelay = 833;

    pulse[1].gpioOn = 0;
    pulse[1].gpioOff = (1<<gpio);
    pulse[1].usDelay = 833;

    gpioWaveAddNew();

    gpioWaveAddGeneric(2, pulse);

    int wave_id = gpioWaveCreate();

    if (wave_id >= 0)
    {
        gpioWaveTxSend(wave_id, PI_WAVE_MODE_REPEAT);

        // Transmit for 30 seconds.

        sleep(30);

        gpioWaveTxStop();
    }
    else
    {
        // Wave create failed.
    }




}

