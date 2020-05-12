#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED端口定义
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


void PWM_Init(void);//初始化		 				    
#endif
