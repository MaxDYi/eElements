#include "epd_gui.h"

#define EPD_ACTOMICNUM_FONT 24
#define EPD_ACTOMICNUM_X 15
#define EPD_ACTOMICNUM_Y 10
#define EPD_ACTOMICSYMBOL_FONT 24
#define EPD_ACTOMICSYMBOL_X 15
#define EPD_ACTOMICSYMBOL_Y (EPD_ACTOMICNUM_Y + 30)
#define EPD_ACTOMICNAMEEN_FONT 24
#define EPD_ACTOMICNAMEEN_X 15
#define EPD_ACTOMICNAMEEN_Y (EPD_ACTOMICSYMBOL_Y + 30)
#define EPD_ACTOMICNAMECN_FONT 32
#define EPD_ACTOMICNAMECN_X 15
#define EPD_ACTOMICNAMECN_Y (EPD_ACTOMICNAMEEN_Y + 30)
#define EPD_ACTOMICMASS_FONT 24
#define EPD_ACTOMICMASS_X 15
#define EPD_ACTOMICMASS_Y (EPD_ACTOMICNAMECN_Y + 38)
#define EPD_ACTOMICELECTRONSHELL_FONT 24
#define EPD_ACTOMICELECTRONSHELL_X 165
#define EPD_ACTOMICELECTRONSHELL_Y 10
#define EPD_ACTOMICELECTRONSHELL_INTERNAL 25



void EPD_DrawFrame(uint8_t num) {
    EPD_Init();

    uint8_t Image_BW[EPD_W * EPD_H / 8];
    EPD_GUIInit();
    Paint_NewImage(Image_BW , EPD_W , EPD_H , 0 , WHITE);
    EPD_Clear(WHITE);

    struct elements ele = elementInfo[num];

    EPD_DrawAtomicNum(ele.atomicNumber);
    EPD_DrawAtomicSymbol(ele.atomicSymbol);
    EPD_DrawAtomicNameEN(ele.nameEN);
    EPD_DrawAtomicNameCN(num);
    EPD_DrawAtomicMass(ele.massAccuracy , ele.relativeAtomicMass);
    EPD_DrawElectronShell(ele.electronShellNumber , ele.electronShell);

    EPD_Display(Image_BW);

    EPD_Deinit();
}

void EPD_DrawEmpty(void) {
    EPD_Init();

    uint8_t Image_BW[EPD_W * EPD_H / 8];
    EPD_GUIInit();
    Paint_NewImage(Image_BW , EPD_W , EPD_H , 0 , WHITE);
    EPD_Clear(WHITE);

    EPD_Display(Image_BW);

    EPD_Deinit();
}

void EPD_DrawLowVoltage(void) {
    EPD_Init();

    uint8_t Image_BW[EPD_W * EPD_H / 8];
    EPD_GUIInit();
    Paint_NewImage(Image_BW , EPD_W , EPD_H , 0 , WHITE);
    EPD_Clear(WHITE);

    EPD_ShowString(12 , 76 , "Battery power is low," , 16 , BLACK);
    EPD_ShowString(8 , 108 , "please charge in time!" , 16 , BLACK);

    EPD_Display(Image_BW);

    EPD_Deinit();
}

void EPD_DrawAtomicNum(uint8_t atomicNumber) {
    if (atomicNumber < 10) {
        EPD_ShowNum(EPD_ACTOMICNUM_X , EPD_ACTOMICNUM_Y , atomicNumber , 1 , EPD_ACTOMICNUM_FONT , BLACK);
    }
    else if (atomicNumber < 100) {
        EPD_ShowNum(EPD_ACTOMICNUM_X , EPD_ACTOMICNUM_Y , atomicNumber , 2 , EPD_ACTOMICNUM_FONT , BLACK);
    }
    else {
        EPD_ShowNum(EPD_ACTOMICNUM_X , EPD_ACTOMICNUM_Y , atomicNumber , 3 , EPD_ACTOMICNUM_FONT , BLACK);
    }
}

void EPD_DrawAtomicSymbol(uint8_t* atomicSymbol) {
    EPD_ShowString(EPD_ACTOMICSYMBOL_X , EPD_ACTOMICSYMBOL_Y , atomicSymbol , EPD_ACTOMICSYMBOL_FONT , BLACK);
}

void EPD_DrawAtomicNameEN(uint8_t* nameEN) {
    EPD_ShowString(EPD_ACTOMICNAMEEN_X , EPD_ACTOMICNAMEEN_Y , nameEN , EPD_ACTOMICNAMEEN_FONT , BLACK);
}

void EPD_DrawAtomicNameCN(uint8_t num) {
    EPD_ShowChinese(EPD_ACTOMICNAMECN_X , EPD_ACTOMICNAMECN_Y , num , EPD_ACTOMICNAMECN_FONT , BLACK);
}

void EPD_DrawAtomicMass(uint8_t massAccuracy , float relativeAtomicMass) {
    if (massAccuracy == 1) {
        char relativeAtomicMass_str[10];
        sprintf(relativeAtomicMass_str , "%.3f" , (double)relativeAtomicMass);
        EPD_ShowString(EPD_ACTOMICMASS_X , EPD_ACTOMICMASS_Y , (uint8_t*)relativeAtomicMass_str , EPD_ACTOMICMASS_FONT , BLACK);
    }
    else {
        char relativeAtomicMass_str[10];
        sprintf(relativeAtomicMass_str , "(%.0f)" , (double)relativeAtomicMass);
        EPD_ShowString(EPD_ACTOMICMASS_X , EPD_ACTOMICMASS_Y , (uint8_t*)relativeAtomicMass_str , EPD_ACTOMICMASS_FONT , BLACK);
    }
}

void EPD_DrawElectronShell(uint8_t shellNum , uint8_t* shell) {
    for (uint8_t i = 0;i < shellNum; i++) {
        uint8_t len = 0;
        if (shell[i] < 10) {
            len = 1;
        }
        else if (shell[i] < 100) {
            len = 2;
        }
        else {
            len = 3;
        }
        EPD_ShowNum(EPD_ACTOMICELECTRONSHELL_X , EPD_ACTOMICELECTRONSHELL_Y + i * EPD_ACTOMICELECTRONSHELL_INTERNAL ,
            shell[i] , len , EPD_ACTOMICELECTRONSHELL_FONT , BLACK);
    }
}