#include "sr04.h"

/**********************************
引脚说明：
PC8--TRIG(触发信号)，作普通输出；
PC9--ECHO(回响信号)，作普通输入。
***********************************/

void Sr04_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	//时钟初始化
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	//引脚初始化
	//引脚2
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;		//输出模式
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;		//推挽输出
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;			//上拉
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_25MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	//引脚3
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	//设置定时器3
	TIM_TimeBaseInitStruct.TIM_Prescaler    =84-1; 				//84分频，84MHZ/84=1MHZ
	TIM_TimeBaseInitStruct.TIM_Period       =50000-1;				
	TIM_TimeBaseInitStruct.TIM_CounterMode  =TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;			//分配因子
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	//不使能定时器
	TIM_Cmd(TIM3,DISABLE);
	
}
int Get_Sr04_Value(void)
{
	int temp=-3,distance,t=0;
	
	//PC8输出低电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	delay_us(50);
	
	//PC8输出高电平
	GPIO_SetBits(GPIOC,GPIO_Pin_8);
	delay_us(10);
	
	//PC8输出低电平
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	
	//设置定时器的CNT为0
	TIM3->CNT=0;
	
	//PC9等待高电平到来，参考按键松动代码
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==0)
	{
		t++;
		delay_us(10);
		//等待2000us未有高电平，则退出
		// 原：等待2000us未有高电平，则退出
		// 改：等待10000us则正常，鉴定为等待时间过短导致的一直卡在循环里面
		if (t >= 1000) 
            return -1; // 超时返回错误
        
	}
	t=0;
	//使能定时器开始计数
	TIM_Cmd(TIM3,ENABLE);
	//PC9等待低电平到来，参考按键松动代码
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==1)
	{
		t++;
		delay_us(10);
		//等待200ms未有低电平，则退出
		 if (t >= 20000) //等待200ms未有高电平，则退出
        
            return -2;
        
	}
	//获取定时器CNT值，从而得到高电平持续时间
	temp=TIM3->CNT;
	// 关闭定时器
	TIM_Cmd(TIM3,DISABLE);
	//通过公式结算出超声波测量距离
	distance=temp/58;
	return distance;
	
	
}