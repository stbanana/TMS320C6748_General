//*****************************************************************************
//
// pinout.c - Function to configure the device pins on the EK-TM4C1294XL.
//
// Copyright (c) 2013-2014 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 2.1.0.12573 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <Includes.h>

//*****************************************************************************
//
//! \addtogroup pinout_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
//! Configures the device pins for the standard usages on the EK-TM4C1294XL.
//!
//! \param bEthernet is a boolean used to determine function of Ethernet pins.
//! If true Ethernet pins are  configured as Ethernet LEDs.  If false GPIO are
//! available for application use.
//! \param bUSB is a boolean used to determine function of USB pins. If true USB
//! pins are configured for USB use.  If false then USB pins are available for
//! application use as GPIO.
//!
//! This function enables the GPIO modules and configures the device pins for
//! the default, standard usages on the EK-TM4C1294XL.  Applications that
//! require alternate configurations of the device pins can either not call
//! this function and take full responsibility for configuring all the device
//! pins, or can reconfigure the required device pins after calling this
//! function.
//!
//! \return None.
//
//*****************************************************************************
void
PinoutSet(void)
{
    GPIOBank0Pin1PinMuxSetup(); //GPIO0[1]
    GPIOBank0Pin5PinMuxSetup(); //GPIO0[5]
    GPIOBank0Pin8PinMuxSetup(); //GPIO0[8]
    GPIOBank0Pin10PinMuxSetup(); //GPIO0[10]
    GPIOBank0Pin12PinMuxSetup(); //GPIO0[12]
    GPIOBank0Pin13PinMuxSetup(); //GPIO0[13]
    GPIOBank0Pin15PinMuxSetup(); //GPIO0[15]
    GPIOBank1Pin2PinMuxSetup();  //GPIO1[2]
    GPIOBank1Pin15PinMuxSetup(); //GPIO1[15]
    GPIOBank2Pin4PinMuxSetup(); //GPIO2[4]
    GPIOBank6Pin1PinMuxSetup(); //GPIO6[1]
    GPIOBank6Pin2PinMuxSetup(); //GPIO6[2]
    GPIOBank6Pin3PinMuxSetup(); //GPIO6[3]
    GPIOBank6Pin6PinMuxSetup(); //GPIO6[6]
    GPIOBank6Pin7PinMuxSetup(); //GPIO6[7]
    GPIOBank6Pin12PinMuxSetup(); //GPIO6[12]  LED_LIVE  核心板LED
    GPIOBank6Pin13PinMuxSetup(); //GPIO6[13]
    GPIOBank6Pin14PinMuxSetup(); //GPIO6[14]
//    GPIOBank0Pin0PinMuxSetup(); // LED_LIVE  D7  GPIO0[0]

    UARTPinMuxSetup(1, FALSE);//UART1系列pin口配置 禁用流控

    EMACPinMuxSetup(); // EMAC MII的pin口配置

    uPPPinMuxSetup(uPP_CHB_16BIT);  //uPP配置为B通道16bit的pin口配置
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
