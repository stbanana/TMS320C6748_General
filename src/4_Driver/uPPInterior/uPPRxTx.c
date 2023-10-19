/********************************************************************************

 **** Copyright (C), 2020, Shenzhen SKONDA ELECTRONIC LTD  ****

 ********************************************************************************
 * File Name     : uPPRxTx.c
 * Author        : Sven
 * Date          : 2022-11-07
 * Version       : 1.0
********************************************************************************/

#define __UPP_RX_TX_C__

/* Includes ------------------------------------------------------------------*/
#include "Includes.h"

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uPPRxTxHandleDef uPPOBJ;//内部uPP队列

// 接收 / 发送缓存变量
#pragma DATA_ALIGN(upp_buffer_a, 8)
#pragma DATA_ALIGN(upp_buffer_b, 8)
unsigned short upp_buffer_a[UPP_FRAME_SIZE];
unsigned short upp_buffer_b[UPP_FRAME_SIZE];

/* Private Constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/ 

void uPPRxTx_Reset()
{

}


void uPPRxTx_Init()
{
    uPPOBJ.uPPRx.transposeParRx.WindowAddress     = (uint32_t *)(upp_buffer_a);
    uPPOBJ.uPPRx.transposeParRx.LineCount         = UPP_LINE_COUNT;
    uPPOBJ.uPPRx.transposeParRx.ByteCount         = (UPP_LINE_SIZE*sizeof(uint16_t));
    uPPOBJ.uPPRx.transposeParRx.LineOffsetAddress = (UPP_LINE_OFFSET*sizeof(uint16_t));
    uPPOBJ.uPPRx.RxBufferPtr = upp_buffer_a;

    uPPOBJ.uPPTx.transposeParTx.WindowAddress     = (uint32_t *)(upp_buffer_b);
    uPPOBJ.uPPTx.transposeParTx.LineCount         = UPP_LINE_COUNT;
    uPPOBJ.uPPTx.transposeParTx.ByteCount         = (UPP_LINE_SIZE*sizeof(uint16_t));
    uPPOBJ.uPPTx.transposeParTx.LineOffsetAddress = (UPP_LINE_OFFSET*sizeof(uint16_t));
    uPPOBJ.uPPTx.TxBufferPtr = upp_buffer_b;
}



void uPPRxTx_Read()
{
    static uPPDMAStatus* uPPILineStatu;
    uPPILineStatu = uPPGetDMAStatus(SOC_UPP_0_REGS, uPP_DMA_CHI);
    if(uPPOBJ.uPPRx.RxInterruptEOWCnt > 0)
    {//有接收则进行回读
        CacheWBInv((unsigned int)uPPOBJ.uPPRx.RxBufferPtr, sizeof(upp_buffer_a));
        uPPOBJ.uPPRx.RxInterruptEOWCnt = 0;
    }
    if(uPPILineStatu->PEND == 0)
    {//线路空闲则启动接收
        uPPDMATransfer(SOC_UPP_0_REGS, uPP_DMA_CHI, &uPPOBJ.uPPRx.transposeParRx);
    }
}

void uPPRxTx_Schedule()
{

}

//uPP并不需要向FPGA发送大量数据，此逻辑未来可能删除
void uPPRxTx_Write()
{
    static uPPDMAStatus* uPPQLineStatu;
    uPPQLineStatu = uPPGetDMAStatus(SOC_UPP_0_REGS, uPP_DMA_CHQ);
    if(uPPOBJ.uPPTx.TxInterruptEOWCnt > 0)
    {//有发送则进行清除
        CacheInv((unsigned int)uPPOBJ.uPPTx.TxBufferPtr, sizeof(upp_buffer_a));
    }
    if(uPPQLineStatu->PEND == 0)
    {//线路空闲则启动发送
        uPPDMATransfer(SOC_UPP_0_REGS, uPP_DMA_CHQ, &uPPOBJ.uPPTx.transposeParTx);
    }
}

//每毫秒进行uPP任务流程
void uPPRxTx(void)
{

    uPPRxTx_Reset();

    uPPRxTx_Schedule();

    uPPRxTx_Read();

//    uPPRxTx_Write();

}
