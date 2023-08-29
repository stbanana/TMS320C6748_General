/****************************************************************************/
/*                                                                          */
/*              ���ݴ������ӿƼ����޹�˾                                    */
/*                                                                          */
/*              Copyright 2015 Tronlong All rights reserved                 */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              uPP �豸����㺯��                                          */
/*                                                                          */
/*              2015��04��19��                                              */
/*                                                                          */
/****************************************************************************/
#include "hw_upp.h"
#include "debug.h"
#include "hw_types.h"
#include "uPP.h"

#include "soc_C6748.h"
#include "hw_syscfg0_C6748.h"

#include <stdio.h>
#include <stdlib.h>

/****************************************************************************/
/*                                                                          */
/*              �궨��                                                      */
/*                                                                          */
/****************************************************************************/
static void Delay(volatile unsigned int count);

/****************************************************************************/
/*                                                                          */
/*              �ܽŸ�������                                                */
/*                                                                          */
/****************************************************************************/
void uPPPinMuxSetup(unsigned char OperatingMode)
{
	volatile unsigned int savePinMux = 0;

	// ���ݹܽŸ�������
	switch(OperatingMode)
	{
		case uPP_CHA_8BIT:
		{
			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) & ~(0xFFFFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) |= (0x44444400 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) & ~(0x000000FF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) |= (0x00000044 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & ~(0x00FFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) |= (0x00444400 | savePinMux);
			break;
		}

		case uPP_CHA_16BIT:
		{
			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) & ~(0xFFFFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) |= (0x44444400 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) & ~(0xFFFFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) |= (0x44444444 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) & ~(0x000000FF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) |= (0x00000044 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & ~(0x00FFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) |= (0x00444400 | savePinMux);
			break;
		}

		case uPP_CHA_8BIT_CHB_8BIT:
		{
			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) & ~(0xFFFF0000);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) |= (0x44440000 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) & ~(0xFFFFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) |= (0x44444400 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) & ~(0xFFFFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) |= (0x44444444 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) & ~(0x000000FF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) |= (0x00000044 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & ~(0x00FFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) |= (0x00444400 | savePinMux);
			break;
		}

		case uPP_CHA_8BIT_CHB_16BIT:
		{
			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) & ~(0xFFFF0000);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) |= (0x44440000 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) & ~(0xFFFFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) |= (0x44444400 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) & ~(0xFFFFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) |= (0x44444444 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) & ~(0xFFFFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) |= (0x44444444 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) & ~(0x000000FF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) |= (0x00000044 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & ~(0x00FFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) |= (0x00444400 | savePinMux);
			break;
		}

		case uPP_CHA_16BIT_CHB_8BIT:
		{
			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) & ~(0xFFFF0000);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) |= (0x44440000 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) & ~(0xFFFFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) |= (0x44444400 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) & ~(0xFFFFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) |= (0x44444444 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) & ~(0x000000FF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) |= (0x00000044 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) & ~(0xFFFFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) |= (0x44444400 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & ~(0x00FFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) |= (0x00444444 | savePinMux);
			break;
		}

		case uPP_CHA_16BIT_CHB_16BIT:
		{
			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) & ~(0xFFFF0000);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(13)) |= (0x44440000 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) & ~(0xFFFFFF00);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(14)) |= (0x44444400 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) & ~(0xFFFFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(15)) |= (0x44444444 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) & ~(0xFFFFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(16)) |= (0x44444444 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) & ~(0xFFFFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(17)) |= (0x44444444 | savePinMux);

			savePinMux = HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) & ~(0x00FFFFFF);
			HWREG(SOC_SYSCFG_0_REGS + SYSCFG0_PINMUX(18)) |= (0x00444444 | savePinMux);
			break;
		}

		default:
		{
			printf("\r\nuPPPinMuxSetup: unsupported Operating Mode!\r\n");
		}
	}

	// ���ƹܽŸ�������

}

/****************************************************************************/
/*                                                                          */
/*              ʱ������                                                    */
/*                                                                          */
/****************************************************************************/
/*
 * baseAddr��uPP�Ĵ�����ַ SOC_UPP_0_REGS
 * channel��ͨ��A��B uPP_CHA uPP_CHB
 * Clk��uppģʽ��Ƶ��
 * moduleClk��uppģ���Ƶ�� ��PSCʱ�ӷ������
 * polarity����λģʽ����(���ɣ�����ϸ����оƬ����
 *
 * uPPCLK = (CPUCLK / 2) / (2 * (DIV + 1) (DIV = 0, 1, 2, 3 ... 15)
 * 456MHz ��Ƶ��֧�ֵ�ʱ�� 114MHz��57MHz��38MHz��28.5MHz��22.8MHz ......
 */
