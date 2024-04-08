/*
 * @FilePath: \eElements\Drivers\bsp\bsp.c
 * @Author: MaxDYi
 * @Date: 2024-04-07 18:13:32
 * @LastEditors: MaxDYi
 * @LastEditTime: 2024-04-08 10:52:02
 * @Description:��������ص������ʼ��
 */

#include "bsp.h"

 /**
  * @description: ��LED��
  * @return {*}
  */
void LED_GREEN_On(void)
{
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port , LED_GREEN_Pin , GPIO_PIN_RESET);
}

/**
 * @description: �ر�LED��
 * @return {*}
 */
void LED_GREEN_Off(void)
{
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port , LED_GREEN_Pin , GPIO_PIN_SET);
}

/**
 * @description: ��ʼ��LED��IO
 * @return {*}
 */
void LED_GREEN_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port , LED_GREEN_Pin , GPIO_PIN_RESET);
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = LED_GREEN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA , &GPIO_InitStruct);
}

/**
 * @description: �ر�LED��IO
 * @return {*}
 */
void LED_GREEN_GPIO_Deinit(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = LED_GREEN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LED_GREEN_GPIO_Port , &GPIO_InitStruct);
}

/**
 * @description: ��LDO��Դ
 * @return {*}
 */
void PWR_LDO_On(void)
{
    HAL_GPIO_WritePin(PWR_LDO_GPIO_Port , PWR_LDO_Pin , GPIO_PIN_SET);
}

/**
 * @description: �ر�LDO��Դ
 * @return {*}
 */
void PWR_LDO_Off(void)
{
    HAL_GPIO_WritePin(PWR_LDO_GPIO_Port , PWR_LDO_Pin , GPIO_PIN_RESET);
}

/**
 * @description: ��ʼ��LDO��ԴIO
 * @return {*}
 */
void PWR_LDO_GPIO_Init(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = PWR_LDO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PWR_LDO_GPIO_Port , &GPIO_InitStruct);
}

/**
 * @description: ��ʼ������ֽIO
 * @return {*}
 */
void EPD_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOB , EPD_RES_Pin | EPD_DC_Pin , GPIO_PIN_RESET);

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    GPIO_InitStruct.Pin = EPD_RES_Pin | EPD_DC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(EPD_RES_GPIO_Port , &GPIO_InitStruct);

    GPIO_InitStruct.Pin = EPD_BUSY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EPD_BUSY_GPIO_Port , &GPIO_InitStruct);
}

/**
 * @description: �رյ���ֽIO
 * @return {*}
 */
void EPD_GPIO_Deinit(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = EPD_RES_Pin | EPD_DC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EPD_RES_GPIO_Port , &GPIO_InitStruct);

    GPIO_InitStruct.Pin = EPD_BUSY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EPD_BUSY_GPIO_Port , &GPIO_InitStruct);
}

/**
 * @description: ��ʼ������ֽ����
 * @return {*}
 */
void EPD_Init(void)
{
    EPD_GPIO_Init();
    MX_SPI1_Init();
}

/**
 * @description: �رյ���ֽ����
 * @return {*}
 */
void EPD_Deinit(void)
{
    EPD_GPIO_Deinit();
    HAL_SPI_DeInit(&hspi1);
}

/**
 * @description: ��ʼ������IO
 * @return {*}
 */
void KEY_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = KEY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(KEY_GPIO_Port , &GPIO_InitStruct);
}

/**
 * @description: �رհ���IO
 * @return {*}
 */
void KEY_GPIO_Deinit(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = KEY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(KEY_GPIO_Port , &GPIO_InitStruct);
}

/**
 * @description: ��ȡ����״̬
 * @return {*}
 */
uint8_t KEY_Read(void)
{
    if (HAL_GPIO_ReadPin(KEY_GPIO_Port , KEY_Pin) == GPIO_PIN_RESET)
    {
        return KEY_DOWN;
    }
    else
    {
        return KEY_UP;
    }
}

/**
 * @description: ��������
 * @param {uint8_t} count_100ms
 * @return {*}
 */
uint8_t KEY_Hold(uint8_t count_100ms) {
    if (KEY_Read() == KEY_DOWN) {
        while (count_100ms > 0) {
            if (KEY_Read() == KEY_DOWN) {
                HAL_Delay(100);
            }
            else {
                return KEY_UP;
            }
            count_100ms--;
        }
        return KEY_DOWN;
    }
    return KEY_UP;
}

/**
 * @description: ��ʼ��WKUP����IO
 * @return {*}
 */
void WKUP_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = KEY_Pin;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(KEY_GPIO_Port , &GPIO_InitStruct);
    HAL_NVIC_SetPriority(EXTI2_IRQn , 1 , 0);
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);
    HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN4);
}

/**
 * @description: �ر�WKUP����IO
 * @return {*}
 */
void WKUP_Deinit(void) {
    HAL_NVIC_DisableIRQ(EXTI2_IRQn);
    HAL_PWR_DisableWakeUpPin(PWR_WAKEUP_PIN4);
}

/**
 * @description: ��ʼ�����״̬IO
 * @return {*}
 */
void BAT_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = BAT_CHRG_Pin | BAT_STDBY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(BAT_CHRG_GPIO_Port , &GPIO_InitStruct);
}

/**
 * @description: �رյ��״̬IO
 * @return {*}
 */
void BAT_GPIO_Deinit(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = BAT_CHRG_Pin | BAT_STDBY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(KEY_GPIO_Port , &GPIO_InitStruct);
}


