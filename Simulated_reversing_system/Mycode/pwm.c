#include "pwm.h"


/********************************

引脚说明


PA8-TIM1_CH1 (TIM1--APB1  16位 84MHz )

********************************/

void Pwm_PA8_Init(void)
{
    GPIO_InitTypeDef 		 GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef  		 TIM_OCInitStructure;
	//使能定时器TIM1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	// 使能GPIOA组时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* GPIOC Configuration: TIM1 CH1 (PA8) */
	GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_8 ;
	GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_AF;      //复用模式
	GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_25MHz;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	//  PA8映射TIM1功能
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
		
	TIM_TimeBaseInitStruct.TIM_Prescaler    =(84-1); 				//84分频，84MHZ/84=1MHZ
	TIM_TimeBaseInitStruct.TIM_Period       =(1000-1);				//在计数周期下，记1000个数，用时1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  =TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;			//分配因子
	//2.初始化定时器时钟，配置ARR,PSC	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);

	/* PWM1 Mode configuration: Channel1 */
	//通道初始化
	TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;         //PWM1模式
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //通道使能
	TIM_OCInitStructure.TIM_Pulse       = 0x00;                       //CCR值
	//TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_Low ;     //极性电平，这里设置为低电平
	TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High ;     //极性电平，这里设置为高电平
	//OC1--通道1
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	//使能预装载寄存器,OC1--通道1
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

 
    //使能自动重装载的预装载寄存器允许位
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	// 使能 TIM1 主输出（针对高级定时器）
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	
	//TIM1使能 
	TIM_Cmd(TIM1, ENABLE);

}	