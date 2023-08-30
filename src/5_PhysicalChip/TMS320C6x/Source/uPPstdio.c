/*
 * uPPstido.c
 *
 *  Created on: 2023��8��28��
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

    // ȡ�� DMA �ж�״̬
    intr_dmai_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);
    intr_dmaq_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHQ);

    while(intr_dmai_status != 0 || intr_dmaq_status != 0)
    {
        if (intr_dmai_status & uPP_INT_EOL)
        {//��ʾI��·����
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOL);
            uPPOBJ.uPPRx.RxInterruptEOL = TRUE;
        }
        if (intr_dmai_status & uPP_INT_EOW)
        {//��ʾI���ڽ���
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOW);
            uPPOBJ.uPPRx.RxInterruptEOWCnt++;
        }
        if (intr_dmai_status & uPP_INT_ERR)
        {//��ʾ����Iͨ������
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_ERR);
            uPPOBJ.uPPRx.RxInterruptERRCnt++;
        }
        if (intr_dmai_status & uPP_INT_UOR)
        {//��ʾ����IǷ�ػ����
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_UOR);
            uPPOBJ.uPPRx.RxInterruptUOR = TRUE;
        }
        if (intr_dmai_status & uPP_INT_DPE)
        {//��ʾI��̴���
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_DPE);
            uPPOBJ.uPPRx.RxInterruptDPE = TRUE;
        }

        if (intr_dmaq_status & uPP_INT_EOL)
        {//��ʾQ��·����
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_EOL);
            uPPOBJ.uPPTx.TxInterruptEOL = TRUE;
        }
        if (intr_dmaq_status & uPP_INT_EOW)
        {//��ʾQ���ڽ���
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_EOW);
            uPPOBJ.uPPTx.TxInterruptEOWCnt++;
        }
        if (intr_dmaq_status & uPP_INT_ERR)
        {//��ʾ����Qͨ������
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_ERR);
            uPPOBJ.uPPTx.TxInterruptERRCnt++;
        }
        if (intr_dmaq_status & uPP_INT_UOR)
        {//��ʾ����QǷ�ػ����
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_UOR);
            uPPOBJ.uPPTx.TxInterruptUOR = TRUE;
        }
        if (intr_dmaq_status & uPP_INT_DPE)
        {//��ʾI��̴���
            uPPIntClear(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_DPE);
            uPPOBJ.uPPTx.TxInterruptDPE = TRUE;
        }

        // uPP �жϽ�����¼����Ϊͬһ�ж�Դ
        // �ж��Ƿ�ȫ�����鱻�������
        intr_dmai_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);
        intr_dmaq_status = uPPIntStatus(SOC_UPP_0_REGS, uPP_DMA_CHQ);
    }

    // ֪ͨ CPU uPP �жϴ�������Ա�����¼����Բ���
    uPPEndOfInt(SOC_UPP_0_REGS);
}
