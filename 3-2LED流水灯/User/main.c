#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//时钟开启
	
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//模式控制——现在是推免
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//频率
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	while(1)
	{
		GPIO_Write(GPIOA,~0x0000);//设置DR为~0x0001
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0001);//设置DR为~0x0001
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0002);
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0004);
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0008);
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0010);
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0020);
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0040);
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0080);
		Delay_ms(500);
	}
}
