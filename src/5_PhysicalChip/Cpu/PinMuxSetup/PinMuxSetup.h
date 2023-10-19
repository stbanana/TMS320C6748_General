/*
 * PinMuxSetup.h
 *
 *  Created on: 2023年8月23日
 *      Author: 19218
 */

#ifndef _PINMUXSETUP_H_
#define _PINMUXSETUP_H_

extern void GPIOBank0Pin0PinMuxSetup(void);
extern void GPIOBank0Pin1PinMuxSetup(void);
extern void GPIOBank0Pin2PinMuxSetup(void);
extern void GPIOBank0Pin5PinMuxSetup(void);
extern void GPIOBank0Pin6PinMuxSetup(void);
extern void GPIOBank0Pin8PinMuxSetup(void);
extern void GPIOBank0Pin10PinMuxSetup(void);
extern void GPIOBank0Pin12PinMuxSetup(void);
extern void GPIOBank0Pin13PinMuxSetup(void);
extern void GPIOBank0Pin15PinMuxSetup(void);
extern void GPIOBank1Pin2PinMuxSetup(void);
extern void GPIOBank1Pin15PinMuxSetup(void);
extern void GPIOBank2Pin4PinMuxSetup(void);
extern void GPIOBank6Pin1PinMuxSetup(void);
extern void GPIOBank6Pin2PinMuxSetup(void);
extern void GPIOBank6Pin3PinMuxSetup(void);
extern void GPIOBank6Pin6PinMuxSetup(void);
extern void GPIOBank6Pin7PinMuxSetup(void);
extern void GPIOBank6Pin12PinMuxSetup(void);
extern void GPIOBank6Pin13PinMuxSetup(void);
extern void GPIOBank6Pin14PinMuxSetup(void);

extern void UARTPinMuxSetup(uint32_t ui32PortNum, uint32_t modemCtrlChoice);

extern void RTCPinMuxSetup(unsigned int alarmPinReqd);

extern void SPI0CSPinMuxSetup(unsigned int csPinNum);
extern void SPI1CSPinMuxSetup(unsigned int csPinNum);
extern void SPIPinMuxSetup(unsigned int instanceNum);

extern void I2CPinMuxSetup(unsigned int instanceNum);

extern void ConfigRasterDisplayEnable(void);

extern void EHRPWM0PinMuxSetup(void);
extern void EHRPWM1PinMuxSetup(void);

extern void ECAPPinMuxSetup(uint32_t ui32PortNum);

extern void McASPPinMuxSetup(void);

extern void EMACPinMuxSetup(void);
extern void EMACPinMuxRMIISetup(void);

//extern void LIDDPinMuxSetup(void); //暂无此函数，可在
extern void LCDPinMuxSetup(void);

extern void NANDPinMuxSetup(void);
extern void AD7606PinMuxSetup(void);
extern void EMIFAClkConfig(void);

extern void VPIFPinMuxSetup(void);

extern void RS485PinMuxSetup(void);



#endif /* 4_DRIVER_PINMUXSETUP_PINMUXSETUP_H_ */
