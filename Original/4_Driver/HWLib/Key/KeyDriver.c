/*
 * KeyDriver.c
 *
 *  Created on: 2023年7月29日
 *      Author: skond
 */



#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#include "KeyDriver.h"


void InitKeyObject(CUSTOM_KEY* pd)
{
    pd->Key_Duration_state = 0;
    pd->state = KEY_STATE_SPAN_JUDGE;
    pd->value = cKEY_NONE;
}
/*******************************************************************************
Function name: sSampleSumCal
Description:一个按键消抖函数
*******************************************************************************/
uint8_t KeyObjectDriver(CUSTOM_KEY* pd, uint8_t key_state, uint32_t long_key_time)
{
    pd->value = cKEY_NONE;
    switch(pd->state)
    {
         case KEY_STATE_JUDGE:
             if(key_state)
             {
                 pd->state = KEY_STATE_DEBOUNCE;
                 pd->count = 0;
             }
         break;
         case KEY_STATE_DEBOUNCE:   //消抖状态
             if (key_state)
             {
                 pd->count++;
                 if (pd->count >= SINGLE_KEY_TIME)
                 {
                     pd->state = KEY_STATE_SPAN;
                 }
             }
             else
                 pd->state = KEY_STATE_JUDGE;
         break;
         case KEY_STATE_SPAN:
             if(!key_state)
             {
                 if(pd->count > (SINGLE_KEY_TIME-10))
                 {
                     pd->count -= 5;
                 }
                 else
                 {
                     pd->state = KEY_STATE_JUDGE;
                     pd->count = 0;
                 }
             }
             else
             {

                 if (pd->count >= (long_key_time-10)) //计数器值
                 {
                     pd->value = cKEY_SHORT;
                 }
                 else
                     pd->count++;

             }
         break;
         default:
             pd->state = KEY_STATE_JUDGE;
             break;
     }
    return pd->value;
}
