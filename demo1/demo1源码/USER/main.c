/***********************************************************
  项目名：12Dof9g机器狗
  作者：大冒险鸡 bilibiliUID:70338326
  当前版本描述：
  开发板：STM32f407
  机器狗可以实现前后左右平移，快速移动。采用mg90s9g舵机，骨骼采用3D打印，暂时未挂载传感器
  修改人：BlackBox114
  修改时间：2020.4.20
  修改内容：更新更详细的注释
  修改时间：2020.4.25
  修改内容：重设腿部参数，增强移动能力
  修改时间：2020.5.1
  修改内容：软PWM全部更换为硬PWM
  接线：暂无
 ***********************************************************/
 
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include <math.h>
#define Pi 3.1415926 
#define PY 4 
#define ZS 0 
#define SP 3 
#define HIGH 75 
u8 XH[12]={90,90,45,45,90,90,90,90,45,45,90,90};
//u8 XH[12]={90,90,90,90,90,90,90,90,90,90,90,90};
u16 a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11;
u8 flag1=0;//定时器计数20ms到了的标志

void WZ(int x1,int y1,int z1,int x2,int y2,int z2,int x3,int y3,int z3,int x4,int y4,int z4);
int LUJIN_X(u8 t);
int LUJIN_Y(u8 t);
int LUJIN_Z(u8 t);

int main(void)
{ 
	u8 t1=1,t2=6;//对角步态的标志
	int a=0;
	u8 mode=0;//模式
	u8 speed=6,speed2=3;//设置步距
	delay_init(100);                                                                                                                  	  //初始化延时函数
	PWM_Init();		        //初始化舵机控制端口
	uart_init(9600);
	TIM2_Int_Init(99,9);//10us
	delay_ms(2000);

	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			if(USART_RX_BUF[0]=='1')
			{
				mode=1;//前进											
			}else if(USART_RX_BUF[0]=='2')
			{
				mode=2;//后退						
			}else if(USART_RX_BUF[0]=='3')
			{
				mode=3;//左转						
			}else if(USART_RX_BUF[0]=='4')
			{
				mode=4;//右转									
			}else if(USART_RX_BUF[0]=='5')
			{
				mode=5;//LED						
			}else if(USART_RX_BUF[0]=='6')
			{
				mode=6;//横向左走									
			}else if(USART_RX_BUF[0]=='7')
			{
				mode=7;//横向右走									
			}else if(USART_RX_BUF[0]=='8')
			{
				mode=8;//扭转身躯								
			}else if(USART_RX_BUF[0]=='0')
			{
				mode=0;//停止
			}
			USART_RX_STA=0;
		}
		if(flag1==1)
		{
			flag1=0;
			if(mode==2)//后退
			{
				WZ(ZS+speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS+speed*LUJIN_X(t1),HIGH-4+LUJIN_Y(t1),0,ZS+speed*LUJIN_X(t2),HIGH-4+LUJIN_Y(t2),0,ZS+speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0);
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==1)//前进
			{
				WZ(ZS-speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS-speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0,ZS-speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS-speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0);			
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==8)//扭转身躯
			{
				for(a=0;a<30;a++)
				{
					WZ(70*cos((28-a)*Pi/180)-62,HIGH,34-70*sin((28-a)*Pi/180),62-70*cos((28+a)*Pi/180),HIGH,34-70*sin((28+a)*Pi/180),62-70*cos((28-a)*Pi/180),HIGH,70*sin((28-a)*Pi/180)-34,70*cos((28+a)*Pi/180)-62,HIGH,70*sin((28+a)*Pi/180)-34);
					delay_ms(20);
				}
				for(a=30;a>-30;a--)
				{
					WZ(70*cos((28-a)*Pi/180)-62,HIGH,34-70*sin((28-a)*Pi/180),62-70*cos((28+a)*Pi/180),HIGH,34-70*sin((28+a)*Pi/180),62-70*cos((28-a)*Pi/180),HIGH,70*sin((28-a)*Pi/180)-34,70*cos((28+a)*Pi/180)-62,HIGH,70*sin((28+a)*Pi/180)-34);
					delay_ms(20);
				}
				for(a=-30;a<0;a++)
				{
					WZ(70*cos((28-a)*Pi/180)-62,HIGH,34-70*sin((28-a)*Pi/180),62-70*cos((28+a)*Pi/180),HIGH,34-70*sin((28+a)*Pi/180),62-70*cos((28-a)*Pi/180),HIGH,70*sin((28-a)*Pi/180)-34,70*cos((28+a)*Pi/180)-62,HIGH,70*sin((28+a)*Pi/180)-34);
					delay_ms(20);
				}
			}else if(mode==4)//右转
			{
				WZ(ZS+speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS+speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0,ZS-speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS-speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0);	
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==3)//左转
			{
				WZ(ZS-speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS-speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0,ZS+speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS+speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0);	
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==5)//LED
			{
				LED=1;
				delay_ms(1);
			}else if(mode==6)//横向左走
			{
				WZ(0,HIGH+LUJIN_Y(t2),ZS+speed2*LUJIN_X(t2),0,HIGH-4+LUJIN_Y(t1),ZS+speed2*LUJIN_X(t1),0,HIGH-4+LUJIN_Y(t2),ZS+speed2*LUJIN_X(t2),0,HIGH+LUJIN_Y(t1),ZS+speed2*LUJIN_X(t1));
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==7)//横向右走
			{
				WZ(0,HIGH+LUJIN_Y(t2)-4,ZS-speed2*LUJIN_X(t2),0,HIGH+LUJIN_Y(t1)-4,ZS-speed2*LUJIN_X(t1),0,HIGH+LUJIN_Y(t2),ZS-speed2*LUJIN_X(t2),0,HIGH+LUJIN_Y(t1),ZS-speed2*LUJIN_X(t1));
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==0)
			{
				WZ(ZS+0,HIGH,0,ZS+0,HIGH,0,ZS+0,HIGH,0,ZS+0,HIGH,0);
				t1=1;t2=6;
				LED=0;
				delay_ms(1);
			}
		}
	}
}

