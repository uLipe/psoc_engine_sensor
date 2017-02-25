/*!*****************************************************************************
* \file engine_sensor_adc_UABH_A.h
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

#if !defined(engine_sensor_adc_UABH_A_H)
#define engine_sensor_adc_UABH_A_H

#include "cytypes.h"
#include "engine_sensor_adc_UABH_A_CyUAB_types.h"
#include "engine_sensor_adc_UABH_A_CyUAB.h"
#include "engine_sensor_adc_UABH_A_regs.h"


/* Switch function implementation */

/* Dynamic and Static Switch control field shift and mask values */

/* sw_id:= switch identifier - See CyUAB_sw_id_enum -
values are not arbitrary - they are packed with:
register address offset, 
the switch control field shift value, and 
boolean "x" flag for switches that interact with the x inputs */

/* The x inputs are an abstract concept of analog inputs of the UABPRIM that 
PSoC Creator P&R maps to the underlying UAB hardware's vin analog inputs -
this shuffling of the inputs give the analog router more freedom */

/* Switch IDs that have the x flag set are switches that connect to the x inputs */

/* x input field shift value:= abstract UABPRIM instance x analog input switch field shift value (0,4,8,12) */    
/* x input index:= abstract UABPRIM instance x input switch number (0...3) */
/* vin input index:= underlying hardware UAB vin input switch number (0...3)  */
/* vin input field shift value:= underlying hardware UAB vin input switch field shift value (0,4,8,12) */

/* conversion process with nested macros: 
sw_id -> x input field shift value -> x input index -> vin input index -> vin input field shift value */   






/* Static switch control fields occupy 1 bit to configure statically open or statically closed. */
#define engine_sensor_adc_UABH_A_STATIC_PRESHIFT_MASK  1UL
/* Dynamic switch control fields occupy 4 bits to select one of twelve waveforms, statically open, or statically closed */
#define engine_sensor_adc_UABH_A_DYNAMIC_PRESHIFT_MASK 0xfUL

/* Spacing between the LSbit of each static switch field */
/* needed when converting between the field shift location and the number of the shuffled x analog inputs */
#define engine_sensor_adc_UABH_A_STATIC_FIELD_SIZE  1UL

/* Spacing between the LSbit of each dynamic switch field */
/* needed when converting between the field shift location and the number of the shuffled x analog inputs */
#define engine_sensor_adc_UABH_A_DYNAMIC_FIELD_SIZE 4UL


/*Macros*/

/* Find UAB vin input index from UABPRIM x input index with cyfitter.h mappings */
#if !defined(engine_sensor_adc_UABH_A_Vin)
#define engine_sensor_adc_UABH_A_Vin(xIndex) (\
    (0UL==(xIndex))? ((uint32)engine_sensor_adc_UABH_A_X0) : (\
    (1UL==(xIndex))? ((uint32)engine_sensor_adc_UABH_A_X1) : (\
    (2UL==(xIndex))? ((uint32)engine_sensor_adc_UABH_A_X2) : (\
                   ((uint32)engine_sensor_adc_UABH_A_X3) \
))))
#endif
    
/* static switch, get x input index from switch id by down-scaling the x input field shift value by the field size */
#define engine_sensor_adc_UABH_A_StaticXin(sw_id)     ( CyUAB_GetSwShift((sw_id)) / engine_sensor_adc_UABH_A_STATIC_FIELD_SIZE )    
    
/* static switch, get the vin input field shift value by converting x input index to vin input index and up-scaling by the field size */
#define engine_sensor_adc_UABH_A_StaticVShift(sw_id)  ( engine_sensor_adc_UABH_A_Vin( engine_sensor_adc_UABH_A_StaticXin((sw_id)) ) * engine_sensor_adc_UABH_A_STATIC_FIELD_SIZE )
/* static switch, if id refers to an x input, handle the shuffling, otherwise just unpack the field shift from id */
#define engine_sensor_adc_UABH_A_StaticSwShift(sw_id)   ( CyUAB_IsSwX((sw_id)) ? engine_sensor_adc_UABH_A_StaticVShift((sw_id)) : CyUAB_GetSwShift((sw_id)) )
/* static switch, post shift mask */
#define engine_sensor_adc_UABH_A_StaticSwMask(sw_id)    ( engine_sensor_adc_UABH_A_STATIC_PRESHIFT_MASK<<engine_sensor_adc_UABH_A_StaticSwShift((sw_id)) )

