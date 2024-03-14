#include "epd_gui.h"

void EPD_DrawFrame(uint8_t num) {
    EPD_Init();

    uint8_t Image_BW[EPD_W * EPD_H / 8];
    EPD_GUIInit();
    Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE);
    EPD_Clear(WHITE);

    EPD_ShowChinese(20, 0, 3, 32, BLACK);
    EPD_ShowChinese(52, 0, 4, 32, BLACK);
    EPD_ShowChinese(84, 0, 5, 32, BLACK);
    EPD_ShowChinese(116, 0, 6, 32, BLACK);
    EPD_ShowChinese(148, 0, 7, 32, BLACK);
    EPD_ShowString(60, 34, "2022/05/11", 16, BLACK);
    EPD_ShowString(40, 50, "ASCII:", 16, BLACK);
    EPD_ShowString(100, 50, "CODE:", 16, BLACK);
    EPD_Display(Image_BW);

    EPD_Deinit();
}