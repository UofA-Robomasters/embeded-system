#include "main.h"

void BSP_Init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     
	PWM_Configuration();
	//servo_Configuration();//servo (hero arm)
	Led_Configuration();            
	Laser_Configuration();
	TIM2_Configuration();		
  MPU6050_Initialize();    
	TIM6_Configuration();		
	Quad_Encoder_Configuration();		
	CAN2_NEW_Configuration();           
	CAN1_NEW_Configuration();        //old can 2      
	USART1_Configuration(100000);        
	USART3_Configuration();         
	TIM6_Start();   	
  MPU6050_IntConfiguration();     
	MPU6050_EnableInt();    	
	Encoder_Start();
}

