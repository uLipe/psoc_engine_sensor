/*!*****************************************************************************
* \file engine_sensor_adc_UABH_A_param.h
* \version 1.10
*
* \brief 
*   Definitions from Component Parameter
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

/* excluding defs in this file with cond and endcond */
/*! @cond */

#if !defined(engine_sensor_adc_UABH_A_PARAM_H)
#define engine_sensor_adc_UABH_A_PARAM_H

#include "engine_sensor_adc_UABH_A_CyUAB_types.h"
#include "engine_sensor_adc_UABH_A_regs.h"
#include "cytypes.h"
#include "cyfitter.h"

#define engine_sensor_adc_UABH_A_Nonzero(x) ( (x) != 0 )

#define engine_sensor_adc_UABH_A_UnmappedIsZero(x)  ((uint32)(((x)==-1)? 0 : (x)))

/*!
* \addtogroup group_init
* @{
*/
/*! Component Parameters set in the component customizer */
#define engine_sensor_adc_UABH_A_PARAM_COMP_MASK        0
#define engine_sensor_adc_UABH_A_PARAM_VDAC_EMPTY_MASK  0

#define engine_sensor_adc_UABH_A_NONZERO_INTR_MASK (engine_sensor_adc_UABH_A_Nonzero( \
    ( 0 |0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_INTR_MASK ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_COMP_MASK)<<engine_sensor_adc_UABH_A_INTR_COMP_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_VDAC_EMPTY_MASK)<<engine_sensor_adc_UABH_A_INTR_VDAC_EMPTY_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_UAB_PWR        2
#define engine_sensor_adc_UABH_A_PARAM_AGND_PTS       0
#define engine_sensor_adc_UABH_A_PARAM_AGND_PWR       7
#define engine_sensor_adc_UABH_A_PARAM_REF_PTS        0
#define engine_sensor_adc_UABH_A_PARAM_REF_PWR        0
#define engine_sensor_adc_UABH_A_PARAM_CMP_DSI_LEVEL  0
#define engine_sensor_adc_UABH_A_PARAM_CMP_EDGE       0
#define engine_sensor_adc_UABH_A_PARAM_CMP_PWR        0
#define engine_sensor_adc_UABH_A_PARAM_OA_PWR         7

#define engine_sensor_adc_UABH_A_PARAM_AGND_TIED      1
#define engine_sensor_adc_UABH_A_PARAM_REF_TIED       0


/*
#define engine_sensor_adc_UABH_A_NONZERO_OA_CTRL (engine_sensor_adc_UABH_A_Nonzero( \
    (2|0|7|0|\
    0||0|0|0|7) ))
*/

/* force inclusion in _initPairs */
#define engine_sensor_adc_UABH_A_NONZERO_OA_CTRL (engine_sensor_adc_UABH_A_Nonzero(1))

/*Shared switches agnd_tied and ref_tied occupy the same bit position, so ommitting from DEFAULT_OA_CTRL -
handled in Init() */
#define engine_sensor_adc_UABH_A_DEFAULT_OA_CTRL ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_UAB_PWR)<<engine_sensor_adc_UABH_A_UAB_PWR_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_AGND_PTS)<<engine_sensor_adc_UABH_A_AGND_PTS_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_AGND_PWR)<<engine_sensor_adc_UABH_A_AGND_PWR_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_REF_PTS)<<engine_sensor_adc_UABH_A_REF_PTS_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_REF_PWR)<<engine_sensor_adc_UABH_A_REF_PWR_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CMP_DSI_LEVEL)<<engine_sensor_adc_UABH_A_CMP_DSI_LEVEL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CMP_EDGE)<<engine_sensor_adc_UABH_A_CMP_EDGE_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CMP_PWR)<<engine_sensor_adc_UABH_A_CMP_PWR_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_OA_PWR)<<engine_sensor_adc_UABH_A_OA_PWR_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_CB_GND       0
#define engine_sensor_adc_UABH_A_PARAM_CC_GND       0
#define engine_sensor_adc_UABH_A_PARAM_FRC_SIGN_BIT 0
#define engine_sensor_adc_UABH_A_PARAM_DAC_MODE_EN  0
#define engine_sensor_adc_UABH_A_PARAM_DAC_MODE     0

