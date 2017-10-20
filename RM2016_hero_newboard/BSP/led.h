#ifndef __LED_H__
#define __LED_H__

void Led_Configuration(void);

#define GREEN_LED_ON()      GPIO_ResetBits(GPIOE, GPIO_Pin_7)
#define GREEN_LED_OFF()     GPIO_SetBits(GPIOE, GPIO_Pin_7)
#define GREEN_LED_TOGGLE()      GPIO_ToggleBits(GPIOE, GPIO_Pin_7)

#define RED_LED_ON()            GPIO_ResetBits(GPIOF, GPIO_Pin_14)
#define RED_LED_OFF()           GPIO_SetBits(GPIOF, GPIO_Pin_14)
#define RED_LED_TOGGLE()        GPIO_ToggleBits(GPIOF, GPIO_Pin_14)


//#define GREEN_LED_ON()          ((void)0)
//#define GREEN_LED_OFF()         ((void)0)
//#define GREEN_LED_TOGGLE()      ((void)0)

//#define RED_LED_ON()            ((void)0)
//#define RED_LED_OFF()           ((void)0)
//#define RED_LED_TOGGLE()        ((void)0)
	
#define BOTH_LED_TOGGLE()\
GPIO_ToggleBits(GPIOF, GPIO_Pin_14);\
GPIO_ToggleBits(GPIOE, GPIO_Pin_7)

#endif
