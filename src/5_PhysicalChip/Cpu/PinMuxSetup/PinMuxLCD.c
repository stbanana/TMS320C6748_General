/****************************************************************************/
/*                                                                          */
/*              创龙 DSP6748 开发板相关函数                                 */
/*                                                                          */
/*              2014年07月12日                                              */
/*                                                                          */
/****************************************************************************/
#include <stdint.h>
#include "hw_types.h"

#include "psc.h"
#include "gpio.h"

#include "PinMuxSetup.h"
#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"

/****************************************************************************/
/*                                                                          */
/*              宏定义                                                      */
/*                                                                          */
/****************************************************************************/
#define PINMUX16_LCD_ENABLE     (SYSCFG_PINMUX16_PINMUX16_31_28_LCD_D2 << \
                                 SYSCFG_PINMUX16_PINMUX16_31_28_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_27_24_LCD_D3 << \
                                 SYSCFG_PINMUX16_PINMUX16_27_24_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_23_20_LCD_D4 << \
                                 SYSCFG_PINMUX16_PINMUX16_23_20_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_19_16_LCD_D5 << \
                                 SYSCFG_PINMUX16_PINMUX16_19_16_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_15_12_LCD_D6 << \
                                 SYSCFG_PINMUX16_PINMUX16_15_12_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_11_8_LCD_D7 << \
                                 SYSCFG_PINMUX16_PINMUX16_11_8_SHIFT)

#define PINMUX17_LCD_ENABLE     (SYSCFG_PINMUX17_PINMUX17_31_28_LCD_D10 << \
                                 SYSCFG_PINMUX17_PINMUX17_31_28_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_27_24_LCD_D11 << \
                                 SYSCFG_PINMUX17_PINMUX17_27_24_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_23_20_LCD_D12 << \
                                 SYSCFG_PINMUX17_PINMUX17_23_20_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_19_16_LCD_D13 << \
                                 SYSCFG_PINMUX17_PINMUX17_19_16_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_15_12_LCD_D14 << \
                                 SYSCFG_PINMUX17_PINMUX17_15_12_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_11_8_LCD_D15 << \
                                 SYSCFG_PINMUX17_PINMUX17_11_8_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_7_4_LCD_D0 << \
                                 SYSCFG_PINMUX17_PINMUX17_7_4_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_3_0_LCD_D1 << \
                                 SYSCFG_PINMUX17_PINMUX17_3_0_SHIFT)

#define PINMUX18_LCD_ENABLE     (SYSCFG_PINMUX18_PINMUX18_31_28_LCD_MCLK << \
                                 SYSCFG_PINMUX18_PINMUX18_31_28_SHIFT) | \
                                (SYSCFG_PINMUX18_PINMUX18_27_24_LCD_PCLK << \
                                 SYSCFG_PINMUX18_PINMUX18_27_24_SHIFT) | \
                                (SYSCFG_PINMUX18_PINMUX18_7_4_LCD_D8 << \
                                 SYSCFG_PINMUX18_PINMUX18_7_4_SHIFT) | \
                                (SYSCFG_PINMUX18_PINMUX18_3_0_LCD_D9 << \
                                 SYSCFG_PINMUX18_PINMUX18_3_0_SHIFT)
 
#define PINMUX19_LCD_ENABLE     (SYSCFG_PINMUX19_PINMUX19_27_24_NLCD_AC_ENB_CS << \
                                 SYSCFG_PINMUX19_PINMUX19_27_24_SHIFT) | \
                                (SYSCFG_PINMUX19_PINMUX19_7_4_LCD_VSYNC << \
                                 SYSCFG_PINMUX19_PINMUX19_7_4_SHIFT) | \
                                (SYSCFG_PINMUX19_PINMUX19_3_0_LCD_HSYNC << \
                                 SYSCFG_PINMUX19_PINMUX19_3_0_SHIFT)

#define PINMUX1_GPIO0_7_ENABLE     (SYSCFG_PINMUX1_PINMUX1_3_0_GPIO0_7    << \
                                    SYSCFG_PINMUX1_PINMUX1_3_0_SHIFT)

#define PINMUX13_GPIO6_15_ENABLE   (SYSCFG_PINMUX13_PINMUX13_3_0_GPIO6_15 << \
                                    SYSCFG_PINMUX13_PINMUX13_3_0_SHIFT)

   
