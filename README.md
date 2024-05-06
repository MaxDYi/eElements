# 墨水屏元素周期表

# 0 目录

1. 简介
2. 原理图
3. PCB
4. 外壳
5. 物料清单
6. 成本核算
7. 代码实现
8. 功耗分析

# 1 简介

电子沙漏使用STM32L431CCT6作为主控，驱动1.54寸墨水屏（200x200分辨率），待机功耗低。

- 原子序数、原子序数、相对原子量、核外电子排布以及中英文原子名称。
- 整机刷新功耗5mA，休眠功耗136uA，续航达数月。

# 2 原理图

![eElements-SCH_page-0001](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202405060924414.jpg)

# 3 PCB

![image-20240506092701951](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202405060927021.png)

![image-20240506092642711](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202405060926815.png)

PCB使用4层板设计，面积3.2x4.0cm，全部元器件均位于背面。

# 4 外壳

外壳设计详见github库中的**4.Component**部分，共设计**内层**与**外层**两部分，使用3D打印进行实现。

| 元件 |        尺寸         |  体积   |  表面积  |
| :--: | :-----------------: | :-----: | :------: |
| 内层 | 1.17 * 3.2 * 4.24cm | 2.49cm³ | 39.59cm² |
| 外层 | 1.37 * 3.5 * 4.34cm | 3.57cm³ | 73.94cm² |

# 5 物料清单

| Comment          | Description                                 | Designator                                       | Footprint          | Quantity |
| ---------------- | ------------------------------------------- | ------------------------------------------------ | ------------------ | -------- |
| 100nF            | 贴片电容/MLCC电容                           | C2, C4, C5, C6, C7,  C8, C21, C22, C26, C27      | C0402_M            | 10       |
| 1uF/50V          | 贴片电容/MLCC电容                           | C9, C10, C11, C12,  C13, C14, C15, C16, C17, C18 | C0402_M            | 10       |
| 10uF             | 贴片电容/MLCC电容                           | C19, C20                                         | C0402_M            | 2        |
| 1uF              | 贴片电容/MLCC电容                           | C23, C24                                         | C0402_M            | 2        |
| 22nF             | 贴片电容/MLCC电容                           | C25                                              | C0402_M            | 1        |
| 1N5819WS         | 肖特基二极管                                | D1, D2, D3, D4, D5,  D6, D7                      | SOD-323            | 7        |
| DEBUG PAD        | 调试断点焊盘                                | DE1                                              | DEBUG_B            | 1        |
| TP4056           | 锂电池充电管理                              | IC1                                              | SOIC-8_EP          | 1        |
| CON-24P          | 2.54寸墨水屏24P连接器                       | JP1                                              | FPC0.5-WT-24P-上接 | 1        |
| HDR-1X2          | 2P连接器                                    | JP2                                              | MX1.25-W-2P        | 1        |
| HDR-1X4          | 4P连接器                                    | JP3                                              | HDR1.27-LI-4P      | 1        |
| 47uH/1A          | 贴片小功率电感                              | L1                                               | SWPA4030           | 1        |
| GREEN            | 贴片LED                                     | LED1, LED3                                       | LED0603_R          | 2        |
| RED              | 贴片LED                                     | LED2                                             | LED0603_R          | 1        |
| AO3400           | N沟道 30V/4.2A                              | Q1, Q3                                           | SOT23-3N           | 2        |
| AO3401           | P沟道 30V/4.2A                              | Q2                                               | SOT23-3N           | 1        |
| 1K               | 贴片电阻                                    | R1, R7, R8                                       | R0402_M            | 3        |
| 100K             | 贴片电阻                                    | R2, R16                                          | R0402_M            | 2        |
| 4.7K             | 贴片电阻                                    | R3, R4                                           | R0402_M            | 2        |
| 1M               | 贴片电阻                                    | R5, R13, R14, R15,  R19                          | R0402_M            | 5        |
| 2.2R             | 贴片电阻                                    | R6                                               | R0603_M            | 1        |
| 10K              | 贴片电阻                                    | R9, R12, R17, R18                                | R0402_M            | 4        |
| 5.1K             | 贴片电阻                                    | R10, R11                                         | R0402_M            | 2        |
| 3x6x5            | 微动开关                                    | SW1                                              | SW 3*6*4.3-S-W     | 1        |
| 3x6x5            | 微动开关                                    | SW2, SW3                                         | SW SMD-3*6*2.5     | 2        |
| STM32L431CCT6    | Ultra-low-power with  FPU Arm Cortex-M4 MCU | U1                                               | LQFP48_M           | 1        |
| RT9193-33GB      | LDO 3.3V/0.3A                               | U2                                               | SOT-23-5           | 1        |
| CH340K           | USB转串口芯片, 内置晶振                     | U3                                               | SOP10_M            | 1        |
| TYPE-C 2.0  -16P | USB2.0_Type-C_16Pin母座                     | USBC1                                            | USB-C-SMD_16P      | 1        |

# 6 成本核算

|  类目  |       型号       | 采购总价 | 采购数量 | 采购单价 | 使用数量 |  小计  |
| :----: | :--------------: | :------: | :------: | :------: | :------: | :----: |
|  PCB   |   四层板1.6mm    |  ¥20.00  |    5     | ¥4.0000  |    1     | ¥4.00  |
|  SMT   |      经济型      | ¥100.06  |    5     | ¥20.0120 |    1     | ¥20.01 |
| 元器件 | STM32L431CCT6等  |  ¥7.20   |    1     | ¥7.2000  |    1     | ¥7.20  |
|  外壳  | 外壳（白色树脂） |  ¥4.96   |    1     | ¥4.9600  |    1     | ¥4.96  |
| 锂电池 | 500mAh单节锂电池 |  ¥8.20   |    1     | ¥8.2000  |    1     | ¥8.20  |
|  合计  |                  |          |          |          |          | ¥65.92 |

# 7 代码实现

## 7.1 软件环境

IAR 9.30

STM32CubeMX 6.5.0

## 7.2 主要库

使用到的库位于**\eHorglass\Drivers**路径下。

| 库          | 功能                                 |
| ----------- | ------------------------------------ |
| battery     | 锂电池相关库                         |
| bsp         | 开发板相关                           |
| element     | 元素信息存储                         |
| epd         | 墨水屏驱动库                         |
| parameter   | 运行参数配置库                       |
| PWRSandMove | 电源与低功耗控制砂砾运动控制核心算法 |

# 8 功耗分析

使用Power Profiler Kit II进行功耗分析。

![image-20240506094910203](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202405060949288.png)

固件采取刷新后休眠30s的运行模式，对功耗进行测量。

|   模式   |   功耗   | 时长 |
| :------: | :------: | :--: |
| 关机功耗 | 30.95uA  |  0s  |
| 刷新功耗 |  5.09mA  |  2s  |
| 休眠功耗 | 136.13uA | 10s  |



![ppk-20240401T023107](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202404011031758.png)

![ppk-20240401T023441](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202404011035941.png)

![ppk-20240401T044010](https://raw.githubusercontent.com/MaxDYi/PicGo/main/202404011240165.png)
