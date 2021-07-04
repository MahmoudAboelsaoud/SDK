/*****************************************/
/*  Author: Mahmoud Aboelsaoud           */
/*  DATE  : Jul 1, 2021                  */
/*  VERSION : V01                        */
/*  DESCRIPTION : code for NEC IR        */
/*****************************************/



#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "TIMER_private.h"
#include "MGPIO_private.h"
#include "MGPIO_interface.h"
#include "EXTI_interface.h"
#include "TIMER_interface.h"

#include "MHAL_IRconfig.h"
#include "MHAL_IRprivate.h"
#include "MHAL_IRinterface.h"


/*struct which config the EXTI */
gstr_ext_interrupt_config obg_interrupt =
{
	.interrupt_number = INT_0,
	.interrupt_level  = FALLING_EDAGE,
};

/*struct which config the Timer0  */
gcfg_hal_timer_t obg_timer =
{
	.ins_timer = TIMER_0,
	.freq = PRESCALER_256,
	.timer_fun = NORMAL_MODE,
};

/* callback function called after receiving all the bit as it called after 65.s ms from the last bit in the ir frame  */
 static void static_TackAction()
{
	u8 DataInFrame = 0 ;/*carry the binary of the frame*/
	if ((arr_u32IncomingFrame[0] > 40) && (arr_u32IncomingFrame[0] < 70)) /*check if the start bit came in the range 10.24ms to 17.92ms */
	{
		for (u8 i =0; i<8; i++)
		{    /*start from [i+17] as the first 16 bits is consider address and address inverted */
			if ((arr_u32IncomingFrame[17+i] >= 7) && (arr_u32IncomingFrame[17+i] <= 11))/*check the timer for each received bit to consider which is one and which is zero according to its time*/
			{
				SET_BIT(DataInFrame,i);/* if the time of the bit in the range of 2.250 ms consider one if in  7*0.256 = 1.792 ms to 2.816ms */
			}
			else
			{
			  	CLR_BIT(DataInFrame,i);	/*zero o.w*/	   
			}		
		}
	}
	else
	{
		/*Invaild frame*/   
	}
	/*reset the variables to receive other frame */
	arr_u32IncomingFrame [0] = 0;
	DataInFrame = 0;
	StartFlag = 0 ;
}

/* the callback function at every falling edge in the incoming frame */
void HAL_boolIRSensorGetFrame()
{
	if (StartFlag == 0)/*check if it the first bit (start bit) */
	{
		hal_start_timer(&obg_timer); /*start the timer*/
		StartFlag = 1; /*set the flag*/
	}
	else
	{
		arr_u32IncomingFrame[bitsCounter] = hal_ReadTimerCurrentValue(&obg_timer); /*save the time for each bit in the array */
		hal_update_init_timer_value(&obg_timer, 0); /*reset the timer to 0*/
		hal_start_timer(&obg_timer); /*start the timer*/
		bitsCounter++;/*increment the array index*/
	}
	
}

/* Init the needed drivers */
bool_t HAL_boolIRSensorInit(u8 copy_u8ConnectPort, u8 copy_u8ConnectPin)
{
	bool_t ret_val = E_TRUE;
	
	MGPIO_SetPortDirection(copy_u8ConnectPort, copy_u8ConnectPin, INPUT); /*Init the port IR sensor connected */
	
	hal_Init_Timer0_Cb_OV(static_TackAction);/*set timer callback function the overflow after 65.28 ms it is good as well as it longer then 
												the max time of the period between two falling edges is equal 13.5 ms as each clock tick = 0.256ms */
	hal_init_timer(&obg_timer);/*Init the timer0*/
	
	Hal_Ext_Interrupt_Cb_INT0(HAL_boolIRSensorGetFrame); /*set the EXIT callback function at each falling edge*/
	Hal_Ext_Interrupt_Init(&obg_interrupt);/*init the EXTI */
	
	return ret_val;
}