#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED�˿ڶ���
#define PWM0 PAout(0)	// 
#define PWM1 PAout(1)	// 
#define PWM2 PAout(2)	// 
#define PWM3 PAout(3)	// 
#define PWM4 PAout(4)	// 
#define PWM5 PAout(5)	// 
#define PWM6 PAout(6)	// 
#define PWM7 PAout(7)	// 
#define PWM8 PBout(0)	// 
#define PWM9 PBout(1)	// 
#define PWM10 PBout(2)// 
#define PWM11 PBout(10)// 

#define LED PAout(8)	// 


void PWM_Init(void);//��ʼ��		 				    
#endif
