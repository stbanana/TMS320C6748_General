/********************************************************************************


 **** Copyright (C), 2020, Shenzhen SKONDA ELECTRONIC LTD  ****


 ********************************************************************************
 * File Name     : PinMuxGPIO.c
 * Author        : SKONDA
 * Date          : 2023-06-30
 * Version       : 1.0
********************************************************************************/
/**************************************************************************/
/*GPIO的引脚配置，改变Mux的函数*/
#include <stdint.h>
#include "hw_types.h"

#include "PinMuxSetup.h"
#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"





/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*              BANK0系列                                                     */
/****************************************************************************/
/*               宏定义                                                      */

#define PINMUX1_GPIO0_0_ENABLE    (SYSCFG_PINMUX1_PINMUX1_31_28_GPIO0_0    << \
                                    SYSCFG_PINMUX1_PINMUX1_31_28_SHIFT)
 
#define PINMUX1_GPIO0_1_ENABLE    (SYSCFG_PINMUX1_PINMUX1_27_24_GPIO0_1    << \
                                    SYSCFG_PINMUX1_PINMUX1_27_24_SHIFT)

#define PINMUX1_GPIO0_2_ENABLE    (SYSCFG_PINMUX1_PINMUX1_23_20_GPIO0_2    << \
                                    SYSCFG_PINMUX1_PINMUX1_23_20_SHIFT)

#define PINMUX1_GPIO0_5_ENABLE    (SYSCFG_PINMUX1_PINMUX1_11_8_GPIO0_5     << \
                                    SYSCFG_PINMUX1_PINMUX1_11_8_SHIFT)

#define PINMUX1_GPIO0_6_ENABLE    (SYSCFG_PINMUX1_PINMUX1_7_4_GPIO0_6      << \
                                    SYSCFG_PINMUX1_PINMUX1_7_4_SHIFT)

#define PINMUX0_GPIO0_8_ENABLE    (SYSCFG_PINMUX0_PINMUX0_31_28_GPIO0_8     << \
                                    SYSCFG_PINMUX0_PINMUX0_31_28_SHIFT)

#define PINMUX0_GPIO0_10_ENABLE    (SYSCFG_PINMUX0_PINMUX0_23_20_GPIO0_10     << \
                                    SYSCFG_PINMUX0_PINMUX0_23_20_SHIFT)

#define PINMUX0_GPIO0_12_ENABLE    (SYSCFG_PINMUX0_PINMUX0_15_12_GPIO0_12     << \
                                    SYSCFG_PINMUX0_PINMUX0_15_12_SHIFT)

#define PINMUX0_GPIO0_13_ENABLE    (SYSCFG_PINMUX0_PINMUX0_11_8_GPIO0_13     << \
                                    SYSCFG_PINMUX0_PINMUX0_11_8_SHIFT)

#define PINMUX0_GPIO0_15_ENABLE    (SYSCFG_PINMUX0_PINMUX0_3_0_GPIO0_15     << \
                                    SYSCFG_PINMUX0_PINMUX0_3_0_SHIFT)
/*               函数                                                     */
void GPIOBank0Pin0PinMuxSetup(void)
{
     unsigned int savePinmux = 0;

     savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
                  ~(SYSCFG_PINMUX1_PINMUX1_31_28));

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
          (PINMUX1_GPIO0_0_ENABLE | savePinmux);
}

void GPIOBank0Pin1PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
                 ~(SYSCFG_PINMUX1_PINMUX1_27_24));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
         (PINMUX1_GPIO0_1_ENABLE | savePinmux);
}

void GPIOBank0Pin2PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
                 ~(SYSCFG_PINMUX1_PINMUX1_23_20));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
         (PINMUX1_GPIO0_2_ENABLE | savePinmux);
}

void GPIOBank0Pin5PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
                 ~(SYSCFG_PINMUX1_PINMUX1_11_8));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
         (PINMUX1_GPIO0_5_ENABLE | savePinmux);
}

void GPIOBank0Pin6PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
                 ~(SYSCFG_PINMUX1_PINMUX1_7_4));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
         (PINMUX1_GPIO0_6_ENABLE | savePinmux);
}

void GPIOBank0Pin8PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) &
                 ~(SYSCFG_PINMUX0_PINMUX0_31_28));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) =
         (PINMUX0_GPIO0_8_ENABLE | savePinmux);
}

void GPIOBank0Pin10PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) &
                 ~(SYSCFG_PINMUX0_PINMUX0_23_20));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) =
         (PINMUX0_GPIO0_10_ENABLE | savePinmux);
}
void GPIOBank0Pin12PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) &
                 ~(SYSCFG_PINMUX0_PINMUX0_15_12));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) =
         (PINMUX0_GPIO0_12_ENABLE | savePinmux);
}
void GPIOBank0Pin13PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) &
                 ~(SYSCFG_PINMUX0_PINMUX0_11_8));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) =
         (PINMUX0_GPIO0_13_ENABLE | savePinmux);
}
void GPIOBank0Pin15PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) &
                 ~(SYSCFG_PINMUX0_PINMUX0_3_0));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) =
         (PINMUX0_GPIO0_15_ENABLE | savePinmux);
}

/****************************************************************************/
/*              BANK1系列                                                     */
/****************************************************************************/
/*               宏定义                                                      */

