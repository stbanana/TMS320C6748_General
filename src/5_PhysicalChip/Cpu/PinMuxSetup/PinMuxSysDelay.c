/****************************************************************************/
/*                                                                          */
/*              ���� DSP6748 ��������غ���                                 */
/*                                                                          */
/*              2014��07��12��                                              */
/*                                                                          */
/****************************************************************************/
#include "hw_types.h"

#include "interrupt.h"

#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"

#include "timer.h"
#include "PinMuxSetup.h"
#include "delay.h"

/****************************************************************************/
/*                                                                          */
/*              ȫ�ֱ���                                                    */
/*                                                                          */
/****************************************************************************/
static volatile unsigned int flagIsrCnt = 1;

/****************************************************************************/
/*                                                                          */
/*              �궨��                                                      */
/*                                                                          */
/****************************************************************************/
#define TMR_PERIOD_LSB32              0x5DC0
#define TMR_PERIOD_MSB32              0x0

/****************************************************************************/
/*                                                                          */
/*              ��ʱ���жϷ�����                                          */
/*                                                                          */
/****************************************************************************/
static void TimerIsr(void)
{
    TimerIntDisable(SOC_TMR_0_REGS, TMR_INT_TMR12_NON_CAPT_MODE);

    IntEventClear(SYS_INT_T64P0_TINT12);
    TimerIntStatusClear(SOC_TMR_0_REGS, TMR_INT_TMR12_NON_CAPT_MODE);

    flagIsrCnt = 0;

    TimerIntEnable(SOC_TMR_0_REGS, TMR_INT_TMR12_NON_CAPT_MODE);
}

/****************************************************************************/
/*                                                                          */
/*              ��ʱ���жϳ�ʼ��                                            */
/*                                                                          */
/****************************************************************************/
static void AintcTimerIntrSetUp(void)
{
    IntRegister(C674X_MASK_INT10, TimerIsr);
  
    IntEventMap(C674X_MASK_INT10, SYS_INT_T64P0_TINT12);

    IntEnable(C674X_MASK_INT10);
}

/****************************************************************************/
/*                                                                          */
/*              ��ʱ����ʼ��                                                */
/*                                                                          */
/****************************************************************************/
void SysDelayTimerSetup(void)
{    
    TimerConfigure(SOC_TMR_0_REGS, TMR_CFG_32BIT_UNCH_CLK_BOTH_INT);

    AintcTimerIntrSetUp();

    TimerIntEnable(SOC_TMR_0_REGS, TMR_INT_TMR12_NON_CAPT_MODE);    
}


void Sysdelay(unsigned int milliSec)
{

    TimerCounterSet(SOC_TMR_0_REGS, TMR_TIMER12, 0);
	TimerPeriodSet(SOC_TMR_0_REGS, TMR_TIMER12, (milliSec * TMR_PERIOD_LSB32));
	
	TimerEnable(SOC_TMR_0_REGS, TMR_TIMER12, TMR_ENABLE_ONCE);

	while(flagIsrCnt);
	
	flagIsrCnt = 1;

	TimerDisable(SOC_TMR_0_REGS, TMR_TIMER12); 
}

/****************************************************************************/
/*                                                                          */
/*              ��ʱ������                                                  */
/*                                                                          */
/****************************************************************************/
void SysStartTimer(unsigned int milliSec)
{
    TimerCounterSet (SOC_TMR_0_REGS, TMR_TIMER12, 0);
    TimerPeriodSet(SOC_TMR_0_REGS, TMR_TIMER12, (milliSec * TMR_PERIOD_LSB32));

    TimerEnable(SOC_TMR_0_REGS, TMR_TIMER12, TMR_ENABLE_ONCE);
}

/****************************************************************************/
/*                                                                          */
/*              ��ʱ��ֹͣ                                                  */
/*                                                                          */
/****************************************************************************/
void SysStopTimer(void)
{
    flagIsrCnt = 1;

    TimerDisable(SOC_TMR_0_REGS, TMR_TIMER12);
}

/****************************************************************************/
/*                                                                          */
/*              ��ʱ����ʱ�ж�                                              */
/*                                                                          */
/****************************************************************************/
unsigned int SysIsTimerElapsed(void)
{
    if (flagIsrCnt)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
