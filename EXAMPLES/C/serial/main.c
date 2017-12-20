/*
author: zhaoxin
compilation:gcc -lrt -lpthread -lpigpio main.c

*/





#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define GPIO 4
#define gpio 18




void * sendWave(void *arg){
// Construct and send a 30 microsecond square wave.

gpioSetMode(gpio, PI_OUTPUT);
gpioPulse_t pulse[10];

pulse[0].gpioOn = 0;
pulse[0].gpioOff = (1<<gpio);
pulse[0].usDelay = 833;

pulse[1].gpioOn =(1<<gpio);
pulse[1].gpioOff = 0;
pulse[1].usDelay = 833;


pulse[2].gpioOn =(1<<gpio);
pulse[2].gpioOff = 0;
pulse[2].usDelay = 833;


pulse[3].gpioOn = 0;
pulse[3].gpioOff = (1<<gpio);
pulse[3].usDelay = 833;


pulse[4].gpioOn = 0;
pulse[4].gpioOff = (1<<gpio);
pulse[4].usDelay = 833;


pulse[5].gpioOn = 0;
pulse[5].gpioOff = (1<<gpio);
pulse[5].usDelay = 833;


pulse[6].gpioOn = 0;
pulse[6].gpioOff = (1<<gpio);
pulse[6].usDelay = 833;


pulse[7].gpioOn = (1<<gpio);
pulse[7].gpioOff = 0;
pulse[7].usDelay = 833;


pulse[8].gpioOn = 0;
pulse[8].gpioOff = (1<<gpio);
pulse[8].usDelay = 833;


pulse[9].gpioOn = (1<<gpio);
pulse[9].gpioOff = 0;
pulse[9].usDelay = 833;




sleep(2);



gpioWaveAddNew();

gpioWaveAddGeneric(10, pulse);

int wave_id = gpioWaveCreate();

if (wave_id >= 0)
{
   //gpioWaveTxSend(wave_id, PI_WAVE_MODE_ONE_SHOT);
  // gpioWaveTxSend(wave_id, PI_WAVE_MODE_REPEAT);

   // Transmit for 30 seconds.

   sleep(30);

   gpioWaveTxStop();
}
else
{
   // Wave create failed.
}

}



int main()
{
    gpioInitialise();
    /*
    gpioSerialReadOpen  Opens a GPIO for bit bang serial reads
    gpioSerialReadInvert    Configures normal/inverted for serial reads
    gpioSerialRead  Reads bit bang serial data from a GPIO
    gpioSerialReadClose Closes a GPIO for bit bang serial reads
    */

    //since there is no parity in pigpio serial com interface, 
    //we get 8 data bits and 1 parity by 9 data bits

    gpioSetMode(gpio, PI_OUTPUT);
    gpioWrite(gpio,1); //pull up



    int r = gpioSerialReadOpen(GPIO,1200,9);
    if( r!= 0 ){
        printf("gpio %d serial open failed!\n",GPIO);
        exit(-1);
    }

    gpioStartThread(sendWave, NULL); 

    if(PI_OUTPUT != gpioGetMode(GPIO)){
       printf("the mode of GPIO %d is not PI_OUTPUT\n",GPIO);
       // exit(-1);
    }



    do{
        char buf[512] = "";
        r = gpioSerialRead(GPIO,buf,512);
        int flag=r;
        if( r<0){
            printf("gpio %d serial read failed!\n",GPIO);
            exit(-1);
        }
        int i=0;
        while (r>0){ 
            printf("gpio serial read 0x%x ",*((unsigned short *)(&buf[(i++)*2])) );
            r=r-2;
        }
        if(flag>0)
            printf("!\n");
        //usleep(1000*200);
        sleep(1);
    }
    while(1);
}
