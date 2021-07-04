/*
 * MHAL_IRinterface.h
 *
 *  Created on: Jul 1, 2021
 *      Author: M.Aboelsaoud
 */

#ifndef MHAL_IRINTERFACE_H_
#define MHAL_IRINTERFACE_H_
#include "STD_TYPES.h"

/*HAL_boolIRSensorInit function init the used drivers (GPIO , TIMER , EXTI) 
* Config PIN2 in GPIOA as input floating as it the IR sensor input. 
* Config Timer0 to work in normal mode with external frequency 1MHZ and prescalar is 256
  to allow overflow at 65.5 ms.
* Config ExTI to work in INT0 with falling edge trigger.      
*/
bool_t HAL_boolIRSensorInit(u8 copy_u8ConnectPort, u8 copy_u8ConnectPin);



#endif /* MHAL_IRINTERFACE_H_ */
