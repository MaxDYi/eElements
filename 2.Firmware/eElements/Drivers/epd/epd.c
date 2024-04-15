#include "epd.h"

#define EPD_SPI hspi1

// ��ʼ��GPIO
void EPD_GPIOInit(void)
{
    // MX_SPI1_Init();
}

// ģ��SPIʱ��
void EPD_WR_Bus(uint8_t dat)
{
    HAL_SPI_Transmit(&EPD_SPI , &dat , 1 , 0xffff);
}

// д��һ������
void EPD_WR_REG(uint8_t reg)
{
    EPD_DC_Clr();
    EPD_WR_Bus(reg);
    EPD_DC_Set();
}

// д��һ���ֽ�
void EPD_WR_DATA8(uint8_t dat)
{
    EPD_WR_Bus(dat);
}

PAINT Paint;

void Epaper_READBUSY()
{
    while (1)
    {
        if (EPD_BUSY() == GPIO_PIN_RESET)
        {
            break;
        }
    }
}

void EPD_Update(void)
{
    EPD_WR_REG(0x22); // Display Update Control
    EPD_WR_DATA8(0xF7);
    // EPD_WR_DATA8(0xFF);
    EPD_WR_REG(0x20); // Activate Display Update Sequence
    Epaper_READBUSY();
}

// ��ʼ����Ļ
void EPD_GUIInit(void)
{
    EPD_GPIOInit();
    EPD_RES_Clr(); // Module reset
    HAL_Delay(20); // At least 10ms delay
    EPD_RES_Set();
    HAL_Delay(20); // At least 10ms delay

    Epaper_READBUSY();
    EPD_WR_REG(0x12); // SWRESET
    Epaper_READBUSY();

    EPD_WR_REG(0x01); // Driver output control
    EPD_WR_DATA8(0xC7);
    EPD_WR_DATA8(0x00);
    EPD_WR_DATA8(0x01);

    EPD_WR_REG(0x11); // data entry mode
    EPD_WR_DATA8(0x01);

    EPD_WR_REG(0x44); // set Ram-X address start/end position
    EPD_WR_DATA8(0x00);
    EPD_WR_DATA8(0x18); // 0x0F-->(15+1)*8=128

    EPD_WR_REG(0x45);   // set Ram-Y address start/end position
    EPD_WR_DATA8(0xC7); // 0xF9-->(249+1)=250
    EPD_WR_DATA8(0x00);
    EPD_WR_DATA8(0x00);
    EPD_WR_DATA8(0x00);

    EPD_WR_REG(0x3C); // BorderWavefrom
    EPD_WR_DATA8(0x05);

    //  EPD_WR_REG(0x21); //  Display update control
    //  EPD_WR_DATA8(0x00);
    //  EPD_WR_DATA8(0x80);

    EPD_WR_REG(0x18); // Read built-in temperature sensor
    EPD_WR_DATA8(0x80);

    EPD_WR_REG(0x4E); // set RAM x address count to 0;
    EPD_WR_DATA8(0x00);
    EPD_WR_REG(0x4F); // set RAM y address count to 0X199;
    EPD_WR_DATA8(0xC7);
    EPD_WR_DATA8(0x00);

    Epaper_READBUSY();
}

void Paint_NewImage(uint8_t* image , uint16_t Width , uint16_t Height , uint16_t Rotate , uint16_t Color)
{
    Paint.Image = 0x00;
    Paint.Image = image;

    Paint.WidthMemory = Width;
    Paint.HeightMemory = Height;
    Paint.Color = Color;
    Paint.WidthByte = (Width % 8 == 0) ? (Width / 8) : (Width / 8 + 1);
    Paint.HeightByte = Height;
    Paint.Rotate = Rotate;
    if (Rotate == ROTATE_0 || Rotate == ROTATE_180)
    {
        Paint.Width = Width;
        Paint.Height = Height;
    }
    else
    {
        Paint.Width = Height;
        Paint.Height = Width;
    }
}

void Paint_SetPixel(uint16_t Xpoint , uint16_t Ypoint , uint16_t Color)
{
    uint16_t X , Y;
    uint32_t Addr;
    uint8_t Rdata;
    switch (Paint.Rotate)
    {
    case 0:
    X = Xpoint;
    Y = Ypoint;
    break;
    case 90:
    X = Paint.WidthMemory - Ypoint - 1;
    Y = Xpoint;
    break;
    case 180:
    X = Paint.WidthMemory - Xpoint - 1;
    Y = Paint.HeightMemory - Ypoint - 1;
    break;
    case 270:
    X = Ypoint;
    Y = Paint.HeightMemory - Xpoint - 1;
    break;
    default:
    return;
    }
    Addr = X / 8 + Y * Paint.WidthByte;
    Rdata = Paint.Image[Addr];
    if (Color == BLACK)
    {
        Paint.Image[Addr] = Rdata & ~(0x80 >> (X % 8)); // ����Ӧ����λ��0
    }
    else
        Paint.Image[Addr] = Rdata | (0x80 >> (X % 8)); // ����Ӧ����λ��1
}

