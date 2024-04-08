/*
 * @FilePath: \eElements\Drivers\battery\battery.c
 * @Author: MaxDYi
 * @Date: 2024-04-07 18:13:32
 * @LastEditors: MaxDYi
 * @LastEditTime: 2024-04-08 10:52:18
 * @Description:锂电池相关的库函数
 */

#include "battery.h"

 /**
  * @description: 读取电池电压
  * @return {*}
  */
float Bat_GetVoltage(void)
{
    MX_OPAMP1_Init();
    HAL_OPAMP_Start(&hopamp1);
    MX_ADC1_Init();
    HAL_ADCEx_Calibration_Start(&hadc1 , ADC_SINGLE_ENDED);
    //HAL_Delay(10);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1 , 100);
    uint16_t adcValue = HAL_ADC_GetValue(&hadc1);
    float voltage = adcValue * 3.3 / 4096.0 * 2;
    HAL_ADC_Stop(&hadc1);
    HAL_OPAMP_Stop(&hopamp1);
    HAL_ADC_DeInit(&hadc1);
    HAL_OPAMP_DeInit(&hopamp1);
    return voltage;
}

/**
 * @description: 读取电池状态
 * @return {*}
 */
uint8_t Bat_GetMode(void)
{
    BAT_GPIO_Init();
    uint8_t mode = BAT_STATUS_ERROR;
    if (Bat_ReadChrg() == GPIO_PIN_RESET && Bat_ReadStdby() == GPIO_PIN_SET) {
        mode = BAT_STATUS_CHARGING;
    }
    else if (Bat_ReadChrg() == GPIO_PIN_SET && Bat_ReadStdby() == GPIO_PIN_RESET) {
        mode = BAT_STATUS_FULL;
    }
    else if (Bat_ReadChrg() == GPIO_PIN_SET && Bat_ReadStdby() == GPIO_PIN_SET) {
        mode = BAT_STATUS_ERROR;
    }
    else if (Bat_ReadStdby() == GPIO_PIN_RESET) {
        uint8_t chrg = Bat_ReadStdby();
        uint8_t count = 40;
        while (count--) {
            if (Bat_ReadStdby() != chrg) {
                mode = BAT_STATUS_NOBAT;
                break;
            }
            HAL_Delay(100);
        }
    }
    BAT_GPIO_Deinit();
    return mode;
}

/**
 * @description: 读取电池充电状态
 * @return {*}
 */
uint8_t Bat_ReadChrg(void)
{
    return HAL_GPIO_ReadPin(BAT_CHRG_GPIO_Port , BAT_CHRG_Pin);
}

/**
 * @description: 读取电池待机状态
 * @return {*}
 */
uint8_t Bat_ReadStdby(void)
{
    return HAL_GPIO_ReadPin(BAT_STDBY_GPIO_Port , BAT_STDBY_Pin);
}


