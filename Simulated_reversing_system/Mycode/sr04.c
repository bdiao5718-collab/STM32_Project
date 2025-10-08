#include "sr04.h"

/**********************************
����˵����
PC8--TRIG(�����ź�)������ͨ�����
PC9--ECHO(�����ź�)������ͨ���롣
***********************************/

void Sr04_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//ʱ�ӳ�ʼ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	//���ų�ʼ��
	//����2
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;		//���ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;		//�������
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;			//����
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_25MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	//����3
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	//���ö�ʱ��3
	TIM_TimeBaseInitStruct.TIM_Prescaler    =84-1; 				//84��Ƶ��84MHZ/84=1MHZ
	TIM_TimeBaseInitStruct.TIM_Period       =50000-1;				
	TIM_TimeBaseInitStruct.TIM_CounterMode  =TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;			//��������
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	//��ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3,DISABLE);
	
}
int Get_Sr04_Value(void)
{
	int temp=-3,distance,t=0;
	
	//PC8����͵�ƽ
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	delay_us(50);
	
	//PC8����ߵ�ƽ
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
	delay_us(10);
	
	//PC8����͵�ƽ
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	
	//���ö�ʱ����CNTΪ0
	TIM3->CNT=0;
	
	//PC9�ȴ��ߵ�ƽ�������ο������ɶ�����
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==0)
	{
		t++;
		delay_us(10);
		//�ȴ�2000usδ�иߵ�ƽ�����˳�
		// ԭ���ȴ�2000usδ�иߵ�ƽ�����˳�
		// �ģ��ȴ�10000us������������Ϊ�ȴ�ʱ����̵��µ�һֱ����ѭ������
		if (t >= 1000) 
            return -1; // ��ʱ���ش���
        
	}
	t=0;
	//ʹ�ܶ�ʱ����ʼ����
	TIM_Cmd(TIM3,ENABLE);
	//PC9�ȴ��͵�ƽ�������ο������ɶ�����
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==1)
	{
		t++;
		delay_us(10);
		//�ȴ�200msδ�е͵�ƽ�����˳�
		 if (t >= 20000) //�ȴ�200msδ�иߵ�ƽ�����˳�
        
            return -2;
        
	}
	//��ȡ��ʱ��CNTֵ���Ӷ��õ��ߵ�ƽ����ʱ��
	temp=TIM3->CNT;
	// �رն�ʱ��
	TIM_Cmd(TIM3,DISABLE);
	//ͨ����ʽ�������������������
	distance=temp/58;
	return distance;
	
	
}