#ifndef __BSP_H 
#define __BSP_H

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "BSP_Led.h"
#include "BSP_Debug.h"
#include "BSP_MultiTimer.h"
#include "BSP_delay.h"
#include "BSP_temp_hum.h"
#include "BSP_oled.h"
#include "BSP_display.h"
#include "BSP_ADC_DMA.h"
#include "BSP_multi_button.h"
/**************************************************************************/
#include "esp8266.h"
#include "onenet.h"
/**************************************************************************/
#include "API_S_SystemClock.h"
#include "API_U_SystemClock.h"

/**************************************************************************/
void BSP_Init(void);
void Task_Create(void);

/*****************************软件定时器***********************************/
extern MultiTimer LED_Timer;


/*****************************软件定时器***********************************/


//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


/******************************************************************
*                           通用宏定义                            *
******************************************************************/
#define Success  0  //正确
#define Error    1  //错误

#define Disable  0  //禁用
#define Enable   1  //使能

#define NoTimeOut  0  //时间还没到
#define TimeOut    1  //时间到

#define No   0  //不是
#define Yes  1  //是

#define OFF  0  //关闭
#define ON   1  //打开

/**********************************************************************/
/*							DHT11温湿度传感器						  */
/**********************************************************************/

//#define _DHT11_DATA_1(x)  (x)? HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 1):HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 0)
//#define _DHT11_DATA_READ_1 HAL_GPIO_ReadPin(DHT11_GPIO_Port,DHT11_Pin)  //DHT11


//传感器(DHT11_1)
#define _DHT11_DATA_1       PAout(5)   //DHT11
#define _DHT11_DATA_READ_1  PAin(5)    //DHT11

//#define DHT11_DATA_IN_1()  {GPIOA->CRL&=0XFF0FFFFF;GPIOB->CRH|=(u32)8<<20;}  //1000  上拉或下拉输入
#define DHT11_DATA_IN_1()  {GPIOA->CRL&=0XFF0FFFFF;GPIOB->CRL|=(u32)4<<20;}  //0100  浮空输入
#define DHT11_DATA_OUT_1() {GPIOA->CRL&=0XFF0FFFFF;GPIOB->CRL|=(u32)7<<20;}
/**********************************************************************/

#endif