#define engine_sensor_adc_UABH_A_NONZERO_CAP_CTRL ( engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_CAP_CTRL ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CB_GND)<<engine_sensor_adc_UABH_A_CB_GND_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CC_GND)<<engine_sensor_adc_UABH_A_CC_GND_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_FRC_SIGN_BIT)<<engine_sensor_adc_UABH_A_FRC_SIGN_BIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_DAC_MODE_EN)<<engine_sensor_adc_UABH_A_DAC_MODE_EN_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_DAC_MODE)<<engine_sensor_adc_UABH_A_DAC_MODE_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_CB_VAL    0
#define engine_sensor_adc_UABH_A_PARAM_CA_VAL    0
#define engine_sensor_adc_UABH_A_PARAM_SIGN_VAL  0
#define engine_sensor_adc_UABH_A_PARAM_CB_64     0
#define engine_sensor_adc_UABH_A_PARAM_CC_VAL    0
#define engine_sensor_adc_UABH_A_PARAM_CF_VAL    0

#define engine_sensor_adc_UABH_A_NONZERO_CAP_ABCF_VAL  (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_CAP_ABCF_VAL  ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CB_VAL)<<engine_sensor_adc_UABH_A_CB_VAL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CA_VAL)<<engine_sensor_adc_UABH_A_CA_VAL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SIGN_VAL)<<engine_sensor_adc_UABH_A_SIGN_VAL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CB_64)<<engine_sensor_adc_UABH_A_CB_64_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CC_VAL)<<engine_sensor_adc_UABH_A_CC_VAL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CF_VAL)<<engine_sensor_adc_UABH_A_CF_VAL_SHIFT) \
))

#define engine_sensor_adc_UABH_A_NONZERO_CAP_AB_VAL_NXT (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_CAP_AB_VAL_NXT  ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CB_VAL)<<engine_sensor_adc_UABH_A_CB_VAL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CA_VAL)<<engine_sensor_adc_UABH_A_CA_VAL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SIGN_VAL)<<engine_sensor_adc_UABH_A_SIGN_VAL_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_CC_VAL_UPDATE  0
#define engine_sensor_adc_UABH_A_PARAM_CF_VAL_UPDATE  0

#define engine_sensor_adc_UABH_A_NONZERO_CAP_CF_VAL_NXT (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_CAP_CF_VAL_NXT ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CC_VAL)<<engine_sensor_adc_UABH_A_CC_VAL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CF_VAL)<<engine_sensor_adc_UABH_A_CF_VAL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CC_VAL_UPDATE)<<engine_sensor_adc_UABH_A_CC_VAL_UPDATE_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CF_VAL_UPDATE)<<engine_sensor_adc_UABH_A_CF_VAL_UPDATE_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_GX0        CyUAB_SwIsClosed( 0 )
#define engine_sensor_adc_UABH_A_PARAM_SW_GX1        CyUAB_SwIsClosed( 0 )
#define engine_sensor_adc_UABH_A_PARAM_SW_GX2        CyUAB_SwIsClosed( 0 )
#define engine_sensor_adc_UABH_A_PARAM_SW_GX3        CyUAB_SwIsClosed( 0 )
#define engine_sensor_adc_UABH_A_PARAM_SW_RG         CyUAB_SwIsClosed( 0  )
#define engine_sensor_adc_UABH_A_PARAM_SW_GG         CyUAB_SwIsClosed( 1  )
#define engine_sensor_adc_UABH_A_PARAM_SW_RT         CyUAB_SwIsClosed( 0  )
#define engine_sensor_adc_UABH_A_PARAM_SW_GT         CyUAB_SwIsClosed( 0  )
#define engine_sensor_adc_UABH_A_PARAM_SW_QT         CyUAB_SwIsClosed( 0  )
#define engine_sensor_adc_UABH_A_PARAM_EARLY_PS      0
#define engine_sensor_adc_UABH_A_PARAM_EARLY_PO      1

/*strobe source from cyfitter.h*/
#define engine_sensor_adc_UABH_A_PARAM_STRB_RST_SEL  (engine_sensor_adc_UABH_A_UnmappedIsZero(engine_sensor_adc_UABH_A_halfuab__STRB_RST_SEL))