void uPPClkConfig(unsigned int baseAddr, unsigned char channel, unsigned int Clk,
		unsigned int moduleClk, unsigned char polarity)
{
	// ʱ��ֻ�ڷ���ģʽ��Ч
	// ����ģʽ�����ʱ���಻�ܳ��� CPU ʱ���ķ�֮һ
    unsigned int clkDiv;
    clkDiv = moduleClk / Clk / 2 - 1;

    // ��Ƶϵ���������������Χ
    ASSERT(((clkDiv >= 0) && (clkDiv <= 15)));

    if(channel == uPP_CHA)
    {
    	HWREG(baseAddr + UPP_UPICR) &= ~(UPP_UPICR_CLKINVA | UPP_UPICR_CLKDIVA);
    	HWREG(baseAddr + UPP_UPICR) |= (clkDiv <<  UPP_UPICR_CLKDIVA_SHIFT) \
    									| (polarity << UPP_UPICR_CLKINVA_SHIFT);
    }
    else if(channel == uPP_CHB)
    {
    	HWREG(baseAddr + UPP_UPICR) &= ~(UPP_UPICR_CLKINVB | UPP_UPICR_CLKDIVB);
    	HWREG(baseAddr + UPP_UPICR) |= (clkDiv <<  UPP_UPICR_CLKDIVB_SHIFT) \
										| (polarity << UPP_UPICR_CLKINVB_SHIFT);
    }
}

/****************************************************************************/
/*                                                                          */
/*              ����ʹ��                                                    */
/*                                                                          */
/****************************************************************************/
void uPPEnable(unsigned int baseAddr)
{
   	HWREG(baseAddr + UPP_UPPCR) |= ((0x00000001u) <<  UPP_UPPCR_EN_SHIFT);
}

/****************************************************************************/
/*                                                                          */
/*              �������                                                    */
/*                                                                          */
/****************************************************************************/
void uPPDisable(unsigned int baseAddr)
{
   	HWREG(baseAddr + UPP_UPPCR) &= ((0x00000000u) <<  UPP_UPPCR_EN_SHIFT);
}

/****************************************************************************/
/*                                                                          */
/*              ��������                                                    */
/*                                                                          */
/****************************************************************************/
void uPPPeripheralConfig(unsigned int baseAddr, unsigned int config)
{
	HWREG(baseAddr + UPP_UPPCR) |= config;
}

/****************************************************************************/
/*                                                                          */
/*              ���ݸ�ʽ����                                                */
/*                                                                          */
/****************************************************************************/
void uPPDataFmtConfig(unsigned int baseAddr, unsigned char channel, unsigned int config)
{
	if(channel == uPP_CHA)
	{
		config <<= 16;
		HWREG(baseAddr + UPP_UPCTL) |= (config & (0x007F0000));
	}
	else if(channel == uPP_CHB)
	{
		config <<= 24;
		HWREG(baseAddr + UPP_UPCTL) |= (config & (0x7F000000));
	}
}

/****************************************************************************/
/*                                                                          */
/*              ͨ������                                                    */
/*                                                                          */
/****************************************************************************/
void uPPChannelConfig(unsigned int baseAddr, unsigned int config)
{
	HWREG(baseAddr + UPP_UPCTL) |= (config & (0x0000001F));
}

/****************************************************************************/
/*                                                                          */
/*              �ܽ�����                                                    */
/*                                                                          */
/****************************************************************************/
void uPPPinConfig(unsigned int baseAddr, unsigned char channel, unsigned int config)
{
	if(channel == uPP_CHA)
	{
		HWREG(baseAddr + UPP_UPICR) |= (config & (0x00003038));
	}
	else if(channel == uPP_CHB)
	{
		config <<= 16;
		HWREG(baseAddr + UPP_UPICR) |= (config & (0x30380000));
	}
}

/****************************************************************************/
/*                                                                          */
/*              �ܽ���λ����                                                */
/*                                                                          */
/****************************************************************************/
void uPPPinPolarityConfig(unsigned int baseAddr, unsigned char channel, unsigned int config)
{
	if(channel == uPP_CHA)
	{
		HWREG(baseAddr + UPP_UPICR) |= (config & (0x00000007));
	}
	else if(channel == uPP_CHB)
	{
		config <<= 16;
		HWREG(baseAddr + UPP_UPICR) |= (config & (0x00070000));
	}
}

