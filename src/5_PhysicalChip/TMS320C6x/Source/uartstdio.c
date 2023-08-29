//*****************************************************************************
//
// uartstdio.c - Utility driver to provide simple UART console functions.
//
// Copyright (c) 2007-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.0.12573 of the Tiva Utility Library.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include <soc_C6748.h>
//#include "hw_ints.h"
//#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_uart.h"
#include "debug.h"
#include "interrupt.h"
//#include "rom.h"
//#include "rom_map.h"
//#include "sysctl.h"
#include "uart.h"
#include "uartstdio.h"
#include "portmacro.h"

//*****************************************************************************
//
// If buffered mode is defined, set aside RX and TX buffers and read/write
// pointers to control them.
//
//*****************************************************************************
#ifdef UART_BUFFERED

// ��������BUFFER
static unsigned char g_pcUARTTxBuffer[UART_BUFFER_ID_SIZE][UART_TX_BUFFER_SIZE];
static volatile uint32_t g_ui32UARTTxWriteIndex[UART_BUFFER_ID_SIZE];
static volatile uint32_t g_ui32UARTTxReadIndex[UART_BUFFER_ID_SIZE];

// ��������BUFFER
static unsigned char g_pcUARTRxBuffer[UART_BUFFER_ID_SIZE][UART_RX_BUFFER_SIZE];
static volatile uint32_t g_ui32UARTRxWriteIndex[UART_BUFFER_ID_SIZE];
static volatile uint32_t g_ui32UARTRxReadIndex[UART_BUFFER_ID_SIZE];


////BUFFER������
#define ADVANCE_TX_BUFFER_INDEX(Index)  (Index) = ((Index) + 1) % UART_TX_BUFFER_SIZE
#define ADVANCE_RX_BUFFER_INDEX(Index)  (Index) = ((Index) + 1) % UART_RX_BUFFER_SIZE
#endif

/*���¶�����Ҫ��UARTStdioConfig����������*/
// ��־ʹ�õ�UART��ַ.
static uint32_t g_ui32Base[UART_BUFFER_ID_SIZE];
// ��׼ʹ�õ�UART�жϺ�
static uint32_t g_ui32UARTInt[UART_BUFFER_ID_SIZE];

//*****************************************************************************
//
// The list of possible base addresses for the console UART.
//
//*****************************************************************************
static const uint32_t g_ui32UARTBase[UART_BUFFER_ID_SIZE] =
{
 SOC_UART_0_REGS, SOC_UART_1_REGS, SOC_UART_2_REGS
};

//*****************************************************************************
//! \param PortNum UART��
//! ȷ��BUFFER�Ƿ�Ϊ��
//! \return ������/��(bool)
//*****************************************************************************
#ifdef UART_BUFFERED
static bool
IsTxBufferFull(uint32_t PortNum)
{
    uint32_t ui32Write;
    uint32_t ui32Read;

    ui32Write = g_ui32UARTTxWriteIndex[PortNum];
    ui32Read = g_ui32UARTTxReadIndex[PortNum];

    return ((((ui32Write + 1) % UART_TX_BUFFER_SIZE) == ui32Read) ? true : false);
}
static bool
IsRxBufferFull(uint32_t PortNum)
{
    uint32_t ui32Write;
    uint32_t ui32Read;

    ui32Write = g_ui32UARTRxWriteIndex[PortNum];
    ui32Read = g_ui32UARTRxReadIndex[PortNum];

    return ((((ui32Write + 1) % UART_RX_BUFFER_SIZE) == ui32Read) ? true : false);
}
#endif

//*****************************************************************************
//! \param PortNum UART��
//! ȷ��BUFFER�Ƿ�Ϊ��
//! \return ������/��(bool)
//*****************************************************************************
#ifdef UART_BUFFERED
static bool IsTxBufferEmpty(uint32_t PortNum)
{
    uint32_t ui32Write;
    uint32_t ui32Read;

    ui32Write = g_ui32UARTTxWriteIndex[PortNum];
    ui32Read = g_ui32UARTTxReadIndex[PortNum];

    return ((ui32Write == ui32Read) ? true : false);
}
static bool IsRxBufferEmpty(uint32_t PortNum)
{
    uint32_t ui32Write;
    uint32_t ui32Read;

    ui32Write = g_ui32UARTRxWriteIndex[PortNum];
    ui32Read = g_ui32UARTRxReadIndex[PortNum];

    return ((ui32Write == ui32Read) ? true : false);
}
#endif

