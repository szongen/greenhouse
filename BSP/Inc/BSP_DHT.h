#ifndef DHT_H_
#define DHT_H_

#include "main.h"

/* Настройки */
#define DHT_TIMEOUT 				10000	
#define DHT_POLLING_CONTROL			1		
#define DHT_POLLING_INTERVAL_DHT11	2000	
#define DHT_POLLING_INTERVAL_DHT22	1000	
#define DHT_IRQ_CONTROL						
/* Структура возвращаемых датчиком данных */
typedef struct {
	float hum;
	float temp;
} DHT_data;

/* Тип используемого датчика */
typedef enum {
	DHT11,
	DHT22
} DHT_type;

/* Структура объекта датчика */
typedef struct {
	GPIO_TypeDef *DHT_Port;	//Порт датчика (GPIOA, GPIOB, etc)
	uint16_t DHT_Pin;		//Номер пина датчика (GPIO_PIN_0, GPIO_PIN_1, etc)
	DHT_type type;			//Тип датчика (DHT11 или DHT22)
	uint8_t pullUp;			//Нужна ли подтяжка линии данных к питанию (GPIO_NOPULL - нет, GPIO_PULLUP - да)

	//Контроль частоты опроса датчика. Значения не заполнять!
	#if DHT_POLLING_CONTROL == 1
	uint32_t lastPollingTime;//Время последнего опроса датчика
	float lastTemp;			 //Последнее значение температуры
	float lastHum;			 //Последнее значение влажности
	#endif
} DHT_sensor;


/* Прототипы функций */
DHT_data DHT_getData(DHT_sensor *sensor); //Получить данные с датчика

#endif
