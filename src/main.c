

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
    InitCpu();     // ��ʼ��оƬ
//    InitSysVar();  // ��ʼ������
//    InitSysPara(); // ��ʼ������

    xTaskCreate(TaskLED, (const portCHAR *)"TaskLED", configMINIMAL_STACK_SIZE, NULL, 4, NULL); // led��������

    xTaskCreate(TaskInterior, (const portCHAR *)"TaskInterior", configMINIMAL_STACK_SIZE, NULL, 3, NULL); // �ڲ�ͨ�Ŵ���

    vTaskStartScheduler();

	return 0;
}

