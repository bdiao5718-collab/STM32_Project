#include "stm32f4xx.h"
#include "Beep.h"
#include "key.h"
#include "exti.h"
#include "led_pro.h"
#include "delay.h"
#include "tim.h"
#include "pwm.h"
#include "usart.h"
#include "string.h"
#include "sr04.h"
#include "sys.h"
/**************************************
引脚说明:

蜂鸣器连接在PA8
	PA8输出在高电平（1），蜂鸣器响；
	PA8输出在低电平（0），蜂鸣器不响；

连接在PE4,KEY1连接在PE3

按键按下KEY0,实现增加安全距离；
按键按下KEY1,实现减少安全距离；

安全距离默认设置，分三级
	第一级别：两个LED全亮，表示测量距离远远小于安全距离；
	第二级别：一个LED亮，表示测量距离小于安全距离，但比第一级别的距离更长一些；
	第三级别：两个LED都不亮，表示测量距离大于安全距离；

LED2（D2）连接在PA6
	PA6输出在低电平（0），灯亮；PA6输出在高电平（1），灯灭；
LED3（D3）连接在PA7
	PA7输出在低电平（0），灯亮；PA7输出在高电平（1），灯灭；
	


PC8--TRIG(触发信号)，作普通输出；
PC9--ECHO(回响信号)，作普通输入。

**************************************/

extern uint8_t data;
extern uint8_t flag;
u8 count,rx_i=0;
u8 rx_flag=0;//ex_flag=1表示数据输入完成
u8 rx_buffer[32]={0};
u8 buffer[32]={0};
u16 SafeDistance =100;


int main(void)
{
	int re;
	uint8_t auto_flag=0;
	uint8_t sec =5;
	//设置NVIC分组（一个项目只能配置一次）
	//NVIC第二分组：抢占优先级范围：0~3 响应优先级：0~3
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	Led_Init();
	Pwm_PA8_Init();
	Sr04_Init();
	Exti_PE_Init();
	BlueTeeth_Usart_Init(9600);
	Tim2_IT_Init(5,DISABLE);
	
	printf("welcome !\r\n");
	while(1)
	{
			if(flag)
		{
			
			switch(data)
			{
				//手动
						case'1':
						re=Get_Sr04_Value();
						if(re<0)
						{
					// 发送错误信息到蓝牙
              printf("测量错误:%dcm\r\n", re);
							continue;
						}
						printf("当前距离:%dcm\r\n", re);
						break;
						//自动
						case '2':
							Tim2_IT_Init(sec,ENABLE);
							auto_flag=1;
							printf("自动模式ing——sec:%d\r\n",sec);
						break;
						//增加自动模式触发时间
						case'A':
							if(auto_flag==1)
							{
								sec++;
								if(sec>10)
								{
									sec=10;
								}
								Tim2_IT_Init(sec,ENABLE);
							}
							break;
						//减少自动模式触发时间
						case 'S':
							if(auto_flag==1)
							{
								sec--;
								if(sec<2)
								{
									sec=2;
								}
								Tim2_IT_Init(sec,ENABLE);
							}
							break;
						//取消自动
						case '0':
							printf("退出自动模式\r\n");
							TIM_Cmd(TIM2,DISABLE);
							auto_flag=0;
							break;
						default:
							break;
					}
			flag=0;
				}	
		if(re<=SafeDistance *0.5)
			{
				PAout(6)=0;
				PAout(7)=0;
				TIM_SetCompare1(TIM1,500);
				
			}
			else if(re>SafeDistance *0.5&&re<=SafeDistance)
			{
				PAout(6)=0;
				PAout(7)=1;
				TIM_SetCompare1(TIM1,250);
			}
			else
			{
				PAout(6)=1;
				PAout(7)=1;
				TIM_SetCompare1(TIM1,0);
			}
			delay_ms(100);
		}
	
 return 0;
}
