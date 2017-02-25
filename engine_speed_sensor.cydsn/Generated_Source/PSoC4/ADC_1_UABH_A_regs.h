/*!*****************************************************************************
* \file ADC_1_UABH_A_regs.h
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
    
#ifndef ADC_1_UABH_A_REGS_H
#define ADC_1_UABH_A_REGS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ADC_1_UABH_A_CyUAB_regs.h"

/*!
* \addtogroup group_general
* @{
*/

/*! Get right-aligned register field; mask parameter is alredy shifted */
#define ADC_1_UABH_A_GET_FIELD(addr,mask,shift)         CyUAB_GET_FIELD((addr),(mask),(shift))
/*! Set register field without modifying other fields; mask parameter is already shifted */
#define ADC_1_UABH_A_SET_FIELD(addr,mask,val,shift)     CyUAB_SET_FIELD((addr),(mask),(val),(shift))
/*! Set multiple register fields with a single register write; mask parameter is already shifted and composite of all fields being written */
#define ADC_1_UABH_A_SET_VARIOUS_FIELDS(addr,mask,val)  CyUAB_SET_VARIOUS_FIELDS((addr), (mask), (val))

/*! number of array elements */
#define ADC_1_UABH_A_ELEMENT_COUNT(x)  (sizeof((x))/sizeof((x)[0]))
/*! @} group_general */
    
    
#define ADC_1_UABH_A_POSITION ADC_1_UABH_A_halfuab__POSITION

#define ADC_1_UABH_A_ISODD  ( (ADC_1_UABH_A_POSITION % 2UL) != 0UL )


#define ADC_1_UABH_A_BAD_XIN 0xabadc0deUL
	
/* x input terminals to VIN mapping selected by Creator P&R */

/* 
Decision tree below assigns unused x inputs to unused vin 
can't use preprocessor undef (MISRA requirement, so using a separate flag variable for each stage
VIN_FLAGS A-D track assigned vin assignments through the decision tree steps
*/

#define ADC_1_UABH_A_VIN0_ASSIGNED  ( (\
        (ADC_1_UABH_A_halfuab__X0==0) || (ADC_1_UABH_A_halfuab__X1==0) || \
        (ADC_1_UABH_A_halfuab__X2==0) || (ADC_1_UABH_A_halfuab__X3==0) ) ? 1 : 0 )
#define ADC_1_UABH_A_VIN1_ASSIGNED  ( (\
        (ADC_1_UABH_A_halfuab__X0==1) || (ADC_1_UABH_A_halfuab__X1==1) || \
        (ADC_1_UABH_A_halfuab__X2==1) || (ADC_1_UABH_A_halfuab__X3==1) ) ? 1 : 0 )
#define ADC_1_UABH_A_VIN2_ASSIGNED  ( (\
        (ADC_1_UABH_A_halfuab__X0==2) || (ADC_1_UABH_A_halfuab__X1==2) || \
        (ADC_1_UABH_A_halfuab__X2==2) || (ADC_1_UABH_A_halfuab__X3==2) ) ? 1 : 0 )
#define ADC_1_UABH_A_VIN3_ASSIGNED  ( (\
        (ADC_1_UABH_A_halfuab__X0==3) || (ADC_1_UABH_A_halfuab__X1==3) || \
        (ADC_1_UABH_A_halfuab__X2==3) || (ADC_1_UABH_A_halfuab__X3==3) ) ? 1 : 0 )


#define ADC_1_UABH_A__X0_FLAGS  ( \
    ( (ADC_1_UABH_A_VIN0_ASSIGNED)    ) | \
    ( (ADC_1_UABH_A_VIN1_ASSIGNED)<<1 ) | \
    ( (ADC_1_UABH_A_VIN2_ASSIGNED)<<2 ) | \
    ( (ADC_1_UABH_A_VIN3_ASSIGNED)<<3 )   \
)
    
/*x0 input assignment*/
#if ( (0<=ADC_1_UABH_A_halfuab__X0) && (ADC_1_UABH_A_halfuab__X0<=3) )
    /*fitter assignment is valid*/
    #define ADC_1_UABH_A_X0         (ADC_1_UABH_A_halfuab__X0)
    #define ADC_1_UABH_A__X1_FLAGS  (ADC_1_UABH_A__X0_FLAGS)
#else
    /*x0 input is unused (==-1), so map to unused vin*/
    #if   (( ADC_1_UABH_A__X0_FLAGS & 0x1 )==0)
        #define ADC_1_UABH_A_X0 (0)
        #define ADC_1_UABH_A__X1_FLAGS (ADC_1_UABH_A__X0_FLAGS|0x1)
    #elif (( ADC_1_UABH_A__X0_FLAGS & 0x2 )==0)
        #define ADC_1_UABH_A_X0 (1)
        #define ADC_1_UABH_A__X1_FLAGS (ADC_1_UABH_A__X0_FLAGS|0x2)
    #elif (( ADC_1_UABH_A__X0_FLAGS & 0x4 )==0)
        #define ADC_1_UABH_A_X0 (2)
        #define ADC_1_UABH_A__X1_FLAGS (ADC_1_UABH_A__X0_FLAGS|0x4)
    #elif (( ADC_1_UABH_A__X0_FLAGS & 0x8 )==0)
        #define ADC_1_UABH_A_X0 (3)
        #define ADC_1_UABH_A__X1_FLAGS (ADC_1_UABH_A__X0_FLAGS|0x8)
    #else
        #error "ADC_1_UABH_A_X0 mapping is bad"
    #endif
#endif

/*x1 input assignment*/
#if ( (0<=ADC_1_UABH_A_halfuab__X1) && (ADC_1_UABH_A_halfuab__X1<=3) )
    /*fitter assignment is valid*/
    #define ADC_1_UABH_A_X1         (ADC_1_UABH_A_halfuab__X1)
    #define ADC_1_UABH_A__X2_FLAGS  (ADC_1_UABH_A__X1_FLAGS)
#else
    /*x1 input is unused (==-1), so map to unused vin*/
    #if   (( ADC_1_UABH_A__X1_FLAGS & 0x1 )==0)
        #define ADC_1_UABH_A_X1 (0)
        #define ADC_1_UABH_A__X2_FLAGS (ADC_1_UABH_A__X1_FLAGS|0x1)
    #elif (( ADC_1_UABH_A__X1_FLAGS & 0x2 )==0)
        #define ADC_1_UABH_A_X1 (1)
        #define ADC_1_UABH_A__X2_FLAGS (ADC_1_UABH_A__X1_FLAGS|0x2)
    #elif (( ADC_1_UABH_A__X1_FLAGS & 0x4 )==0)
        #define ADC_1_UABH_A_X1 (2)
        #define ADC_1_UABH_A__X2_FLAGS (ADC_1_UABH_A__X1_FLAGS|0x4)
    #elif (( ADC_1_UABH_A__X1_FLAGS & 0x8 )==0)
        #define ADC_1_UABH_A_X1 (3)
        #define ADC_1_UABH_A__X2_FLAGS (ADC_1_UABH_A__X1_FLAGS|0x8)
    #else
        #error "ADC_1_UABH_A_X1 mapping is bad"
    #endif
#endif

/*x2 input assignment*/
#if ( (0<=ADC_1_UABH_A_halfuab__X2) && (ADC_1_UABH_A_halfuab__X2<=3) )
    /*fitter assignment is valid*/
    #define ADC_1_UABH_A_X2         (ADC_1_UABH_A_halfuab__X2)
    #define ADC_1_UABH_A__X3_FLAGS  (ADC_1_UABH_A__X2_FLAGS)
#else
    /*x2 input is unused (==-1), so map to unused vin*/
    #if   (( ADC_1_UABH_A__X2_FLAGS & 0x1 )==0)
        #define ADC_1_UABH_A_X2 (0)
        #define ADC_1_UABH_A__X3_FLAGS (ADC_1_UABH_A__X2_FLAGS|0x1)
    #elif (( ADC_1_UABH_A__X2_FLAGS & 0x2 )==0)
        #define ADC_1_UABH_A_X2 (1)
        #define ADC_1_UABH_A__X3_FLAGS (ADC_1_UABH_A__X2_FLAGS|0x2)
    #elif (( ADC_1_UABH_A__X2_FLAGS & 0x4 )==0)
        #define ADC_1_UABH_A_X2 (2)
        #define ADC_1_UABH_A__X3_FLAGS (ADC_1_UABH_A__X2_FLAGS|0x4)
    #elif (( ADC_1_UABH_A__X2_FLAGS & 0x8 )==0)
        #define ADC_1_UABH_A_X2 (3)
        #define ADC_1_UABH_A__X3_FLAGS (ADC_1_UABH_A__X2_FLAGS|0x8)
    #else
        #error "ADC_1_UABH_A_X2 mapping is bad"
    #endif
