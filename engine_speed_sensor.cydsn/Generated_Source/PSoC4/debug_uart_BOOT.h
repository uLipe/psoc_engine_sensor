/***************************************************************************//**
* \file debug_uart_BOOT.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_debug_uart_H)
#define CY_SCB_BOOT_debug_uart_H

#include "debug_uart_PVT.h"

#if (debug_uart_SCB_MODE_I2C_INC)
    #include "debug_uart_I2C.h"
#endif /* (debug_uart_SCB_MODE_I2C_INC) */

#if (debug_uart_SCB_MODE_EZI2C_INC)
    #include "debug_uart_EZI2C.h"
#endif /* (debug_uart_SCB_MODE_EZI2C_INC) */

#if (debug_uart_SCB_MODE_SPI_INC || debug_uart_SCB_MODE_UART_INC)
    #include "debug_uart_SPI_UART.h"
#endif /* (debug_uart_SCB_MODE_SPI_INC || debug_uart_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define debug_uart_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_debug_uart) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (debug_uart_SCB_MODE_I2C_INC)
    #define debug_uart_I2C_BTLDR_COMM_ENABLED     (debug_uart_BTLDR_COMM_ENABLED && \
                                                            (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             debug_uart_I2C_SLAVE_CONST))
#else
     #define debug_uart_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (debug_uart_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (debug_uart_SCB_MODE_EZI2C_INC)
    #define debug_uart_EZI2C_BTLDR_COMM_ENABLED   (debug_uart_BTLDR_COMM_ENABLED && \
                                                         debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define debug_uart_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (debug_uart_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (debug_uart_SCB_MODE_SPI_INC)
    #define debug_uart_SPI_BTLDR_COMM_ENABLED     (debug_uart_BTLDR_COMM_ENABLED && \
                                                            (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             debug_uart_SPI_SLAVE_CONST))
#else
        #define debug_uart_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (debug_uart_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (debug_uart_SCB_MODE_UART_INC)
       #define debug_uart_UART_BTLDR_COMM_ENABLED    (debug_uart_BTLDR_COMM_ENABLED && \
                                                            (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (debug_uart_UART_RX_DIRECTION && \
                                                              debug_uart_UART_TX_DIRECTION)))
#else
     #define debug_uart_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (debug_uart_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define debug_uart_BTLDR_COMM_MODE_ENABLED    (debug_uart_I2C_BTLDR_COMM_ENABLED   || \
                                                     debug_uart_SPI_BTLDR_COMM_ENABLED   || \
                                                     debug_uart_EZI2C_BTLDR_COMM_ENABLED || \
                                                     debug_uart_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void debug_uart_I2CCyBtldrCommStart(void);
    void debug_uart_I2CCyBtldrCommStop (void);
    void debug_uart_I2CCyBtldrCommReset(void);
    cystatus debug_uart_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus debug_uart_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (debug_uart_SCB_MODE_I2C_CONST_CFG)
        #define debug_uart_CyBtldrCommStart   debug_uart_I2CCyBtldrCommStart
        #define debug_uart_CyBtldrCommStop    debug_uart_I2CCyBtldrCommStop
        #define debug_uart_CyBtldrCommReset   debug_uart_I2CCyBtldrCommReset
        #define debug_uart_CyBtldrCommRead    debug_uart_I2CCyBtldrCommRead
        #define debug_uart_CyBtldrCommWrite   debug_uart_I2CCyBtldrCommWrite
    #endif /* (debug_uart_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void debug_uart_EzI2CCyBtldrCommStart(void);
    void debug_uart_EzI2CCyBtldrCommStop (void);
    void debug_uart_EzI2CCyBtldrCommReset(void);
    cystatus debug_uart_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus debug_uart_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (debug_uart_SCB_MODE_EZI2C_CONST_CFG)
        #define debug_uart_CyBtldrCommStart   debug_uart_EzI2CCyBtldrCommStart
        #define debug_uart_CyBtldrCommStop    debug_uart_EzI2CCyBtldrCommStop
        #define debug_uart_CyBtldrCommReset   debug_uart_EzI2CCyBtldrCommReset
        #define debug_uart_CyBtldrCommRead    debug_uart_EzI2CCyBtldrCommRead
        #define debug_uart_CyBtldrCommWrite   debug_uart_EzI2CCyBtldrCommWrite
    #endif /* (debug_uart_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void debug_uart_SpiCyBtldrCommStart(void);
    void debug_uart_SpiCyBtldrCommStop (void);
    void debug_uart_SpiCyBtldrCommReset(void);
    cystatus debug_uart_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus debug_uart_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (debug_uart_SCB_MODE_SPI_CONST_CFG)
        #define debug_uart_CyBtldrCommStart   debug_uart_SpiCyBtldrCommStart
        #define debug_uart_CyBtldrCommStop    debug_uart_SpiCyBtldrCommStop
        #define debug_uart_CyBtldrCommReset   debug_uart_SpiCyBtldrCommReset
        #define debug_uart_CyBtldrCommRead    debug_uart_SpiCyBtldrCommRead
        #define debug_uart_CyBtldrCommWrite   debug_uart_SpiCyBtldrCommWrite
    #endif /* (debug_uart_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void debug_uart_UartCyBtldrCommStart(void);
    void debug_uart_UartCyBtldrCommStop (void);
    void debug_uart_UartCyBtldrCommReset(void);
    cystatus debug_uart_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus debug_uart_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (debug_uart_SCB_MODE_UART_CONST_CFG)
        #define debug_uart_CyBtldrCommStart   debug_uart_UartCyBtldrCommStart
        #define debug_uart_CyBtldrCommStop    debug_uart_UartCyBtldrCommStop
        #define debug_uart_CyBtldrCommReset   debug_uart_UartCyBtldrCommReset
        #define debug_uart_CyBtldrCommRead    debug_uart_UartCyBtldrCommRead
        #define debug_uart_CyBtldrCommWrite   debug_uart_UartCyBtldrCommWrite
    #endif /* (debug_uart_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_BTLDR_COMM_ENABLED)
    #if (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void debug_uart_CyBtldrCommStart(void);
        void debug_uart_CyBtldrCommStop (void);
        void debug_uart_CyBtldrCommReset(void);
        cystatus debug_uart_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus debug_uart_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_debug_uart)
        #define CyBtldrCommStart    debug_uart_CyBtldrCommStart
        #define CyBtldrCommStop     debug_uart_CyBtldrCommStop
        #define CyBtldrCommReset    debug_uart_CyBtldrCommReset
        #define CyBtldrCommWrite    debug_uart_CyBtldrCommWrite
        #define CyBtldrCommRead     debug_uart_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_debug_uart) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (debug_uart_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define debug_uart_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define debug_uart_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define debug_uart_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define debug_uart_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef debug_uart_SPI_BYTE_TO_BYTE
    #define debug_uart_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef debug_uart_UART_BYTE_TO_BYTE
    #define debug_uart_UART_BYTE_TO_BYTE  (175u)
#endif /* debug_uart_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_debug_uart_H) */


/* [] END OF FILE */
