 #include <stdio.h>
#include "irslinger.h"

int main(int argc, char *argv[])
{
	uint32_t outPin =18;            // The Broadcom pin number the signal will be sent on
	int frequency = 38000;          // The frequency of the IR signal in Hz
	double dutyCycle = 0.5;         // The duty cycle of the IR signal. 0.5 means for every cycle,
	                                // the LED will turn on for half the cycle time, and off the other half

	/*int codes[] = {9000, 4500, 600, 600, 600, 1688, 600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
		600, 1688, 600, 1688, 600, 600, 600, 1688, 600, 1688, 600, 600, 600, 1688, 600, 1688,
		600, 600, 600, 600, 600, 1688, 600, 600, 600, 1688, 600, 1688, 600, 600, 600, 600,
		600, 600, 600, 1688, 600, 600, 600, 1688, 600, 600, 600, 600, 600, 1688, 600, 1688,
		600, 1688, 600};*/

    int baud=1200;
    char sendbytes[200]={0x11};
     sendbytes[196]=0x55;
    sendbytes[197]=0x77;
    sendbytes[198]=0x88;
    sendbytes[199]=0x99;
    int onDuration = (int)round(1000000/1200);
    printf("onDuration is %i\n", onDuration); 
    int codes[1000];
    int pos=0;
    char bitoldvalue=0;
    char bitnewvalue=0;
    codes[pos]=0;
    long sendpulsepos=0;
    int sendcodepos=0;
    for(int i=0;i<199;i++)
    {   char bitcount=0;
        while(bitcount<11)
        {
            if(bitcount==0)
              {
                bitnewvalue=0;
                sendpulsepos+=(int)round(onDuration/13);
              }
            else if(bitcount<9)
            {
                if((sendbytes[i] & (1<<(bitcount-1))))
                {
                    bitnewvalue=1;
                    sendpulsepos+=1;           
                }
                else
                {
                    bitnewvalue=0;
                    sendpulsepos+=(int)round(onDuration/13);
                }
            }
            else if(bitcount==9)//parity
            {
               bitnewvalue=0;
               sendpulsepos+=(int)round(onDuration/13);
            }
            else if(bitcount==10)//stopbit
            {
                bitnewvalue=1;
                sendpulsepos+=1;
            }
            if( bitnewvalue!= bitoldvalue)
            {
                pos++;
                codes[pos]=onDuration;
                bitoldvalue= bitnewvalue;
            }
            else
            {
                codes[pos]+=onDuration;
            }
            bitcount++;
        }
         printf("codelen is %i\n", pos+1);
         printf("sendpulsepos is %i\n", sendpulsepos);     
        if(sendpulsepos>11300)
        {
           sendcodepos=pos+1;
           int result = irSlingRaw( outPin, frequency, dutyCycle, codes, sendcodepos);
            printf("codelen is %i\n", sendcodepos);
            for(int ii=0;ii<sendcodepos;ii++)
                printf("code is %i\n", codes[ii]);        
           pos=0;  bitoldvalue=0;bitnewvalue=0;codes[pos]=0;sendpulsepos=0;
        }
    }
    if(pos>0)
    {
        sendcodepos=pos+1;
        int result = irSlingRaw( outPin, frequency, dutyCycle, codes, sendcodepos);
        printf("codelen is %i\n", sendcodepos);
        for(int ii=0;ii<sendcodepos;ii++)
            printf("code is %i\n", codes[ii]);    
    }


/*int codes[] = {
    833 ,833,5831,1666,833,0, 2499,833,833, 1666,833,1666 };


int result = irSlingRaw(
        outPin,
        frequency,
        dutyCycle,
        codes,
        sizeof(codes) / sizeof(int));

return result;*/
}