#endif

/*x3 input assignment*/
#if ( (0<=ADC_1_UABH_A_halfuab__X3) && (ADC_1_UABH_A_halfuab__X3<=3) )
    /*fitter assignment is valid*/
    #define ADC_1_UABH_A_X3         (ADC_1_UABH_A_halfuab__X3)
    #define ADC_1_UABH_A__X4_FLAGS  (ADC_1_UABH_A__X3_FLAGS)
#else
    /*x2 input is unused (==-1), so map to unused vin*/
    #if   (( ADC_1_UABH_A__X3_FLAGS & 0x1 )==0)
        #define ADC_1_UABH_A_X3 (0)
        #define ADC_1_UABH_A__X4_FLAGS (ADC_1_UABH_A__X3_FLAGS|0x1)
    #elif (( ADC_1_UABH_A__X3_FLAGS & 0x2 )==0)
        #define ADC_1_UABH_A_X3 (1)
        #define ADC_1_UABH_A__X4_FLAGS (ADC_1_UABH_A__X3_FLAGS|0x2)
    #elif (( ADC_1_UABH_A__X3_FLAGS & 0x4 )==0)
        #define ADC_1_UABH_A_X3 (2)
        #define ADC_1_UABH_A__X4_FLAGS (ADC_1_UABH_A__X3_FLAGS|0x4)
    #elif (( ADC_1_UABH_A__X3_FLAGS & 0x8 )==0)
        #define ADC_1_UABH_A_X3 (3)
        #define ADC_1_UABH_A__X4_FLAGS (ADC_1_UABH_A__X3_FLAGS|0x8)
    #else
        #error "ADC_1_UABH_A_X3 mapping is bad"
    #endif
#endif

/*check results of mapping
1. All vin mapped
2. x0,x1,x2, and x3 are in range of 0 to 3
3. x0,x1,x2, and x3 are unique
*/
#if !( (ADC_1_UABH_A__X4_FLAGS==0xF) && \
    ( (0<=ADC_1_UABH_A_X0) && (ADC_1_UABH_A_X0<=3) ) && \
    ( (0<=ADC_1_UABH_A_X1) && (ADC_1_UABH_A_X1<=3) ) && \
    ( (0<=ADC_1_UABH_A_X2) && (ADC_1_UABH_A_X2<=3) ) && \
    ( (0<=ADC_1_UABH_A_X3) && (ADC_1_UABH_A_X3<=3) ) && \
    (ADC_1_UABH_A_X0!=ADC_1_UABH_A_X1) && \
    (ADC_1_UABH_A_X1!=ADC_1_UABH_A_X2) && \
    (ADC_1_UABH_A_X2!=ADC_1_UABH_A_X3) )
#error "bad x input to vin mapping"
#endif

#define ADC_1_UABH_A_XIN_COUNT 4UL



/* UAB half shared switch assymmetry special cases */
#define ADC_1_UABH_A_AGND_TIED_ADDR (ADC_1_UABH_A_halfuab__AGND_TIED)
#define ADC_1_UABH_A_AGND_TIED_PTR  ((reg32*)ADC_1_UABH_A_AGND_TIED_ADDR)
#define ADC_1_UABH_A_AGND_TIED_REG  (*(ADC_1_UABH_A_AGND_TIED_PTR))

#define ADC_1_UABH_A_REF_TIED_PTR  ((reg32*)ADC_1_UABH_A_halfuab__REF_TIED)
#define ADC_1_UABH_A_REF_TIED_REG  (*(ADC_1_UABH_A_REF_TIED_PTR))

#define ADC_1_UABH_A_SW_AA_PTR     ((reg32*)ADC_1_UABH_A_halfuab__SW_AA)
#define ADC_1_UABH_A_SW_AA_REG     (*(ADC_1_UABH_A_SW_AA_PTR))

#define ADC_1_UABH_A_SW_BB_PTR     ((reg32*)ADC_1_UABH_A_halfuab__SW_BB)
#define ADC_1_UABH_A_SW_BB_REG     (*(ADC_1_UABH_A_SW_BB_PTR))

#define ADC_1_UABH_A_SW_CC_ADDR     (ADC_1_UABH_A_halfuab__SW_CC)
#define ADC_1_UABH_A_SW_CC_PTR     ((reg32*)ADC_1_UABH_A_SW_CC_ADDR)
#define ADC_1_UABH_A_SW_CC_REG     (*(ADC_1_UABH_A_SW_CC_PTR))

#define ADC_1_UABH_A_ISPAIRED      (ADC_1_UABH_A_halfuab__ISPAIRED)

#define ADC_1_UABH_A_UAB_CTRL_ADDR                 (ADC_1_UABH_A_halfuab__UAB_CTRL)
#define ADC_1_UABH_A_UAB_CTRL_PTR                 ((reg32*)ADC_1_UABH_A_UAB_CTRL_ADDR)
#define ADC_1_UABH_A_UAB_CTRL_REG                 (*(ADC_1_UABH_A_UAB_CTRL_PTR))

#define ADC_1_UABH_A_INTR_ADDR                     (ADC_1_UABH_A_halfuab__INTR)
#define ADC_1_UABH_A_INTR_PTR                     ((reg32*)ADC_1_UABH_A_INTR_ADDR)
#define ADC_1_UABH_A_INTR_REG                     (*(ADC_1_UABH_A_INTR_PTR))

#define ADC_1_UABH_A_INTR_SET_ADDR                 (ADC_1_UABH_A_halfuab__INTR_SET)
#define ADC_1_UABH_A_INTR_SET_PTR                 ((reg32*)ADC_1_UABH_A_INTR_SET_ADDR)
#define ADC_1_UABH_A_INTR_SET_REG                 (*(ADC_1_UABH_A_INTR_SET_PTR))

#define ADC_1_UABH_A_INTR_MASK_ADDR                (ADC_1_UABH_A_halfuab__INTR_MASK)
#define ADC_1_UABH_A_INTR_MASK_PTR                ((reg32*)ADC_1_UABH_A_INTR_MASK_ADDR)
#define ADC_1_UABH_A_INTR_MASK_REG                (*(ADC_1_UABH_A_INTR_MASK_PTR))

#define ADC_1_UABH_A_INTR_MASKED_ADDR              (ADC_1_UABH_A_halfuab__INTR_MASKED)
#define ADC_1_UABH_A_INTR_MASKED_PTR              ((reg32*)ADC_1_UABH_A_INTR_MASKED_ADDR)
#define ADC_1_UABH_A_INTR_MASKED_REG              (*(ADC_1_UABH_A_INTR_MASKED_PTR))

#define ADC_1_UABH_A_OA_CTRL_ADDR                  (ADC_1_UABH_A_halfuab__OA_CTRL)
#define ADC_1_UABH_A_OA_CTRL_PTR                  ((reg32*)ADC_1_UABH_A_OA_CTRL_ADDR)
#define ADC_1_UABH_A_OA_CTRL_REG                  (*(ADC_1_UABH_A_OA_CTRL_PTR))

#define ADC_1_UABH_A_CAP_CTRL_ADDR                 (ADC_1_UABH_A_halfuab__CAP_CTRL)
#define ADC_1_UABH_A_CAP_CTRL_PTR                 ((reg32*)ADC_1_UABH_A_CAP_CTRL_ADDR)
#define ADC_1_UABH_A_CAP_CTRL_REG                 (*(ADC_1_UABH_A_CAP_CTRL_PTR))

#define ADC_1_UABH_A_CAP_ABCF_VAL_ADDR             (ADC_1_UABH_A_halfuab__CAP_ABCF_VAL)
#define ADC_1_UABH_A_CAP_ABCF_VAL_PTR             ((reg32*)ADC_1_UABH_A_CAP_ABCF_VAL_ADDR)
#define ADC_1_UABH_A_CAP_ABCF_VAL_REG             (*(ADC_1_UABH_A_CAP_ABCF_VAL_PTR))

