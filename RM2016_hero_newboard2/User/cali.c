#include "main.h"
			
bool ManualCali(void){
		
			SetGyroCaliData(&GyroCaliData);   //set the apparamStruct using the GyroCaliData, and save apparamStruct to the flash 
			//read GyroCaliData at the begining, keep tracking the value
			
			Sensor_Offset_Param_Init(&gAppParamStruct);   //update the parameter
			ResetCaliCmdFlag(CALI_END_FLAG_GYRO);		//reset the cali cmd
}

bool SetGyro(void){

	//process of the cali if error return error, elseif in processing return in , and if done return done
	if(Is_Lost_Error_Set(LOST_ERROR_IMU))    //
	{
		return false;
	}else{
		GyroSavedCaliData.GyroXOffset = 0;
		GyroSavedCaliData.GyroYOffset = 0;
		GyroSavedCaliData.GyroZOffset = 0;	
		return true;
	}
}

bool SetCali(void){
	
	static uint32_t loopCount = 0;
	static uint32_t loopTime = 10;
	static int32_t pitchSum = 0;
	static int32_t yawSum = 0;
	
	if(Is_Lost_Error_Set(LOST_ERROR_MOTOR5) || Is_Lost_Error_Set(LOST_ERROR_MOTOR6))
	{
		return false;
	}
	else 
	{
		for(loopCount++<loopTime) {  //in cali state
		pitchSum += GMPitchEncoder.raw_value;
		yawSum += GMYawEncoder.raw_value;
		}
		GimbalCaliData.GimbalPitchOffset = pitchSum/loopTime;   //¶ÁÈ¡pitchÖáÍÓÂÝÒÇ×÷ÎªÆ«²î
	  GimbalCaliData.GimbalYawOffset = yawSum/loopTime;		//¶ÁÈ¡yawÖáÍÓÂÝÒÇ×÷ÎªÆ«²î
		GimbalCaliData.GimbalCaliFlag = PARAM_CALI_DONE;
		pitchSum = 0;
		yawSum = 0;
		loopCount = 0;
		return ture;
	}
}


