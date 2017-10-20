#ifndef _CAN_BUS_TASK_H_
#define _CAN_BUS_TASK_H_

#include "main.h"

/* CAN Bus 1 */  
#define CAN_BUS2_ZGYRO_FEEDBACK_MSG_ID            0x401
#define CAN_BUS2_SHOOTMOTOR_MSG_ID						    0x207
#define CAN_BUS2_HEROARMH1_FEEDBACK_MSG_ID        0x201
#define CAN_BUS2_HEROARMH2_FEEDBACK_MSG_ID        0x202 
#define CAN_BUS2_HEROTRACK1_FEEDBACK_MSG_ID				0x203
#define CAN_BUS2_HEROTRACK2_FEEDBACK_MSG_ID				0x204


/* CAN Bus 1 */  
#define CAN_BUS1_MOTOR1_FEEDBACK_MSG_ID           0x201
#define CAN_BUS1_MOTOR2_FEEDBACK_MSG_ID           0x202 
#define CAN_BUS1_MOTOR3_FEEDBACK_MSG_ID           0x203
#define CAN_BUS1_MOTOR4_FEEDBACK_MSG_ID           0x204
#define CAN_BUS1_MOTOR5_FEEDBACK_MSG_ID           0x205
#define CAN_BUS1_MOTOR6_FEEDBACK_MSG_ID           0x206

#define CAN_BUS1_ZGYRO_FEEDBACK_MSG_ID   		  0x401

extern volatile Encoder CM1Encoder;
extern volatile Encoder CM2Encoder;
extern volatile Encoder CM3Encoder;
extern volatile Encoder CM4Encoder;
extern volatile Encoder GMYawEncoder;
extern volatile Encoder GMPitchEncoder;
extern volatile Encoder ShootMotorEncoder;
extern volatile Encoder HeroReloadEncoder;
extern volatile Encoder HeroTrackEncoder;
extern float ZGyroModuleAngle;

void GetEncoderBias(volatile Encoder *v, CanRxMsg * msg);
void EncoderProcess(volatile Encoder *v, CanRxMsg * msg);
void Can1ReceiveMsgProcess(CanRxMsg * msg);
void Can2ReceiveMsgProcess(CanRxMsg * msg);
void Set_Gimbal_Current(CAN_TypeDef *CANx, int16_t gimbal_pitch_iq, int16_t gimbal_yaw_iq);
void Set_CM_Speed(CAN_TypeDef *CANx, int16_t cm1_iq, int16_t cm2_iq, int16_t cm3_iq, int16_t cm4_iq);
void Set_ShootMotor_Speed(CAN_TypeDef *CANx, int16_t shoot_motor_iq);
#endif

