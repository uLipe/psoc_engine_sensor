/*!*****************************************************************************
* \file ADC_1_UABH_A.c
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


#include "cytypes.h"
#include "ADC_1_UABH_A_CyUAB_types.h"
#include "ADC_1_UABH_A_CyUAB.h"
#include "ADC_1_UABH_A_param.h"
#include "ADC_1_UABH_A_regs.h"
#include "ADC_1_UABH_A.h"


/*General*/

uint32 ADC_1_UABH_A_initVar = 0UL; /**< 0 if component is uninitialized. 1 otherwise. */

/*!
* \addtogroup group_init
* @{
*/

/*! Part of default configuration used to initialize UAB in ADC_1_UABH_A_Start() */
uint16 ADC_1_UABH_A_waveConfig[ADC_1_UABH_A_NUM_STEPS] = {
/*0<=last_step<=15 , so always at least one step*/
((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_0)

#if ADC_1_UABH_A_INC_STEP_1
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_1)
#endif
#if ADC_1_UABH_A_INC_STEP_2
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_2)
#endif
#if ADC_1_UABH_A_INC_STEP_3
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_3)
#endif
#if ADC_1_UABH_A_INC_STEP_4
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_4)
#endif
#if ADC_1_UABH_A_INC_STEP_5
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_5)
#endif
#if ADC_1_UABH_A_INC_STEP_6
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_6)
#endif
#if ADC_1_UABH_A_INC_STEP_7
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_7)
#endif
#if ADC_1_UABH_A_INC_STEP_8
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_8)
#endif
#if ADC_1_UABH_A_INC_STEP_9
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_9)
#endif
#if ADC_1_UABH_A_INC_STEP_10
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_10)
#endif
#if ADC_1_UABH_A_INC_STEP_11
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_11)
#endif
#if ADC_1_UABH_A_INC_STEP_12
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_12)
#endif
#if ADC_1_UABH_A_INC_STEP_13
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_13)
#endif
#if ADC_1_UABH_A_INC_STEP_14
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_14)
#endif
#if ADC_1_UABH_A_INC_STEP_15
,((uint16)ADC_1_UABH_A_PARAM_WAVE_STEP_15)
#endif
};

/*! Part of default configuration used to initialize UAB in ADC_1_UABH_A_Start() */
CyUAB_reg_pair ADC_1_UABH_A_initPairs[ADC_1_UABH_A_INIT_PAIRS_COUNT] = {

	/*OA_CTRL default always first element in initPairs*/
#if ADC_1_UABH_A_NONZERO_OA_CTRL
    {ADC_1_UABH_A_OA_CTRL_PTR         , ((uint32)ADC_1_UABH_A_DEFAULT_OA_CTRL)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_STATIC
    ,{ADC_1_UABH_A_SW_STATIC_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_STATIC)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_MODBIT_SRC
    ,{ADC_1_UABH_A_SW_MODBIT_SRC_PTR  , ((uint32)ADC_1_UABH_A_DEFAULT_SW_MODBIT_SRC)}
#endif
#if ADC_1_UABH_A_NONZERO_SRAM_CTRL
    ,{ADC_1_UABH_A_SRAM_CTRL_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SRAM_CTRL)} 
#endif





#if ADC_1_UABH_A_NONZERO_INTR_MASK	
    ,{ADC_1_UABH_A_INTR_MASK_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_INTR_MASK)}
#endif
#if ADC_1_UABH_A_NONZERO_CAP_CTRL
    ,{ADC_1_UABH_A_CAP_CTRL_PTR       , ((uint32)ADC_1_UABH_A_DEFAULT_CAP_CTRL)}
#endif
#if ADC_1_UABH_A_NONZERO_CAP_ABCF_VAL
    ,{ADC_1_UABH_A_CAP_ABCF_VAL_PTR   , ((uint32)ADC_1_UABH_A_DEFAULT_CAP_ABCF_VAL)}
#endif
#if ADC_1_UABH_A_NONZERO_CAP_AB_VAL_NXT
    ,{ADC_1_UABH_A_CAP_AB_VAL_NXT_PTR , ((uint32)ADC_1_UABH_A_DEFAULT_CAP_AB_VAL_NXT)}
#endif
#if ADC_1_UABH_A_NONZERO_CAP_CF_VAL_NXT
    ,{ADC_1_UABH_A_CAP_CF_VAL_NXT_PTR , ((uint32)ADC_1_UABH_A_DEFAULT_CAP_CF_VAL_NXT)}
#endif
#if ADC_1_UABH_A_NONZERO_STARTUP_DELAY
    ,{ADC_1_UABH_A_STARTUP_DELAY_PTR  , ((uint32)ADC_1_UABH_A_DEFAULT_STARTUP_DELAY)}
#endif
#if ADC_1_UABH_A_NONZERO_SUBSAMPLE_CTRL
    ,{ADC_1_UABH_A_SUBSAMPLE_CTRL_PTR , ((uint32)ADC_1_UABH_A_DEFAULT_SUBSAMPLE_CTRL)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CA_IN0
    ,{ADC_1_UABH_A_SW_CA_IN0_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CA_IN0)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CA_IN1
    ,{ADC_1_UABH_A_SW_CA_IN1_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CA_IN1)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CA_TOP
    ,{ADC_1_UABH_A_SW_CA_TOP_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CA_TOP)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CB_IN0
    ,{ADC_1_UABH_A_SW_CB_IN0_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CB_IN0)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CB_IN1
    ,{ADC_1_UABH_A_SW_CB_IN1_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CB_IN1)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CB_TOP
    ,{ADC_1_UABH_A_SW_CB_TOP_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CB_TOP)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CC_IN0
    ,{ADC_1_UABH_A_SW_CC_IN0_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CC_IN0)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CC_IN1
    ,{ADC_1_UABH_A_SW_CC_IN1_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CC_IN1)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CC_TOP
    ,{ADC_1_UABH_A_SW_CC_TOP_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CC_TOP)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_CF_BOT
    ,{ADC_1_UABH_A_SW_CF_BOT_PTR      , ((uint32)ADC_1_UABH_A_DEFAULT_SW_CF_BOT)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_OTHER
    ,{ADC_1_UABH_A_SW_OTHER_PTR       , ((uint32)ADC_1_UABH_A_DEFAULT_SW_OTHER)}
#endif
#if ADC_1_UABH_A_NONZERO_SW_BOOST_CTRL
    ,{ADC_1_UABH_A_SW_BOOST_CTRL_PTR  , ((uint32)ADC_1_UABH_A_DEFAULT_SW_BOOST_CTRL)}
#endif


};

/*! Default configuration used to initialize UAB in ADC_1_UABH_A_Start() */
CyUAB_config ADC_1_UABH_A_config = {
    ADC_1_UABH_A_waveConfig,
    ADC_1_UABH_A_initPairs,
    CyUAB_SHARED_SW_CFG(ADC_1_UABH_A_PARAM_REF_TIED,ADC_1_UABH_A_PARAM_AGND_TIED,
        ADC_1_UABH_A_PARAM_SW_CC,ADC_1_UABH_A_PARAM_SW_BB,ADC_1_UABH_A_PARAM_SW_AA),
    ADC_1_UABH_A_NUM_STEPS,
    (uint8)(ADC_1_UABH_A_ELEMENT_COUNT(ADC_1_UABH_A_initPairs))
};

/*! @} group_init */


/************** ADC_1_UABH_A_Start() **************************************/
/*!
* @brief Initializes and enables the component.
* 
* @details This function is equivalent to calling 
* ADC_1_UABH_A_Enable(), ADC_1_UABH_A_Init(&ADC_1_UABH_A_config), and ADC_1_UABH_A_Run(1UL).  
* Takes no parameters.  Returns @c void.
* 
* @internal
* @reglist
* @image html SetTopSwitch.png
* @endinternal
* 
* @see ADC_1_UABH_A_Enable()
* @see ADC_1_UABH_A_Init()
* @see ADC_1_UABH_A_Run()
* @see ADC_1_UABH_A_Stop()
*
* @sideeffect Sets ENABLED bit for whole UAB - both half0 and half1.
*
* \globalvars
*  \ref ADC_1_UABH_A_initVar (RW)
*
*******************************************************************************/
void ADC_1_UABH_A_Start(void)
{
    if (ADC_1_UABH_A_initVar != 1UL)
    {
        ADC_1_UABH_A_Init(&ADC_1_UABH_A_config);
        ADC_1_UABH_A_initVar = 1UL;
    }
    else 
    {
        /* Already initialized - empty */
    }
    
    /*no delay required between Enable() and Run(1) - run bit control logic handles UAB ramp up*/
    ADC_1_UABH_A_Run(1UL); /*set the run bit*/
}

/************* ADC_1_UABH_A_Stop() ****************************************/
/*!
* @brief Stops component functionality.
* 
* @details Disables the clocks.  Call this before modifying the UAB configuration.
* Takes no parameters.  Returns @c void.
* 
* @internal
* @reglist
* @endinternal
* 
* @see ADC_1_UABH_A_Start()
* @see ADC_1_UABH_A_Run()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_Stop(void)
{
    ADC_1_UABH_A_Run(0UL); /*Clear run bit*/
    /*Intentionally not clearing the enable bit because it has a side-effect - 
	the enable bit is shared with another UAB half*/
}


