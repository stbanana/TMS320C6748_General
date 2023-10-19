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
//SPI0
#define PINMUX3_SPI0_CLK_ENABLE   (SYSCFG_PINMUX3_PINMUX3_3_0_SPI0_CLK << \
                                    SYSCFG_PINMUX3_PINMUX3_3_0_SHIFT)

#define PINMUX3_SPI0_SIMO_ENABLE  (SYSCFG_PINMUX3_PINMUX3_15_12_SPI0_SIMO0 << \
                                    SYSCFG_PINMUX3_PINMUX3_15_12_SHIFT)

#define PINMUX3_SPI0_SOMI_ENABLE  (SYSCFG_PINMUX3_PINMUX3_11_8_SPI0_SOMI0 << \
                                    SYSCFG_PINMUX3_PINMUX3_11_8_SHIFT)

#define PINMUX3_SPI0_ENA_ENABLE   (SYSCFG_PINMUX3_PINMUX3_7_4_NSPI0_ENA << \
                                    SYSCFG_PINMUX3_PINMUX3_7_4_SHIFT)

// SPI1 pins
#define PINMUX5_SPI1_CLK_ENABLE   (SYSCFG_PINMUX5_PINMUX5_11_8_SPI1_CLK << \
                                   SYSCFG_PINMUX5_PINMUX5_11_8_SHIFT)

#define PINMUX5_SPI1_SIMO_ENABLE  (SYSCFG_PINMUX5_PINMUX5_23_20_SPI1_SIMO0 << \
                                   SYSCFG_PINMUX5_PINMUX5_23_20_SHIFT)

#define PINMUX5_SPI1_SOMI_ENABLE  (SYSCFG_PINMUX5_PINMUX5_19_16_SPI1_SOMI0 << \
                                   SYSCFG_PINMUX5_PINMUX5_19_16_SHIFT)

#define PINMUX5_SPI1_ENA_ENABLE   (SYSCFG_PINMUX5_PINMUX5_15_12_NSPI1_ENA << \
                                   SYSCFG_PINMUX5_PINMUX5_15_12_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              �ܽŸ�������                                                */
/*                                                                          */
/****************************************************************************/
void SPIPinMuxSetup(unsigned int instanceNum)
{
    unsigned int savePinMux = 0;    

    if(0 == instanceNum)
    {
        savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                            ~(SYSCFG_PINMUX3_PINMUX3_3_0 | \
                              SYSCFG_PINMUX3_PINMUX3_15_12 | \
                              SYSCFG_PINMUX3_PINMUX3_11_8 | \
                              SYSCFG_PINMUX3_PINMUX3_7_4);

        HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
             (PINMUX3_SPI0_CLK_ENABLE | PINMUX3_SPI0_SIMO_ENABLE | \
              PINMUX3_SPI0_SOMI_ENABLE | PINMUX3_SPI0_ENA_ENABLE | \
              savePinMux);

    }
    else if(1 == instanceNum)
    {
        savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & \
                            ~(SYSCFG_PINMUX5_PINMUX5_11_8 | \
                              SYSCFG_PINMUX5_PINMUX5_23_20 | \
                              SYSCFG_PINMUX5_PINMUX5_19_16 | \
                              SYSCFG_PINMUX5_PINMUX5_15_12);     

        HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) = \
             (PINMUX5_SPI1_CLK_ENABLE | PINMUX5_SPI1_SIMO_ENABLE | \
              PINMUX5_SPI1_SOMI_ENABLE | PINMUX5_SPI1_ENA_ENABLE | \
              savePinMux);
    }
    else
    {


    }

}

