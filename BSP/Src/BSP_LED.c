#include "BSP_LED.h"



LED_STATUS led_status;

/*
************************************************************
*	函数名称：	Led2_Set
*
*	函数功能：	LED4控制
*
*	入口参数：	status：LED_ON-开灯	LED_OFF-关灯
*
*	返回参数：	无
*
*	说明：		
************************************************************
*/
void Led2_Set(LED_ENUM status)
{
//		if(status ==LED_ON)
//		{
//			HAL_GPIO_WritePin(relay_GPIO_Port,relay_Pin,GPIO_PIN_SET);
//		}
//		else if(status ==LED_OFF)
//		{
//			HAL_GPIO_WritePin(relay_GPIO_Port,relay_Pin,GPIO_PIN_RESET);
//		}
		

	HAL_GPIO_WritePin(relay_GPIO_Port, relay_Pin, status != LED_ON ? GPIO_PIN_RESET : GPIO_PIN_SET);
	led_status.Led2Sta = status;
}

