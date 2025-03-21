#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Dht11.h"


int main()
{
	OLED_Init();
	Delay_ms(2000);
//	Dht11_Init();
	OLED_ShowString(1,1,":  .  ");
	OLED_ShowString(2,1,":  .  `C");
	
	
	
	
	while(1)
	{
		
		DHT11_RC_Data();
		
		OLED_ShowNum(1,2,DTH11_data[0],2);
		OLED_ShowNum(1,5,DTH11_data[1],2);
		
		OLED_ShowNum(2,2,DTH11_data[2],2);
		OLED_ShowNum(2,5,DTH11_data[3],2);
		
		Delay_ms(2000);
		
	}
}

