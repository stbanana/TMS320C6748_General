/****************************************************************************/
/*                                                                          */
/*              创龙 DSP6748 开发板相关函数                                 */
/*                                                                          */
/*              2014年07月12日                                              */
/*                                                                          */
/****************************************************************************/
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
#define PINMUX0_MCASP0_ACLKR_ENABLE    (SYSCFG_PINMUX0_PINMUX0_3_0_ACLKR0 << \
                                       SYSCFG_PINMUX0_PINMUX0_3_0_SHIFT)

#define PINMUX0_MCASP0_ACLKX_ENABLE    (SYSCFG_PINMUX0_PINMUX0_7_4_ACLKX0 << \
                                       SYSCFG_PINMUX0_PINMUX0_7_4_SHIFT)

#define PINMUX0_MCASP0_AFSR_ENABLE     (SYSCFG_PINMUX0_PINMUX0_11_8_AFSR0 << \
                                       SYSCFG_PINMUX0_PINMUX0_11_8_SHIFT)

#define PINMUX0_MCASP0_AFSX_ENABLE     (SYSCFG_PINMUX0_PINMUX0_15_12_AFSX0 << \
                                       SYSCFG_PINMUX0_PINMUX0_15_12_SHIFT)

#define PINMUX0_MCASP0_AHCLKR_ENABLE   (SYSCFG_PINMUX0_PINMUX0_19_16_AHCLKR0 << \
                                       SYSCFG_PINMUX0_PINMUX0_19_16_SHIFT)

#define PINMUX0_MCASP0_AHCLKX_ENABLE   (SYSCFG_PINMUX0_PINMUX0_23_20_AHCLKX0 << \
                                       SYSCFG_PINMUX0_PINMUX0_23_20_SHIFT)

#define PINMUX0_MCASP0_AMUTE_ENABLE    (SYSCFG_PINMUX0_PINMUX0_27_24_AMUTE0 << \
                                       SYSCFG_PINMUX0_PINMUX0_27_24_SHIFT)

//AXR[11] 和 AXR[12]
#define PINMUX1_MCASP0_AXR11_ENABLE    (SYSCFG_PINMUX1_PINMUX1_19_16_AXR0_11 <<\
                                       SYSCFG_PINMUX1_PINMUX1_19_16_SHIFT)

#define PINMUX1_MCASP0_AXR12_ENABLE    (SYSCFG_PINMUX1_PINMUX1_15_12_AXR0_12 << \
                                       SYSCFG_PINMUX1_PINMUX1_15_12_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
void McASPPinMuxSetup(void)
{
    unsigned int savePinMux = 0;

    savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) & \
                       ~(SYSCFG_PINMUX0_PINMUX0_27_24 | \
                         SYSCFG_PINMUX0_PINMUX0_23_20 | \
                         SYSCFG_PINMUX0_PINMUX0_19_16 | \
                         SYSCFG_PINMUX0_PINMUX0_15_12 | \
                         SYSCFG_PINMUX0_PINMUX0_11_8 | \
                         SYSCFG_PINMUX0_PINMUX0_7_4 | \
                         SYSCFG_PINMUX0_PINMUX0_3_0);

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) = \
         (PINMUX0_MCASP0_AMUTE_ENABLE | PINMUX0_MCASP0_AHCLKX_ENABLE | \
          PINMUX0_MCASP0_AHCLKR_ENABLE | PINMUX0_MCASP0_AFSX_ENABLE | \
          PINMUX0_MCASP0_AFSR_ENABLE | PINMUX0_MCASP0_ACLKX_ENABLE | \
          PINMUX0_MCASP0_ACLKR_ENABLE | savePinMux);

    savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) & \
                       ~(SYSCFG_PINMUX1_PINMUX1_19_16 | \
                         SYSCFG_PINMUX1_PINMUX1_15_12);

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) = \
         (PINMUX1_MCASP0_AXR11_ENABLE | \
          PINMUX1_MCASP0_AXR12_ENABLE | \
          savePinMux);
}
