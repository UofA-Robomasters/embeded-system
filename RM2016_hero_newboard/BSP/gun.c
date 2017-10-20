#include "stm32f4xx.h"
#include "gun.h"
/*-LEFT---(PH9---TIM12_CH2)--*/
/*-RIGHT--(PH6--TIM12_CH1)--*/

GPIO_InitTypeDef          gpio;
TIM_TimeBaseInitTypeDef   tim;
TIM_OCInitTypeDef         oc;

void GUN_OFF(void){
		TIM12->CCR1 = 0;
		TIM12->CCR2 = 0;
}
void GUN_ON(void){
		TIM12->CCR1 = 2000;
		TIM12->CCR2 = 2000;
}
void GUN_Control(int dutycycle){
		TIM12->CCR1 = dutycycle;
		TIM12->CCR2 = dutycycle;
}
void APS_ON(void){
		TIM9->CCR1 = 1000;
}
void APS_OFF(void){
		TIM9->CCR1 = 0;
}


void PWM_Configuration(void)
{
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH ,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);   //PCLK1=42MHz,TIM12 clk =84MHz
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);   //PCLK1=42MHz,TIM2 clk =84MHz

    gpio.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_9;
    gpio.GPIO_Mode = GPIO_Mode_AF; 
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOH,&gpio);

    GPIO_PinAFConfig(GPIOH,GPIO_PinSource6, GPIO_AF_TIM12);
    GPIO_PinAFConfig(GPIOH,GPIO_PinSource9,GPIO_AF_TIM12); 
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM9);	
    /* TIM12 */
    tim.TIM_Prescaler = 84-1;
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 2500;   //2.5ms
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM12,&tim);
		
    /* TIM9 */
		tim.TIM_Prescaler = 168-1;
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 1000;   //1ms,1KHz
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    //TIM_TimeBaseInit(TIM9,&tim);
		
    oc.TIM_OCMode = TIM_OCMode_PWM2;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_OutputNState = TIM_OutputState_Disable;
    oc.TIM_Pulse = 1000;
    oc.TIM_OCPolarity = TIM_OCPolarity_Low;
    oc.TIM_OCNPolarity = TIM_OCPolarity_High;
    oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
    oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
    TIM_OC1Init(TIM12,&oc);
    TIM_OC2Init(TIM12,&oc);
		oc.TIM_Pulse = 0;
		//TIM_OC1Init(TIM9,&oc);
    
    TIM_OC1PreloadConfig(TIM12,TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM12,TIM_OCPreload_Enable);
		//TIM_OC1PreloadConfig(TIM9,TIM_OCPreload_Enable);
           
    TIM_ARRPreloadConfig(TIM12,ENABLE);
    TIM_ARRPreloadConfig(TIM9,ENABLE);
		
    TIM_Cmd(TIM12,ENABLE);
		//TIM_Cmd(TIM9,ENABLE);
}

void servo_Configuration(void)
{
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH ,ENABLE);
   gpio.GPIO_Pin = GPIO_Pin_10;
   gpio.GPIO_Mode = GPIO_Mode_AF; 
   gpio.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_Init(GPIOH,&gpio);
	 GPIO_PinAFConfig(GPIOH,GPIO_PinSource10, GPIO_AF_TIM5);
	  tim.TIM_Prescaler = 84-1;
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_Period = 2000;   //2.5ms
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM5,&tim);
	
	  oc.TIM_OCMode = TIM_OCMode_PWM2;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_OutputNState = TIM_OutputState_Disable;
    oc.TIM_Pulse = 100;
    oc.TIM_OCPolarity = TIM_OCPolarity_Low;
    oc.TIM_OCNPolarity = TIM_OCPolarity_High;
    oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
    oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
    TIM_OC1Init(TIM5,&oc);
	  TIM_OC1PreloadConfig(TIM5,TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM5,ENABLE);
		 TIM_Cmd(TIM5,ENABLE);
}