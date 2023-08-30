/*
 * KeyDriver.h
 *
 *  Created on: 2023年7月29日
 *      Author: skond
 */

#ifndef _HWLIB_KEY_KEYDRIVER_H_
#define _HWLIB_KEY_KEYDRIVER_H_




#define cKEY_NONE       0       // 未长按返回
#define cKEY_SHORT      1       // 长按返回
#define KEY_STATE_JUDGE         0        //判断有无按键按下状态
#define KEY_STATE_DEBOUNCE      1        //消抖状态
#define KEY_STATE_SPAN          2        //判断是按
#define SINGLE_KEY_TIME         50       //消抖

typedef enum
{//  0:未按 1:短按 2:长按
    KEY_STATE_SPAN_JUDGE = 0,
    KEY_STATE_SPAN_SHORT,
    KEY_STATE_SPAN_LONG
}_KEY_STATE_ENUM;

typedef struct
{
    uint8_t Key_Duration_state;             //标识按动时长    0:未按 1:短按 2:长按
    uint8_t    state;                       //按键状态  消抖中使用 KEY_STATE_JUDGE|KEY_STATE_DEBOUNCE|KEY_STATE_SPAN
    uint8_t    value;                       //按键返回值 消抖中返回 cKEY_NONE|cKEY_SHORT
    uint16_t   count;                       //按键时间计数器
}CUSTOM_KEY;

////物理按键的处理函数
//Output开关
extern void InitKeyObject(CUSTOM_KEY* pd);  //初始化按键结构体

extern uint8_t KeyObjectDriver(CUSTOM_KEY* pd, uint8_t key_state, uint32_t long_key_time);//一个按键消抖函数

#endif /* 4_DRIVER_HWLIB_KEY_KEYDRIVER_H_ */
