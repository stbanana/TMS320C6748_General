/*
 * Includes.h
 *
 *  Created on: 2023年8月23日
 *      Author: 19218
 */

#ifndef _INCLUDES_H_
#define _INCLUDES_H_

/*C语言头文件*/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/*TI通用驱动头文件*/
//头文件名称通用，函数名称通用，内部实现不同
#include <gpio.h>
#include <uart.h>
#include <upp.h>
#include <dspcache.h>

/*MCU专用头文件*/
//厂商提供
#include <psc.h>        //实际上即是 #include <hw_psc_C6748.h>
#include <soc_C6748.h>
#include <lcdkC6748.h>
#include <interrupt.h>
#include <hw_types.h>
//自写提供
#include <Macro.h>
#include <PinMuxSetup.h>
#include <uartstdio.h>
#include <uPPstdio.h>

/*uPP应用*/
#include <uPPRxTx.h>

/*可操作外设应用*/
#include <LEDDriver.h>

/*RTOS任务*/
#include <TaskInterior.h>
#include <TestLed.h>

/*程序初始化函数*/
#include <InitCpu.h>
#include <pinout.h>

/*FreeRTOS*/
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"
#include "queue.h"



#endif /* 1_APP_INCLUDE_INCLUDES_H_ */
