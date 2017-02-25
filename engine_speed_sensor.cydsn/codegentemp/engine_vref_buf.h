/*******************************************************************************
* File Name: engine_vref_buf.h
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


#if !defined(CY_OPAMP_engine_vref_buf_H)
#define CY_OPAMP_engine_vref_buf_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} engine_vref_buf_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void engine_vref_buf_Init(void);
void engine_vref_buf_Enable(void);
void engine_vref_buf_Start(void);
void engine_vref_buf_Stop(void);
void engine_vref_buf_SetPower(uint32 power);
void engine_vref_buf_PumpControl(uint32 onOff);
void engine_vref_buf_Sleep(void);
void engine_vref_buf_Wakeup(void);
void engine_vref_buf_SaveConfig(void);
void engine_vref_buf_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define engine_vref_buf_LOW_POWER      (1u)
#define engine_vref_buf_MED_POWER      (2u)
#define engine_vref_buf_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define engine_vref_buf_PUMP_ON        (1u)
#define engine_vref_buf_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define engine_vref_buf_OUTPUT_CURRENT         (1u)
#define engine_vref_buf_POWER                  (3u)
#define engine_vref_buf_MODE                   (1u)
#define engine_vref_buf_OA_COMP_TRIM_VALUE     (3u)
#define engine_vref_buf_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  engine_vref_buf_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define engine_vref_buf_CTB_CTRL_REG       (*(reg32 *) engine_vref_buf_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define engine_vref_buf_CTB_CTRL_PTR       ( (reg32 *) engine_vref_buf_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define engine_vref_buf_CTB_CTRL_REG       (*(reg32 *) engine_vref_buf_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define engine_vref_buf_CTB_CTRL_PTR       ( (reg32 *) engine_vref_buf_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define engine_vref_buf_OA_RES_CTRL_REG    (*(reg32 *) engine_vref_buf_cy_psoc4_abuf__OA_RES_CTRL)
#define engine_vref_buf_OA_RES_CTRL_PTR    ( (reg32 *) engine_vref_buf_cy_psoc4_abuf__OA_RES_CTRL)
#define engine_vref_buf_OA_COMP_TRIM_REG   (*(reg32 *) engine_vref_buf_cy_psoc4_abuf__OA_COMP_TRIM)
#define engine_vref_buf_OA_COMP_TRIM_PTR   ( (reg32 *) engine_vref_buf_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* engine_vref_buf_CTB_CTRL_REG */
#define engine_vref_buf_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define engine_vref_buf_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define engine_vref_buf_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << engine_vref_buf_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define engine_vref_buf_CTB_CTRL_ENABLED               ((uint32) 0x01u << engine_vref_buf_CTB_CTRL_ENABLED_SHIFT)


/* engine_vref_buf_OA_RES_CTRL_REG */
#define engine_vref_buf_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define engine_vref_buf_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define engine_vref_buf_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define engine_vref_buf_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define engine_vref_buf_OA_PWR_MODE                ((uint32) 0x02u << engine_vref_buf_OA_PWR_MODE_SHIFT)
#define engine_vref_buf_OA_PWR_MODE_MASK           ((uint32) 0x03u << engine_vref_buf_OA_PWR_MODE_SHIFT)
#define engine_vref_buf_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << engine_vref_buf_OA_DRIVE_STR_SEL_SHIFT)
#define engine_vref_buf_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << engine_vref_buf_OA_DRIVE_STR_SEL_SHIFT)
#define engine_vref_buf_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << engine_vref_buf_OA_DRIVE_STR_SEL_SHIFT)
#define engine_vref_buf_OA_COMP_EN                 ((uint32) 0x00u << engine_vref_buf_OA_COMP_EN_SHIFT)
#define engine_vref_buf_OA_PUMP_EN                 ((uint32) 0x01u << engine_vref_buf_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define engine_vref_buf_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (engine_vref_buf_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define engine_vref_buf_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (engine_vref_buf_OA_DRIVE_STR_SEL_10X) : \
                                                                             (engine_vref_buf_OA_DRIVE_STR_SEL_1X))
#define engine_vref_buf_GET_OA_PWR_MODE(mode)          ((mode) & engine_vref_buf_OA_PWR_MODE_MASK)
#define engine_vref_buf_CHECK_PWR_MODE_OFF             (0u != (engine_vref_buf_OA_RES_CTRL_REG & \
                                                                engine_vref_buf_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define engine_vref_buf_CHECK_DEEPSLEEP_SUPPORT        (0u != engine_vref_buf_DEEPSLEEP_SUPPORT) 

#define engine_vref_buf_DEFAULT_CTB_CTRL (engine_vref_buf_GET_DEEPSLEEP_ON(engine_vref_buf_DEEPSLEEP_SUPPORT) | \
                                           engine_vref_buf_CTB_CTRL_ENABLED)

#define engine_vref_buf_DEFAULT_OA_RES_CTRL (engine_vref_buf_OA_COMP_EN | \
                                              engine_vref_buf_GET_OA_DRIVE_STR(engine_vref_buf_OUTPUT_CURRENT))

#define engine_vref_buf_DEFAULT_OA_COMP_TRIM_REG (engine_vref_buf_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define engine_vref_buf_LOWPOWER                   (engine_vref_buf_LOW_POWER)
#define engine_vref_buf_MEDPOWER                   (engine_vref_buf_MED_POWER)
#define engine_vref_buf_HIGHPOWER                  (engine_vref_buf_HIGH_POWER)

/* PUMP ON/OFF defines */
#define engine_vref_buf_PUMPON                     (engine_vref_buf_PUMP_ON)
#define engine_vref_buf_PUMPOFF                    (engine_vref_buf_PUMP_OFF)

#define engine_vref_buf_OA_CTRL                    (engine_vref_buf_CTB_CTRL_REG)
#define engine_vref_buf_OA_RES_CTRL                (engine_vref_buf_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define engine_vref_buf_OA_CTB_EN_SHIFT            (engine_vref_buf_CTB_CTRL_ENABLED_SHIFT)
#define engine_vref_buf_OA_PUMP_CTRL_SHIFT         (engine_vref_buf_OA_PUMP_EN_SHIFT)
#define engine_vref_buf_OA_PUMP_EN_MASK            (0x800u)
#define engine_vref_buf_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_engine_vref_buf_H */


/* [] END OF FILE */