/* static switch address */
#define engine_sensor_adc_UABH_A_GetStaticSwAddr(sw_id)  ( (reg32*)( ((uint32)engine_sensor_adc_UABH_A_BASE_ADDR) + ((uint32)(CyUAB_GetSwAddr((sw_id)) )) ) )
    

/* dynamic switch, get x input index from switch id by down-scaling the x input field shift value by the field size */
#define engine_sensor_adc_UABH_A_DynamicXin(sw_id)    ( CyUAB_GetSwShift((sw_id)) / engine_sensor_adc_UABH_A_DYNAMIC_FIELD_SIZE )
/* dynamic switch, get the vin input field shift value by converting x input index to vin input index and up-scaling by the field size */
#define engine_sensor_adc_UABH_A_DynamicVShift(sw_id) ( engine_sensor_adc_UABH_A_Vin( engine_sensor_adc_UABH_A_DynamicXin((sw_id)) ) * engine_sensor_adc_UABH_A_DYNAMIC_FIELD_SIZE )
/* dynamic switch, if id refers to an x input, handle the shuffling, otherwise just unpack the field shift from id */
#define engine_sensor_adc_UABH_A_DynamicSwShift(sw_id)  ( CyUAB_IsSwX((sw_id)) ? engine_sensor_adc_UABH_A_DynamicVShift((sw_id)) : CyUAB_GetSwShift((sw_id)) )
/* dynamic switch, post shift mask */
#define engine_sensor_adc_UABH_A_DynamicSwMask(sw_id)   ( engine_sensor_adc_UABH_A_DYNAMIC_PRESHIFT_MASK<<engine_sensor_adc_UABH_A_DynamicSwShift((sw_id)) )

/* dynamic switch address - handle SW_AA, SW_BB, and SW_CC */
#define engine_sensor_adc_UABH_A_GetDynamicSwAddr(sw_id)  ( (CyUAB_SW_AA==(sw_id)) ? engine_sensor_adc_UABH_A_SW_AA_PTR : (\
    (CyUAB_SW_BB==(sw_id)) ? engine_sensor_adc_UABH_A_SW_BB_PTR : ( \
    (CyUAB_SW_CC==(sw_id)) ? engine_sensor_adc_UABH_A_SW_CC_PTR : ( \
    ( (reg32*)( ((uint32)engine_sensor_adc_UABH_A_BASE_ADDR) + ((uint32)(CyUAB_GetSwAddr((sw_id)) )) ) ) \
) ) ) )



#include "engine_sensor_adc_UABH_A_param.h"


/*! Calculate waveConfig array size */
#define engine_sensor_adc_UABH_A_NUM_STEPS ( (uint8)( \
(engine_sensor_adc_UABH_A_INC_STEP_0  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_1  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_2  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_3  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_4  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_5  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_6  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_7  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_8  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_9  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_10 ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_11 ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_12 ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_13 ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_14 ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_INC_STEP_15 ? 1UL : 0UL) ) )

/*! initPairs array index of default OA_CTRL */
#define engine_sensor_adc_UABH_A_IDX_OA_CTRL       (0UL)
/*! initPairs array index of default SW_STATIC */
#define engine_sensor_adc_UABH_A_IDX_SW_STATIC     (1UL)
/*! initPairs array index of default SW_MODBIT_SRC */
#define engine_sensor_adc_UABH_A_IDX_SW_MODBIT_SRC (2UL)
/*! initPairs array index of default SRAM_CTRL */
#define engine_sensor_adc_UABH_A_IDX_SRAM_CTRL     (3UL)

