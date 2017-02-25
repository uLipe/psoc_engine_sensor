/***************************************************************************//**
* \file     engine_sensor_pga_PVT.h
* \version  1.0
*
* \brief
*  This file contains the private constants and macros used in
*  the PGA_P4 Component code.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PGA_P4_engine_sensor_pga_PVT_H) 
#define CY_PGA_P4_engine_sensor_pga_PVT_H

#include "engine_sensor_pga.h"


/***************************************
*         Internal Constants
***************************************/
    
#define engine_sensor_pga_POWER                  ((uint32)3u)
#define engine_sensor_pga_GAIN                   ((uint32)8u)
    
#define engine_sensor_pga_POWER_MAX              (engine_sensor_pga_HIGH)
#define engine_sensor_pga_GAIN_MAX               (engine_sensor_pga_GAIN_32)

/* ((Gain steps / 2) + 1) */
#define engine_sensor_pga_COMP_TAB_HEIGHT        ((engine_sensor_pga_GAIN_MAX >> 1u) + 1u)
#define engine_sensor_pga_COMP_TAB_WIDTH         (engine_sensor_pga_POWER_MAX)
#define engine_sensor_pga_GET_COMP_TAB_GAIN_MASK (0x00000007u)

#define engine_sensor_pga_VREF_INTERNAL          (0u)
#define engine_sensor_pga_OUTPUT_MODE_10x        (1u)

#define engine_sensor_pga_DEFAULT_POWER          ((uint32)engine_sensor_pga_POWER << engine_sensor_pga_OA_PWR_MODE_SHIFT)
#define engine_sensor_pga_DEFAULT_GAIN           ((uint32)engine_sensor_pga_GAIN << engine_sensor_pga_RES_TAP_SHIFT)
#define engine_sensor_pga_DEFAULT_GAIN_POWER     (engine_sensor_pga_DEFAULT_GAIN | engine_sensor_pga_DEFAULT_POWER)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint32 engine_sensor_pga_internalGainPower;
extern const uint32 engine_sensor_pga_compTab[engine_sensor_pga_COMP_TAB_HEIGHT][engine_sensor_pga_COMP_TAB_WIDTH];


/***************************************
*       Macro Definitions
***************************************/

/* Returns true if component available in Deep Sleep power mode */
#define engine_sensor_pga_CHECK_DEEPSLEEP_SUPPORT (engine_sensor_pga_DEEPSLEEP_SUPPORT != 0u)
/* Returns true if component uses 10x (Class AB) output buffer mode*/
#define engine_sensor_pga_CHECK_OUTPUT_MODE      (engine_sensor_pga_OUTPUT_MODE == engine_sensor_pga_OUTPUT_MODE_10x)
#define engine_sensor_pga_GET_DEEPSLEEP_ON       ((engine_sensor_pga_CHECK_DEEPSLEEP_SUPPORT) ? \
                                                    (engine_sensor_pga_DEEPSLEEP_ON) : (0u))
#define engine_sensor_pga_GET_OA_DRIVE_STR       ((engine_sensor_pga_CHECK_OUTPUT_MODE) ? \
                                                    (engine_sensor_pga_OA_DRIVE_STR_SEL_10X) : \
                                                        (engine_sensor_pga_OA_DRIVE_STR_SEL_1X))
#define engine_sensor_pga_GET_POWER              (engine_sensor_pga_internalGainPower & \
                                                    engine_sensor_pga_OA_PWR_MODE_MASK)
#define engine_sensor_pga_DEFAULT_CTB_CTRL       (engine_sensor_pga_GET_DEEPSLEEP_ON | engine_sensor_pga_ENABLED)
#define engine_sensor_pga_DEFAULT_OA_RES_CTRL    (engine_sensor_pga_GET_OA_DRIVE_STR | engine_sensor_pga_OA_PUMP_EN)
#define engine_sensor_pga_DEFAULT_OA_RES_CTRL_MASK (engine_sensor_pga_OA_DRIVE_STR_SEL_MASK | engine_sensor_pga_OA_PUMP_EN)
#define engine_sensor_pga_GET_COMP_TAB_GAIN      ((engine_sensor_pga_internalGainPower >> \
                                                    (engine_sensor_pga_RES_TAP_SHIFT + 1u)) & \
                                                        engine_sensor_pga_GET_COMP_TAB_GAIN_MASK)
#define engine_sensor_pga_GET_COMP_TAB           (engine_sensor_pga_compTab[engine_sensor_pga_GET_COMP_TAB_GAIN] \
                                                                         [engine_sensor_pga_GET_POWER - 1u])
#define engine_sensor_pga_GET_C_FB               (engine_sensor_pga_GET_COMP_TAB & engine_sensor_pga_C_FB_MASK)
#define engine_sensor_pga_GET_OA_COMP_TRIM       (engine_sensor_pga_GET_COMP_TAB & engine_sensor_pga_OA_COMP_TRIM_MASK)


#endif /* CY_PGA_P4_engine_sensor_pga_PVT_H */

/* [] END OF FILE */
