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
#include "gpio.h"

void PWR_GPIOCLK_Enable(void);

void PWR_GPIOCLK_Disable(void);

void PWR_GPIO_ModeAnalog(void);

#endif
