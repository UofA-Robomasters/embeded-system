#include "main.h"
#include "FIFO.h"
#include "protocal.h"

/*-----USART3_TX-----PD10-----PD8*/
/*-----USART3_RX-----PD11-----PD9*/

FIFO_S_t* UART_TranFifo;
static unsigned char rx_buffer[256];
void USART3_Configuration(void)
{
    USART_InitTypeDef usart3;
    GPIO_InitTypeDef  gpio;
    NVIC_InitTypeDef  nvic;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);

    GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_USART3); 

    gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_Speed = GPIO_Speed_100MHz;
    gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD,&gpio);

    usart3.USART_BaudRate = 115200;          // speed 10byte/ms
    usart3.USART_WordLength = USART_WordLength_8b;
    usart3.USART_StopBits = USART_StopBits_1;
    usart3.USART_Parity = USART_Parity_No;
    usart3.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
    usart3.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART3,&usart3);

    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3,ENABLE);

    nvic.NVIC_IRQChannel = USART3_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 1;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&nvic);

    UART_TranFifo = FIFO_S_Create(100);  
    if(!UART_TranFifo)
    {
       // while(1);  avoid while in program
	}
}


void UART3_PrintCh(uint8_t ch)
{    
    FIFO_S_Put(UART_TranFifo, ch);
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
    
}

void UART3_PrintBlock(uint8_t* pdata, uint8_t len)
{
	uint8_t i = 0;
    for(i = 0; i < len; i++)
    {
        FIFO_S_Put(UART_TranFifo, pdata[i]);
    }
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);  //发送寄存器空中断
}

void Convert16to8(uint16_t data_16, uint8_t* data_8)
{
	data_8[1] = (uint8_t)(data_16 & 0x00ff);
	data_8[0] = (uint8_t)((data_16 >> 8) & 0x00ff);
}

void Convert32to8(uint32_t data_32, uint8_t* data_8)
{
	uint16_t data_16[2];
	data_16[1] = (uint16_t)(data_32 & 0x0000ffff);
	data_16[0] = (uint16_t)((data_32 >> 16) & 0x0000ffff);
	Convert16to8(data_16[1], &data_8[2]);
	Convert16to8(data_16[0], data_8);
}

int fputc(int ch, FILE *f)
{
    while (USART_GetFlagStatus(USART3,USART_FLAG_TC) == RESET);
//    USART_SendData(USART3, (uint8_t)ch);
    return ch;
}

void USART3_IRQHandler(void)
{  
    if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
    {   
        if(!FIFO_S_IsEmpty(UART_TranFifo))
        {
        uint16_t data = (uint16_t)FIFO_S_Get(UART_TranFifo);
//        USART_SendData(USART3, data);
        }
        else
        {
        USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
        }  
    }else if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)    //接收中断
    {
        uint8_t tmp = USART_ReceiveData(USART3);
			
				uint16_t ZGyro_uint16 = (uint16_t)ZGyroModuleAngle;
				uint16_t yaw_uint16 =(uint16_t)yaw_angle;
				if (tmp == 0x1){
						//USART_SendData(USART3, ZGyro_uint16); 
//					USART_SendData(USART3,ShootMotorSpeedPID.output);
				}
				if(tmp==0x2)
				{
						//USART_SendData(USART3, yaw_angle); //
//					USART_SendData(USART3, yaw_uint16); 
				}
			
/*        if(FrameUnpack(tmp, rx_buffer))
        {
            if(GetFrameCmd(rx_buffer)  == CMD_ID_SENSOR_CALI)     //传感器校准命令ID
            {
                CALI_CMD *pData = (CALI_CMD *)GetFrameDataAddress(rx_buffer);	
                //get the pData->type									
                if(pData->type == GYRO_CALI_START)
                {
                    SetCaliCmdFlag(CALI_START_FLAG_GYRO);
                }
                else if(pData->type == GYRO_CALI_END)
                {
                    SetCaliCmdFlag(CALI_END_FLAG_GYRO);
                }	
                else if(pData->type == MAG_CALI_START)
                {
                    SetCaliCmdFlag(CALI_START_FLAG_MAG);
                }
                else if(pData->type == MAG_CALI_END)
                {
                    SetCaliCmdFlag(CALI_END_FLAG_MAG);
                }
                else if(pData->type == Encoder_CALI_START)
                {
                    SetCaliCmdFlag(CALI_START_FLAG_GIMBAL);
                }	
                else if(pData->type == Encoder_CALI_END)
                {
                    SetCaliCmdFlag(CALI_END_FLAG_GIMBAL);
                }
            }
            else if(GetFrameCmd(rx_buffer)  == CMD_ID_UPLOAD_CALI_INFO)  //如果是要求上传校准信息
            {
            }
            else if(GetFrameCmd(rx_buffer) == CMD_ID_PID_CALI)				//接收PID参数校准命令
            {
                PIDParamStruct_t *pData = (PIDParamStruct_t *)GetFrameDataAddress(rx_buffer);
                PIDCaliProcess(pData);   //保存calidata到static变量中
                SetCaliCmdFlag(CALI_FLAG_PID);	//PID参数							
            }
            else
            {

            }
        }
						*/
    }       
}