//*****************************************************************************
//! \param PortNum UART��
//! ȷ��BUFFER�е��ֽ���
//! \return �����ֽ���(32λ)
//*****************************************************************************
#ifdef UART_BUFFERED
static uint32_t
GetTxBufferCount(uint32_t PortNum)
{
    uint32_t ui32Write;
    uint32_t ui32Read;

    ui32Write = g_ui32UARTTxWriteIndex[PortNum];
    ui32Read = g_ui32UARTTxReadIndex[PortNum];

    return ((ui32Write >= ui32Read) ? (ui32Write - ui32Read) :
            (UART_TX_BUFFER_SIZE - (ui32Read - ui32Write)));
}

static uint32_t
GetRxBufferCount(uint32_t PortNum)
{
    uint32_t ui32Write;
    uint32_t ui32Read;

    ui32Write = g_ui32UARTRxWriteIndex[PortNum];
    ui32Read = g_ui32UARTRxReadIndex[PortNum];

    return ((ui32Write >= ui32Read) ? (ui32Write - ui32Read) :
            (UART_RX_BUFFER_SIZE - (ui32Read - ui32Write)));
}
#endif
//*****************************************************************************
//! \param PortNum UART��
//! ȷ��BUFFER�п�����ֽ��� (����ʹ��)
//! \return �����ֽ���(32λ)
//*****************************************************************************
#ifdef UART_BUFFERED
static uint32_t
GetTxBufferFreeCount(uint32_t PortNum)
{
    return (UART_TX_BUFFER_SIZE-GetTxBufferCount(PortNum));
}

//static uint32_t
//GetRxBufferFreeCount(uint32_t PortNum)
//{
//    return (UART_RX_BUFFER_SIZE-GetRxBufferCount(PortNum));
//}
#endif
//*****************************************************************************
//
// Take as many bytes from the transmit buffer as we have space for and move
// them into the UART transmit FIFO.
//
//*****************************************************************************
#ifdef UART_BUFFERED
static void
UARTPrimeTransmit(uint32_t ui32Base, uint32_t PortNum)
{
    if (!IsTxBufferEmpty(PortNum))
    {
        IntDisable(g_ui32UARTInt[PortNum]);
        while (UARTSpaceAvail(ui32Base) && !IsTxBufferEmpty(PortNum))
        {
            UARTCharPutNonBlocking(ui32Base,
                                       g_pcUARTTxBuffer[PortNum][g_ui32UARTTxReadIndex[PortNum]]);
            ADVANCE_TX_BUFFER_INDEX(g_ui32UARTTxReadIndex[PortNum]);
        }
        IntEnable(g_ui32UARTInt[PortNum]);
    }
}

#endif

//*****************************************************************************
//
//! Configures the UART console.
//!
//! \param ui32PortNum is the number of UART port to use for the serial console
//! (0-2)
//! \param ui32Baud is the bit rate that the UART is to be configured to use.
//! \param ui32SrcClock is the frequency of the source clock for the UART
//! module.
//!
//! This function will configure the specified serial port to be used as a
//! serial console.  The serial parameters are set to the baud rate
//! specified by the \e ui32Baud parameter and use 8 bit, no parity, and 1 stop
//! bit.
//!
//! This function must be called prior to using any of the other UART console
//! functions: UARTprintf() or UARTgets().  This function assumes that the
//! caller has previously configured the relevant UART pins for operation as a
//! UART rather than as GPIOs.
//!
//! \return None.
//
//*****************************************************************************
void
UARTStdioConfig(uint32_t ui32PortNum, uint32_t ui32IntNum, uint32_t ui32Baud, uint32_t ui32SrcClock)
{
    ASSERT(   (ui32PortNum == 0)
           || (ui32PortNum == 1)
           || (ui32PortNum == 2));


    ASSERT(g_ui32Base[ui32PortNum] == 0);



    g_ui32Base[ui32PortNum] = g_ui32UARTBase[ui32PortNum]; //�趨UART[Num]��ַ
    g_ui32UARTInt[ui32PortNum] = ui32IntNum;


    /*�趨UART����ַ��clkƵ�ʣ�������,
            У��λ �ޣ�ֹͣλ 1������λ 8,
            16����������*/
    UARTConfigSetExpClk(g_ui32Base[ui32PortNum], ui32SrcClock, ui32Baud,
                          /*UART_STICK_PARITY| UART_STOP_BIT |*/UART_WORDL_8BITS,
                          UART_OVER_SAMP_RATE_16);

    // ʹ�� UART
    UARTEnable(g_ui32Base[ui32PortNum]);

    // ʹ�ܽ��� / ���� FIFO
    UARTFIFOEnable(g_ui32Base[ui32PortNum]);

    // ���� FIFO ����
    UARTFIFOLevelSet(g_ui32Base[ui32PortNum], UART_RX_TRIG_LEVEL_1);

    // ʹ���ж� �����жϴ�����ʽ
    UARTIntEnable(g_ui32Base[ui32PortNum], UART_INT_LINE_STAT  | UART_INT_TX_EMPTY | UART_INT_RXDATA_CTI);
}

