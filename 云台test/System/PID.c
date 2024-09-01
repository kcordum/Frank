#include "stm32f10x.h"                  // Device header
#include <cmath> // for fabs

//声明变量
 
//float ek = 0;                    //偏差e[k]
 
int pid(float ek) {
	//定义变量
	float Kp = 0.8;                  //PID调节的比例常数
	float Ti = 0.1;                  //PID调节的积分常数
	float T = 0.01;                  //采样周期
	float Td = 0.0002;               //PID调节的微分时间常数
	float a0;
	float a1;
	float a2;
 

	float ek1 = 0;                   //偏差e[k-1]
	float ek2 = 0;                   //偏差e[k-2]
	float uk = 0;                    //u[k]
	int uk1 = 0;                     //对uk四舍五入求整
	int adjust = 0;                 //最终输出的调整量
 
	//初始化PID系数
	a0 = Kp * (1 + T / Ti + Td / T);
	a1 = -Kp * (1 + 2 * Td / T);
	a2 = Kp * Td / T;
    if (fabs(ek) < 0.01) {  //使用适当的阈值
        adjust = 0;
    } else {
        uk = a0 * ek + a1 * ek1 + a2 * ek2;
        ek2 = ek1;
        ek1 = ek;
        uk1 = (int)round(uk); // 使用 round 函数来四舍五入
 
        adjust = uk1;
    }
    return adjust;
}
