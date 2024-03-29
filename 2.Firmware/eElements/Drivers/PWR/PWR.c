/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-03-13 09:40:18
 * @LastEditTime: 2024-03-29 21:05:05
 * @FilePath: \eElements\Drivers\PWR\PWR.c
 */
#include "PWR.h"



void PWR_CLK_Disable(void)
{
    RTC_HandleTypeDef RTCHandle;
    HAL_RTCEx_DeactivateWakeUpTimer(&RTCHandle);
}

void PWR_DisableGPIOA(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    GPIO_InitStructure.Pin &= (~KEY_Pin);
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA , &GPIO_InitStructure);
    //__HAL_RCC_GPIOA_CLK_DISABLE();
}

void PWR_DisableGPIOB(void) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    GPIO_InitStructure.Pin = GPIO_PIN_All;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB , &GPIO_InitStructure);
    __HAL_RCC_GPIOB_CLK_DISABLE();
}

void PWR_DisableGPIOC(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    GPIO_InitStructure.Pin &= (~PWR_LDO_Pin);
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC , &GPIO_InitStructure);
    //__HAL_RCC_GPIOC_CLK_DISABLE();
}

void PWR_DisableGPIOH(void) {
    __HAL_RCC_GPIOH_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    GPIO_InitStructure.Pin = GPIO_PIN_All;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA , &GPIO_InitStructure);
    __HAL_RCC_GPIOH_CLK_DISABLE();
}



void PWR_EnterStop2Mode(uint16_t stopTime)
{
    HAL_SPI_DeInit(&hspi1);
    HAL_UART_DeInit(&huart1);
    HAL_ADC_DeInit(&hadc1);
    HAL_OPAMP_DeInit(&hopamp1);

    PWR_DisableGPIOA();
    PWR_DisableGPIOB();
    PWR_DisableGPIOC();
    PWR_DisableGPIOH();

    __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);
    HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
    HAL_RTCEx_SetWakeUpTimer_IT(&hrtc , stopTime , RTC_WAKEUPCLOCK_RTCCLK_DIV16);

    //HAL_SuspendTick();

    HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);

    //HAL_ResumeTick();
}

uint8_t PWR_PowerEnough(void)
{
    if (Bat_GetVoltage() < BAT_LOW_VOLTAGE) {
        if (Bat_GetMode() == BAT_STATUS_CHARGING) {
            return TRUE;
        }
        else if (Bat_GetMode() == BAT_STATUS_FULL) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    return TRUE;
}