#define engine_sensor_adc_UABH_A_PARAM_STRB_RST_EN   0


/*if switch parameter references a bad x input, ignored in initialization*/
#define engine_sensor_adc_UABH_A_XIN_OK(xin) ( (0UL==((uint32)(xin))) || (1UL==((uint32)(xin))) || (2UL==((uint32)(xin))) || (3UL==((uint32)(xin))) )
#define engine_sensor_adc_UABH_A_IGNORE_VAL 0UL      
#define engine_sensor_adc_UABH_A_XField(xin,val)  ( engine_sensor_adc_UABH_A_XIN_OK((xin)) ? ((uint32)(val)) : engine_sensor_adc_UABH_A_IGNORE_VAL )

/*
#define engine_sensor_adc_UABH_A_NONZERO_SW_STATIC (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0|0|1|0|0|0|0|1|0|0) ))
*/

/* force inclusion in _initPairs */
#define engine_sensor_adc_UABH_A_NONZERO_SW_STATIC (engine_sensor_adc_UABH_A_Nonzero(1))

#define engine_sensor_adc_UABH_A_DEFAULT_SW_STATIC ((uint32)(\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X0,engine_sensor_adc_UABH_A_PARAM_SW_GX0<<engine_sensor_adc_UABH_A_StaticVShift(CyUAB_SW_GX0)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X1,engine_sensor_adc_UABH_A_PARAM_SW_GX1<<engine_sensor_adc_UABH_A_StaticVShift(CyUAB_SW_GX1)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X2,engine_sensor_adc_UABH_A_PARAM_SW_GX2<<engine_sensor_adc_UABH_A_StaticVShift(CyUAB_SW_GX2)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X3,engine_sensor_adc_UABH_A_PARAM_SW_GX3<<engine_sensor_adc_UABH_A_StaticVShift(CyUAB_SW_GX3)) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_RG)<<engine_sensor_adc_UABH_A_SW_RG_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_GG)<<engine_sensor_adc_UABH_A_SW_GG_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_RT)<<engine_sensor_adc_UABH_A_SW_RT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_GT)<<engine_sensor_adc_UABH_A_SW_GT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_QT)<<engine_sensor_adc_UABH_A_SW_QT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_EARLY_PS)<<engine_sensor_adc_UABH_A_EARLY_PS_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_EARLY_PO)<<engine_sensor_adc_UABH_A_EARLY_PO_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_STRB_RST_SEL)<<engine_sensor_adc_UABH_A_STRB_RST_SEL_SHIFT) | \
    (((uint32)engine_sensor_adc_UABH_A_PARAM_STRB_RST_EN)<<engine_sensor_adc_UABH_A_STRB_RST_EN_SHIFT) \
))

/*modbitab source from cyfitter.h*/
#define engine_sensor_adc_UABH_A_PARAM_MODBIT0_SRC_SEL   (engine_sensor_adc_UABH_A_UnmappedIsZero(engine_sensor_adc_UABH_A_halfuab__MODBIT0_SEL))
/*modbitc source from cyfitter.h*/
#define engine_sensor_adc_UABH_A_PARAM_MODBIT1_SRC_SEL   (engine_sensor_adc_UABH_A_UnmappedIsZero(engine_sensor_adc_UABH_A_halfuab__MODBIT1_SEL))

/*
#define engine_sensor_adc_UABH_A_NONZERO_SW_MODBIT_SRC (engine_sensor_adc_UABH_A_Nonzero( \
    (0|31) ))
*/
/* force inclusion in _initPairs */
#define engine_sensor_adc_UABH_A_NONZERO_SW_MODBIT_SRC (engine_sensor_adc_UABH_A_Nonzero(1))

#define engine_sensor_adc_UABH_A_DEFAULT_SW_MODBIT_SRC ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_MODBIT0_SRC_SEL)<<engine_sensor_adc_UABH_A_MODBIT0_SRC_SEL_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_MODBIT1_SRC_SEL)<<engine_sensor_adc_UABH_A_MODBIT1_SRC_SEL_SHIFT) \
))


    
#define engine_sensor_adc_UABH_A_PARAM_SW_AX0_MODBIT  0
#define engine_sensor_adc_UABH_A_PARAM_SW_AX1_MODBIT  0
#define engine_sensor_adc_UABH_A_PARAM_SW_AX2_MODBIT  0
#define engine_sensor_adc_UABH_A_PARAM_SW_AX3_MODBIT  0
#define engine_sensor_adc_UABH_A_PARAM_SW_AP          0
#define engine_sensor_adc_UABH_A_PARAM_SW_AQ          0

