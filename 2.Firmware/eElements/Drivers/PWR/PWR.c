/*
 * @Description  : 
 * @Author       : MaxDYi
 * @Date         : 2024-03-13 09:40:18
 * @LastEditTime: 2024-03-28 23:26:01
 * @FilePath: \eElements\Drivers\PWR\PWR.c
 */
#include "PWR.h"

void PWR_GPIOCLK_Enable(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    //__HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
}

void PWR_GPIOCLK_Disable(void)
{
    __HAL_RCC_GPIOA_CLK_DISABLE();
    __HAL_RCC_GPIOB_CLK_DISABLE();
    //__HAL_RCC_GPIOC_CLK_DISABLE();
    __HAL_RCC_GPIOH_CLK_DISABLE();
}

void PWR_GPIO_ModeAnalog(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    GPIO_InitStructure.Pin = GPIO_PIN_All;
    GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStructure.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
    //HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);
    HAL_GPIO_Init(GPIOH, &GPIO_InitStructure);
}

void PWR_CLK_Disable(void)
{
    RTC_HandleTypeDef RTCHandle;
    HAL_RTCEx_DeactivateWakeUpTimer(&RTCHandle);
}

void PWR_EnterStop2Mode(uint16_t stopTime)
{
    printf("STOP\r\n");

    HAL_SPI_DeInit(&hspi1);
    HAL_UART_DeInit(&huart1);
    HAL_ADC_DeInit(&hadc1);
    HAL_OPAMP_DeInit(&hopamp1);


    PWR_GPIOCLK_Enable();
    PWR_GPIO_ModeAnalog();
    PWR_GPIOCLK_Disable();

    HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
    HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, stopTime, RTC_WAKEUPCLOCK_RTCCLK_DIV16);

    __HAL_RCC_WAKEUPSTOP_CLK_CONFIG(RCC_STOP_WAKEUPCLOCK_MSI);
    HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
}