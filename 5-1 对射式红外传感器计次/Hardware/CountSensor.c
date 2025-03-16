#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启APB2的时钟，开启引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启AFIO的时钟，选择引脚
	//EXTI 、NVIC 两个外设，不用打开，一直打开的，NVIC是内核的，所以不用开
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入，默认高电平
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//连接CPIOB的14号引脚
	
	//配置EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;//指定要配置的中断线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;// 开启中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //模式  中断模式
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;//触发  上升沿触发
	EXTI_Init(&EXTI_InitStructure);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//放在模块中分组，要确保每个模块的分组一致，也可以放到主函数中分组，模块就不用分组了
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//指定通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)//中断函数名字,在启动文件中
{
	//判断是否是相应的中断进来了
	if(EXTI_GetITStatus(EXTI_Line14)==SET)//判断EXTI14的中断标志位是不是1
	{
		CountSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);//将中断标志位清除
	}
}