/*! Calculate initPairs array size*/
#define engine_sensor_adc_UABH_A_INIT_PAIRS_COUNT ( \
(engine_sensor_adc_UABH_A_NONZERO_OA_CTRL        ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_STATIC      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_MODBIT_SRC  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SRAM_CTRL      ? 1UL : 0UL) + \
  \
(engine_sensor_adc_UABH_A_NONZERO_INTR_MASK      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_CAP_CTRL       ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_CAP_ABCF_VAL   ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_CAP_AB_VAL_NXT ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_CAP_CF_VAL_NXT ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_STARTUP_DELAY  ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SUBSAMPLE_CTRL ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CA_IN0      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CA_IN1      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CA_TOP      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CB_IN0      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CB_IN1      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CB_TOP      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CC_IN0      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CC_IN1      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CC_TOP      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_CF_BOT      ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_OTHER       ? 1UL : 0UL) + \
(engine_sensor_adc_UABH_A_NONZERO_SW_BOOST_CTRL  ? 1UL : 0UL) \
)

/***************************************
*    Variables with External Linkage
***************************************/
/*!
* \addtogroup group_globals
* Globals are noted in the descriptions of the functions that use globals.
* They are marked with (R), (W), or (RW) noting whether the variable is read,
* write, or read/write.
* @{
*/
/*! Tracks whether block is initialized (1) or not (0). */
extern uint32 engine_sensor_adc_UABH_A_initVar;
extern CyUAB_config engine_sensor_adc_UABH_A_config;
extern uint16 engine_sensor_adc_UABH_A_waveConfig[engine_sensor_adc_UABH_A_NUM_STEPS];
extern CyUAB_reg_pair engine_sensor_adc_UABH_A_initPairs[engine_sensor_adc_UABH_A_INIT_PAIRS_COUNT];


/*! @} globals */

/*------------------ Function Prototypes -------------------------------------*/


    
/*!
* \addtogroup group_init
* @{
*/    
void engine_sensor_adc_UABH_A_Start(void);
void engine_sensor_adc_UABH_A_Stop(void);
void engine_sensor_adc_UABH_A_Init(const CyUAB_config* cfg);
void engine_sensor_adc_UABH_A_Enable(void);


/*! @} group_init */

/* Support function for engine_sensor_adc_UABH_A_Init()
prototyp here for MISRA compliance - exclude from group_init */
void engine_sensor_adc_UABH_A_WriteInitPairs(const CyUAB_reg_pair pairs[], size_t n);

/*!
* \addtogroup group_interrupts
* @{
*/ 
void engine_sensor_adc_UABH_A_ClearInterrupt(CyUAB_intr_enum intr);
void engine_sensor_adc_UABH_A_SetInterrupt(CyUAB_intr_enum intr);
void engine_sensor_adc_UABH_A_SetInterruptMask(CyUAB_intr_enum intr);
void engine_sensor_adc_UABH_A_ClearInterruptMask(CyUAB_intr_enum intr);
uint32 engine_sensor_adc_UABH_A_GetInterruptIsMasked(CyUAB_intr_enum intr);
/*! @} interrupts */

/*!
* \addtogroup group_power
* @{
*/
void engine_sensor_adc_UABH_A_SetUABPower(CyUAB_coarse_pwr_enum powerLevel);
void engine_sensor_adc_UABH_A_SetOAPower(CyUAB_fine_pwr_enum powerLevel);
void engine_sensor_adc_UABH_A_SetCompPower(CyUAB_fine_pwr_enum powerLevel);
void engine_sensor_adc_UABH_A_SetRefPower(CyUAB_fine_pwr_enum powerLevel);
void engine_sensor_adc_UABH_A_SetAgndPower(CyUAB_fine_pwr_enum powerLevel);
/** @} power */

/*!
* \addtogroup group_ref
* @{
*/
void engine_sensor_adc_UABH_A_SetRefVdda(CyUAB_ref_force_vdda_enum forceVdda);
void engine_sensor_adc_UABH_A_SetAgndVdda(CyUAB_agnd_force_vdda_enum forceVdda);