// ��������
void EPD_Clear(uint16_t Color)
{
    uint16_t X , Y;
    uint32_t Addr;
    for (Y = 0; Y < Paint.HeightByte; Y++)
    {
        for (X = 0; X < Paint.WidthByte; X++)
        { // 8 pixel =  1 byte
            Addr = X + Y * Paint.WidthByte;
            Paint.Image[Addr] = Color;
        }
    }
}

// ���㺯��
void EPD_DrawPoint(uint16_t Xpoint , uint16_t Ypoint , uint16_t Color)
{
    Paint_SetPixel(Xpoint - 1 , Ypoint - 1 , Color);
}

// ���µ��Դ�
void EPD_Display(unsigned char* Image)
{
    unsigned int Width , Height;
    Width = EPD_W;
    Height = EPD_H / 8;
    EPD_WR_REG(0x24);
    HAL_SPI_Transmit(&EPD_SPI , &Image[0] , Width * Height , 0xffff);
    EPD_Update();
}

// ��ֱ��
void EPD_DrawLine(uint16_t Xstart , uint16_t Ystart , uint16_t Xend , uint16_t Yend , uint16_t Color)
{
    uint16_t Xpoint , Ypoint;
    int dx , dy;
    int XAddway , YAddway;
    int Esp;
    char Dotted_Len;
    Xpoint = Xstart;
    Ypoint = Ystart;
    dx = (int)Xend - (int)Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
    dy = (int)Yend - (int)Ystart <= 0 ? Yend - Ystart : Ystart - Yend;

    XAddway = Xstart < Xend ? 1 : -1;
    YAddway = Ystart < Yend ? 1 : -1;

    Esp = dx + dy;
    Dotted_Len = 0;

    for (;;)
    {
        Dotted_Len++;
        EPD_DrawPoint(Xpoint , Ypoint , Color);
        if (2 * Esp >= dy)
        {
            if (Xpoint == Xend)
                break;
            Esp += dy;
            Xpoint += XAddway;
        }
        if (2 * Esp <= dx)
        {
            if (Ypoint == Yend)
                break;
            Esp += dx;
            Ypoint += YAddway;
        }
    }
}

// ������
void EPD_DrawRectangle(uint16_t Xstart , uint16_t Ystart , uint16_t Xend , uint16_t Yend , uint16_t Color , uint8_t mode)
{
    uint16_t i;
    if (mode)
    {
        for (i = Ystart; i < Yend; i++)
        {
            EPD_DrawLine(Xstart , i , Xend , i , Color);
        }
    }
    else
    {
        EPD_DrawLine(Xstart , Ystart , Xend , Ystart , Color);
        EPD_DrawLine(Xstart , Ystart , Xstart , Yend , Color);
        EPD_DrawLine(Xend , Yend , Xend , Ystart , Color);
        EPD_DrawLine(Xend , Yend , Xstart , Yend , Color);
    }
}

// ��Բ��
void EPD_DrawCircle(uint16_t X_Center , uint16_t Y_Center , uint16_t Radius , uint16_t Color , uint8_t mode)
{
    uint16_t Esp , sCountY;
    uint16_t XCurrent , YCurrent;
    XCurrent = 0;
    YCurrent = Radius;
    Esp = 3 - (Radius << 1);
    if (mode)
    {
        while (XCurrent <= YCurrent)
        { // Realistic circles
            for (sCountY = XCurrent; sCountY <= YCurrent; sCountY++)
            {
                EPD_DrawPoint(X_Center + XCurrent , Y_Center + sCountY , Color); // 1
                EPD_DrawPoint(X_Center - XCurrent , Y_Center + sCountY , Color); // 2
                EPD_DrawPoint(X_Center - sCountY , Y_Center + XCurrent , Color); // 3
                EPD_DrawPoint(X_Center - sCountY , Y_Center - XCurrent , Color); // 4
                EPD_DrawPoint(X_Center - XCurrent , Y_Center - sCountY , Color); // 5
                EPD_DrawPoint(X_Center + XCurrent , Y_Center - sCountY , Color); // 6
                EPD_DrawPoint(X_Center + sCountY , Y_Center - XCurrent , Color); // 7
                EPD_DrawPoint(X_Center + sCountY , Y_Center + XCurrent , Color);
            }
            if ((int)Esp < 0)
                Esp += 4 * XCurrent + 6;
            else
            {
                Esp += 10 + 4 * (XCurrent - YCurrent);
                YCurrent--;
            }
            XCurrent++;
        }
    }
    else
    { // Draw a hollow circle
        while (XCurrent <= YCurrent)
        {
            EPD_DrawPoint(X_Center + XCurrent , Y_Center + YCurrent , Color); // 1
            EPD_DrawPoint(X_Center - XCurrent , Y_Center + YCurrent , Color); // 2
            EPD_DrawPoint(X_Center - YCurrent , Y_Center + XCurrent , Color); // 3
            EPD_DrawPoint(X_Center - YCurrent , Y_Center - XCurrent , Color); // 4
            EPD_DrawPoint(X_Center - XCurrent , Y_Center - YCurrent , Color); // 5
            EPD_DrawPoint(X_Center + XCurrent , Y_Center - YCurrent , Color); // 6
            EPD_DrawPoint(X_Center + YCurrent , Y_Center - XCurrent , Color); // 7
            EPD_DrawPoint(X_Center + YCurrent , Y_Center + XCurrent , Color); // 0
            if ((int)Esp < 0)
                Esp += 4 * XCurrent + 6;
            else
            {
                Esp += 10 + 4 * (XCurrent - YCurrent);
                YCurrent--;
            }
            XCurrent++;
        }
    }
}

