#include "delay.h"

u32 my_us=21;			//��21MHZ�£�1us��21����
u32 my_ms=21000;		//��21MHZ�£�1ms��21000����


void Delay_Init(void)
{
//Systick��ʱ��ʱ��Դ HCLK/8=21MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	
}
//nusȡֵ��Χ��1~798915
void delay_us(int nus){
	u32 temp = 0x00;
	//��������ֵ�Ĵ���
	SysTick->LOAD =my_us*nus-1;
	//��ռ�����
	SysTick->VAL=0x00;
	//ʹ�ܶ�ʱ�� SysTick->LOAD��ֵװ�ص�SysTick->VAL����������ʼ����
	SysTick->CTRL |=(0X01<<0);
	//cpu�ȴ��������
	do{
		temp = SysTick->CTRL;
	//�ж϶�ʱ���Ƿ�ʹ��      �ж�temp��16Ϊ�Ƿ�Ϊ1	
	}while((temp&(0x01<<0))&&(!(temp&(0x01<<16))));
	//��ʹ�ܶ�ʱ��
	SysTick->CTRL &=~(0X01<<0);
}
//nmsȡֵ��Χ��1~798
void delay_ms(int nms){
	u32 temp = 0x00;
	//��������ֵ�Ĵ���
	SysTick->LOAD =my_ms*nms-1;
	//��ռ�����
	SysTick->VAL=0x00;
	//ʹ�ܶ�ʱ�� SysTick->LOAD��ֵװ�ص�SysTick->VAL����������ʼ����
	SysTick->CTRL |=(0X01<<0);
	//cpu�ȴ��������
	do{
		temp = SysTick->CTRL;
	//�ж϶�ʱ���Ƿ�ʹ��      �ж�temp��16Ϊ�Ƿ�Ϊ1	
	}while((temp&(0x01<<0))&&(!(temp&(0x01<<16))));
	//��ʹ�ܶ�ʱ��
	SysTick->CTRL &=~(0X01<<0);
}

void delay_s(int ns)
{
	int i;
		for(i=0;i<ns;i++)
		{
			delay_ms(500);
			delay_ms(500);
		}
}