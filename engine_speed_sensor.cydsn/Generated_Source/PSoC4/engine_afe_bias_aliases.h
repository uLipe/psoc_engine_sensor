/*******************************************************************************
* File Name: engine_afe_bias.h  
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

#if !defined(CY_PINS_engine_afe_bias_ALIASES_H) /* Pins engine_afe_bias_ALIASES_H */
#define CY_PINS_engine_afe_bias_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define engine_afe_bias_0			(engine_afe_bias__0__PC)
#define engine_afe_bias_0_PS		(engine_afe_bias__0__PS)
#define engine_afe_bias_0_PC		(engine_afe_bias__0__PC)
#define engine_afe_bias_0_DR		(engine_afe_bias__0__DR)
#define engine_afe_bias_0_SHIFT	(engine_afe_bias__0__SHIFT)
#define engine_afe_bias_0_INTR	((uint16)((uint16)0x0003u << (engine_afe_bias__0__SHIFT*2u)))

#define engine_afe_bias_INTR_ALL	 ((uint16)(engine_afe_bias_0_INTR))


#endif /* End Pins engine_afe_bias_ALIASES_H */


/* [] END OF FILE */
