/**
  *@file test_uart.c
  *@date 2016-12-12
  *@author Albert.D
  *@brief 
  */

#include "test_uart.h"
#include "usart.h"
  
uint8_t uart3_rx_buff[50];
uint8_t uart6_rx_buff[50];

//it will be auto callback when usart receive msg completely
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == &huart6)
  {
    HAL_UART_Transmit(huart, uart6_rx_buff, 1, 100);
    
    __HAL_UART_CLEAR_PEFLAG(&huart6);
    HAL_UART_Receive_IT(&huart6, uart6_rx_buff, 1);
  }
  if(huart == &huart3)
  {
    		uint8_t test_data1[8] = {0x2};
		HAL_UART_Transmit(&huart3,test_data1,1,10);
		__HAL_UART_CLEAR_PEFLAG(&huart3);
    HAL_UART_Receive_IT(&huart3, uart3_rx_buff, 1);

  }
  
}
