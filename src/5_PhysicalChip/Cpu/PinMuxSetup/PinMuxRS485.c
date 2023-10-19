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
// RS485 Enable
#define PINMUX0_RS485_ENABLE    (SYSCFG_PINMUX0_PINMUX0_19_16_GPIO0_11 << \
                                     SYSCFG_PINMUX0_PINMUX0_19_16_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
void RS485PinMuxSetup(void)
{
    unsigned int savePinMux = 0;

    savePinMux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) & \
					 ~(SYSCFG_PINMUX0_PINMUX0_19_16 | \
					   SYSCFG_PINMUX0_PINMUX0_19_16));

	HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) = (PINMUX0_RS485_ENABLE | savePinMux);
}
