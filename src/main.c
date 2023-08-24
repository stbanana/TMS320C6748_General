

/**
 * main.c
 */

#include "Includes.h"

/****************************************************************************/
/*                      LOCAL FUNCTION PROTOTYPES                           */
/****************************************************************************/
static void ConfigureIntUART(void);
static void SetupInt(void);
static void UARTIsr(void);

/****************************************************************************/
/*                      GLOBAL VARIABLES                                    */
/****************************************************************************/
char txArray[] = "StarterWare UART echo application\n\r";

/****************************************************************************/
/*                      LOCAL FUNCTION DEFINITIONS                          */
/****************************************************************************/

int main(void)
{
    unsigned int intFlags = 0;
    unsigned int config = 0;

    /* Enabling the PSC for UART1.*/
//    PSCModuleControl(SOC_PSC_1_REGS, HW_PSC_UART1, PSC_POWERDOMAIN_ALWAYS_ON,
//             PSC_MDCTL_NEXT_ENABLE);

    /* Setup PINMUX */

    UARTPinMuxSetup(2, FALSE);

    /* Enabling the transmitter and receiver*/
    UARTEnable(SOC_UART_1_REGS);

    /* 1 stopbit, 8-bit character, no parity */
    config = UART_WORDL_8BITS;

    /* Configuring the UART parameters*/
    UARTConfigSetExpClk(SOC_UART_1_REGS, SOC_UART_1_MODULE_FREQ,
                        BAUD_115200, config,
                        UART_OVER_SAMP_RATE_16);

    /* Enabling the FIFO and flushing the Tx and Rx FIFOs.*/
    UARTFIFOEnable(SOC_UART_1_REGS);

    /* Setting the UART Receiver Trigger Level*/
    UARTFIFOLevelSet(SOC_UART_1_REGS, UART_RX_TRIG_LEVEL_1);

    /*
    ** Enable AINTC to handle interrupts. Also enable IRQ interrupt in ARM
    ** processor.
    */
    SetupInt();

    /* Configure AINTC to receive and handle UART interrupts. */
    ConfigureIntUART();

    /* Preparing the 'intFlags' variable to be passed as an argument.*/
    intFlags |= (UART_INT_LINE_STAT  |  \
                 UART_INT_TX_EMPTY |    \
                 UART_INT_RXDATA_CTI);

    /* Enable the Interrupts in UART.*/
    UARTIntEnable(SOC_UART_1_REGS, intFlags);

    InitCpu();     // 初始化芯片
//    InitSysVar();  // 初始化常量
//    InitSysPara(); // 初始化变量

    TEST_led();
	return 0;
}
//0x01C20000

/*
** \brief   Interrupt Service Routine(ISR) to be executed on UART interrupts.
**          Depending on the source of interrupt, this
**          1> writes to the serial communication console, or
**          2> reads from the serial communication console, or
**          3> reads the byte in RBR if receiver line error has occured.
*/
static void UARTIsr()
{
    static unsigned int length = sizeof(txArray);
    static unsigned int count = 0;
    unsigned char rxData = 0;
    unsigned int int_id = 0;
    /* This determines the cause of UART1 interrupt.*/
    //确认中断触发事件
    int_id = UARTIntStatus(SOC_UART_1_REGS);

#ifdef _TMS320C6X
    // Clear UART1 system interrupt in DSPINTC
    IntEventClear(SYS_INT_UART1_INT);
#else
    /* Clears the system interupt status of UART1 in AINTC. */
    IntSystemStatusClear(SYS_INT_UARTINT2);
#endif

    /* Checked if the cause is transmitter empty condition.*/
    if(UART_INTID_TX_EMPTY == int_id)
    {
        if(0 < length)
        {
            /* Write a byte into the THR if THR is free. */
            UARTCharPutNonBlocking(SOC_UART_1_REGS, txArray[count]);
            length--;
            count++;
        }
        if(0 == length)
        {
            /* Disable the Transmitter interrupt in UART.*/
            UARTIntDisable(SOC_UART_1_REGS, UART_INT_TX_EMPTY);
        }
     }

    /* Check if the cause is receiver data condition.*/
    if(UART_INTID_RX_DATA == int_id)
    {
        rxData = UARTCharGetNonBlocking(SOC_UART_1_REGS);
        UARTCharPutNonBlocking(SOC_UART_1_REGS, rxData);
    }


    /* Check if the cause is receiver line error condition.*/
    if(UART_INTID_RX_LINE_STAT == int_id)
    {
        while(UARTRxErrorGet(SOC_UART_1_REGS))
        {
            /* Read a byte from the RBR if RBR has data.*/
            UARTCharGetNonBlocking(SOC_UART_1_REGS);
        }
    }

    return;
}

/*
** \brief   This function invokes necessary functions to configure the ARM
**          processor and ARM Interrupt Controller(AINTC) to receive and
**          handle interrupts.
*/


static void SetupInt(void)
{
#ifdef _TMS320C6X
    // Initialize the DSP INTC
    IntDSPINTCInit();

    // Enable DSP interrupts globally
    IntGlobalEnable();
#else
    /* Initialize the ARM Interrupt Controller(AINTC). */
    IntAINTCInit();

    /* Enable IRQ in CPSR.*/
    IntMasterIRQEnable();

    /* Enable the interrupts in GER of AINTC.*/
    IntGlobalEnable();

    /* Enable the interrupts in HIER of AINTC.*/
    IntIRQEnable();
#endif
}

/*
** \brief  This function confiugres the AINTC to receive UART interrupts.
*/
static void ConfigureIntUART(void)
{
#ifdef _TMS320C6X
    IntRegister(C674X_MASK_INT4, UARTIsr);
    IntEventMap(C674X_MASK_INT4, SYS_INT_UART1_INT);
    IntEnable(C674X_MASK_INT4);
#else
    /* Registers the UARTIsr in the Interrupt Vector Table of AINTC. */
    IntRegister(SYS_INT_UARTINT2, UARTIsr);

    /* Map the channel number 2 of AINTC to UART1 system interrupt. */
    IntChannelSet(SYS_INT_UARTINT2, 2);

    IntSystemEnable(SYS_INT_UARTINT2);
#endif
}
