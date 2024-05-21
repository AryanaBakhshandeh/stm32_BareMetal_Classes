
#ifndef ARYANA_DELAY_H
#define ARYANA_DELAY_H

#include "stm32f4xx.h"

class aryana_delay
{
public:
	aryana_delay(int freq = 16);
    void ms(int delay_ms);

private:
    int sysFreq_Mhz;
    int CTRL_ENABLE;
    int CTRL_CLKSRC;
    int CTRL_COUNTFLAG;

};

#endif
