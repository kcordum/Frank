#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "inv_mpu.h"
#include "Servo.h"

float Pitch,Roll,Yaw;
float AngleX, AngleY, AngleZ;
int16_t ax,ay,az,gx,gy,gz;							
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az);

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	MPU6050_DMP_Init();
	Servo_Init();
	
	OLED_ShowString(2,1,"Pitch=");
	OLED_ShowString(3,1,"Roll=");
	OLED_ShowString(4,1,"Yaw=");
	OLED_ShowString(1,1,"AngleZ=");
	//OLED_ShowString(1,1,"AngleY=");
	ServoZ_SetAngle(90);
	
	while (1)
	{
		MPU6050_DMP_Get_Data(&Pitch,&Roll,&Yaw);			
		MPU_Get_Gyroscope(&gx,&gy,&gz);
		MPU_Get_Accelerometer(&ax,&ay,&az);

		
		AngleY = 80 + Pitch;
		ServoY_SetAngle(AngleY);
		AngleZ = 90 - Yaw;
		ServoZ_SetAngle(AngleZ);
		AngleX = 90 + Roll;
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
