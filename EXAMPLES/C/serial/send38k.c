/*
author: zhaoxin
compilation:gcc -lrt -lpthread -lpigpio main.c

 */





#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#define GPIO 4
#define gpio 18






int main(){


    int r=0;
    gpioInitialise();

    gpioSetMode(gpio, PI_OUTPUT);
    gpioPulse_t pulse[4];

    pulse[0].gpioOn = (1<<gpio);
    pulse[0].gpioOff = 0;
    pulse[0].usDelay = 13;

    pulse[1].gpioOn = 0;
    pulse[1].gpioOff = (1<<gpio);
    pulse[1].usDelay = 13;
    gpioWaveAddNew();
    r = gpioWaveAddGeneric(2, pulse);


    pulse[2].gpioOn = (1<<gpio);
    pulse[2].gpioOff = 0;
    pulse[2].usDelay = 833;

    pulse[3].gpioOn = 0;
    pulse[3].gpioOff = (1<<gpio);
    pulse[3].usDelay = 833;
//    gpioWaveAddNew();
//    r = gpioWaveAddGeneric(2, pulse+2);

    int wave_id = gpioWaveCreate();

    if (wave_id >= 0)
    {
        //gpioWaveTxSend(wave_id, PI_WAVE_MODE_ONE_SHOT);
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
