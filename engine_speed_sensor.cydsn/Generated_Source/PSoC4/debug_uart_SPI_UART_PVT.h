/***************************************************************************//**
* \file debug_uart_SPI_UART_PVT.h
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

#if !defined(CY_SCB_SPI_UART_PVT_debug_uart_H)
#define CY_SCB_SPI_UART_PVT_debug_uart_H

#include "debug_uart_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (debug_uart_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  debug_uart_rxBufferHead;
    extern volatile uint32  debug_uart_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   debug_uart_rxBufferOverflow;
    /** @} globals */
#endif /* (debug_uart_INTERNAL_RX_SW_BUFFER_CONST) */

#if (debug_uart_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  debug_uart_txBufferHead;
    extern volatile uint32  debug_uart_txBufferTail;
#endif /* (debug_uart_INTERNAL_TX_SW_BUFFER_CONST) */

#if (debug_uart_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 debug_uart_rxBufferInternal[debug_uart_INTERNAL_RX_BUFFER_SIZE];
#endif /* (debug_uart_INTERNAL_RX_SW_BUFFER) */

#if (debug_uart_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 debug_uart_txBufferInternal[debug_uart_TX_BUFFER_SIZE];
#endif /* (debug_uart_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void debug_uart_SpiPostEnable(void);
void debug_uart_SpiStop(void);

#if (debug_uart_SCB_MODE_SPI_CONST_CFG)
    void debug_uart_SpiInit(void);
#endif /* (debug_uart_SCB_MODE_SPI_CONST_CFG) */

#if (debug_uart_SPI_WAKE_ENABLE_CONST)
    void debug_uart_SpiSaveConfig(void);
    void debug_uart_SpiRestoreConfig(void);
#endif /* (debug_uart_SPI_WAKE_ENABLE_CONST) */

void debug_uart_UartPostEnable(void);
void debug_uart_UartStop(void);

#if (debug_uart_SCB_MODE_UART_CONST_CFG)
    void debug_uart_UartInit(void);
#endif /* (debug_uart_SCB_MODE_UART_CONST_CFG) */

#if (debug_uart_UART_WAKE_ENABLE_CONST)
    void debug_uart_UartSaveConfig(void);
    void debug_uart_UartRestoreConfig(void);
#endif /* (debug_uart_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in debug_uart_SetPins() */
#define debug_uart_UART_RX_PIN_ENABLE    (debug_uart_UART_RX)
#define debug_uart_UART_TX_PIN_ENABLE    (debug_uart_UART_TX)

/* UART RTS and CTS position to be used in  debug_uart_SetPins() */
#define debug_uart_UART_RTS_PIN_ENABLE    (0x10u)
#define debug_uart_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define debug_uart_SpiUartEnableIntRx(intSourceMask)  debug_uart_SetRxInterruptMode(intSourceMask)
#define debug_uart_SpiUartEnableIntTx(intSourceMask)  debug_uart_SetTxInterruptMode(intSourceMask)
uint32  debug_uart_SpiUartDisableIntRx(void);
uint32  debug_uart_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_debug_uart_H) */


/* [] END OF FILE */
