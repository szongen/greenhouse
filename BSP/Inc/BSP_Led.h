#ifndef BSP_Led_H
#define BSP_Led_H

#include "BSP.h"

static u8 Led_state;

#define ON 0
#define OFF 1

void Led_ON(void);
void Led_OFF(void);
void Led_Setstate(u8 state);
u8 Recall_Led_State(void);

# endif
