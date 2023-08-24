/****************************************************************************/
/*                                                                          */
/*              创龙 DSP6748 开发板相关函数                                 */
/*                                                                          */
/*              2014年07月12日                                              */
/*                                                                          */
/****************************************************************************/
#include "hw_types.h"

#include "PinMuxSetup.h"
#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"

#include "uart.h"
#include "psc.h"

/****************************************************************************/
/*                                                                          */
/*              宏定义                                                      */
/*                                                                          */
/****************************************************************************/
#define UART_STDIO_INSTANCE             (2)
#define UART_CONSOLE_BASE               (SOC_UART_2_REGS)

/****************************************************************************/
/*                                                                          */
/*              函数声明                                                    */
/*                                                                          */
/****************************************************************************/
static void UARTStdioInitExpClk(unsigned int baudRate,
                                unsigned int rxTrigLevel);
void UARTConsolePutc(unsigned char data);
unsigned char UARTConsoleGetc(void);
void UARTConsoleInit(void);

/****************************************************************************/
/*                                                                          */
/*              串口控制台配置                                              */
/*                                                                          */
/****************************************************************************/
static void UARTStdioInitExpClk(unsigned int baudRate, unsigned int rxTrigLevel)
{
     // 使能接收 / 发送
     UARTEnable(UART_CONSOLE_BASE);

     // 串口参数配置
     // 8位数据位 1位停止位 无校验
     UARTConfigSetExpClk(UART_CONSOLE_BASE, 
                         SOC_UART_2_MODULE_FREQ,
                         baudRate, 
                         UART_WORDL_8BITS,
                         UART_OVER_SAMP_RATE_16);


     // 使能接收 / 发送 FIFO
     UARTFIFOEnable(UART_CONSOLE_BASE);

     // 设置接收 FIFO 级别
     UARTFIFOLevelSet(UART_CONSOLE_BASE, rxTrigLevel);

}

/****************************************************************************/
/*                                                                          */
/*              串口控制台初始化                                            */
/*                                                                          */
/****************************************************************************/
void UARTConsoleInit(void)
{
     #if (0 == UART_STDIO_INSTANCE)
     {
          PSCModuleControl(SOC_PSC_0_REGS,9, 0, PSC_MDCTL_NEXT_ENABLE);
          UARTPinMuxSetup(0, FALSE);
     }
     
     #elif (1 == UART_STDIO_INSTANCE)
     {
          PSCModuleControl(SOC_PSC_1_REGS,12, 0, PSC_MDCTL_NEXT_ENABLE);
          UARTPinMuxSetup(1, FALSE);
     }

     #else 
     {
          PSCModuleControl(SOC_PSC_1_REGS,13, 0, PSC_MDCTL_NEXT_ENABLE);
          UARTPinMuxSetup(2, FALSE);
     }
     #endif
     
     UARTStdioInitExpClk(BAUD_115200, UART_RX_TRIG_LEVEL_1);
}

/****************************************************************************/
/*                                                                          */
/*              输出一个字符                                                */
/*                                                                          */
/****************************************************************************/
void UARTConsolePutc(unsigned char data)
{
     UARTCharPut(UART_CONSOLE_BASE, data);
}

/****************************************************************************/
/*                                                                          */
/*              取得一个字符                                                */
/*                                                                          */
/****************************************************************************/
unsigned char UARTConsoleGetc(void)
{
    return ((unsigned char)UARTCharGet(UART_CONSOLE_BASE));
}