#define ADC_1_UABH_A_CAP_AB_VAL_NXT_ADDR           (ADC_1_UABH_A_halfuab__CAP_AB_VAL_NXT)
#define ADC_1_UABH_A_CAP_AB_VAL_NXT_PTR           ((reg32*)ADC_1_UABH_A_CAP_AB_VAL_NXT_ADDR)
#define ADC_1_UABH_A_CAP_AB_VAL_NXT_REG           (*(ADC_1_UABH_A_CAP_AB_VAL_NXT_PTR))

#define ADC_1_UABH_A_CAP_CF_VAL_NXT_ADDR           (ADC_1_UABH_A_halfuab__CAP_CF_VAL_NXT)
#define ADC_1_UABH_A_CAP_CF_VAL_NXT_PTR           ((reg32*)ADC_1_UABH_A_CAP_CF_VAL_NXT_ADDR)
#define ADC_1_UABH_A_CAP_CF_VAL_NXT_REG           (*(ADC_1_UABH_A_CAP_CF_VAL_NXT_PTR))

#define ADC_1_UABH_A_STARTUP_DELAY_ADDR            (ADC_1_UABH_A_halfuab__STARTUP_DELAY)
#define ADC_1_UABH_A_STARTUP_DELAY_PTR            ((reg32*)ADC_1_UABH_A_STARTUP_DELAY_ADDR)
#define ADC_1_UABH_A_STARTUP_DELAY_REG            (*(ADC_1_UABH_A_STARTUP_DELAY_PTR))

#define ADC_1_UABH_A_SUBSAMPLE_CTRL_ADDR           (ADC_1_UABH_A_halfuab__SUBSAMPLE_CTRL)
#define ADC_1_UABH_A_SUBSAMPLE_CTRL_PTR           ((reg32*)ADC_1_UABH_A_SUBSAMPLE_CTRL_ADDR)
#define ADC_1_UABH_A_SUBSAMPLE_CTRL_REG           (*(ADC_1_UABH_A_SUBSAMPLE_CTRL_PTR))

#define ADC_1_UABH_A_SW_STATIC_ADDR               (ADC_1_UABH_A_halfuab__SW_STATIC )
#define ADC_1_UABH_A_SW_STATIC_PTR                ((reg32*)ADC_1_UABH_A_SW_STATIC_ADDR)
#define ADC_1_UABH_A_SW_STATIC_REG                (*(ADC_1_UABH_A_SW_STATIC_PTR))

#define ADC_1_UABH_A_SW_MODBIT_SRC_ADDR            (ADC_1_UABH_A_halfuab__SW_MODBIT_SRC)
#define ADC_1_UABH_A_SW_MODBIT_SRC_PTR            ((reg32*)ADC_1_UABH_A_SW_MODBIT_SRC_ADDR)
#define ADC_1_UABH_A_SW_MODBIT_SRC_REG            (*(ADC_1_UABH_A_SW_MODBIT_SRC_PTR))

#define ADC_1_UABH_A_SW_CA_IN0_ADDR                (ADC_1_UABH_A_halfuab__SW_CA_IN0)
#define ADC_1_UABH_A_SW_CA_IN0_PTR                ((reg32*)ADC_1_UABH_A_SW_CA_IN0_ADDR)
#define ADC_1_UABH_A_SW_CA_IN0_REG                (*(ADC_1_UABH_A_SW_CA_IN0_PTR))

#define ADC_1_UABH_A_SW_CA_IN1_ADDR                (ADC_1_UABH_A_halfuab__SW_CA_IN1)
#define ADC_1_UABH_A_SW_CA_IN1_PTR                ((reg32*)ADC_1_UABH_A_SW_CA_IN1_ADDR)
#define ADC_1_UABH_A_SW_CA_IN1_REG                (*(ADC_1_UABH_A_SW_CA_IN1_PTR))

#define ADC_1_UABH_A_SW_CA_TOP_ADDR                (ADC_1_UABH_A_halfuab__SW_CA_TOP)
#define ADC_1_UABH_A_SW_CA_TOP_PTR                ((reg32*)ADC_1_UABH_A_SW_CA_TOP_ADDR)
#define ADC_1_UABH_A_SW_CA_TOP_REG                (*(ADC_1_UABH_A_SW_CA_TOP_PTR))

#define ADC_1_UABH_A_SW_CB_IN0_ADDR                (ADC_1_UABH_A_halfuab__SW_CB_IN0)
#define ADC_1_UABH_A_SW_CB_IN0_PTR                ((reg32*)ADC_1_UABH_A_SW_CB_IN0_ADDR)
#define ADC_1_UABH_A_SW_CB_IN0_REG                (*(ADC_1_UABH_A_SW_CB_IN0_PTR))

#define ADC_1_UABH_A_SW_CB_IN1_ADDR                (ADC_1_UABH_A_halfuab__SW_CB_IN1)
#define ADC_1_UABH_A_SW_CB_IN1_PTR                ((reg32*)ADC_1_UABH_A_SW_CB_IN1_ADDR)
#define ADC_1_UABH_A_SW_CB_IN1_REG                (*(ADC_1_UABH_A_SW_CB_IN1_PTR))

#define ADC_1_UABH_A_SW_CB_TOP_ADDR                (ADC_1_UABH_A_halfuab__SW_CB_TOP)
#define ADC_1_UABH_A_SW_CB_TOP_PTR                ((reg32*)ADC_1_UABH_A_SW_CB_TOP_ADDR)
#define ADC_1_UABH_A_SW_CB_TOP_REG                (*(ADC_1_UABH_A_SW_CB_TOP_PTR))

#define ADC_1_UABH_A_SW_CC_IN0_ADDR                (ADC_1_UABH_A_halfuab__SW_CC_IN0)
#define ADC_1_UABH_A_SW_CC_IN0_PTR                ((reg32*)ADC_1_UABH_A_SW_CC_IN0_ADDR)
#define ADC_1_UABH_A_SW_CC_IN0_REG                (*(ADC_1_UABH_A_SW_CC_IN0_PTR))

#define ADC_1_UABH_A_SW_CC_IN1_ADDR                (ADC_1_UABH_A_halfuab__SW_CC_IN1)
#define ADC_1_UABH_A_SW_CC_IN1_PTR                ((reg32*)ADC_1_UABH_A_SW_CC_IN1_ADDR)
#define ADC_1_UABH_A_SW_CC_IN1_REG                (*(ADC_1_UABH_A_SW_CC_IN1_PTR))

#define ADC_1_UABH_A_SW_CC_TOP_ADDR                (ADC_1_UABH_A_halfuab__SW_CC_TOP)
#define ADC_1_UABH_A_SW_CC_TOP_PTR                ((reg32*)ADC_1_UABH_A_SW_CC_TOP_ADDR)
#define ADC_1_UABH_A_SW_CC_TOP_REG                (*(ADC_1_UABH_A_SW_CC_TOP_PTR))

#define ADC_1_UABH_A_SW_CF_BOT_ADDR                (ADC_1_UABH_A_halfuab__SW_CF_BOT)
#define ADC_1_UABH_A_SW_CF_BOT_PTR                ((reg32*)ADC_1_UABH_A_SW_CF_BOT_ADDR)
#define ADC_1_UABH_A_SW_CF_BOT_REG                (*(ADC_1_UABH_A_SW_CF_BOT_PTR))

#define ADC_1_UABH_A_SW_OTHER_ADDR                 (ADC_1_UABH_A_halfuab__SW_OTHER)
#define ADC_1_UABH_A_SW_OTHER_PTR                 ((reg32*)ADC_1_UABH_A_SW_OTHER_ADDR)
#define ADC_1_UABH_A_SW_OTHER_REG                 (*(ADC_1_UABH_A_SW_OTHER_PTR))

#define ADC_1_UABH_A_SW_BOOST_CTRL_ADDR            (ADC_1_UABH_A_halfuab__SW_BOOST_CTRL)
#define ADC_1_UABH_A_SW_BOOST_CTRL_PTR            ((reg32*)ADC_1_UABH_A_SW_BOOST_CTRL_ADDR)
#define ADC_1_UABH_A_SW_BOOST_CTRL_REG            (*(ADC_1_UABH_A_SW_BOOST_CTRL_PTR))

