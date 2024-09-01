#include "stm32f10x.h"                  // Device header

void PWM_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//开启时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//引脚重映射(p119)
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	
	//初始化GPIOA_Pin_1，2，3
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	TIM_InternalClockConfig(TIM2);//配置时钟源
	
	//初始化时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;				//计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;				//预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			//重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//初始化输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStructure;				//定义结构体变量
	TIM_OCStructInit(&TIM_OCInitStructure);				//结构体初始化
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //设置输出比较模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //设置输出比较极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //设置输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;  //设置CCR
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);	//初始化通道二，其引脚复用端口为PA1
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	/*
	PWM频率 = CK_PSC/(PSC+1)/(ARR+1)
	PWM占空比 = CRR/(ARR+1)
	PWMF分辨率 = 1/(ARR+1)*/
	
	TIM_Cmd(TIM2, ENABLE);//启动定时器
}

void PWM_SetCompare2(uint16_t Compare){
	TIM_SetCompare2(TIM2, Compare);
}