//*****************************************************************************
//! \param pcBuf ��Ҫ���ⷢBUFFER������ͷ
//! \param ui32Len ��BUFFER���ֽ���
//! \param PortNum ��PortNum��ӦUART�ŵ�BUFFER
//! ����Ӧ�ŵ�BUFFER�п��࣬��pcBufΪ��ַͷ��һЩ���������Ӧ�ŵ�BUFFER
//! \return ����ʵ����BUFFER���ֽ���
//*****************************************************************************
int
UARTwrite(const uint8_t *pcBuf, uint32_t ui32Len, uint32_t PortNum)
{
    unsigned int uIdx;
    ASSERT(pcBuf != 0);
    ASSERT(g_ui32Base[PortNum] != 0);

    while(GetTxBufferFreeCount(PortNum)<ui32Len)
    {

    }
    for (uIdx = 0; uIdx < ui32Len; uIdx++)
    {
        if (!IsTxBufferFull(PortNum))
        {
            g_pcUARTTxBuffer[PortNum][g_ui32UARTTxWriteIndex[PortNum]] = pcBuf[uIdx];
            ADVANCE_TX_BUFFER_INDEX(g_ui32UARTTxWriteIndex[PortNum]);
        }
        else
        {
            break;
        }
    }

    if (!IsTxBufferEmpty(PortNum))
    {
        UARTPrimeTransmit(g_ui32Base[PortNum],PortNum);
        UARTIntEnable(g_ui32Base[PortNum], UART_INT_TX_EMPTY);
    }

    return (uIdx);
}

//*****************************************************************************
//
//! A simple UART based get string function, with some line processing.
//!
//! \param pcBuf points to a buffer for the incoming string from the UART.
//! \param ui32Len is the length of the buffer for storage of the string,
//! including the trailing 0.
//!
//! This function will receive a string from the UART input and store the
//! characters in the buffer pointed to by \e pcBuf.  The characters will
//! continue to be stored until a termination character is received.  The
//! termination characters are CR, LF, or ESC.  A CRLF pair is treated as a
//! single termination character.  The termination characters are not stored in
//! the string.  The string will be terminated with a 0 and the function will
//! return.
//!
//! In both buffered and unbuffered modes, this function will block until
//! a termination character is received.  If non-blocking operation is required
//! in buffered mode, a call to UARTPeek() may be made to determine whether
//! a termination character already exists in the receive buffer prior to
//! calling UARTgets().
//!
//! Since the string will be null terminated, the user must ensure that the
//! buffer is sized to allow for the additional null character.
//!
//! \return Returns the count of characters that were stored, not including
//! the trailing 0.
//
//*****************************************************************************
int
UARTgets(uint8_t *pcBuf, uint32_t ui32Len,uint32_t PortNum)
{
    uint32_t ui32Count = 0;
    int8_t cChar;
    ASSERT(pcBuf != 0);
    ASSERT(ui32Len != 0);
    ASSERT(g_ui32Base[PortNum] != 0);

    ui32Len--;

    if (GetRxBufferCount(PortNum) > ui32Len)
    {
        cChar = g_pcUARTRxBuffer[PortNum][g_ui32UARTRxReadIndex[PortNum]];
        ADVANCE_RX_BUFFER_INDEX(g_ui32UARTRxReadIndex[PortNum]);

        if ((cChar == '\r') || (cChar == '\n') || (cChar == 0x1b))
        {
            //
            // Stop processing the input and end the line.
            //
            //break;
        }

        if (ui32Count < ui32Len)
        {
            //
            // Store the character in the caller supplied buffer.
            //
            pcBuf[ui32Count] = cChar;

            //
            // Increment the count of characters received.
            //
            ui32Count++;
        }
    }

    pcBuf[ui32Count] = 0;

    return (ui32Count);
}

