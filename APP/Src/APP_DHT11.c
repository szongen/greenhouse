#include "APP_DHT11.h"

uint16_t APP_DHT_CurrentTime_ms;

DHT11_SENSOR DHT11_1;

void APP_DHT11(void)
{
	
  if (API_SystemClock_TimingQuery_ms(DHT11_1.DHT11_CurrentTime_ms, 1000) == TimeOut)
  {
    dht11Read(&DHT11_1.Temp, &DHT11_1.Humidity);
    printf("DHT11.Temp:%d,DHT11.Humidity:%d\r\n", DHT11_1.Temp, DHT11_1.Humidity);
    DHT11_1.DHT11_CurrentTime_ms = API_SystemClock_CurrentTime_ms();
  }
}
