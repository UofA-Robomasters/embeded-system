#ifndef __USART3_H__
#define __USART3_H__
#include "main.h"
void USART3_Configuration(void);
void Convert16to8(uint16_t data_16, uint8_t* data_8);
void Convert32to8(uint32_t data_32, uint8_t* data_8);
#endif
