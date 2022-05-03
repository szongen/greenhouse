#include "BSP_ADC_DMA.h"
#include "BSP_Debug.h"

uint16_t i ;



void ADC_DMA_Init(void)
{
//	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&temp, 100);
}

float ADC_DMA_GET(void)
{

//      printf("ad = %f\r\n", (float)temp[0]*3.3f/4096);
/*
	ad = 0;
	for(i = 0; i < 10; ++i)
	{
		ad += temp[i];
	}
	ad1 = ad / 10;
	printf("ADC Value %f\r\n",ad1);
	printf("vol %f\r\n", (float)ad1 * 3.3 / 4096);
	return ((float)ad*3.3/4096);
*/
	
	HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,0xffff);
    i=HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	printf("MQ2=%f\r\n",(float)i*3.3/4096);
	return (float)(i*3.3/4096);

}
