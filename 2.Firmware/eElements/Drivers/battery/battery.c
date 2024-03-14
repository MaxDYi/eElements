/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-03-14 09:53:20
 * @LastEditTime : 2024-03-14 12:18:11
 * @FilePath     : \eElements\Drivers\battery\battery.c
 */
#include "battery.h"

float Bat_GetVoltage(void)
{
    MX_OPAMP1_Init();
    HAL_OPAMP_Start(&hopamp1);
    MX_ADC1_Init();
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    //HAL_Delay(10);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 100);
    uint16_t adcValue = HAL_ADC_GetValue(&hadc1);
    float voltage = adcValue * 3.3 / 4096.0;
    HAL_ADC_Stop(&hadc1);
    HAL_OPAMP_Stop(&hopamp1);
    HAL_ADC_DeInit(&hadc1);
    HAL_OPAMP_DeInit(&hopamp1);
    return voltage;
}

uint8_t Bat_GetMode(void)
{
    uint8_t mode = 0;

    return mode;
}