#define engine_sensor_adc_UABH_A_NONZERO_SW_CA_IN0 (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CA_IN0 ((uint32)(\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X0,engine_sensor_adc_UABH_A_PARAM_SW_AX0_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_AX0_MODBIT)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X1,engine_sensor_adc_UABH_A_PARAM_SW_AX1_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_AX1_MODBIT)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X2,engine_sensor_adc_UABH_A_PARAM_SW_AX2_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_AX2_MODBIT)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X3,engine_sensor_adc_UABH_A_PARAM_SW_AX3_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_AX3_MODBIT)) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_AP)<<engine_sensor_adc_UABH_A_SW_AP_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_AQ)<<engine_sensor_adc_UABH_A_SW_AQ_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_AA         0
#define engine_sensor_adc_UABH_A_PARAM_SW_AR_MODBIT  0
#define engine_sensor_adc_UABH_A_PARAM_SW_AG_MODBIT  0
#define engine_sensor_adc_UABH_A_PARAM_SW_AV_MODBIT  0

/*Shared switch AA intentionally ommitted - handled in Init()*/
#define engine_sensor_adc_UABH_A_NONZERO_SW_CA_IN1 (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CA_IN1 ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_AR_MODBIT)<<engine_sensor_adc_UABH_A_SW_AR_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_AG_MODBIT)<<engine_sensor_adc_UABH_A_SW_AG_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_AV_MODBIT)<<engine_sensor_adc_UABH_A_SW_AV_MODBIT_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_RA_MODBIT  0
#define engine_sensor_adc_UABH_A_PARAM_SW_GA_MODBIT  0
#define engine_sensor_adc_UABH_A_PARAM_SW_VA_MODBIT  0
#define engine_sensor_adc_UABH_A_PARAM_SW_SA         0

#define engine_sensor_adc_UABH_A_NONZERO_SW_CA_TOP (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CA_TOP ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_RA_MODBIT)<<engine_sensor_adc_UABH_A_SW_RA_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_GA_MODBIT)<<engine_sensor_adc_UABH_A_SW_GA_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_VA_MODBIT)<<engine_sensor_adc_UABH_A_SW_VA_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_SA)<<engine_sensor_adc_UABH_A_SW_SA_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_BX0_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_BX1_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_BX2_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_BX3_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_BP         0
#define engine_sensor_adc_UABH_A_PARAM_SW_BQ         0

#define engine_sensor_adc_UABH_A_NONZERO_SW_CB_IN0 (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CB_IN0 ((uint32)(\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X0,engine_sensor_adc_UABH_A_PARAM_SW_BX0_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_BX0_MODBIT)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X1,engine_sensor_adc_UABH_A_PARAM_SW_BX1_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_BX1_MODBIT)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X2,engine_sensor_adc_UABH_A_PARAM_SW_BX2_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_BX2_MODBIT)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X3,engine_sensor_adc_UABH_A_PARAM_SW_BX3_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_BX3_MODBIT)) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_BP)<<engine_sensor_adc_UABH_A_SW_BP_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_BQ)<<engine_sensor_adc_UABH_A_SW_BQ_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_BB        0
#define engine_sensor_adc_UABH_A_PARAM_SW_BR_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_BG_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_BV_MODBIT 0

/*Shared switch BB intentionally ommitted - handled in Init()*/
#define engine_sensor_adc_UABH_A_NONZERO_SW_CB_IN1 (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CB_IN1 ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_BR_MODBIT)<<engine_sensor_adc_UABH_A_SW_BR_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_BG_MODBIT)<<engine_sensor_adc_UABH_A_SW_BG_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_BV_MODBIT)<<engine_sensor_adc_UABH_A_SW_BV_MODBIT_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_RB_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_GB_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_VB_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_TB        0
#define engine_sensor_adc_UABH_A_PARAM_SW_SB        0

