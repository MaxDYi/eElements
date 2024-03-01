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

//-----------------����LED�˿ڶ���----------------

// #define LED_ON HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET)
// #define LED_OFF HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET)

//-----------------OLED�˿ڶ���----------------

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

#define ROTATE_0 0     // ��Ļ������ʾ
#define ROTATE_90 90   // ��Ļ��ת90����ʾ
#define ROTATE_180 180 // ��Ļ��ת180����ʾ
#define ROTATE_270 270 // ��Ļ��ת270����ʾ

#define WHITE 0xFF // ��ʾ��ɫ
#define BLACK 0x00 // ��ʾ��ɫ

void EPD_GPIOInit(void);                                                 // ��ʼ��GPIO
void EPD_WR_Bus(uint8_t dat);                                            // ģ��SPIʱ��
void EPD_WR_REG(uint8_t reg);                                            // д��һ������
void EPD_WR_DATA8(uint8_t dat);                                          // д��һ���ֽ�
void EPD_AddressSet(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye); // ����λ�ú���
void EPD_Init(void);                                                     // ��ʼ����Ļ

void Epaper_READBUSY(void);
void EPD_Update(void);

void Paint_NewImage(uint8_t *image, uint16_t Width, uint16_t Height, uint16_t Rotate, uint16_t Color);                // ��������������ʾ����
void EPD_Clear(uint16_t Color);                                                                                       // ��������
void EPD_DrawPoint(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color);                                                 // ����
void EPD_DrawLine(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color);                    // ����
void EPD_DrawRectangle(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color, uint8_t mode); // ������
void EPD_DrawCircle(uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Color, uint8_t mode);             // ��Բ
void EPD_ShowChar(uint16_t x, uint16_t y, uint16_t chr, uint16_t size1, uint16_t color);                              // ��ʾ�ַ�
void EPD_ShowString(uint16_t x, uint16_t y, uint8_t *chr, uint16_t size1, uint16_t color);                            // ��ʾ�ַ���
void EPD_ShowNum(uint16_t x, uint16_t y, uint32_t num, uint16_t len, uint16_t size1, uint16_t color);                 // ��ʾ����
void EPD_ShowChinese(uint16_t x, uint16_t y, uint16_t num, uint16_t size1, uint16_t color);                           // ��ʾ����
void EPD_ShowPicture(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, const uint8_t BMP[], uint16_t color);    // ��ʾͼƬ
void EPD_Display(unsigned char *Image);                                                                               // ���µ���Ļ
void EPD_GUIInit(void);                                                                                               // ��ĻGUI��ʼ��

#endif
