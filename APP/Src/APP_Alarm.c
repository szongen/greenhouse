#include "APP_Alarm.h"

unsigned char MQ2_ADC_Alarm; 
unsigned char Auto_Flag = 0; 

void APP_Alarm()
{
	if(MQ2_ADC>=0.32)
	{
		MQ2_ADC_Alarm = Yes;
		
	}
	else
	{
		MQ2_ADC_Alarm = No;
	}
}









