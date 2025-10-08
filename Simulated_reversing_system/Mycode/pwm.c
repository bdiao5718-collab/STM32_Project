#include "pwm.h"


/********************************

����˵��


PA8-TIM1_CH1 (TIM1--APB1  16λ 84MHz )

********************************/

void Pwm_PA8_Init(void)
{
    GPIO_InitTypeDef 		 GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef  		 TIM_OCInitStructure;
	//ʹ�ܶ�ʱ��TIM1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	// ʹ��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* GPIOC Configuration: TIM1 CH1 (PA8) */
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_8 ;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;      //����ģʽ
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	//  PA8ӳ��TIM1����
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
		
	TIM_TimeBaseInitStruct.TIM_Prescaler    =(84-1); 				//84��Ƶ��84MHZ/84=1MHZ
	TIM_TimeBaseInitStruct.TIM_Period       =(1000-1);				//�ڼ��������£���1000��������ʱ1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  =TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;			//��������
	//2.��ʼ����ʱ��ʱ�ӣ�����ARR,PSC	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);

	/* PWM1 Mode configuration: Channel1 */
	//ͨ����ʼ��
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;         //PWM1ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //ͨ��ʹ��
	TIM_OCInitStructure.TIM_Pulse       = 0x00;                       //CCRֵ
	//TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low ;     //���Ե�ƽ����������Ϊ�͵�ƽ
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High ;     //���Ե�ƽ����������Ϊ�ߵ�ƽ
	//OC1--ͨ��1
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	//ʹ��Ԥװ�ؼĴ���,OC1--ͨ��1
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

 
    //ʹ���Զ���װ�ص�Ԥװ�ؼĴ�������λ
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	// ʹ�� TIM1 ���������Ը߼���ʱ����
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	//TIM1ʹ�� 
	TIM_Cmd(TIM1, ENABLE);

}	