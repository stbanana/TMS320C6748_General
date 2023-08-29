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

}



void uPPRxTx_Read()
{

}

void uPPRxTx_Schedule()
{

}

void uPPRxTx_Write()
{

}

//每毫秒进行uPP任务流程
void uPPRxTx(void)
{

    uPPRxTx_Reset();

    uPPRxTx_Schedule();

    uPPRxTx_Read();

    uPPRxTx_Write();

}
