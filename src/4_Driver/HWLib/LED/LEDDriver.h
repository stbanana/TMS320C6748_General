/*
 * LEDDriver.h
 *
 *  Created on: 2023Äê8ÔÂ1ÈÕ
 *      Author: skond
 */

#ifndef _LED_LEDDRIVER_H_
#define _LED_LEDDRIVER_H_


//#define   LifeLedOff()              GPIOPinWrite(SOC_GPIO_0_REGS, GPIO_BANK_BASE_0+GPIO_PIN_ADDTL_0, GPIO_PIN_LOW);\
//                                    GPIOPinWrite(SOC_GPIO_0_REGS, GPIO_BANK_BASE_6+GPIO_PIN_ADDTL_12, GPIO_PIN_LOW)
//#define   LifeLedOn()               GPIOPinWrite(SOC_GPIO_0_REGS, GPIO_BANK_BASE_0+GPIO_PIN_ADDTL_0, GPIO_PIN_HIGH);\
//                                    GPIOPinWrite(SOC_GPIO_0_REGS, GPIO_BANK_BASE_6+GPIO_PIN_ADDTL_12, GPIO_PIN_HIGH)

#define   LifeLedOff()              GPIOPinWrite(SOC_GPIO_0_REGS, GPIO_BANK_BASE_6+GPIO_PIN_ADDTL_12, GPIO_PIN_LOW)
#define   LifeLedOn()               GPIOPinWrite(SOC_GPIO_0_REGS, GPIO_BANK_BASE_6+GPIO_PIN_ADDTL_12, GPIO_PIN_HIGH)
#define   LifeLedQ()                GPIOPinRead(SOC_GPIO_0_REGS, GPIO_BANK_BASE_6+GPIO_PIN_ADDTL_12)


extern void LifeLedSwitch(void);

#endif /* 4_DRIVER_HWLIB_LED_LEDDRIVER_H_ */
