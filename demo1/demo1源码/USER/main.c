/***********************************************************
  ��Ŀ����12Dof9g������
  ���ߣ���ð�ռ� bilibiliUID:70338326
  ��ǰ�汾������
  �����壺STM32f407
  ����������ʵ��ǰ������ƽ�ƣ������ƶ�������mg90s9g�������������3D��ӡ����ʱδ���ش�����
  �޸��ˣ�BlackBox114
  �޸�ʱ�䣺2020.4.20
  �޸����ݣ����¸���ϸ��ע��
  �޸�ʱ�䣺2020.4.25
  �޸����ݣ������Ȳ���������ǿ�ƶ�����
  �޸�ʱ�䣺2020.5.1
  �޸����ݣ���PWMȫ������ΪӲPWM
  ���ߣ�����
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
u8 flag1=0;//��ʱ������20ms���˵ı�־

void WZ(int x1,int y1,int z1,int x2,int y2,int z2,int x3,int y3,int z3,int x4,int y4,int z4);
int LUJIN_X(u8 t);
int LUJIN_Y(u8 t);
int LUJIN_Z(u8 t);

int main(void)
{ 
	u8 t1=1,t2=6;//�Խǲ�̬�ı�־
	int a=0;
	u8 mode=0;//ģʽ
	u8 speed=6,speed2=3;//���ò���
	delay_init(100);                                                                                                                  	  //��ʼ����ʱ����
	PWM_Init();		        //��ʼ��������ƶ˿�
	uart_init(9600);
	TIM2_Int_Init(99,9);//10us
	delay_ms(2000);

	while(1)
	{
		if(USART_RX_STA&0x8000)
		{
			if(USART_RX_BUF[0]=='1')
			{
				mode=1;//ǰ��											
			}else if(USART_RX_BUF[0]=='2')
			{
				mode=2;//����						
			}else if(USART_RX_BUF[0]=='3')
			{
				mode=3;//��ת						
			}else if(USART_RX_BUF[0]=='4')
			{
				mode=4;//��ת									
			}else if(USART_RX_BUF[0]=='5')
			{
				mode=5;//LED						
			}else if(USART_RX_BUF[0]=='6')
			{
				mode=6;//��������									
			}else if(USART_RX_BUF[0]=='7')
			{
				mode=7;//��������									
			}else if(USART_RX_BUF[0]=='8')
			{
				mode=8;//Ťת����								
			}else if(USART_RX_BUF[0]=='0')
			{
				mode=0;//ֹͣ
			}
			USART_RX_STA=0;
		}
		if(flag1==1)
		{
			flag1=0;
			if(mode==2)//����
			{
				WZ(ZS+speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS+speed*LUJIN_X(t1),HIGH-4+LUJIN_Y(t1),0,ZS+speed*LUJIN_X(t2),HIGH-4+LUJIN_Y(t2),0,ZS+speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0);
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==1)//ǰ��
			{
				WZ(ZS-speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS-speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0,ZS-speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS-speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0);			
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==8)//Ťת����
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
			}else if(mode==4)//��ת
			{
				WZ(ZS+speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS+speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0,ZS-speed*LUJIN_X(t2),HIGH+LUJIN_Y(t2),0,ZS-speed*LUJIN_X(t1),HIGH+LUJIN_Y(t1),0);	
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==3)//��ת
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
			}else if(mode==6)//��������
			{
				WZ(0,HIGH+LUJIN_Y(t2),ZS+speed2*LUJIN_X(t2),0,HIGH-4+LUJIN_Y(t1),ZS+speed2*LUJIN_X(t1),0,HIGH-4+LUJIN_Y(t2),ZS+speed2*LUJIN_X(t2),0,HIGH+LUJIN_Y(t1),ZS+speed2*LUJIN_X(t1));
				t1++;t2++;
				if(t1>=13)t1=1;
				if(t2>=13)t2=1;
				delay_ms(1);
			}else if(mode==7)//��������
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

//��ʱ��2�жϷ�����
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
			a0++;a1++;a2++;a3++;a4++;a5++;
		a6++;a7++;a8++;a9++;a10++;a11++;
/*************���0**************/			
			if(a0==(60+180-XH[0]-5))
			{
				PWM0=0;
			}
/*************���1**************/				
			if(a1==(60+XH[1]-7))
			{
				PWM1=0;
			}
/*************���2**************/				
			if(a2==(60+XH[2]))
			{
				PWM2=0;
			}
/*************���3**************/				
		  if(a3==(60+180-XH[3]+9))
			{
				PWM3=0;
			}
/*************���4**************/				
			if(a4==(60+180-XH[4]))
			{
				PWM4=0;
			}
/*************���5**************/	
			if(a5==(60+XH[5]-6))
			{
				PWM5=0;
			}
/*************���6**************/			
			if(a6==(60+180-XH[6]-5))
			{
				PWM6=0;
			}
/*************���7**************/				
			if(a7==(60+XH[7]+7))
			{
				PWM7=0;
			}
/*************���8**************/				
			if(a8==(60+XH[8]-6))
			{
				PWM8=0;
			}
/*************���8**************/				
		  if(a9==(60+180-XH[9]+9))
			{
				PWM9=0;
			}
/*************���10**************/				
			if(a10==(60+180-XH[10]-0))
			{
				PWM10=0;
			}
/*************���11**************/	
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
