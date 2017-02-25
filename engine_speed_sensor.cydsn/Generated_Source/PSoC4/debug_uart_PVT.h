/***************************************************************************//**
* \file .h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_debug_uart_H)
#define CY_SCB_PVT_debug_uart_H

#include "debug_uart.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define debug_uart_SetI2CExtClkInterruptMode(interruptMask) debug_uart_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define debug_uart_ClearI2CExtClkInterruptSource(interruptMask) debug_uart_CLEAR_INTR_I2C_EC(interruptMask)
#define debug_uart_GetI2CExtClkInterruptSource()                (debug_uart_INTR_I2C_EC_REG)
#define debug_uart_GetI2CExtClkInterruptMode()                  (debug_uart_INTR_I2C_EC_MASK_REG)
#define debug_uart_GetI2CExtClkInterruptSourceMasked()          (debug_uart_INTR_I2C_EC_MASKED_REG)

#if (!debug_uart_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define debug_uart_SetSpiExtClkInterruptMode(interruptMask) \
                                                                debug_uart_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define debug_uart_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                debug_uart_CLEAR_INTR_SPI_EC(interruptMask)
    #define debug_uart_GetExtSpiClkInterruptSource()                 (debug_uart_INTR_SPI_EC_REG)
    #define debug_uart_GetExtSpiClkInterruptMode()                   (debug_uart_INTR_SPI_EC_MASK_REG)
    #define debug_uart_GetExtSpiClkInterruptSourceMasked()           (debug_uart_INTR_SPI_EC_MASKED_REG)
#endif /* (!debug_uart_CY_SCBIP_V1) */

#if(debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void debug_uart_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (debug_uart_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_debug_uart_CUSTOM_INTR_HANDLER)
    extern cyisraddress debug_uart_customIntrHandler;
#endif /* !defined (CY_REMOVE_debug_uart_CUSTOM_INTR_HANDLER) */
#endif /* (debug_uart_SCB_IRQ_INTERNAL) */

extern debug_uart_BACKUP_STRUCT debug_uart_backup;

#if(debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 debug_uart_scbMode;
    extern uint8 debug_uart_scbEnableWake;
    extern uint8 debug_uart_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 debug_uart_mode;
    extern uint8 debug_uart_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * debug_uart_rxBuffer;
    extern uint8   debug_uart_rxDataBits;
    extern uint32  debug_uart_rxBufferSize;

    extern volatile uint8 * debug_uart_txBuffer;
    extern uint8   debug_uart_txDataBits;
    extern uint32  debug_uart_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 debug_uart_numberOfAddr;
    extern uint8 debug_uart_subAddrSize;
#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (debug_uart_SCB_MODE_I2C_CONST_CFG || \
        debug_uart_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 debug_uart_IntrTxMask;
#endif /* (! (debug_uart_SCB_MODE_I2C_CONST_CFG || \
              debug_uart_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define debug_uart_SCB_MODE_I2C_RUNTM_CFG     (debug_uart_SCB_MODE_I2C      == debug_uart_scbMode)
    #define debug_uart_SCB_MODE_SPI_RUNTM_CFG     (debug_uart_SCB_MODE_SPI      == debug_uart_scbMode)
    #define debug_uart_SCB_MODE_UART_RUNTM_CFG    (debug_uart_SCB_MODE_UART     == debug_uart_scbMode)
    #define debug_uart_SCB_MODE_EZI2C_RUNTM_CFG   (debug_uart_SCB_MODE_EZI2C    == debug_uart_scbMode)
    #define debug_uart_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (debug_uart_SCB_MODE_UNCONFIG == debug_uart_scbMode)

    /* Defines wakeup enable */
    #define debug_uart_SCB_WAKE_ENABLE_CHECK       (0u != debug_uart_scbEnableWake)
#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!debug_uart_CY_SCBIP_V1)
    #define debug_uart_SCB_PINS_NUMBER    (7u)
#else
    #define debug_uart_SCB_PINS_NUMBER    (2u)
#endif /* (!debug_uart_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_debug_uart_H) */


/* [] END OF FILE */
