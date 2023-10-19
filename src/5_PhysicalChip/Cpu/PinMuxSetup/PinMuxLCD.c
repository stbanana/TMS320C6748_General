/****************************************************************************/
/*                                                                          */
/*              ���� DSP6748 ��������غ���                                 */
/*                                                                          */
/*              2014��07��12��                                              */
/*                                                                          */
/****************************************************************************/
#include <stdint.h>
#include "hw_types.h"

#include "psc.h"
#include "gpio.h"

#include "PinMuxSetup.h"
#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"

/****************************************************************************/
/*                                                                          */
/*              �궨��                                                      */
/*                                                                          */
/****************************************************************************/
#define PINMUX16_LCD_ENABLE     (SYSCFG_PINMUX16_PINMUX16_31_28_LCD_D2 << \
                                 SYSCFG_PINMUX16_PINMUX16_31_28_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_27_24_LCD_D3 << \
                                 SYSCFG_PINMUX16_PINMUX16_27_24_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_23_20_LCD_D4 << \
                                 SYSCFG_PINMUX16_PINMUX16_23_20_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_19_16_LCD_D5 << \
                                 SYSCFG_PINMUX16_PINMUX16_19_16_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_15_12_LCD_D6 << \
                                 SYSCFG_PINMUX16_PINMUX16_15_12_SHIFT) | \
                                (SYSCFG_PINMUX16_PINMUX16_11_8_LCD_D7 << \
                                 SYSCFG_PINMUX16_PINMUX16_11_8_SHIFT)

#define PINMUX17_LCD_ENABLE     (SYSCFG_PINMUX17_PINMUX17_31_28_LCD_D10 << \
                                 SYSCFG_PINMUX17_PINMUX17_31_28_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_27_24_LCD_D11 << \
                                 SYSCFG_PINMUX17_PINMUX17_27_24_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_23_20_LCD_D12 << \
                                 SYSCFG_PINMUX17_PINMUX17_23_20_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_19_16_LCD_D13 << \
                                 SYSCFG_PINMUX17_PINMUX17_19_16_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_15_12_LCD_D14 << \
                                 SYSCFG_PINMUX17_PINMUX17_15_12_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_11_8_LCD_D15 << \
                                 SYSCFG_PINMUX17_PINMUX17_11_8_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_7_4_LCD_D0 << \
                                 SYSCFG_PINMUX17_PINMUX17_7_4_SHIFT) | \
                                (SYSCFG_PINMUX17_PINMUX17_3_0_LCD_D1 << \
                                 SYSCFG_PINMUX17_PINMUX17_3_0_SHIFT)

#define PINMUX18_LCD_ENABLE     (SYSCFG_PINMUX18_PINMUX18_31_28_LCD_MCLK << \
                                 SYSCFG_PINMUX18_PINMUX18_31_28_SHIFT) | \
                                (SYSCFG_PINMUX18_PINMUX18_27_24_LCD_PCLK << \
                                 SYSCFG_PINMUX18_PINMUX18_27_24_SHIFT) | \
                                (SYSCFG_PINMUX18_PINMUX18_7_4_LCD_D8 << \
                                 SYSCFG_PINMUX18_PINMUX18_7_4_SHIFT) | \
                                (SYSCFG_PINMUX18_PINMUX18_3_0_LCD_D9 << \
                                 SYSCFG_PINMUX18_PINMUX18_3_0_SHIFT)
 
#define PINMUX19_LCD_ENABLE     (SYSCFG_PINMUX19_PINMUX19_27_24_NLCD_AC_ENB_CS << \
                                 SYSCFG_PINMUX19_PINMUX19_27_24_SHIFT) | \
                                (SYSCFG_PINMUX19_PINMUX19_7_4_LCD_VSYNC << \
                                 SYSCFG_PINMUX19_PINMUX19_7_4_SHIFT) | \
                                (SYSCFG_PINMUX19_PINMUX19_3_0_LCD_HSYNC << \
                                 SYSCFG_PINMUX19_PINMUX19_3_0_SHIFT)

#define PINMUX1_GPIO0_7_ENABLE     (SYSCFG_PINMUX1_PINMUX1_3_0_GPIO0_7    << \
                                    SYSCFG_PINMUX1_PINMUX1_3_0_SHIFT)

#define PINMUX13_GPIO6_15_ENABLE   (SYSCFG_PINMUX13_PINMUX13_3_0_GPIO6_15 << \
                                    SYSCFG_PINMUX13_PINMUX13_3_0_SHIFT)

   
