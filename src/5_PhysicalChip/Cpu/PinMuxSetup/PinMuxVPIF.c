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
#define PINMUX14_VPIF_ENABLE    (SYSCFG_PINMUX14_PINMUX14_31_28_DIN2 << \
                                 SYSCFG_PINMUX14_PINMUX14_31_28_SHIFT) | \
                                (SYSCFG_PINMUX14_PINMUX14_27_24_DIN3 << \
                                 SYSCFG_PINMUX14_PINMUX14_27_24_SHIFT) | \
                                (SYSCFG_PINMUX14_PINMUX14_23_20_DIN4 << \
                                 SYSCFG_PINMUX14_PINMUX14_23_20_SHIFT) | \
                                (SYSCFG_PINMUX14_PINMUX14_19_16_DIN5 << \
                                 SYSCFG_PINMUX14_PINMUX14_19_16_SHIFT) | \
                                (SYSCFG_PINMUX14_PINMUX14_15_12_DIN6 << \
                                 SYSCFG_PINMUX14_PINMUX14_15_12_SHIFT) | \
                                (SYSCFG_PINMUX14_PINMUX14_11_8_DIN7 << \
                                 SYSCFG_PINMUX14_PINMUX14_11_8_SHIFT) | \
                                (SYSCFG_PINMUX14_PINMUX14_7_4_CLKIN1 << \
                                 SYSCFG_PINMUX14_PINMUX14_7_4_SHIFT) | \
                                (SYSCFG_PINMUX14_PINMUX14_3_0_CLKIN0 << \
                                 SYSCFG_PINMUX14_PINMUX14_3_0_SHIFT)


#define PINMUX15_VPIF_ENABLE    (SYSCFG_PINMUX15_PINMUX15_31_28_DIN10 << \
                                 SYSCFG_PINMUX15_PINMUX15_31_28_SHIFT) | \
                                (SYSCFG_PINMUX15_PINMUX15_27_24_DIN11 << \
                                 SYSCFG_PINMUX15_PINMUX15_27_24_SHIFT) | \
                                (SYSCFG_PINMUX15_PINMUX15_23_20_DIN12 << \
                                 SYSCFG_PINMUX15_PINMUX15_23_20_SHIFT) | \
                                (SYSCFG_PINMUX15_PINMUX15_19_16_DIN13_FIELD << \
                                 SYSCFG_PINMUX15_PINMUX15_19_16_SHIFT) | \
                                (SYSCFG_PINMUX15_PINMUX15_15_12_DIN14_HSYNC << \
                                 SYSCFG_PINMUX15_PINMUX15_15_12_SHIFT) | \
                                (SYSCFG_PINMUX15_PINMUX15_11_8_DIN15_VSYNC << \
                                 SYSCFG_PINMUX15_PINMUX15_11_8_SHIFT) | \
                                (SYSCFG_PINMUX15_PINMUX15_7_4_DIN0 << \
                                 SYSCFG_PINMUX15_PINMUX15_7_4_SHIFT) | \
                                (SYSCFG_PINMUX15_PINMUX15_3_0_DIN1 << \
                                 SYSCFG_PINMUX15_PINMUX15_3_0_SHIFT)



#define PINMUX16_VPIF_ENABLE    (SYSCFG_PINMUX16_PINMUX16_31_28_DOUT2 << \
                                 SYSCFG_PINMUX16_PINMUX16_31_28_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_27_24_DOUT3 << \
                                 SYSCFG_PINMUX16_PINMUX16_27_24_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_23_20_DOUT4 << \
                                 SYSCFG_PINMUX16_PINMUX16_23_20_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_19_16_DOUT5 << \
                                 SYSCFG_PINMUX16_PINMUX16_19_16_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_15_12_DOUT6 << \
                                 SYSCFG_PINMUX16_PINMUX16_15_12_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_11_8_DOUT7 << \
                                 SYSCFG_PINMUX16_PINMUX16_11_8_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_7_4_DIN8 << \
                                 SYSCFG_PINMUX16_PINMUX16_7_4_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_3_0_DIN9 << \
                                 SYSCFG_PINMUX16_PINMUX16_3_0_SHIFT)

