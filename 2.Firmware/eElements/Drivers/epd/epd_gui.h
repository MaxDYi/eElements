/*
 * @Description  :
 * @Author       : MaxDYi
 * @Date         : 2024-03-14 11:44:48
 * @LastEditTime: 2024-03-19 14:26:05
 * @FilePath: \eElements\Drivers\epd\epd_gui.h
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

void EPD_DrawAtomicNum(uint8_t atomicNumber);

void EPD_DrawAtomicSymbol(uint8_t* atomicSymbol);

void EPD_DrawAtomicNameEN(uint8_t* nameEN);

void EPD_DrawAtomicNameCN(uint8_t num);

void EPD_DrawAtomicMass(uint8_t massAccuracy,float relativeAtomicMass);

void EPD_DrawElectronShell(uint8_t shellNum,uint8_t *shell);

#endif