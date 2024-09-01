#ifndef __KALMAN_H
#define __KALMAN_H

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


 //初始化
KalmanResult_Typedef KalmanInit(Kalman_Typedef* p_Kalman, Kalman_Typedef KalmanParameter);
 

// 一阶卡尔曼滤波
 KalmanResult_Typedef KalmanFilter(Kalman_Typedef* p_Kalman, Kalman_F8 Value);

#endif
