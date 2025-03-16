#ifndef __COUNT_SENSOR_H
#define __COUNT_SENSOR_H

void CountSensor_Init(void);
//void EXTI15_10_IRQHandler(void) 中断函数不需要声明，自动执行
uint16_t CountSensor_Get(void);
#endif
