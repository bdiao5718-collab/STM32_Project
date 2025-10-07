#include "main.h"

/*******************
引脚说明：
LED1<->PA8 
输出低电平->亮；
输出高电平->灭；
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
	// direction 控制方向，1表示递减，-1表示递增
	while(1)
	{
		//delay_ms(10);
		//GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		//LED_ON;
  

    for (i = 300; i != 0; i += direction) {
		Delay_Ms(10);
        TIM_SetCompare1(TIM1,i);
        
        // 当 i 等于 1 时，切换方向
        if (i == 1) {
            direction = -1;
        }
    }
	
	}
return 0;
}