#define ADC_1_UABH_A_SRAM_CTRL_ADDR                (ADC_1_UABH_A_halfuab__SRAM_CTRL)
#define ADC_1_UABH_A_SRAM_CTRL_PTR                ((reg32*)ADC_1_UABH_A_SRAM_CTRL_ADDR)
#define ADC_1_UABH_A_SRAM_CTRL_REG                (*(ADC_1_UABH_A_SRAM_CTRL_PTR))

#define ADC_1_UABH_A_STAT_ADDR                     (ADC_1_UABH_A_halfuab__STAT)
#define ADC_1_UABH_A_STAT_PTR                     ((reg32*)ADC_1_UABH_A_STAT_ADDR)
#define ADC_1_UABH_A_STAT_REG                     (*(ADC_1_UABH_A_STAT_PTR))

#define ADC_1_UABH_A_SRAM0_ADDR                    (ADC_1_UABH_A_halfuab__SRAM0)
#define ADC_1_UABH_A_SRAM0_PTR                    ((reg32*)ADC_1_UABH_A_SRAM0_ADDR)
#define ADC_1_UABH_A_SRAM0_REG                    (*(ADC_1_UABH_A_SRAM0_PTR))

#define ADC_1_UABH_A_SRAM1_ADDR                    (ADC_1_UABH_A_halfuab__SRAM1)
#define ADC_1_UABH_A_SRAM1_PTR                    ((reg32*)ADC_1_UABH_A_SRAM1_ADDR)
#define ADC_1_UABH_A_SRAM1_REG                    (*(ADC_1_UABH_A_SRAM1_PTR))

#define ADC_1_UABH_A_SRAM2_ADDR                    (ADC_1_UABH_A_halfuab__SRAM2)
#define ADC_1_UABH_A_SRAM2_PTR                    ((reg32*)ADC_1_UABH_A_SRAM2_ADDR)
#define ADC_1_UABH_A_SRAM2_REG                    (*(ADC_1_UABH_A_SRAM2_PTR))

#define ADC_1_UABH_A_SRAM3_ADDR                    (ADC_1_UABH_A_halfuab__SRAM3)
#define ADC_1_UABH_A_SRAM3_PTR                    ((reg32*)ADC_1_UABH_A_SRAM3_ADDR)
#define ADC_1_UABH_A_SRAM3_REG                    (*(ADC_1_UABH_A_SRAM3_PTR))

#define ADC_1_UABH_A_SRAM4_ADDR                    (ADC_1_UABH_A_halfuab__SRAM4)
#define ADC_1_UABH_A_SRAM4_PTR                    ((reg32*)ADC_1_UABH_A_SRAM4_ADDR)
#define ADC_1_UABH_A_SRAM4_REG                    (*(ADC_1_UABH_A_SRAM4_PTR))

#define ADC_1_UABH_A_SRAM5_ADDR                    (ADC_1_UABH_A_halfuab__SRAM5)
#define ADC_1_UABH_A_SRAM5_PTR                    ((reg32*)ADC_1_UABH_A_SRAM5_ADDR)
#define ADC_1_UABH_A_SRAM5_REG                    (*(ADC_1_UABH_A_SRAM5_PTR))

#define ADC_1_UABH_A_SRAM6_ADDR                    (ADC_1_UABH_A_halfuab__SRAM6)
#define ADC_1_UABH_A_SRAM6_PTR                    ((reg32*)ADC_1_UABH_A_SRAM6_ADDR)
#define ADC_1_UABH_A_SRAM6_REG                    (*(ADC_1_UABH_A_SRAM6_PTR))

#define ADC_1_UABH_A_SRAM7_ADDR                    (ADC_1_UABH_A_halfuab__SRAM7)
#define ADC_1_UABH_A_SRAM7_PTR                    ((reg32*)ADC_1_UABH_A_SRAM7_ADDR)
#define ADC_1_UABH_A_SRAM7_REG                    (*(ADC_1_UABH_A_SRAM7_PTR))

#define ADC_1_UABH_A_SRAM8_ADDR                    (ADC_1_UABH_A_halfuab__SRAM8)
#define ADC_1_UABH_A_SRAM8_PTR                    ((reg32*)ADC_1_UABH_A_SRAM8_ADDR)
#define ADC_1_UABH_A_SRAM8_REG                    (*(ADC_1_UABH_A_SRAM8_PTR))

#define ADC_1_UABH_A_SRAM9_ADDR                    (ADC_1_UABH_A_halfuab__SRAM9)
#define ADC_1_UABH_A_SRAM9_PTR                    ((reg32*)ADC_1_UABH_A_SRAM9_ADDR)
#define ADC_1_UABH_A_SRAM9_REG                    (*(ADC_1_UABH_A_SRAM9_PTR))

#define ADC_1_UABH_A_SRAM10_ADDR                   (ADC_1_UABH_A_halfuab__SRAM10)
#define ADC_1_UABH_A_SRAM10_PTR                   ((reg32*)ADC_1_UABH_A_SRAM10_ADDR)
#define ADC_1_UABH_A_SRAM10_REG                   (*(ADC_1_UABH_A_SRAM10_PTR))

#define ADC_1_UABH_A_SRAM11_ADDR                   (ADC_1_UABH_A_halfuab__SRAM11)
#define ADC_1_UABH_A_SRAM11_PTR                   ((reg32*)ADC_1_UABH_A_SRAM11_ADDR)
#define ADC_1_UABH_A_SRAM11_REG                   (*(ADC_1_UABH_A_SRAM11_PTR))

#define ADC_1_UABH_A_SRAM12_ADDR                   (ADC_1_UABH_A_halfuab__SRAM12)
#define ADC_1_UABH_A_SRAM12_PTR                   ((reg32*)ADC_1_UABH_A_SRAM12_ADDR)
#define ADC_1_UABH_A_SRAM12_REG                   (*(ADC_1_UABH_A_SRAM12_PTR))

#define ADC_1_UABH_A_SRAM13_ADDR                   (ADC_1_UABH_A_halfuab__SRAM13)
#define ADC_1_UABH_A_SRAM13_PTR                   ((reg32*)ADC_1_UABH_A_SRAM13_ADDR)
#define ADC_1_UABH_A_SRAM13_REG                   (*(ADC_1_UABH_A_SRAM13_PTR))

#define ADC_1_UABH_A_SRAM14_ADDR                   (ADC_1_UABH_A_halfuab__SRAM14)
#define ADC_1_UABH_A_SRAM14_PTR                   ((reg32*)ADC_1_UABH_A_SRAM14_ADDR)
#define ADC_1_UABH_A_SRAM14_REG                   (*(ADC_1_UABH_A_SRAM14_PTR))

#define ADC_1_UABH_A_SRAM15_ADDR                   (ADC_1_UABH_A_halfuab__SRAM15)
#define ADC_1_UABH_A_SRAM15_PTR                   ((reg32*)ADC_1_UABH_A_SRAM15_ADDR)
#define ADC_1_UABH_A_SRAM15_REG                   (*(ADC_1_UABH_A_SRAM15_PTR))

#define ADC_1_UABH_A_SW_CC1_IN0_ADDR               (ADC_1_UABH_A_halfuab__SW_CC1_IN0)
#define ADC_1_UABH_A_SW_CC1_IN0_PTR               ((reg32*)ADC_1_UABH_A_SW_CC1_IN0_ADDR)
#define ADC_1_UABH_A_SW_CC1_IN0_REG               (*(ADC_1_UABH_A_SW_CC1_IN0_PTR))

#define ADC_1_UABH_A_SW_CC1_IN1_ADDR               (ADC_1_UABH_A_halfuab__SW_CC1_IN1)
#define ADC_1_UABH_A_SW_CC1_IN1_PTR               ((reg32*)ADC_1_UABH_A_SW_CC1_IN1_ADDR)
#define ADC_1_UABH_A_SW_CC1_IN1_REG               (*(ADC_1_UABH_A_SW_CC1_IN1_PTR))

#define ADC_1_UABH_A_SW_CC1_TOP_ADDR               (ADC_1_UABH_A_halfuab__SW_CC1_TOP)
#define ADC_1_UABH_A_SW_CC1_TOP_PTR               ((reg32*)ADC_1_UABH_A_SW_CC1_TOP_ADDR)
#define ADC_1_UABH_A_SW_CC1_TOP_REG               (*(ADC_1_UABH_A_SW_CC1_TOP_PTR))

