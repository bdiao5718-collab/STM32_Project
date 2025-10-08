#include "exti.h"
#include "sr04.h"
#include "usart.h"
extern u16 SafeDistance;
/*****************************************************
����˵����
KEY0������PE4,KEY1������PE3

KEY0������PE4,ѡ���½��ش�����ʵ�ּ��ٰ�ȫ����Ч��
KEY1������PE3,ѡ���½��ش�����ʵ�����Ӱ�ȫ����Ч��


PE4--EXTI1
PE3--EXTI0


******************************************************/


void Exti_PE_Init(void)
{
   EXTI_InitTypeDef   EXTI_InitStructure;
   GPIO_InitTypeDef   GPIO_InitStructure;
   NVIC_InitTypeDef   NVIC_InitStructure;
 
   /* Enable GPIOE clock */
	//ʹ��GPIOE��ʱ��
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
   /* Enable SYSCFG clock */
	//ʹ��SYSCFGʱ��
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
   
/*************************** ����PE3 ********************************/
	
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
   GPIO_Init(GPIOE, &GPIO_InitStructure);
 
   //ӳ��PE3��EXTI3
   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);

   EXTI_InitStructure.EXTI_Line = EXTI_Line3;                 //�ж��¼���3
   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;        //�ж�ģʽ
   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    //�½��ش�����������½��ص�������ִ���жϷ���
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;                  //�ж���ʹ��
   //����NVIC
   EXTI_Init(&EXTI_InitStructure);
 
   
   NVIC_InitStructure.NVIC_IRQChannel                   = EXTI3_IRQn;   //�ж�ͨ�����ж�ͨ����stm32f4xx.h
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         //��ռ���ȼ�
   NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         //��Ӧ���ȼ�
   NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       //ͨ��ʹ��
   NVIC_Init(&NVIC_InitStructure);

 /******************************** ����PE4 **************************************/
	
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
   GPIO_Init(GPIOE, &GPIO_InitStructure);
 
	//ӳ��PE4��EXTI4
   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
 
    
   EXTI_InitStructure.EXTI_Line = EXTI_Line4;                 //�ж��¼���4
   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;        //�ж�ģʽ
   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    //�½��ش�����������½��ص�������ִ���жϷ���
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;                  //�ж���ʹ��
   //����NVIC
   EXTI_Init(&EXTI_InitStructure);
 
   
   NVIC_InitStructure.NVIC_IRQChannel                   = EXTI4_IRQn;   //�ж�ͨ�����ж�ͨ����stm32f4xx.h
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         //��ռ���ȼ�
   NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         //��Ӧ���ȼ�
   NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       //ͨ��ʹ��
   NVIC_Init(&NVIC_InitStructure);
    
  
  
   
  
}
//�жϷ�����

//���Ӱ�ȫ����ʵ��
void EXTI3_IRQHandler(void)
{
	//�жϱ�־λ�Ƿ���λ
	if(EXTI_GetITStatus(EXTI_Line3)==SET)
	{
		//15ms���ڹ����½���
		delay_ms(15);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)
		{
			SafeDistance+=10;
			//���°�����������Ӧ������
		}if(SafeDistance>=200)
		{
			SafeDistance=200;
		}
		printf("���õİ�ȫ���룺%dcm\r\n",SafeDistance);
		
	}
	//����жϱ�־λ
	EXTI_ClearITPendingBit(EXTI_Line3);
}
//���ٰ�ȫ����ʵ��
void EXTI4_IRQHandler(void)
{
	//�жϱ�־λ�Ƿ���λ
	if(EXTI_GetITStatus(EXTI_Line4)==SET)
	{
		//15ms���ڹ����½���
		delay_ms(15);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)
		{
			SafeDistance-=10;
			//���°�����������Ӧ������
		}if(SafeDistance<=20)
		{
			SafeDistance=20;
		}
		printf("���õİ�ȫ���룺%dcm\r\n",SafeDistance);
		
	}
	//����жϱ�־λ
	EXTI_ClearITPendingBit(EXTI_Line4);
}
