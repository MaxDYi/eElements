/*
 * @Description  : �����洢
 * @Author       : MaxDYi
 * @Date         : 2024-02-15 14:22:57
 * @LastEditTime : 2024-02-16 09:55:34
 * @FilePath     :
 */
#ifndef __PARAMETER_H__
#define __PARAMETER_H__

#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "element.h"

struct parameters {
    uint32_t initFlag;
    uint8_t showStr[32];
    uint64_t sleepTime;
    uint8_t showFlag[ELEMENT_NUM];
};

void LoadParameters(struct parameters* para);

uint8_t SaveParameters(struct parameters* para);

#endif // __PARAMETER_H__