/* Support function for ADC_1_UABH_A_Init() */
void ADC_1_UABH_A_WriteInitPairs(const CyUAB_reg_pair pairs[], size_t n)
{
    uint32 i;
    for( i = 0UL; i < n; i++ )
    {
        CY_SET_REG32( pairs[i].addr, pairs[i].value );
    }    
}




    


/*************** ADC_1_UABH_A_Init() **************************************/
/*!
* @brief Initializes component settings.
* 
* @details Enables UAB and sets initial configurations, but does not start clocking.
*
* @param cfg pointer to a UAB configuration
* Returns @c void.
*
* Start() is the preferred way to enable the UAB.
*
* Can be used for dynamic reconfiguration - must create configurations that handle
* the deltas between them including clearing registers.
* 
* @internal
* @reglist all
* @endinternal
* 
* @see ADC_1_UABH_A_Start()
* @see ADC_1_UABH_A_Enable()
* 
* @sideeffect Sets ENABLED bit for whole UAB - both half0 and half1.
*******************************************************************************/
void ADC_1_UABH_A_Init(const CyUAB_config * cfg)
{
#if ADC_1_UABH_A_ISPAIRED 
    CyUAB_agnd_tied_enum agndTied;
    CyUAB_ref_tied_enum refTied;
    CyUAB_clk_enum clk_AA;
    CyUAB_clk_enum clk_BB;
    CyUAB_clk_enum clk_CC;
#endif

    ADC_1_UABH_A_Enable();
    
    CyUAB_SetNSteps( ADC_1_UABH_A_SRAM0_PTR, ((size_t)(cfg->stepCount)), (cfg->waveSteps) );
    
    /* Optimized version of ClearAllClocks() -- 
    Clear remaining wavesteps, so clock editing with SetClock() works
    */
    (void)CyUAB_wordset( 
        ((reg32*)( ((uint32)(ADC_1_UABH_A_SRAM0_PTR)) + (((uint32)(cfg->stepCount))*sizeof(uint32)) )), 
        0UL, 
        ( ( CyUAB_STEPS_LEN_MAX - ((uint32)(cfg->stepCount)) ) * sizeof(uint32) )
    );
    
    ADC_1_UABH_A_WriteInitPairs( cfg->pairs, ((size_t)(cfg->pairCount)) );
    /* ^ 
    *  | 
    *  | 
    *  Direct writes must happen before writing shared switch fields*/
    
    
#if ADC_1_UABH_A_ISPAIRED
    /*Handle shared switches - switches that connect paired UABPRIM instances*/
    agndTied = CyUAB_SHARED_SW_CFG_AGNDTIED( cfg->shared_sw );
    ADC_1_UABH_A_SetAgndTied( agndTied );
    refTied = CyUAB_SHARED_SW_CFG_REFTIED(  cfg->shared_sw );
    ADC_1_UABH_A_SetRefTied( refTied );
    clk_AA = CyUAB_SHARED_SW_CFG_AA(  cfg->shared_sw );
    ADC_1_UABH_A_SetSwitch( CyUAB_SW_AA, clk_AA );
    clk_BB = CyUAB_SHARED_SW_CFG_BB(  cfg->shared_sw );
    ADC_1_UABH_A_SetSwitch( CyUAB_SW_BB, clk_BB );
    clk_CC = CyUAB_SHARED_SW_CFG_CC(  cfg->shared_sw );
    ADC_1_UABH_A_SetSwitch( CyUAB_SW_CC, clk_CC );
#endif
    
}

/************** ADC_1_UABH_A_Enable() *************************************/
/*!
* @brief Enables the component.
* 
* @details Provides power to the op-amp, charge pump, comparator, and reference 
* buffers.  Enable() does not enable the clocking.  Call Run(1UL) to enable clocking.
* Takes no parameters.  Returns @c void.
*
* Start() is the preferred way to enable the UAB if all of your configuration is 
* captured in symbol parameters.
*
* NOTE: The ENABLED bit controls both half0 and half1 within a UAB pair.
*
* Disable() is not implemented.
* Clearing the ENABLED bit has the side effect of disabling both halves.
* How to disable:
* ADC_1_UABH_A_UAB_CTRL_REG &= ~ADC_1_UABH_A_ENABLED_MASK;
*
* The actual power settings are Controlled by the power setting functions.
* 
* @internal
* @reglist
* @endinternal
* 
* @see ADC_1_UABH_A_Start()
* @see ADC_1_UABH_A_Init()
* @see ADC_1_UABH_A_SetUABPower()
* @see ADC_1_UABH_A_SetOAPower()
* @see ADC_1_UABH_A_SetCompPower()
* @see ADC_1_UABH_A_SetRefPower()
* @see ADC_1_UABH_A_SetAgndPower()
* 
* @sideeffect Sets ENABLED bit for whole UAB - both half0 and half1.
*******************************************************************************/
void ADC_1_UABH_A_Enable(void)
{
    ADC_1_UABH_A_UAB_CTRL_REG |= ADC_1_UABH_A_ENABLED_MASK; /*Side effect: also enables other UAB half in same pair*/
}


/*Interrupts*/


/*********** ADC_1_UABH_A_ClearInterrupt() ********************************/
/*!
* @brief Reset an interrupt request bit. 
* 
* @details After an interrupt has been fired, this function resets the interrupt 
* so it can fire again. Returns @c void.
* 
* @param intr 
* @arg CyUAB_INTR_COMP select comparator interrupt
* @arg CyUAB_INTR_VDAC_EMPTY select VDAC empty interrupt
*
* @internal
* @reglist @reg ADC_1_UABH_A_INTR_REG
* @endinternal
* 
* @see ADC_1_UABH_A_SetInterrupt()
* 
* @see ADC_1_UABH_A_SetInterruptMask()
* @see ADC_1_UABH_A_ClearInterruptMask()
* @see ADC_1_UABH_A_GetInterruptIsMasked()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_ClearInterrupt(CyUAB_intr_enum intr)
{
    /* Write '1' to the register bit field to clear the interrupt bit. */
    /*intentionally omitting decimator interrupt - handled in decimator component*/    

    uint32 mask = ( (CyUAB_INTR_COMP==intr)      ? ((uint32)ADC_1_UABH_A_INTR_COMP_MASK) : 
                  ( (CyUAB_INTR_VDAC_EMPTY==intr)? ((uint32)ADC_1_UABH_A_INTR_VDAC_EMPTY_MASK) : 
                  0UL ) );
    if(0UL!=mask)
    {
        *(ADC_1_UABH_A_INTR_PTR) |= mask;    
    }
}

/************* ADC_1_UABH_A_SetInterrupt() ********************************/
/*!
* @brief Sets the bit in the interrupt request register.
* 
* @details Set the bit to activate a certain interrupt request. Returns @c void.
* 
* @param intr 
* @arg CyUAB_INTR_COMP select comparator interrupt
* @arg CyUAB_INTR_VDAC_EMPTY select VDAC empty interrupt
*
* @internal
* @reglist @reg ADC_1_UABH_A_INTR_SET_REG
* @endinternal
*
* 
* @see ADC_1_UABH_A_ClearInterrupt()
* @see ADC_1_UABH_A_SetInterruptMask()
* @see ADC_1_UABH_A_ClearInterruptMask()
* @see ADC_1_UABH_A_GetInterruptIsMasked()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetInterrupt(CyUAB_intr_enum intr)
{
    /* Write with '1' to set corresponding bit in interrupt request register. */
    /*intentionally omitting decimator interrupt - handled in decimator component*/
    
    uint32 mask = ( (CyUAB_INTR_COMP==intr)      ? ((uint32)ADC_1_UABH_A_INTR_COMP_MASK) : 
                  ( (CyUAB_INTR_VDAC_EMPTY==intr)? ((uint32)ADC_1_UABH_A_INTR_VDAC_EMPTY_MASK) : 
                  0UL ) );
    if(0UL!=mask)
    {
        *(ADC_1_UABH_A_INTR_SET_PTR) |= mask;
    }
}