void SPI0CSPinMuxSetup(unsigned int csPinNum)
{
     unsigned int spi0CSPinMux = 0;
     unsigned int savePinMux = 0;

     switch(csPinNum)
     {
          case 0: 
              spi0CSPinMux = (SYSCFG_PINMUX4_PINMUX4_7_4_NSPI0_SCS0 << \
                              SYSCFG_PINMUX4_PINMUX4_7_4_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                 ~(SYSCFG_PINMUX4_PINMUX4_7_4);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                   (spi0CSPinMux | savePinMux); 
          break;

          case 1: 
              spi0CSPinMux = (SYSCFG_PINMUX4_PINMUX4_3_0_NSPI0_SCS1 << \
                              SYSCFG_PINMUX4_PINMUX4_3_0_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                 ~(SYSCFG_PINMUX4_PINMUX4_3_0);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                   (spi0CSPinMux | savePinMux); 

          break;    

          case 2: 
              spi0CSPinMux = (SYSCFG_PINMUX3_PINMUX3_31_28_NSPI0_SCS2 << \
                              SYSCFG_PINMUX3_PINMUX3_31_28_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                                 ~(SYSCFG_PINMUX3_PINMUX3_31_28); 

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
                   (spi0CSPinMux | savePinMux);

          break;

          case 3: 
              spi0CSPinMux = (SYSCFG_PINMUX3_PINMUX3_27_24_NSPI0_SCS3 << \
                              SYSCFG_PINMUX3_PINMUX3_27_24_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                                 ~(SYSCFG_PINMUX3_PINMUX3_27_24);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
                   (spi0CSPinMux | savePinMux);

          break;

          case 4: 
              spi0CSPinMux = (SYSCFG_PINMUX3_PINMUX3_23_20_NSPI0_SCS4 << \
                              SYSCFG_PINMUX3_PINMUX3_23_20_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                                 ~(SYSCFG_PINMUX3_PINMUX3_23_20);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
                   (spi0CSPinMux | savePinMux);

          break;

          case 5: 
              spi0CSPinMux = (SYSCFG_PINMUX3_PINMUX3_19_16_NSPI0_SCS5 << \
                              SYSCFG_PINMUX3_PINMUX3_19_16_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) & \
                                 ~(SYSCFG_PINMUX3_PINMUX3_19_16);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(3)) = \
                   (spi0CSPinMux | savePinMux);

          break;

          default:
          break;
     }

}

void SPI1CSPinMuxSetup(unsigned int csPinNum)
{
     unsigned int spi1CSPinMux = 0;
     unsigned int savePinMux = 0;

     switch(csPinNum)
     {
          case 0: 
              spi1CSPinMux = (SYSCFG_PINMUX5_PINMUX5_7_4_NSPI1_SCS0 << \
                              SYSCFG_PINMUX5_PINMUX5_7_4_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & \
                                 ~(SYSCFG_PINMUX5_PINMUX5_7_4);
              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) = \
                   (spi1CSPinMux | savePinMux);

          break;

          case 1: 
              spi1CSPinMux = (SYSCFG_PINMUX5_PINMUX5_3_0_NSPI1_SCS1 << \
                              SYSCFG_PINMUX5_PINMUX5_3_0_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) & \
                                 ~(SYSCFG_PINMUX5_PINMUX5_3_0);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(5)) = \
                   (spi1CSPinMux | savePinMux);

          break;

          case 2: 
              spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_31_28_NSPI1_SCS2 << \
                              SYSCFG_PINMUX4_PINMUX4_31_28_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) &
                                 ~(SYSCFG_PINMUX4_PINMUX4_31_28);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                   (spi1CSPinMux | savePinMux);

          break;

          case 3: 
              spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_27_24_NSPI1_SCS3 << \
                              SYSCFG_PINMUX4_PINMUX4_27_24_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                 ~(SYSCFG_PINMUX4_PINMUX4_27_24);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                   (spi1CSPinMux | savePinMux);

          break;

          case 4: 
              spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_23_20_NSPI1_SCS4 << \
                              SYSCFG_PINMUX4_PINMUX4_23_20_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                 ~(SYSCFG_PINMUX4_PINMUX4_23_20);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                   (spi1CSPinMux | savePinMux);

          break;

          case 5: 
              spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_19_16_NSPI1_SCS5 << \
                              SYSCFG_PINMUX4_PINMUX4_19_16_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                 ~(SYSCFG_PINMUX4_PINMUX4_19_16);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                   (spi1CSPinMux | savePinMux);

          break;

          case 6: 
              spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_15_12_NSPI1_SCS6 << \
                              SYSCFG_PINMUX4_PINMUX4_15_12_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                 ~(SYSCFG_PINMUX4_PINMUX4_15_12);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                   (spi1CSPinMux | savePinMux);

          break;

          case 7: 
              spi1CSPinMux = (SYSCFG_PINMUX4_PINMUX4_11_8_NSPI1_SCS7 << \
                              SYSCFG_PINMUX4_PINMUX4_11_8_SHIFT);

              savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                                 ~(SYSCFG_PINMUX4_PINMUX4_11_8);

              HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                   (spi1CSPinMux | savePinMux);

          break;

          default:
          break;

     }

}
