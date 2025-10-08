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
����˵��:

������������PA8
	PA8����ڸߵ�ƽ��1�����������죻
	PA8����ڵ͵�ƽ��0�������������죻

������PE4,KEY1������PE3

��������KEY0,ʵ�����Ӱ�ȫ���룻
��������KEY1,ʵ�ּ��ٰ�ȫ���룻

��ȫ����Ĭ�����ã�������
	��һ��������LEDȫ������ʾ��������ԶԶС�ڰ�ȫ���룻
	�ڶ�����һ��LED������ʾ��������С�ڰ�ȫ���룬���ȵ�һ����ľ������һЩ��
	������������LED����������ʾ����������ڰ�ȫ���룻

LED2��D2��������PA6
	PA6����ڵ͵�ƽ��0����������PA6����ڸߵ�ƽ��1��������
LED3��D3��������PA7
	PA7����ڵ͵�ƽ��0����������PA7����ڸߵ�ƽ��1��������
	


PC8--TRIG(�����ź�)������ͨ�����
PC9--ECHO(�����ź�)������ͨ���롣

**************************************/

extern uint8_t data;
extern uint8_t flag;
u8 count,rx_i=0;
u8 rx_flag=0;//ex_flag=1��ʾ�����������
u8 rx_buffer[32]={0};
u8 buffer[32]={0};
u16 SafeDistance =100;


int main(void)
{
	int re;
	uint8_t auto_flag=0;
	uint8_t sec =5;
	//����NVIC���飨һ����Ŀֻ������һ�Σ�
	//NVIC�ڶ����飺��ռ���ȼ���Χ��0~3 ��Ӧ���ȼ���0~3
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
				//�ֶ�
						case'1':
						re=Get_Sr04_Value();
						if(re<0)
						{
					// ���ʹ�����Ϣ������
              printf("��������:%dcm\r\n", re);
							continue;
						}
						printf("��ǰ����:%dcm\r\n", re);
						break;
						//�Զ�
						case '2':
							Tim2_IT_Init(sec,ENABLE);
							auto_flag=1;
							printf("�Զ�ģʽing����sec:%d\r\n",sec);
						break;
						//�����Զ�ģʽ����ʱ��
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
						//�����Զ�ģʽ����ʱ��
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
						//ȡ���Զ�
						case '0':
							printf("�˳��Զ�ģʽ\r\n");
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
