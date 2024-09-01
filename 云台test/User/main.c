#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "Servo.h"
#include "PID.h"
#include "Kalman.h"

float Pitch,Roll,Yaw;					//姿态角
float AngleX, AngleY, AngleZ;			//XYZ轴旋转角
float ek = 0;                    		//偏差e[k]
int16_t ax,ay,az,gx,gy,gz;				//MPU6050数据读取			
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);

int main(void)
{
	//初始化
	OLED_Init();
	MPU6050_Init();
	MPU6050_DMP_Init();
	Servo_Init();
	
	//OLED屏幕显示
	OLED_ShowString(2,1,"Pitch=");
	OLED_ShowString(3,1,"Roll=");
	OLED_ShowString(4,1,"Yaw=");
	OLED_ShowString(1,1,"AngleZ=");
	//OLED_ShowString(1,1,"AngleY=");
	ServoZ_SetAngle(90);
	
	while (1)
	{
		//姿态数据处理
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);			
		MPU_Get_Gyroscope(&gx,&gy,&gz);
		MPU_Get_Accelerometer(&ax,&ay,&az);

		//舵机对应运动
		AngleY = 80 + Pitch - pid(Pitch - 0);
		ServoY_SetAngle(AngleY);
		AngleZ = 90 - Yaw - pid(Yaw - 0);
		ServoZ_SetAngle(AngleZ);
		AngleX = 90 + Roll - pid(Roll - 0);
		ServoX_SetAngle(AngleX);
		OLED_ShowSignedNum(2, 8, Pitch, 3);
		OLED_ShowSignedNum(3, 8, Roll, 3);
		OLED_ShowSignedNum(4, 8, Yaw, 3);
		OLED_ShowSignedNum(1, 8, AngleX, 3);
//		OLED_ShowSignedNum(2, 8, gx, 5);
//		OLED_ShowSignedNum(3, 8, gy, 5);
//		OLED_ShowSignedNum(4, 8, gz, 5);
	}
}