/************** ADC_1_UABH_A_SetInterruptMask() ***************************/
/*!
* @brief Sets the mask bit for the passed interrupt.
* 
* @details Set the mask bit for setting an interrupt request. Returns @c void.
* 
* @param intr 
* @arg CyUAB_INTR_COMP select comparator interrupt
* @arg CyUAB_INTR_VDAC_EMPTY select VDAC empty interrupt
*
* @internal
* @reglist @reg ADC_1_UABH_A_INTR_MASK_REG
* @endinternal
* 
* @see ADC_1_UABH_A_SetInterrupt()
* @see ADC_1_UABH_A_ClearInterrupt()
* 
* @see ADC_1_UABH_A_ClearInterruptMask()
* @see ADC_1_UABH_A_GetInterruptIsMasked()
*
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetInterruptMask(CyUAB_intr_enum intr)
{
    /* Write with '1' to set interrupt mask*/
    /*intentionally omitting decimator interrupt - handled in decimator component*/
    
    uint32 mask = ( (CyUAB_INTR_COMP==intr)      ? ((uint32)ADC_1_UABH_A_INTR_COMP_MASK) : 
                  ( (CyUAB_INTR_VDAC_EMPTY==intr)? ((uint32)ADC_1_UABH_A_INTR_VDAC_EMPTY_MASK) : 
                  0UL ) );
    if(0UL!=mask)
    {
        *(ADC_1_UABH_A_INTR_MASK_PTR) |= mask;    
    }
}

/************* ADC_1_UABH_A_ClearInterruptMask() **************************/
/*!
* @brief Clears the mask bit for the passed interrupt.
* 
* @details Clear the mask bit for setting an interrupt request. Returns @c void.
* 
* @param intr 
* @arg CyUAB_INTR_COMP select comparator interrupt
* @arg CyUAB_INTR_VDAC_EMPTY select VDAC empty interrupt
*
* @internal
* @reglist @reg ADC_1_UABH_A_INTR_MASK_REG
* @endinternal
* 
* @see ADC_1_UABH_A_SetInterrupt()
* @see ADC_1_UABH_A_ClearInterrupt()
* @see ADC_1_UABH_A_SetInterruptMask()
* 
* @see ADC_1_UABH_A_GetInterruptIsMasked()
* 
* @sideeffect None
******************************************************************************/
void ADC_1_UABH_A_ClearInterruptMask(CyUAB_intr_enum intr)
{
    /* Write with '0' to clear interrupt mask*/
    /*intentionally omitting decimator interrupt - handled in decimator component*/
    
    uint32 mask = ( (CyUAB_INTR_COMP==intr)      ? ~((uint32)ADC_1_UABH_A_INTR_COMP_MASK) : 
                  ( (CyUAB_INTR_VDAC_EMPTY==intr)? ~((uint32)ADC_1_UABH_A_INTR_VDAC_EMPTY_MASK) : 
                  0xFFFFFFFFUL ) );
    if(0xFFFFFFFFUL!=mask)
    {
        *(ADC_1_UABH_A_INTR_MASK_PTR) &= mask;    
    }
}

/********** ADC_1_UABH_A_GetInterruptIsMasked() ***************************/
/*!
* @brief Check for interrupt masked.
* 
* @details Return type is @c uint32 32-bit unsigned integer. Returns 1 if the passed 
interrupt is both masked and requested. Returns 0 otherwise.
* 
* @param intr 
* @arg CyUAB_INTR_COMP select comparator interrupt
* @arg CyUAB_INTR_VDAC_EMPTY select VDAC empty interrupt
*
* @internal
* @reglist ADC_1_UABH_A_INTR_MASKED_REG
* @endinternal
*
* @see ADC_1_UABH_A_SetInterrupt()
* @see ADC_1_UABH_A_ClearInterrupt()
* @see ADC_1_UABH_A_SetInterruptMask()
* @see ADC_1_UABH_A_ClearInterruptMask()
* 
*
* @sideeffect None
*******************************************************************************/
uint32 ADC_1_UABH_A_GetInterruptIsMasked(CyUAB_intr_enum intr)
{
    uint32 r; /*return value*/
    
    /*intentionally omitting decimator interrupt - handled in decimator component*/
    
    uint32 mask = ( (CyUAB_INTR_COMP==intr)      ? ((uint32)ADC_1_UABH_A_INTR_COMP_MASK) : 
                  ( (CyUAB_INTR_VDAC_EMPTY==intr)? ((uint32)ADC_1_UABH_A_INTR_VDAC_EMPTY_MASK) : 
                  0UL ) );
    
    r = ( 0UL != ( (*(ADC_1_UABH_A_INTR_MASKED_PTR)) & mask ) ) ? 1UL : 0UL;
    return r;
}

/*Power*/