void engine_sensor_adc_UABH_A_SetRefTied( CyUAB_ref_tied_enum refTied);
void engine_sensor_adc_UABH_A_SetAgndTied(CyUAB_agnd_tied_enum agndTied);
/*! @} vref */

/*!
* \addtogroup group_caps
* @{
*/
void engine_sensor_adc_UABH_A_SetCapA(CyUAB_cap_enum   capA);
void engine_sensor_adc_UABH_A_SetCapB(CyUAB_b_cap_enum capB);
void engine_sensor_adc_UABH_A_SetCapC(CyUAB_cap_enum   capC);
void engine_sensor_adc_UABH_A_SetCapF(CyUAB_f_cap_enum capF);
void engine_sensor_adc_UABH_A_SetCaps(CyUAB_cap_enum capA, CyUAB_b_cap_enum capB, 
    CyUAB_cap_enum capC, CyUAB_f_cap_enum capF);
void engine_sensor_adc_UABH_A_SetGroundUnused(CyUAB_gnd_unused_enum gndUnusedB, CyUAB_gnd_unused_enum gndUnusedC );


/*! @} caps */

/*!
* \addtogroup group_dac
* @{
*/
void engine_sensor_adc_UABH_A_SetDacModeEn(CyUAB_dac_mode_en_enum isEnabled);
void engine_sensor_adc_UABH_A_SetDacMode(CyUAB_dac_mode_enum dacMode);

void engine_sensor_adc_UABH_A_SetDacNext(int16 nextDACVal);
/** @} dac */

/*!
* \addtogroup group_pga
* @{
*/
void engine_sensor_adc_UABH_A_SetCapCFNext(CyUAB_cap_enum nextCapC,
    CyUAB_f_cap_enum nextCapF);
/*! Maps gain ratio to appropriate capacitance function parameters */
#define engine_sensor_adc_UABH_A_SetPGAGain(NUMERATOR,DENOMINATOR) \
  (CyUAB_SetCapCFNext((NUMERATOR),(DENOMINATOR)))
/** @} pga */

/*!
* \addtogroup group_comparator
* @{
*/
void engine_sensor_adc_UABH_A_SetCompEdgeDetect(CyUAB_cmp_edge_enum detectMode);
void engine_sensor_adc_UABH_A_SetCompOutLevel(CyUAB_cmp_level_enum isLevel);
uint32 engine_sensor_adc_UABH_A_GetCompStatus(void);
/*! @} comparator */


/*!
* \addtogroup group_switches
* @{
*/
void engine_sensor_adc_UABH_A_SetStaticSwitch( CyUAB_sw_id_enum sw_id, CyUAB_clk_enum clk);
void engine_sensor_adc_UABH_A_SetSwitch(CyUAB_sw_id_enum sw_id, CyUAB_clk_enum clk);

/*! Select B branch attenuation bypass switch waveform */
#define engine_sensor_adc_UABH_A_SetAttenBypassSwitchB(clk) engine_sensor_adc_UABH_A_SetSwitch(CyUAB_SW_TB,(clk))
/*! Select C branch attenuation bypass switch waveform */
#define engine_sensor_adc_UABH_A_SetAttenBypassSwitchC(clk) engine_sensor_adc_UABH_A_SetSwitch(CyUAB_SW_TC,(clk))

/*! Select Comparator flip-flop clock */
#define engine_sensor_adc_UABH_A_SetCompoutFFClock(clk) engine_sensor_adc_UABH_A_SetSwitch(CyUAB_SW_CMP_FF,(clk))
/*! Select VALID waveform */
#define engine_sensor_adc_UABH_A_SetValidClock(clk)     engine_sensor_adc_UABH_A_SetSwitch(CyUAB_SW_VALID, (clk))
/*! Select Output trigger waveform */
#define engine_sensor_adc_UABH_A_SetTrigClock(clk)      engine_sensor_adc_UABH_A_SetSwitch(CyUAB_SW_TRIG_OUT,  (clk))