//*****************************************************************************
//! \param data_rx ��Ҫ��ֵ�ı�����ַ
//! \param PortNum ȡֵ��BUFFER��Ӧ��UART��
//! ��Num��UART�Ľ���BUFFER��ȡһ���ֽڸ�ֵ��data_rx
//! \return ���� ��������ʵ�ֵ�״̬
//*****************************************************************************
unsigned char
UARTgetc(uint8_t *data_rx,uint32_t PortNum)
{
    if (IsRxBufferEmpty(PortNum))
    {
        return (cQ_BUFF_EMPTY);
    }
    portENTER_CRITICAL();   //ʹ���ٽ��
    *data_rx = g_pcUARTRxBuffer[PortNum][g_ui32UARTRxReadIndex[PortNum]];
    ADVANCE_RX_BUFFER_INDEX(g_ui32UARTRxReadIndex[PortNum]);
    portEXIT_CRITICAL();    //�˳��ٽ��
    return (cQ_BUFF_NORMAL);
}


//*****************************************************************************
//! ��ʼ��Num��UART�Ľ���BUFFER
//*****************************************************************************
#if defined(UART_BUFFERED) || defined(DOXYGEN)
void
UARTFlushRx(uint8_t PortNum)       //  ��BUFFER
{
    g_ui32UARTRxReadIndex[PortNum] = 0;
    g_ui32UARTRxWriteIndex[PortNum] = 0;

}
#endif

//*****************************************************************************
//! ��ʼ��Num��UART�ķ���BUFFER
//*****************************************************************************
#if defined(UART_BUFFERED) || defined(DOXYGEN)
void
UARTFlushTx(bool bDiscard, uint32_t PortNum)
{
    if (bDiscard)
    {

        g_ui32UARTTxReadIndex[PortNum] = 0;          //����ջ������BUFFER
        g_ui32UARTTxWriteIndex[PortNum] = 0;

    }
    else
    {
        while (!IsTxBufferEmpty(PortNum))        //������ջ��Ϊ��
        {

        }
    }
}
#endif


//*****************************************************************************
//
//! Handles UART interrupts.
//!
//! This function handles interrupts from the UART.  It will copy data from the
//! transmit buffer to the UART transmit FIFO if space is available, and it
//! will copy data from the UART receive FIFO to the receive buffer if data is
//! available.
//!
//! \return None.
//
//*****************************************************************************
#if defined(UART_BUFFERED) || defined(DOXYGEN)
void
UART2StdioIntHandler(void)  //��Ϊvoid UART2�ж�
{

    uint32_t ui32Ints;
    int32_t i32Char;

    ui32Ints = UARTIntStatus(SOC_UART_2_REGS);       // ȷ���ж�Դ
    IntEventClear(SYS_INT_UART2_INT);                // ��� UART2 ϵͳ�ж�

    if (ui32Ints & UART_INTID_TX_EMPTY)                             //  ȷ�Ϸ���FIFO
    {
        UARTPrimeTransmit(g_ui32Base[2], 2);
        if (IsTxBufferEmpty(2))
        {
            UARTIntDisable(g_ui32Base[2], UART_INT_TX_EMPTY);
        }
    }

    if (ui32Ints & UART_INTID_RX_DATA)            // ȷ�Ͻ���FIFO
    {
        while (UARTCharsAvail(g_ui32Base[2]))              // �ӵ�ǰUART[Num]��ȡ����
        {
            i32Char = UARTCharGetNonBlocking(SOC_UART_2_REGS);   //�趨������
            if (!IsRxBufferFull(2))
            {
                g_pcUARTRxBuffer[2][g_ui32UARTRxWriteIndex[2]] =
                    (unsigned char)(i32Char & 0xFF);
                ADVANCE_RX_BUFFER_INDEX(g_ui32UARTRxWriteIndex[2]);    //�趨BUFFER��

            }
        }

        UARTPrimeTransmit(g_ui32Base[2], 2);                  // ����TXBUFFER
        UARTIntEnable(g_ui32Base[2], UART_INT_TX_EMPTY);     // ����ǰUART[Num]�ж�
    }
}
#endif
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
