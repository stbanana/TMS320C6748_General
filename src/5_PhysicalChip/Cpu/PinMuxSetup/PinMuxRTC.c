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
// RTC_ALARM
#define PINMUX0_RTC_ALARM_ENABLE   (SYSCFG_PINMUX0_PINMUX0_31_28_ALARM << \
                                    SYSCFG_PINMUX0_PINMUX0_31_28_SHIFT)

// RTCK
#define PINMUX19_RTCK_ENABLE       (SYSCFG_PINMUX19_PINMUX19_31_28_RTCK << \
                                    SYSCFG_PINMUX19_PINMUX19_31_28_SHIFT)

/****************************************************************************/
/*                                                                          */
/*              �ܽŸ�������                                                */
/*                                                                          */
/****************************************************************************/
void RTCPinMuxSetup(unsigned int alarmPinReqd)
{
     unsigned int savePinMux = 0;

     if(TRUE == alarmPinReqd)
     {
          savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) & \
                              ~(SYSCFG_PINMUX0_PINMUX0_31_28);
    
          HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(0)) = \
               (PINMUX0_RTC_ALARM_ENABLE | savePinMux);
     }

     savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) & \
                          ~(SYSCFG_PINMUX19_PINMUX19_31_28);

     HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(19)) = (PINMUX19_RTCK_ENABLE | \
                                                      savePinMux);
}

/****************************************************************************/
/*                                                                          */
/*              ����ʶ����                                                  */
/*                                                                          */
/****************************************************************************/
unsigned int RtcVersionGet(void)
{
    return 1;
}
