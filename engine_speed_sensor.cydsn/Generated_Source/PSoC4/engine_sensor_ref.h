/***************************************************************************//**
* \file engine_sensor_ref.h
* \version 1.0
*
* \brief
*  This file provides constants and parameter values for the Programmable
*  Voltage Reference component.
*
* Note:
*  None
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PVref_P4_engine_sensor_ref_H)
#define CY_PVref_P4_engine_sensor_ref_H

#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define engine_sensor_ref_SEL_OUTPUT_VOLTAGE      (8u)
#define engine_sensor_ref_SEL_REFERENCE_SOURCE    (1u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} engine_sensor_ref_backup_struct;


/***************************************
*        Function Prototypes
***************************************/
/**
* \addtogroup group_general
* @{
*/
void engine_sensor_ref_Init(void);
void engine_sensor_ref_Enable(void);
void engine_sensor_ref_Start(void);
void engine_sensor_ref_Stop(void);
void engine_sensor_ref_SetTap(uint32 dividerTap);
void engine_sensor_ref_SetVRefSrc(uint32 reference);
/** @} group_general */
/**
* \addtogroup group_power
* @{
*/
void engine_sensor_ref_Sleep(void);
void engine_sensor_ref_Wakeup(void);
/** @} power */


/***************************************
*           Global Variables
***************************************/
/**
* \addtogroup group_globals
* @{
*/
extern uint8 engine_sensor_ref_initVar;
/** @} globals */


/***************************************
*           API Constants
***************************************/

#define engine_sensor_ref_VDDA_MVOLTS             (3300u)
#define engine_sensor_ref_BANDGAP_MVOLTS          (1200u)

#define engine_sensor_ref_BANDGAP_REFERENCE       (0u)
#define engine_sensor_ref_VDDA_REFERENCE          (1u)

#define engine_sensor_ref_PRB_CTRL_REG_INIT       (engine_sensor_ref_PRB_IP_ENABLE | \
            (uint32) ((uint32) engine_sensor_ref_SEL_REFERENCE_SOURCE << engine_sensor_ref_VDDA_ENABLE_POS))
#define engine_sensor_ref_PRB_REF_REG_INIT        ( \
            (uint32) ((uint32) engine_sensor_ref_SEL_REFERENCE_SOURCE << engine_sensor_ref_VREF_SUPPLY_SEL_POS) | \
            (uint32) ((uint32) (engine_sensor_ref_SEL_OUTPUT_VOLTAGE - 1u) << engine_sensor_ref_VREF_LEVEL_SEL_MASK_POS))


/***************************************
*             Registers
***************************************/

/* Programmable Voltage Reference IP block registers */
#define engine_sensor_ref_PRB_CTRL_REG            (*(reg32*) CYREG_PASS_PRB_CTRL)
#define engine_sensor_ref_PRB_CTRL_PTR            ( (reg32*) CYREG_PASS_PRB_CTRL)
#define engine_sensor_ref_PRB_REF_REG             (*(reg32*) engine_sensor_ref_cy_psoc4_pref_PRB_REF)
#define engine_sensor_ref_PRB_REF_PTR             ( (reg32*) engine_sensor_ref_cy_psoc4_pref_PRB_REF)


/***************************************
*       Register Constants
***************************************/

/* Global Programmable Voltage Reference IP block register bits */
#define engine_sensor_ref_VBGR_BUF_GAIN_MASK_POS  (0u)
#define engine_sensor_ref_VDDA_ENABLE_POS         (4u)
#define engine_sensor_ref_DEEPSLEEP_ON_POS        (30u)
#define engine_sensor_ref_PRB_IP_ENABLE_POS       (31u)

#define engine_sensor_ref_VBGR_BUF_GAIN_MASK      ((uint32) ((uint32) 0x03u << engine_sensor_ref_VBGR_BUF_GAIN_MASK_POS))
#define engine_sensor_ref_VDDA_ENABLE             ((uint32) ((uint32) 0x01u << engine_sensor_ref_VDDA_ENABLE_POS))
#define engine_sensor_ref_DEEPSLEEP_ON            ((uint32) ((uint32) 0x01u << engine_sensor_ref_DEEPSLEEP_ON_POS))
#define engine_sensor_ref_PRB_IP_ENABLE           ((uint32) ((uint32) 0x01u << engine_sensor_ref_PRB_IP_ENABLE_POS))

/* VREF Control register bits */
#define engine_sensor_ref_VREF_ENABLE_POS         (0u)
#define engine_sensor_ref_VREF_SUPPLY_SEL_POS     (1u)
#define engine_sensor_ref_VREF_LEVEL_SEL_MASK_POS (4u)

#define engine_sensor_ref_VREF_ENABLE             ((uint32) ((uint32) 0x01u << engine_sensor_ref_VREF_ENABLE_POS))
#define engine_sensor_ref_VREF_SUPPLY_SEL         ((uint32) ((uint32) 0x01u << engine_sensor_ref_VREF_SUPPLY_SEL_POS))
#define engine_sensor_ref_VREF_LEVEL_SEL_MASK     ((uint32) ((uint32) 0x0Fu << engine_sensor_ref_VREF_LEVEL_SEL_MASK_POS))

#endif /* End CY_PVref_P4_engine_sensor_ref_H */


/* [] END OF FILE */
