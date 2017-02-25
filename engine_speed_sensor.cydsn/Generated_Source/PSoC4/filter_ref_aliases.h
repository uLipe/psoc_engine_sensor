/*******************************************************************************
* File Name: filter_ref.h  
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

#if !defined(CY_PINS_filter_ref_ALIASES_H) /* Pins filter_ref_ALIASES_H */
#define CY_PINS_filter_ref_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define filter_ref_0			(filter_ref__0__PC)
#define filter_ref_0_PS		(filter_ref__0__PS)
#define filter_ref_0_PC		(filter_ref__0__PC)
#define filter_ref_0_DR		(filter_ref__0__DR)
#define filter_ref_0_SHIFT	(filter_ref__0__SHIFT)
#define filter_ref_0_INTR	((uint16)((uint16)0x0003u << (filter_ref__0__SHIFT*2u)))

#define filter_ref_INTR_ALL	 ((uint16)(filter_ref_0_INTR))


#endif /* End Pins filter_ref_ALIASES_H */


/* [] END OF FILE */
