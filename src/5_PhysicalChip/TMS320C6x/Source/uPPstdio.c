/*
 * uPPstido.c
 *
 *  Created on: 2023年8月28日
 *      Author: 19218
 */


#include <stdio.h>
#include <soc_C6748.h>

#include <upp.h>
#include <dspcache.h>

volatile int upp_interrupt_count = 0;
volatile int upp_error_count = 0;

void uPPIsr(void)
{
    unsigned int intr_dmai_status, intr_dmaq_status;

    // 取得 DMA 中断状态
    intr_dmai_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);
    intr_dmaq_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHQ);

    while(intr_dmai_status != 0 || intr_dmaq_status != 0)
    {
        if (intr_dmai_status & uPP_INT_EOL)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOL);
        }

        if (intr_dmai_status & uPP_INT_EOW)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOW);
            upp_interrupt_count++;
        }

        if (intr_dmai_status & uPP_INT_ERR)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_ERR);
            upp_error_count++;
        }

        if (intr_dmai_status & uPP_INT_UOR)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_UOR);
            upp_error_count++;
        }

        if (intr_dmai_status & uPP_INT_DPE)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_DPE);
            upp_error_count++;
        }

        if (intr_dmaq_status & uPP_INT_EOL)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_EOL);
        }

        if (intr_dmaq_status & uPP_INT_EOW)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_EOW);
            upp_interrupt_count++;
        }

        if (intr_dmaq_status & uPP_INT_ERR)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_ERR);
            upp_error_count++;
        }

        if (intr_dmaq_status & uPP_INT_UOR)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_UOR);
            upp_error_count++;
        }

        if (intr_dmaq_status & uPP_INT_DPE)
        {
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_DPE);
            upp_error_count++;
        }

        // uPP 中断将多个事件组合为同一中断源
        // 判断是否全部事情被处理完毕
        intr_dmai_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);
        intr_dmaq_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHQ);
    }

    // 通知 CPU uPP 中断处理完毕以便后续事件可以产生
    uPPEndOfInt(SOC_UPP_0_REGS);
}
