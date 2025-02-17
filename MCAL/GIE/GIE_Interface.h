/*
 * GIE_Interface.h
 *
 *  Created on: Jul 8, 2024
 *      Author: Ali Mohamed
 */

#ifndef MCAL_GIE_GIE_INTERFACE_H_
#define MCAL_GIE_GIE_INTERFACE_H_

#include "../BIT_MATH.h"
#include "../PLATFORM_TYPES.h"
#include "GIE_Config.h"
#include "GIE_Private.h"

#define GI_DISABLE      0
#define GI_ENABLE       1


Std_ReturnType MCAL_GlobalINTStatusWrite(uint8 Copy_GIStatus);
Std_ReturnType MCAL_GlobalINTStatusRead(uint8 *Copy_GIStatus);


#endif /* MCAL_GIE_GIE_INTERFACE_H_ */
