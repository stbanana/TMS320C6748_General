//******************************************************************************
//*                               InitCpu.c                                  *
//******************************************************************************
//*           Copyright (c) 2020 SKONDA ELECTRONIC LTD                        *
//******************************************************************************
//* FILE NAME  : InitCpu.c
//* DESCRIPTION:
//* ORIGINATOR : Sven
//* DATE       : 11/07/2022
//* VERSION    : 1.0.0
//******************************************************************************
/*==============================================================================
                           head file information
===============================================================================*/
#include "Includes.h"
/******************************************************************************
                           constant variables
*******************************************************************************/

/******************************************************************************
                           external variables
*******************************************************************************/
/******************************************************************************
                           private variables
*******************************************************************************/
uint32_t ui32SysClock;
/******************************************************************************
                           external functions
*******************************************************************************/

/******************************************************************************
                           private functions
*******************************************************************************/
static void PSCInit(void);      //PSCʱ��ʹ��

static void CaCheInit(void);    //�����ʼ��
static void InterruptInit(void);    //�жϺ�������
static void GPIOInit(void);     //GPIO��������
static void UARTInit(void);     //UART��������
static void uPPInit(void);      //uPP��������

/******************************************************************************
function name : InitCpu
Description   :
*******************************************************************************/
void InitCpu(void)
{
    /*����Ӳ��PCB���*/
    PSCInit();      //PSCʱ������
    PinoutSet();    //���Ÿ�������
    /*��������������*/
    CaCheInit();    //�����ʼ��
    InterruptInit();    //�жϺ�����
    GPIOInit();    //GPIO��������
    UARTInit();    //UART��������
    uPPInit();     //uPP��������
}

static void PSCInit(void)
{
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_TC2, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);    // ʹ�� tc2 ģ�� freertos��֧�ֶ�ʱ��
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_GPIO, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);    // ʹ�� GPIO ģ��
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_UART2, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);   // ʹ�� UART2 ģ��
    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_UPP, PSC_POWERDOMAIN_ALWAYS_ON, PSC_MDCTL_NEXT_ENABLE);     // ʹ�� Upp ģ��
}

void CaCheInit(void)
{
    CacheEnableMAR((unsigned int)0xC0000000, (unsigned int)0x10000000);
    CacheEnable(L1PCFG_L1PMODE_32K | L1DCFG_L1DMODE_32K | L2CFG_L2MODE_256K);
}

void InterruptInit(void)
{
    IntDSPINTCInit();   // ��ʼ�� DSP �жϿ�����
    IntGlobalEnable();  // ʹ�� DSP ȫ���ж�

    /*������rtos֧�ֺ����������ж���������ֱ��д��*/
//    IntRegister(portTICK_INT_MASK, _vPortTickISR);      //rtos��֧���ж� �����л�    ռ��15���ж�
//    IntRegister(portYIELD_INT_MASK, _vPortYieldISR);    //rtos��֧���ж� ��ʱ��2     ռ��14���ж�

    /* ��UART2�жϺ��� */
    IntRegister(C674X_MASK_UART2, UART2StdioIntHandler);
    IntEventMap(C674X_MASK_UART2, SYS_INT_UART2_INT);
    IntEnable(C674X_MASK_UART2);

    /* ��uPP�жϺ��� */
    IntRegister(C674X_MASK_INT5, uPPIsr);
    IntEventMap(C674X_MASK_INT5, SYS_INT_UPP_INT);
    IntEnable(C674X_MASK_INT5);
}

static void GPIOInit(void)
{
    /* ���İ� LED */
    GPIODirModeSet(SOC_GPIO_0_REGS, GPIO_BANK_BASE_6+GPIO_PIN_ADDTL_12, GPIO_DIR_OUTPUT);   // GPIO6[12]

    /* �װ� LED */
    GPIODirModeSet(SOC_GPIO_0_REGS, GPIO_BANK_BASE_0+GPIO_PIN_ADDTL_0, GPIO_DIR_OUTPUT);    // GPIO0[0]     D7
}

static void UARTInit(void)
{
    /* UART2 */
    UARTStdioConfig(2, C674X_MASK_UART2, BAUD_115200, UART_2_FREQ);
}

static void uPPInit(void)
{
    /* uPP���ݸ�ʽ���� */
    uPPDataFmtConfig(SOC_UPP_0_REGS, uPP_CHA, uPP_DataPackingFmt_LJZE | uPP_DataPacking_FULL
                            | uPP_InterfaceWidth_8BIT | uPP_DataRate_SINGLE);
    uPPDataFmtConfig(SOC_UPP_0_REGS, uPP_CHB, uPP_DataPackingFmt_LJZE | uPP_DataPacking_FULL
                            | uPP_InterfaceWidth_8BIT | uPP_DataRate_SINGLE);
    /* uPPͨ������ */
    uPPChannelConfig(SOC_UPP_0_REGS, uPP_DDRDEMUX_DISABLE | uPP_SDRTXIL_DISABLE | uPP_CHN_TWO
                                | uPP_DUPLEX0);
    /* uPP�������� */
    uPPPinConfig(SOC_UPP_0_REGS, uPP_CHA, uPP_PIN_TRIS | uPP_PIN_ENABLE | uPP_PIN_WAIT | uPP_PIN_START);
    uPPPinConfig(SOC_UPP_0_REGS, uPP_CHB, uPP_PIN_ENABLE | uPP_PIN_WAIT | uPP_PIN_START);
    /* uPPʱ������ */
    uPPClkConfig(SOC_UPP_0_REGS, uPP_CHB, 57000000, UPP_FREQ, uPP_PIN_PHASE_NORMAL);
    /* uPP����������� */
    uPPIdleValueConfig(SOC_UPP_0_REGS, uPP_CHB, 0xAAAA);
    /* uPP�ж�ʹ������ */
    uPPIntEnable(SOC_UPP_0_REGS, uPP_DMA_CHI, uPP_INT_EOW);
    uPPIntEnable(SOC_UPP_0_REGS, uPP_DMA_CHQ, uPP_INT_EOW);
    /* uPPʹ�� */
    uPPEnable(SOC_UPP_0_REGS);
}


