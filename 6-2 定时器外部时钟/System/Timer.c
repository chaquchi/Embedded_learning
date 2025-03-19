#include "stm32f10x.h"                  // Device header
//extern uint16_t Num; 方法1
void Timer_Init(void)
{
	//初始化TIM2:是APB1总线的外设
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//配置引脚
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	//选择时基单元的时钟
	TIM_ETRClockMode2Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00);//外部时钟
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBasestructure;
	TIM_TimeBasestructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频
	TIM_TimeBasestructure.TIM_CounterMode = TIM_CounterMode_Up;//计数方式
	TIM_TimeBasestructure.TIM_Period = 10 - 1;//ARR自动重装器的值  决定定时时间的参数
	TIM_TimeBasestructure.TIM_Prescaler = 1 - 1;//PSC预分频器的值  决定定时时间的参数
	TIM_TimeBasestructure.TIM_RepetitionCounter = 0;//重复计数器的值——高级定时器才有，这里直接给
	TIM_TimeBaseInit(TIM2,&TIM_TimeBasestructure);//初始化时基单元
	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//手动把更新中断标志位清除一下，就能避免初始化完就进入中断
	
	//使能中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//开起来更新中断到NVIC的通路
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//分组
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);//启动定时器
}

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);//获取计数器的值
}


//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)== SET )//判断是否是TIM2的中断
//	{
//		Num++;
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	}
//}