// ��ʾ�ַ�
void EPD_ShowChar(uint16_t x , uint16_t y , uint16_t chr , uint16_t size1 , uint16_t color)
{
    uint16_t i , m , temp , size2 , chr1;
    uint16_t x0 , y0;
    x += 1 , y += 1 , x0 = x , y0 = y;
    if (size1 == 8)
        size2 = 6;
    else
        size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2); // �õ�����һ���ַ���Ӧ������ռ���ֽ���
    chr1 = chr - ' ';                                              // ����ƫ�ƺ���?
    for (i = 0; i < size2; i++)
    {
        if (size1 == 8)
        {
            temp = asc2_0806[chr1][i];
        } // ����0806����
        else if (size1 == 12)
        {
            temp = asc2_1206[chr1][i];
        } // ����1206����
        else if (size1 == 16)
        {
            temp = asc2_1608[chr1][i];
        } // ����1608����
        else if (size1 == 24)
        {
            temp = asc2_2412[chr1][i];
        } // ����2412����
        else if (size1 == 50)
        {
            temp = asc2_5036[chr1][i];
        } // ����5036����
        else
            return;
        for (m = 0; m < 8; m++)
        {
            if (temp & 0x01)
                EPD_DrawPoint(x , y , color);
            else
                EPD_DrawPoint(x , y , !color);
            temp >>= 1;
            y++;
        }
        x++;
        if ((size1 != 8) && ((x - x0) == size1 / 2))
        {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
}

// ��ʾ�ַ���
// x,y:�������?
// size1:������?
//*chr:�ַ�����ʼ��ַ
// mode:0,��ɫ��ʾ;1,������ʾ
void EPD_ShowString(uint16_t x , uint16_t y , uint8_t* chr , uint16_t size1 , uint16_t color)
{
    while (*chr != '\0') // �ж��ǲ��ǷǷ��ַ�!
    {

        EPD_ShowChar(x , y , *chr , size1 , color);
        chr++;
        x += size1 / 2;
    }
}

// m^n
uint32_t EPD_Pow(uint16_t m , uint16_t n)
{
    uint32_t result = 1;
    while (n--)
    {
        result *= m;
    }
    return result;
}

// ��ʾ����
// x,y :�������?
// num :Ҫ��ʾ������
// len :���ֵ�λ��
// size:������?
// mode:0,��ɫ��ʾ;1,������ʾ
void EPD_ShowNum(uint16_t x , uint16_t y , uint32_t num , uint16_t len , uint16_t size1 , uint16_t color)
{
    uint8_t t , temp , m = 0;
    if (size1 == 8)
        m = 2;
    for (t = 0; t < len; t++)
    {
        temp = (num / EPD_Pow(10 , len - t - 1)) % 10;
        if (temp == 0)
        {
            EPD_ShowChar(x + (size1 / 2 + m) * t , y , '0' , size1 , color);
        }
        else
        {
            EPD_ShowChar(x + (size1 / 2 + m) * t , y , temp + '0' , size1 , color);
        }
    }
}

// ��ʾ����
// x,y:�������?
// num:���ֶ�Ӧ�����?
// mode:0,��ɫ��ʾ;1,������ʾ
void EPD_ShowChinese(uint16_t x , uint16_t y , uint16_t num , uint16_t size1 , uint16_t color)
{
    uint16_t m , temp;
    uint16_t x0 , y0;
    uint16_t i , size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1; // �õ�����һ���ַ���Ӧ������ռ���ֽ���
    x += 1 , y += 1 , x0 = x , y0 = y;
    for (i = 0; i < size3; i++)
    {
        if (size1 == 16)
        {
            //temp = Hzk1[num][i];
        } // ����16*16����
        else if (size1 == 24)
        {
            //temp = Hzk2[num][i];
        } // ����24*24����
        else if (size1 == 32)
        {
            //temp = Hzk3[num][i];
            temp = Hzk_e[num][i];
        } // ����32*32����
        else if (size1 == 64)
        {
            //temp = Hzk4[num][i];
        } // ����64*64����

        else
            return;
        for (m = 0; m < 8; m++)
        {
            if (temp & 0x01)
                EPD_DrawPoint(x , y , color);
            else
                EPD_DrawPoint(x , y , !color);
            temp >>= 1;
            y++;
        }
        x++;
        if ((x - x0) == size1)
        {
            x = x0;
            y0 = y0 + 8;
        }
        y = y0;
    }
}