/***************** ADC_1_UABH_A_SetUABPower() *****************************/
/*!
* @brief Sets the UAB half's power mode.
* 
* @details The UAB half has several power modes available.  This sets the power
* reference that is used for the active components as well, that is, the op-amp
* and comparator have settings that are HI, MED, and LOW relative to the entire
* UAB half's power.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL @reg ADC_1_UABH_A_OA1_CTRL
* @endinternal
* 
* @see ADC_1_UABH_A_Stop()
* @see ADC_1_UABH_A_SetOAPower()
* @see ADC_1_UABH_A_SetCompPower()
* @see ADC_1_UABH_A_SetRefPower()
* @see ADC_1_UABH_A_SetAgndPower()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetUABPower(CyUAB_coarse_pwr_enum powerLevel)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_OA_CTRL_PTR, 
      ADC_1_UABH_A_UAB_PWR_MASK, 
      ((uint32)powerLevel), 
      ADC_1_UABH_A_UAB_PWR_SHIFT
    );
}


/************* ADC_1_UABH_A_SetOAPower() **********************************/
/*!
* @brief Set the op-amp power level.
* 
* @details The power of the op-amp is relative to the power mode of the UAB. 
* This function sets that relative setting.  Returns @c void.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL @reg ADC_1_UABH_A_OA1_CTRL
* @image html _.png 
* @endinternal
* 
* @see ADC_1_UABH_A_SetUABPower()
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetOAPower(CyUAB_fine_pwr_enum powerLevel)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_OA_CTRL_PTR, 
      ADC_1_UABH_A_OA_PWR_MASK, 
      ((uint32)powerLevel), 
      ADC_1_UABH_A_OA_PWR_SHIFT
    );
}


/******************** ADC_1_UABH_A_SetCompPower() *************************/
/*!
* @brief Set the comparator power level.
* 
* @details The power of the comparator is relative to the power mode of the UAB.
* This function sets that relative setting.  Returns @c void.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL @reg ADC_1_UABH_A_OA1_CTRL
* @image html SetCompPower.png 
* @endinternal
*
* @see ADC_1_UABH_A_SetUABPower()
*
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetCompPower(CyUAB_fine_pwr_enum powerLevel)
{  
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_OA_CTRL_PTR, 
      ADC_1_UABH_A_CMP_PWR_MASK, 
      ((uint32)powerLevel), 
      ADC_1_UABH_A_CMP_PWR_SHIFT
    );
}


/***************** ADC_1_UABH_A_SetRefPower *******************************/
/*!
* @brief Set the power level of the buffer for the reference voltage.
* 
* @details There are two buffered inputs: reference and analog-ground.  This 
* function sets the power of the reference buffer--which connects to the 
* ADC_1_UABH_A_NET_REF signal--relative to the power mode of the UAB. Returns @c void.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL @reg ADC_1_UABH_A_OA1_CTRL
* @image html SetRefPower.png 
* @endinternal
* 
* @see ADC_1_UABH_A_SetUABPower()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetRefPower(CyUAB_fine_pwr_enum powerLevel)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_OA_CTRL_PTR, 
      ADC_1_UABH_A_REF_PWR_MASK, 
      ((uint32)powerLevel), 
      ADC_1_UABH_A_REF_PWR_SHIFT
    );
}


/**************** ADC_1_UABH_A_SetAgndPower() *****************************/
/*!
* @brief Set the power level of the buffer for the analog-ground voltage.
* 
* @details There are two buffered inputs: reference and analog-ground.  This 
* function sets the power of the analog-ground buffer--which connects to the 
* ADC_1_UABH_A_NET_REF signal--relative to the power mode of the UAB. Returns @c void.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL @reg ADC_1_UABH_A_OA1_CTRL
* @image html SetAgndPower.png 
* @endinternal
* 
* @see ADC_1_UABH_A_SetUABPower()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetAgndPower(CyUAB_fine_pwr_enum powerLevel)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_OA_CTRL_PTR, 
      ADC_1_UABH_A_AGND_PWR_MASK, 
      ((uint32)powerLevel), 
      ADC_1_UABH_A_AGND_PWR_SHIFT
    );
}


/**************** ADC_1_UABH_A_SetRefVdda() *******************************/
/*!
* @brief Force buffered ref to VDDA.
* 
* @details Replace ref buffer output with VDDA (REFx_PTS). Returns @c void.
*
* @param forceVdda
* @arg 0 use routed reference
* @arg 1 use vdda for reference 
*
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL @reg ADC_1_UABH_A_OA1_CTRL
* @image html _.png 
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetRefVdda(CyUAB_ref_force_vdda_enum forceVdda)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_OA_CTRL_PTR, 
      ADC_1_UABH_A_REF_PTS_MASK, 
      ((uint32)forceVdda), 
      ADC_1_UABH_A_REF_PTS_SHIFT
    );
}


/*************** ADC_1_UABH_A_SetAgndVdda() *******************************/
/*!
* @brief Force buffered agnd to VDDA.
* 
* @details Replace analog ground buffer output with VDDA. (AGNDx_PTS). Returns @c void.
* 
* @param forceVdda
* @arg 0 use routed reference
* @arg 1 use vdda for reference
*
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL @reg ADC_1_UABH_A_OA1_CTRL
* @image html _.png 
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetAgndVdda(CyUAB_agnd_force_vdda_enum forceVdda)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_OA_CTRL_PTR, 
      ADC_1_UABH_A_AGND_PTS_MASK, 
      ((uint32)forceVdda), 
      ADC_1_UABH_A_AGND_PTS_SHIFT
    );
}


/************* ADC_1_UABH_A_SetRefTied() **********************************/
/*!
* @brief Ties the outputs of the reference buffers of the two UAB-halves together.
* 
* @details The reference buffers of this half-UAB and its sibling half-UAB can be
* tied together.
* 
* @param refTied
* @arg 0 references not shared
* @arg 1 references shared
*
* @note Make sure that one of the reference buffers is disabled before tying them
* together.
*
* @internal
* @reglist @reg ADC_1_UABH_A_OA1_CTRL
* @image html _.png 
* @endinternal
* 
* 
* @see ADC_1_UABH_A_SetAgndTied()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetRefTied( CyUAB_ref_tied_enum refTied)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_REF_TIED_PTR, 
      ADC_1_UABH_A_REF_TIED_MASK, 
      ((uint32)refTied), 
      ADC_1_UABH_A_REF_TIED_SHIFT
    );
}

/*********** ADC_1_UABH_A_SetAgndTied() ***********************************/
/*!
* @brief Ties the outputs of the analog-ground buffers of the two UAB-halves
* together.
* 
* @details The analog-ground buffers of this half-UAB and its sibling half-UAB can
* be tied together.
*
* @param agndTied
* @arg 0 references not shared
* @arg 1 references shared
*
* @note Make sure that one of the analog-ground buffers is disabled before tying
* them together.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL
* @image html _.png 
* @endinternal
* 
* @see ADC_1_UABH_A_SetRefTied()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetAgndTied(CyUAB_agnd_tied_enum agndTied)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_AGND_TIED_PTR, 
      ADC_1_UABH_A_AGND_TIED_MASK, 
      ((uint32)agndTied), 
      ADC_1_UABH_A_AGND_TIED_SHIFT
    );
}


/*Caps*/

/***************** ADC_1_UABH_A_SetCapA() *********************************/
/*!
* @brief Set the capacitance for branch A
* 
* @details There are three input branches (A, B, C) and a single feedback branch (F).  
* Each branch can have its capacitance configured independently.
* 
* The A, B, and C branches have capacitance range of 0-63 units (0-3150fF) in increments of 50fF.  
* The F branch has a capacitance range of 0-64 units (0-3200fF) in increments of 100fF.
*
* @note In branches B and C, there are attenuation capacitors in the signal path.
* This function does not configure those capacitors.
* @see ADC_1_UABH_A_SetAttenBypassSwitchB()
* @see ADC_1_UABH_A_SetAttenBypassSwitchC()
*
* @see ADC_1_UABH_A_SetCaps()
* @see ADC_1_UABH_A_SetCapB()
* @see ADC_1_UABH_A_SetCapC()
* @see ADC_1_UABH_A_SetCapF()
*
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_ABCF0_VAL @reg ADC_1_UABH_A_CAP_ABCF1_VAL
* @image html SetCapacitors.png 
* @endinternal
*
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetCapA(CyUAB_cap_enum capA)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_ABCF_VAL_PTR,
      ADC_1_UABH_A_CA_VAL_MASK, 
      ((uint32)capA), 
      ADC_1_UABH_A_CA_VAL_SHIFT
    );
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_AB_VAL_NXT_PTR, 
      ADC_1_UABH_A_CA_VAL_MASK, 
      ((uint32)capA), 
      ADC_1_UABH_A_CA_VAL_SHIFT
    ); 
}

/***************** ADC_1_UABH_A_SetCapB() *********************************/
/*!
* @brief Set the capacitance for branch B
* 
* @details There are three input branches (A, B, C) and a single feedback branch (F).  
* Each branch can have its capacitance configured independently.
* 
* The A, B, and C branches have capacitance range of 0-63 units (0-3150fF) in increments of 50fF.  
* The F branch has a capacitance range of 0-64 units (0-3200fF) in increments of 100fF.
*
* @note In branches B and C, there are attenuation capacitors in the signal path.
* This function does not configure those capacitors.
* @see ADC_1_UABH_A_SetAttenBypassSwitchB()
* @see ADC_1_UABH_A_SetAttenBypassSwitchC()
*
* @see ADC_1_UABH_A_SetCaps()
* @see ADC_1_UABH_A_SetCapA()
* @see ADC_1_UABH_A_SetCapC()
* @see ADC_1_UABH_A_SetCapF()
* @see ADC_1_UABH_A_SetGroundUnused()
*
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_ABCF0_VAL @reg ADC_1_UABH_A_CAP_ABCF1_VAL
* @image html SetCapacitors.png 
* @endinternal
* 
* @sideeffect capB[5:0] = capB[6] ? 0x3F : capB[5:0]
*******************************************************************************/
void ADC_1_UABH_A_SetCapB(CyUAB_b_cap_enum capB)
{
    const uint32 threshold64 = 64UL; /*capB>=64 are treated the same (set CB_64 and CB_VAL[5:0]==0x3F) */
    const uint32 b64 = ADC_1_UABH_A_CB_64_MASK | ADC_1_UABH_A_CB_VAL_MASK;
    uint32 bval = (((uint32)capB)>=threshold64) ? b64 : ((uint32)capB);
    ADC_1_UABH_A_SET_VARIOUS_FIELDS(
      ADC_1_UABH_A_CAP_ABCF_VAL_PTR,
      ADC_1_UABH_A_CB_64_MASK | ADC_1_UABH_A_CB_VAL_MASK, 
       bval
    );
    
    /*No CB_64 in CAP_AB_VAL_NXT register*/
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_AB_VAL_NXT_PTR, 
      ADC_1_UABH_A_CB_VAL_MASK, 
      bval,
      ADC_1_UABH_A_CB_VAL_SHIFT
    );
}

/***************** ADC_1_UABH_A_SetCapC() *********************************/
/*!
* @brief Set the capacitance for branch C
* 
* @details There are three input branches (A, B, C) and a single feedback branch (F).  
* Each branch can have its capacitance configured independently.
* 
* The A, B, and C branches have capacitance range of 0-63 units (0-3150fF) in increments of 50fF.  
* The F branch has a capacitance range of 0-64 units (0-3200fF) in increments of 100fF.
*
* @note In branches B and C, there are attenuation capacitors in the signal path.
* This function does not configure those capacitors.
* @see ADC_1_UABH_A_SetAttenBypassSwitchB()
* @see ADC_1_UABH_A_SetAttenBypassSwitchC()
* 
* @see ADC_1_UABH_A_SetCaps()
* @see ADC_1_UABH_A_SetCapA()
* @see ADC_1_UABH_A_SetCapB()
* @see ADC_1_UABH_A_SetCapF()
* @see ADC_1_UABH_A_SetGroundUnused()
*
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_ABCF0_VAL @reg ADC_1_UABH_A_CAP_ABCF1_VAL
* @image html SetCapacitors.png 
* @endinternal
*
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetCapC(CyUAB_cap_enum capC)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_ABCF_VAL_PTR,
      ADC_1_UABH_A_CC_VAL_MASK, 
      ((uint32)capC), 
      ADC_1_UABH_A_CC_VAL_SHIFT
    );
    /*Not setting CC_VAL_UPDATE bit*/
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_CF_VAL_NXT_PTR, 
      ADC_1_UABH_A_CC_VAL_MASK, 
      ((uint32)capC), 
      ADC_1_UABH_A_CC_VAL_SHIFT
    );
}

