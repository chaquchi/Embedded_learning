#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include <stdio.h>
#include <stdarg.h>


uint8_t DTH11_data[4];//一次穿4个字节




void ST_out(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitTypeStructure;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitTypeStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitTypeStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitTypeStructure);
}


void ST_in(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitTypeStructure;
	GPIO_InitTypeStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_InitTypeStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitTypeStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitTypeStructure);
	
}


void Dht11_Init(void)
{
	ST_out();
	
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
//	
//	Delay_us(30);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	
	Delay_ms(20);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	Delay_us(30);
	
	ST_in();
}

//获取一个字节

uint8_t DHT11_RC_Byte(void)
{
	uint8_t i,data = 0;
	uint16_t time = 1000;
	for (i = 0; i < 8;++i)
	{
		
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0&&time--)//等待从低电平到高电平
		{
			if(time==0)
			{
				OLED_ShowString(3,5,"Byte_Error");
				return 0;
			}
		}
		Delay_us(40);
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 1)
		{
			data|=(1<<(7-i));
//			OLED_ShowString(3,5,"Byte_1");
		}
		
		time = 1000; // 重置超时
        while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 1 && time--); // 等待高电平结束
		
		
		
	}
	
	return data;
	
}

//获取数据


void DHT11_RC_Data(void)
{
	uint8_t R_H,R_L,T_H,T_L ,CHCK;
	uint32_t timeout = 2;
	
	
	Dht11_Init();
	
//	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0)//判断DHT11是否拉低点平，响应
	{
//		OLED_ShowString(3,1,"ok1");
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 0 && timeout--)//等待80us的响应
		{
			if(timeout == 0) {
            OLED_ShowString(3, 5, "Timeout");
            return; // 超时退出
			}
			Delay_us(83);
		}
		
//		OLED_ShowString(3,5,"ok2");
		timeout = 1000;
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) == 1&& timeout)//等待电平拉高后的数据传输
		{
			if(--timeout == 0) {
            OLED_ShowString(3, 5, "Error1");
            return;
			}
			Delay_us(1);
		}
//		OLED_ShowString(3, 5, "Error2");
		R_H = DHT11_RC_Byte();
		R_L = DHT11_RC_Byte();
		T_H = DHT11_RC_Byte();
		T_L = DHT11_RC_Byte();
		CHCK = DHT11_RC_Byte();
		
	}
	
	//校验
	if((R_H + R_L + T_H + T_L ) == CHCK)
	{
		DTH11_data[0] = R_H; // 湿度高字节
        DTH11_data[1] = R_L; // 湿度低字节
        DTH11_data[2] = T_H; // 温度高字节
        DTH11_data[3] = T_L; // 温度低字节
		OLED_ShowString(3,1,"ok3");
		
	}
	else
	{
		OLED_ShowString(3,1,"Checksum Err");
    // 输出原始数据辅助调试
		OLED_ShowNum(1, 1, R_H/10, 2);  // 显示原始湿度高字节
		OLED_ShowNum(1, 4, R_L, 2);  // 显示原始湿度低字节
		OLED_ShowNum(2, 1, T_H, 2);  // 显示原始温度高字节
		OLED_ShowNum(2, 4, T_L, 2);  // 显示原始温度低字节
		
		OLED_ShowNum(1, 7, (R_H + R_L + T_H + T_L), 2);  
		OLED_ShowNum(2, 7, (CHCK), 2);  
		return;
		
	}
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	Delay_us(50);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
	OLED_ShowString(3,1,"ok4");
	
	

}





