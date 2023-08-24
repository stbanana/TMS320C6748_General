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
//I2C0 pins
#define PINMUX4_I2C0_SDA_ENABLE    (SYSCFG_PINMUX4_PINMUX4_15_12_I2C0_SDA << \
                                    SYSCFG_PINMUX4_PINMUX4_15_12_SHIFT)

#define PINMUX4_I2C0_SCL_ENABLE    (SYSCFG_PINMUX4_PINMUX4_11_8_I2C0_SCL << \
                                    SYSCFG_PINMUX4_PINMUX4_11_8_SHIFT)


// I2C1
#define PINMUX4_I2C1_SDA_ENABLE    (SYSCFG_PINMUX4_PINMUX4_23_20_I2C1_SDA << \
                                    SYSCFG_PINMUX4_PINMUX4_23_20_SHIFT)

#define PINMUX4_I2C1_SCL_ENABLE    (SYSCFG_PINMUX4_PINMUX4_19_16_I2C1_SCL << \
                                    SYSCFG_PINMUX4_PINMUX4_19_16_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              管脚复用配置                                                */
/*                                                                          */
/****************************************************************************/
void I2CPinMuxSetup(unsigned int instanceNum)
{
     unsigned int savePinMux = 0;

     if(0 == instanceNum)
     {

          savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                             ~(SYSCFG_PINMUX4_PINMUX4_15_12 | \
                               SYSCFG_PINMUX4_PINMUX4_11_8);

          HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
               (PINMUX4_I2C0_SDA_ENABLE | \
                PINMUX4_I2C0_SCL_ENABLE | \
                savePinMux);

     }

     else if(1 == instanceNum)
     {
          savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) & \
                             ~(SYSCFG_PINMUX4_PINMUX4_23_20 | \
                               SYSCFG_PINMUX4_PINMUX4_19_16);

          HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(4)) = \
                (PINMUX4_I2C1_SDA_ENABLE | \
                 PINMUX4_I2C1_SCL_ENABLE | \
                 savePinMux);

     }
    
     else
     {

     }

}
