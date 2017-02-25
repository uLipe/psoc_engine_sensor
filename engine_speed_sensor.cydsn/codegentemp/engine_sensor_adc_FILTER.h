/***************************************************************************//**
* \file     engine_sensor_adc_FILTER.c
* \version  1.20
*
* \brief
* Provides filter defines to the API for the engine_sensor_adc Component.
*
********************************************************************************
* \copyright
* (c) 2015-2016, Cypress Semiconductor Corporation. All rights reserved.
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

#if !defined(CY_engine_sensor_adc_FILTER_H)
    #define CY_engine_sensor_adc_FILTER_H

    
#define engine_sensor_adc_FILTER_CFG0_FILTER_PRESENT          (1uL)
#define engine_sensor_adc_FILTER_CFG1_FILTER_PRESENT          (0uL)
#define engine_sensor_adc_FILTER_CFG2_FILTER_PRESENT          (0uL)
#define engine_sensor_adc_FILTER_CFG3_FILTER_PRESENT          (0uL)
	
#define engine_sensor_adc_FILTER_ANY_CONFIG_USES_FILTER       ( engine_sensor_adc_FILTER_CFG0_FILTER_PRESENT \
                                                             | engine_sensor_adc_FILTER_CFG1_FILTER_PRESENT \
                                                             | engine_sensor_adc_FILTER_CFG2_FILTER_PRESENT \
                                                             | engine_sensor_adc_FILTER_CFG3_FILTER_PRESENT \
                                                             )
	

#if(engine_sensor_adc_FILTER_ANY_CONFIG_USES_FILTER	!= 0u)	
    
#include "engine_sensor_adc_UABH_A_CyUAB_types.h"
#include "engine_sensor_adc_UABH_A_CyUAB_regs.h"
#include "engine_sensor_adc_UABH_A_CyUAB.h"
#include "engine_sensor_adc_UABH_A_param.h"
#include "engine_sensor_adc_UABH_B_param.h"
#include "engine_sensor_adc_UABH_A_regs.h"
#include "engine_sensor_adc_UABH_B_regs.h"
#include "engine_sensor_adc_UABH_A.h"
#include "engine_sensor_adc_UABH_B.h"

/*******************************************************************************
* Filter function prototypes
*******************************************************************************/
void engine_sensor_adc_TrimFilterVos(void);
void engine_sensor_adc_filterInit(uint32 configNum);

/*******************************************************************************
* Filter trim constants and macros
*******************************************************************************/
#define engine_sensor_adc_OPAMP_TRIM_POS_BASE     (0x00uL)
#define engine_sensor_adc_OPAMP_TRIM_POS_LIMIT    (0x08uL)
#define engine_sensor_adc_OPAMP_TRIM_NEG_BASE     (engine_sensor_adc_OPAMP_TRIM_POS_LIMIT)
#define engine_sensor_adc_OPAMP_TRIM_NEG_LIMIT    (0x10uL)
#define engine_sensor_adc_OPAMP_TRIM_MASK         (0x0fuL)
    
#define engine_sensor_adc_AGND_TRIM_POS_BASE      (0x00uL)
#define engine_sensor_adc_AGND_TRIM_POS_LIMIT     (0x10uL)
#define engine_sensor_adc_AGND_TRIM_NEG_BASE      (engine_sensor_adc_AGND_TRIM_POS_LIMIT)
#define engine_sensor_adc_AGND_TRIM_NEG_LIMIT     (0x20uL)
#define engine_sensor_adc_AGND_TRIM_MASK          (0x1fuL)

/*******************************************************************************
* Filter Parameters
*******************************************************************************/
#define engine_sensor_adc_FILTERTOPOLOGY_HIGH_Q  (0u)
#define engine_sensor_adc_FILTERTOPOLOGY_LOW_Q   (1u)
    
#define engine_sensor_adc_TRANSFERTYPE_LOW_PASS (0u)
#define engine_sensor_adc_TRANSFERTYPE_HIGH_PASS (1u)
#define engine_sensor_adc_TRANSFERTYPE_BAND_PASS (2u)
#define engine_sensor_adc_TRANSFERTYPE_BAND_STOP (3u)


#define engine_sensor_adc_UABH_A_INVAR_SRAM_CTRL        ((uint32)((uint32)1u << CyUAB_TRIGGER_EN_SHIFT) \
                                                    |  (uint32)((uint32)31u << CyUAB_TRIG_SEL_SHIFT)   \
                                                    |  (uint32)((uint32)1u << CyUAB_LAST_STEP_SHIFT))
#define engine_sensor_adc_UABH_B_INVAR_SRAM_CTRL        ((uint32)((uint32)1u << CyUAB_TRIGGER_EN_SHIFT) \
                                                    |  (uint32)((uint32)31u << CyUAB_TRIG_SEL_SHIFT)   \
                                                    |  (uint32)((uint32)1u << CyUAB_LAST_STEP_SHIFT))
#define engine_sensor_adc_UABH_A_INVAR_SW_MODBIT_SRC    ((31uL << CyUAB_MODBIT0_SRC_SEL_SHIFT) \
                                                    |  (31uL << CyUAB_MODBIT1_SRC_SEL_SHIFT))
#define engine_sensor_adc_UABH_B_INVAR_SW_MODBIT_SRC    ((31uL << CyUAB_MODBIT0_SRC_SEL_SHIFT) \
                                                    |  (31uL << CyUAB_MODBIT1_SRC_SEL_SHIFT))


/*******************************************************************************
* Low-Q definitions
*******************************************************************************/

