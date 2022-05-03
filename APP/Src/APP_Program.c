#include "APP_Program.h"

unsigned char water_flag;
void APP_Program_Init()
{
	DHT11_1.Humidity_Setting = 35;
	DHT11_1.Temp_Setting = 25;
	water_flag = 0;
}

void APP_Program()
{
	if((DHT11_1.Humidity<=DHT11_1.Humidity_Setting)&&(Auto_Flag ==Yes))
	{
		Led2_Set(LED_ON);
	}
	else if((DHT11_1.Temp>=DHT11_1.Temp_Setting)&&(Auto_Flag ==Yes))
	{
		Led2_Set(LED_ON);
	}
	else if(Auto_Flag ==Yes)
	{
		Led2_Set(LED_OFF);
		
	}
}







