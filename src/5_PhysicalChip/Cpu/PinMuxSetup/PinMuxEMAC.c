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
#include "hw_emac.h"

/****************************************************************************/
/*                                                                          */
/*              �궨��                                                      */
/*                                                                          */
/****************************************************************************/
#define PINMUX4_MDIO_ENABLE      (SYSCFG_PINMUX4_PINMUX4_7_4_MDIO_D << \
                                  SYSCFG_PINMUX4_PINMUX4_7_4_SHIFT) | \
                                 (SYSCFG_PINMUX4_PINMUX4_3_0_MDIO_CLK << \
                                  SYSCFG_PINMUX4_PINMUX4_3_0_SHIFT)

#define PINMUX2_EMAC_ENABLE      (SYSCFG_PINMUX2_PINMUX2_31_28_MII_TXD0 << \
                                  SYSCFG_PINMUX2_PINMUX2_31_28_SHIFT) | \
                                 (SYSCFG_PINMUX2_PINMUX2_27_24_MII_TXD1 << \
                                  SYSCFG_PINMUX2_PINMUX2_27_24_SHIFT) | \
                                 (SYSCFG_PINMUX2_PINMUX2_23_20_MII_TXD2 << \
                                  SYSCFG_PINMUX2_PINMUX2_23_20_SHIFT) | \
                                 (SYSCFG_PINMUX2_PINMUX2_19_16_MII_TXD3 << \
                                  SYSCFG_PINMUX2_PINMUX2_19_16_SHIFT) | \
                                 (SYSCFG_PINMUX2_PINMUX2_15_12_MII_COL << \
                                  SYSCFG_PINMUX2_PINMUX2_15_12_SHIFT) | \
                                 (SYSCFG_PINMUX2_PINMUX2_11_8_MII_TXCLK << \
                                  SYSCFG_PINMUX2_PINMUX2_11_8_SHIFT) | \
                                 (SYSCFG_PINMUX2_PINMUX2_7_4_MII_TXEN << \
                                  SYSCFG_PINMUX2_PINMUX2_7_4_SHIFT)


#define PINMUX3_EMAC_ENABLE      (SYSCFG_PINMUX3_PINMUX3_31_28_MII_RXD0 << \
                                  SYSCFG_PINMUX3_PINMUX3_31_28_SHIFT) | \
                                 (SYSCFG_PINMUX3_PINMUX3_27_24_MII_RXD1 << \
                                  SYSCFG_PINMUX3_PINMUX3_27_24_SHIFT) | \
                                 (SYSCFG_PINMUX3_PINMUX3_23_20_MII_RXD2 << \
                                  SYSCFG_PINMUX3_PINMUX3_23_20_SHIFT) | \
                                 (SYSCFG_PINMUX3_PINMUX3_19_16_MII_RXD3 << \
                                  SYSCFG_PINMUX3_PINMUX3_19_16_SHIFT) | \
                                 (SYSCFG_PINMUX3_PINMUX3_15_12_MII_CRS << \
                                  SYSCFG_PINMUX3_PINMUX3_15_12_SHIFT) | \
                                 (SYSCFG_PINMUX3_PINMUX3_11_8_MII_RXER << \
                                  SYSCFG_PINMUX3_PINMUX3_11_8_SHIFT) | \
                                 (SYSCFG_PINMUX3_PINMUX3_7_4_MII_RXDV << \
                                  SYSCFG_PINMUX3_PINMUX3_7_4_SHIFT) | \
                                 (SYSCFG_PINMUX3_PINMUX3_3_0_MII_RXCLK << \
                                  SYSCFG_PINMUX3_PINMUX3_3_0_SHIFT)

