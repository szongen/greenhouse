#ifndef _dr_oled_H
#define _dr_oled_H

#include "main.h"

//OLED��ʼ��
void OLED_Init(void);
//OLEDȫ����ʾ
void OLED_Diaplay(char displaybuf[][8]);
//�ر�OLED��ʾ 
void OLED_Display_Off(void);
//����OLED��ʾ
void OLED_Display_On(void);

#endif

