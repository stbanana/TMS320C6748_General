/*
 * KeyDriver.h
 *
 *  Created on: 2023��7��29��
 *      Author: skond
 */

#ifndef _HWLIB_KEY_KEYDRIVER_H_
#define _HWLIB_KEY_KEYDRIVER_H_




#define cKEY_NONE       0       // δ��������
#define cKEY_SHORT      1       // ��������
#define KEY_STATE_JUDGE         0        //�ж����ް�������״̬
#define KEY_STATE_DEBOUNCE      1        //����״̬
#define KEY_STATE_SPAN          2        //�ж��ǰ�
#define SINGLE_KEY_TIME         50       //����

typedef enum
{//  0:δ�� 1:�̰� 2:����
    KEY_STATE_SPAN_JUDGE = 0,
    KEY_STATE_SPAN_SHORT,
    KEY_STATE_SPAN_LONG
}_KEY_STATE_ENUM;

typedef struct
{
    uint8_t Key_Duration_state;             //��ʶ����ʱ��    0:δ�� 1:�̰� 2:����
    uint8_t    state;                       //����״̬  ������ʹ�� KEY_STATE_JUDGE|KEY_STATE_DEBOUNCE|KEY_STATE_SPAN
    uint8_t    value;                       //��������ֵ �����з��� cKEY_NONE|cKEY_SHORT
    uint16_t   count;                       //����ʱ�������
}CUSTOM_KEY;

////�������Ĵ�����
//Output����
extern void InitKeyObject(CUSTOM_KEY* pd);  //��ʼ�������ṹ��

extern uint8_t KeyObjectDriver(CUSTOM_KEY* pd, uint8_t key_state, uint32_t long_key_time);//һ��������������

#endif /* 4_DRIVER_HWLIB_KEY_KEYDRIVER_H_ */
