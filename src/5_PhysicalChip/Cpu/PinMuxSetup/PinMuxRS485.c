/****************************************************************************/
/*                                                                          */
/*              ���� DSP6748 ��������غ���                                 */
/*                                                                          */
/*              2014��07��12��                                              */
/*                                                                          */
/****************************************************************************/
#include <stdint.h>
#include "hw_types.h"

#include "PinMuxSetup.h"
#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"

/****************************************************************************/
/*                                                                          */
/*              �궨��                                                      */
/*                                                                          */
/****************************************************************************/
// RS485 Enable
#define PINMUX0_RS485_ENABLE    (SYSCFG_PINMUX0_PINMUX0_19_16_GPIO0_11 << \
                                     SYSCFG_PINMUX0_PINMUX0_19_16_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              �ܽŸ�������                                                */
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