/***************** ADC_1_UABH_A_SetCapF() *********************************/
/*!
* @brief Set the capacitance for branch F
* 
* @details There are three input branches (A, B, C) and a single feedback branch (F).  
* Each branch can have its capacitance configured independently.
* 
* The A, B, and C branches have capacitance range of 0-63 units (0-3150fF) in increments of 50fF.  
* The F branch has a capacitance range of 0-64 units (0-3200fF) in increments of 100fF.
*
* @note In branches B and C, there are attenuation capacitors in the signal path.
* This function does not configure those capacitors.
* @see ADC_1_UABH_A_SetAttenBypassSwitchB()
* @see ADC_1_UABH_A_SetAttenBypassSwitchC()
*
* @see ADC_1_UABH_A_SetCaps()
* @see ADC_1_UABH_A_SetCapA()
* @see ADC_1_UABH_A_SetCapB()
* @see ADC_1_UABH_A_SetCapC()
*
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_ABCF0_VAL @reg ADC_1_UABH_A_CAP_ABCF1_VAL
* @image html SetCapacitors.png 
* @endinternal
*
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetCapF(CyUAB_f_cap_enum capF)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_ABCF_VAL_PTR,
      ADC_1_UABH_A_CF_VAL_MASK, 
      ((uint32)capF), 
      ADC_1_UABH_A_CF_VAL_SHIFT
    );
    /*Not setting CF_VAL_UPDATE bit*/
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_CF_VAL_NXT_PTR, 
      ADC_1_UABH_A_CF_VAL_MASK, 
      ((uint32)capF), 
      ADC_1_UABH_A_CF_VAL_SHIFT
    );    
}

/***************** ADC_1_UABH_A_SetCaps() *********************************/
/*!
* @brief Set the capacitances individually for all branches (A,B,C,F)
* 
* @details There are three input branches (A, B, C) and a single feedback branch (F).  
* Each branch can have its capacitance configured independently.
* 
* The A, B, and C branches have capacitance range of 0-63 units (0-3150fF) in increments of 50fF.  
* The F branch has a capacitance range of 0-64 units (0-3200fF) in increments of 100fF.

* @note In branches B and C, there are attenuation capacitors in the signal path.
* This function does not configure those capacitors.  See ADC_1_UABH_A_SetAttenuationTrim() 
* and ADC_1_UABH_A_SetAttenBypassSwitch().
* 
* @param capA Use the CyUAB_cap_enum enumerated values.
* @param capB Use the CyUAB_b_cap_enum enumerated values.
* @param capC Use the CyUAB_cap_enum enumerated values.
* @param capF Use the CyUAB_f_cap_enum enumerated values.
*
* @see ADC_1_UABH_A_SetCapA()
* @see ADC_1_UABH_A_SetCapC()
* @see ADC_1_UABH_A_SetCapF()
* @see ADC_1_UABH_A_SetGroundUnused()
* @see ADC_1_UABH_A_SetSwitch(CyUAB_SW_TB,clk)
* @see ADC_1_UABH_A_SetSwitch(CyUAB_SW_TC,clk)
* 
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_ABCF0_VAL @reg ADC_1_UABH_A_CAP_ABCF1_VAL
* @image html _.png 
* @endinternal
*
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetCaps(CyUAB_cap_enum capA, CyUAB_b_cap_enum capB, 
    CyUAB_cap_enum capC, CyUAB_f_cap_enum capF)
{
    ADC_1_UABH_A_SetCapA(capA);
    ADC_1_UABH_A_SetCapB(capB);
    ADC_1_UABH_A_SetCapC(capC);
    ADC_1_UABH_A_SetCapF(capF);
}

/********* ADC_1_UABH_A_SetGroundUnused() *********************************/
/*!
* @brief Sets whether unused capacitors are grounded or floating.
* 
* @details By default unused caps in the cap array are left floating.  
* Unused caps in branch B and C can be grounded when not in use.  
*
* When used as a DAC, the UAB uses two branches, one for MSBs, one for LSBs.
* The MSB cap array unit cells have their bottom plate floated when the
* CAP is not being used. For the LSB array, the unused caps must be shorted to the
* Analog Ground. Most common case will be using Branch A as MSB, with one of
* either B/C as the LSB.  Returns @c void.
*
* @param gndUnusedB ground unused caps in branch B
* @param gndUnusedC gournd unused caps in branch C
*
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_CTRL0 ADC_1_UABH_A_CAP_CTRL1
* @image html SetCapacitors.png 
* @endinternal
*
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetGroundUnused(CyUAB_gnd_unused_enum gndUnusedB, CyUAB_gnd_unused_enum gndUnusedC )
{
    
    /*mask input values before shifting to prevent overlap*/
    const uint32 CB_GND_PRESHIFT_MASK = ADC_1_UABH_A_CB_GND_MASK>>ADC_1_UABH_A_CB_GND_SHIFT;
    const uint32 CC_GND_PRESHIFT_MASK = ADC_1_UABH_A_CC_GND_MASK>>ADC_1_UABH_A_CC_GND_SHIFT;
    const uint32 mask = ADC_1_UABH_A_CC_GND_MASK | ADC_1_UABH_A_CB_GND_MASK;
    ADC_1_UABH_A_SET_VARIOUS_FIELDS(
      ADC_1_UABH_A_CAP_CTRL_PTR,
      mask,
      ((uint32)( 
        ( ( ((uint32)gndUnusedC) & CC_GND_PRESHIFT_MASK) <<ADC_1_UABH_A_CC_GND_SHIFT ) |
        ( ( ((uint32)gndUnusedB) & CB_GND_PRESHIFT_MASK) <<ADC_1_UABH_A_CB_GND_SHIFT )
      ))
    );
}



/*DAC*/

/******************* ADC_1_UABH_A_SetDacModeEn() **************************/
/*!
* @brief DACMODE_EN effects how the sign bit of DAC data is used as modbit.
* 
* @details If the UAB is set to a DAC_MODE, then the SIGN_VAL bit is used as part
* of the DAC number.  The entire data word is decoded according to the DAC_MODE.
* If the UAB is not in a DAC_MODE, the SIGN_VAL bit is not computed when determining
* how to decode the data in the capacitor registers.  In either case, the modbit_src
* must be set to the firmware choice.
*
* @param isEnabled enable DAC mode
*
* @see ADC_1_UABH_A_SetDacMode()
* @see ADC_1_UABH_A_SetModbitSource()
*
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_CTRL_REG
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetDacModeEn(CyUAB_dac_mode_en_enum isEnabled)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_CTRL_PTR, 
      ADC_1_UABH_A_DAC_MODE_EN_MASK, 
      ((uint32)isEnabled), 
      ADC_1_UABH_A_DAC_MODE_EN_SHIFT
    );
}

/*************** ADC_1_UABH_A_SetDacMode() ********************************/
/*!
* @brief Sets the DAC mode.
* 
* @details The DAC can be operated as a 12-bit unsigned, 12-bit virtual signed, 
* or 13-bit unsigned DAC.  This function sets that mode.
* 
* @param dacMode DAC mode selection
*
* @see ADC_1_UABH_A_SetDacModeEn()
* @see ADC_1_UABH_A_SetModbitSource()
*
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_CTRL_REG
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetDacMode(CyUAB_dac_mode_enum dacMode)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_CTRL_PTR, 
      ADC_1_UABH_A_DAC_MODE_MASK, 
      ((uint32)dacMode), 
      ADC_1_UABH_A_DAC_MODE_SHIFT
    );    
}

/*************** ADC_1_UABH_A_SetDacNext() ********************************/
/*!
* @brief Set the next value to be converted by the DAC.
* 
* @details To make sure that the DAC loads its values at the right time, there
* is a register used as a digital buffer.  This function loads that buffer,
* which gets transferred to the capacitors during the next @c strobe signal.
* 
* @param nextDACVal buffered DAC value
*
* @see ADC_1_UABH_A_SetDacModeEn()
* @see ADC_1_UABH_A_SetDacMode()
* @see ADC_1_UABH_A_SetModbitSource()
*
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_AB_VAL_NXT_REG.
* This function is @b NOT generalized.  It depends on the 'next' values all
* being contiguous within a single register.
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetDacNext(int16 nextDACVal)
{
    /*Uses a custom mask because the operation writes over three bitfields. 
    The shift amount is the shift amount for the field that represents the LSBs*/
    
    uint32 val = ( ((uint32)nextDACVal) & ((uint32)ADC_1_UABH_A_DAC_NEXT_MASK) );
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_AB_VAL_NXT_PTR, 
      ADC_1_UABH_A_DAC_NEXT_MASK, 
      val, 
      ADC_1_UABH_A_CB_VAL_SHIFT
    );
}

