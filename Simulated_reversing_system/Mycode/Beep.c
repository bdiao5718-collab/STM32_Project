#include "Beep.h"

/**************************************
����˵��:

������������PA8
PA8����ڸߵ�ƽ��1�����������죻
PA8����ڵ͵�ƽ��0�������������죻
**************************************/
void BEEP_Init(void)
{
	//�⺯��д��
	//ʱ�ӳ�ʼ��
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;  //ͨ�����ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP; //�������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;      //����5
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;   //�������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_25MHz; //ʱ��Ƶ��25MHz
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
/*	�Ĵ���д��
//ʹ��GPIOA��ʱ��
  RCC_AHB1ENR |=(0x01<<0);
	
//����Ϊ���ģʽ	
	GPIOA_MODER &= ~(0x01<<11);//11λ��0
	GPIOA_MODER |= (0x01<<10);//10λ��1
	
//�������
	GPIOA_OTYPER &= ~(0x01<<5);//5λ��0
	
//�����ٶȣ�50MHz
    GPIOA_OSPEEDR |= (0x01<<11);//11λ��1	
	GPIOA_OSPEEDR &= ~(0x01<<10);//10λ��0
	
	
//��������	
	GPIOA_PUPDR &= ~(0x01<<11);//11λ��0
	GPIOA_PUPDR |= (0x01<<10);//10λ��1
*/	
	
}