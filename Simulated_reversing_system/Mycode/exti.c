#include "exti.h"
#include "sr04.h"
#include "usart.h"
extern u16 SafeDistance;
/*****************************************************
引脚说明：
KEY0连接在PE4,KEY1连接在PE3

KEY0连接在PE4,选择下降沿触发，实现减少安全距离效果
KEY1连接在PE3,选择下降沿触发，实现增加安全距离效果


PE4--EXTI1
PE3--EXTI0


******************************************************/


void Exti_PE_Init(void)
{
   EXTI_InitTypeDef   EXTI_InitStructure;
   GPIO_InitTypeDef   GPIO_InitStructure;
   NVIC_InitTypeDef   NVIC_InitStructure;
 
   /* Enable GPIOE clock */
	//使能GPIOE组时钟
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
   /* Enable SYSCFG clock */
	//使能SYSCFG时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
   
/*************************** 引脚PE3 ********************************/
	
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3;
   GPIO_Init(GPIOE, &GPIO_InitStructure);
 
   //映射PE3到EXTI3
   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);

   EXTI_InitStructure.EXTI_Line = EXTI_Line3;                 //中断事件线3
   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;        //中断模式
   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    //下降沿触发，如果有下降沿到来，则执行中断服务
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;                  //中断线使能
   //配置NVIC
   EXTI_Init(&EXTI_InitStructure);
 
   
   NVIC_InitStructure.NVIC_IRQChannel                   = EXTI3_IRQn;   //中断通道，中断通道在stm32f4xx.h
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         //抢占优先级
   NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         //响应优先级
   NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       //通道使能
   NVIC_Init(&NVIC_InitStructure);

 /******************************** 引脚PE4 **************************************/
	
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
   GPIO_Init(GPIOE, &GPIO_InitStructure);
 
	//映射PE4到EXTI4
   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);
 
    
   EXTI_InitStructure.EXTI_Line = EXTI_Line4;                 //中断事件线4
   EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;        //中断模式
   EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;    //下降沿触发，如果有下降沿到来，则执行中断服务
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;                  //中断线使能
   //配置NVIC
   EXTI_Init(&EXTI_InitStructure);
 
   
   NVIC_InitStructure.NVIC_IRQChannel                   = EXTI4_IRQn;   //中断通道，中断通道在stm32f4xx.h
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         //抢占优先级
   NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         //响应优先级
   NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       //通道使能
   NVIC_Init(&NVIC_InitStructure);
    
  
  
   
  
}
//中断服务函数

//增加安全距离实现
void EXTI3_IRQHandler(void)
{
	//判断标志位是否置位
	if(EXTI_GetITStatus(EXTI_Line3)==SET)
	{
		//15ms用于过滤下降沿
		delay_ms(15);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)==0)
		{
			SafeDistance+=10;
			//按下按键，处理相应的事情
		}if(SafeDistance>=200)
		{
			SafeDistance=200;
		}
		printf("设置的安全距离：%dcm\r\n",SafeDistance);
		
	}
	//清除中断标志位
	EXTI_ClearITPendingBit(EXTI_Line3);
}
//减少安全距离实现
void EXTI4_IRQHandler(void)
{
	//判断标志位是否置位
	if(EXTI_GetITStatus(EXTI_Line4)==SET)
	{
		//15ms用于过滤下降沿
		delay_ms(15);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)
		{
			SafeDistance-=10;
			//按下按键，处理相应的事情
		}if(SafeDistance<=20)
		{
			SafeDistance=20;
		}
		printf("设置的安全距离：%dcm\r\n",SafeDistance);
		
	}
	//清除中断标志位
	EXTI_ClearITPendingBit(EXTI_Line4);
}
