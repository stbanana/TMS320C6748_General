/********************************************************************************


 **** Copyright (C), 2020, Shenzhen SKONDA ELECTRONIC LTD  ****


 ********************************************************************************
 * File Name     : PinMuxUART.c
 * Author        : SKONDA
 * Date          : 2023-06-30
 * Version       : 1.0
********************************************************************************/
/**************************************************************************/
/*UART的引脚配置，改变Mux的函数*/
#include <stdint.h>
#include "hw_types.h"

#include "PinMuxSetup.h"
#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"

/****************************************************************************/
/*                                                                          */
/*              宏定义                                                      */
/*                                                                          */
/****************************************************************************/
// UART0
#define PINMUX3_UART0_CTS_ENABLE    (SYSCFG_PINMUX3_PINMUX3_27_24_UART0_CTS << \
                                     SYSCFG_PINMUX3_PINMUX3_27_24_SHIFT)

#define PINMUX3_UART0_RTS_ENABLE    (SYSCFG_PINMUX3_PINMUX3_31_28_UART0_RTS << \
                                     SYSCFG_PINMUX3_PINMUX3_31_28_SHIFT)

#define PINMUX3_UART0_TXD_ENABLE    (SYSCFG_PINMUX3_PINMUX3_23_20_UART0_TXD << \
                                     SYSCFG_PINMUX3_PINMUX3_23_20_SHIFT)

#define PINMUX3_UART0_RXD_ENABLE    (SYSCFG_PINMUX3_PINMUX3_19_16_UART0_RXD << \
                                     SYSCFG_PINMUX3_PINMUX3_19_16_SHIFT)

// UART1
#define PINMUX0_UART1_CTS_ENABLE    (SYSCFG_PINMUX0_PINMUX0_23_20_UART1_CTS << \
                                     SYSCFG_PINMUX0_PINMUX0_23_20_SHIFT)

#define PINMUX0_UART1_RTS_ENABLE    (SYSCFG_PINMUX0_PINMUX0_19_16_UART1_RTS << \
                                     SYSCFG_PINMUX0_PINMUX0_19_16_SHIFT)

#define PINMUX4_UART1_TXD_ENABLE    (SYSCFG_PINMUX4_PINMUX4_31_28_UART1_TXD << \
                                     SYSCFG_PINMUX4_PINMUX4_31_28_SHIFT)

#define PINMUX4_UART1_RXD_ENABLE    (SYSCFG_PINMUX4_PINMUX4_27_24_UART1_RXD << \
                                     SYSCFG_PINMUX4_PINMUX4_27_24_SHIFT)


// UART2
#define PINMUX0_UART2_CTS_ENABLE    (SYSCFG_PINMUX0_PINMUX0_31_28_UART2_CTS << \
                                     SYSCFG_PINMUX0_PINMUX0_31_28_SHIFT)

#define PINMUX0_UART2_RTS_ENABLE    (SYSCFG_PINMUX0_PINMUX0_27_24_UART2_RTS << \
                                     SYSCFG_PINMUX0_PINMUX0_27_24_SHIFT)

#define PINMUX4_UART2_TXD_ENABLE    (SYSCFG_PINMUX4_PINMUX4_23_20_UART2_TXD << \
                                     SYSCFG_PINMUX4_PINMUX4_23_20_SHIFT)

#define PINMUX4_UART2_RXD_ENABLE    (SYSCFG_PINMUX4_PINMUX4_19_16_UART2_RXD << \
                                     SYSCFG_PINMUX4_PINMUX4_19_16_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
// 若modemCtrlChoice为FALSE,则禁用流控，少配置两个流控引脚，仅有读写两个引脚
void UARTPinMuxSetup(uint32_t ui32PortNum, uint32_t modemCtrlChoice)
{
    uint32_t svPinMuxRtsCts = 0;
    uint32_t svPinMuxTxdRxd = 0;

    if(0 == ui32PortNum)
    {
          if(TRUE == modemCtrlChoice)
          {
               svPinMuxRtsCts = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                                 ~(SYSCFG_PINMUX3_PINMUX3_27_24 | \
                                   SYSCFG_PINMUX3_PINMUX3_31_28));

               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
                    (PINMUX3_UART0_CTS_ENABLE | \
                     PINMUX3_UART0_RTS_ENABLE | \
                     svPinMuxRtsCts);
          }

          svPinMuxTxdRxd = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                            ~(SYSCFG_PINMUX3_PINMUX3_23_20 | \
                              SYSCFG_PINMUX3_PINMUX3_19_16));
       
          HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
               (PINMUX3_UART0_TXD_ENABLE | \
                PINMUX3_UART0_RXD_ENABLE | \
                svPinMuxTxdRxd);
     }

     else if(1 == ui32PortNum)
     {
          if(TRUE == modemCtrlChoice)
          {
               svPinMuxRtsCts = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) & \
                                 ~(SYSCFG_PINMUX0_PINMUX0_23_20 | \
                                   SYSCFG_PINMUX0_PINMUX0_19_16));

               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) = \
                    (PINMUX0_UART1_CTS_ENABLE | \
                     PINMUX0_UART1_RTS_ENABLE | \
                     svPinMuxRtsCts);
          }
        
          svPinMuxTxdRxd = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                           ~(SYSCFG_PINMUX4_PINMUX4_31_28 | \
                             SYSCFG_PINMUX4_PINMUX4_27_24)); 

          HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
               (PINMUX4_UART1_TXD_ENABLE | \
                PINMUX4_UART1_RXD_ENABLE | \
                svPinMuxTxdRxd);
    }      
                       
     else if(2 == ui32PortNum)
     {

          if(TRUE == modemCtrlChoice)
          {
               svPinMuxRtsCts = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) & \
                                 ~(SYSCFG_PINMUX0_PINMUX0_31_28 | \
                                   SYSCFG_PINMUX0_PINMUX0_27_24));

               HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) = \
                    (PINMUX0_UART2_CTS_ENABLE | \
                     PINMUX0_UART2_RTS_ENABLE | \
                     svPinMuxRtsCts);
          }

          svPinMuxTxdRxd = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                            ~(SYSCFG_PINMUX4_PINMUX4_23_20 | \
                              SYSCFG_PINMUX4_PINMUX4_19_16));

          HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
               (PINMUX4_UART2_TXD_ENABLE | \
                PINMUX4_UART2_RXD_ENABLE | \
                svPinMuxTxdRxd);
          
    }

    else
    {

    }
}
