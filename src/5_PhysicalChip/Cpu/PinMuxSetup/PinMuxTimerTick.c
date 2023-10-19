/****************************************************************************/
/*                                                                          */
/*              创龙 DSP6748 开发板相关函数                                 */
/*                                                                          */
/*              2014年07月12日                                              */
/*                                                                          */
/****************************************************************************/
#include <stdint.h>
#include "interrupt.h"

#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"

#include "timer.h"
#include "PinMuxSetup.h"
#include "systick.h"

/****************************************************************************/
/*                                                                          */
/*              全局变量                                                    */
/*                                                                          */
/****************************************************************************/
static volatile unsigned int flagIsrCnt = 1;

/****************************************************************************/
/*                                                                          */
/*              宏定义                                                      */
/*                                                                          */
/****************************************************************************/
#define TMR_PERIOD_LSB32              0x5DC0
#define TMR_PERIOD_MSB32              0x0

/****************************************************************************/
/*                                                                          */
/*              函数声明                                                    */
/*                                                                          */
/****************************************************************************/
void (*pfnCallbackHandler)(void);

/****************************************************************************/
/*                                                                          */
/*              定时器中断服务函数                                          */
/*                                                                          */
/****************************************************************************/
static void TimerTickIsr(void)
{
    TimerIntDisable(SOC_TMR_0_REGS, TMR_INT_TMR34_NON_CAPT_MODE);

    IntEventClear(SYS_INT_T64P0_TINT34);
    TimerIntStatusClear(SOC_TMR_0_REGS, TMR_INT_TMR34_NON_CAPT_MODE);
  
     pfnCallbackHandler(); 
  
    TimerIntEnable(SOC_TMR_0_REGS, TMR_INT_TMR34_NON_CAPT_MODE);
}

/****************************************************************************/
/*                                                                          */
/*              定时器中断初始化                                            */
/*                                                                          */
/****************************************************************************/
void TimerTickConfigure(void (*pfnHandler)(void))
{    
    pfnCallbackHandler = pfnHandler;

    TimerConfigure(SOC_TMR_0_REGS, TMR_CFG_32BIT_UNCH_CLK_BOTH_INT);

    IntRegister(C674X_MASK_INT11, TimerTickIsr);
    IntEventMap(C674X_MASK_INT11, SYS_INT_T64P0_TINT34);
    IntEnable(C674X_MASK_INT11);

    TimerIntEnable(SOC_TMR_0_REGS, TMR_INT_TMR34_NON_CAPT_MODE);
}

/****************************************************************************/
/*                                                                          */
/*              定时器初始化                                                */
/*                                                                          */
/****************************************************************************/
void TimerTickPeriodSet(unsigned int milliSec)
{
	TimerPeriodSet(SOC_TMR_0_REGS, TMR_TIMER34, (milliSec * TMR_PERIOD_LSB32));
	TimerReloadSet(SOC_TMR_0_REGS, TMR_TIMER34, (milliSec * TMR_PERIOD_LSB32));
}

/****************************************************************************/
/*                                                                          */
/*              定时器启动                                                  */
/*                                                                          */
/****************************************************************************/
void TimerTickEnable(void)
{	
	TimerEnable(SOC_TMR_0_REGS, TMR_TIMER34, TMR_ENABLE_CONTRELOAD);
}

/****************************************************************************/
/*                                                                          */
/*              定时器停止                                                  */
/*                                                                          */
/****************************************************************************/
void TimerTickDisable(void)
{
	TimerDisable(SOC_TMR_0_REGS, TMR_TIMER34); 
}
