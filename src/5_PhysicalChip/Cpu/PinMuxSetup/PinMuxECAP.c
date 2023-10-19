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
// ECAP0
#define PINMUX2_ECAP0_ENABLE    (SYSCFG_PINMUX2_PINMUX2_31_28_ECAP0 << \
					              SYSCFG_PINMUX2_PINMUX2_31_28_SHIFT)

// ECAP1
#define PINMUX1_ECAP1_ENABLE	 (SYSCFG_PINMUX1_PINMUX1_31_28_ECAP1 << \
                                  SYSCFG_PINMUX1_PINMUX1_31_28_SHIFT)

// ECAP2
#define PINMUX1_ECAP2_ENABLE	 (SYSCFG_PINMUX1_PINMUX1_3_0_ECAP2   << \
                                  SYSCFG_PINMUX1_PINMUX1_3_0_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
void ECAPPinMuxSetup(uint32_t ui32PortNum)
{
    uint32_t savePinmux = 0;

    if(ui32PortNum==0)
    {
		savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) &
					 ~(SYSCFG_PINMUX2_PINMUX2_31_28));

		HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) =
			 (PINMUX2_ECAP0_ENABLE | savePinmux);
    }
    else if(ui32PortNum==1)
    {
		savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
					 ~(SYSCFG_PINMUX1_PINMUX1_31_28));

		HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
			 (PINMUX1_ECAP1_ENABLE | savePinmux);
    }
    else if(ui32PortNum==2)
    {
		savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
					 ~(SYSCFG_PINMUX1_PINMUX1_3_0));

		HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
			 (PINMUX1_ECAP2_ENABLE | savePinmux);
    }
}

