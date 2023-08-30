/********************************************************************************

 **** Copyright (C), 2020, Shenzhen SKONDA ELECTRONIC LTD  ****

 ********************************************************************************
 * File Name     : uPPRxTx.h
 * Author        : Sven
 * Date          : 2022-11-07
 * Version       : 1.0
********************************************************************************/
  
/* Define to prevent recursive inclusion -------------------------------------*/  
#ifndef  __UPP_RX_TX_H__
#define  __UPP_RX_TX_H__


/* Includes ------------------------------------------------------------------*/
#include <upp.h>
/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
#define UPP_LINE_SIZE        (512)
#define UPP_LINE_COUNT       (2*1024)
#define UPP_FRAME_SIZE       (UPP_LINE_SIZE * UPP_LINE_COUNT)
#define UPP_LINE_OFFSET      (UPP_LINE_SIZE)
/* Exported types ------------------------------------------------------------*/
typedef struct
{
    struct
    { /*I线路作为Rx*/
        uPPDMAConfig transposeParRx;                    //Rx通道参数
        uint16_t* RxBufferPtr;                          //Rx存储区指针
        uint16_t RxInterruptEOL     :1;                 //Rx线路结束触发
        uint16_t RxInterruptEOWCnt  :7;                 //Rx窗口结束触发次数
        uint16_t RxInterruptERRCnt  :6;                 //Rx通道错误触发次数
        uint16_t RxInterruptUOR     :1;                 //Rx欠载或溢出触发
        uint16_t RxInterruptDPE     :1;                 //Rx编程错误触发
    }uPPRx;

    struct
    {/*Q线路作为Tx*/
        uPPDMAConfig transposeParTx;                    //Tx通道参数
        uint16_t* TxBufferPtr;                          //Tx存储区指针
        uint16_t TxInterruptEOL     :1;                 //Tx线路结束触发
        uint16_t TxInterruptEOWCnt  :7;                 //Tx窗口结束触发次数
        uint16_t TxInterruptERRCnt  :6;                 //Tx通道错误触发次数
        uint16_t TxInterruptUOR     :1;                 //Tx欠载或溢出触发
        uint16_t TxInterruptDPE     :1;                 //Tx编程错误触发
    }uPPTx;



    uint16_t NoTxCnt;                               //无发送Cnt数
    uint16_t NoRxCnt;                               //无接收Cnt数
    uint16_t CntTxNum;                              //一个ms周期发送数
}uPPRxTxHandleDef;

/* Exported variables ---------------------------------------------------------*/
extern uPPRxTxHandleDef uPPOBJ;     //内部uPP队列


/* Exported functions ---------------------------------------------------------*/
extern void uPPRxTx_Init(void);//内部CAN队列初始化
extern void uPPRxTx(void);//内部CAN周期调用
#endif  
