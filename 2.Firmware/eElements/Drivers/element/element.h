/*
 * @FilePath: \eElements\Drivers\element\element.h
 * @Author: MaxDYi
 * @Date: 2024-02-27 10:49:54
 * @LastEditors: MaxDYi
 * @LastEditTime: 2024-03-19 14:19:28
 * @Description:
 */
#ifndef __EPD_H__
#define __EPD_H__

#include "main.h"

#define ELEMENT_NUM 64
#define ELEMENT_SAVE_ADDR 0x08003000

struct elements
{
    uint8_t atomicNumber;
    uint8_t nameCN[4];
    uint8_t nameEN[16];
    uint8_t atomicSymbol[2];
    float relativeAtomicMass;
    uint8_t massAccuracy;
    uint8_t electronShellNumber;
    uint8_t electronShell[7];
};


extern struct elements elementInfo[];

#endif