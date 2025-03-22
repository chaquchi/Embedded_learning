#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	//初始化TIM2:是APB1总线的外设
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//重映射
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//使用复用推挽输出，
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;  //PA15
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//默认是低电平
	
	//选择时基单元的时钟
	TIM_InternalClockConfig(TIM2);//内部时钟——可以不写，因为默认使用内部时钟
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBasestructure;
	TIM_TimeBasestructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频
	TIM_TimeBasestructure.TIM_CounterMode = TIM_CounterMode_Up;//计数方式
	TIM_TimeBasestructure.TIM_Period = 100 - 1;//ARR自动重装器的值  决定定时时间的参数
	TIM_TimeBasestructure.TIM_Prescaler = 720 - 1;//PSC预分频器的值  决定定时时间的参数
	TIM_TimeBasestructure.TIM_RepetitionCounter = 0;//重复计数器的值——高级定时器才有，这里直接给
	TIM_TimeBaseInit(TIM2,&TIM_TimeBasestructure);//初始化时基单元
	
	//初始化输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//赋初始值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//输出比较极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出状态——输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;//设置CCR寄存器值
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	
	
	TIM_Cmd(TIM2,ENABLE);//启动定时器
}


void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}

