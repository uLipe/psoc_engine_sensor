/***************************************************************************//**
* \file     engine_sensor_pga.h
* \version  1.0
*
* \brief
*  This file contains the public API function prototypes and constants used in
*  the PGA_P4 Component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_P4_engine_sensor_pga_H) 
#define CY_PGA_P4_engine_sensor_pga_H 

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define engine_sensor_pga_VREF_MODE              (1u)
#define engine_sensor_pga_OUTPUT_MODE            (1u)
#define engine_sensor_pga_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

/**
* \addtogroup group_globals
* @{
*/
extern uint8 engine_sensor_pga_initVar;
/** @} globals */


/***************************************
*        Function Prototypes 
***************************************/

/**
* \addtogroup group_general
* @{
*/
void engine_sensor_pga_Init(void);
void engine_sensor_pga_Enable(void);
void engine_sensor_pga_Start(void);
void engine_sensor_pga_Stop(void);
void engine_sensor_pga_SetPower(uint32 powerLevel);
void engine_sensor_pga_SetGain(uint32 gainLevel);
void engine_sensor_pga_PumpControl(uint32 onOff);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void engine_sensor_pga_Sleep(void);
void engine_sensor_pga_Wakeup(void);
void engine_sensor_pga_SaveConfig(void);
void engine_sensor_pga_RestoreConfig(void);
/** @} power */


/**************************************
*           API Constants
**************************************/

/* Gain setting constants */
#define engine_sensor_pga__GAIN_1 0
#define engine_sensor_pga__GAIN_1_4 1
#define engine_sensor_pga__GAIN_2 2
#define engine_sensor_pga__GAIN_2_8 3
#define engine_sensor_pga__GAIN_4 4
#define engine_sensor_pga__GAIN_5_8 5
#define engine_sensor_pga__GAIN_10_7 7
#define engine_sensor_pga__GAIN_8 6
#define engine_sensor_pga__GAIN_21_3 9
#define engine_sensor_pga__GAIN_32 10
#define engine_sensor_pga__GAIN_16 8


/* Power setting constants */
#define engine_sensor_pga__LOW 1
#define engine_sensor_pga__MED 2
#define engine_sensor_pga__HIGH 3


