/***************************************************************************//**
* \file engine_sensor_uart_SPI_UART_PVT.h
* \version 3.20
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
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

#if !defined(CY_SCB_SPI_UART_PVT_engine_sensor_uart_H)
#define CY_SCB_SPI_UART_PVT_engine_sensor_uart_H

#include "engine_sensor_uart_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  engine_sensor_uart_rxBufferHead;
    extern volatile uint32  engine_sensor_uart_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   engine_sensor_uart_rxBufferOverflow;
    /** @} globals */
#endif /* (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST) */

#if (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  engine_sensor_uart_txBufferHead;
    extern volatile uint32  engine_sensor_uart_txBufferTail;
#endif /* (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST) */

#if (engine_sensor_uart_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 engine_sensor_uart_rxBufferInternal[engine_sensor_uart_INTERNAL_RX_BUFFER_SIZE];
#endif /* (engine_sensor_uart_INTERNAL_RX_SW_BUFFER) */

#if (engine_sensor_uart_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 engine_sensor_uart_txBufferInternal[engine_sensor_uart_TX_BUFFER_SIZE];
#endif /* (engine_sensor_uart_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void engine_sensor_uart_SpiPostEnable(void);
void engine_sensor_uart_SpiStop(void);

#if (engine_sensor_uart_SCB_MODE_SPI_CONST_CFG)
    void engine_sensor_uart_SpiInit(void);
#endif /* (engine_sensor_uart_SCB_MODE_SPI_CONST_CFG) */

#if (engine_sensor_uart_SPI_WAKE_ENABLE_CONST)
    void engine_sensor_uart_SpiSaveConfig(void);
    void engine_sensor_uart_SpiRestoreConfig(void);
#endif /* (engine_sensor_uart_SPI_WAKE_ENABLE_CONST) */

void engine_sensor_uart_UartPostEnable(void);
void engine_sensor_uart_UartStop(void);

#if (engine_sensor_uart_SCB_MODE_UART_CONST_CFG)
    void engine_sensor_uart_UartInit(void);
#endif /* (engine_sensor_uart_SCB_MODE_UART_CONST_CFG) */

#if (engine_sensor_uart_UART_WAKE_ENABLE_CONST)
    void engine_sensor_uart_UartSaveConfig(void);
    void engine_sensor_uart_UartRestoreConfig(void);
#endif /* (engine_sensor_uart_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in engine_sensor_uart_SetPins() */
#define engine_sensor_uart_UART_RX_PIN_ENABLE    (engine_sensor_uart_UART_RX)
#define engine_sensor_uart_UART_TX_PIN_ENABLE    (engine_sensor_uart_UART_TX)

/* UART RTS and CTS position to be used in  engine_sensor_uart_SetPins() */
#define engine_sensor_uart_UART_RTS_PIN_ENABLE    (0x10u)
#define engine_sensor_uart_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define engine_sensor_uart_SpiUartEnableIntRx(intSourceMask)  engine_sensor_uart_SetRxInterruptMode(intSourceMask)
#define engine_sensor_uart_SpiUartEnableIntTx(intSourceMask)  engine_sensor_uart_SetTxInterruptMode(intSourceMask)
uint32  engine_sensor_uart_SpiUartDisableIntRx(void);
uint32  engine_sensor_uart_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_engine_sensor_uart_H) */


/* [] END OF FILE */
