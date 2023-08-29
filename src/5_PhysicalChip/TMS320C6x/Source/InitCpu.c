//******************************************************************************
//*                               InitCpu.c                                  *
//******************************************************************************
//*           Copyright (c) 2020 SKONDA ELECTRONIC LTD                        *
//******************************************************************************
//* FILE NAME  : InitCpu.c
//* DESCRIPTION:
//* ORIGINATOR : Sven
//* DATE       : 11/07/2022
//* VERSION    : 1.0.0
//******************************************************************************
/*==============================================================================
                           head file information
===============================================================================*/
#include "Includes.h"
/******************************************************************************
                           constant variables
*******************************************************************************/

/******************************************************************************
                           external variables
*******************************************************************************/
/******************************************************************************
                           private variables
*******************************************************************************/
uint32_t ui32SysClock;
/******************************************************************************
                           external functions
*******************************************************************************/

/******************************************************************************
                           private functions
*******************************************************************************/
static void PSCInit(void);      //PSC时钟使能

static void CaCheInit(void);    //缓存初始化
static void InterruptInit(void);    //中断函数配置
static void GPIOInit(void);     //GPIO功能配置
static void UARTInit(void);     //UART功能配置
static void uPPInit(void);      //uPP功能配置

/******************************************************************************
function name : InitCpu
Description   :
*******************************************************************************/
void InitCpu(void)
{
    /*以下硬件PCB相关*/
    PSCInit();      //PSC时钟配置
    PinoutSet();    //引脚复用配置
    /*以下软件功能相关*/
    CaCheInit();    //缓存初始化
    InterruptInit();    //中断函数绑定
    GPIOInit();    //GPIO功能配置
    UARTInit();    //UART功能配置
    uPPInit();     //uPP功能配置
}

static void PSCInit(void)
{
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_TC2, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);    // 使能 tc2 模块 freertos的支持定时器
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_GPIO, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);    // 使能 GPIO 模块
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_UART2, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);   // 使能 UART2 模块
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_UPP, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);     // 使能 Upp 模块
}

void CaCheInit(void)
{
    CacheEnableMAR((unsigned int)0xC0000000, (unsigned int)0x10000000);
    CacheEnable(L1PCFG_L1PMODE_32K | L1DCFG_L1DMODE_32K | L2CFG_L2MODE_256K);
}

void InterruptInit(void)
{
    IntDSPINTCInit();   // 初始化 DSP 中断控制器
    IntGlobalEnable();  // 使能 DSP 全局中断

    /*这两个rtos支持函数必须在中断向量表中直接写入*/
//    IntRegister(portTICK_INT_MASK, _vPortTickISR);      //rtos的支持中断 进程切换    占用15号中断
//    IntRegister(portYIELD_INT_MASK, _vPortYieldISR);    //rtos的支持中断 定时器2     占用14号中断

    /* 绑定UART2中断函数 */
    IntRegister(C674X_MASK_UART2, UART2StdioIntHandler);
    IntEventMap(C674X_MASK_UART2, SYS_INT_UART2_INT);
    IntEnable(C674X_MASK_UART2);

    /* 绑定uPP中断函数 */
    IntRegister(C674X_MASK_INT5, uPPIsr);
    IntEventMap(C674X_MASK_INT5, SYS_INT_UPP_INT);
    IntEnable(C674X_MASK_INT5);
}

static void GPIOInit(void)
{
    /* 核心板 LED */
    GPIODirModeSet(SOC_GPIO_0_REGS, GPIO_BANK_BASE_6+GPIO_PIN_ADDTL_12, GPIO_DIR_OUTPUT);   // GPIO6[12]

    /* 底板 LED */
    GPIODirModeSet(SOC_GPIO_0_REGS, GPIO_BANK_BASE_0+GPIO_PIN_ADDTL_0, GPIO_DIR_OUTPUT);    // GPIO0[0]     D7
}

static void UARTInit(void)
{
    /* UART2 */
    UARTStdioConfig(2, C674X_MASK_UART2, BAUD_115200, UART_2_FREQ);
}

static void uPPInit(void)
{
    /* uPP数据格式配置 */
    uPPDataFmtConfig(SOC_UPP_0_REGS, uPP_CHA, uPP_DataPackingFmt_LJZE | uPP_DataPacking_FULL
                            | uPP_InterfaceWidth_8BIT | uPP_DataRate_SINGLE);
    uPPDataFmtConfig(SOC_UPP_0_REGS, uPP_CHB, uPP_DataPackingFmt_LJZE | uPP_DataPacking_FULL
                            | uPP_InterfaceWidth_8BIT | uPP_DataRate_SINGLE);
    /* uPP通道配置 */
    uPPChannelConfig(SOC_UPP_0_REGS, uPP_DDRDEMUX_DISABLE | uPP_SDRTXIL_DISABLE | uPP_CHN_TWO
                                | uPP_DUPLEX0);
    /* uPP引脚配置 */
    uPPPinConfig(SOC_UPP_0_REGS, uPP_CHA, uPP_PIN_TRIS | uPP_PIN_ENABLE | uPP_PIN_WAIT | uPP_PIN_START);
    uPPPinConfig(SOC_UPP_0_REGS, uPP_CHB, uPP_PIN_ENABLE | uPP_PIN_WAIT | uPP_PIN_START);
    /* uPP时钟配置 */
    uPPClkConfig(SOC_UPP_0_REGS, uPP_CHB, 57000000, UPP_FREQ, uPP_PIN_PHASE_NORMAL);
    /* uPP空闲输出配置 */
    uPPIdleValueConfig(SOC_UPP_0_REGS, uPP_CHB, 0xAAAA);
    /* uPP中断使能配置 */
    uPPIntEnable(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOW);
    uPPIntEnable(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_EOW);
    /* uPP使能 */
    uPPEnable(SOC_UPP_0_REGS);
}


