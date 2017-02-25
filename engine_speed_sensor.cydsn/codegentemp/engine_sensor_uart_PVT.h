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

#if !defined(CY_SCB_PVT_engine_sensor_uart_H)
#define CY_SCB_PVT_engine_sensor_uart_H

#include "engine_sensor_uart.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define engine_sensor_uart_SetI2CExtClkInterruptMode(interruptMask) engine_sensor_uart_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define engine_sensor_uart_ClearI2CExtClkInterruptSource(interruptMask) engine_sensor_uart_CLEAR_INTR_I2C_EC(interruptMask)
#define engine_sensor_uart_GetI2CExtClkInterruptSource()                (engine_sensor_uart_INTR_I2C_EC_REG)
#define engine_sensor_uart_GetI2CExtClkInterruptMode()                  (engine_sensor_uart_INTR_I2C_EC_MASK_REG)
#define engine_sensor_uart_GetI2CExtClkInterruptSourceMasked()          (engine_sensor_uart_INTR_I2C_EC_MASKED_REG)

#if (!engine_sensor_uart_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define engine_sensor_uart_SetSpiExtClkInterruptMode(interruptMask) \
                                                                engine_sensor_uart_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define engine_sensor_uart_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                engine_sensor_uart_CLEAR_INTR_SPI_EC(interruptMask)
    #define engine_sensor_uart_GetExtSpiClkInterruptSource()                 (engine_sensor_uart_INTR_SPI_EC_REG)
    #define engine_sensor_uart_GetExtSpiClkInterruptMode()                   (engine_sensor_uart_INTR_SPI_EC_MASK_REG)
    #define engine_sensor_uart_GetExtSpiClkInterruptSourceMasked()           (engine_sensor_uart_INTR_SPI_EC_MASKED_REG)
#endif /* (!engine_sensor_uart_CY_SCBIP_V1) */

#if(engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void engine_sensor_uart_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (engine_sensor_uart_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_engine_sensor_uart_CUSTOM_INTR_HANDLER)
    extern cyisraddress engine_sensor_uart_customIntrHandler;
#endif /* !defined (CY_REMOVE_engine_sensor_uart_CUSTOM_INTR_HANDLER) */
#endif /* (engine_sensor_uart_SCB_IRQ_INTERNAL) */

extern engine_sensor_uart_BACKUP_STRUCT engine_sensor_uart_backup;

#if(engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 engine_sensor_uart_scbMode;
    extern uint8 engine_sensor_uart_scbEnableWake;
    extern uint8 engine_sensor_uart_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 engine_sensor_uart_mode;
    extern uint8 engine_sensor_uart_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * engine_sensor_uart_rxBuffer;
    extern uint8   engine_sensor_uart_rxDataBits;
    extern uint32  engine_sensor_uart_rxBufferSize;

    extern volatile uint8 * engine_sensor_uart_txBuffer;
    extern uint8   engine_sensor_uart_txDataBits;
    extern uint32  engine_sensor_uart_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 engine_sensor_uart_numberOfAddr;
    extern uint8 engine_sensor_uart_subAddrSize;
#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (engine_sensor_uart_SCB_MODE_I2C_CONST_CFG || \
        engine_sensor_uart_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 engine_sensor_uart_IntrTxMask;
#endif /* (! (engine_sensor_uart_SCB_MODE_I2C_CONST_CFG || \
              engine_sensor_uart_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define engine_sensor_uart_SCB_MODE_I2C_RUNTM_CFG     (engine_sensor_uart_SCB_MODE_I2C      == engine_sensor_uart_scbMode)
    #define engine_sensor_uart_SCB_MODE_SPI_RUNTM_CFG     (engine_sensor_uart_SCB_MODE_SPI      == engine_sensor_uart_scbMode)
    #define engine_sensor_uart_SCB_MODE_UART_RUNTM_CFG    (engine_sensor_uart_SCB_MODE_UART     == engine_sensor_uart_scbMode)
    #define engine_sensor_uart_SCB_MODE_EZI2C_RUNTM_CFG   (engine_sensor_uart_SCB_MODE_EZI2C    == engine_sensor_uart_scbMode)
    #define engine_sensor_uart_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (engine_sensor_uart_SCB_MODE_UNCONFIG == engine_sensor_uart_scbMode)

    /* Defines wakeup enable */
    #define engine_sensor_uart_SCB_WAKE_ENABLE_CHECK       (0u != engine_sensor_uart_scbEnableWake)
#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!engine_sensor_uart_CY_SCBIP_V1)
    #define engine_sensor_uart_SCB_PINS_NUMBER    (7u)
#else
    #define engine_sensor_uart_SCB_PINS_NUMBER    (2u)
#endif /* (!engine_sensor_uart_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_engine_sensor_uart_H) */


/* [] END OF FILE */
