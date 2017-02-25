/*******************************************************************************
* File Name: engine_sensor_uart_tx.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_engine_sensor_uart_tx_ALIASES_H) /* Pins engine_sensor_uart_tx_ALIASES_H */
#define CY_PINS_engine_sensor_uart_tx_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define engine_sensor_uart_tx_0			(engine_sensor_uart_tx__0__PC)
#define engine_sensor_uart_tx_0_PS		(engine_sensor_uart_tx__0__PS)
#define engine_sensor_uart_tx_0_PC		(engine_sensor_uart_tx__0__PC)
#define engine_sensor_uart_tx_0_DR		(engine_sensor_uart_tx__0__DR)
#define engine_sensor_uart_tx_0_SHIFT	(engine_sensor_uart_tx__0__SHIFT)
#define engine_sensor_uart_tx_0_INTR	((uint16)((uint16)0x0003u << (engine_sensor_uart_tx__0__SHIFT*2u)))

#define engine_sensor_uart_tx_INTR_ALL	 ((uint16)(engine_sensor_uart_tx_0_INTR))


#endif /* End Pins engine_sensor_uart_tx_ALIASES_H */


/* [] END OF FILE */
