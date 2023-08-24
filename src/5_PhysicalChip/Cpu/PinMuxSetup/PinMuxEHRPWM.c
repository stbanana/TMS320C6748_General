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
// EPWM0A
#define PINMUX3_EPWM0A_ENABLE    (SYSCFG_PINMUX3_PINMUX3_3_0_EPWM0A << \
					SYSCFG_PINMUX3_PINMUX3_3_0_SHIFT)

// EPWM0B
#define PINMUX3_EPWM0B_ENABLE	 (SYSCFG_PINMUX3_PINMUX3_7_4_EPWM0B << \
					SYSCFG_PINMUX3_PINMUX3_7_4_SHIFT)

// EPWM0TZ0
#define PINMUX1_EPWM0TZ0_ENABLE	(SYSCFG_PINMUX1_PINMUX1_3_0_EPWM0TZ0 << \
					SYSCFG_PINMUX1_PINMUX1_3_0_SHIFT)

// EPWM1A
#define PINMUX5_EPWM1A_ENABLE	(SYSCFG_PINMUX5_PINMUX5_3_0_EPWM1A << \
					SYSCFG_PINMUX5_PINMUX5_3_0_SHIFT)

// EPWM1B
#define PINMUX5_EPWM1B_ENABLE	(SYSCFG_PINMUX5_PINMUX5_7_4_EPWM1B << \
					SYSCFG_PINMUX5_PINMUX5_7_4_SHIFT)

// EPWM1TZ0
#define PINMUX2_EPWM1TZ0_ENABLE	(SYSCFG_PINMUX2_PINMUX2_3_0_EPWM1TZ0 << \
					SYSCFG_PINMUX2_PINMUX2_3_0_SHIFT)

// EPWMSYNCO
#define PINMUX3_EPWMSYNCO_ENABLE (SYSCFG_PINMUX3_PINMUX3_15_12_EPWMSYNCO << \
					SYSCFG_PINMUX3_PINMUX3_15_12_SHIFT)

// EPWMSYNCI
#define	PINMUX3_EPWMSYNCI_ENABLE (SYSCFG_PINMUX3_PINMUX3_11_8_EPWMSYNCI << \
					SYSCFG_PINMUX3_PINMUX3_11_8_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
void EHRPWM0PinMuxSetup(void)
{

    // EPWM0A
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & 
		 (~(SYSCFG_PINMUX3_PINMUX3_3_0))) | (PINMUX3_EPWM0A_ENABLE);

    // EPWM0B
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & 
		 (~(SYSCFG_PINMUX3_PINMUX3_7_4))) | (PINMUX3_EPWM0B_ENABLE);
    
    // EPWM0TZ[0]
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) & (~(SYSCFG_PINMUX1_PINMUX1_3_0))) |
	    	(PINMUX1_EPWM0TZ0_ENABLE);

 
    // EPWMSYNCO
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & (~(SYSCFG_PINMUX3_PINMUX3_15_12))) |
	    	(PINMUX3_EPWMSYNCO_ENABLE);

    // EPWMSYNCI
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & (~(SYSCFG_PINMUX3_PINMUX3_11_8))) |
	    	(PINMUX3_EPWMSYNCI_ENABLE);

    // 使能 PWM 时钟
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_CFGCHIP1) |= SYSCFG_CFGCHIP1_TBCLKSYNC;
}

void EHRPWM1PinMuxSetup(void)
{

    // EPWM1A
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & (~(SYSCFG_PINMUX5_PINMUX5_3_0))) |
	    	(PINMUX5_EPWM1A_ENABLE);

    // EPWM1B
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & (~(SYSCFG_PINMUX5_PINMUX5_7_4))) |
	    	(PINMUX5_EPWM1B_ENABLE);

    // EPWM1TZ[0]
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) & (~(SYSCFG_PINMUX2_PINMUX2_3_0))) |
	    	(PINMUX2_EPWM1TZ0_ENABLE);


    // EPWMSYNCO
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & (~(SYSCFG_PINMUX3_PINMUX3_15_12))) |
	    	(PINMUX3_EPWMSYNCO_ENABLE);

    // EPWMSYNCI
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) =  
	    	(HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & (~(SYSCFG_PINMUX3_PINMUX3_11_8))) |
	    	(PINMUX3_EPWMSYNCI_ENABLE);

    // 使能 PWM 时钟
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_CFGCHIP1) |= SYSCFG_CFGCHIP1_TBCLKSYNC;
}