/*! Strobe anytime */
#define engine_sensor_adc_UABH_A_STROBE_UPDATE_ANYTIME engine_sensor_adc_UABH_A_DYNAMIC_SWITCH_CLOSED
/*! Select strobe waveform */
#define engine_sensor_adc_UABH_A_SetStrobeClock(clk)    engine_sensor_adc_UABH_A_SetSwitch(CyUAB_SW_STROBE_RST,(clk))

void engine_sensor_adc_UABH_A_SetEarly(CyUAB_sw_id_enum sw_id, CyUAB_clk_adj_enum isEarly);

/*! @} switches */

/*!
* \addtogroup group_clocking
* @{
*/

void engine_sensor_adc_UABH_A_Run(uint32 flag);
/*! Enable clocking of already configured UAB half */
#define engine_sensor_adc_UABH_A_EnableClocks()  engine_sensor_adc_UABH_A_Run(1UL)
/*! Disable clocking of UAB half */
#define engine_sensor_adc_UABH_A_DisableClocks() engine_sensor_adc_UABH_A_Run(0UL)

void engine_sensor_adc_UABH_A_SetLastStep(uint32 lastStep);

void engine_sensor_adc_UABH_A_SetStartupDelay(uint16 delayCount);
void engine_sensor_adc_UABH_A_SetAlignMode(CyUAB_align_mode_enum alignMode);
void engine_sensor_adc_UABH_A_SetSubsample(uint8 subsample);
void engine_sensor_adc_UABH_A_SetSubsampleInit(uint8 subsampleInit);

uint32 engine_sensor_adc_UABH_A_GetCurrentSubsample(void);
uint32 engine_sensor_adc_UABH_A_GetCurrentStep(void);

void engine_sensor_adc_UABH_A_SetModbitSource( uint32 modbitSrcAB, uint32 modbitSrcC );

void engine_sensor_adc_UABH_A_SetStrobeMode(CyUAB_strobe_mode_enum strobeMode);
void engine_sensor_adc_UABH_A_SetStrobeSource(uint32 strobeSource);

void engine_sensor_adc_UABH_A_SetFirmwareModbit(uint32 flag);

void engine_sensor_adc_UABH_A_SetInputTrigger(uint32 triggerEn, uint32 triggerSel );

/*! Clear all clock waveform memory */
#define engine_sensor_adc_UABH_A_ClearAllClocks() CyUAB_wordset(\
    (engine_sensor_adc_UABH_A_SRAM0_PTR), \
    0UL,\
    (CyUAB_STEPS_LEN_MAX*sizeof(uint32)) \
)

/*! Set all steps for a single clock phi; 
@param phi clock 1-12
@param pattern PHI1 to PHI12 waveform steps; uint16 where step0 is LSbit and step15 is MSbit; 
@param modbitPattern PHI9 to PHI12 modbit waveform steps; uint16 where step0 is LSbit and step15 is MSbit */
#define engine_sensor_adc_UABH_A_SetClock(phi,pattern,modbitPattern)  \
  CyUAB_SetClock(engine_sensor_adc_UABH_A_SRAM0_PTR,(phi),(pattern),(modbitPattern))

/*! Set multiple steps for all clocks 
@param len number of steps
@param stepArray array of steps */
#define engine_sensor_adc_UABH_A_SetNSteps(len,stepArray)  \
  CyUAB_SetNSteps(engine_sensor_adc_UABH_A_SRAM0_PTR,(len),(stepArray))

/*! Set single step for all clocks
@param idx index of step to write
@param stepVal value of step */
#define engine_sensor_adc_UABH_A_SetSingleStep(idx,stepVal)  \
  CyUAB_SetSingleStep(engine_sensor_adc_UABH_A_SRAM0_PTR,(idx),(stepVal))

/*! @} group_clocking */




#endif /* #if !defined(engine_sensor_adc_UABH_A_H) */

/* [] END OF FILE */