/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup group_powerLevel
     * \brief Definitions for engine_sensor_pga_SetPower() function.
     *  @{
     */
    #define engine_sensor_pga_LOW                ((uint32)engine_sensor_pga__LOW)
    #define engine_sensor_pga_MED                ((uint32)engine_sensor_pga__MED)
    #define engine_sensor_pga_HIGH               ((uint32)engine_sensor_pga__HIGH)
    /** @} powerLevel */

    /** \addtogroup group_boostPump
     * \brief Definitions for engine_sensor_pga_PumpControl() function.
     *  @{
     */
    #define engine_sensor_pga_BOOST_ON           ((uint32)1u)
    #define engine_sensor_pga_BOOST_OFF          ((uint32)0u)
    /** @} boostPump */

    /** \addtogroup group_gain
     * \brief Definitions for engine_sensor_pga_SetGain() function.
     *  @{
     */
    #define engine_sensor_pga_GAIN_1             ((uint32)engine_sensor_pga__GAIN_1)
    #define engine_sensor_pga_GAIN_1_4           ((uint32)engine_sensor_pga__GAIN_1_4)
    #define engine_sensor_pga_GAIN_2             ((uint32)engine_sensor_pga__GAIN_2)
    #define engine_sensor_pga_GAIN_2_8           ((uint32)engine_sensor_pga__GAIN_2_8)
    #define engine_sensor_pga_GAIN_4             ((uint32)engine_sensor_pga__GAIN_4)
    #define engine_sensor_pga_GAIN_5_8           ((uint32)engine_sensor_pga__GAIN_5_8)
    #define engine_sensor_pga_GAIN_8             ((uint32)engine_sensor_pga__GAIN_8)
    #define engine_sensor_pga_GAIN_10_7          ((uint32)engine_sensor_pga__GAIN_10_7)
    #define engine_sensor_pga_GAIN_16            ((uint32)engine_sensor_pga__GAIN_16)
    #define engine_sensor_pga_GAIN_21_3          ((uint32)engine_sensor_pga__GAIN_21_3)
    #define engine_sensor_pga_GAIN_32            ((uint32)engine_sensor_pga__GAIN_32)
    /** @} gain */
/** @} group_constants */


/***************************************
* Registers
***************************************/

#define engine_sensor_pga_CTB_CTRL_REG           (*(reg32 *) engine_sensor_pga_cy_psoc4_abuf__CTB_CTB_CTRL)
#define engine_sensor_pga_CTB_CTRL_PTR           ( (reg32 *) engine_sensor_pga_cy_psoc4_abuf__CTB_CTB_CTRL)
#define engine_sensor_pga_OA_RES_CTRL_REG        (*(reg32 *) engine_sensor_pga_cy_psoc4_abuf__OA_RES_CTRL)
#define engine_sensor_pga_OA_RES_CTRL_PTR        ( (reg32 *) engine_sensor_pga_cy_psoc4_abuf__OA_RES_CTRL)
#define engine_sensor_pga_OA_SW_REG              (*(reg32 *) engine_sensor_pga_cy_psoc4_abuf__OA_SW)
#define engine_sensor_pga_OA_SW_PTR              ( (reg32 *) engine_sensor_pga_cy_psoc4_abuf__OA_SW)
#define engine_sensor_pga_OA_COMP_TRIM_REG       (*(reg32 *) engine_sensor_pga_cy_psoc4_abuf__OA_COMP_TRIM)
#define engine_sensor_pga_OA_COMP_TRIM_PTR       ( (reg32 *) engine_sensor_pga_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
* Register Constants
***************************************/

/* engine_sensor_pga_CTB_CTRL_REG */
#define engine_sensor_pga_DEEPSLEEP_ON_SHIFT     (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define engine_sensor_pga_ENABLED_SHIFT          (31u)   /* [31] Enable of the CTB IP */

#define engine_sensor_pga_DEEPSLEEP_ON           ((uint32)0x01u << engine_sensor_pga_DEEPSLEEP_ON_SHIFT)
#define engine_sensor_pga_ENABLED                ((uint32)0x01u << engine_sensor_pga_ENABLED_SHIFT)

/* engine_sensor_pga_OA_RES_CTRL_REG */
#define engine_sensor_pga_OA_PWR_MODE_SHIFT      (0u)    /* [1:0]    Power level */
#define engine_sensor_pga_OA_DRIVE_STR_SEL_SHIFT (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define engine_sensor_pga_OA_PUMP_EN_SHIFT       (11u)   /* [11]     Pump enable */
#define engine_sensor_pga_RES_TAP_SHIFT          (16u)   /* [19:16]  PGA gain (resistor tap point) */
#define engine_sensor_pga_C_FB_SHIFT             (24u)   /* [27:24]  Feedback Capacitor */

#define engine_sensor_pga_OA_PWR_MODE_MASK       ((uint32)0x03u << engine_sensor_pga_OA_PWR_MODE_SHIFT)
#define engine_sensor_pga_OA_DRIVE_STR_SEL_1X    ((uint32)0x00u << engine_sensor_pga_OA_DRIVE_STR_SEL_SHIFT)
#define engine_sensor_pga_OA_DRIVE_STR_SEL_10X   ((uint32)0x01u << engine_sensor_pga_OA_DRIVE_STR_SEL_SHIFT)
#define engine_sensor_pga_OA_DRIVE_STR_SEL_MASK  ((uint32)0x01u << engine_sensor_pga_OA_DRIVE_STR_SEL_SHIFT)
#define engine_sensor_pga_OA_PUMP_EN             ((uint32)0x01u << engine_sensor_pga_OA_PUMP_EN_SHIFT)
#define engine_sensor_pga_RES_TAP_MASK           ((uint32)0x0Fu << engine_sensor_pga_RES_TAP_SHIFT)
#define engine_sensor_pga_C_FB_MASK              ((uint32)0x0Fu << engine_sensor_pga_C_FB_SHIFT)

/** engine_sensor_pga_OA_COMP_TRIM_REG */
#define engine_sensor_pga_OA_COMP_TRIM_SHIFT     (0u)    /* [1:0]    Opamp Compensation Capacitor Trim */
#define engine_sensor_pga_OA_COMP_TRIM_MASK      ((uint32)0x03u << engine_sensor_pga_OA_COMP_TRIM_SHIFT)

/** engine_sensor_pga_OA_SW_REG */
#define engine_sensor_pga_RBOT_TO_VSSA_SHIFT     (28u)   /* Resistor bottom  to VSSA */
#define engine_sensor_pga_RBOT_TO_VSSA           ((uint32)0x01u << engine_sensor_pga_RBOT_TO_VSSA_SHIFT)


#endif /* CY_PGA_P4_engine_sensor_pga_H */


/* [] END OF FILE */
