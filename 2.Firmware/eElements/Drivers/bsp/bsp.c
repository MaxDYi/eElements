/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-03-14 09:53:20
 * @LastEditTime : 2024-03-14 11:47:09
 * @FilePath     : \eElements\Drivers\bsp\bsp.c
 */
#include "bsp.h"

void LED_GREEN_On(void)
{
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
}

void LED_GREEN_Off(void)
{
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
}

void LED_GREEN_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = LED_GREEN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void LED_GREEN_Deinit(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = LED_GREEN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LED_GREEN_GPIO_Port, &GPIO_InitStruct);
}

void PWR_LDO_On(void)
{
    HAL_GPIO_WritePin(PWR_LDO_GPIO_Port, PWR_LDO_Pin, GPIO_PIN_SET);
}

void PWR_LDO_Off(void)
{
    HAL_GPIO_WritePin(PWR_LDO_GPIO_Port, PWR_LDO_Pin, GPIO_PIN_RESET);
}

void PWR_LDO_GPIO_Init(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = PWR_LDO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(PWR_LDO_GPIO_Port, &GPIO_InitStruct);
}

void EPD_GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOB, EPD_RES_Pin | EPD_DC_Pin, GPIO_PIN_RESET);

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };

    GPIO_InitStruct.Pin = EPD_RES_Pin | EPD_DC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(EPD_RES_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = EPD_BUSY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EPD_BUSY_GPIO_Port, &GPIO_InitStruct);

}

void EPD_GPIO_Deinit(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = { 0 };
    GPIO_InitStruct.Pin = EPD_RES_Pin | EPD_DC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EPD_RES_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = EPD_BUSY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(EPD_BUSY_GPIO_Port, &GPIO_InitStruct);
}

void EPD_Init(void) {
    EPD_GPIO_Init();
    MX_SPI1_Init();
}

void EPD_Deinit(void) {
    EPD_GPIO_Deinit();
    HAL_SPI_DeInit(&hspi1);
}
