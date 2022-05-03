/**
  ******************************************************************************
  * @file    :user_debug.c
  * @brief   :类似标准库的printf()
  *             注意一次输出最长字符串为80字节
  * @author  :szongen
  * @date    :2021/03/27
  * @version :1.0  创建初始代码
  *
  *
  ******************************************************************************
  */




/* Includes ------------------------------------------------------------------*/

#include "BSP_Debug.h"



/** @defgroup XXXX_Private_TypesDefinitions
  * @{
  */


/**
  * @}
  */




/** @defgroup XXXX_Private_Defines
  * @{
  */


/**
  * @}
  */




/** @defgroup XXXX_Private_Macros
  * @{
  */


/**
  * @}
  */




/** @defgroup XXXX_Private_Variables
  * @{
  */


/**
  * @}
  */




/** @defgroup XXXX_Private_FunctionPrototypes
  * @{
  */


/**
  * @}
  */




/** @defgroup XXXX_Exported_FunctionPrototypes
  * @{
  */
  
//加入以下代码,支持printf函数，使用printf函数从串口输出。
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 
 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 

void _ttywrch(int ch)
    {
        ch = ch;
    }

//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
        while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
        USART1->DR = (unsigned char) ch;              //写DR,串口1将发送数据
        return ch;
}
#endif 
  

void u_print(const char *fmt, ...) // custom printf() function
{
    unsigned char string[80];

    va_list arg;
    va_start(arg, fmt);
    if (0 < vsprintf((char *) string, fmt, arg)) // build string
    {
        HAL_UART_Transmit(&huart2, string, strlen((const char *) string), 0xff); // send message via UART
    } else {}
    va_end(arg);
}

/**
  * @}
  */



/************************ (C) COPYRIGHT szongen *****END OF FILE****/


