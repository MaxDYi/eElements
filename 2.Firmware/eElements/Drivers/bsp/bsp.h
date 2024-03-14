
#ifndef __BSP_H__
#define __BSP_H__

#include "main.h"
#include "spi.h"

void LED_GREEN_On(void);

void LED_GREEN_Off(void);

void LED_GREEN_Init(void);

void LED_GREEN_Deinit(void);

void PWR_LDO_On(void);

void PWR_LDO_Off(void);

void PWR_LDO_GPIO_Init(void);

void EPD_GPIO_Init(void);

void EPD_GPIO_Deinit(void);

void EPD_Init(void);

void EPD_Deinit(void);

#endif
