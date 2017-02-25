/*!*****************************************************************************
* \file ADC_1_UABH_B_CyUAB.h
* \version 1.10
*
* \brief 
*   API for Universal Analog Block (UAB)
*
********************************************************************************
* \copyright
* (c) 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
* This software, including source code, documentation and related
* materials ("Software"), is owned by Cypress Semiconductor
* Corporation ("Cypress") and is protected by and subject to worldwide
* patent protection (United States and foreign), United States copyright
* laws and international treaty provisions. Therefore, you may use this
* Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
* non-transferable license to copy, modify, and compile the
* Software source code solely for use in connection with Cypress's
* integrated circuit products. Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE. Cypress reserves the right to make
* changes to the Software without notice. Cypress does not assume any
* liability arising out of the application or use of the Software or any
* product or circuit described in the Software. Cypress does not
* authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#if !defined(CyUAB_H)
#define CyUAB_H
    
#include "cytypes.h"
#include "CyLib.h"
#include "ADC_1_UABH_B_CyUAB_types.h"

    
#define ADC_1_UABH_B_MIN(x, y)  ( ((x)>(y))? (y) : (x) )

/*(0x00001fffUL)*/
#define CyUAB_DAC_NEXT_MASK   (ADC_1_UABH_B_SIGN_VAL_MASK | ADC_1_UABH_B_CA_VAL_MASK | ADC_1_UABH_B_CB_VAL_MASK)
#define CyUAB_DAC_NEXT_SHIFT  (ADC_1_UABH_B_CB_VAL_SHIFT)
    
/*(0x00000fffUL)*/
#define CyUAB_CF_NEXT_MASK    (ADC_1_UABH_B_CF_VAL_MASK | ADC_1_UABH_B_CC_VAL_MASK)

    
#define CyUAB_CLOCK_MASK     (0xfUL)



    
#define CyUAB_STEPS_LEN_MAX (16UL)  
#define CyUAB_STEPS_IDX_MAX (CyUAB_STEPS_LEN_MAX-1UL)

#define CyUAB_OFFSET_MASK (0xffUL)
#define CyUAB_SRAM_OFFSET  ( ((uint32)ADC_1_UABH_B_SRAM0_PTR) - ((uint32)ADC_1_UABH_B_BASE_ADDR) )

/*!
* \addtogroup group_clocking
* @{
*/
/* set all steps for a single clock (1-bit or 2-bit) */
void CyUAB_SetClock( reg32 uabSram[], CyUAB_clk_enum phi, uint16 pattern, uint16 modbitPattern );

/* set all clocks for N steps */
void CyUAB_SetNSteps( reg32 uabSram[], size_t n, const uint16 stepArray[] );

/* set all clocks for a single step */
void CyUAB_SetSingleStep( reg32 uabSram[], size_t idx, const uint16 stepValue );
/** @} clocking */

/* 32-bit memset */
reg32* CyUAB_wordset( reg32 s[], uint32 c, size_t size );

#endif /* #ifndef CyUAB_H */

/* [] END OF FILE */
