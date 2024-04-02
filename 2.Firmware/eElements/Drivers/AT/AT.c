#include "AT.h"

#define AT_CMD_LEN 256

#define PARA_SAND_NUM_MAX 64
#define PARA_SLEEP_TIME_MIN 10
#define PARA_SLEEP_TIME_MAX 0xFFFFFFFF

struct parameters* flashPara;


/**
 * @description: 串口1输出
 * @param {uint8_t} *str
 * @return {*}
 */
void com_printf(uint8_t* str)
{
    uint8_t len = strlen((char*)str);
    HAL_UART_Transmit(&huart1 , str , len , 0xFFFF);
}

/**
 * @description:AT指令初始化
 * @param {parameters} *para
 * @return {*}
 */
void AT_Init(struct parameters* para)
{
    flashPara = para;
}

/**
 * @description: AT指令回复OK
 * @return {*}
 */
void AT_ResponseOK(void)
{
    com_printf("OK\r\n");
}

/**
 * @description: AT指令回复ERROR
 * @return {*}
 */
void AT_ResponseError(void)
{
    com_printf("ERROR\r\n");
}

/**
 * @description: AT指令回复系统信息
 * @return {*}
 */
void AT_ResponseInfo(void)
{
    com_printf("Designed By MaxDYi\r\n2024/02\r\n");
}

/**
 * @description: AT指令回复显示字符串
 * @param {uint8_t} *str
 * @return {*}
 */
void AT_ResponseShowStr(uint8_t* str) {
    uint8_t buffer[64];
    sprintf((char*)buffer , "AT+SHOWSTR=%s\r\n" , str);
    com_printf(buffer);
}

/**
 * @description: AT指令回复睡眠时间
 * @param {uint32_t} time
 * @return {*}
 */
void AT_ResponseSleepTime(uint32_t sleepTime)
{
    uint8_t buffer[32];
    sprintf((char*)buffer , "AT+SLEEPTIME=%d\r\n" , sleepTime);
    com_printf(buffer);
}

/**
 * @description: AT指令回复不显示元素号
 * @return {*}
 */
void AT_ResponseBan(void) {
    com_printf("Ban elements:\r\n");
    for (uint8_t i = 0;i < ELEMENT_NUM;i++) {
        if (flashPara->showFlag[i] == 0) {
            uint8_t buffer[32];
            sprintf((char*)buffer , "%d\t" , i + 1);
            com_printf(buffer);
        }
    }
    com_printf("\r\n");
}

/**
 * @description: AT指令回复显示元素号
 * @return {*}
 */
void AT_ResponsePick(void) {
    com_printf("Pick elements:\r\n");
    for (uint8_t i = 0;i < ELEMENT_NUM;i++) {
        if (flashPara->showFlag[i] == 1) {
            uint8_t buffer[32];
            sprintf((char*)buffer , "%d\t" , i + 1);
            com_printf(buffer);
        }
    }
    com_printf("\r\n");
}

/**
 * @description: AT指令接收重置
 * @return {*}
 */
void AT_RecevieReInit(void)
{
    flashPara->initFlag = 0;
    SaveParameters(flashPara);
}

/**
 * @description: AT指令接收不显示的元素
 * @param {uint8_t} num
 * @return {*}
 */
void AT_RecevieBan(uint8_t num) {
    flashPara->showFlag[num - 1] = 0;
    SaveParameters(flashPara);
}

/**
 * @description: AT指令接收显示的元素
 * @param {uint8_t} num
 * @return {*}
 */
void AT_ReceviePick(uint8_t num) {
    flashPara->showFlag[num - 1] = 1;
    SaveParameters(flashPara);
}

/**
 * @description: AT指令接收显示所有元素
 * @return {*}
 */
void AT_ReceivePickAll(void) {
    for (uint8_t i = 0;i < ELEMENT_NUM;i++) {
        flashPara->showFlag[i] = 1;
    }
    SaveParameters(flashPara);
}

/**
 * @description: AT指令接收重启
 * @return {*}
 */
void AT_ReceiveReboot(void) {
    NVIC_SystemReset();
}

/**
 * @description: AT指令接收帧时间
 * @param {uint32_t} time
 * @return {*}
 */
void AT_RecevieSleepTime(uint32_t sleepTime)
{
    if ((sleepTime >= PARA_SLEEP_TIME_MIN))
    {
        flashPara->sleepTime = sleepTime;
        SaveParameters(flashPara);
        AT_ResponseSleepTime(sleepTime);
    }
    else
    {
        AT_ResponseError();
    }
}

/**
 * @description: AT指令解析
 * @param {uint8_t} *buffer
 * @return {*}
 */
void AT_ParseCommand(uint8_t* buffer)
{
    char command[AT_CMD_LEN];
    char questionMark;
    int number;
    memset(command , 0 , AT_CMD_LEN);

    // 首先检查是否以"AT+"开头，并提取CMD部分
    if (sscanf((char*)buffer , "AT+%[^=]=%c" , command , &questionMark) == 2)
    {
        // 检查"?"位置的字符是'?'还是数字
        if (questionMark == '?')
        {
            if (strcmp(command , "INFO") == 0)
            {
                AT_ResponseInfo();
            }
            else if (strcmp(command , "SHOWSTR") == 0) {
                AT_ResponseShowStr(flashPara->showStr);
            }
            else if (strcmp(command , "SLEEPTIME") == 0)
            {
                AT_ResponseSleepTime(flashPara->sleepTime);
            }
        }
        else
        {
            // 如果不是'?'，假设是数字，尝试解析整个字符串
            int result = sscanf((char*)buffer , "AT+%[^=]=%d" , command , &number);
            if (result == 2)
            {
                // 解析成功，处理数字情况
                if (strcmp(command , "REINIT") == 0)
                {
                    if (number == 1)
                    {
                        AT_RecevieReInit();
                    }
                    else
                    {
                        AT_ResponseError();
                    }
                }
                else if (strcmp(command , "BAN") == 0) {
                    if (number >= 1 && number <= ELEMENT_NUM) {
                        AT_RecevieBan(number);
                    }
                    else {
                        AT_ResponseError();
                    }
                }
                else if (strcmp(command , "PICK") == 0) {
                    if (number >= 1 && number <= ELEMENT_NUM) {
                        AT_ReceviePick(number);
                    }
                    else {
                        AT_ResponseError();
                    }
                }
            }
            else
            {
                AT_ResponseError();
            }
        }
    }
    else
    {
        AT_ResponseError();
    }
}
