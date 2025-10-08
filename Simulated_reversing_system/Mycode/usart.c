#include "usart.h"

/*************************************** 重 定 向 ******************************************/
#include "stdio.h"

#pragma import(__use_no_semihosting)

// 标准库需要的支持函数
struct __FILE
{
	int handle;
};

FILE __stdout;
uint8_t data = 0;
uint8_t flag = 0;

//定义_sys_exit()以避免使用半主机模式
int _sys_exit(int x)
{
	label :goto label;

}
//重定义fputc函数 printf是个宏
int fputc(int ch,FILE *f)
{
	//通过串口发送数据
	USART_SendData(USART2,ch);
	//等待数据发送完毕
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	return ch;
}

/**********************************************************************/

/**********************************
引脚说明

PA9---USART1_TX(发送端)
PA10---USART1_RX(接收端)

PA2---USART2_TX(发送端)-->蓝牙
PA3---USART2_RX(接收端)-->蓝牙

***********************************/


void Usart1_Init(int myBaudRate)
{

	GPIO_InitTypeDef   GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	//串口时钟使能，GPIO时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//设置引脚复用器映射：调用GPIO_PinAFConfig函数
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	//GPIO初始化设置：设置模式为复用功能
	GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_9 |GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_AF;      //复用模式
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	
	//串口参数初始化：设置波特率，字长，奇偶校验等参数
	USART_InitStruct.USART_BaudRate            = myBaudRate;     			    //波特率
	USART_InitStruct.USART_Mode                = USART_Mode_Tx|USART_Mode_Rx;   //全双工
	USART_InitStruct.USART_Parity              = USART_Parity_No;			    //无奇偶校验位
	USART_InitStruct.USART_StopBits			   = USART_StopBits_1;			    //1位停止位
	USART_InitStruct.USART_WordLength		   = USART_WordLength_8b;		    //字长一个字节
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件控制流
	USART_Init(USART1,&USART_InitStruct);
	
	//开启中断并且初始化NVIC，使能中断（如果需要开启串口中断才需要这个步骤）
	NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;   //中断通道，中断通道在stm32f4xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         //响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       //通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	//配置为接收中断（表示有数据过来，CPU要中断进行接收）

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//使能串口
	USART_Cmd(USART1,ENABLE);
}
//蓝牙-->串口2
void BlueTeeth_Usart_Init(int myBaudRate)
{

	GPIO_InitTypeDef   GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	//串口时钟使能，GPIO时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	

	
	//GPIO初始化设置：设置模式为复用功能
	GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_2 |GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_AF;      //复用模式
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//设置引脚复用器映射：调用GPIO_PinAFConfig函数
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	USART_StructInit(&USART_InitStruct);
	
	//串口参数初始化：设置波特率，字长，奇偶校验等参数
	if(myBaudRate!=9600)
	{
		USART_InitStruct.USART_BaudRate            = myBaudRate;     			//波特率
	}
	
	USART_Init(USART2,&USART_InitStruct);
	

	USART_ClearFlag(USART2,USART_FLAG_TC);//清除中断标志位
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//开启接收中断标志位
	
	//开启中断并且初始化NVIC，使能中断（如果需要开启串口中断才需要这个步骤）
	NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;   //中断通道，中断通道在stm32f4xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         //响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       //通道使能
	NVIC_Init(&NVIC_InitStructure);
	
	
	//使能串口
	USART_Cmd(USART2,ENABLE);
}

//判断接收回来的字符串（串口2-->蓝牙）
void USART2_IRQHandler(void){

	//判断中断标志位是否为1
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		
		data=USART_ReceiveData(USART2);
		
		flag=1;	
		
	}
	 USART_ClearITPendingBit(USART2,USART_IT_RXNE);


}
