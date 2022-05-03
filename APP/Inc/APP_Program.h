#ifndef _APP_Program_H
#define _APP_Program_H

#include "main.h"
#include "BSP.h"
#include "APP_DHT11.h"
#include "APP_Alarm.h"

extern unsigned char water_flag;
void APP_Program_Init(void);
void APP_Program(void);

#endif

