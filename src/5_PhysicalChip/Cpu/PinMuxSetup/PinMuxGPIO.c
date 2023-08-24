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

/****************************************************************************/
/*                                                                          */
/*              宏定义                                                      */
/*                                                                          */
/****************************************************************************/
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

#define PINMUX19_GPIO6_1_ENABLE   (SYSCFG_PINMUX19_PINMUX19_23_20_GPIO6_1  << \
                                    SYSCFG_PINMUX19_PINMUX19_23_20_SHIFT)

#define PINMUX13_GPIO6_12_ENABLE  (SYSCFG_PINMUX13_PINMUX13_15_12_GPIO6_12 << \
                                    SYSCFG_PINMUX13_PINMUX13_15_12_SHIFT)

#define PINMUX13_GPIO6_13_ENABLE  (SYSCFG_PINMUX13_PINMUX13_11_8_GPIO6_13  << \
                                    SYSCFG_PINMUX13_PINMUX13_11_8_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
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

void GPIOBank6Pin1PinMuxSetup(void)
{
    unsigned int savePinmux = 0;

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) &
                 ~(SYSCFG_PINMUX19_PINMUX19_23_20));

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) =
         (PINMUX19_GPIO6_1_ENABLE | savePinmux);
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
