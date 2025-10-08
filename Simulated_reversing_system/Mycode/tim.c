#include "tim.h"
#include "sr04.h"

/**************************
定时器说明

TIM2挂APB1,定时器频率：84MHZ

TIM2:16位定时器

**************************/

void Tim2_IT_Init(uint32_t sec,FunctionalState status)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	//1.使能定时器时钟	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
	TIM_TimeBaseInitStruct.TIM_Prescaler    =8400-1; 				//84分频，84MHZ/8400=1kHZ
	TIM_TimeBaseInitStruct.TIM_Period       =(sec*10)-1;			//sec *10个数
	TIM_TimeBaseInitStruct.TIM_CounterMode  =TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;			//分配因子

	//2.初始化定时器时钟，配置ARR,PSC	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	
	//有坑，配置了中断立即触发中断服务函数
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;          //中断通道，中断通道在stm32f4xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         				//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         				//响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       				//通道使能
	//3.启用定时器中断，配置NVIC
	NVIC_Init(&NVIC_InitStructure);
	
	
	
	//5.使能定时器
	TIM_Cmd(TIM2,status);
}
void Tim2_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef         NVIC_InitStructure;
	
	//1.使能定时器时钟	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
	TIM_TimeBaseInitStruct.TIM_Prescaler    =(84-1); 				//84分频，84MHZ/84=1MHZ
	TIM_TimeBaseInitStruct.TIM_Period       =(50000-1);				//在计数周期下，即1MHZ=1/1000000s,记1000个数，用时1ms
	TIM_TimeBaseInitStruct.TIM_CounterMode  =TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;			//分配因子
	

	//2.初始化定时器时钟，配置ARR,PSC	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);


	
	//5.使能定时器
	TIM_Cmd(TIM2,DISABLE);
}

int counts=0;
//中断服务函数
void TIM2_IRQHandler(void){
	volatile int auto_re=-1;
	
	//判断中断标志位是否为1
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		counts++;
		if(counts==1000)
		{
			auto_re=Get_Sr04_Value();
			  if(auto_re > 0) {
            printf("自动测量距离:%dcm\r\n", auto_re);
        } else {
            printf("自动测量错误:%d\r\n", auto_re);
        }
				counts=0;
		}
		
	//清空中断标志位
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}

}
