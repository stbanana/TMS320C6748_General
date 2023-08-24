/****************************************************************************/
/*                                                                          */
/*              ���� DSP6748 ��������غ���                                 */
/*                                                                          */
/*              2014��07��12��                                              */
/*                                                                          */
/****************************************************************************/
#include "hw_types.h"

#include "PinMuxSetup.h"
#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"

/****************************************************************************/
/*                                                                          */
/*              �궨��                                                      */
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
/*              �ܽŸ�������                                                */
/*                                                                          */
/****************************************************************************/
void ECAPPinMuxSetup(unsigned char n)
{
    unsigned int savePinmux = 0;

    if(n==0)
    {
		savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) &
					 ~(SYSCFG_PINMUX2_PINMUX2_31_28));

		HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) =
			 (PINMUX2_ECAP0_ENABLE | savePinmux);
    }
    else if(n==1)
    {
		savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
					 ~(SYSCFG_PINMUX1_PINMUX1_31_28));

		HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
			 (PINMUX1_ECAP1_ENABLE | savePinmux);
    }
    else if(n==2)
    {
		savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
					 ~(SYSCFG_PINMUX1_PINMUX1_3_0));

		HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
			 (PINMUX1_ECAP2_ENABLE | savePinmux);
    }
}

