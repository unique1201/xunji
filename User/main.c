#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PWM.h"
#include "Motor.h"
#include "Delay.h"
#include "Key.h"
#include "Trace.h"


int key,page=1,speed=0,start=0;


int main()
{
	OLED_Init();
	PWM_Init();
	Motor_Init();
	Key_Init();
	

	while (1)
	{
		OLED_ShowString(1,1,"->SpeedControl");
		OLED_ShowString(2,1,"Start");
		key=Key_GetNum();
		if (start==0)
		{	//菜单
			if (key==1 && page == 1)
			{
				OLED_ShowString(1,1,"SpeedControl");
				OLED_ShowString(2,1,"->Start");
				page=2;
			}
			else if (key == 1 && page == 2)
			{
				OLED_ShowString(1,1,"->SpeedControl");
				OLED_ShowString(2,1,"Start");
				page=1;
			}
			else if (key == 2 && page == 1)
			{
				OLED_ShowString(1,1,"SpeedControl  E");
				OLED_ShowString(2,1,"Speed:");
				OLED_ShowNum(2,6,speed,5);
				page=3;
			}
			else if (key == 2 && page == 2)
			{
				start=1;
			}
			else if (page == 3 && key == 1)
			{
				speed=(speed+10)%100;
			}
			else if (page == 3 && key == 3)
			{
				page=1;
				OLED_ShowString(1,1,"->SpeedControl");
				OLED_ShowString(2,1,"Start");
			}
	
	
		}
		else
		{
			char state=TrackingSensor_GetState();
			if (state==TRACK_FORWARD || state==TRACK_CROSS_ROAD)
			{
				Motor_SetSpeed1(speed);
				Motor_SetSpeed2(speed);
			}
			else if (state==TRACK_TURN_LEFT_SLOW)
			{
				Motor_SetSpeed1(-50);
				Motor_SetSpeed2(50);
			}
			else if (state==TRACK_TURN_LEFT_FAST)
			{
				Motor_SetSpeed1(speed-50);
				Motor_SetSpeed2(speed);
			}
			else if (state==TRACK_TURN_RIGHT_SLOW)
			{
				Motor_SetSpeed1(-50);
				Motor_SetSpeed2(50);
			}
			else if (state==TRACK_TURN_RIGHT_FAST)
			{
				Motor_SetSpeed1(speed-50);
				Motor_SetSpeed2(speed);
			}
			else if (state==TRACK_LOST)
			{
				Motor_SetSpeed1(0);
				Motor_SetSpeed2(0);
			}
			
		}
	}


}



