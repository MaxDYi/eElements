#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "main.h"
#include "opamp.h"
#include "adc.h"
#include "bsp.h"

#define BAT_LOW_VOLTAGE 3.6f

#define BAT_STATUS_CHARGING 0
#define BAT_STATUS_FULL 1
#define BAT_STATUS_ERROR 2
#define BAT_STATUS_NOBAT 3

float Bat_GetVoltage(void);

uint8_t Bat_GetMode(void);

uint8_t Bat_ReadChrg(void);

uint8_t Bat_ReadStdby(void);

#endif
