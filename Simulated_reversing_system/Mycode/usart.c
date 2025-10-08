#include "usart.h"

/*************************************** �� �� �� ******************************************/
#include "stdio.h"

#pragma import(__use_no_semihosting)

// ��׼����Ҫ��֧�ֺ���
struct __FILE
{
	int handle;
};

FILE __stdout;
uint8_t data = 0;
uint8_t flag = 0;

//����_sys_exit()�Ա���ʹ�ð�����ģʽ
int _sys_exit(int x)
{
	label :goto label;

}
//�ض���fputc���� printf�Ǹ���
int fputc(int ch,FILE *f)
{
	//ͨ�����ڷ�������
	USART_SendData(USART2,ch);
	//�ȴ����ݷ������
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	return ch;
}

/**********************************************************************/

/**********************************
����˵��

PA9---USART1_TX(���Ͷ�)
PA10---USART1_RX(���ն�)

PA2---USART2_TX(���Ͷ�)-->����
PA3---USART2_RX(���ն�)-->����

***********************************/


void Usart1_Init(int myBaudRate)
{

	GPIO_InitTypeDef   GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	//����ʱ��ʹ�ܣ�GPIOʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//�������Ÿ�����ӳ�䣺����GPIO_PinAFConfig����
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	//GPIO��ʼ�����ã�����ģʽΪ���ù���
	GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_9 |GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_AF;      //����ģʽ
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_25MHz;
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	
	//���ڲ�����ʼ�������ò����ʣ��ֳ�����żУ��Ȳ���
	USART_InitStruct.USART_BaudRate            = myBaudRate;     			    //������
	USART_InitStruct.USART_Mode                = USART_Mode_Tx|USART_Mode_Rx;   //ȫ˫��
	USART_InitStruct.USART_Parity              = USART_Parity_No;			    //����żУ��λ
	USART_InitStruct.USART_StopBits			   = USART_StopBits_1;			    //1λֹͣλ
	USART_InitStruct.USART_WordLength		   = USART_WordLength_8b;		    //�ֳ�һ���ֽ�
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_Init(USART1,&USART_InitStruct);
	
	//�����жϲ��ҳ�ʼ��NVIC��ʹ���жϣ������Ҫ���������жϲ���Ҫ������裩
	NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;   //�ж�ͨ�����ж�ͨ����stm32f4xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       //ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	//����Ϊ�����жϣ���ʾ�����ݹ�����CPUҪ�жϽ��н��գ�

	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//ʹ�ܴ���
	USART_Cmd(USART1,ENABLE);
}
//����-->����2
void BlueTeeth_Usart_Init(int myBaudRate)
{

	GPIO_InitTypeDef   GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	
	//����ʱ��ʹ�ܣ�GPIOʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	

	
	//GPIO��ʼ�����ã�����ģʽΪ���ù���
	GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_2 |GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_AF;      //����ģʽ
	GPIO_InitStruct.GPIO_Speed  = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//�������Ÿ�����ӳ�䣺����GPIO_PinAFConfig����
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	USART_StructInit(&USART_InitStruct);
	
	//���ڲ�����ʼ�������ò����ʣ��ֳ�����żУ��Ȳ���
	if(myBaudRate!=9600)
	{
		USART_InitStruct.USART_BaudRate            = myBaudRate;     			//������
	}
	
	USART_Init(USART2,&USART_InitStruct);
	

	USART_ClearFlag(USART2,USART_FLAG_TC);//����жϱ�־λ
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//���������жϱ�־λ
	
	//�����жϲ��ҳ�ʼ��NVIC��ʹ���жϣ������Ҫ���������жϲ���Ҫ������裩
	NVIC_InitStructure.NVIC_IRQChannel                   = USART2_IRQn;   //�ж�ͨ�����ж�ͨ����stm32f4xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;         //��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x01;         //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;       //ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	
	//ʹ�ܴ���
	USART_Cmd(USART2,ENABLE);
}

//�жϽ��ջ������ַ���������2-->������
void USART2_IRQHandler(void){

	//�ж��жϱ�־λ�Ƿ�Ϊ1
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
	{
		
		data=USART_ReceiveData(USART2);
		
		flag=1;	
		
	}
	 USART_ClearITPendingBit(USART2,USART_IT_RXNE);


}
