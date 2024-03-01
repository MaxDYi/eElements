/*
 * @FilePath: \ArcheryTimer_Appe:\eElements\2.Firmware\eElements\Drivers\epd\epd.h
 * @Author: MaxDYi
 * @Date: 2024-02-27 10:43:34
 * @LastEditors: MaxDYi
 * @LastEditTime: 2024-02-28 13:07:54
 * @Description:
 */
#ifndef __EPD_H
#define __EPD_H

#include "main.h"

//-----------------测试LED端口定义----------------

// #define LED_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)
// #define LED_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET)

//-----------------OLED端口定义----------------

#define EPD_SCL_Clr() HAL_GPIO_WritePin(EPD_SCL_GPIO_Port, EPD_SCL_Pin, GPIO_PIN_RESET) // CLK
#define EPD_SCL_Set() HAL_GPIO_WritePin(EPD_SCL_GPIO_Port, EPD_SCL_Pin, GPIO_PIN_SET)

#define EPD_SDA_Clr() HAL_GPIO_WritePin(EPD_SDA_GPIO_Port, EPD_SDA_Pin, GPIO_PIN_RESET) // DIN
#define EPD_SDA_Set() HAL_GPIO_WritePin(EPD_SDA_GPIO_Port, EPD_SDA_Pin, GPIO_PIN_SET)

#define EPD_RES_Clr() HAL_GPIO_WritePin(EPD_RES_GPIO_Port, EPD_RES_Pin, GPIO_PIN_RESET) // RES
#define EPD_RES_Set() HAL_GPIO_WritePin(EPD_RES_GPIO_Port, EPD_RES_Pin, GPIO_PIN_SET)

#define EPD_DC_Clr() HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_RESET) // DC
#define EPD_DC_Set() HAL_GPIO_WritePin(EPD_DC_GPIO_Port, EPD_DC_Pin, GPIO_PIN_SET)

#define EPD_CS_Clr() HAL_GPIO_WritePin(EPD_CS_GPIO_Port, EPD_CS_Pin, GPIO_PIN_RESET) // CS
#define EPD_CS_Set() HAL_GPIO_WritePin(EPD_CS_GPIO_Port, EPD_CS_Pin, GPIO_PIN_SET)

#define EPD_BUSY() HAL_GPIO_ReadPin(EPD_BUSY_GPIO_Port, EPD_BUSY_Pin)


#define uint16_t unsigned int

#define EPD_W 200
#define EPD_H 200

typedef struct
{
    uint8_t *Image;
    uint16_t Width;
    uint16_t Height;
    uint16_t WidthMemory;
    uint16_t HeightMemory;
    uint16_t Color;
    uint16_t Rotate;
    uint16_t WidthByte;
    uint16_t HeightByte;
} PAINT;
extern PAINT Paint;

#define ROTATE_0 0     // 屏幕正向显示
#define ROTATE_90 90   // 屏幕旋转90度显示
#define ROTATE_180 180 // 屏幕旋转180度显示
#define ROTATE_270 270 // 屏幕旋转270度显示

#define WHITE 0xFF // 显示白色
#define BLACK 0x00 // 显示黑色

void EPD_GPIOInit(void);                                                 // 初始化GPIO
void EPD_WR_Bus(uint8_t dat);                                            // 模拟SPI时序
void EPD_WR_REG(uint8_t reg);                                            // 写入一个命令
void EPD_WR_DATA8(uint8_t dat);                                          // 写入一个字节
void EPD_AddressSet(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye); // 设置位置函数
void EPD_Init(void);                                                     // 初始化屏幕

void Epaper_READBUSY(void);
void EPD_Update(void);

void Paint_NewImage(uint8_t *image, uint16_t Width, uint16_t Height, uint16_t Rotate, uint16_t Color);                // 创建画布控制显示方向
void EPD_Clear(uint16_t Color);                                                                                       // 清屏函数
void EPD_DrawPoint(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color);                                                 // 画点
void EPD_DrawLine(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color);                    // 画线
void EPD_DrawRectangle(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color, uint8_t mode); // 画矩形
void EPD_DrawCircle(uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Color, uint8_t mode);             // 画圆
void EPD_ShowChar(uint16_t x, uint16_t y, uint16_t chr, uint16_t size1, uint16_t color);                              // 显示字符
void EPD_ShowString(uint16_t x, uint16_t y, uint8_t *chr, uint16_t size1, uint16_t color);                            // 显示字符串
void EPD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint16_t len, uint16_t size1, uint16_t color);                 // 显示数字
void EPD_ShowChinese(uint16_t x, uint16_t y, uint16_t num, uint16_t size1, uint16_t color);                           // 显示中文
void EPD_ShowPicture(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, const uint8_t BMP[], uint16_t color);    // 显示图片
void EPD_Display(unsigned char *Image);                                                                               // 更新到屏幕
void EPD_GUIInit(void);                                                                                               // 屏幕GUI初始化

#endif
