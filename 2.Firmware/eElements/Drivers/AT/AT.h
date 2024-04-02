#ifndef __AT_H__
#define __AT_H__

#include "main.h"
#include "usart.h"
#include "parameter.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void com_printf(uint8_t* str);

void AT_Init(struct parameters* para);

void AT_ResponseOK(void);

void AT_ResponseError(void);

void AT_ResponseInfo(void);

void AT_ResponseShowStr(uint8_t* str);

void AT_ResponseSleepTime(uint32_t sleepTime);

void AT_ResponseBan(void);

void AT_ResponsePick(void);

void AT_RecevieReInit(void);

void AT_RecevieBan(uint8_t num);

void AT_ReceviePick(uint8_t num);

void AT_ReceivePickAll(void);

void AT_ReceiveReboot(void);

void AT_RecevieSleepTime(uint32_t sleepTime);

void AT_RecevieBan(uint8_t num);

void AT_ReceviePick(uint8_t num);

void AT_ParseCommand(uint8_t* buffer);

#endif // __AT_H__