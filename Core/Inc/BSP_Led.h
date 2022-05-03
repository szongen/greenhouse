#ifndef BSP_Led_H
#define BSP_Led_H

#include "BSP.h"

static u8 Led_state;

void Led_ON(void);
void Led_OFF(void);
void Led_Setstate(u8 state);
u8 Recall_Led_State(void);



typedef struct
{

	_Bool Led2Sta;
//	_Bool Led3Sta;
//	_Bool Led4Sta;
//	_Bool Led5Sta;

} LED_STATUS;

extern LED_STATUS led_status;


typedef enum
{

	LED_OFF = 0,
	LED_ON

} LED_ENUM;


void Led_Init(void);

void Led2_Set(LED_ENUM status);

void Led3_Set(LED_ENUM status);

void Led4_Set(LED_ENUM status);

void Led5_Set(LED_ENUM status);

# endif
