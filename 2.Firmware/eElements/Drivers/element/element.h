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

struct elements elementInfo[ELEMENT_NUM] = {
    {.atomicNumber = 1,
     .nameCN = "氢",
     .nameEN = "Hydrogen",
     .atomicSymbol = "H",
     .relativeAtomicMass = 1.008},
    {.atomicNumber = 2,
     .nameCN = "氦",
     .nameEN = "Helium",
     .atomicSymbol = "He",
     .relativeAtomicMass = 4.0026},
    {.atomicNumber = 3,
     .nameCN = "锂",
     .nameEN = "Lithium",
     .atomicSymbol = "Li",
     .relativeAtomicMass = 6.94},
    {.atomicNumber = 4,
     .nameCN = "铍",
     .nameEN = "Beryllium",
     .atomicSymbol = "Be",
     .relativeAtomicMass = 9.0122},
    {.atomicNumber = 5,
     .nameCN = "硼",
     .nameEN = "Boron",
     .atomicSymbol = "B",
     .relativeAtomicMass = 10.81},
    {.atomicNumber = 6,
     .nameCN = "碳",
     .nameEN = "Carbon",
     .atomicSymbol = "C",
     .relativeAtomicMass = 12.011},
    {.atomicNumber = 7,
     .nameCN = "氮",
     .nameEN = "Nitrogen",
     .atomicSymbol = "N",
     .relativeAtomicMass = 14.007},
    {.atomicNumber = 8,
     .nameCN = "氧",
     .nameEN = "Oxygen",
     .atomicSymbol = "O",
     .relativeAtomicMass = 15.999},
    {.atomicNumber = 9,
     .nameCN = "氟",
     .nameEN = "Fluorine",
     .atomicSymbol = "F",
     .relativeAtomicMass = 18.998},
    {.atomicNumber = 10,
     .nameCN = "氖",
     .nameEN = "Neon",
     .atomicSymbol = "Ne",
     .relativeAtomicMass = 20.180},
    {.atomicNumber = 11,
     .nameCN = "钠",
     .nameEN = "Sodium",
     .atomicSymbol = "Na",
     .relativeAtomicMass = 22.990},
    {.atomicNumber = 12,
     .nameCN = "镁",
     .nameEN = "Magnesium",
     .atomicSymbol = "Mg",
     .relativeAtomicMass = 24.305},
    {.atomicNumber = 13,
     .nameCN = "铝",
     .nameEN = "Aluminum",
     .atomicSymbol = "Al",
     .relativeAtomicMass = 26.982}
     
};

#endif