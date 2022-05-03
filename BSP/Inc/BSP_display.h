#ifndef _display_dr_H
#define _display_dr_H

#include "main.h"

//字符转换,方便全局调用
extern char  LCD_CACHE[20];
//显示屏初始化
void DisplayInit(void);
//显示屏刷新显示
void DisplayRefresh(void) ;
//画点
void Oled_Draw_Point(uint8_t x,uint8_t y);
//显示字符串
void Oled_Disp_String(uint8_t x,uint8_t y,char const  *text);
//反显
void Interfacr_Shadow(uint8_t x,uint8_t y,uint8_t kuan,uint8_t gao);
//清除区域
void Clear_Disp(uint8_t x,uint8_t y,uint8_t kuan,uint8_t gao);

#endif

