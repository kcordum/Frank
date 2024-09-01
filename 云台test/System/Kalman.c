#include "stm32f10x.h"                  // Device header
#include "stddef.h"

typedef unsigned char Kalman_U8;
typedef unsigned short int Kalman_U16;
typedef unsigned long int Kalman_U32;
typedef float Kalman_F8;

typedef enum
{
	KalmanResult_NULL,
	KalmanResult_OK,
	KalmanResult_ERROR,
}
KalmanResult_Typedef;

typedef struct
{
	Kalman_F8 LastP;		//上次协方差
	Kalman_F8 NowP;			//当前协方差
	Kalman_F8 X_hat;		//卡尔曼滤波计算值
	Kalman_F8 Kg;			//卡尔曼增益系数
	Kalman_F8 Q;			//过程噪声
	Kalman_F8 R;			//测量噪声
}
Kalman_Typedef;

/*
 * 功能：初始化
 * 输入：p_Kalman：卡尔曼结果体指针
 * 		KalmanParameter：卡尔曼初始化参数
 * 输出：KalmanResult_ERROR：卡尔曼结果体指针无效
 *		KalmanResult_OK：初始化完成
 */
KalmanResult_Typedef KalmanInit(Kalman_Typedef* p_Kalman, Kalman_Typedef KalmanParameter)
{
	if(p_Kalman == NULL)
	{
		return KalmanResult_ERROR;
	}
	else
	{
		*p_Kalman = KalmanParameter;
 
		return KalmanResult_OK;
	}
}
 

/*
 * 功能：一阶卡尔曼滤波
 * 输入：p_Kalman：卡尔曼结果体指针
 * 输出：KalmanResult_ERROR：卡尔曼结果体指针无效
 *		KalmanResult_OK：计算完成
 * 备注：p_Kalman->X_hat存放最新的最优值
 */
KalmanResult_Typedef KalmanFilter(Kalman_Typedef* p_Kalman, Kalman_F8 Value)
{
	if(p_Kalman == NULL)
	{
		return KalmanResult_ERROR;
	}
	else
	{
		p_Kalman->NowP = p_Kalman->LastP + p_Kalman->Q;
		p_Kalman->Kg = p_Kalman->NowP / (p_Kalman->NowP + p_Kalman->R);
		p_Kalman->X_hat = p_Kalman->Kg * (Value - p_Kalman->X_hat) + p_Kalman->X_hat;
		p_Kalman->LastP = (1 - p_Kalman->Kg) * p_Kalman->NowP;
 
		return KalmanResult_OK;
	}
}
