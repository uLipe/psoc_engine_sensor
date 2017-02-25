/***************************************************************************//**
* \file engine_sensor_adc_PM.c  
* \version 1.20
*
* \brief
*  This file provides the power manager source code to the API for 
*  engine_sensor_adc component.
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

#include "engine_sensor_adc.h"

/**
* \addtogroup group_globals
* @{
*/
/** Contains configuration of engine_sensor_adc before sleep. Enable state is the
*   only data required to be preserved. */
static engine_sensor_adc_BACKUP_STRUCT  engine_sensor_adc_backup =
{
    0u,
};
/** @} globals */


/*******************************************************************************   
* Function Name: engine_sensor_adc_Sleep
****************************************************************************//**
*
* \brief This is the preferred routine to prepare the component for sleep. The 
* engine_sensor_adc_Sleep() routine saves the current component state. Then it 
* calls the engine_sensor_adc_Stop() function and calls 
* engine_sensor_adc_SaveConfig() to save the hardware configuration.
* 
* Call the engine_sensor_adc_Sleep() function before calling the 
* CySysPmDeepSleep() or the CySysPmHibernate() function. See the PSoC Creator 
* System Reference Guide for more information about power-management functions.
* 
* \param None
* 
* \return None
*
* \sideeffect If this function is called twice in the enable state of the 
* component, the disabled state of the component will be stored. So 
* engine_sensor_adc_Enable() and engine_sensor_adc_StartConvert() must be called 
* after engine_sensor_adc_Wakeup() in this case.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_engine_sensor_adc_Sleep
*
* \globalvars
*  \ref engine_sensor_adc_backup (W)
*
* \globalvars
*  \ref engine_sensor_adc_backup
*
*******************************************************************************/
void engine_sensor_adc_Sleep(void) 
{
    uint32 dftRegVal = (uint32) engine_sensor_adc_SAR_DFT_CTRL_REG;

    engine_sensor_adc_backup.enableState = 0u;
    
    /* Save nonretention SAR_DFT_CTRL register state. */
    if((dftRegVal & engine_sensor_adc_SAR_DFT_CTRL_DCEN_MSK) != 0u)
    {
        engine_sensor_adc_backup.enableState |= engine_sensor_adc_SLEEP_DFT_DCEN;
    }
    if((dftRegVal & engine_sensor_adc_SAR_DFT_CTRL_DLY_INC_MSK) != 0u)
    {
        engine_sensor_adc_backup.enableState |= engine_sensor_adc_SLEEP_DFT_DLY_INC;
    }
    
    /* During deepsleep/ hibernate mode keep SARMUX active, i.e. do not open
    *   all switches (disconnect), to be used for ADFT
    */
    engine_sensor_adc_SAR_DFT_CTRL_REG |= engine_sensor_adc_SAR_DFT_CTRL_ADFT_OVERRIDE_MSK;
    
    if((engine_sensor_adc_SAR_CTRL_REG  & engine_sensor_adc_SAR_CTRL_ENABLED_MSK) != 0u)
    {
        engine_sensor_adc_backup.enableState |= engine_sensor_adc_ENABLED;
        if((engine_sensor_adc_SAR_SAMPLE_CTRL_REG & engine_sensor_adc_SAR_SAMPLE_CTRL_CONTINUOUS_MSK) != 0u)
        {
            engine_sensor_adc_backup.enableState |= engine_sensor_adc_STARTED;
        }

        engine_sensor_adc_StopConvert();
        engine_sensor_adc_Stop();
        
        /* Disable the SAR internal pump before entering the chip low power mode */
        if((engine_sensor_adc_SAR_CTRL_REG & engine_sensor_adc_SAR_CTRL_BOOSTPUMP_EN_MSK) != 0u)
        {
            engine_sensor_adc_SAR_CTRL_REG &= (uint32)~engine_sensor_adc_SAR_CTRL_BOOSTPUMP_EN_MSK;
            engine_sensor_adc_backup.enableState |= engine_sensor_adc_BOOSTPUMP_ENABLED;
        }
    }
}


/*******************************************************************************
* Function Name: engine_sensor_adc_Wakeup
****************************************************************************//**
*
* \brief This is the preferred routine to restore the component to the state when 
* engine_sensor_adc_Sleep() was called. The engine_sensor_adc_Wakeup() function 
* calls the engine_sensor_adc_RestoreConfig() function to restore the 
* configuration. If the component was enabled before the engine_sensor_adc_Sleep() 
* function was called, the engine_sensor_adc_Wakeup() function also re-enables the 
* component.
*
* \param None
* 
* \return None
*
* \sideeffect
* Calling this function without previously calling engine_sensor_adc_Sleep() may lead to 
* unpredictable results.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_engine_sensor_adc_Wakeup
*
* \globalvars
*  \ref engine_sensor_adc_backup (R)
*
* \globalvars
*  \ref engine_sensor_adc_backup
* 
*******************************************************************************/
void engine_sensor_adc_Wakeup(void)
{
    uint32 dftRegVal = (uint32)engine_sensor_adc_SAR_DFT_CTRL_HIZ_MSK;
    
    /* Restore nonretention SAR_DFT_CTRL register state. */
    if ((engine_sensor_adc_backup.enableState & engine_sensor_adc_SLEEP_DFT_DCEN) != 0u)
    {
        dftRegVal |= engine_sensor_adc_SAR_DFT_CTRL_DCEN_MSK;
    }
    if ((engine_sensor_adc_backup.enableState & engine_sensor_adc_SLEEP_DFT_DLY_INC) != 0u)
    {
        dftRegVal |= engine_sensor_adc_SAR_DFT_CTRL_DLY_INC_MSK;
    }
    engine_sensor_adc_SAR_DFT_CTRL_REG = dftRegVal;
    
    if((engine_sensor_adc_backup.enableState & engine_sensor_adc_ENABLED) != 0u)
    {
        /* Enable the SAR internal pump  */
        if((engine_sensor_adc_backup.enableState & engine_sensor_adc_BOOSTPUMP_ENABLED) != 0u)
        {
            engine_sensor_adc_SAR_CTRL_REG |= engine_sensor_adc_SAR_CTRL_BOOSTPUMP_EN_MSK;
        }
        
        engine_sensor_adc_Enable();
        
        if((engine_sensor_adc_backup.enableState & engine_sensor_adc_STARTED) != 0u)
        {
            engine_sensor_adc_StartConvert();
        }
    }
}

/* ****************************************************************************
* Function Name: engine_sensor_adc_SaveConfig
****************************************************************************//*
*
* \brief Saves the current configuration of engine_sensor_adc non-retention registers.
*
* \param None
* 
* \return None
* 
* \sideeffect None
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_engine_sensor_adc_SaveConfig
*
* 
*******************************************************************************/
void engine_sensor_adc_SaveConfig(void)
{
     /* All configuration registers are marked as [reset_all_retention] */
}

/* ****************************************************************************
* Function Name: engine_sensor_adc_RestoreConfig
****************************************************************************//*
*
* \brief Restores the configuration of engine_sensor_adc non-retention registers.
* 
* \param None
* 
* \return None
*
* \sideeffect Calling this function without previously calling 
* engine_sensor_adc_SaveConfig() or engine_sensor_adc_Sleep will lead to 
* unpredictable results.
*
* <b>Code Snippet</b>
*  \snippet main.c snippet_engine_sensor_adc_RestoreConfig
*
* 
*******************************************************************************/
void engine_sensor_adc_RestoreConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}

/* [] END OF FILE */
