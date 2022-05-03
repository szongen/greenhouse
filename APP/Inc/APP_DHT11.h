#ifndef _APP_DHT11_H
#define _APP_DHT11_H

#include "main.h"
#include "BSP.h"

typedef struct
{
//  u8 DHT11_WorkingState;  //DHT11�Ĺ���״̬
  unsigned int DHT11_CurrentTime_ms;  //DHT11��ʱ������ʼʱ�䣨���룩
  
  unsigned char Humidity;        //ʪ��ֵ
//  u8 Humidity_shi;    //ʪ������ʮλ����
//  u8 Humidity_ge;     //ʪ�����ݸ�λ����
//  u8 Humidity_point;  //ʪ������С������

  unsigned char Temp;     //�¶�ֵ
//  u8 Temp_bai;    //�¶����ݰ�λ����
//  u8 Temp_shi;    //�¶�����ʮλ����
//  u8 Temp_ge;     //�¶����ݸ�λ����
//  u8 Temp_point;  //�¶�����С������

//  u8 FLAG_FirstReadData;  //�Ƿ��״ζ����ݱ�־λ
//  u8 FLAG_FirstReadData2;  //�Ƿ��״ζ����ݱ�־λ
//  u8 FLAG_Sensor_Fault;  //���������ϱ�־λ
//  u8 DHT11_FaultCount;  //DHT11���ϼ���

//  u8 U8comdata;  //DHT11���ݶ�ȡ����

//  s8 BC_C;  //�¶Ȳ�����
//  s8 BC_RH; //ʪ�Ȳ�����
//  
//  float BC_C;  //�¶Ȳ�����
//  float BC_RH; //ʪ�Ȳ�����
unsigned char Humidity_Setting;
unsigned char Temp_Setting;
}DHT11_SENSOR;
extern DHT11_SENSOR DHT11_1;

void APP_DHT11(void);

#endif
