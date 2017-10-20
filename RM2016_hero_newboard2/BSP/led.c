#include "main.h"

/*----GREEN LED----PA6-----'0' is on,'1' is off */
/*----RED LED----PA7-----'0' is on,'1' is off */

void Led_Configuration(void)
{
  GPIO_InitTypeDef gpioe;
  GPIO_InitTypeDef gpiof;  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	gpioe.GPIO_Pin = GPIO_Pin_7;  //green led
	gpiof.GPIO_Pin = GPIO_Pin_14; //red led

	gpioe.GPIO_Mode = GPIO_Mode_OUT;
	gpioe.GPIO_OType = GPIO_OType_PP;
	gpioe.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOE,&gpioe);
  
	gpiof.GPIO_Mode = GPIO_Mode_OUT;
	gpiof.GPIO_OType = GPIO_OType_PP;
	gpiof.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOF,&gpiof);
  
    GREEN_LED_ON();
    RED_LED_ON();// was all off
}