#define engine_sensor_adc_UABH_A_LOWQSTAT_SW_CA_IN0 (CyUAB_SW_CLOSED << CyUAB_SW_AP_SHIFT)
#define engine_sensor_adc_UABH_A_LOWQSTAT_SW_CA_TOP (CyUAB_SW_CLOSED << CyUAB_SW_SA_SHIFT)
#define engine_sensor_adc_UABH_A_LOWQSTAT_SW_CC_IN0 (CyUAB_CLK_PHI1  << CyUAB_SW_CQ_SHIFT)
#define engine_sensor_adc_UABH_A_LOWQSTAT_SW_CC_IN1 (CyUAB_CLK_PHI2  << CyUAB_SW_CG_MODBIT_SHIFT)
#define engine_sensor_adc_UABH_A_LOWQSTAT_SW_CF_BOT (CyUAB_SW_CLOSED << CyUAB_SW_PF_SHIFT)
#define engine_sensor_adc_UABH_B_LOWQSTAT_SW_CA_IN0 (CyUAB_CLK_PHI2  << CyUAB_SW_AP_SHIFT)
#define engine_sensor_adc_UABH_B_LOWQSTAT_SW_CA_IN1 (CyUAB_CLK_PHI1  << CyUAB_SW_AG_MODBIT_SHIFT)
#define engine_sensor_adc_UABH_B_LOWQSTAT_SW_CA_TOP ((CyUAB_CLK_PHI2  << CyUAB_SW_SA_SHIFT) \
                                                 | (CyUAB_CLK_PHI1  << CyUAB_SW_GA_MODBIT_SHIFT))
#define engine_sensor_adc_UABH_B_LOWQSTAT_SW_CB_IN0 (CyUAB_CLK_PHI1  << CyUAB_SW_BQ_SHIFT)
#define engine_sensor_adc_UABH_B_LOWQSTAT_SW_CB_IN1 (CyUAB_CLK_PHI2  << CyUAB_SW_BG_MODBIT_SHIFT)
#define engine_sensor_adc_UABH_B_LOWQSTAT_SW_CB_TOP ((CyUAB_CLK_PHI2 << CyUAB_SW_SB_SHIFT) \
                                                 | (CyUAB_CLK_PHI1  << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                 | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
#define engine_sensor_adc_UABH_B_LOWQSTAT_SW_CC_IN0 ((uint32)CyUAB_CLK_PHI12 << (engine_sensor_adc_UABH_B_halfuab__X0 << 2u))
#define engine_sensor_adc_UABH_B_LOWQSTAT_SW_CC_IN1 (CyUAB_CLK_PHI11 << CyUAB_SW_CG_MODBIT_SHIFT)
#define engine_sensor_adc_UABH_B_LOWQSTAT_SW_CF_BOT ((CyUAB_SW_CLOSED << CyUAB_SW_PF_SHIFT) \
                                                 |  (CyUAB_CLK_PHI3  << CyUAB_SW_PO_SHIFT))

/*******************************************************************************
* High-Q definitions
*******************************************************************************/

#define engine_sensor_adc_UABH_A_HIGHQSTAT_SW_CA_IN0 (CyUAB_SW_CLOSED << CyUAB_SW_AQ_SHIFT)
#define engine_sensor_adc_UABH_A_HIGHQSTAT_SW_CA_TOP (CyUAB_SW_CLOSED << CyUAB_SW_SA_SHIFT)
#define engine_sensor_adc_UABH_A_HIGHQSTAT_SW_CB_IN0 (CyUAB_CLK_PHI1 << CyUAB_SW_BQ_SHIFT)
#define engine_sensor_adc_UABH_A_HIGHQSTAT_SW_CB_IN1 (CyUAB_CLK_PHI2 << CyUAB_SW_BG_MODBIT_SHIFT)
#define engine_sensor_adc_UABH_A_HIGHQSTAT_SW_CC_IN0 (CyUAB_CLK_PHI12 << (engine_sensor_adc_UABH_A_halfuab__X0 << 2u))
#define engine_sensor_adc_UABH_A_HIGHQSTAT_SW_CC_IN1 (CyUAB_CLK_PHI11 << CyUAB_SW_CG_MODBIT_SHIFT)
#define engine_sensor_adc_UABH_A_HIGHQSTAT_SW_CC_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT) \
                                                |    (CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT))
#define engine_sensor_adc_UABH_A_HIGHQSTAT_SW_CF_BOT (CyUAB_SW_CLOSED << CyUAB_SW_PF_SHIFT)
#define engine_sensor_adc_UABH_B_HIGHQSTAT_SW_CA_IN0 (CyUAB_CLK_PHI1 << CyUAB_SW_AQ_SHIFT)
#define engine_sensor_adc_UABH_B_HIGHQSTAT_SW_CA_IN1 (CyUAB_CLK_PHI2 << CyUAB_SW_AG_MODBIT_SHIFT)
#define engine_sensor_adc_UABH_B_HIGHQSTAT_SW_CA_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_GA_MODBIT_SHIFT) \
                                                |    (CyUAB_CLK_PHI2 << CyUAB_SW_SA_SHIFT))

#define engine_sensor_adc_UABH_B_HIGHQSTAT_SW_CB_IN0 (CyUAB_CLK_PHI12 << (engine_sensor_adc_UABH_B_halfuab__X0 << 2u))
#define engine_sensor_adc_UABH_B_HIGHQSTAT_SW_CB_IN1 (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)

#define engine_sensor_adc_UABH_B_HIGHQSTAT_SW_CC_IN0 (CyUAB_CLK_PHI10 << (engine_sensor_adc_UABH_B_halfuab__X0 << 2u))
#define engine_sensor_adc_UABH_B_HIGHQSTAT_SW_CC_IN1 (CyUAB_CLK_PHI9 << CyUAB_SW_CG_MODBIT_SHIFT)

#define engine_sensor_adc_UABH_B_HIGHQSTAT_SW_CF_BOT ((CyUAB_SW_CLOSED << CyUAB_SW_PF_SHIFT) \
                                                 |   (CyUAB_CLK_PHI3  << CyUAB_SW_PO_SHIFT))