//定时器2中断服务函数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
			a0++;a1++;a2++;a3++;a4++;a5++;
		a6++;a7++;a8++;a9++;a10++;a11++;
/*************舵机0**************/			
			if(a0==(60+180-XH[0]-5))
			{
				PWM0=0;
			}
/*************舵机1**************/				
			if(a1==(60+XH[1]-7))
			{
				PWM1=0;
			}
/*************舵机2**************/				
			if(a2==(60+XH[2]))
			{
				PWM2=0;
			}
/*************舵机3**************/				
		  if(a3==(60+180-XH[3]+9))
			{
				PWM3=0;
			}
/*************舵机4**************/				
			if(a4==(60+180-XH[4]))
			{
				PWM4=0;
			}
/*************舵机5**************/	
			if(a5==(60+XH[5]-6))
			{
				PWM5=0;
			}
/*************舵机6**************/			
			if(a6==(60+180-XH[6]-5))
			{
				PWM6=0;
			}
/*************舵机7**************/				
			if(a7==(60+XH[7]+7))
			{
				PWM7=0;
			}
/*************舵机8**************/				
			if(a8==(60+XH[8]-6))
			{
				PWM8=0;
			}
/*************舵机8**************/				
		  if(a9==(60+180-XH[9]+9))
			{
				PWM9=0;
			}
/*************舵机10**************/				
			if(a10==(60+180-XH[10]-0))
			{
				PWM10=0;
			}
/*************舵机11**************/	
			if(a11==(60+XH[11]+15))
			{
				PWM11=0;
			}						
			
			if(a0>=2000)
			{
				a0=0;
				PWM0=1;
				
				a1=0;
				PWM1=1;
				
				a2=0;
				PWM2=1;
				
				a3=0;
				PWM3=1;
				
				a4=0;
				PWM4=1;
				
				a5=0;
				PWM5=1;
				
				a6=0;
				PWM6=1;
				
				a7=0;
				PWM7=1;
				
				a8=0;
				PWM8=1;
				
				a9=0;
				PWM9=1;
				
				a10=0;
				PWM10=1;
				
				a11=0;
				PWM11=1;
				
				flag1=1;
			}
	}
	
}
 
