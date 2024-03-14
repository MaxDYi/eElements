#include "epd_gui.h"


void EPD_DrawFrame(uint8_t num) {
    EPD_Init();

    uint8_t Image_BW[EPD_W * EPD_H / 8];
    EPD_GUIInit();
    Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE);
    EPD_Clear(WHITE);

    struct elements ele = elementInfo[num];

    EPD_ShowNum(10, 10, ele.atomicNumber, 1, 24, BLACK);
    EPD_ShowString(10, 40, ele.atomicSymbol, 24, BLACK);
    EPD_ShowString(10, 70, ele.nameEN, 24, BLACK);
    //EPD_ShowNum(10, 100, ele.relativeAtomicMass, 1, 24, BLACK);
    char relativeAtomicMass_str[10];
    sprintf(relativeAtomicMass_str, "%.3f", (double)ele.relativeAtomicMass);
    EPD_ShowString(10, 100, (uint8_t*)relativeAtomicMass_str, 24, BLACK);
    EPD_Display(Image_BW);

    EPD_Deinit();
}

void EPD_DrawEmpty(void) {
    EPD_Init();

    uint8_t Image_BW[EPD_W * EPD_H / 8];
    EPD_GUIInit();
    Paint_NewImage(Image_BW, EPD_W, EPD_H, 0, WHITE);
    EPD_Clear(WHITE);

    EPD_Display(Image_BW);

    EPD_Deinit();
}