/****************************************************************************/
/*                                                                          */
/*              �ӿڿ����������                                            */
/*                                                                          */
/****************************************************************************/
void uPPIdleValueConfig(unsigned int baseAddr, unsigned char channel, unsigned int config)
{
    if(channel == uPP_CHA)
    {
    	HWREG(baseAddr + UPP_UPIVR) |= (config <<  UPP_UPIVR_VALA_SHIFT);
    }
    else if(channel == uPP_CHB)
    {
    	HWREG(baseAddr + UPP_UPIVR) |= (config <<  UPP_UPIVR_VALB_SHIFT);
    }
}

/****************************************************************************/
/*                                                                          */
/*              ��������                                                    */
/*                                                                          */
/****************************************************************************/
void uPPThresholdConfig(unsigned int baseAddr, unsigned char channel, unsigned int config)
{
	switch (channel)
	{
		case uPP_CHA:
			HWREG(baseAddr + UPP_UPTCR) |= (config <<  UPP_UPTCR_TXSIZEA_SHIFT);
			break;
		case uPP_CHB:
			HWREG(baseAddr + UPP_UPTCR) |= (config <<  UPP_UPTCR_TXSIZEB_SHIFT);
			break;
		case uPP_DMA_CHI:
			HWREG(baseAddr + UPP_UPTCR) |= (config <<  UPP_UPTCR_RDSIZEI_SHIFT);
			break;
		case uPP_DMA_CHQ:
			HWREG(baseAddr + UPP_UPTCR) |= (config <<  UPP_UPTCR_RDSIZEQ_SHIFT);
			break;

	}
}

/****************************************************************************/
/*                                                                          */
/*              ���ֻػ�����                                                */
/*                                                                          */
/****************************************************************************/
void uPPDLBConfig(unsigned int baseAddr, unsigned int config)
{
	HWREG(baseAddr + UPP_UPDLB) &= ~0x00003000u;
	HWREG(baseAddr + UPP_UPDLB) |= config;

	if(config == UPP_UPDLB_BA)
	{
		HWREG(baseAddr + UPP_UPCTL) &= ~0x00000003u;
		HWREG(baseAddr + UPP_UPCTL) |=0x00000002u;
	}
	else if(config == UPP_UPDLB_AB)
	{
		HWREG(baseAddr + UPP_UPCTL) &= ~0x00000003u;
		HWREG(baseAddr + UPP_UPCTL) |= 0x00000003u;
	}
}

/****************************************************************************/
/*                                                                          */
/*              �ж�ʹ��                                                    */
/*                                                                          */
/****************************************************************************/
void uPPIntEnable(unsigned int baseAddr, unsigned char DMAchannel, unsigned int intFlags)
{
	if(DMAchannel == uPP_DMA_CHI)
	{
		HWREG(baseAddr + UPP_UPIES) = intFlags;
	}
	else if(DMAchannel == uPP_DMA_CHQ)
	{
		HWREG(baseAddr + UPP_UPIES) = (intFlags <<  8);
	}
}

/****************************************************************************/
/*                                                                          */
/*              �жϽ���                                                    */
/*                                                                          */
/****************************************************************************/
void uPPIntDisable(unsigned int baseAddr, unsigned char DMAchannel, unsigned int intFlags)
{
	if(DMAchannel == uPP_DMA_CHI)
	{
		HWREG(baseAddr + UPP_UPIEC) = intFlags;
	}
	else if(DMAchannel == uPP_DMA_CHQ)
	{
		HWREG(baseAddr + UPP_UPIEC) = (intFlags << 8);
	}
}

/****************************************************************************/
/*                                                                          */
/*              �ж����                                                    */
/*                                                                          */
/****************************************************************************/
void uPPIntClear(unsigned int baseAddr, unsigned char DMAchannel, unsigned int intFlags)
{
	if(DMAchannel == uPP_DMA_CHI)
	{
		HWREG(baseAddr + UPP_UPIER) = intFlags;
	}
	else if(DMAchannel == uPP_DMA_CHQ)
	{
		HWREG(baseAddr + UPP_UPIER) = (intFlags <<  8);
	}
}