/*PGA*/

/************** ADC_1_UABH_A_SetCapCFNext() *******************************/
/*!
* @brief Set the next value to be loaded into branch C and branch F capacitors.
* 
* @details To make sure that the C/F cap arrays are double-buffered, there
* is a register used as a digital buffer.  This function loads that buffer,
* which gets transferred to the capacitors during the next @c strobe signal.
* 
* @param nextCapC buffered C capacitance
* @param nextCapF buffered F capacitance
*
* @internal
* @reglist @reg ADC_1_UABH_A_CAP_CF_VAL_NXT_REG.
* This function is @b NOT generalized.  It depends on the 'next' values all
* being contiguous within a single register.
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetCapCFNext(CyUAB_cap_enum nextCapC,CyUAB_f_cap_enum nextCapF)
{
    const uint32 CF_VAL_PRESHIFT_MASK = ((uint32)(ADC_1_UABH_A_CF_VAL_MASK>>ADC_1_UABH_A_CF_VAL_SHIFT));
    const uint32 CC_VAL_PRESHIFT_MASK = ((uint32)(ADC_1_UABH_A_CC_VAL_MASK>>ADC_1_UABH_A_CC_VAL_SHIFT));
    const uint32 mask = ((uint32)ADC_1_UABH_A_CF_VAL_UPDATE_MASK) | ((uint32)ADC_1_UABH_A_CC_VAL_UPDATE_MASK) |
      ((uint32)ADC_1_UABH_A_CF_VAL_MASK) | ((uint32)ADC_1_UABH_A_CC_VAL_MASK);
    
    /* Also setting CF_VAL_UPDATE and CC_VAL_UPDATE bits */
    ADC_1_UABH_A_SET_VARIOUS_FIELDS(
      ADC_1_UABH_A_CAP_CF_VAL_NXT_PTR,
      mask,
      ((uint32)ADC_1_UABH_A_CF_VAL_UPDATE_MASK) | ((uint32)ADC_1_UABH_A_CC_VAL_UPDATE_MASK) |
        ( ( ((uint32)nextCapF) & CF_VAL_PRESHIFT_MASK)<<ADC_1_UABH_A_CF_VAL_SHIFT ) |
        ( ( ((uint32)nextCapC) & CC_VAL_PRESHIFT_MASK)<<ADC_1_UABH_A_CC_VAL_SHIFT ) 
	);
}


/* Comparator */

/*************** ADC_1_UABH_A_SetCompEdgeDetect() *************************/
/*!
* @brief Set what level of comparator activity to use to generate interrupt and
* trigger-output.
* 
* @details The comparator can be used as the source for an interrupt and/or a 
* trigger-output.  This function configures whether an interrupt is triggered, 
* and if so, whether to trigger on the comparator's rising edge, falling edge, 
* or both.  Returns @c void.
* 
* @param detectMode interrupt and trigger output comparator edge selection
*
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL_REG ADC_1_UABH_A_OA1_CTRL_REG
* @endinternal
* 
* 
* @see ADC_1_UABH_A_SetCompOutLevel()
* @see ADC_1_UABH_A_GetCompStatus()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetCompEdgeDetect(CyUAB_cmp_edge_enum detectMode)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_OA_CTRL_PTR, 
      ADC_1_UABH_A_CMP_EDGE_MASK, 
      ((uint32)detectMode), 
      ADC_1_UABH_A_CMP_EDGE_SHIFT
    );
}

/************ ADC_1_UABH_A_SetCompOutLevel ********************************/
/*!
* @brief Sets the comparator output trigger level.
* 
* @details
* 
* @internal
* @reglist @reg ADC_1_UABH_A_OA0_CTRL_REG
* @endinternal
* 
* @param isLevel
*   @arg @c 0 - Output trigger will be a pulse.
*   @arg @c 1 - Output trigger will be level.
*
* @see ADC_1_UABH_A_SetCompEdgeDetect()
* 
* @see ADC_1_UABH_A_GetCompStatus()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetCompOutLevel(CyUAB_cmp_level_enum isLevel)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_OA_CTRL_PTR, 
      ADC_1_UABH_A_CMP_DSI_LEVEL_MASK, 
      ((uint32)isLevel), 
      ADC_1_UABH_A_CMP_DSI_LEVEL_SHIFT
    );
}


/************  ADC_1_UABH_A_GetCompStatus() *******************************/
/*!
* @brief Get the output status of the Comparator.
* 
* @details Show the current comparator status output. Return type is @c uint8 an 
* unsigned 8-bit integer. It returns 1 if the current comp output is HIGH, and 
* returns 0 if current comp output is LOW
* 
* @internal
* @reglist @reg STAT0 STAT1
* @endinternal
* 
* @see ADC_1_UABH_A_SetCompEdgeDetect()
* @see ADC_1_UABH_A_SetCompOutLevel()
* 
* 
* @sideeffect None
*******************************************************************************/
uint32 ADC_1_UABH_A_GetCompStatus(void)
{
    /*GET_FIELD() has an addional shift*/
    uint32 r = (0UL != ((*(ADC_1_UABH_A_STAT_PTR)) & ADC_1_UABH_A_COMP_MASK)) ? 1UL : 0UL;
    return r;    
}


/* Switches */


/************** ADC_1_UABH_A_SetEarly() ***********************************/
/*!
* @brief Set early clock timing for specific switches
* 
* @details Applies to PS (OUT<->SUM) and PO (VOUT->OUT) switches only.
*
* @param sw_id CyUAB_SW_PS or CyUAB_SW_PO - ignores all other values of id
* @param isEarly 
* @arg CyUAB_CLK_ADJ_NOEARLY normal timing
* @arg CyUAB_CLK_ADJ_EARLY   early timing
*
* @internal
* @reglist @reg ADC_1_UABH_A_SW_STATIC0_REG or ADC_1_UABH_A_SW_STATIC1_REG
* @image html _.png 
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetEarly(CyUAB_sw_id_enum sw_id, CyUAB_clk_adj_enum isEarly)
{
    if( CyUAB_SW_PS==sw_id )
    {
        ADC_1_UABH_A_SET_FIELD(
          ADC_1_UABH_A_SW_STATIC_PTR, 
          ADC_1_UABH_A_EARLY_PS_MASK, 
          ((uint32)isEarly), 
          ADC_1_UABH_A_EARLY_PS_SHIFT
        ); 
    }
    else if( CyUAB_SW_PO==sw_id )
    {
        ADC_1_UABH_A_SET_FIELD(
          ADC_1_UABH_A_SW_STATIC_PTR, 
          ADC_1_UABH_A_EARLY_PO_MASK, 
          ((uint32)isEarly), 
          ADC_1_UABH_A_EARLY_PO_SHIFT
        );
    }
    else
    {
        /* do nothing - only 2 switches have early option */   
    }
}



/* Clocking */




