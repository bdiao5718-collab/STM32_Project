#include "led.h"
void Led_Init(void)
{
	/******* �⺯��д��**************/
	GPIO_InitTypeDef  GPIO_InitStruct;
	//��ʱ��GPIOA��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//���ų�ʼ��
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
//	RCC->APB2ENR |=(1<<2); 	//��PAʱ��
//	GPIOA->CRH &=~(0xf<<0); //����
//	GPIOA->CRH |=(2<<0);	//���ģʽ������ٶ�2MHz
//	GPIOA->CRH &=~(3<<2);	//ͨ���������ģʽ
//	GPIOA->ODR |=~(1<<8);	//Ĭ����
	
	
}