void WZ(int x1,int y1,int z1,int x2,int y2,int z2,int x3,int y3,int z3,int x4,int y4,int z4)
{
	float bb,x,y,z;
	u8 a1,b1,c1;
	u8 a2,b2,c2;
	u8 a3,b3,c3;
	u8 a4,b4,c4;
	x=-x1;
	y=y1;
	z=z1;
	if(z>0)
	c1=atan(y/z)*180/Pi;
	if(z<0)
	c1=180+atan(y/z)*180/Pi;
	if(z==0)
	c1=90;
	bb=(3200-(sqrt(x*x+y*y+z*z)-8)*(sqrt(x*x+y*y+z*z)-8))/3200;
	b1=180-acos(bb)*180/Pi;
	if(x>0)
	a1=atan((y-8*cos(c1))/x)*180/Pi-b1/2;
	if(x<0)
	a1=180+atan((y-8*cos(c1))/x)*180/Pi-b1/2;
	if(x==0)
	a1=90-b1/2;
	XH[7]=b1;
	XH[9]=a1;
	XH[11]=c1;
	
	x=-x4;
	y=y4;
	z=-z4;
	if(z>0)
	c2=atan(y/z)*180/Pi;
	if(z<0)
	c2=180+atan(y/z)*180/Pi;
	if(z==0)
	c2=90;
	bb=(3200-(sqrt(x*x+y*y+z*z)-8)*(sqrt(x*x+y*y+z*z)-8))/3200;
	b2=180-acos(bb)*180/Pi;
	if(x>0)
	a2=atan((y-8*cos(c2))/x)*180/Pi-b2/2;
	if(x<0)
	a2=180+atan((y-8*cos(c2))/x)*180/Pi-b2/2;
	if(x==0)
	a2=90-b2/2;
	XH[6]=b2;
	XH[8]=a2;
	XH[10]=c2;
	
	x=x2;
	y=y2;
	z=z2;
	if(z>0)
	c3=atan(y/z)*180/Pi;
	if(z<0)
	c3=180+atan(y/z)*180/Pi;
	if(z==0)
	c3=90;
	bb=(3200-(sqrt(x*x+y*y+z*z)-8)*(sqrt(x*x+y*y+z*z)-8))/3200;
	b3=180-acos(bb)*180/Pi;
	if(x>0)
	a3=atan((y-8*cos(c3))/x)*180/Pi-b3/2;
	if(x<0)
	a3=180+atan((y-8*cos(c3))/x)*180/Pi-b3/2;
	if(x==0)
	a3=90-b3/2;
	XH[4]=b3;
	XH[2]=a3;
	XH[0]=c3;
	
	x=x3;
	y=y3;
	z=-z3;
	if(z>0)
	c4=atan(y/z)*180/Pi;
	if(z<0)
	c4=180+atan(y/z)*180/Pi;
	if(z==0)
	c4=90;
	bb=(3200-(sqrt(x*x+y*y+z*z)-8)*(sqrt(x*x+y*y+z*z)-8))/3200;
	b4=180-acos(bb)*180/Pi;
	if(x>0)
	a4=atan((y-8*cos(c4))/x)*180/Pi-b4/2;
	if(x<0)
	a4=180+atan((y-8*cos(c4))/x)*180/Pi-b4/2;
	if(x==0)
	a4=90-b4/2;
	XH[5]=b4;
	XH[3]=a4;
	XH[1]=c4;
}

int LUJIN_X(u8 t)
{
	int x;
	if(t>=1&&t<=4)
	{
		x=t;
	}else if(t>=5&&t<=8)
	{
		x=12-t*2;
	}else if(t>=9&&t<=12)//1,2,3,2,0,-2,-4,-3,-2-1,0
	{
		x=t-12;
	}
	return x;
}

int LUJIN_Y(u8 t)
{
	int y;
	if(t>=1&&t<=4)
	{
		y=0;
	}else if(t>=5&&t<=8)
	{
		y=-(t-4)*PY;
	}else if(t>=9&&t<=12)
	{
		y=0;
	}
	return y;
}

int LUJIN_Z(u8 t)
{
	int z;
	if(t<=5)
	{
		z=t;
	}else if(t>=6&&t<=11)
	{
		z=11-t;
	}else if(t>=12&&t<=17)
	{
		z=-t+12;
	}else if(t>=18&&t<=23)
	{
		z=t-23;
	}
	return z;
}