/****************************************************************************/
/*                                                                          */
/*              �ж�״̬                                                    */
/*                                                                          */
/****************************************************************************/
unsigned int uPPIntStatus(unsigned int baseAddr, unsigned char DMAchannel)
{
	unsigned int intFlags;

	if(DMAchannel == uPP_DMA_CHI)
	{
		intFlags = HWREG(baseAddr + UPP_UPIER) & 0x0000001F;
	}
	else if(DMAchannel == uPP_DMA_CHQ)
	{
		intFlags = HWREG(baseAddr + UPP_UPIER) & 0x00001F00;
		intFlags >>=  8;
	}
	return (intFlags);
}

/****************************************************************************/
/*                                                                          */
/*              ȷ���ж�                                                    */
/*                                                                          */
/****************************************************************************/
void uPPEndOfInt(unsigned int baseAddr)
{
   	HWREG(baseAddr + UPP_UPEOI) = 0x00000000u;
}
/****************************************************************************/
/*                                                                          */
/*              DMA ����                                                    */
/*                                                                          */
/****************************************************************************/
void uPPDMATransfer(unsigned int baseAddr, unsigned char DMAchannel, uPPDMAConfig *config)
{
	if(DMAchannel == uPP_DMA_CHI)
	{
		HWREG(baseAddr + UPP_UPID0) = (int)config->WindowAddress << 3;
		HWREG(baseAddr + UPP_UPID1) = (config->LineCount << 16 ) | (config->ByteCount << 1);
		HWREG(baseAddr + UPP_UPID2) = config->LineOffsetAddress << 3;
	}
	else if(DMAchannel == uPP_DMA_CHQ)
	{
		HWREG(baseAddr + UPP_UPQD0) = (int)config->WindowAddress << 3;
		HWREG(baseAddr + UPP_UPQD1) = (config->LineCount << 16 ) | (config->ByteCount << 1);
		HWREG(baseAddr + UPP_UPQD2) = config->LineOffsetAddress << 3;
	}
}

/****************************************************************************/
/*                                                                          */
/*              DMA ״̬                                                    */
/*                                                                          */
/****************************************************************************/
uPPDMAStatus *uPPGetDMAStatus(unsigned int baseAddr, unsigned char channel)
{
	uPPDMAStatus * pDMAStatus;

	pDMAStatus = calloc(1, sizeof(uPPDMAStatus));

	if(channel == uPP_DMA_CHI)
	{
		pDMAStatus->WindowAddress = HWREG(baseAddr + UPP_UPIS0);
		pDMAStatus->LineCount     = (HWREG(baseAddr + UPP_UPIS1) >> 16) & 0x0000FFFF;
		pDMAStatus->ByteCount     = HWREG(baseAddr + UPP_UPIS1) & 0x0000FFFF;
		pDMAStatus->FIFO          = (HWREG(baseAddr + UPP_UPIS2) >> 4) & 0x0000000F;
		pDMAStatus->PEND          = (HWREG(baseAddr + UPP_UPIS2) >> 1) & 0x00000001;
		pDMAStatus->DMA           = HWREG(baseAddr + UPP_UPIS2) & 0x00000001;
	}
	else if(channel == uPP_DMA_CHQ)
	{
		pDMAStatus->WindowAddress = HWREG(baseAddr + UPP_UPQS0);
		pDMAStatus->LineCount     = (HWREG(baseAddr + UPP_UPQS1) >> 16) & 0x0000FFFF;
		pDMAStatus->ByteCount     = HWREG(baseAddr + UPP_UPQS1) & 0x0000FFFF;
		pDMAStatus->FIFO          = (HWREG(baseAddr + UPP_UPQS2) >> 4) & 0x0000000F;
		pDMAStatus->PEND          = (HWREG(baseAddr + UPP_UPQS2) >> 1) & 0x00000001;
		pDMAStatus->DMA           = HWREG(baseAddr + UPP_UPQS2) & 0x00000001;
	}

	return (pDMAStatus);
}

/****************************************************************************/
/*                                                                          */
/*              UPP��λ                                              */
/*                                                                          */
/****************************************************************************/
void uPPReset(unsigned int baseAddr)
{
	// toggle reset with short delay
	HWREG(baseAddr + UPP_UPPCR) &= ~0x00000010u;
	HWREG(baseAddr + UPP_UPPCR) |= 0x00000001u << 0x00000004u;
	Delay(0xffff);
	HWREG(baseAddr + UPP_UPPCR) &= ~0x00000010u;
}

/****************************************************************************/
/*                                                                          */
/*              ��ʱ                                                        */
/*                                                                          */
/****************************************************************************/
static void Delay(volatile unsigned int count)
{
    while(count--);
}
