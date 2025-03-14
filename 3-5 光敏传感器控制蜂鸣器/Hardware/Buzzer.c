#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);//默认是低电平
	
	GPIO_SetBits(GPIOB,GPIO_Pin_12);//设置为高电平
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void Buzzer_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_12)==0)//读取输出寄存器中的A的一口（就是当前端口输出状态）
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);//设置1 不亮
	}else{
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);//设置0 亮
	}
}