/****************************************************************************/
/*                                                                          */
/*              �ܽŸ�������                                                */
/*                                                                          */
/****************************************************************************/
void LCDPinMuxSetup(void)
{
     unsigned int savePinMux = 0;

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) & \
                        ~(SYSCFG_PINMUX16_PINMUX16_31_28 | \
                          SYSCFG_PINMUX16_PINMUX16_27_24 | \
                          SYSCFG_PINMUX16_PINMUX16_23_20 | \
                          SYSCFG_PINMUX16_PINMUX16_19_16 | \
                          SYSCFG_PINMUX16_PINMUX16_15_12 | \
                          SYSCFG_PINMUX16_PINMUX16_11_8);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) = \
          (PINMUX16_LCD_ENABLE | savePinMux);

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) & \
                        ~(SYSCFG_PINMUX17_PINMUX17_31_28 | \
                          SYSCFG_PINMUX17_PINMUX17_27_24 | \
                          SYSCFG_PINMUX17_PINMUX17_23_20 | \
                          SYSCFG_PINMUX17_PINMUX17_19_16 | \
                          SYSCFG_PINMUX17_PINMUX17_15_12 | \
                          SYSCFG_PINMUX17_PINMUX17_11_8 | \
                          SYSCFG_PINMUX17_PINMUX17_7_4 | \
                          SYSCFG_PINMUX17_PINMUX17_3_0);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) = \
          (PINMUX17_LCD_ENABLE | savePinMux);

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & \
                       ~(SYSCFG_PINMUX18_PINMUX18_31_28 | \
                         SYSCFG_PINMUX18_PINMUX18_27_24 | \
                         SYSCFG_PINMUX18_PINMUX18_7_4 |  \
                         SYSCFG_PINMUX18_PINMUX18_3_0);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) = \
           (PINMUX18_LCD_ENABLE | savePinMux);

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) & \
                       ~(SYSCFG_PINMUX19_PINMUX19_27_24 | \
                         SYSCFG_PINMUX19_PINMUX19_7_4 | \
                         SYSCFG_PINMUX19_PINMUX19_3_0);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) = \
          (PINMUX19_LCD_ENABLE | savePinMux);
}

/****************************************************************************/
/*                                                                          */
/*              ��ʱ                                                        */
/*                                                                          */
/****************************************************************************/
static void Delay(volatile unsigned int delay)
{
    while(delay--);
}

/****************************************************************************/
/*                                                                          */
/*              �ܽŸ�������                                                */
/*                                                                          */
/****************************************************************************/
void ConfigRasterGpioPins(void)
{
    unsigned int savePinmux = 0;
    
    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) &
                     ~(SYSCFG_PINMUX1_PINMUX1_3_0));

    // �����������
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(1)) =
          (PINMUX1_GPIO0_7_ENABLE | savePinmux);

    savePinmux = (HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) &
                  ~(SYSCFG_PINMUX13_PINMUX13_3_0));

    // ��Դʹ������
    HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) =
          (PINMUX13_GPIO6_15_ENABLE | savePinmux);
}

/****************************************************************************/
/*                                                                          */
/*              LCD ʹ��                                                    */
/*                                                                          */
/****************************************************************************/
void ConfigRasterDisplayEnable(void)
{
    // ʹ�� GPIO ģ��
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_GPIO, PSC_POWERDOMAIN_ALWAYS_ON,
		     PSC_MDCTL_NEXT_ENABLE);

    ConfigRasterGpioPins();

    // ���ùܽ� 48 (GP2[15]) Ϊ�������
    GPIODirModeSet(SOC_GPIO_0_REGS, 48, GPIO_DIR_OUTPUT);

    // ���ùܽ� 139(GP18[10]) Ϊ��Դʹ��
    GPIODirModeSet(SOC_GPIO_0_REGS, 41, GPIO_DIR_OUTPUT);

    // ���ùܽ� 48 �����ؼ��½��ش����ж�
    GPIOIntTypeSet(SOC_GPIO_0_REGS, 48, GPIO_INT_TYPE_BOTHEDGE);
  
    // ���ùܽ� 41 �����ؼ��½��ش����ж�
    GPIOIntTypeSet(SOC_GPIO_0_REGS, 41, GPIO_INT_TYPE_BOTHEDGE);

    // ���ñ���
    GPIOPinWrite(SOC_GPIO_0_REGS, 48, 0);
    Delay(0xFFFFF);

    // ���õ�Դ
    GPIOPinWrite(SOC_GPIO_0_REGS, 41, 0);
    Delay(0xFFFFF);

    // ʹ�ܱ���
    GPIOPinWrite(SOC_GPIO_0_REGS, 48, 1);
    Delay(0xFFFFF);

    // ʹ�ܵ�Դ
    GPIOPinWrite(SOC_GPIO_0_REGS, 41, 1);
    Delay(0xFFFFF);
}

/****************************************************************************/
/*                                                                          */
/*              ����ʶ����                                                  */
/*                                                                          */
/****************************************************************************/
unsigned int LCDVersionGet(void)
{
    return 1;
}
