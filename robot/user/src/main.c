#include "main.h"

/*******************
����˵����
LED1<->PA8 
����͵�ƽ->����
����ߵ�ƽ->��
*******************/

//void delay_ms(int count)
//{
//	for(int i=0;i<count;i++)
//	for(int j=0;j<30000;j++);
//}
int main(void)
{
	
	//Led_Init();
	PWM_PA8_Init();
	u16 i;
    unsigned int direction = 1;  
	// direction ���Ʒ���1��ʾ�ݼ���-1��ʾ����
	while(1)
	{
		//delay_ms(10);
		//GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		//LED_ON;
  

    for (i = 300; i != 0; i += direction) {
		Delay_Ms(10);
        TIM_SetCompare1(TIM1,i);
        
        // �� i ���� 1 ʱ���л�����
        if (i == 1) {
            direction = -1;
        }
    }
	
	}
return 0;
}


