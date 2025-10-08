#include "tim.h"
#include "sr04.h"

/**************************
��ʱ��˵��

TIM2��APB1,��ʱ��Ƶ�ʣ�84MHZ

TIM2:16λ��ʱ��

**************************/

void Tim2_IT_Init(uint32_t sec,FunctionalState status)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	//1.ʹ�ܶ�ʱ��ʱ��	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
	TIM_TimeBaseInitStruct.TIM_Prescaler    =8400-1; 				//84��Ƶ��84MHZ/8400=1kHZ
	TIM_TimeBaseInitStruct.TIM_Period       =(sec*10)-1;			//sec *10����
	TIM_TimeBaseInitStruct.TIM_CounterMode  =TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;			//��������

	//2.��ʼ����ʱ��ʱ�ӣ�����ARR,PSC	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
	//�пӣ��������ж����������жϷ�����
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;          //�ж�ͨ�����ж�ͨ����stm32f4xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         				//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         				//��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       				//ͨ��ʹ��
	//3.���ö�ʱ���жϣ�����NVIC
	NVIC_Init(&NVIC_InitStructure);
	
	
	
	//5.ʹ�ܶ�ʱ��
	TIM_Cmd(TIM2,status);
}
void Tim2_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	//1.ʹ�ܶ�ʱ��ʱ��	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
	TIM_TimeBaseInitStruct.TIM_Prescaler    =(84-1); 				//84��Ƶ��84MHZ/84=1MHZ
	TIM_TimeBaseInitStruct.TIM_Period       =(50000-1);				//�ڼ��������£���1MHZ=1/1000000s,��1000��������ʱ1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  =TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;			//��������
	

	//2.��ʼ����ʱ��ʱ�ӣ�����ARR,PSC	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);


	
	//5.ʹ�ܶ�ʱ��
	TIM_Cmd(TIM2,DISABLE);
}

int counts=0;
//�жϷ�����
void TIM2_IRQHandler(void){
	volatile int auto_re=-1;
	
	//�ж��жϱ�־λ�Ƿ�Ϊ1
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		counts++;
		if(counts==1000)
		{
			auto_re=Get_Sr04_Value();
			  if(auto_re > 0) {
            printf("�Զ���������:%dcm\r\n", auto_re);
        } else {
            printf("�Զ���������:%d\r\n", auto_re);
        }
				counts=0;
		}
		
	//����жϱ�־λ
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}

}
