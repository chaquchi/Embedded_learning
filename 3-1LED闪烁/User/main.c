#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//时钟开启
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//模式控制——现在是推免
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//频率
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	while(1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);//控制PA0口，高电平
		Delay_ms(500);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		Delay_ms(500);
		
		
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);//Bit_RESET 控制
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_SET);
		Delay_ms(500);
		
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)0);
		Delay_ms(500);
		GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)1);
		Delay_ms(500);
	}
}
