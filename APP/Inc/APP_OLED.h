#ifndef _APP_OLED_H
#define _APP_OLED_H

#include "main.h"
#include "BSP.h"
#include "APP_DHT11.h"
#include "APP_ADC.h"
#include "APP_Alarm.h"
#include "APP_Program.h"

#define  menu 1
#define  setting 2

extern unsigned char Page[2] ;
extern unsigned char Page_setting[1] ;
extern unsigned char connet_flag;

void APP_OLED(void);



#endif