/************** ADC_1_UABH_A_Run() ****************************************/
/*!
* @brief UAB clock enabling
* 
* @details sets and clears RUN bit
* The UAB clocks are not enabled by default.  Once they are enabled,
* they will either wait for a trigger (see ADC_1_UABH_A_SetInputTrigger()),
* or start immediately.
*
* Can call this immediately after calling Enable() (setting ENABLED bit) - 
* no delay required - run bit control logic handles UAB ramp up
*
* @param flag
* @arg 0 clear run bit
* @arg 1 set run bit
*
* @internal
* @reglist @reg SRAM0_CTRL @reg SRAM1_CTRL
* @image html _.png 
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_Run(uint32 flag)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_SRAM_CTRL_PTR,
      ADC_1_UABH_A_RUN_MASK, 
      flag, 
      ADC_1_UABH_A_RUN_SHIFT
    );    
}


/************** ADC_1_UABH_A_SetLastStep() ********************************/
/*!
* @brief Configure UAB-half clock width
* 
* @details The clocks can be up to 16 steps wide.  They can be configured to
* use any or all of the 16 step.  This function sets how many of the steps are
* to be used.  This width applies to all 12 clocks.  Returns @c void.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_SRAM0_CTRL_REG
* @endinternal
* 
* @param lastStep The last step desired to be used from SRAM clocks.
* Should be between @c 0 and @c 15 inclusive.
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetLastStep(uint32 lastStep)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_SRAM_CTRL_PTR, 
      ADC_1_UABH_A_LAST_STEP_MASK,
      lastStep, 
      ADC_1_UABH_A_LAST_STEP_SHIFT
    );    
}

/******** ADC_1_UABH_A_SetStartupDelay() **********************************/
/*!
* @brief Set the delay time before UAB starts running.
* 
* @details After a positive edge on the Trigger it will take STARTUP_DELAY clk half 
* cycles before the first UAB clock happens. This allows firmware to precisely align 
* the UAB output with the SAR schedule. Returns @c void.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_STARTUP_DELAY0_REG
* @endinternal
* 
* @param delayCount The number of clock cycles to delay before starting the UAB clocks. 
* A value of 0 disables this function.
* 
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetStartupDelay(uint16 delayCount)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_STARTUP_DELAY_PTR, 
      ADC_1_UABH_A_STARTUP_DELAY_MASK, 
      (uint32)delayCount, 
      ADC_1_UABH_A_STARTUP_DELAY_SHIFT
    );
}

/*********** ADC_1_UABH_A_SetAlignMode() **********************************/
/*!
* @brief Change meaning of startupDelay based on scheduled or unscheduled mode
* 
* @details 
*
* @internal
* @reglist @reg ADC_1_UABH_A_STARTUP_DELAY0_REG , ADC_1_UABH_A_STARTUP_DELAY1_REG
* @endinternal
*
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetAlignMode(CyUAB_align_mode_enum alignMode)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_STARTUP_DELAY_PTR, 
      ADC_1_UABH_A_ALIGN_MODE_MASK, 
      ((uint32)alignMode), 
      ADC_1_UABH_A_ALIGN_MODE_SHIFT
    );
}


/******** ADC_1_UABH_A_SetSubsample() *************************************/
/*!
* @brief Set the sub-sample waveform for selecting VALID signal.
* 
* @details Suppress VALID signal during the first subSampNum analog clock
* periods. Only allow VALID output in the last of the subSampNum+1 analog clock
* periods. Returns @c void.
* 
* @internal
* @reglist @reg SUBSAMPLE_CTRL0 @reg SUBSAMPLE_CTRL1
* @endinternal
* 
* @param subsample The VALID signal will be suppressed this many times.  
* A value of 0 will not suppress the VALID signal.
* 
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetSubsample(uint8 subsample)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_SUBSAMPLE_CTRL_PTR, 
      ADC_1_UABH_A_SUBSAMPLE_MASK, 
      ((uint32)subsample), 
      ADC_1_UABH_A_SUBSAMPLE_SHIFT
    );
}

/***************  ADC_1_UABH_A_SetSubsampleInit() *************************/
/*!
* @brief Set the subsampling counter value.
* 
* @details Initial value of the subsampling down counter. Before this UAB half is
* running the firmware can write to this field the initial value of the subsample
* down counter. It is recommended that the following is true for the initial value
* SUBSAMPLE_INIT <= SUBSAMPLE, however this is not a requirement. Writing a bigger
* value can be used to postpone the very first Valid output. Returns @c void.
* 
* @internal
* @reglist @reg SUBSAMPLE_CTRL0 @reg SUBSAMPLE_CTRL1
* @endinternal
* 
* @param subsampleInit: The initial value for the subsampling counter.
*
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetSubsampleInit(uint8 subsampleInit)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_SUBSAMPLE_CTRL_PTR, 
      ADC_1_UABH_A_SUBSAMPLE_INIT_MASK, 
      ((uint32)subsampleInit), 
      ADC_1_UABH_A_SUBSAMPLE_INIT_SHIFT
    );
}


/************* ADC_1_UABH_A_GetCurrentSubsample() *************************/
/*!
* @brief Get currSubsample
* 
* @details
*
*
* @internal
* @reglist @reg STAT0.CURR_SUBSAMPLE @reg STAT1.CURR_SUBSAMPLE
* @image html _.png 
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
uint32 ADC_1_UABH_A_GetCurrentSubsample(void)
{
    return ADC_1_UABH_A_GET_FIELD(
      ADC_1_UABH_A_STAT_PTR,
      ADC_1_UABH_A_CURR_SUBSAMPLE_MASK,
      ADC_1_UABH_A_CURR_SUBSAMPLE_SHIFT
    );
}

/************** ADC_1_UABH_A_GetCurrentStep() *****************************/
/*!
* @brief Get currStep
* 
* @details
*
*
* @internal
* @reglist @reg STAT0.CURR_STEP @reg STAT1.CURR_STEP
* @image html _.png 
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
uint32 ADC_1_UABH_A_GetCurrentStep(void)
{
    return ADC_1_UABH_A_GET_FIELD(
      ADC_1_UABH_A_STAT_PTR,
      ADC_1_UABH_A_CURR_STEP_MASK,
      ADC_1_UABH_A_CURR_STEP_SHIFT
    );
}


/**************** ADC_1_UABH_A_SetModbitSource() **************************/
/*!
* @brief Select source of switch control (modbit).
* 
* @details 4 of UAB clocks can use a modbit signal. This function selects the 
* source of the modbit.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_SW_MODBIT_SRC0 , ADC_1_UABH_A_SW_MODBIT_SRC1
* @endinternal
* 
* @param modbitSrcAB branch A and branch B modbit selection
* @param modbitSrcC  branch C modbit selection valid choices are:
* @arg    0    = UAB0 half 0 comparator output
* @arg    1    = UAB0 half 1 comparator output
* @arg    2    = UAB1 half 0 comparator output
* @arg    3    = UAB1 half 1 comparator output
* @arg    4    = UAB2 half 0 comparator output
* @arg    5    = UAB2 half 1 comparator output
* @arg    6    = UAB3 half 0 comparator output
* @arg    7    = UAB3 half 1 comparator output
* @arg    8-30 = generic trigger inputs 0-22
* @arg    31   = SIGN_VAL , also used as Firmware modbit. 
* (In VDAC use-case this inverts the voltage on the A and B Caps). 
* @param modbitSrcC  branch C modbit selection valid choices are:
* @arg    0    = UAB0 half 0 comparator output
* @arg    1    = UAB0 half 1 comparator output
* @arg    2    = UAB1 half 0 comparator output
* @arg    3    = UAB1 half 1 comparator output
* @arg    4    = UAB2 half 0 comparator output
* @arg    5    = UAB2 half 1 comparator output
* @arg    6    = UAB3 half 0 comparator output
* @arg    7    = UAB3 half 1 comparator output
* @arg    8-30 = generic trigger inputs 0-22
* @arg    31   = SIGN_VAL , also used as Firmware modbit.
* For PSoC4400, only values 0-1, 8-13, and 31 are valid.
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetModbitSource( uint32 modbitSrcAB, uint32 modbitSrcC )
{
    /*mask input values before shifting to prevent overlap*/
    const uint32 MODBIT_SRC_AB_PRESHIFT_MASK = ADC_1_UABH_A_MODBIT0_SRC_SEL_MASK>>ADC_1_UABH_A_MODBIT0_SRC_SEL_SHIFT;
    const uint32 MODBIT_SRC_C_PRESHIFT_MASK = ADC_1_UABH_A_MODBIT1_SRC_SEL_MASK>>ADC_1_UABH_A_MODBIT1_SRC_SEL_SHIFT;
    ADC_1_UABH_A_SET_VARIOUS_FIELDS(
      ADC_1_UABH_A_SW_MODBIT_SRC_PTR,
      ADC_1_UABH_A_MODBIT1_SRC_SEL_MASK | ADC_1_UABH_A_MODBIT0_SRC_SEL_MASK,
      (uint32)( 
        ( (modbitSrcAB & MODBIT_SRC_AB_PRESHIFT_MASK) <<ADC_1_UABH_A_MODBIT0_SRC_SEL_SHIFT ) | 
        ( (modbitSrcC &MODBIT_SRC_C_PRESHIFT_MASK) <<ADC_1_UABH_A_MODBIT1_SRC_SEL_SHIFT ) 
      )
    );    
}