#define engine_sensor_adc_UABH_A_NONZERO_SW_CB_TOP (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CB_TOP ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_RB_MODBIT)<<engine_sensor_adc_UABH_A_SW_RB_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_GB_MODBIT)<<engine_sensor_adc_UABH_A_SW_GB_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_VB_MODBIT)<<engine_sensor_adc_UABH_A_SW_VB_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_TB)<<engine_sensor_adc_UABH_A_SW_TB_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_SB)<<engine_sensor_adc_UABH_A_SW_SB_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_CX0_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_CX1_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_CX2_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_CX3_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_CP         0
#define engine_sensor_adc_UABH_A_PARAM_SW_CQ         0
    
#define engine_sensor_adc_UABH_A_NONZERO_SW_CC_IN0 (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CC_IN0 ((uint32)(\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X0,engine_sensor_adc_UABH_A_PARAM_SW_CX0_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_CX0_MODBIT)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X1,engine_sensor_adc_UABH_A_PARAM_SW_CX1_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_CX1_MODBIT)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X2,engine_sensor_adc_UABH_A_PARAM_SW_CX2_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_CX2_MODBIT)) |\
    engine_sensor_adc_UABH_A_XField(engine_sensor_adc_UABH_A_X3,engine_sensor_adc_UABH_A_PARAM_SW_CX3_MODBIT<<engine_sensor_adc_UABH_A_DynamicVShift(CyUAB_SW_CX3_MODBIT)) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_CP)<<engine_sensor_adc_UABH_A_SW_CP_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_CQ)<<engine_sensor_adc_UABH_A_SW_CQ_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_CC        0
#define engine_sensor_adc_UABH_A_PARAM_SW_CR_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_CG_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_CV_MODBIT 0

/*Shared switch CC intentionally ommitted - handled in Init()*/
#define engine_sensor_adc_UABH_A_NONZERO_SW_CC_IN1 (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CC_IN1 ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_CR_MODBIT)<<engine_sensor_adc_UABH_A_SW_CR_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_CG_MODBIT)<<engine_sensor_adc_UABH_A_SW_CG_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_CV_MODBIT)<<engine_sensor_adc_UABH_A_SW_CV_MODBIT_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_RC_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_GC_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_VC_MODBIT 0
#define engine_sensor_adc_UABH_A_PARAM_SW_TC        0
#define engine_sensor_adc_UABH_A_PARAM_SW_SC        0
#define engine_sensor_adc_UABH_A_PARAM_SW_ZC        0

#define engine_sensor_adc_UABH_A_NONZERO_SW_CC_TOP (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CC_TOP ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_RC_MODBIT)<<engine_sensor_adc_UABH_A_SW_RC_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_GC_MODBIT)<<engine_sensor_adc_UABH_A_SW_GC_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_VC_MODBIT)<<engine_sensor_adc_UABH_A_SW_VC_MODBIT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_TC)<<engine_sensor_adc_UABH_A_SW_TC_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_SC)<<engine_sensor_adc_UABH_A_SW_SC_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_ZC)<<engine_sensor_adc_UABH_A_SW_ZC_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SW_GF 0
#define engine_sensor_adc_UABH_A_PARAM_SW_PF 0
#define engine_sensor_adc_UABH_A_PARAM_SW_PS 0
#define engine_sensor_adc_UABH_A_PARAM_SW_PO 0

#define engine_sensor_adc_UABH_A_NONZERO_SW_CF_BOT (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_CF_BOT ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_GF)<<engine_sensor_adc_UABH_A_SW_GF_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_PF)<<engine_sensor_adc_UABH_A_SW_PF_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_PS)<<engine_sensor_adc_UABH_A_SW_PS_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SW_PO)<<engine_sensor_adc_UABH_A_SW_PO_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_CMP_FF     0
#define engine_sensor_adc_UABH_A_PARAM_VALID_WAVE 0
#define engine_sensor_adc_UABH_A_PARAM_TRIG_OUT   0
#define engine_sensor_adc_UABH_A_PARAM_STROBE_SW  15
#define engine_sensor_adc_UABH_A_PARAM_STROBE_RST 0