/*******************************************************************************
* CFG0 definitions
*******************************************************************************/
#if (0u != engine_sensor_adc_FILTER_CFG0_FILTER_PRESENT)
    
    #define engine_sensor_adc_CFG0_FILTERTYPE_USED   engine_sensor_adc_FILTERTOPOLOGY_HIGH_Q
    #define engine_sensor_adc_CFG0_TRANSFERTYPE_0   engine_sensor_adc_FILTERTOPOLOGY_BAND_PASS
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define engine_sensor_adc_CFG0_FILTER_GT_C1_NUMERATOR_VAL    (0ul)
    #define engine_sensor_adc_CFG0_FILTER_GT_C1_DENOMINATOR_VAL  (1ul)
    #define engine_sensor_adc_CFG0_FILTER_GT_C2_NUMERATOR_VAL    (5ul)
    #define engine_sensor_adc_CFG0_FILTER_GT_C2_DENOMINATOR_VAL  (1ul) 
    #define engine_sensor_adc_CFG0_FILTER_GT_C3_VAL              (10ul)      
    #define engine_sensor_adc_CFG0_FILTER_GT_C4_VAL              (16ul)      
    #define engine_sensor_adc_CFG0_FILTER_GT_Cp_VAL              (12ul)      
    #define engine_sensor_adc_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL   (1ul)  
    #define engine_sensor_adc_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL (1ul)  
    #define engine_sensor_adc_CFG0_FILTER_GT_CA_VAL              (58ul)      
    #define engine_sensor_adc_CFG0_FILTER_GT_CB_VAL              (54ul)     

    #define engine_sensor_adc_CFG0_FILTER_IDEAL_BIQUAD_NUM0      (-0.0255177166425601)
    #define engine_sensor_adc_CFG0_FILTER_IDEAL_BIQUAD_NUM1      (0)
    #define engine_sensor_adc_CFG0_FILTER_IDEAL_BIQUAD_NUM2      (0.0255177166425601)
    #define engine_sensor_adc_CFG0_FILTER_IDEAL_BIQUAD_DEN0      (0.94896456671488)
    #define engine_sensor_adc_CFG0_FILTER_IDEAL_BIQUAD_DEN1      (-1.9329532794814)
    #define engine_sensor_adc_CFG0_FILTER_IDEAL_BIQUAD_DEN2      (1)

    #define engine_sensor_adc_CFG0_FILTER_UAB_BIQUAD_NUM0        (-0.0197956577266922)
    #define engine_sensor_adc_CFG0_FILTER_UAB_BIQUAD_NUM1        (0.00127713920817369)
    #define engine_sensor_adc_CFG0_FILTER_UAB_BIQUAD_NUM2        (0.0185185185185185)
    #define engine_sensor_adc_CFG0_FILTER_UAB_BIQUAD_DEN0        (0.948914431673052)
    #define engine_sensor_adc_CFG0_FILTER_UAB_BIQUAD_DEN1        (-1.93295019157088)
    #define engine_sensor_adc_CFG0_FILTER_UAB_BIQUAD_DEN2        (1)
    
    #define engine_sensor_adc_CFG0_UABH_A_STARTUP_DELAY    ((uint32)((uint32)109u << CyUAB_STARTUP_DELAY_SHIFT))
    #define engine_sensor_adc_CFG0_UABH_B_STARTUP_DELAY    ((uint32)((uint32)109u << CyUAB_STARTUP_DELAY_SHIFT))
    
    #if (engine_sensor_adc_CFG0_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < engine_sensor_adc_CFG0_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == engine_sensor_adc_CFG0_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(engine_sensor_adc_CFG0_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == engine_sensor_adc_CFG0_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(engine_sensor_adc_CFG0_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(engine_sensor_adc_CFG0_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_F_VAL_PRE (engine_sensor_adc_CFG0_FILTER_GT_CA_VAL/4u)
        #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((engine_sensor_adc_CFG0_FILTER_GT_CA_VAL - (2u * (engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_ABCF_VAL ((engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define engine_sensor_adc_CFG0_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG0_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(engine_sensor_adc_CFG0_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT))          \
                                                       | (uint32)(engine_sensor_adc_CFG0_FILTER_GT_C4_VAL            << CyUAB_CA_VAL_SHIFT)    \
                                                       | (uint32)(engine_sensor_adc_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)  \
                                                       | (uint32)((uint32)((engine_sensor_adc_CFG0_FILTER_GT_CB_VAL / 2u) - 1u)  << CyUAB_CF_VAL_SHIFT))


        #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_CAP_CTRL ((((engine_sensor_adc_CFG0_FILTER_GT_C1_NUMERATOR_VAL > 0u)      \
                                                           && (engine_sensor_adc_CFG0_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT)                                              \
                                                            : 0u)                                                     \
                                                         | ((engine_sensor_adc_CFG0_FILTER_GT_C2_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                              \
                                                            : 0u))
        #if (engine_sensor_adc_CFG0_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_SW_CB_IN0    ((uint32)CyUAB_CLK_PHI10 << (engine_sensor_adc_UABH_A_halfuab__X0 << 2u))
            #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_SW_CB_IN1    ((uint32)CyUAB_CLK_PHI9 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              | (((engine_sensor_adc_CFG0_FILTER_GT_C1_DENOMINATOR_VAL > 1u)    \
                                                                  ? CyUAB_CLK_PHI2                                            \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_SW_CB_IN0    (CyUAB_CLK_PHI12 << (engine_sensor_adc_UABH_A_halfuab__X0 << 2u))
            #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_SW_CB_IN1    (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                                | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
        #endif /* (engine_sensor_adc_CFG0_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define engine_sensor_adc_CFG0_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT)                              \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)                       \
                                                           | (((engine_sensor_adc_CFG0_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2                                                   \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define engine_sensor_adc_CFG0_UABH_B_LOWQDYN_CAP_CTRL     ((engine_sensor_adc_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                                 \
                                                            : 0u)
        #define engine_sensor_adc_CFG0_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT) \
                                                            | (((engine_sensor_adc_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_SW_OPEN                                              \
                                                            : CyUAB_SW_CLOSED) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG0 High-Q definitions
    *******************************************************************************/
        
    #elif (engine_sensor_adc_CFG0_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define engine_sensor_adc_CFG0_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG0_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (engine_sensor_adc_CFG0_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (engine_sensor_adc_CFG0_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT)           \
                                                            | (engine_sensor_adc_CFG0_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT)           \
                                                            | ((uint32)((engine_sensor_adc_CFG0_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define engine_sensor_adc_CFG0_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (engine_sensor_adc_CFG0_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (engine_sensor_adc_CFG0_FILTER_GT_C3_VAL            << CyUAB_CA_VAL_SHIFT)      \
                                                       | (engine_sensor_adc_CFG0_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)       \
                                                       | ((uint32)((engine_sensor_adc_CFG0_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define engine_sensor_adc_CFG0_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT)  \
                                                        |  ((1u < engine_sensor_adc_CFG0_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))

        #define engine_sensor_adc_CFG0_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                        |  ((1u < engine_sensor_adc_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_SW_OPEN << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))
        #define engine_sensor_adc_CFG0_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((1u < engine_sensor_adc_CFG0_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT)))

        #define engine_sensor_adc_CFG0_UABH_A_HIGHQDYN_CAP_CTRL ((1u < engine_sensor_adc_CFG0_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)     \
                                                            : 0u )
        
        #define engine_sensor_adc_CFG0_UABH_B_HIGHQDYN_CAP_CTRL (((1u < engine_sensor_adc_CFG0_FILTER_GT_Cpp_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)   \
                                                            : 0u) \
                                                        | ((1u < engine_sensor_adc_CFG0_FILTER_GT_C1_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT)   \
                                                            : 0u))
        
    #endif /*(engine_sensor_adc_CFG0_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != engine_sensor_adc_FILTER_CFG0_FILTER_PRESENT) */
/*******************************************************************************
* CFG1 definitions
*******************************************************************************/
#if (0u != engine_sensor_adc_FILTER_CFG1_FILTER_PRESENT)
    
    #define engine_sensor_adc_CFG1_FILTERTYPE_USED   engine_sensor_adc_FILTERTOPOLOGY_
    #define engine_sensor_adc_CFG1_TRANSFERTYPE_0   engine_sensor_adc_FILTERTOPOLOGY_
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define engine_sensor_adc_CFG1_FILTER_GT_C1_NUMERATOR_VAL    (ul)
    #define engine_sensor_adc_CFG1_FILTER_GT_C1_DENOMINATOR_VAL  (ul)
    #define engine_sensor_adc_CFG1_FILTER_GT_C2_NUMERATOR_VAL    (ul)
    #define engine_sensor_adc_CFG1_FILTER_GT_C2_DENOMINATOR_VAL  (ul) 
    #define engine_sensor_adc_CFG1_FILTER_GT_C3_VAL              (ul)      
    #define engine_sensor_adc_CFG1_FILTER_GT_C4_VAL              (ul)      
    #define engine_sensor_adc_CFG1_FILTER_GT_Cp_VAL              (ul)      
    #define engine_sensor_adc_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL   (ul)  
    #define engine_sensor_adc_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL (ul)  
    #define engine_sensor_adc_CFG1_FILTER_GT_CA_VAL              (ul)      
    #define engine_sensor_adc_CFG1_FILTER_GT_CB_VAL              (ul)     

    #define engine_sensor_adc_CFG1_FILTER_IDEAL_BIQUAD_NUM0      ()
    #define engine_sensor_adc_CFG1_FILTER_IDEAL_BIQUAD_NUM1      ()
    #define engine_sensor_adc_CFG1_FILTER_IDEAL_BIQUAD_NUM2      ()
    #define engine_sensor_adc_CFG1_FILTER_IDEAL_BIQUAD_DEN0      ()
    #define engine_sensor_adc_CFG1_FILTER_IDEAL_BIQUAD_DEN1      ()
    #define engine_sensor_adc_CFG1_FILTER_IDEAL_BIQUAD_DEN2      ()

    #define engine_sensor_adc_CFG1_FILTER_UAB_BIQUAD_NUM0        ()
    #define engine_sensor_adc_CFG1_FILTER_UAB_BIQUAD_NUM1        ()
    #define engine_sensor_adc_CFG1_FILTER_UAB_BIQUAD_NUM2        ()
    #define engine_sensor_adc_CFG1_FILTER_UAB_BIQUAD_DEN0        ()
    #define engine_sensor_adc_CFG1_FILTER_UAB_BIQUAD_DEN1        ()
    #define engine_sensor_adc_CFG1_FILTER_UAB_BIQUAD_DEN2        ()
    
    #define engine_sensor_adc_CFG1_UABH_A_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))
    #define engine_sensor_adc_CFG1_UABH_B_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))
    
    #if (engine_sensor_adc_CFG1_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < engine_sensor_adc_CFG1_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == engine_sensor_adc_CFG1_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(engine_sensor_adc_CFG1_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == engine_sensor_adc_CFG1_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(engine_sensor_adc_CFG1_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(engine_sensor_adc_CFG1_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_F_VAL_PRE (engine_sensor_adc_CFG1_FILTER_GT_CA_VAL/4u)
        #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((engine_sensor_adc_CFG1_FILTER_GT_CA_VAL - (2u * (engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_ABCF_VAL ((engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define engine_sensor_adc_CFG1_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG1_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(engine_sensor_adc_CFG1_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT))          \
                                                       | (uint32)(engine_sensor_adc_CFG1_FILTER_GT_C4_VAL            << CyUAB_CA_VAL_SHIFT)    \
                                                       | (uint32)(engine_sensor_adc_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)  \
                                                       | (uint32)((uint32)((engine_sensor_adc_CFG1_FILTER_GT_CB_VAL / 2u) - 1u)  << CyUAB_CF_VAL_SHIFT))


        #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_CAP_CTRL ((((engine_sensor_adc_CFG1_FILTER_GT_C1_NUMERATOR_VAL > 0u)      \
                                                           && (engine_sensor_adc_CFG1_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT)                                              \
                                                            : 0u)                                                     \
                                                         | ((engine_sensor_adc_CFG1_FILTER_GT_C2_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                              \
                                                            : 0u))
        #if (engine_sensor_adc_CFG1_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_SW_CB_IN0    ((uint32)CyUAB_CLK_PHI10 << (engine_sensor_adc_UABH_A_halfuab__X0 << 2u))
            #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_SW_CB_IN1    ((uint32)CyUAB_CLK_PHI9 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              | (((engine_sensor_adc_CFG1_FILTER_GT_C1_DENOMINATOR_VAL > 1u)    \
                                                                  ? CyUAB_CLK_PHI2                                            \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_SW_CB_IN0    (CyUAB_CLK_PHI12 << (engine_sensor_adc_UABH_A_halfuab__X0 << 2u))
            #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_SW_CB_IN1    (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                                | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
        #endif /* (engine_sensor_adc_CFG1_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define engine_sensor_adc_CFG1_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT)                              \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)                       \
                                                           | (((engine_sensor_adc_CFG1_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2                                                   \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define engine_sensor_adc_CFG1_UABH_B_LOWQDYN_CAP_CTRL     ((engine_sensor_adc_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                                 \
                                                            : 0u)
        #define engine_sensor_adc_CFG1_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT) \
                                                            | (((engine_sensor_adc_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_SW_OPEN                                              \
                                                            : CyUAB_SW_CLOSED) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG1 High-Q definitions
    *******************************************************************************/
        
    #elif (engine_sensor_adc_CFG1_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define engine_sensor_adc_CFG1_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG1_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (engine_sensor_adc_CFG1_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (engine_sensor_adc_CFG1_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT)           \
                                                            | (engine_sensor_adc_CFG1_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT)           \
                                                            | ((uint32)((engine_sensor_adc_CFG1_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define engine_sensor_adc_CFG1_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (engine_sensor_adc_CFG1_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (engine_sensor_adc_CFG1_FILTER_GT_C3_VAL            << CyUAB_CA_VAL_SHIFT)      \
                                                       | (engine_sensor_adc_CFG1_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)       \
                                                       | ((uint32)((engine_sensor_adc_CFG1_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define engine_sensor_adc_CFG1_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT)  \
                                                        |  ((1u < engine_sensor_adc_CFG1_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))

        #define engine_sensor_adc_CFG1_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                        |  ((1u < engine_sensor_adc_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_SW_OPEN << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))
        #define engine_sensor_adc_CFG1_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((1u < engine_sensor_adc_CFG1_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT)))

        #define engine_sensor_adc_CFG1_UABH_A_HIGHQDYN_CAP_CTRL ((1u < engine_sensor_adc_CFG1_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)     \
                                                            : 0u )
        
        #define engine_sensor_adc_CFG1_UABH_B_HIGHQDYN_CAP_CTRL (((1u < engine_sensor_adc_CFG1_FILTER_GT_Cpp_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)   \
                                                            : 0u) \
                                                        | ((1u < engine_sensor_adc_CFG1_FILTER_GT_C1_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT)   \
                                                            : 0u))
        
    #endif /*(engine_sensor_adc_CFG1_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != engine_sensor_adc_FILTER_CFG1_FILTER_PRESENT) */

/*******************************************************************************
* CFG2 definitions
*******************************************************************************/
#if (0u != engine_sensor_adc_FILTER_CFG2_FILTER_PRESENT)
    
    #define engine_sensor_adc_CFG2_FILTERTYPE_USED   engine_sensor_adc_FILTERTOPOLOGY_
    #define engine_sensor_adc_CFG2_TRANSFERTYPE_0   engine_sensor_adc_FILTERTOPOLOGY_
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define engine_sensor_adc_CFG2_FILTER_GT_C1_NUMERATOR_VAL    (ul)
    #define engine_sensor_adc_CFG2_FILTER_GT_C1_DENOMINATOR_VAL  (ul)
    #define engine_sensor_adc_CFG2_FILTER_GT_C2_NUMERATOR_VAL    (ul)
    #define engine_sensor_adc_CFG2_FILTER_GT_C2_DENOMINATOR_VAL  (ul) 
    #define engine_sensor_adc_CFG2_FILTER_GT_C3_VAL              (ul)      
    #define engine_sensor_adc_CFG2_FILTER_GT_C4_VAL              (ul)      
    #define engine_sensor_adc_CFG2_FILTER_GT_Cp_VAL              (ul)      
    #define engine_sensor_adc_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL   (ul)  
    #define engine_sensor_adc_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL (ul)  
    #define engine_sensor_adc_CFG2_FILTER_GT_CA_VAL              (ul)      
    #define engine_sensor_adc_CFG2_FILTER_GT_CB_VAL              (ul)     

    #define engine_sensor_adc_CFG2_FILTER_IDEAL_BIQUAD_NUM0      ()
    #define engine_sensor_adc_CFG2_FILTER_IDEAL_BIQUAD_NUM1      ()
    #define engine_sensor_adc_CFG2_FILTER_IDEAL_BIQUAD_NUM2      ()
    #define engine_sensor_adc_CFG2_FILTER_IDEAL_BIQUAD_DEN0      ()
    #define engine_sensor_adc_CFG2_FILTER_IDEAL_BIQUAD_DEN1      ()
    #define engine_sensor_adc_CFG2_FILTER_IDEAL_BIQUAD_DEN2      ()

    #define engine_sensor_adc_CFG2_FILTER_UAB_BIQUAD_NUM0        ()
    #define engine_sensor_adc_CFG2_FILTER_UAB_BIQUAD_NUM1        ()
    #define engine_sensor_adc_CFG2_FILTER_UAB_BIQUAD_NUM2        ()
    #define engine_sensor_adc_CFG2_FILTER_UAB_BIQUAD_DEN0        ()
    #define engine_sensor_adc_CFG2_FILTER_UAB_BIQUAD_DEN1        ()
    #define engine_sensor_adc_CFG2_FILTER_UAB_BIQUAD_DEN2        ()
    
    #define engine_sensor_adc_CFG2_UABH_A_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))
    #define engine_sensor_adc_CFG2_UABH_B_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))
    
    #if (engine_sensor_adc_CFG2_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < engine_sensor_adc_CFG2_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == engine_sensor_adc_CFG2_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(engine_sensor_adc_CFG2_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == engine_sensor_adc_CFG2_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(engine_sensor_adc_CFG2_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(engine_sensor_adc_CFG2_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_F_VAL_PRE (engine_sensor_adc_CFG2_FILTER_GT_CA_VAL/4u)
        #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((engine_sensor_adc_CFG2_FILTER_GT_CA_VAL - (2u * (engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_ABCF_VAL ((engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define engine_sensor_adc_CFG2_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG2_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(engine_sensor_adc_CFG2_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT))          \
                                                       | (uint32)(engine_sensor_adc_CFG2_FILTER_GT_C4_VAL            << CyUAB_CA_VAL_SHIFT)    \
                                                       | (uint32)(engine_sensor_adc_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)  \
                                                       | (uint32)((uint32)((engine_sensor_adc_CFG2_FILTER_GT_CB_VAL / 2u) - 1u)  << CyUAB_CF_VAL_SHIFT))


        #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_CAP_CTRL ((((engine_sensor_adc_CFG2_FILTER_GT_C1_NUMERATOR_VAL > 0u)      \
                                                           && (engine_sensor_adc_CFG2_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT)                                              \
                                                            : 0u)                                                     \
                                                         | ((engine_sensor_adc_CFG2_FILTER_GT_C2_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                              \
                                                            : 0u))
        #if (engine_sensor_adc_CFG2_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_SW_CB_IN0    ((uint32)CyUAB_CLK_PHI10 << (engine_sensor_adc_UABH_A_halfuab__X0 << 2u))
            #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_SW_CB_IN1    ((uint32)CyUAB_CLK_PHI9 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              | (((engine_sensor_adc_CFG2_FILTER_GT_C1_DENOMINATOR_VAL > 1u)    \
                                                                  ? CyUAB_CLK_PHI2                                            \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_SW_CB_IN0    (CyUAB_CLK_PHI12 << (engine_sensor_adc_UABH_A_halfuab__X0 << 2u))
            #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_SW_CB_IN1    (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                                | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
        #endif /* (engine_sensor_adc_CFG2_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define engine_sensor_adc_CFG2_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT)                              \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)                       \
                                                           | (((engine_sensor_adc_CFG2_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2                                                   \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define engine_sensor_adc_CFG2_UABH_B_LOWQDYN_CAP_CTRL     ((engine_sensor_adc_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                                 \
                                                            : 0u)
        #define engine_sensor_adc_CFG2_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT) \
                                                            | (((engine_sensor_adc_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_SW_OPEN                                              \
                                                            : CyUAB_SW_CLOSED) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG2 High-Q definitions
    *******************************************************************************/
        
    #elif (engine_sensor_adc_CFG2_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define engine_sensor_adc_CFG2_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG2_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (engine_sensor_adc_CFG2_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (engine_sensor_adc_CFG2_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT)           \
                                                            | (engine_sensor_adc_CFG2_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT)           \
                                                            | ((uint32)((engine_sensor_adc_CFG2_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define engine_sensor_adc_CFG2_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (engine_sensor_adc_CFG2_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (engine_sensor_adc_CFG2_FILTER_GT_C3_VAL            << CyUAB_CA_VAL_SHIFT)      \
                                                       | (engine_sensor_adc_CFG2_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)       \
                                                       | ((uint32)((engine_sensor_adc_CFG2_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define engine_sensor_adc_CFG2_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT)  \
                                                        |  ((1u < engine_sensor_adc_CFG2_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))

        #define engine_sensor_adc_CFG2_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                        |  ((1u < engine_sensor_adc_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_SW_OPEN << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))
        #define engine_sensor_adc_CFG2_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((1u < engine_sensor_adc_CFG2_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT)))

        #define engine_sensor_adc_CFG2_UABH_A_HIGHQDYN_CAP_CTRL ((1u < engine_sensor_adc_CFG2_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)     \
                                                            : 0u )
        
        #define engine_sensor_adc_CFG2_UABH_B_HIGHQDYN_CAP_CTRL (((1u < engine_sensor_adc_CFG2_FILTER_GT_Cpp_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)   \
                                                            : 0u) \
                                                        | ((1u < engine_sensor_adc_CFG2_FILTER_GT_C1_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT)   \
                                                            : 0u))
        
    #endif /*(engine_sensor_adc_CFG2_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != engine_sensor_adc_FILTER_CFG2_FILTER_PRESENT) */

/*******************************************************************************
* CFG3 definitions
*******************************************************************************/
#if (0u != engine_sensor_adc_FILTER_CFG3_FILTER_PRESENT)
    
    #define engine_sensor_adc_CFG3_FILTERTYPE_USED   engine_sensor_adc_FILTERTOPOLOGY_
    #define engine_sensor_adc_CFG3_TRANSFERTYPE_0   engine_sensor_adc_FILTERTOPOLOGY_
    /* Capacitors that can be fractional should have *
     * a numerator 0-63 and a denominator 1 or 64.   *
     * CA may have a value 1-127.                    *
     * CB may only have a value 2-64                 */

    #define engine_sensor_adc_CFG3_FILTER_GT_C1_NUMERATOR_VAL    (ul)
    #define engine_sensor_adc_CFG3_FILTER_GT_C1_DENOMINATOR_VAL  (ul)
    #define engine_sensor_adc_CFG3_FILTER_GT_C2_NUMERATOR_VAL    (ul)
    #define engine_sensor_adc_CFG3_FILTER_GT_C2_DENOMINATOR_VAL  (ul) 
    #define engine_sensor_adc_CFG3_FILTER_GT_C3_VAL              (ul)      
    #define engine_sensor_adc_CFG3_FILTER_GT_C4_VAL              (ul)      
    #define engine_sensor_adc_CFG3_FILTER_GT_Cp_VAL              (ul)      
    #define engine_sensor_adc_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL   (ul)  
    #define engine_sensor_adc_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL (ul)  
    #define engine_sensor_adc_CFG3_FILTER_GT_CA_VAL              (ul)      
    #define engine_sensor_adc_CFG3_FILTER_GT_CB_VAL              (ul)     

    #define engine_sensor_adc_CFG3_FILTER_IDEAL_BIQUAD_NUM0      ()
    #define engine_sensor_adc_CFG3_FILTER_IDEAL_BIQUAD_NUM1      ()
    #define engine_sensor_adc_CFG3_FILTER_IDEAL_BIQUAD_NUM2      ()
    #define engine_sensor_adc_CFG3_FILTER_IDEAL_BIQUAD_DEN0      ()
    #define engine_sensor_adc_CFG3_FILTER_IDEAL_BIQUAD_DEN1      ()
    #define engine_sensor_adc_CFG3_FILTER_IDEAL_BIQUAD_DEN2      ()

    #define engine_sensor_adc_CFG3_FILTER_UAB_BIQUAD_NUM0        ()
    #define engine_sensor_adc_CFG3_FILTER_UAB_BIQUAD_NUM1        ()
    #define engine_sensor_adc_CFG3_FILTER_UAB_BIQUAD_NUM2        ()
    #define engine_sensor_adc_CFG3_FILTER_UAB_BIQUAD_DEN0        ()
    #define engine_sensor_adc_CFG3_FILTER_UAB_BIQUAD_DEN1        ()
    #define engine_sensor_adc_CFG3_FILTER_UAB_BIQUAD_DEN2        ()
    
    #define engine_sensor_adc_CFG3_UABH_A_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))
    #define engine_sensor_adc_CFG3_UABH_B_STARTUP_DELAY    ((uint32)((uint32)u << CyUAB_STARTUP_DELAY_SHIFT))
    
    #if (engine_sensor_adc_CFG3_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_LOW_Q)
        /*  C1 = Bbranch
         *  C2 = Cbranch
         *  CA = Abranch + Fbranch */
        #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_B_VAL    ((0u < engine_sensor_adc_CFG3_FILTER_GT_C1_NUMERATOR_VAL) \
                                                           ? ((64u == engine_sensor_adc_CFG3_FILTER_GT_C1_NUMERATOR_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(engine_sensor_adc_CFG3_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                           : ((64u == engine_sensor_adc_CFG3_FILTER_GT_Cp_VAL) \
                                                             ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                             : (uint32)(engine_sensor_adc_CFG3_FILTER_GT_Cp_VAL << CyUAB_CB_VAL_SHIFT)))
        #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_C_VAL ((uint32)(engine_sensor_adc_CFG3_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT))
        #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_F_VAL_PRE (engine_sensor_adc_CFG3_FILTER_GT_CA_VAL/4u)
        #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_F_VAL ((uint32)(engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_F_VAL_PRE << CyUAB_CF_VAL_SHIFT))
        #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_A_VAL ((uint32)((engine_sensor_adc_CFG3_FILTER_GT_CA_VAL - (2u * (engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_F_VAL_PRE + 1u))) << CyUAB_CA_VAL_SHIFT))

        #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_ABCF_VAL ((engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_A_VAL) \
                                                           |  (engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_B_VAL) \
                                                           |  (engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_C_VAL) \
                                                           |  (engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_F_VAL))
        /* C3  = Bbranch
         * C4  = Abranch
         * Cpp = Cbranch
         * CB  = Fbranch */
        #define engine_sensor_adc_CFG3_UABH_B_LOWQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG3_FILTER_GT_C3_VAL) \
                                                              ? (uint32)((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (uint32)(engine_sensor_adc_CFG3_FILTER_GT_C3_VAL << CyUAB_CB_VAL_SHIFT))          \
                                                       | (uint32)(engine_sensor_adc_CFG3_FILTER_GT_C4_VAL            << CyUAB_CA_VAL_SHIFT)    \
                                                       | (uint32)(engine_sensor_adc_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)  \
                                                       | (uint32)((uint32)((engine_sensor_adc_CFG3_FILTER_GT_CB_VAL / 2u) - 1u)  << CyUAB_CF_VAL_SHIFT))


        #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_CAP_CTRL ((((engine_sensor_adc_CFG3_FILTER_GT_C1_NUMERATOR_VAL > 0u)      \
                                                           && (engine_sensor_adc_CFG3_FILTER_GT_C1_DENOMINATOR_VAL > 1u)) \
                                                            ? (uint32)((uint32)1u << CyUAB_CB_GND_SHIFT)                                              \
                                                            : 0u)                                                     \
                                                         | ((engine_sensor_adc_CFG3_FILTER_GT_C2_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                              \
                                                            : 0u))
        #if (engine_sensor_adc_CFG3_FILTER_GT_C1_NUMERATOR_VAL > 0u) /* CB is C1*/
            #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_SW_CB_IN0    ((uint32)CyUAB_CLK_PHI10 << (engine_sensor_adc_UABH_A_halfuab__X0 << 2u))
            #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_SW_CB_IN1    ((uint32)CyUAB_CLK_PHI9 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_SW_CB_TOP   ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                              |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT) \
                                                              | (((engine_sensor_adc_CFG3_FILTER_GT_C1_DENOMINATOR_VAL > 1u)    \
                                                                  ? CyUAB_CLK_PHI2                                            \
                                                                  : CyUAB_CLK_PHI1) << CyUAB_SW_TB_SHIFT))
        #else /* CB is C' */
            #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_SW_CB_IN0    (CyUAB_CLK_PHI12 << (engine_sensor_adc_UABH_A_halfuab__X0 << 2u))
            #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_SW_CB_IN1    (CyUAB_CLK_PHI11 << CyUAB_SW_BG_MODBIT_SHIFT)
            #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_SW_CB_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                                | (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT))
        #endif /* (engine_sensor_adc_CFG3_FILTER_GT_C1_NUMERATOR_VAL > 0u) */

        #define engine_sensor_adc_CFG3_UABH_A_LOWQDYN_SW_CC_TOP    ((CyUAB_CLK_PHI1 << CyUAB_SW_SC_SHIFT)                              \
                                                           |  (CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)                       \
                                                           | (((engine_sensor_adc_CFG3_FILTER_GT_C2_DENOMINATOR_VAL > 1u) \
                                                              ? CyUAB_CLK_PHI2                                                   \
                                                              : CyUAB_CLK_PHI1) << CyUAB_SW_TC_SHIFT))
        #define engine_sensor_adc_CFG3_UABH_B_LOWQDYN_CAP_CTRL     ((engine_sensor_adc_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u)    \
                                                            ? (uint32)((uint32)1u << CyUAB_CC_GND_SHIFT)                                                 \
                                                            : 0u)
        #define engine_sensor_adc_CFG3_UABH_B_LOWQDYN_SW_CC_TOP    ((CyUAB_SW_CLOSED << CyUAB_SW_SC_SHIFT) \
                                                            | (((engine_sensor_adc_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL > 1u) \
                                                            ? CyUAB_SW_OPEN                                              \
                                                            : CyUAB_SW_CLOSED) << CyUAB_SW_TB_SHIFT))

    /*******************************************************************************
    * CFG3 High-Q definitions
    *******************************************************************************/
        
    #elif (engine_sensor_adc_CFG3_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_HIGH_Q)
        /*  C4 = Abranch  *
         *  C2 = Bbranch  *
         *  Cp = Cbranch  *
         *  CA = Fbranch  */
        #define engine_sensor_adc_CFG3_UABH_A_HIGHQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG3_FILTER_GT_C2_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (engine_sensor_adc_CFG3_FILTER_GT_C2_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                            | (engine_sensor_adc_CFG3_FILTER_GT_Cp_VAL << CyUAB_CC_VAL_SHIFT)           \
                                                            | (engine_sensor_adc_CFG3_FILTER_GT_C4_VAL << CyUAB_CA_VAL_SHIFT)           \
                                                            | ((uint32)((engine_sensor_adc_CFG3_FILTER_GT_CA_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))
        /* C3  = Abranch
         * Cpp = Bbranch
         * C1  = Cbranch
         * CB  = Fbranch */
        #define engine_sensor_adc_CFG3_UABH_B_HIGHQDYN_CAP_ABCF_VAL (((64u == engine_sensor_adc_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL) \
                                                              ? ((uint32)1u << CyUAB_CB_64_SHIFT) \
                                                              : (engine_sensor_adc_CFG3_FILTER_GT_Cpp_NUMERATOR_VAL << CyUAB_CB_VAL_SHIFT)) \
                                                       | (engine_sensor_adc_CFG3_FILTER_GT_C3_VAL            << CyUAB_CA_VAL_SHIFT)      \
                                                       | (engine_sensor_adc_CFG3_FILTER_GT_C1_NUMERATOR_VAL << CyUAB_CC_VAL_SHIFT)       \
                                                       | ((uint32)((engine_sensor_adc_CFG3_FILTER_GT_CB_VAL / 2u) - 1u) << CyUAB_CF_VAL_SHIFT))


        #define engine_sensor_adc_CFG3_UABH_A_HIGHQDYN_SW_CB_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_SB_SHIFT) \
                                                        |  (CyUAB_CLK_PHI2 << CyUAB_SW_GB_MODBIT_SHIFT)  \
                                                        |  ((1u < engine_sensor_adc_CFG3_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))

        #define engine_sensor_adc_CFG3_UABH_B_HIGHQDYN_SW_CB_TOP ((CyUAB_SW_CLOSED << CyUAB_SW_SB_SHIFT) \
                                                        |  ((1u < engine_sensor_adc_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL) \
                                                            ? (CyUAB_SW_OPEN << CyUAB_SW_TB_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TB_SHIFT)))
        #define engine_sensor_adc_CFG3_UABH_B_HIGHQDYN_SW_CC_TOP ((CyUAB_CLK_PHI1 << CyUAB_SW_ZC_SHIFT) \
                                                        |  ((CyUAB_CLK_PHI2 << CyUAB_SW_GC_MODBIT_SHIFT)) \
                                                        |  ((1u < engine_sensor_adc_CFG3_FILTER_GT_C1_DENOMINATOR_VAL) \
                                                            ? (CyUAB_CLK_PHI2 << CyUAB_SW_TC_SHIFT) \
                                                            : (CyUAB_SW_CLOSED << CyUAB_SW_TC_SHIFT)))

        #define engine_sensor_adc_CFG3_UABH_A_HIGHQDYN_CAP_CTRL ((1u < engine_sensor_adc_CFG3_FILTER_GT_C2_DENOMINATOR_VAL) \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)     \
                                                            : 0u )
        
        #define engine_sensor_adc_CFG3_UABH_B_HIGHQDYN_CAP_CTRL (((1u < engine_sensor_adc_CFG3_FILTER_GT_Cpp_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CB_GND_SHIFT)   \
                                                            : 0u) \
                                                        | ((1u < engine_sensor_adc_CFG3_FILTER_GT_C1_DENOMINATOR_VAL)    \
                                                            ? ((uint32)1u << CyUAB_CC_GND_SHIFT)   \
                                                            : 0u))
        
    #endif /*(engine_sensor_adc_CFG3_FILTERTYPE_USED == engine_sensor_adc_FILTERTOPOLOGY_LOW_Q)*/
#endif /* (0u != engine_sensor_adc_FILTER_CFG3_FILTER_PRESENT) */


#endif /* (engine_sensor_adc_ANY_CONFIG_USES_FILTER	!= 0u)	 */
#endif /* !defined(CY_engine_sensor_adc_FILTER_H) */
/* [] END OF FILE */
