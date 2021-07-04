/*
 * MHAL_IRprivate.h
 *
 *  Created on: Jul 1, 2021
 *      Author: M.Aboelsaoud
 */

#ifndef MHAL_IRPRIVATE_H_
#define MHAL_IRPRIVATE_H_


volatile u32 arr_u32IncomingFrame[50] ={0};   /*array to carry the frame coming from the IR sender*/
volatile u8  bitsCounter=0; /* count the array elements*/
volatile u8  StartFlag=0;/*used to identify the start bit in the frame */



#endif /* MHAL_IRPRIVATE_H_ */
