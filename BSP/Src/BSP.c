#include "BSP.h"
#include "tim.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == htim3.Instance) //��ʱ��3  --10ms����ϵͳʱ��
  {
	  
    API_SystemClock_ReferenceClock(); //��ʱ

	  
  }
  if(htim->Instance == htim2.Instance)
  {
	  	  button_ticks();
  }
}




void BSP_Init(void)
{
	delay_init(72);
    HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim2);
	dht11Init();
	DisplayInit();
	Oled_Disp_String(0, 0, "�����߲˴���ϵͳ");
	DisplayRefresh();
	ESP8266_Init();    //��ʼ��ESP8266
	
}



