/*! ----------------------------------------------------------------------------
 * @file	deca_mutex.c
 * @brief	IRQ interface / mutex implementation
 *
 * @attention
 *
 * Copyright 2013 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 */

#include "deca_device_api.h"

decaIrqStatus_t decamutexon(void)           
{
//	decaIrqStatus_t s = port_GetEXT_IRQStatus();
//
//	if(s) {
//		port_DisableEXT_IRQ(); //disable the external interrupt line
//	}
//	return s ;   // return state before disable, value is used to re-enable in decamutexoff call
    return 0;
}

/*! ------------------------------------------------------------------------------------------------------------------
 * Function: decamutexoff()
 *
 * Description: This function should re-enable interrupts, or at least restore their state as returned(&saved) by decamutexon 
 * This is called at the end of a critical section
 *
 * Note: The body of this function is defined in deca_mutex.c and is platform specific
 *
 * input parameters:	
 * @param s - the state of the DW1000 interrupt as returned by decamutexon
 *
 * output parameters
 *
 * returns the state of the DW1000 interrupt
 */
void decamutexoff(decaIrqStatus_t s)        // put a function here that re-enables the interrupt at the end of the critical section
{
//	if(s) { //need to check the port state as we can't use level sensitive interrupt on the STM ARM
//		port_EnableEXT_IRQ();
//	}
}
