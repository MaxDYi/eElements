/*
 * @FilePath: \ArcheryTimer_Appe:\eElements\2.Firmware\eElements\Drivers\element\element.h
 * @Author: MaxDYi
 * @Date: 2024-02-27 10:49:54
 * @LastEditors: MaxDYi
 * @LastEditTime: 2024-02-27 11:22:25
 * @Description:
 */
#ifndef __EPD_H__
#define __EPD_H__

#include "main.h"

#define ELEMENT_NUM 18
#define ELEMENT_SAVE_ADDR 0x08003000

struct elements
{
    uint8_t atomicNumber;
    uint8_t nameCN[4];
    uint8_t nameEN[16];
    uint8_t atomicSymbol[2];
    float relativeAtomicMass;
};


extern struct elements elementInfo[];

#endif