/*
 * uPPstido.c
 *
 *  Created on: 2023年8月28日
 *      Author: 19218
 */


#include <stdint.h>
#include <hw_types.h>
#include <soc_C6748.h>

#include <upp.h>
#include <dspcache.h>

#include <uPPRxTx.h>


void uPPIsr(void)
{
    unsigned int intr_dmai_status, intr_dmaq_status;

    // 取得 DMA 中断状态
    intr_dmai_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);
    intr_dmaq_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHQ);

    while(intr_dmai_status != 0 || intr_dmaq_status != 0)
    {
        if (intr_dmai_status & uPP_INT_EOL)
        {//表示I线路结束
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOL);
            uPPOBJ.uPPRx.RxInterruptEOL = TRUE;
        }
        if (intr_dmai_status & uPP_INT_EOW)
        {//表示I窗口结束
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOW);
            uPPOBJ.uPPRx.RxInterruptEOWCnt++;
        }
        if (intr_dmai_status & uPP_INT_ERR)
        {//表示产生I通道错误
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_ERR);
            uPPOBJ.uPPRx.RxInterruptERRCnt++;
        }
        if (intr_dmai_status & uPP_INT_UOR)
        {//表示产生I欠载或溢出
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_UOR);
            uPPOBJ.uPPRx.RxInterruptUOR = TRUE;
        }
        if (intr_dmai_status & uPP_INT_DPE)
        {//表示I编程错误
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_DPE);
            uPPOBJ.uPPRx.RxInterruptDPE = TRUE;
        }

        if (intr_dmaq_status & uPP_INT_EOL)
        {//表示Q线路结束
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_EOL);
            uPPOBJ.uPPTx.TxInterruptEOL = TRUE;
        }
        if (intr_dmaq_status & uPP_INT_EOW)
        {//表示Q窗口结束
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_EOW);
            uPPOBJ.uPPTx.TxInterruptEOWCnt++;
        }
        if (intr_dmaq_status & uPP_INT_ERR)
        {//表示产生Q通道错误
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_ERR);
            uPPOBJ.uPPTx.TxInterruptERRCnt++;
        }
        if (intr_dmaq_status & uPP_INT_UOR)
        {//表示产生Q欠载或溢出
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_UOR);
            uPPOBJ.uPPTx.TxInterruptUOR = TRUE;
        }
        if (intr_dmaq_status & uPP_INT_DPE)
        {//表示I编程错误
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_DPE);
            uPPOBJ.uPPTx.TxInterruptDPE = TRUE;
        }

        // uPP 中断将多个事件组合为同一中断源
        // 判断是否全部事情被处理完毕
        intr_dmai_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);
        intr_dmaq_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHQ);
    }

    // 通知 CPU uPP 中断处理完毕以便后续事件可以产生
    uPPEndOfInt(SOC_UPP_0_REGS);
}