#define PINMUX14_EMAC_ENABLE    (SYSCFG_PINMUX14_PINMUX14_31_28_RMII_RXER << \
                                  SYSCFG_PINMUX14_PINMUX14_31_28_SHIFT) | \
                                 (SYSCFG_PINMUX14_PINMUX14_27_24_RMII_RXD0 << \
                                  SYSCFG_PINMUX14_PINMUX14_27_24_SHIFT) | \
                                 (SYSCFG_PINMUX14_PINMUX14_23_20_RMII_RXD1 << \
                                  SYSCFG_PINMUX14_PINMUX14_23_20_SHIFT) | \
                                 (SYSCFG_PINMUX14_PINMUX14_19_16_RMII_TXEN << \
                                  SYSCFG_PINMUX14_PINMUX14_19_16_SHIFT) | \
                                 (SYSCFG_PINMUX14_PINMUX14_15_12_RMII_TXD0 << \
                                  SYSCFG_PINMUX14_PINMUX14_15_12_SHIFT) | \
                                 (SYSCFG_PINMUX14_PINMUX14_11_8_RMII_TXD1 << \
                                  SYSCFG_PINMUX14_PINMUX14_11_8_SHIFT)

#define PINMUX15_EMAC_ENABLE    (SYSCFG_PINMUX15_PINMUX15_7_4_RMII_CRS_DV << \
                                  SYSCFG_PINMUX15_PINMUX15_7_4_SHIFT) | \
                                 (SYSCFG_PINMUX15_PINMUX15_3_0_DEFAULT << \
                                  SYSCFG_PINMUX15_PINMUX15_3_0_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              �ܽŸ�������                                                */
/*                                                                          */
/****************************************************************************/
void EMACPinMuxSetup(void)
{
    unsigned int savePinMux = 0;

    savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                       ~(SYSCFG_PINMUX4_PINMUX4_3_0 | \
                         SYSCFG_PINMUX4_PINMUX4_7_4);

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
         (PINMUX4_MDIO_ENABLE | savePinMux);

    savePinMux =  HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) & \
                        ~(SYSCFG_PINMUX2_PINMUX2_31_28 | \
                          SYSCFG_PINMUX2_PINMUX2_27_24 | \
                          SYSCFG_PINMUX2_PINMUX2_23_20 | \
                          SYSCFG_PINMUX2_PINMUX2_19_16 | \
                          SYSCFG_PINMUX2_PINMUX2_15_12 | \
                          SYSCFG_PINMUX2_PINMUX2_11_8 | \
                          SYSCFG_PINMUX2_PINMUX2_7_4);

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(2)) = \
         (PINMUX2_EMAC_ENABLE | savePinMux);

    savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                       ~(SYSCFG_PINMUX3_PINMUX3_31_28 | \
                         SYSCFG_PINMUX3_PINMUX3_27_24 | \
                         SYSCFG_PINMUX3_PINMUX3_23_20 | \
                         SYSCFG_PINMUX3_PINMUX3_19_16 | \
                         SYSCFG_PINMUX3_PINMUX3_15_12 | \
                         SYSCFG_PINMUX3_PINMUX3_11_8 | \
                         SYSCFG_PINMUX3_PINMUX3_7_4 | \
                         SYSCFG_PINMUX3_PINMUX3_3_0);

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
         (PINMUX3_EMAC_ENABLE | savePinMux);

    // ʹ�� MII ģʽ
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_CFGCHIP3) &= ~(SYSCFG_CFGCHIP3_RMII_SEL);
}

void EMACPinMuxRMIISetup(void)
{
    unsigned int savePinMux = 0;

    savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                       ~(SYSCFG_PINMUX4_PINMUX4_3_0 | \
                         SYSCFG_PINMUX4_PINMUX4_7_4);

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
         (PINMUX4_MDIO_ENABLE | savePinMux);

    savePinMux =  HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) & \
                        ~(SYSCFG_PINMUX14_PINMUX14_31_28 | \
                          SYSCFG_PINMUX14_PINMUX14_27_24 | \
                          SYSCFG_PINMUX14_PINMUX14_23_20 | \
                          SYSCFG_PINMUX14_PINMUX14_19_16 | \
                          SYSCFG_PINMUX14_PINMUX14_15_12 | \
                          SYSCFG_PINMUX14_PINMUX14_11_8);

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) = \
         (PINMUX14_EMAC_ENABLE | savePinMux);

    savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) & \
                       ~(SYSCFG_PINMUX15_PINMUX15_7_4 | \
                         SYSCFG_PINMUX15_PINMUX15_3_0);

    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) = \
         (PINMUX15_EMAC_ENABLE | savePinMux);

    // ʹ�� RMII ģʽ
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_CFGCHIP3) &= SYSCFG_CFGCHIP3_RMII_SEL;
}
