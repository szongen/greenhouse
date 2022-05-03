#ifndef _APP_DHT11_H
#define _APP_DHT11_H

#include "main.h"
#include "BSP.h"

typedef struct
{
//  u8 DHT11_WorkingState;  //DHT11的工作状态
  unsigned int DHT11_CurrentTime_ms;  //DHT11定时器的起始时间（毫秒）
  
  unsigned char Humidity;        //湿度值
//  u8 Humidity_shi;    //湿度数据十位数字
//  u8 Humidity_ge;     //湿度数据个位数字
//  u8 Humidity_point;  //湿度数据小数数字

  unsigned char Temp;     //温度值
//  u8 Temp_bai;    //温度数据百位数字
//  u8 Temp_shi;    //温度数据十位数字
//  u8 Temp_ge;     //温度数据个位数字
//  u8 Temp_point;  //温度数据小数数字

//  u8 FLAG_FirstReadData;  //是否首次读数据标志位
//  u8 FLAG_FirstReadData2;  //是否首次读数据标志位
//  u8 FLAG_Sensor_Fault;  //传感器故障标志位
//  u8 DHT11_FaultCount;  //DHT11故障计数

//  u8 U8comdata;  //DHT11数据读取传递

//  s8 BC_C;  //温度补偿？
//  s8 BC_RH; //湿度补偿？
//  
//  float BC_C;  //温度补偿？
//  float BC_RH; //湿度补偿？
unsigned char Humidity_Setting;
unsigned char Temp_Setting;
}DHT11_SENSOR;
extern DHT11_SENSOR DHT11_1;

void APP_DHT11(void);

#endif
