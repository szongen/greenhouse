#include "BSP_LED.h"



LED_STATUS led_status;

/*
************************************************************
*	�������ƣ�	Led2_Set
*
*	�������ܣ�	LED4����
*
*	��ڲ�����	status��LED_ON-����	LED_OFF-�ص�
*
*	���ز�����	��
*
*	˵����		
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

