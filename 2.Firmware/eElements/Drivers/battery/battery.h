#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "main.h"
#include "opamp.h"
#include "adc.h"

float Bat_GetVoltage(void);

uint8_t Bat_GetMode(void);

#endif
