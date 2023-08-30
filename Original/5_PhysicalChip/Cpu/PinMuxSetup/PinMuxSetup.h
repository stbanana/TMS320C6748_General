/*
 * PinMuxSetup.h
 *
 *  Created on: 2023Äê8ÔÂ23ÈÕ
 *      Author: 19218
 */

#ifndef _PINMUXSETUP_H_
#define _PINMUXSETUP_H_

extern void UARTPinMuxSetup(unsigned int instanceNum,
                            unsigned int modemCtrlChoice);
extern void RTCPinMuxSetup(unsigned int alarmPinReqd);
extern void SPI0CSPinMuxSetup(unsigned int csPinNum);
extern void SPI1CSPinMuxSetup(unsigned int csPinNum);
extern void I2CPinMuxSetup(unsigned int instanceNum);
extern void SPIPinMuxSetup(unsigned int instanceNum);
extern void ConfigRasterDisplayEnable(void);
extern void GPIOBank0Pin0PinMuxSetup(void);
extern void GPIOBank0Pin1PinMuxSetup(void);
extern void GPIOBank0Pin2PinMuxSetup(void);
extern void GPIOBank0Pin5PinMuxSetup(void);
extern void GPIOBank0Pin6PinMuxSetup(void);
extern void GPIOBank6Pin1PinMuxSetup(void);
extern void GPIOBank6Pin12PinMuxSetup(void);
extern void GPIOBank6Pin13PinMuxSetup(void);
extern void EHRPWM0PinMuxSetup(void);
extern void EHRPWM1PinMuxSetup(void);
extern void ECAPPinMuxSetup(unsigned char n);
extern void LIDDDisplayEnable(void);
extern void McASPPinMuxSetup(void);
extern void EMACPinMuxSetup(void);
extern void LIDDPinMuxSetup(void);
extern void LCDPinMuxSetup(void);
extern void NANDPinMuxSetup(void);
extern void EMIFAClkConfig(void);
extern void VPIFPinMuxSetup(void);
extern void RS485PinMuxSetup(void);
extern void AD7606PinMuxSetup(void);
extern void EMACPinMuxRMIISetup(void);

#endif /* 4_DRIVER_PINMUXSETUP_PINMUXSETUP_H_ */
