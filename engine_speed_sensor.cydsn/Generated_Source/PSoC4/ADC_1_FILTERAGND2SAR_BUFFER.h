/*******************************************************************************
* File Name: ADC_1_FILTERAGND2SAR_BUFFER.h
* Version 1.20
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Opamp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_ADC_1_FILTERAGND2SAR_BUFFER_H)
#define CY_OPAMP_ADC_1_FILTERAGND2SAR_BUFFER_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} ADC_1_FILTERAGND2SAR_BUFFER_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void ADC_1_FILTERAGND2SAR_BUFFER_Init(void);
void ADC_1_FILTERAGND2SAR_BUFFER_Enable(void);
void ADC_1_FILTERAGND2SAR_BUFFER_Start(void);
void ADC_1_FILTERAGND2SAR_BUFFER_Stop(void);
void ADC_1_FILTERAGND2SAR_BUFFER_SetPower(uint32 power);
void ADC_1_FILTERAGND2SAR_BUFFER_PumpControl(uint32 onOff);
void ADC_1_FILTERAGND2SAR_BUFFER_Sleep(void);
void ADC_1_FILTERAGND2SAR_BUFFER_Wakeup(void);
void ADC_1_FILTERAGND2SAR_BUFFER_SaveConfig(void);
void ADC_1_FILTERAGND2SAR_BUFFER_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define ADC_1_FILTERAGND2SAR_BUFFER_LOW_POWER      (1u)
#define ADC_1_FILTERAGND2SAR_BUFFER_MED_POWER      (2u)
#define ADC_1_FILTERAGND2SAR_BUFFER_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define ADC_1_FILTERAGND2SAR_BUFFER_PUMP_ON        (1u)
#define ADC_1_FILTERAGND2SAR_BUFFER_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define ADC_1_FILTERAGND2SAR_BUFFER_OUTPUT_CURRENT         (0u)
#define ADC_1_FILTERAGND2SAR_BUFFER_POWER                  (3u)
#define ADC_1_FILTERAGND2SAR_BUFFER_MODE                   (1u)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_COMP_TRIM_VALUE     (3u)
#define ADC_1_FILTERAGND2SAR_BUFFER_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  ADC_1_FILTERAGND2SAR_BUFFER_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_REG       (*(reg32 *) ADC_1_FILTERAGND2SAR_BUFFER_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_PTR       ( (reg32 *) ADC_1_FILTERAGND2SAR_BUFFER_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_REG       (*(reg32 *) ADC_1_FILTERAGND2SAR_BUFFER_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_PTR       ( (reg32 *) ADC_1_FILTERAGND2SAR_BUFFER_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_REG    (*(reg32 *) ADC_1_FILTERAGND2SAR_BUFFER_cy_psoc4_abuf__OA_RES_CTRL)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_PTR    ( (reg32 *) ADC_1_FILTERAGND2SAR_BUFFER_cy_psoc4_abuf__OA_RES_CTRL)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_COMP_TRIM_REG   (*(reg32 *) ADC_1_FILTERAGND2SAR_BUFFER_cy_psoc4_abuf__OA_COMP_TRIM)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_COMP_TRIM_PTR   ( (reg32 *) ADC_1_FILTERAGND2SAR_BUFFER_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_REG */
#define ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_ENABLED               ((uint32) 0x01u << ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_ENABLED_SHIFT)


/* ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_REG */
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define ADC_1_FILTERAGND2SAR_BUFFER_OA_PWR_MODE                ((uint32) 0x02u << ADC_1_FILTERAGND2SAR_BUFFER_OA_PWR_MODE_SHIFT)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_PWR_MODE_MASK           ((uint32) 0x03u << ADC_1_FILTERAGND2SAR_BUFFER_OA_PWR_MODE_SHIFT)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << ADC_1_FILTERAGND2SAR_BUFFER_OA_DRIVE_STR_SEL_SHIFT)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << ADC_1_FILTERAGND2SAR_BUFFER_OA_DRIVE_STR_SEL_SHIFT)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << ADC_1_FILTERAGND2SAR_BUFFER_OA_DRIVE_STR_SEL_SHIFT)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_COMP_EN                 ((uint32) 0x00u << ADC_1_FILTERAGND2SAR_BUFFER_OA_COMP_EN_SHIFT)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_EN                 ((uint32) 0x01u << ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define ADC_1_FILTERAGND2SAR_BUFFER_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define ADC_1_FILTERAGND2SAR_BUFFER_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (ADC_1_FILTERAGND2SAR_BUFFER_OA_DRIVE_STR_SEL_10X) : \
                                                                             (ADC_1_FILTERAGND2SAR_BUFFER_OA_DRIVE_STR_SEL_1X))
#define ADC_1_FILTERAGND2SAR_BUFFER_GET_OA_PWR_MODE(mode)          ((mode) & ADC_1_FILTERAGND2SAR_BUFFER_OA_PWR_MODE_MASK)
#define ADC_1_FILTERAGND2SAR_BUFFER_CHECK_PWR_MODE_OFF             (0u != (ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_REG & \
                                                                ADC_1_FILTERAGND2SAR_BUFFER_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define ADC_1_FILTERAGND2SAR_BUFFER_CHECK_DEEPSLEEP_SUPPORT        (0u != ADC_1_FILTERAGND2SAR_BUFFER_DEEPSLEEP_SUPPORT) 

#define ADC_1_FILTERAGND2SAR_BUFFER_DEFAULT_CTB_CTRL (ADC_1_FILTERAGND2SAR_BUFFER_GET_DEEPSLEEP_ON(ADC_1_FILTERAGND2SAR_BUFFER_DEEPSLEEP_SUPPORT) | \
                                           ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_ENABLED)

#define ADC_1_FILTERAGND2SAR_BUFFER_DEFAULT_OA_RES_CTRL (ADC_1_FILTERAGND2SAR_BUFFER_OA_COMP_EN | \
                                              ADC_1_FILTERAGND2SAR_BUFFER_GET_OA_DRIVE_STR(ADC_1_FILTERAGND2SAR_BUFFER_OUTPUT_CURRENT))

#define ADC_1_FILTERAGND2SAR_BUFFER_DEFAULT_OA_COMP_TRIM_REG (ADC_1_FILTERAGND2SAR_BUFFER_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define ADC_1_FILTERAGND2SAR_BUFFER_LOWPOWER                   (ADC_1_FILTERAGND2SAR_BUFFER_LOW_POWER)
#define ADC_1_FILTERAGND2SAR_BUFFER_MEDPOWER                   (ADC_1_FILTERAGND2SAR_BUFFER_MED_POWER)
#define ADC_1_FILTERAGND2SAR_BUFFER_HIGHPOWER                  (ADC_1_FILTERAGND2SAR_BUFFER_HIGH_POWER)

/* PUMP ON/OFF defines */
#define ADC_1_FILTERAGND2SAR_BUFFER_PUMPON                     (ADC_1_FILTERAGND2SAR_BUFFER_PUMP_ON)
#define ADC_1_FILTERAGND2SAR_BUFFER_PUMPOFF                    (ADC_1_FILTERAGND2SAR_BUFFER_PUMP_OFF)

#define ADC_1_FILTERAGND2SAR_BUFFER_OA_CTRL                    (ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_REG)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL                (ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_CTB_EN_SHIFT            (ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_ENABLED_SHIFT)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_CTRL_SHIFT         (ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_EN_SHIFT)
#define ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_EN_MASK            (0x800u)
#define ADC_1_FILTERAGND2SAR_BUFFER_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_ADC_1_FILTERAGND2SAR_BUFFER_H */


/* [] END OF FILE */