/********************** ADC_1_UABH_A_SetStrobeMode ************************/
/*!
* @brief Configure whether strobe is used to load next capacitor values or 
* discharge them.
* 
* @details The strobe signal is used to time when to load the “next” value
* (in the case of DAC usage) or to discharge the capacitors (in the case of DelSig
* usage).  This function chooses which of those options the strobe is used for.
* 
* @internal
* @reglist @reg SW_STATIC0 @reg SW_STATIC1
* @endinternal
* 
* @param strobeMode
*   @arg @c 0 - Strobe will be used to load next capacitor values (for DAC)
*   @arg @c 1 - Strobe will be used to discharge capacitors
* 
* @see
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetStrobeMode(CyUAB_strobe_mode_enum strobeMode)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_SW_STATIC_PTR, 
      ADC_1_UABH_A_STRB_RST_EN_MASK, 
      ((uint32)strobeMode), 
      ADC_1_UABH_A_STRB_RST_EN_SHIFT
    );
}

/*********** ADC_1_UABH_A_SetStrobeSource *********************************/
/*!
@brief Select the trigger source that is logically ANDed with STROBE_RST waveform source.  

@details Normally, the positive edge of the STROBE_RST waveform is used to 
synchronize the time when to load the "next" caps value (in the case of DAC usage) 
or to discharge the capacitors (in the case of DelSig usage). 
When STROBE_RST is a modbitted waveform, the trigger source selected by this function 
must also be asserted. 
Returns @c void.

@internal
@reglist @reg ADC_1_UABH_A_SW_STATIC0_REG.STRB_RST0_SEL or ADC_1_UABH_A_SW_STATIC1_REG.STRB_RST1_SEL
@endinternal

@param strobeSource
* @arg    0    = UAB0 half 0 comparator output
* @arg    1    = UAB0 half 1 comparator output
* @arg    2    = UAB1 half 0 comparator output
* @arg    3    = UAB1 half 1 comparator output
* @arg    4    = UAB2 half 0 comparator output
* @arg    5    = UAB2 half 1 comparator output
* @arg    6    = UAB3 half 0 comparator output
* @arg    7    = UAB3 half 1 comparator output
* @arg    8-31 = generic trigger inputs 0-23
*
* For PSoC4400, only values 0-1 and 8-13 are valid.
*
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetStrobeSource(uint32 strobeSource)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_SW_STATIC_PTR, 
      ADC_1_UABH_A_STRB_RST_SEL_MASK, 
      strobeSource, 
      ADC_1_UABH_A_STRB_RST_SEL_SHIFT
    );
}


/************ ADC_1_UABH_A_SetFirmwareModbit() ****************************/
/*!
* @brief Set the firmware modbit.
* 
* @details This function sets the firmware modbit. The modbit affects several 
* clocks.  If firmware modbit is selected (Use ADC_1_UABH_A_SetModbitSource() choice 31),
* this value will be used.  
* 
* @see ADC_1_UABH_A_SetModbitSource()
*
* @internal
* @reglist @reg CAP_AB0_VAL_NXT_REG.SIGN0_VAL @reg CAP_AB1_VAL_NXT_REG.SIGN0_VAL
* @endinternal
*
* 
* @sideeffect The firmware modbit is also used as a "sign bit" by the
* DAC.
*******************************************************************************/
void ADC_1_UABH_A_SetFirmwareModbit(uint32 flag)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_CAP_ABCF_VAL_PTR, 
      ADC_1_UABH_A_SIGN_VAL_MASK,
      (uint32)flag, 
      ADC_1_UABH_A_SIGN_VAL_SHIFT
    );
}


/************* ADC_1_UABH_A_SetInputTrigger() *****************************/
/*!
* @brief Configure UAB-half clock starting trigger.
* 
* @details The clocks can be configured to start running when a trigger signal 
* is received.  This function chooses whether to use the trigger, and if so, 
* which trigger to use.  Trigger state is irrelevant if ADC_1_UABH_A_EnableClocks()
* has not been called.
* 
* @internal
* @reglist @reg ADC_1_UABH_A_SRAM0_CTRL_REG ADC_1_UABH_A_SRAM1_CTRL_REG
* @endinternal
* 
* @param triggerEn Enables the input trigger.  If 0, trigger signal is ignored,
* and the SRAM clocks will start running as soon as the ADC_1_UABH_A_EnableClocks()
* is invoked.  If not 0, the SRAM clocks will start running when the trigger
* signal is received.
* @param triggerSel Choice for trigger signal. Valid inputs are:
* @arg    0    = UAB0 half 0 trigger output
* @arg    1    = UAB0 half 1 trigger output
* @arg    2    = UAB1 half 0 trigger output
* @arg    3    = UAB1 half 1 trigger output
* @arg    4    = UAB2 half 0 trigger output
* @arg    5    = UAB2 half 1 trigger output
* @arg    6    = UAB3 half 0 trigger output
* @arg    7    = UAB3 half 1 trigger output
* @arg    8-30 = generic trigger inputs 0-22
* @arg    31   = SAR trigger output
*
* For PSoC4400, only values 0-1, 8-13, and 31 are valid.
*
* @see ADC_1_UABH_A_EnableClocks()
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetInputTrigger(uint32 triggerEn, uint32 triggerSel)
{
    /*mask input values before shifting to prevent overlap*/
    const uint32 TRIG_SEL_PRESHIFT_MASK = ADC_1_UABH_A_TRIG_SEL_MASK>>ADC_1_UABH_A_TRIG_SEL_SHIFT;
    const uint32 TRIGGER_EN_PRESHIFT_MASK = ADC_1_UABH_A_TRIGGER_EN_MASK>>ADC_1_UABH_A_TRIGGER_EN_SHIFT;
    ADC_1_UABH_A_SET_VARIOUS_FIELDS(
      ADC_1_UABH_A_SRAM_CTRL_PTR,
      ADC_1_UABH_A_TRIG_SEL_MASK | ADC_1_UABH_A_TRIGGER_EN_MASK,
      ( (triggerSel & TRIG_SEL_PRESHIFT_MASK) <<ADC_1_UABH_A_TRIG_SEL_SHIFT   ) | 
      ( (triggerEn & TRIGGER_EN_PRESHIFT_MASK) <<ADC_1_UABH_A_TRIGGER_EN_SHIFT )
    );
}


/****************** ADC_1_UABH_A_SetStaticSwitch() ************************/
/*!
* @brief Consistent interface for configuring static switches.
* 
* @details 
* Unpacks @p sw_id to get switch control field location (register offset and field 
* shift value) and sets that location to @p clk 
*
* @param sw_id represents a switch encoded with its reg field location
* @param clk switch setting (enum converted to single static switch bit field)
* CyUAB_SW_OPEN: open switch 
* CyUAB_SW_CLOSED and all other non-zero values: close switch 
*
* @note The exception is the two agnd and ref buffer sharing switches - 
* they are set through a different interface.
* 
* @internal
* @reglist @reg MANY
* @image html test123.png 
* @endinternal
* 
* @sideeffect None
*******************************************************************************/
void ADC_1_UABH_A_SetStaticSwitch(CyUAB_sw_id_enum sw_id, CyUAB_clk_enum clk)
{   
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_GetStaticSwAddr( (sw_id) ), 
      ADC_1_UABH_A_StaticSwMask( (sw_id) ),
      CyUAB_SwIsClosed( (clk) ), 
      ADC_1_UABH_A_StaticSwShift( (sw_id) )
    );
}


/******************** ADC_1_UABH_A_SetSwitch() ****************************/
/*!
* @brief Consistent interface for configuring anything (switches or otherwise) 
* that can select one of the 12 UAB clocks or can be statically set open or closed.
* 
* @details 
* Unpacks @p sw_id to get switch control field location (register offset and field 
* shift value) and sets that location to @p clk.
*
* @param sw_id represents a switch encoded with its reg field location
* @param clk switch setting
* 
* @internal
* @reglist @reg MANY
* @image html test123.png 
* @endinternal
* 
* @sideeffect None
*//*==========================================================================*/
void ADC_1_UABH_A_SetSwitch(CyUAB_sw_id_enum sw_id, CyUAB_clk_enum clk)
{
    ADC_1_UABH_A_SET_FIELD(
      ADC_1_UABH_A_GetDynamicSwAddr( (sw_id) ),
      ADC_1_UABH_A_DynamicSwMask( (sw_id) ),
      ((uint32)((clk))), 
      ADC_1_UABH_A_DynamicSwShift( (sw_id) )
    ); 
}

/* [] END OF FILE */

