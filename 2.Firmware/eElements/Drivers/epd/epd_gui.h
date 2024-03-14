/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-03-14 11:44:48
 * @LastEditTime : 2024-03-14 14:18:17
 * @FilePath     : \eElements\Drivers\epd\epd_gui.h
 */
#ifndef __EPD_GUI_H__
#define __EPD_GUI_H__

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "bsp.h"
#include "epd.h"
#include "element.h"

void EPD_DrawFrame(uint8_t num);

void EPD_DrawEmpty(void);

#endif