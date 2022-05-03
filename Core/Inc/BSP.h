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

/*****************************�����ʱ��***********************************/
extern MultiTimer LED_Timer;


/*****************************�����ʱ��***********************************/


//λ������,ʵ��51���Ƶ�GPIO���ƹ���
//����ʵ��˼��,�ο�<<CM3Ȩ��ָ��>>������(87ҳ~92ҳ).
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
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
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����


/******************************************************************
*                           ͨ�ú궨��                            *
******************************************************************/
#define Success  0  //��ȷ
#define Error    1  //����

#define Disable  0  //����
#define Enable   1  //ʹ��

#define NoTimeOut  0  //ʱ�仹û��
#define TimeOut    1  //ʱ�䵽

#define No   0  //����
#define Yes  1  //��

#define OFF  0  //�ر�
#define ON   1  //��

/**********************************************************************/
/*							DHT11��ʪ�ȴ�����						  */
/**********************************************************************/

//#define _DHT11_DATA_1(x)  (x)? HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 1):HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 0)
//#define _DHT11_DATA_READ_1 HAL_GPIO_ReadPin(DHT11_GPIO_Port,DHT11_Pin)  //DHT11


//������(DHT11_1)
#define _DHT11_DATA_1       PAout(5)   //DHT11
#define _DHT11_DATA_READ_1  PAin(5)    //DHT11

//#define DHT11_DATA_IN_1()  {GPIOA->CRL&=0XFF0FFFFF;GPIOB->CRH|=(u32)8<<20;}  //1000  ��������������
#define DHT11_DATA_IN_1()  {GPIOA->CRL&=0XFF0FFFFF;GPIOB->CRL|=(u32)4<<20;}  //0100  ��������
#define DHT11_DATA_OUT_1() {GPIOA->CRL&=0XFF0FFFFF;GPIOB->CRL|=(u32)7<<20;}
/**********************************************************************/

#endif