/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
void LCDPinMuxSetup(void)
{
     unsigned int savePinMux = 0;

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) & \
                        ~(SYSCFG_PINMUX16_PINMUX16_31_28 | \
                          SYSCFG_PINMUX16_PINMUX16_27_24 | \
                          SYSCFG_PINMUX16_PINMUX16_23_20 | \
                          SYSCFG_PINMUX16_PINMUX16_19_16 | \
                          SYSCFG_PINMUX16_PINMUX16_15_12 | \
                          SYSCFG_PINMUX16_PINMUX16_11_8);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) = \
          (PINMUX16_LCD_ENABLE | savePinMux);

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) & \
                        ~(SYSCFG_PINMUX17_PINMUX17_31_28 | \
                          SYSCFG_PINMUX17_PINMUX17_27_24 | \
                          SYSCFG_PINMUX17_PINMUX17_23_20 | \
                          SYSCFG_PINMUX17_PINMUX17_19_16 | \
                          SYSCFG_PINMUX17_PINMUX17_15_12 | \
                          SYSCFG_PINMUX17_PINMUX17_11_8 | \
                          SYSCFG_PINMUX17_PINMUX17_7_4 | \
                          SYSCFG_PINMUX17_PINMUX17_3_0);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) = \
          (PINMUX17_LCD_ENABLE | savePinMux);

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & \
                       ~(SYSCFG_PINMUX18_PINMUX18_31_28 | \
                         SYSCFG_PINMUX18_PINMUX18_27_24 | \
                         SYSCFG_PINMUX18_PINMUX18_7_4 |  \
                         SYSCFG_PINMUX18_PINMUX18_3_0);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) = \
           (PINMUX18_LCD_ENABLE | savePinMux);

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) & \
                       ~(SYSCFG_PINMUX19_PINMUX19_27_24 | \
                         SYSCFG_PINMUX19_PINMUX19_7_4 | \
                         SYSCFG_PINMUX19_PINMUX19_3_0);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) = \
          (PINMUX19_LCD_ENABLE | savePinMux);
}

/****************************************************************************/
/*                                                                          */
/*              延时                                                        */
/*                                                                          */
/****************************************************************************/
static void Delay(volatile unsigned int delay)
{
    while(delay--);
}

/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
void ConfigRasterGpioPins(void)
{
    unsigned int savePinmux = 0;
    
    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
                     ~(SYSCFG_PINMUX1_PINMUX1_3_0));

    // 背光控制引脚
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
          (PINMUX1_GPIO0_7_ENABLE | savePinmux);

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) &
                  ~(SYSCFG_PINMUX13_PINMUX13_3_0));

    // 电源使能引脚
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) =
          (PINMUX13_GPIO6_15_ENABLE | savePinmux);
}

/****************************************************************************/
/*                                                                          */
/*              LCD 使能                                                    */
/*                                                                          */
/****************************************************************************/
void ConfigRasterDisplayEnable(void)
{
    // 使能 GPIO 模块
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_GPIO, PSC_POWERDOMAIN_ALWAYS_ON,
		     PSC_MDCTL_NEXT_ENABLE);

    ConfigRasterGpioPins();

    // 设置管脚 48 (GP2[15]) 为背光控制
    GPIODirModeSet(SOC_GPIO_0_REGS, 48, GPIO_DIR_OUTPUT);

    // 设置管脚 139(GP18[10]) 为电源使能
    GPIODirModeSet(SOC_GPIO_0_REGS, 41, GPIO_DIR_OUTPUT);

    // 设置管脚 48 上升沿及下降沿触发中断
    GPIOIntTypeSet(SOC_GPIO_0_REGS, 48, GPIO_INT_TYPE_BOTHEDGE);
  
    // 设置管脚 41 上升沿及下降沿触发中断
    GPIOIntTypeSet(SOC_GPIO_0_REGS, 41, GPIO_INT_TYPE_BOTHEDGE);

    // 禁用背光
    GPIOPinWrite(SOC_GPIO_0_REGS, 48, 0);
    Delay(0xFFFFF);

    // 禁用电源
    GPIOPinWrite(SOC_GPIO_0_REGS, 41, 0);
    Delay(0xFFFFF);

    // 使能背光
    GPIOPinWrite(SOC_GPIO_0_REGS, 48, 1);
    Delay(0xFFFFF);

    // 使能电源
    GPIOPinWrite(SOC_GPIO_0_REGS, 41, 1);
    Delay(0xFFFFF);
}

/****************************************************************************/
/*                                                                          */
/*              返回识别码                                                  */
/*                                                                          */
/****************************************************************************/
unsigned int LCDVersionGet(void)
{
    return 1;
}
