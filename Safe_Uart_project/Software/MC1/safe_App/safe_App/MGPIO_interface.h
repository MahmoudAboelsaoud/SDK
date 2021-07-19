/***********************************************/
/* Auther     : Mahmoud Aboelsaoud             */
/* Date       : 30 Jun 2021                    */
/* Version    : V02                            */
/*Description : interface file                 */
/***********************************************/
#ifndef MGPIO_INTERCAE_H
#define MGPIO_INTERCAE_H

#include "STD_TYPES.h"



bool_t MGPIO_SetPortDirection(u8 Copy_Port, u8 Copy_Pin, u8 Copy_ProtDir);
bool_t MGPIO_SetPin  (u8 Copy_Port, u8 Copy_Pin);
bool_t MGPIO_ClearPin(u8 Copy_Port, u8 Copy_Pin);
bool_t MGPIO_TogalPin(u8 Copy_Port, u8 Copy_Pin);





#endif