#define engine_sensor_adc_UABH_A_NONZERO_SW_OTHER (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0|0|15|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_OTHER ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CMP_FF)<<engine_sensor_adc_UABH_A_CMP_FF_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_VALID_WAVE)<<engine_sensor_adc_UABH_A_VALID_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_TRIG_OUT)<<engine_sensor_adc_UABH_A_TRIG_OUT_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_STROBE_SW)<<engine_sensor_adc_UABH_A_STROBE_SW_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_STROBE_RST)<<engine_sensor_adc_UABH_A_STROBE_RST_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_CA_BOOST  1
#define engine_sensor_adc_UABH_A_PARAM_CB_BOOST  1
#define engine_sensor_adc_UABH_A_PARAM_CC_BOOST  1
#define engine_sensor_adc_UABH_A_PARAM_CF_BOOST  1
#define engine_sensor_adc_UABH_A_PARAM_SUM_BOOST 1
#define engine_sensor_adc_UABH_A_PARAM_PUMP_WAVE 1
    
#define engine_sensor_adc_UABH_A_NONZERO_SW_BOOST_CTRL (engine_sensor_adc_UABH_A_Nonzero( \
    (1|1|1|1|1|1) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SW_BOOST_CTRL ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CA_BOOST)<<engine_sensor_adc_UABH_A_CA_BOOST_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CB_BOOST)<<engine_sensor_adc_UABH_A_CB_BOOST_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CC_BOOST)<<engine_sensor_adc_UABH_A_CC_BOOST_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_CF_BOOST)<<engine_sensor_adc_UABH_A_CF_BOOST_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SUM_BOOST)<<engine_sensor_adc_UABH_A_SUM_BOOST_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_PUMP_WAVE)<<engine_sensor_adc_UABH_A_PUMP_WAVE_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_STARTUP_DELAY 0
#define engine_sensor_adc_UABH_A_PARAM_ALIGN_MODE    0

#define engine_sensor_adc_UABH_A_NONZERO_STARTUP_DELAY (engine_sensor_adc_UABH_A_Nonzero( \
	(0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_STARTUP_DELAY ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_STARTUP_DELAY)<<engine_sensor_adc_UABH_A_STARTUP_DELAY_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_ALIGN_MODE)<<engine_sensor_adc_UABH_A_ALIGN_MODE_SHIFT) \
))

#define engine_sensor_adc_UABH_A_PARAM_SUBSAMPLE 0    
#define engine_sensor_adc_UABH_A_PARAM_SUBSAMPLE_INIT 0    
    
#define engine_sensor_adc_UABH_A_NONZERO_SUBSAMPLE_CTRL (engine_sensor_adc_UABH_A_Nonzero( \
    (0|0) ))
#define engine_sensor_adc_UABH_A_DEFAULT_SUBSAMPLE_CTRL ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SUBSAMPLE)<<engine_sensor_adc_UABH_A_SUBSAMPLE_SHIFT) |\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_SUBSAMPLE_INIT)<<engine_sensor_adc_UABH_A_SUBSAMPLE_INIT_SHIFT) \
))
    
#define engine_sensor_adc_UABH_A_PARAM_LAST_STEP  1

/*trigger_in source from cyfitter.h*/
#define engine_sensor_adc_UABH_A_PARAM_TRIG_SEL    (engine_sensor_adc_UABH_A_UnmappedIsZero(engine_sensor_adc_UABH_A_halfuab__TRIG_SEL))

#define engine_sensor_adc_UABH_A_PARAM_TRIGGER_EN 1

/*
#define engine_sensor_adc_UABH_A_NONZERO_SRAM_CTRL (engine_sensor_adc_UABH_A_Nonzero( \
    (1|31|1) ))
*/
/* force inclusion in _initPairs */
#define engine_sensor_adc_UABH_A_NONZERO_SRAM_CTRL (engine_sensor_adc_UABH_A_Nonzero(1))    
 
