#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//输入模式下没有用
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	//读取GPIO端口的功能
	if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1))//读取Pb的一号口的输入,按键按下为零
	{
		//刚按下按键，有抖动，所以需要延时函数
		Delay_ms(20);
		while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1));//一直按下
		Delay_ms(20);
		KeyNum = 1;
	}
	
	if(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11))//读取Pb的一号口的输入,按键按下为零
	{
		//刚按下按键，有抖动，所以需要延时函数
		Delay_ms(20);
		while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11));//一直按下
		Delay_ms(20);
		KeyNum = 2;
	}
	
	return KeyNum;
}
