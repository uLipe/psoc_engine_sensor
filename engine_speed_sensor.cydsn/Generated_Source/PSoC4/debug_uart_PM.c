/***************************************************************************//**
* \file debug_uart_PM.c
* \version 3.20
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "debug_uart.h"
#include "debug_uart_PVT.h"

#if(debug_uart_SCB_MODE_I2C_INC)
    #include "debug_uart_I2C_PVT.h"
#endif /* (debug_uart_SCB_MODE_I2C_INC) */

#if(debug_uart_SCB_MODE_EZI2C_INC)
    #include "debug_uart_EZI2C_PVT.h"
#endif /* (debug_uart_SCB_MODE_EZI2C_INC) */

#if(debug_uart_SCB_MODE_SPI_INC || debug_uart_SCB_MODE_UART_INC)
    #include "debug_uart_SPI_UART_PVT.h"
#endif /* (debug_uart_SCB_MODE_SPI_INC || debug_uart_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(debug_uart_SCB_MODE_UNCONFIG_CONST_CFG || \
   (debug_uart_SCB_MODE_I2C_CONST_CFG   && (!debug_uart_I2C_WAKE_ENABLE_CONST))   || \
   (debug_uart_SCB_MODE_EZI2C_CONST_CFG && (!debug_uart_EZI2C_WAKE_ENABLE_CONST)) || \
   (debug_uart_SCB_MODE_SPI_CONST_CFG   && (!debug_uart_SPI_WAKE_ENABLE_CONST))   || \
   (debug_uart_SCB_MODE_UART_CONST_CFG  && (!debug_uart_UART_WAKE_ENABLE_CONST)))

    debug_uart_BACKUP_STRUCT debug_uart_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: debug_uart_Sleep
****************************************************************************//**
*
*  Prepares the debug_uart component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the debug_uart_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void debug_uart_Sleep(void)
{
#if(debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)

    if(debug_uart_SCB_WAKE_ENABLE_CHECK)
    {
        if(debug_uart_SCB_MODE_I2C_RUNTM_CFG)
        {
            debug_uart_I2CSaveConfig();
        }
        else if(debug_uart_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            debug_uart_EzI2CSaveConfig();
        }
    #if(!debug_uart_CY_SCBIP_V1)
        else if(debug_uart_SCB_MODE_SPI_RUNTM_CFG)
        {
            debug_uart_SpiSaveConfig();
        }
        else if(debug_uart_SCB_MODE_UART_RUNTM_CFG)
        {
            debug_uart_UartSaveConfig();
        }
    #endif /* (!debug_uart_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        debug_uart_backup.enableState = (uint8) debug_uart_GET_CTRL_ENABLED;

        if(0u != debug_uart_backup.enableState)
        {
            debug_uart_Stop();
        }
    }

#else

    #if (debug_uart_SCB_MODE_I2C_CONST_CFG && debug_uart_I2C_WAKE_ENABLE_CONST)
        debug_uart_I2CSaveConfig();

    #elif (debug_uart_SCB_MODE_EZI2C_CONST_CFG && debug_uart_EZI2C_WAKE_ENABLE_CONST)
        debug_uart_EzI2CSaveConfig();

    #elif (debug_uart_SCB_MODE_SPI_CONST_CFG && debug_uart_SPI_WAKE_ENABLE_CONST)
        debug_uart_SpiSaveConfig();

    #elif (debug_uart_SCB_MODE_UART_CONST_CFG && debug_uart_UART_WAKE_ENABLE_CONST)
        debug_uart_UartSaveConfig();

    #else

        debug_uart_backup.enableState = (uint8) debug_uart_GET_CTRL_ENABLED;

        if(0u != debug_uart_backup.enableState)
        {
            debug_uart_Stop();
        }

    #endif /* defined (debug_uart_SCB_MODE_I2C_CONST_CFG) && (debug_uart_I2C_WAKE_ENABLE_CONST) */

#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: debug_uart_Wakeup
****************************************************************************//**
*
*  Prepares the debug_uart component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the debug_uart_Wakeup() function without first calling the 
*   debug_uart_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void debug_uart_Wakeup(void)
{
#if(debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)

    if(debug_uart_SCB_WAKE_ENABLE_CHECK)
    {
        if(debug_uart_SCB_MODE_I2C_RUNTM_CFG)
        {
            debug_uart_I2CRestoreConfig();
        }
        else if(debug_uart_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            debug_uart_EzI2CRestoreConfig();
        }
    #if(!debug_uart_CY_SCBIP_V1)
        else if(debug_uart_SCB_MODE_SPI_RUNTM_CFG)
        {
            debug_uart_SpiRestoreConfig();
        }
        else if(debug_uart_SCB_MODE_UART_RUNTM_CFG)
        {
            debug_uart_UartRestoreConfig();
        }
    #endif /* (!debug_uart_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != debug_uart_backup.enableState)
        {
            debug_uart_Enable();
        }
    }

#else

    #if (debug_uart_SCB_MODE_I2C_CONST_CFG  && debug_uart_I2C_WAKE_ENABLE_CONST)
        debug_uart_I2CRestoreConfig();

    #elif (debug_uart_SCB_MODE_EZI2C_CONST_CFG && debug_uart_EZI2C_WAKE_ENABLE_CONST)
        debug_uart_EzI2CRestoreConfig();

    #elif (debug_uart_SCB_MODE_SPI_CONST_CFG && debug_uart_SPI_WAKE_ENABLE_CONST)
        debug_uart_SpiRestoreConfig();

    #elif (debug_uart_SCB_MODE_UART_CONST_CFG && debug_uart_UART_WAKE_ENABLE_CONST)
        debug_uart_UartRestoreConfig();

    #else

        if(0u != debug_uart_backup.enableState)
        {
            debug_uart_Enable();
        }

    #endif /* (debug_uart_I2C_WAKE_ENABLE_CONST) */

#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