#define engine_sensor_adc_UABH_A_DEFAULT_SRAM_CTRL ((uint32)(\
    (((uint32)engine_sensor_adc_UABH_A_PARAM_LAST_STEP)<<engine_sensor_adc_UABH_A_LAST_STEP_SHIFT) | \
    (((uint32)engine_sensor_adc_UABH_A_PARAM_TRIG_SEL)<<engine_sensor_adc_UABH_A_TRIG_SEL_SHIFT)   | \
    (((uint32)engine_sensor_adc_UABH_A_PARAM_TRIGGER_EN)<<engine_sensor_adc_UABH_A_TRIGGER_EN_SHIFT) \
))
/*There is intentionally no run bit symbol parameter and the run bit is not set as part of the Init() function*/

#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_0  60933
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_1  57606
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_2  0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_3  0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_4  0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_5  0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_6  0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_7  0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_8  0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_9  0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_10 0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_11 0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_12 0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_13 0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_14 0
#define engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_15 0

#define engine_sensor_adc_UABH_A_NONZERO_WAVE_0  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_0 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_1  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_1 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_2  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_2 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_3  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_3 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_4  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_4 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_5  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_5 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_6  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_6 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_7  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_7 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_8  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_8 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_9  (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_9 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_10 (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_10 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_11 (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_11 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_12 (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_12 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_13 (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_13 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_14 (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_14 ) )
#define engine_sensor_adc_UABH_A_NONZERO_WAVE_15 (engine_sensor_adc_UABH_A_Nonzero( engine_sensor_adc_UABH_A_PARAM_WAVE_STEP_15 ) )


/*all wave steps up to and including the last non-zero wave step 
    are included in the waveConfig array definition */
/*always include WAVE_STEP_0, since LAST_STEP minimum is 0*/
#define engine_sensor_adc_UABH_A_INC_STEP_0 (engine_sensor_adc_UABH_A_Nonzero(1))

#define engine_sensor_adc_UABH_A_INC_STEP_1  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_1  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_2  || engine_sensor_adc_UABH_A_NONZERO_WAVE_3  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_4  || engine_sensor_adc_UABH_A_NONZERO_WAVE_5  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_6  || engine_sensor_adc_UABH_A_NONZERO_WAVE_7  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_8  || engine_sensor_adc_UABH_A_NONZERO_WAVE_9  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_2  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_2  || engine_sensor_adc_UABH_A_NONZERO_WAVE_3  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_4  || engine_sensor_adc_UABH_A_NONZERO_WAVE_5  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_6  || engine_sensor_adc_UABH_A_NONZERO_WAVE_7  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_8  || engine_sensor_adc_UABH_A_NONZERO_WAVE_9  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_3  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_3  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_4  || engine_sensor_adc_UABH_A_NONZERO_WAVE_5  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_6  || engine_sensor_adc_UABH_A_NONZERO_WAVE_7  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_8  || engine_sensor_adc_UABH_A_NONZERO_WAVE_9  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_4  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_4  || engine_sensor_adc_UABH_A_NONZERO_WAVE_5  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_6  || engine_sensor_adc_UABH_A_NONZERO_WAVE_7  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_8  || engine_sensor_adc_UABH_A_NONZERO_WAVE_9  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )

#define engine_sensor_adc_UABH_A_INC_STEP_5  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_5  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_6  || engine_sensor_adc_UABH_A_NONZERO_WAVE_7  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_8  || engine_sensor_adc_UABH_A_NONZERO_WAVE_9  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )

#define engine_sensor_adc_UABH_A_INC_STEP_6  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_6  || engine_sensor_adc_UABH_A_NONZERO_WAVE_7  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_8  || engine_sensor_adc_UABH_A_NONZERO_WAVE_9  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_7  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_7  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_8  || engine_sensor_adc_UABH_A_NONZERO_WAVE_9  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_8  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_8  || engine_sensor_adc_UABH_A_NONZERO_WAVE_9  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_9  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_9  || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_10  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_10 || engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_11  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_11 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_12  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_12 || engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_13  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_13 || \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_14  ( \
    engine_sensor_adc_UABH_A_NONZERO_WAVE_14 || engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
#define engine_sensor_adc_UABH_A_INC_STEP_15  ( engine_sensor_adc_UABH_A_NONZERO_WAVE_15 )
    
    
/*! @} group_init */

#endif /* #ifndef engine_sensor_adc_UABH_A_PARAM_H */
    
/*! @endcond */

/* [] END OF FILE */