#define ADC_1_UABH_A_CAP_TRIM_ADDR                 (ADC_1_UABH_A_halfuab__CAP_TRIM)
#define ADC_1_UABH_A_CAP_TRIM_PTR                 ((reg32*)ADC_1_UABH_A_CAP_TRIM_ADDR)
#define ADC_1_UABH_A_CAP_TRIM_REG                 (*(ADC_1_UABH_A_CAP_TRIM_PTR))

#define ADC_1_UABH_A_OA_TRIM_ADDR                  (ADC_1_UABH_A_halfuab__OA_TRIM)
#define ADC_1_UABH_A_OA_TRIM_PTR                  ((reg32*)ADC_1_UABH_A_OA_TRIM_ADDR)
#define ADC_1_UABH_A_OA_TRIM_REG                  (*(ADC_1_UABH_A_OA_TRIM_PTR))

/* Starting address for half UAB region */
#define ADC_1_UABH_A_BASE_ADDR                    (ADC_1_UABH_A_halfuab__OA_CTRL)
    



/*Register Field Definitions*/

    
/*UAB_CTRL*/
#define ADC_1_UABH_A_ENABLED_SHIFT                CyUAB_ENABLED_SHIFT
#define ADC_1_UABH_A_ENABLED_MASK                 (1UL<<ADC_1_UABH_A_ENABLED_SHIFT)


/*INTR*/
#if ADC_1_UABH_A_ISODD==1
    #define ADC_1_UABH_A_INTR_COMP_SHIFT CyUAB_INTR_COMP1_SHIFT
#else
    #define ADC_1_UABH_A_INTR_COMP_SHIFT CyUAB_INTR_COMP0_SHIFT
#endif
#define ADC_1_UABH_A_INTR_COMP_MASK               (1UL<<ADC_1_UABH_A_INTR_COMP_SHIFT)

#if ADC_1_UABH_A_ISODD==1
   #define ADC_1_UABH_A_INTR_VDAC_EMPTY_SHIFT CyUAB_INTR_VDAC1_EMPTY_SHIFT
#else
   #define ADC_1_UABH_A_INTR_VDAC_EMPTY_SHIFT CyUAB_INTR_VDAC0_EMPTY_SHIFT
#endif
#define ADC_1_UABH_A_INTR_VDAC_EMPTY_MASK         (1UL<<ADC_1_UABH_A_INTR_VDAC_EMPTY_SHIFT)


/*INTR_SET*/
#define ADC_1_UABH_A_INTR_COMP_SET_SHIFT          ADC_1_UABH_A_INTR_COMP_SHIFT
#define ADC_1_UABH_A_INTR_COMP_SET_MASK           (1UL<<ADC_1_UABH_A_INTR_COMP_SET_SHIFT)

#define ADC_1_UABH_A_INTR_VDAC_EMPTY_SET_SHIFT    ADC_1_UABH_A_INTR_VDAC_EMPTY_SHIFT
#define ADC_1_UABH_A_INTR_VDAC_EMPTY_SET_MASK     (1UL<<ADC_1_UABH_A_INTR_VDAC_EMPTY_SET_SHIFT)


/*INTR_MASK*/
#define ADC_1_UABH_A_INTR_COMP_MASK_SHIFT         ADC_1_UABH_A_INTR_COMP_SHIFT
#define ADC_1_UABH_A_INTR_COMP_MASK_MASK          (1UL<<ADC_1_UABH_A_INTR_COMP_MASK_SHIFT)

#define ADC_1_UABH_A_INTR_VDAC_EMPTY_MASK_SHIFT   ADC_1_UABH_A_INTR_VDAC_EMPTY_SHIFT
#define ADC_1_UABH_A_INTR_VDAC_EMPTY_MASK_MASK    (1UL<<ADC_1_UABH_A_INTR_VDAC_EMPTY_MASK_SHIFT)


/*INTR_MASKED*/
#define ADC_1_UABH_A_INTR_COMP_MASKED_SHIFT       ADC_1_UABH_A_INTR_COMP_SHIFT
#define ADC_1_UABH_A_INTR_COMP_MASKED_MASK        (1UL<<ADC_1_UABH_A_INTR_COMP_MASKED_SHIFT)

#define ADC_1_UABH_A_INTR_VDAC_EMPTY_MASKED_SHIFT ADC_1_UABH_A_INTR_VDAC_EMPTY_SHIFT
#define ADC_1_UABH_A_INTR_VDAC_EMPTY_MASKED_MASK  (1UL<<ADC_1_UABH_A_INTR_VDAC_EMPTY_MASKED_SHIFT)


/*OA_CTRL*/
#define ADC_1_UABH_A_OA_PWR_SHIFT                 CyUAB_OA_PWR_SHIFT
#define ADC_1_UABH_A_OA_PWR_MASK                  (0x7UL<<ADC_1_UABH_A_OA_PWR_SHIFT)

#define ADC_1_UABH_A_CMP_PWR_SHIFT                CyUAB_CMP_PWR_SHIFT
#define ADC_1_UABH_A_CMP_PWR_MASK                 (0x7UL<<ADC_1_UABH_A_CMP_PWR_SHIFT)

#define ADC_1_UABH_A_CMP_EDGE_SHIFT               CyUAB_CMP_EDGE_SHIFT
#define ADC_1_UABH_A_CMP_EDGE_MASK                (0x3UL<<ADC_1_UABH_A_CMP_EDGE_SHIFT)
#define ADC_1_UABH_A_CMP_EDGE_DISABLE             (0UL)
#define ADC_1_UABH_A_CMP_EDGE_RISING              (1UL)
#define ADC_1_UABH_A_CMP_EDGE_FALLING             (2UL)
#define ADC_1_UABH_A_CMP_EDGE_BOTH                (3UL)

#define ADC_1_UABH_A_CMP_DSI_LEVEL_SHIFT          CyUAB_CMP_DSI_LEVEL_SHIFT
#define ADC_1_UABH_A_CMP_DSI_LEVEL_MASK           (1UL<<ADC_1_UABH_A_CMP_DSI_LEVEL_SHIFT)

#define ADC_1_UABH_A_CTRL_SPARE_SHIFT             CyUAB_CTRL_SPARE_SHIFT
#define ADC_1_UABH_A_CTRL_SPARE_MASK              (1UL<<ADC_1_UABH_A_CTRL_SPARE_SHIFT)

#define ADC_1_UABH_A_REF_PWR_SHIFT                CyUAB_REF_PWR_SHIFT
#define ADC_1_UABH_A_REF_PWR_MASK                 (0x7UL<<ADC_1_UABH_A_REF_PWR_SHIFT)

#define ADC_1_UABH_A_REF_PTS_SHIFT                CyUAB_REF_PTS_SHIFT
#define ADC_1_UABH_A_REF_PTS_MASK                 (1UL<<ADC_1_UABH_A_REF_PTS_SHIFT)

#define ADC_1_UABH_A_AGND_PWR_SHIFT               CyUAB_AGND_PWR_SHIFT
#define ADC_1_UABH_A_AGND_PWR_MASK                (0x7UL<<ADC_1_UABH_A_AGND_PWR_SHIFT)

#define ADC_1_UABH_A_AGND_PTS_SHIFT               CyUAB_AGND_PTS_SHIFT
#define ADC_1_UABH_A_AGND_PTS_MASK                (1UL<<ADC_1_UABH_A_AGND_PTS_SHIFT)

#define ADC_1_UABH_A_AGND_TIED_SHIFT              CyUAB_AGND_TIED_SHIFT
#define ADC_1_UABH_A_AGND_TIED_MASK               (1UL<<ADC_1_UABH_A_AGND_TIED_SHIFT)

#define ADC_1_UABH_A_REF_TIED_SHIFT               CyUAB_REF_TIED_SHIFT
#define ADC_1_UABH_A_REF_TIED_MASK                (1UL<<ADC_1_UABH_A_REF_TIED_SHIFT)    
    
#define ADC_1_UABH_A_UAB_PWR_SHIFT                CyUAB_UAB_PWR_SHIFT
#define ADC_1_UABH_A_UAB_PWR_MASK                 (0x3UL<<ADC_1_UABH_A_UAB_PWR_SHIFT)
#define ADC_1_UABH_A_UAB_PWR_NORMAL               (0UL)
#define ADC_1_UABH_A_UAB_PWR_ULTRA_LOW            (1UL)
#define ADC_1_UABH_A_UAB_PWR_ULTRA_HIGH           (2UL)
#define ADC_1_UABH_A_UAB_PWR_Reserved             (3UL)


/*CAP_CTRL*/
#define ADC_1_UABH_A_CB_GND_SHIFT                 CyUAB_CB_GND_SHIFT
#define ADC_1_UABH_A_CB_GND_MASK                  (1UL<<ADC_1_UABH_A_CB_GND_SHIFT)

#define ADC_1_UABH_A_CC_GND_SHIFT                 CyUAB_CC_GND_SHIFT
#define ADC_1_UABH_A_CC_GND_MASK                  (1UL<<ADC_1_UABH_A_CC_GND_SHIFT)

#define ADC_1_UABH_A_FRC_SIGN_BIT_SHIFT           CyUAB_FRC_SIGN_BIT_SHIFT
#define ADC_1_UABH_A_FRC_SIGN_BIT_MASK            (1UL<<CyUAB_FRC_SIGN_BIT_SHIFT)

#define ADC_1_UABH_A_DAC_MODE_EN_SHIFT            CyUAB_DAC_MODE_EN_SHIFT
#define ADC_1_UABH_A_DAC_MODE_EN_MASK             (1UL<<ADC_1_UABH_A_DAC_MODE_EN_SHIFT)

#define ADC_1_UABH_A_DAC_MODE_SHIFT               CyUAB_DAC_MODE_SHIFT
#define ADC_1_UABH_A_DAC_MODE_MASK                (0x3UL<<ADC_1_UABH_A_DAC_MODE_SHIFT)
#define ADC_1_UABH_A_DAC_MODE_UNSIGNED12          (0UL)
#define ADC_1_UABH_A_DAC_MODE_VIRT_SIGNED12       (1UL)
#define ADC_1_UABH_A_DAC_MODE_SIGNED13            (2UL)
#define ADC_1_UABH_A_DAC_MODE_RESERVED            (3UL)


/*CAP_ABCF_VAL, CAP_AB_VAL_NXT, and CAP_CF_VAL_NXT*/
#define ADC_1_UABH_A_CB_VAL_SHIFT                 CyUAB_CB_VAL_SHIFT
#define ADC_1_UABH_A_CB_VAL_MASK                  (0x3fUL<<ADC_1_UABH_A_CB_VAL_SHIFT)

#define ADC_1_UABH_A_CA_VAL_SHIFT                 CyUAB_CA_VAL_SHIFT
#define ADC_1_UABH_A_CA_VAL_MASK                  (0x3fUL<<ADC_1_UABH_A_CA_VAL_SHIFT)

#define ADC_1_UABH_A_SIGN_VAL_SHIFT               CyUAB_SIGN_VAL_SHIFT
#define ADC_1_UABH_A_SIGN_VAL_MASK                (1UL<<ADC_1_UABH_A_SIGN_VAL_SHIFT)

#define ADC_1_UABH_A_CB_64_SHIFT                  CyUAB_CB_64_SHIFT
#define ADC_1_UABH_A_CB_64_MASK                   (1UL<<ADC_1_UABH_A_CB_64_SHIFT)

#define ADC_1_UABH_A_CC_VAL_SHIFT                 CyUAB_CC_VAL_SHIFT
#define ADC_1_UABH_A_CC_VAL_MASK                  (0x3fUL<<ADC_1_UABH_A_CC_VAL_SHIFT)

#define ADC_1_UABH_A_CF_VAL_SHIFT                 CyUAB_CF_VAL_SHIFT
#define ADC_1_UABH_A_CF_VAL_MASK                  (0x1fUL<<ADC_1_UABH_A_CF_VAL_SHIFT)


/*CAP_CF_VAL_NXT*/
#define ADC_1_UABH_A_CC_VAL_UPDATE_SHIFT          CyUAB_CC_VAL_UPDATE_SHIFT
#define ADC_1_UABH_A_CC_VAL_UPDATE_MASK           (1UL<<ADC_1_UABH_A_CC_VAL_UPDATE_SHIFT)

#define ADC_1_UABH_A_CF_VAL_UPDATE_SHIFT          CyUAB_CF_VAL_UPDATE_SHIFT
#define ADC_1_UABH_A_CF_VAL_UPDATE_MASK           (1UL<<ADC_1_UABH_A_CF_VAL_UPDATE_SHIFT)


/*STARTUP_DELAY*/
#define ADC_1_UABH_A_STARTUP_DELAY_SHIFT          CyUAB_STARTUP_DELAY_SHIFT
#define ADC_1_UABH_A_STARTUP_DELAY_MASK           (0x0000ffffUL)

#define ADC_1_UABH_A_ALIGN_MODE_SHIFT             CyUAB_ALIGN_MODE_SHIFT
#define ADC_1_UABH_A_ALIGN_MODE_MASK              (1UL<<ADC_1_UABH_A_ALIGN_MODE_SHIFT)


/*SUBSAMPLE_CTRL*/
#define ADC_1_UABH_A_SUBSAMPLE_SHIFT              CyUAB_SUBSAMPLE_SHIFT
#define ADC_1_UABH_A_SUBSAMPLE_MASK               (0xffUL<<ADC_1_UABH_A_SUBSAMPLE_SHIFT)

#define ADC_1_UABH_A_SUBSAMPLE_INIT_SHIFT         CyUAB_SUBSAMPLE_INIT_SHIFT
#define ADC_1_UABH_A_SUBSAMPLE_INIT_MASK          (0xffUL<<ADC_1_UABH_A_SUBSAMPLE_INIT_SHIFT)


/*SW_STATIC*/
#define ADC_1_UABH_A_SW_G0_SHIFT                  CyUAB_SW_G0_SHIFT
#define ADC_1_UABH_A_SW_G0_MASK                   (1UL<<ADC_1_UABH_A_SW_G0_SHIFT)

#define ADC_1_UABH_A_SW_G1_SHIFT                  CyUAB_SW_G1_SHIFT
#define ADC_1_UABH_A_SW_G1_MASK                   (1UL<<ADC_1_UABH_A_SW_G1_SHIFT)

#define ADC_1_UABH_A_SW_G2_SHIFT                  CyUAB_SW_G2_SHIFT
#define ADC_1_UABH_A_SW_G2_MASK                   (1UL<<ADC_1_UABH_A_SW_G2_SHIFT)

#define ADC_1_UABH_A_SW_G3_SHIFT                  CyUAB_SW_G3_SHIFT
#define ADC_1_UABH_A_SW_G3_MASK                   (1UL<<ADC_1_UABH_A_SW_G3_SHIFT)

#define ADC_1_UABH_A_SW_RG_SHIFT                  CyUAB_SW_RG_SHIFT
#define ADC_1_UABH_A_SW_RG_MASK                   (1UL<<ADC_1_UABH_A_SW_RG_SHIFT)

#define ADC_1_UABH_A_SW_GG_SHIFT                  CyUAB_SW_GG_SHIFT
#define ADC_1_UABH_A_SW_GG_MASK                   (1UL<<ADC_1_UABH_A_SW_GG_SHIFT)

#define ADC_1_UABH_A_SW_RT_SHIFT                  CyUAB_SW_RT_SHIFT
#define ADC_1_UABH_A_SW_RT_MASK                   (1UL<<ADC_1_UABH_A_SW_RT_SHIFT)

#define ADC_1_UABH_A_SW_GT_SHIFT                  CyUAB_SW_GT_SHIFT
#define ADC_1_UABH_A_SW_GT_MASK                   (1UL<<ADC_1_UABH_A_SW_GT_SHIFT)

#define ADC_1_UABH_A_SW_QT_SHIFT                  CyUAB_SW_QT_SHIFT
#define ADC_1_UABH_A_SW_QT_MASK                   (1UL<<ADC_1_UABH_A_SW_QT_SHIFT)

#define ADC_1_UABH_A_EARLY_PS_SHIFT               CyUAB_EARLY_PS_SHIFT
#define ADC_1_UABH_A_EARLY_PS_MASK                (1UL<<ADC_1_UABH_A_EARLY_PS_SHIFT)

#define ADC_1_UABH_A_EARLY_PO_SHIFT               CyUAB_EARLY_PO_SHIFT
#define ADC_1_UABH_A_EARLY_PO_MASK                (1UL<<ADC_1_UABH_A_EARLY_PO_SHIFT)

#define ADC_1_UABH_A_STRB_RST_SEL_SHIFT           CyUAB_STRB_RST_SEL_SHIFT
#define ADC_1_UABH_A_STRB_RST_SEL_MASK            (0x1fUL<<ADC_1_UABH_A_STRB_RST_SEL_SHIFT)

#define ADC_1_UABH_A_STRB_RST_EN_SHIFT            CyUAB_STRB_RST_EN_SHIFT
#define ADC_1_UABH_A_STRB_RST_EN_MASK             (1UL<<ADC_1_UABH_A_STRB_RST_EN_SHIFT)


/*SW_MODBIT_SRC*/
#define ADC_1_UABH_A_MODBIT0_SRC_SEL_SHIFT        CyUAB_MODBIT0_SRC_SEL_SHIFT
#define ADC_1_UABH_A_MODBIT0_SRC_SEL_MASK         (0x1fUL<<ADC_1_UABH_A_MODBIT0_SRC_SEL_SHIFT)

#define ADC_1_UABH_A_MODBIT1_SRC_SEL_SHIFT        CyUAB_MODBIT1_SRC_SEL_SHIFT
#define ADC_1_UABH_A_MODBIT1_SRC_SEL_MASK         (0x1fUL<<ADC_1_UABH_A_MODBIT1_SRC_SEL_SHIFT)


/*SW_CA_IN0*/
#define ADC_1_UABH_A_SW_A0_MODBIT_SHIFT           CyUAB_SW_A0_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_A0_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_A0_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_A1_MODBIT_SHIFT           CyUAB_SW_A1_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_A1_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_A1_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_A2_MODBIT_SHIFT           CyUAB_SW_A2_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_A2_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_A2_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_A3_MODBIT_SHIFT           CyUAB_SW_A3_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_A3_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_A3_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_AP_SHIFT                  CyUAB_SW_AP_SHIFT
#define ADC_1_UABH_A_SW_AP_MASK                   (0xfUL<<ADC_1_UABH_A_SW_AP_SHIFT)

#define ADC_1_UABH_A_SW_AQ_SHIFT                  CyUAB_SW_AQ_SHIFT
#define ADC_1_UABH_A_SW_AQ_MASK                   (0xfUL<<ADC_1_UABH_A_SW_AQ_SHIFT)

/*SW_CA_IN1*/    
#define ADC_1_UABH_A_SW_AA_SHIFT                  CyUAB_SW_AA_SHIFT
#define ADC_1_UABH_A_SW_AA_MASK                   (0xfUL<<ADC_1_UABH_A_SW_AA_SHIFT)

#define ADC_1_UABH_A_SW_AR_MODBIT_SHIFT           CyUAB_SW_AR_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_AR_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_AR_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_AG_MODBIT_SHIFT           CyUAB_SW_AG_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_AG_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_AG_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_AV_MODBIT_SHIFT           CyUAB_SW_AV_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_AV_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_AV_MODBIT_SHIFT)


/*SW_CA_TOP*/
#define ADC_1_UABH_A_SW_RA_MODBIT_SHIFT           CyUAB_SW_RA_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_RA_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_RA_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_GA_MODBIT_SHIFT           CyUAB_SW_GA_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_GA_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_GA_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_VA_MODBIT_SHIFT           CyUAB_SW_VA_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_VA_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_VA_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_SA_SHIFT                  CyUAB_SW_SA_SHIFT
#define ADC_1_UABH_A_SW_SA_MASK                   (0xfUL<<ADC_1_UABH_A_SW_SA_SHIFT)


/*SW_CB_IN0*/
#define ADC_1_UABH_A_SW_B0_MODBIT_SHIFT           CyUAB_SW_B0_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_B0_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_B0_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_B1_MODBIT_SHIFT           CyUAB_SW_B1_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_B1_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_B1_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_B2_MODBIT_SHIFT           CyUAB_SW_B2_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_B2_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_B2_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_B3_MODBIT_SHIFT           CyUAB_SW_B3_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_B3_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_B3_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_BP_SHIFT                  CyUAB_SW_BP_SHIFT
#define ADC_1_UABH_A_SW_BP_MASK                   (0xfUL<<ADC_1_UABH_A_SW_BP_SHIFT)

#define ADC_1_UABH_A_SW_BQ_SHIFT                  CyUAB_SW_BQ_SHIFT
#define ADC_1_UABH_A_SW_BQ_MASK                   (0xfUL<<ADC_1_UABH_A_SW_BQ_SHIFT)


/*SW_CB_IN1*/
#define ADC_1_UABH_A_SW_BB_SHIFT                  CyUAB_SW_BB_SHIFT
#define ADC_1_UABH_A_SW_BB_MASK                   (0xfUL<<ADC_1_UABH_A_SW_BB_SHIFT)

#define ADC_1_UABH_A_SW_BR_MODBIT_SHIFT           CyUAB_SW_BR_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_BR_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_BR_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_BG_MODBIT_SHIFT           CyUAB_SW_BG_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_BG_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_BG_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_BV_MODBIT_SHIFT           CyUAB_SW_BV_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_BV_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_BV_MODBIT_SHIFT)


/*SW_CB_TOP*/
#define ADC_1_UABH_A_SW_RB_MODBIT_SHIFT           CyUAB_SW_RB_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_RB_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_RB_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_GB_MODBIT_SHIFT           CyUAB_SW_GB_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_GB_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_GB_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_VB_MODBIT_SHIFT           CyUAB_SW_VB_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_VB_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_VB_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_TB_SHIFT                  CyUAB_SW_TB_SHIFT
#define ADC_1_UABH_A_SW_TB_MASK                   (0xfUL<<ADC_1_UABH_A_SW_TB_SHIFT)

#define ADC_1_UABH_A_SW_SB_SHIFT                  CyUAB_SW_SB_SHIFT
#define ADC_1_UABH_A_SW_SB_MASK                   (0xfUL<<ADC_1_UABH_A_SW_SB_SHIFT)


/*SW_CC_IN0*/
#define ADC_1_UABH_A_SW_C0_MODBIT_SHIFT           CyUAB_SW_C0_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_C0_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_C0_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_C1_MODBIT_SHIFT           CyUAB_SW_C1_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_C1_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_C1_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_C2_MODBIT_SHIFT           CyUAB_SW_C2_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_C2_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_C2_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_C3_MODBIT_SHIFT           CyUAB_SW_C3_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_C3_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_C3_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_CP_SHIFT                  CyUAB_SW_CP_SHIFT
#define ADC_1_UABH_A_SW_CP_MASK                   (0xfUL<<ADC_1_UABH_A_SW_CP_SHIFT)

#define ADC_1_UABH_A_SW_CQ_SHIFT                  CyUAB_SW_CQ_SHIFT
#define ADC_1_UABH_A_SW_CQ_MASK                   (0xfUL<<ADC_1_UABH_A_SW_CQ_SHIFT)


/*SW_CC_IN1*/
#define ADC_1_UABH_A_SW_CC_SHIFT                  CyUAB_SW_CC_SHIFT
#define ADC_1_UABH_A_SW_CC_MASK                   (0xfUL<<ADC_1_UABH_A_SW_CC_SHIFT)

#define ADC_1_UABH_A_SW_CR_MODBIT_SHIFT           CyUAB_SW_CR_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_CR_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_CR_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_CG_MODBIT_SHIFT           CyUAB_SW_CG_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_CG_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_CG_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_CV_MODBIT_SHIFT           CyUAB_SW_CV_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_CV_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_CV_MODBIT_SHIFT)


/*SW_CC_TOP*/
#define ADC_1_UABH_A_SW_RC_MODBIT_SHIFT           CyUAB_SW_RC_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_RC_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_RC_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_GC_MODBIT_SHIFT           CyUAB_SW_GC_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_GC_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_GC_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_VC_MODBIT_SHIFT           CyUAB_SW_VC_MODBIT_SHIFT
#define ADC_1_UABH_A_SW_VC_MODBIT_MASK            (0xfUL<<ADC_1_UABH_A_SW_VC_MODBIT_SHIFT)

#define ADC_1_UABH_A_SW_TC_SHIFT                  CyUAB_SW_TC_SHIFT
#define ADC_1_UABH_A_SW_TC_MASK                   (0xfUL<<ADC_1_UABH_A_SW_TC_SHIFT)

