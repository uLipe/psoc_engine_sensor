/***************************************************************************//**
* \file     engine_sensor_pga_PM.c  
* \version  1.0
*
* \brief
*  This file provides the power management source code to the API for PGA_P4 
*  Component.
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "engine_sensor_pga_PVT.h"


/*******************************************************************************
* Function Name: engine_sensor_pga_SaveConfig
****************************************************************************//**
*
*  Empty function. Included for consistency with other components.
*
*******************************************************************************/
void engine_sensor_pga_SaveConfig(void)
{
    /* Nothing to save as registers are System reset on retention flops */
}


/*******************************************************************************  
* Function Name: engine_sensor_pga_RestoreConfig
****************************************************************************//**
*
*  Empty function. Included for consistency with other components.
*
*******************************************************************************/
void engine_sensor_pga_RestoreConfig(void)
{
    /* Nothing to restore */
}


/*******************************************************************************   
* Function Name: engine_sensor_pga_Sleep
****************************************************************************//**
*
*  When the "Deep sleep operation" is disabled then the function disables 
*  component's operation and saves its configuration. Should be called 
*  just prior to entering sleep.
*  When the "Deep sleep operation" is enabled then the function does nothing
*  and the component continues to operate during Deep Sleep state.
*
*  \internal
*   The engine_sensor_pga_backup.enableState is modified 
*   depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void engine_sensor_pga_Sleep(void)
{
    #if(!engine_sensor_pga_CHECK_DEEPSLEEP_SUPPORT)
        if((engine_sensor_pga_OA_RES_CTRL_REG & engine_sensor_pga_OA_PWR_MODE_MASK) != 0u)
        {
            engine_sensor_pga_internalGainPower |= engine_sensor_pga_ENABLED;
            engine_sensor_pga_Stop();
        }
        else /* The component is disabled */
        {
            engine_sensor_pga_internalGainPower &= (uint32) ~engine_sensor_pga_ENABLED;
        }
        /* Save the configuration */
        engine_sensor_pga_SaveConfig();
    #endif /* (engine_sensor_pga_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: engine_sensor_pga_Wakeup
****************************************************************************//**
*
*  When the "Deep sleep operation" is disabled then the function enables
*  block's operation and restores its configuration. Should be called
*  just after awaking from sleep.
*  When the "Deep sleep operation" is enabled then the function does nothing
*  and the component continues to operate during Active state.
*
*  \internal
*   The engine_sensor_pga_backup.enableState is used to 
*   restore the enable state of block after wakeup from sleep mode.
* 
*******************************************************************************/
void engine_sensor_pga_Wakeup(void)
{
    #if(!engine_sensor_pga_CHECK_DEEPSLEEP_SUPPORT)
        /* Restore the configurations */
        engine_sensor_pga_RestoreConfig();
        /* Enables the component operation */
        if((engine_sensor_pga_internalGainPower & engine_sensor_pga_ENABLED) != 0u)
        {
            engine_sensor_pga_Enable();
        } /* Do nothing if component was disabled before */
    #endif /* (engine_sensor_pga_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */
