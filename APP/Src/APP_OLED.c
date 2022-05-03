#include "APP_OLED.h"

unsigned long APP_OLED_CurrentTime_ms;
unsigned char connet_flag;
//unsigned char APP_OLED_Status;

// enum Page[2]
// {
// 	menu = 0,
// 	geting
// };

unsigned char Page[2] = { 0 , 1 };
unsigned char Page_setting[1] ;

typedef enum APP_OLED_Status
{
	start = 0,
	second,
	third
}APP_OLED_Status;

APP_OLED_Status OLED_Status = start ;

void APP_OLED()
{
	char buffer[20];
	switch(OLED_Status)
	{
		case start:
		{
			if(API_SystemClock_TimingQuery_ms(APP_OLED_CurrentTime_ms,1000) ==TimeOut)
			{
				Oled_Disp_String(0, 0, "智能蔬菜大棚系统");
				if(connet_flag == 0)
				{
					Oled_Disp_String(32, 32, "云平台已连接");
				}
				else
				{
					Oled_Disp_String(32, 32, "云平台未连接");
				}
				DisplayRefresh();
				OLED_Status = second;
				APP_OLED_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
			}
		}
			break;
		case second:
		{
			if(API_SystemClock_TimingQuery_ms(APP_OLED_CurrentTime_ms,700) ==TimeOut)
			{
				// Oled_Disp_String(0, 0, "智能蔬菜大棚系统");
				Oled_Disp_String(0, 0, "温度:");
				sprintf(buffer,"%d",DHT11_1.Temp);
				Oled_Disp_String(0+48,0,buffer);
				Oled_Disp_String(70, 0, "自动:");
				if(Auto_Flag == Yes)
				{
					Oled_Disp_String(70+44,0,"开");
				}
				else{
					Oled_Disp_String(70+44,0,"关");
				}
				Oled_Disp_String(0, 16, "湿度:");
				sprintf(buffer,"%d",DHT11_1.Humidity);
				Oled_Disp_String(0+48,16,buffer);
				Oled_Disp_String(70, 16, "浇水:");
				if(water_flag == 1)
				{
					Oled_Disp_String(70+44, 16, "开");
				}
				else
				{
					Oled_Disp_String(70+44, 16, "关");
				}
				Oled_Disp_String(0, 32, "MQ2:");
				sprintf(buffer,"%.2f",MQ2_ADC);
				Oled_Disp_String(0+48,32,buffer);
				Oled_Disp_String(0, 48, "警告:");
				if(MQ2_ADC_Alarm == Yes)
				{
					Oled_Disp_String(0+48, 48, "有");
				}
				else
				{
					Oled_Disp_String(0+48, 48, "无");
				}

				DisplayRefresh();
				if(Page[0] == 1)
				{
					OLED_Status = third;
				}
				else
				{
					OLED_Status = second;
				}
				APP_OLED_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
			}
			
		}break;
		case third:
		{
			if(API_SystemClock_TimingQuery_ms(APP_OLED_CurrentTime_ms,700) ==TimeOut)
			{
				Oled_Disp_String(32, 0, "设置:");
				Oled_Disp_String(32, 16, "自动:");
				Oled_Disp_String(32, 32, "温度:");
				Oled_Disp_String(32, 48, "湿度:");
				switch(Page_setting[0])
				{
					case 0:
					{
						Interfacr_Shadow(32,16,44,16);
					}
					break;

					case 1:
					{
						Interfacr_Shadow(32,32,44,16);
					}
					break;
					case 2:
					{
						Interfacr_Shadow(32,48,44,16);
					}
					break;
				}	
				if(Auto_Flag == Yes)
				{
					Oled_Disp_String(32+44,16,"开");
				}
				else{
					Oled_Disp_String(32+44,16,"关");
				}	
				sprintf(buffer,"%02d",DHT11_1.Temp_Setting);
				Oled_Disp_String(32+44,32,buffer);
				sprintf(buffer,"%02d",DHT11_1.Humidity_Setting);
				Oled_Disp_String(32+44,48,buffer);
//				if(Auto_Flag ==No)
// {
				// 	Oled_Disp_String(70+44,0,"关");
				// }
				// {
				// 	Oled_Disp_String(70+44,0,"关");
				// }
				if(Page[0] == 1)
				{
					OLED_Status = third;
				}
				else
				{
					OLED_Status = second;
				}
				DisplayRefresh();
				APP_OLED_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
			}
		}
		break;
	}

}

