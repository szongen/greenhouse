#include "APP_NET.h"

unsigned int onenet_currentms,onenet_Rev_currentms;

unsigned char *dataPtr = NULL;

void APP_NET()
{
	
	if(API_SystemClock_TimingQuery_ms(onenet_currentms,5000)==TimeOut)//发送间隔5s
	{
		printf("OneNet_SendData\r\n");
			
		OneNet_SendData();									//发送数据
			
		ESP8266_Clear();
		onenet_currentms = API_SystemClock_CurrentTime_ms();
	}
	if(API_SystemClock_TimingQuery_ms(onenet_Rev_currentms,10)==TimeOut)
	{		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
		{

			OneNet_RevPro(dataPtr);
		}
	onenet_Rev_currentms = API_SystemClock_CurrentTime_ms();
	}
}
		