#define PINMUX4_GPIO1_2_ENABLE   (SYSCFG_PINMUX4_PINMUX4_23_20_GPIO1_2  << \
                                    SYSCFG_PINMUX4_PINMUX4_23_20_SHIFT)

#define PINMUX2_GPIO1_15_ENABLE   (SYSCFG_PINMUX2_PINMUX2_3_0_GPIO1_15  << \
                                    SYSCFG_PINMUX2_PINMUX2_3_0_SHIFT)
/*               函数                                                     */
void GPIOBank1Pin2PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) &
                 ~(SYSCFG_PINMUX4_PINMUX4_23_20));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) =
         (PINMUX4_GPIO1_2_ENABLE | savePinmux);
}
void GPIOBank1Pin15PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) &
                 ~(SYSCFG_PINMUX2_PINMUX2_3_0));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) =
         (PINMUX2_GPIO1_15_ENABLE | savePinmux);
}

/****************************************************************************/
/*              BANK2系列                                                     */
/****************************************************************************/
/*               宏定义                                                      */

#define PINMUX6_GPIO2_4_ENABLE   (SYSCFG_PINMUX6_PINMUX6_15_12_GPIO2_4  << \
                                    SYSCFG_PINMUX6_PINMUX6_15_12_SHIFT)
/*               函数                                                     */
void GPIOBank2Pin4PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(6)) &
                 ~( SYSCFG_PINMUX6_PINMUX6_15_12));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(6)) =
         (PINMUX4_GPIO1_2_ENABLE | savePinmux);
}


/****************************************************************************/
/*              BANK6系列                                                     */
/****************************************************************************/
/*               宏定义                                                      */

#define PINMUX19_GPIO6_1_ENABLE   (SYSCFG_PINMUX19_PINMUX19_23_20_GPIO6_1  << \
                                    SYSCFG_PINMUX19_PINMUX19_23_20_SHIFT)

#define PINMUX19_GPIO6_2_ENABLE   (SYSCFG_PINMUX19_PINMUX19_19_16_GPIO6_2  << \
                                    SYSCFG_PINMUX19_PINMUX19_19_16_SHIFT)

#define PINMUX19_GPIO6_3_ENABLE   (SYSCFG_PINMUX19_PINMUX19_15_12_GPIO6_3  << \
                                    SYSCFG_PINMUX19_PINMUX19_15_12_SHIFT)

#define PINMUX14_GPIO6_6_ENABLE   (SYSCFG_PINMUX14_PINMUX14_7_4_GPIO6_6  << \
                                    SYSCFG_PINMUX14_PINMUX14_7_4_SHIFT)

#define PINMUX14_GPIO6_7_ENABLE   (SYSCFG_PINMUX14_PINMUX14_3_0_GPIO6_7  << \
                                    SYSCFG_PINMUX14_PINMUX14_3_0_SHIFT)

#define PINMUX13_GPIO6_12_ENABLE  (SYSCFG_PINMUX13_PINMUX13_15_12_GPIO6_12 << \
                                    SYSCFG_PINMUX13_PINMUX13_15_12_SHIFT)

#define PINMUX13_GPIO6_13_ENABLE  (SYSCFG_PINMUX13_PINMUX13_11_8_GPIO6_13  << \
                                    SYSCFG_PINMUX13_PINMUX13_11_8_SHIFT)

#define PINMUX13_GPIO6_14_ENABLE  (SYSCFG_PINMUX13_PINMUX13_7_4_GPIO6_14  << \
                                    SYSCFG_PINMUX13_PINMUX13_7_4_SHIFT)
/*               函数                                                     */
void GPIOBank6Pin1PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) &
                 ~(SYSCFG_PINMUX19_PINMUX19_23_20));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) =
         (PINMUX19_GPIO6_1_ENABLE | savePinmux);
}

void GPIOBank6Pin2PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) &
                 ~(SYSCFG_PINMUX19_PINMUX19_19_16));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) =
         (PINMUX19_GPIO6_2_ENABLE | savePinmux);
}

void GPIOBank6Pin3PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) &
                 ~(SYSCFG_PINMUX19_PINMUX19_15_12));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) =
         (PINMUX19_GPIO6_3_ENABLE | savePinmux);
}

void GPIOBank6Pin6PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) &
                 ~(SYSCFG_PINMUX14_PINMUX14_7_4));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) =
         (PINMUX14_GPIO6_6_ENABLE | savePinmux);
}

void GPIOBank6Pin7PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) &
                 ~(SYSCFG_PINMUX14_PINMUX14_3_0));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) =
         (PINMUX14_GPIO6_7_ENABLE | savePinmux);
}

void GPIOBank6Pin12PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) &
                 ~(SYSCFG_PINMUX13_PINMUX13_15_12));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) =
         (PINMUX13_GPIO6_12_ENABLE | savePinmux);
}

void GPIOBank6Pin13PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) &
                 ~(SYSCFG_PINMUX13_PINMUX13_11_8));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) =
         (PINMUX13_GPIO6_13_ENABLE | savePinmux);
}

void GPIOBank6Pin14PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) &
                 ~(SYSCFG_PINMUX13_PINMUX13_7_4));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) =
         (PINMUX13_GPIO6_14_ENABLE | savePinmux);
}


