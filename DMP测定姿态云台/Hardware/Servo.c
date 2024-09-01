#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#define CTD 1920		//CCR to Degree

void Servo_Init(void){
	PWM_Init();
	
}

void ServoZ_SetAngle(float Angle){
	uint16_t CCR = Angle /180 * CTD + 500;
	PWM_SetCompare2(CCR);
}

void ServoY_SetAngle(float Angle){
	uint16_t CCR = Angle /180 * CTD + 500;
	TIM_SetCompare3(TIM2, CCR);
}

void ServoX_SetAngle(float Angle){
	uint16_t CCR = Angle /180 * CTD + 500;
	TIM_SetCompare4(TIM2, CCR);
}
