/***************************************************************************//**
* \file engine_sensor_uart_BOOT.h
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

#if !defined(CY_SCB_BOOT_engine_sensor_uart_H)
#define CY_SCB_BOOT_engine_sensor_uart_H

#include "engine_sensor_uart_PVT.h"

#if (engine_sensor_uart_SCB_MODE_I2C_INC)
    #include "engine_sensor_uart_I2C.h"
#endif /* (engine_sensor_uart_SCB_MODE_I2C_INC) */

#if (engine_sensor_uart_SCB_MODE_EZI2C_INC)
    #include "engine_sensor_uart_EZI2C.h"
#endif /* (engine_sensor_uart_SCB_MODE_EZI2C_INC) */

#if (engine_sensor_uart_SCB_MODE_SPI_INC || engine_sensor_uart_SCB_MODE_UART_INC)
    #include "engine_sensor_uart_SPI_UART.h"
#endif /* (engine_sensor_uart_SCB_MODE_SPI_INC || engine_sensor_uart_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define engine_sensor_uart_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_engine_sensor_uart) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (engine_sensor_uart_SCB_MODE_I2C_INC)
    #define engine_sensor_uart_I2C_BTLDR_COMM_ENABLED     (engine_sensor_uart_BTLDR_COMM_ENABLED && \
                                                            (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             engine_sensor_uart_I2C_SLAVE_CONST))
#else
     #define engine_sensor_uart_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (engine_sensor_uart_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (engine_sensor_uart_SCB_MODE_EZI2C_INC)
    #define engine_sensor_uart_EZI2C_BTLDR_COMM_ENABLED   (engine_sensor_uart_BTLDR_COMM_ENABLED && \
                                                         engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define engine_sensor_uart_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (engine_sensor_uart_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (engine_sensor_uart_SCB_MODE_SPI_INC)
    #define engine_sensor_uart_SPI_BTLDR_COMM_ENABLED     (engine_sensor_uart_BTLDR_COMM_ENABLED && \
                                                            (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             engine_sensor_uart_SPI_SLAVE_CONST))
#else
        #define engine_sensor_uart_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (engine_sensor_uart_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (engine_sensor_uart_SCB_MODE_UART_INC)
       #define engine_sensor_uart_UART_BTLDR_COMM_ENABLED    (engine_sensor_uart_BTLDR_COMM_ENABLED && \
                                                            (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (engine_sensor_uart_UART_RX_DIRECTION && \
                                                              engine_sensor_uart_UART_TX_DIRECTION)))
