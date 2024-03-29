
#ifndef __BSP_H__
#define __BSP_H__

#include "main.h"
#include "spi.h"

#define TRUE 1
#define FALSE 0

#define KEY_UP 0
#define KEY_DOWN 1



void LED_GREEN_On(void);

void LED_GREEN_Off(void);

void LED_GREEN_GPIO_Init(void);

void LED_GREEN_GPIO_Deinit(void);

void PWR_LDO_On(void);

void PWR_LDO_Off(void);

void PWR_LDO_GPIO_Init(void);

void EPD_GPIO_Init(void);

void EPD_GPIO_Deinit(void);

void EPD_Init(void);

void EPD_Deinit(void);

void KEY_GPIO_Init(void);

void KEY_GPIO_Deinit(void);

uint8_t KEY_Read(void);

uint8_t KEY_Hold(uint8_t count_100ms);

void BAT_GPIO_Init(void);

void BAT_GPIO_Deinit(void);

#endif
