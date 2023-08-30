

/**
 * main.c
 */

#include <Includes.h>

/****************************************************************************/
/*                      LOCAL FUNCTION PROTOTYPES                           */
/****************************************************************************/

/****************************************************************************/
/*                      GLOBAL VARIABLES                                    */
/****************************************************************************/


/****************************************************************************/
/*                      LOCAL FUNCTION DEFINITIONS                          */
/****************************************************************************/

int main(void)
{
    InitCpu();     // 初始化芯片
    InitSysVar();  // 初始化常量
    InitSysPara(); // 初始化变量

    xTaskCreate(TaskInterior, (const portCHAR *)"TaskInterior", configMINIMAL_STACK_SIZE, NULL, 3, NULL); // 内部通信处理

    xTaskCreate(TaskLED, (const portCHAR *)"TaskLED", configMINIMAL_STACK_SIZE, NULL, 4, NULL); // led触发任务

    vTaskStartScheduler();

	return 0;
}

