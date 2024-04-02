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

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "main.h"
#include "stm32l4xx_hal.h"
#include "usart.h"
#include "rtc.h"
#include "spi.h"
#include "opamp.h"
#include "bsp.h"
#include "battery.h"

void PWR_CLK_Disable(void);

void PWR_DisableGPIOA(void);

void PWR_DisableGPIOB(void);

void PWR_DisableGPIOC(void);

void PWR_DisableGPIOH(void);

void PWR_EnterStop2Mode(uint16_t stopTime);

void PWR_ExitStop2Mode(void);

uint8_t PWR_PowerEnough(void);

#endif