#define PINMUX17_VPIF_ENABLE    (SYSCFG_PINMUX17_PINMUX17_31_28_DOUT10 << \
                                 SYSCFG_PINMUX17_PINMUX17_31_28_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_27_24_DOUT11 << \
                                 SYSCFG_PINMUX17_PINMUX17_27_24_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_23_20_DOUT12 << \
                                 SYSCFG_PINMUX17_PINMUX17_23_20_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_19_16_DOUT13 << \
                                 SYSCFG_PINMUX17_PINMUX17_19_16_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_15_12_DOUT14 << \
                                 SYSCFG_PINMUX17_PINMUX17_15_12_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_11_8_DOUT15 << \
                                 SYSCFG_PINMUX17_PINMUX17_11_8_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_7_4_DOUT0 << \
                                 SYSCFG_PINMUX17_PINMUX17_7_4_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_3_0_DOUT1 << \
                                 SYSCFG_PINMUX17_PINMUX17_3_0_SHIFT)

#define PINMUX18_VPIF_ENABLE    (SYSCFG_PINMUX18_PINMUX18_7_4_DOUT8 << \
                                 SYSCFG_PINMUX18_PINMUX18_7_4_SHIFT) | \
                                (SYSCFG_PINMUX18_PINMUX18_3_0_DOUT9 << \
                                 SYSCFG_PINMUX18_PINMUX18_3_0_SHIFT)
 
#define PINMUX19_VPIF_ENABLE    (SYSCFG_PINMUX19_PINMUX19_23_20_CLKO3 << \
                                 SYSCFG_PINMUX19_PINMUX19_23_20_SHIFT) | \
                                (SYSCFG_PINMUX19_PINMUX19_19_16_CLKIN3 << \
                                 SYSCFG_PINMUX19_PINMUX19_19_16_SHIFT) | \
                                (SYSCFG_PINMUX19_PINMUX19_15_12_CLKO2 << \
                                 SYSCFG_PINMUX19_PINMUX19_15_12_SHIFT) | \
                                (SYSCFG_PINMUX19_PINMUX19_11_8_CLKIN2 << \
                                 SYSCFG_PINMUX19_PINMUX19_11_8_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              �ܽŸ�������                                                */
/*                                                                          */
/****************************************************************************/
void VPIFPinMuxSetup(void)
{
     unsigned int savePinMux = 0;

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) & \
                        ~(SYSCFG_PINMUX14_PINMUX14_31_28 | \
                          SYSCFG_PINMUX14_PINMUX14_27_24 | \
                          SYSCFG_PINMUX14_PINMUX14_23_20 | \
                          SYSCFG_PINMUX14_PINMUX14_19_16 | \
                          SYSCFG_PINMUX14_PINMUX14_15_12 | \
                          SYSCFG_PINMUX14_PINMUX14_11_8 | \
                          SYSCFG_PINMUX14_PINMUX14_7_4 | \
                          SYSCFG_PINMUX14_PINMUX14_3_0);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) = \
          (PINMUX14_VPIF_ENABLE | savePinMux);

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) & \
                        ~(SYSCFG_PINMUX15_PINMUX15_31_28 | \
                          SYSCFG_PINMUX15_PINMUX15_27_24 | \
                          SYSCFG_PINMUX15_PINMUX15_23_20 | \
                          SYSCFG_PINMUX15_PINMUX15_19_16 | \
                          SYSCFG_PINMUX15_PINMUX15_15_12 | \
                          SYSCFG_PINMUX15_PINMUX15_11_8 | \
                          SYSCFG_PINMUX15_PINMUX15_7_4 | \
                          SYSCFG_PINMUX15_PINMUX15_3_0);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) = \
          (PINMUX15_VPIF_ENABLE | savePinMux);

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) & \
                       ~(SYSCFG_PINMUX19_PINMUX19_23_20 | \
                         SYSCFG_PINMUX19_PINMUX19_19_16 | \
                         SYSCFG_PINMUX19_PINMUX19_15_12 | \
                         SYSCFG_PINMUX19_PINMUX19_11_8  | \
                         SYSCFG_PINMUX19_PINMUX19_7_4   | \
                         SYSCFG_PINMUX19_PINMUX19_3_0);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) = \
          (PINMUX19_VPIF_ENABLE | savePinMux);
}
