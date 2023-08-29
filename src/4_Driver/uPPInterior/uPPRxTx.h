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
    /*I��·��ΪRx*/
    uPPDMAConfig transposeParRx;                    //Rxͨ������
    uint16_t* RxBufferPtr;                          //Rx�洢��ָ��
    /*Q��·��ΪTx*/
    uPPDMAConfig transposeParTx;                    //Txͨ������
    uint16_t* TxBufferPtr;                          //Tx�洢��ָ��

    uint16_t NoTxCnt;                               //�޷���Cnt��
    uint16_t NoRxCnt;                               //�޽���Cnt��
    uint16_t CntTxNum;                              //һ��ms���ڷ�����
}uPPRxTxHandleDef;

/* Exported variables ---------------------------------------------------------*/
extern uPPRxTxHandleDef uPPOBJ;     //�ڲ�uPP����


/* Exported functions ---------------------------------------------------------*/
extern void uPPRxTx_Init(void);//�ڲ�CAN���г�ʼ��
extern void uPPRxTx(void);//�ڲ�CAN���ڵ���
#endif  
