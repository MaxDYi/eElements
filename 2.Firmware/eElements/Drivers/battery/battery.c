/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-03-14 09:53:20
 * @LastEditTime: 2024-03-29 20:10:51
 * @FilePath: \eElements\Drivers\battery\battery.c
 */
#include "battery.h"

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

uint8_t Bat_ReadChrg(void)
{
    return HAL_GPIO_ReadPin(BAT_CHRG_GPIO_Port , BAT_CHRG_Pin);
}

uint8_t Bat_ReadStdby(void)
{
    return HAL_GPIO_ReadPin(BAT_STDBY_GPIO_Port , BAT_STDBY_Pin);
}


