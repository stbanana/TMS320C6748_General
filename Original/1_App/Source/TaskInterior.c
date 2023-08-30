/********************************************************************************


 **** Copyright (C), 2020, Shenzhen SKONDA ELECTRONIC LTD  ****


 ********************************************************************************
 * File Name     : TaskInterior.c
 * Author        : SKONDA
 * Date          : 2023-06-30
 * Version       : 1.0
********************************************************************************/
/**************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "Includes.h"
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//内部通信处理
void TaskInterior(void *pvParameters)
{
    while(1)
    {
        uPPRxTx();      //内部uPP处理
        vTaskDelay(1);
    }
}
