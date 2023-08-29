/*
 * uPPstido.c
 *
 *  Created on: 2023��8��28��
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

    // ȡ�� DMA �ж�״̬
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

        // uPP �жϽ�����¼����Ϊͬһ�ж�Դ
        // �ж��Ƿ�ȫ�����鱻�������
        intr_dmai_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);
        intr_dmaq_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHQ);
    }

    // ֪ͨ CPU uPP �жϴ�������Ա�����¼����Բ���
    uPPEndOfInt(SOC_UPP_0_REGS);
}
