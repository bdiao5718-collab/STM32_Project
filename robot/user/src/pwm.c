#include "pwm.h"

/**********************
PA8--TIM1_CH1:72MHz 16位
***********************/
void PWM_PA8_Init(void)
{
	GPIO_InitTypeDef   		 GPIO_InitStruct;
	TIM_OCInitTypeDef  		 TIM_OCInitStruct;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	//使能定时器1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	
	//使能GPIOA组时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//引脚初始化
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	TIM_InternalClockConfig(TIM1);
	
	//初始化定时器时钟，配置ARR,RSC
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720-1;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;    //分配因子
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
	
	
	
	//PA8映射TM1功能
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
	
	//通道初始化
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_Pulse=050;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High; 
	
	
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);

	
	//使能预装载寄存器,OC1--通道1
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	//使能自动重装载的预装载寄存器允许位
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	
	
	//TIM1使能 
	TIM_Cmd(TIM1, ENABLE);
	
}