#else
     #define engine_sensor_uart_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (engine_sensor_uart_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define engine_sensor_uart_BTLDR_COMM_MODE_ENABLED    (engine_sensor_uart_I2C_BTLDR_COMM_ENABLED   || \
                                                     engine_sensor_uart_SPI_BTLDR_COMM_ENABLED   || \
                                                     engine_sensor_uart_EZI2C_BTLDR_COMM_ENABLED || \
                                                     engine_sensor_uart_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void engine_sensor_uart_I2CCyBtldrCommStart(void);
    void engine_sensor_uart_I2CCyBtldrCommStop (void);
    void engine_sensor_uart_I2CCyBtldrCommReset(void);
    cystatus engine_sensor_uart_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus engine_sensor_uart_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (engine_sensor_uart_SCB_MODE_I2C_CONST_CFG)
        #define engine_sensor_uart_CyBtldrCommStart   engine_sensor_uart_I2CCyBtldrCommStart
        #define engine_sensor_uart_CyBtldrCommStop    engine_sensor_uart_I2CCyBtldrCommStop
        #define engine_sensor_uart_CyBtldrCommReset   engine_sensor_uart_I2CCyBtldrCommReset
        #define engine_sensor_uart_CyBtldrCommRead    engine_sensor_uart_I2CCyBtldrCommRead
        #define engine_sensor_uart_CyBtldrCommWrite   engine_sensor_uart_I2CCyBtldrCommWrite
    #endif /* (engine_sensor_uart_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void engine_sensor_uart_EzI2CCyBtldrCommStart(void);
    void engine_sensor_uart_EzI2CCyBtldrCommStop (void);
    void engine_sensor_uart_EzI2CCyBtldrCommReset(void);
    cystatus engine_sensor_uart_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus engine_sensor_uart_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (engine_sensor_uart_SCB_MODE_EZI2C_CONST_CFG)
        #define engine_sensor_uart_CyBtldrCommStart   engine_sensor_uart_EzI2CCyBtldrCommStart
        #define engine_sensor_uart_CyBtldrCommStop    engine_sensor_uart_EzI2CCyBtldrCommStop
        #define engine_sensor_uart_CyBtldrCommReset   engine_sensor_uart_EzI2CCyBtldrCommReset
        #define engine_sensor_uart_CyBtldrCommRead    engine_sensor_uart_EzI2CCyBtldrCommRead
        #define engine_sensor_uart_CyBtldrCommWrite   engine_sensor_uart_EzI2CCyBtldrCommWrite
    #endif /* (engine_sensor_uart_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void engine_sensor_uart_SpiCyBtldrCommStart(void);
    void engine_sensor_uart_SpiCyBtldrCommStop (void);
    void engine_sensor_uart_SpiCyBtldrCommReset(void);
    cystatus engine_sensor_uart_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus engine_sensor_uart_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (engine_sensor_uart_SCB_MODE_SPI_CONST_CFG)
        #define engine_sensor_uart_CyBtldrCommStart   engine_sensor_uart_SpiCyBtldrCommStart
        #define engine_sensor_uart_CyBtldrCommStop    engine_sensor_uart_SpiCyBtldrCommStop
        #define engine_sensor_uart_CyBtldrCommReset   engine_sensor_uart_SpiCyBtldrCommReset
        #define engine_sensor_uart_CyBtldrCommRead    engine_sensor_uart_SpiCyBtldrCommRead
        #define engine_sensor_uart_CyBtldrCommWrite   engine_sensor_uart_SpiCyBtldrCommWrite
    #endif /* (engine_sensor_uart_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void engine_sensor_uart_UartCyBtldrCommStart(void);
    void engine_sensor_uart_UartCyBtldrCommStop (void);
    void engine_sensor_uart_UartCyBtldrCommReset(void);
    cystatus engine_sensor_uart_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus engine_sensor_uart_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (engine_sensor_uart_SCB_MODE_UART_CONST_CFG)
        #define engine_sensor_uart_CyBtldrCommStart   engine_sensor_uart_UartCyBtldrCommStart
        #define engine_sensor_uart_CyBtldrCommStop    engine_sensor_uart_UartCyBtldrCommStop
        #define engine_sensor_uart_CyBtldrCommReset   engine_sensor_uart_UartCyBtldrCommReset
        #define engine_sensor_uart_CyBtldrCommRead    engine_sensor_uart_UartCyBtldrCommRead
        #define engine_sensor_uart_CyBtldrCommWrite   engine_sensor_uart_UartCyBtldrCommWrite
    #endif /* (engine_sensor_uart_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_BTLDR_COMM_ENABLED)
    #if (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void engine_sensor_uart_CyBtldrCommStart(void);
        void engine_sensor_uart_CyBtldrCommStop (void);
        void engine_sensor_uart_CyBtldrCommReset(void);
        cystatus engine_sensor_uart_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus engine_sensor_uart_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_engine_sensor_uart)
        #define CyBtldrCommStart    engine_sensor_uart_CyBtldrCommStart
        #define CyBtldrCommStop     engine_sensor_uart_CyBtldrCommStop
        #define CyBtldrCommReset    engine_sensor_uart_CyBtldrCommReset
        #define CyBtldrCommWrite    engine_sensor_uart_CyBtldrCommWrite
        #define CyBtldrCommRead     engine_sensor_uart_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_engine_sensor_uart) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (engine_sensor_uart_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define engine_sensor_uart_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define engine_sensor_uart_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define engine_sensor_uart_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define engine_sensor_uart_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef engine_sensor_uart_SPI_BYTE_TO_BYTE
    #define engine_sensor_uart_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef engine_sensor_uart_UART_BYTE_TO_BYTE
    #define engine_sensor_uart_UART_BYTE_TO_BYTE  (175u)
#endif /* engine_sensor_uart_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_engine_sensor_uart_H) */


/* [] END OF FILE */
