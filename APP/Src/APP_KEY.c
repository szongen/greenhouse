#include "APP_KEY.h"

button button1, button2; //按钮控件

uint8_t read_button1_GPIO()
{
	return HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
}

uint8_t read_button2_GPIO()
{
	return HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
}

/********************************************************************/
/*                 button单击，双击，长按                            */
/********************************************************************/
void BTN1_SINGLE_CLICK_Handler(void *btn)
{
	printf("BTN1_SINGLE_CLICK_Handler\r\n");
	if (Page[0] == 1)
	{
		switch(Page_setting[0])
		{
			case 0:
			{	
				Auto_Flag++;
				if (Auto_Flag >= 2)
				{
						Auto_Flag = 0;
				}
			}
			break;
			
			case 1:
			{
				DHT11_1.Temp_Setting--;
				if(DHT11_1.Temp_Setting<=1)
				{
					DHT11_1.Temp_Setting =35;
				}
			}
			break;
			
			case 2:
			{
				DHT11_1.Humidity_Setting--;
				if(DHT11_1.Humidity_Setting<=1)
				{
					DHT11_1.Humidity_Setting =90;
				}
			}
			break;
		}

	}
	else if(Page[0] == 0)
	{
		water_flag++;
		if(water_flag>=2)
		{
			water_flag = 0;
		}
		if(water_flag ==0)
		{
			Led2_Set(LED_OFF);
			printf("Led2_Set(LED_OFF)\r\n");
		}
		else
		{
			Led2_Set(LED_ON);
			printf("Led2_Set(LED_ON);\r\n");
		
		}
	}
	// do something...
}
void BTN1_DOUBLE_CLICK_Handler(void *btn)
{
	if (Page[0] == 1)
	{
		Page_setting[0]++;
		if (Page_setting[0] >= 3)
		{
			Page_setting[0] = 0;
		}
	}
	// do something...
	printf("BTN1_DOUBLE_CLICK_Handler\r\n");
}

void BTN1_LONG_PRESS_HOLD_Handler(void *btn)
{
	if (Page[0] == 0)
	{
		Page[0] = 1;
	}
	printf("BTN1_LONG_PRESS_HOLD_Handler\r\n");
	// do something...
}

/********************************************************************/
/*                 button单击，双击，长按                            */
/********************************************************************/
void BTN2_SINGLE_CLICK_Handler(void *btn)
{
	printf("BTN2_SINGLE_CLICK_Handler\r\n");
	// do something...
	if (Page[0] == 1)
	{
		switch(Page_setting[0])
		{
		
			case 1:
			{
				DHT11_1.Temp_Setting++;
				if(DHT11_1.Temp_Setting>=36)
				{
					DHT11_1.Temp_Setting =1;
				}
			}
			break;
			
			case 2:
			{
				DHT11_1.Humidity_Setting++;
				if(DHT11_1.Humidity_Setting>=90)
				{
					DHT11_1.Humidity_Setting =1;
				}
			}
			break;
		}

	}
}

void BTN2_DOUBLE_CLICK_Handler(void *btn)
{

	printf("BTN2_DOUBLE_CLICK_Handler\r\n");

	// do something...
}
void BTN2_LONG_PRESS_HOLD_Handler(void *btn)
{
	if (Page[0] == 1)
	{
		Page[0] = 0;
	}
	printf("BTN2_LONG_PRESS_Hold_Handler\r\n");
	// do something...
}

/********************************************************************/

void APP_KEY_Init(void)
{
	button_init(&button1, read_button1_GPIO, 0); //低电平触发
	button_init(&button2, read_button2_GPIO, 0); //低电平触发

	button_attach(&button1, SINGLE_CLICK, BTN1_SINGLE_CLICK_Handler);
	button_attach(&button1, DOUBLE_CLICK, BTN1_DOUBLE_CLICK_Handler);
	button_attach(&button1, LONG_PRESS_HOLD, BTN1_LONG_PRESS_HOLD_Handler);
	button_attach(&button2, SINGLE_CLICK, BTN2_SINGLE_CLICK_Handler);
	button_attach(&button2, DOUBLE_CLICK, BTN2_DOUBLE_CLICK_Handler);
	button_attach(&button2, LONG_PRESS_HOLD, BTN2_LONG_PRESS_HOLD_Handler);
	button_start(&button1);
	button_start(&button2);
}

