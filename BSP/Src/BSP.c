#include "BSP.h"
#include "tim.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == htim3.Instance) //定时器3  --10ms用作系统时钟
  {
	  
    API_SystemClock_ReferenceClock(); //延时

	  
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
	Oled_Disp_String(0, 0, "智能蔬菜大棚系统");
	DisplayRefresh();
	ESP8266_Init();    //初始化ESP8266
	
}



