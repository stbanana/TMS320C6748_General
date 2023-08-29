/*
 * Includes.h
 *
 *  Created on: 2023��8��23��
 *      Author: 19218
 */

#ifndef _INCLUDES_H_
#define _INCLUDES_H_

/*C����ͷ�ļ�*/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/*TIͨ������ͷ�ļ�*/
//ͷ�ļ�����ͨ�ã���������ͨ�ã��ڲ�ʵ�ֲ�ͬ
#include <gpio.h>
#include <uart.h>
#include <upp.h>
#include <dspcache.h>

/*MCUר��ͷ�ļ�*/
//�����ṩ
#include <psc.h>        //ʵ���ϼ��� #include <hw_psc_C6748.h>
#include <soc_C6748.h>
#include <lcdkC6748.h>
#include <interrupt.h>
#include <hw_types.h>
//��д�ṩ
#include <Macro.h>
#include <PinMuxSetup.h>
#include <uartstdio.h>
#include <uPPstdio.h>

/*uPPӦ��*/
#include <uPPRxTx.h>

/*�ɲ�������Ӧ��*/
#include <LEDDriver.h>

/*RTOS����*/
#include <TaskInterior.h>
#include <TestLed.h>

/*�����ʼ������*/
#include <InitCpu.h>
#include <pinout.h>

/*FreeRTOS*/
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"
#include "queue.h"



#endif /* 1_APP_INCLUDE_INCLUDES_H_ */