#define ADC_1_UABH_A_SW_SC_SHIFT                  CyUAB_SW_SC_SHIFT
#define ADC_1_UABH_A_SW_SC_MASK                   (0xfUL<<ADC_1_UABH_A_SW_SC_SHIFT)

#define ADC_1_UABH_A_SW_ZC_SHIFT                  CyUAB_SW_ZC_SHIFT
#define ADC_1_UABH_A_SW_ZC_MASK                   (0xfUL<<ADC_1_UABH_A_SW_ZC_SHIFT)


/*SW_CF_BOT*/
#define ADC_1_UABH_A_SW_GF_SHIFT                  CyUAB_SW_GF_SHIFT
#define ADC_1_UABH_A_SW_GF_MASK                   (0xfUL<<ADC_1_UABH_A_SW_GF_SHIFT)

#define ADC_1_UABH_A_SW_PF_SHIFT                  CyUAB_SW_PF_SHIFT
#define ADC_1_UABH_A_SW_PF_MASK                   (0xfUL<<ADC_1_UABH_A_SW_PF_SHIFT)

#define ADC_1_UABH_A_SW_PS_SHIFT                  CyUAB_SW_PS_SHIFT
#define ADC_1_UABH_A_SW_PS_MASK                   (0xfUL<<ADC_1_UABH_A_SW_PS_SHIFT)

#define ADC_1_UABH_A_SW_PO_SHIFT                  CyUAB_SW_PO_SHIFT
#define ADC_1_UABH_A_SW_PO_MASK                   (0xfUL<<ADC_1_UABH_A_SW_PO_SHIFT)


/*SW_OTHER*/
#define ADC_1_UABH_A_CMP_FF_SHIFT                 CyUAB_CMP_FF_SHIFT
#define ADC_1_UABH_A_CMP_FF_MASK                  (0xfUL<<ADC_1_UABH_A_CMP_FF_SHIFT)

#define ADC_1_UABH_A_VALID_SHIFT                  CyUAB_VALID_SHIFT
#define ADC_1_UABH_A_VALID_MASK                   (0xfUL<<ADC_1_UABH_A_VALID_SHIFT)

#define ADC_1_UABH_A_TRIG_OUT_SHIFT               CyUAB_TRIG_OUT_SHIFT
#define ADC_1_UABH_A_TRIG_OUT_MASK                (0xfUL<<ADC_1_UABH_A_TRIG_OUT_SHIFT)

#define ADC_1_UABH_A_STROBE_SW_SHIFT              CyUAB_STROBE_SW_SHIFT
#define ADC_1_UABH_A_STROBE_SW_MASK               (0xfUL<<ADC_1_UABH_A_STROBE_SW_SHIFT)

#define ADC_1_UABH_A_STROBE_RST_SHIFT             CyUAB_STROBE_RST_SHIFT
#define ADC_1_UABH_A_STROBE_RST_MASK              (0xfUL<<ADC_1_UABH_A_STROBE_RST_SHIFT)


/*SW_BOOST_CTRL*/
#define ADC_1_UABH_A_CA_BOOST_SHIFT               CyUAB_CA_BOOST_SHIFT
#define ADC_1_UABH_A_CA_BOOST_MASK                (0xfUL<<ADC_1_UABH_A_CA_BOOST_SHIFT)

#define ADC_1_UABH_A_CB_BOOST_SHIFT               CyUAB_CB_BOOST_SHIFT
#define ADC_1_UABH_A_CB_BOOST_MASK                (0xfUL<<ADC_1_UABH_A_CB_BOOST_SHIFT)

#define ADC_1_UABH_A_CC_BOOST_SHIFT               CyUAB_CC_BOOST_SHIFT
#define ADC_1_UABH_A_CC_BOOST_MASK                (0xfUL<<ADC_1_UABH_A_CC_BOOST_SHIFT)

#define ADC_1_UABH_A_CF_BOOST_SHIFT               CyUAB_CF_BOOST_SHIFT
#define ADC_1_UABH_A_CF_BOOST_MASK                (0xfUL<<ADC_1_UABH_A_CF_BOOST_SHIFT)

#define ADC_1_UABH_A_SUM_BOOST_SHIFT              CyUAB_SUM_BOOST_SHIFT
#define ADC_1_UABH_A_SUM_BOOST_MASK               (0xfUL<<ADC_1_UABH_A_SUM_BOOST_SHIFT)

#define ADC_1_UABH_A_PUMP_WAVE_SHIFT              CyUAB_PUMP_WAVE_SHIFT
#define ADC_1_UABH_A_PUMP_WAVE_MASK               (0xfUL<<ADC_1_UABH_A_PUMP_WAVE_SHIFT)


/*SRAM_CTRL*/
#define ADC_1_UABH_A_LAST_STEP_SHIFT              CyUAB_LAST_STEP_SHIFT
#define ADC_1_UABH_A_LAST_STEP_MASK               (0xfUL<<ADC_1_UABH_A_LAST_STEP_SHIFT)

#define ADC_1_UABH_A_TRIG_SEL_SHIFT               CyUAB_TRIG_SEL_SHIFT
#define ADC_1_UABH_A_TRIG_SEL_MASK                (0x1fUL<<ADC_1_UABH_A_TRIG_SEL_SHIFT)

#define ADC_1_UABH_A_TRIGGER_EN_SHIFT             CyUAB_TRIGGER_EN_SHIFT
#define ADC_1_UABH_A_TRIGGER_EN_MASK              (1UL<<ADC_1_UABH_A_TRIGGER_EN_SHIFT)

#define ADC_1_UABH_A_RUN_SHIFT                    CyUAB_RUN_SHIFT
#define ADC_1_UABH_A_RUN_MASK                     (1UL<<ADC_1_UABH_A_RUN_SHIFT)


/*STAT*/
#define ADC_1_UABH_A_CURR_STEP_SHIFT              CyUAB_CURR_STEP_SHIFT
#define ADC_1_UABH_A_CURR_STEP_MASK               (0xfUL<<ADC_1_UABH_A_CURR_STEP_SHIFT)

#define ADC_1_UABH_A_COMP_SHIFT                   CyUAB_COMP_SHIFT
#define ADC_1_UABH_A_COMP_MASK                    (1UL<<ADC_1_UABH_A_COMP_SHIFT)

#define ADC_1_UABH_A_CURR_SUBSAMPLE_SHIFT         CyUAB_CURR_SUBSAMPLE_SHIFT
#define ADC_1_UABH_A_CURR_SUBSAMPLE_MASK          (0xffUL<<ADC_1_UABH_A_CURR_SUBSAMPLE_SHIFT)


/*SRAM*/
#define ADC_1_UABH_A_WAVE_STEP_SHIFT              CyUAB_WAVE_STEP_SHIFT
#define ADC_1_UABH_A_WAVE_STEP_MASK               (0x0000ffffUL)


/*CAP_TRIM*/
#define ADC_1_UABH_A_CBTC_VAL_SHIFT               CyUAB_CBTC_VAL_SHIFT
#define ADC_1_UABH_A_CBTC_VAL_MASK                (0x7UL<<ADC_1_UABH_A_CBTC_VAL_SHIFT)

#define ADC_1_UABH_A_CCTC_VAL_SHIFT               CyUAB_CCTC_VAL_SHIFT
#define ADC_1_UABH_A_CCTC_VAL_MASK                (0x7UL<<ADC_1_UABH_A_CCTC_VAL_SHIFT)


/*OA_TRIM*/
#define ADC_1_UABH_A_OA_OFFSET_SHIFT              CyUAB_OA_OFFSET_SHIFT
#define ADC_1_UABH_A_OA_OFFSET_MASK               (0xfUL<<ADC_1_UABH_A_OA_OFFSET_SHIFT)

#define ADC_1_UABH_A_REF_OFFSET_SHIFT             CyUAB_REF_OFFSET_SHIFT
#define ADC_1_UABH_A_REF_OFFSET_MASK              (0x1fUL<<ADC_1_UABH_A_REF_OFFSET_SHIFT)

#define ADC_1_UABH_A_AGND_OFFSET_SHIFT            CyUAB_AGND_OFFSET_SHIFT
#define ADC_1_UABH_A_AGND_OFFSET_MASK             (0x1fUL<<ADC_1_UABH_A_AGND_OFFSET_SHIFT)



#define ADC_1_UABH_A_DAC_NEXT_MASK (CyUAB_DAC_NEXT_MASK)


#endif
