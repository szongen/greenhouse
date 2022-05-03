#include "APP_LED.h"


static uint16_t LED_CurrentTime_ms;




void APP_LED_Blink(void)
{
	if(API_SystemClock_TimingQuery_ms(LED_CurrentTime_ms,1000)==TimeOut)
    {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        LED_CurrentTime_ms = API_SystemClock_CurrentTime_ms();

    }
}
