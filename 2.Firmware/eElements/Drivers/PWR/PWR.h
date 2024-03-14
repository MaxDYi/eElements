/*
 * @FilePath: \ArcheryTimer_Appe:\eElements\2.Firmware\eElements\Drivers\PWR\PWR.h
 * @Author: MaxDYi
 * @Date: 2024-03-11 19:17:46
 * @LastEditors: MaxDYi
 * @LastEditTime: 2024-03-12 10:27:26
 * @Description:
 */

#ifndef __PWR_H__
#define __PWR_H__

#include "main.h"
#include "stm32l4xx_hal.h"
#include "gpio.h"
#include "usart.h"
#include "rtc.h"
#include "spi.h"
#include "adc.h"
#include "opamp.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void PWR_GPIOCLK_Enable(void);

void PWR_GPIOCLK_Disable(void);

void PWR_GPIO_ModeAnalog(void);

void PWR_EnterStop2Mode(void);


#endif
