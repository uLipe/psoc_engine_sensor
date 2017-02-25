/*******************************************************************************
* File Name: engine_sensor_adc_FILTERAGND2SAR_BUFFER_PM.c
* Version 1.20
*
* Description:
*  This file provides the power management source code to the API for the
*  Opamp (Analog Buffer) component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "engine_sensor_adc_FILTERAGND2SAR_BUFFER.h"

#if(!engine_sensor_adc_FILTERAGND2SAR_BUFFER_CHECK_DEEPSLEEP_SUPPORT)
    static engine_sensor_adc_FILTERAGND2SAR_BUFFER_BACKUP_STRUCT engine_sensor_adc_FILTERAGND2SAR_BUFFER_backup =
    {
        0u, /* enableState */
    };
#endif /* (engine_sensor_adc_FILTERAGND2SAR_BUFFER_CHECK_DEEPSLEEP_SUPPORT) */


/*******************************************************************************
* Function Name: engine_sensor_adc_FILTERAGND2SAR_BUFFER_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void engine_sensor_adc_FILTERAGND2SAR_BUFFER_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: engine_sensor_adc_FILTERAGND2SAR_BUFFER_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void engine_sensor_adc_FILTERAGND2SAR_BUFFER_RestoreConfig(void)
{
    
}


/*******************************************************************************
* Function Name: engine_sensor_adc_FILTERAGND2SAR_BUFFER_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The Sleep() API 
*  saves the current component state. Call the Sleep() function before calling the 
*  CySysPmDeepSleep() or the CySysPmHibernate() functions. The "Deep sleep operation" 
*  option has an influence on this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  engine_sensor_adc_FILTERAGND2SAR_BUFFER_backup: The structure field 'enableState' is modified
*  depending on the enable state of the block before entering the sleep mode.
*
*******************************************************************************/
void engine_sensor_adc_FILTERAGND2SAR_BUFFER_Sleep(void)
{
#if(!engine_sensor_adc_FILTERAGND2SAR_BUFFER_CHECK_DEEPSLEEP_SUPPORT)
    if(engine_sensor_adc_FILTERAGND2SAR_BUFFER_CHECK_PWR_MODE_OFF)
    {
        engine_sensor_adc_FILTERAGND2SAR_BUFFER_backup.enableState = 1u;
        engine_sensor_adc_FILTERAGND2SAR_BUFFER_Stop();
    }
    else /* The component is disabled */
    {
        engine_sensor_adc_FILTERAGND2SAR_BUFFER_backup.enableState = 0u;
    }
#endif /* (engine_sensor_adc_FILTERAGND2SAR_BUFFER_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: engine_sensor_adc_FILTERAGND2SAR_BUFFER_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when Sleep() 
*  is called. If the component has been enabled before the Sleep() function is 
*  called, the Wakeup() function will also re-enable the component.
*  The "Deep sleep operation" option has an influence on this function
*  implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  engine_sensor_adc_FILTERAGND2SAR_BUFFER_backup: The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void engine_sensor_adc_FILTERAGND2SAR_BUFFER_Wakeup(void)
{
#if(!engine_sensor_adc_FILTERAGND2SAR_BUFFER_CHECK_DEEPSLEEP_SUPPORT)
    if(0u != engine_sensor_adc_FILTERAGND2SAR_BUFFER_backup.enableState)
    {
        /* Enable Opamp's operation */
        engine_sensor_adc_FILTERAGND2SAR_BUFFER_Enable();
    } /* Do nothing if Opamp was disabled before */
#endif /* (engine_sensor_adc_FILTERAGND2SAR_BUFFER_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */
