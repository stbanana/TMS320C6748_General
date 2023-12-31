/****************************************************************************/
/*                                                                          */
/*              广州创龙电子科技有限公司                                    */
/*                                                                          */
/*              Copyright 2015 Tronlong All rights reserved                 */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                                                                          */
/*              uPP 设备抽象层函数                                          */
/*                                                                          */
/*              2015年04月19日                                              */
/*                                                                          */
/****************************************************************************/
#ifndef __UPP_H__
#define __UPP_H__

/****************************************************************************/
/*                                                                          */
/*              宏定义                                                      */
/*                                                                          */
/****************************************************************************/
// uPP 通道
#define uPP_CHA                    (0x00000000u)
#define uPP_CHB                    (0x00000001u)

#define uPP_DMA_CHI                (0x00000002u)
#define uPP_DMA_CHQ                (0x00000003u)

// uPP 管脚复用
// 详情参见 TMS320C6748 DSP Technical Reference Manual 1471页 表 31-3
#define uPP_CHA_8BIT               (0x00000000u)
#define uPP_CHA_16BIT              (0x00000001u)
#define uPP_CHB_16BIT              (0x00000003u)
#define uPP_CHA_8BIT_CHB_8BIT      (0x00000004u)
#define uPP_CHA_8BIT_CHB_16BIT     (0x00000005u)
#define uPP_CHA_16BIT_CHB_8BIT     (0x00000006u)
#define uPP_CHA_16BIT_CHB_16BIT    (0x00000007u)

// uPP 数据格式配置
// 数据对齐方式
#define uPP_DataPackingFmt_RJZE    (0x00000000u << 5)    // 右对齐 零扩展
#define uPP_DataPackingFmt_RJSE    (0x00000001u << 5)    // 右对齐 符号扩展
#define uPP_DataPackingFmt_LJZE    (0x00000002u << 5)    // 左对齐 零扩展

// 通道宽度
#define uPP_DataPacking_FULL       (0x00000000u << 2)    // 8 位或者 16 位
#define uPP_DataPacking_9BIT       (0x00000001u << 2)
#define uPP_DataPacking_10BIT      (0x00000002u << 2)
#define uPP_DataPacking_11BIT      (0x00000003u << 2)
#define uPP_DataPacking_12BIT      (0x00000004u << 2)
#define uPP_DataPacking_13BIT      (0x00000005u << 2)
#define uPP_DataPacking_14BIT      (0x00000006u << 2)
#define uPP_DataPacking_15BIT      (0x00000007u << 2)

// 接口宽度
#define uPP_InterfaceWidth_8BIT    (0x00000000u << 1)    // 8 位
#define uPP_InterfaceWidth_16BIT   (0x00000001u << 1)    // 16 位

// 数据率
#define uPP_DataRate_SINGLE        (0x00000000u << 0)    // 单边沿
#define uPP_DataRate_DOUBLE        (0x00000001u << 0)    // 双边沿

// uPP 通道配置
// 双倍数据率复用模式
#define uPP_DDRDEMUX_DISABLE       (0x00000000u << 4)
#define uPP_DDRDEMUX_ENABLE        (0x00000001u << 4)

// 单倍数据率交错模式
#define uPP_SDRTXIL_DISABLE        (0x00000000u << 3)
#define uPP_SDRTXIL_ENABLE         (0x00000001u << 3)

// 通道使用配置
#define uPP_CHN_ONE                (0x00000000u << 2)
#define uPP_CHN_TWO                (0x00000001u << 2)

// 运行模式
#define uPP_ALL_RECEIVE            (0x00000000u << 0)
#define uPP_ALL_TRANSMIT           (0x00000001u << 0)
#define uPP_DUPLEX0                (0x00000002u << 0)         // 回环 B > A
#define uPP_DUPLEX1                (0x00000003u << 0)         // 回环 A > B

// uPP 接口、管脚、相位配置
#define uPP_PIN_PHASE_NORMAL       (0x00000000u)
#define uPP_PIN_PHASE_INVERT       (0x00000001u)
#define uPP_PIN_TRIS               (0x00002000u)

#define uPP_PIN_WAIT               (0x00000020u)
#define uPP_PIN_ENABLE             (0x00000010u)
#define uPP_PIN_START              (0x00000008u)

#define uPP_PIN_POLARITY_WAIT      (0x00000004u)
#define uPP_PIN_POLARITY_ENABLE    (0x00000002u)
#define uPP_PIN_POLARITY_START     (0x00000001u)

// uPP 门限配置
#define uPP_Threshold_64Bytes      (0x00000000u)
#define uPP_Threshold_128Bytes     (0x00000001u)
#define uPP_Threshold_256Bytes     (0x00000003u)

// uPP DMA 中断
#define uPP_INT_EOL                (0x00000010u)         // 行传输结束中断
#define uPP_INT_EOW                (0x00000008u)         // 窗口传输结束中断
#define uPP_INT_ERR                (0x00000004u)         // 内部总线错误中断
#define uPP_INT_UOR                (0x00000002u)         // 缓冲区欠载 / 溢出错误中断
#define uPP_INT_DPE                (0x00000001u)         // 编程 / 配置错误中断

// uPP DMA 配置
typedef struct
{
	// DMA 窗口地址高 29 位（低 3 位必须为 0 ，强制 64 位对齐）
	unsigned int *WindowAddress;
	// DMA行数 取值范围 0x001-0xFFFF
	unsigned short LineCount;
    // DMA 行字节数目高 15 位（第 0 位必须为 0 ，强制为偶数）取值范围 0x001-0x7FFF
	unsigned short ByteCount;
	// DMA 窗口行偏移地址高 13 位（低 3 位必须为 0 ，强制 64 位对齐） 取值范围 0x000-0x1FFF
	unsigned short LineOffsetAddress;
} uPPDMAConfig;

// uPP DMA 状态
typedef struct
{
	// DMA 当前窗口地址
	unsigned int WindowAddress; //0-FFFFFFFF
	// 当前行数
	unsigned short LineCount;   //0-FFFF
	// 当前字节数
	unsigned short ByteCount;   //0-FFFF
	// FIFO 使用状况
	unsigned char FIFO; //0-F 记录在任何事务期间达到的最大FIFO块占用率
	// DMA 等待中传输（当 DMA 通道空闲时才能够启动新的 DMA 传输）
	unsigned char PEND; //0：没有等待转移。可以编写通道 I 描述符 1：转移待定。通道 I 描述符可能不写入。
	// DMA 状态
	unsigned char DMA;  //0：DMA 处于非活动状态 1：DMA 处于活动状态
} uPPDMAStatus;

/****************************************************************************/
/*                                                                          */
/*              函数声明                                                    */
/*                                                                          */
/****************************************************************************/
void uPPPinMuxSetup(unsigned char OperatingMode);
void uPPClkConfig(unsigned int baseAddr, unsigned char channel, unsigned int Clk,
		            unsigned int moduleClk, unsigned char polarity);
void uPPEnable(unsigned int baseAdd);
void uPPDisable(unsigned int baseAdd);
void uPPPeripheralConfig(unsigned int baseAddr, unsigned int config);
void uPPDataFmtConfig(unsigned int baseAddr, unsigned char channel, unsigned int config);
void uPPChannelConfig(unsigned int baseAddr, unsigned int config);
void uPPPinConfig(unsigned int baseAddr, unsigned char channel, unsigned int config);
void uPPPinPolarityConfig(unsigned int baseAddr, unsigned char channel, unsigned int config);
void uPPIdleValueConfig(unsigned int baseAddr, unsigned char channel, unsigned int config);
void uPPThresholdConfig(unsigned int baseAddr, unsigned char channel, unsigned int config);
void uPPDLBConfig(unsigned int baseAddr, unsigned int config);

void uPPIntEnable(unsigned int baseAdd, unsigned char DMAchannel, unsigned int intFlags);
void uPPIntDisable(unsigned int baseAdd, unsigned char DMAchannel, unsigned int intFlags);
void uPPIntClear(unsigned int baseAdd, unsigned char DMAchannel, unsigned int intFlags);
unsigned int uPPIntStatus(unsigned int baseAdd, unsigned char DMAchannel);
void uPPEndOfInt(unsigned int baseAddr);

void uPPDMATransfer(unsigned int baseAdd, unsigned char DMAChannel, uPPDMAConfig *config);
uPPDMAStatus *uPPGetDMAStatus(unsigned int baseAdd, unsigned char channel);
void uPPReset(unsigned int baseAddr);

#endif
