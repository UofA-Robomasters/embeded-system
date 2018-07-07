#include "testing_task.h"
#include "bsp_can.h"
#include "bsp_uart.h"
#include "cmsis_os.h"
#include "sys_config.h"

#include "rtc.h"
#include "fatfs.h"
#include "string.h"

/* stack usage monitor */
UBaseType_t testing_stack_surplus;

void testing_task(void const *argu)
{
	while(1){
		int a = 0;
		testing_stack_surplus = uxTaskGetStackHighWaterMark(NULL);
	}
}