#ifndef _display_dr_H
#define _display_dr_H

#include "main.h"

//�ַ�ת��,����ȫ�ֵ���
extern char  LCD_CACHE[20];
//��ʾ����ʼ��
void DisplayInit(void);
//��ʾ��ˢ����ʾ
void DisplayRefresh(void) ;
//����
void Oled_Draw_Point(uint8_t x,uint8_t y);
//��ʾ�ַ���
void Oled_Disp_String(uint8_t x,uint8_t y,char const  *text);
//����
void Interfacr_Shadow(uint8_t x,uint8_t y,uint8_t kuan,uint8_t gao);
//�������
void Clear_Disp(uint8_t x,uint8_t y,uint8_t kuan,uint8_t gao);

#endif

