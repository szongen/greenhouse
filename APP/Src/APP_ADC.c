#include "APP_ADC.h"

uint16_t ADC_CurrentTime_ms;

float MQ2_ADC;
	
void APP_ADC(void)
{
	if(API_SystemClock_TimingQuery_ms(ADC_CurrentTime_ms,1000)==TimeOut)
    {
        MQ2_ADC = ADC_DMA_GET();
        ADC_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
    }
}   
