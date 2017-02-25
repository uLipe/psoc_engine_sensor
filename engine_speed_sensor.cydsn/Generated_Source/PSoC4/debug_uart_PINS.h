/***************************************************************************//**
* \file debug_uart_PINS.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_debug_uart_H)
#define CY_SCB_PINS_debug_uart_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define debug_uart_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define debug_uart_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define debug_uart_REMOVE_TX_SDA_MISO_PIN      (1u)
#define debug_uart_REMOVE_CTS_SCLK_PIN      (1u)
#define debug_uart_REMOVE_RTS_SS0_PIN      (1u)
#define debug_uart_REMOVE_SS1_PIN                 (1u)
#define debug_uart_REMOVE_SS2_PIN                 (1u)
#define debug_uart_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define debug_uart_REMOVE_I2C_PINS                (1u)
#define debug_uart_REMOVE_SPI_MASTER_PINS         (1u)
#define debug_uart_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define debug_uart_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define debug_uart_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define debug_uart_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define debug_uart_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define debug_uart_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define debug_uart_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define debug_uart_REMOVE_SPI_SLAVE_PINS          (1u)
#define debug_uart_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define debug_uart_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define debug_uart_REMOVE_UART_TX_PIN             (0u)
#define debug_uart_REMOVE_UART_RX_TX_PIN          (1u)
#define debug_uart_REMOVE_UART_RX_PIN             (0u)
#define debug_uart_REMOVE_UART_RX_WAKE_PIN        (1u)
#define debug_uart_REMOVE_UART_RTS_PIN            (1u)
#define debug_uart_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define debug_uart_RX_WAKE_SCL_MOSI_PIN (0u == debug_uart_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define debug_uart_RX_SCL_MOSI_PIN     (0u == debug_uart_REMOVE_RX_SCL_MOSI_PIN)
#define debug_uart_TX_SDA_MISO_PIN     (0u == debug_uart_REMOVE_TX_SDA_MISO_PIN)
#define debug_uart_CTS_SCLK_PIN     (0u == debug_uart_REMOVE_CTS_SCLK_PIN)
#define debug_uart_RTS_SS0_PIN     (0u == debug_uart_REMOVE_RTS_SS0_PIN)
#define debug_uart_SS1_PIN                (0u == debug_uart_REMOVE_SS1_PIN)
#define debug_uart_SS2_PIN                (0u == debug_uart_REMOVE_SS2_PIN)
#define debug_uart_SS3_PIN                (0u == debug_uart_REMOVE_SS3_PIN)

/* Mode defined pins */
#define debug_uart_I2C_PINS               (0u == debug_uart_REMOVE_I2C_PINS)
#define debug_uart_SPI_MASTER_PINS        (0u == debug_uart_REMOVE_SPI_MASTER_PINS)
#define debug_uart_SPI_MASTER_SCLK_PIN    (0u == debug_uart_REMOVE_SPI_MASTER_SCLK_PIN)
#define debug_uart_SPI_MASTER_MOSI_PIN    (0u == debug_uart_REMOVE_SPI_MASTER_MOSI_PIN)
#define debug_uart_SPI_MASTER_MISO_PIN    (0u == debug_uart_REMOVE_SPI_MASTER_MISO_PIN)
#define debug_uart_SPI_MASTER_SS0_PIN     (0u == debug_uart_REMOVE_SPI_MASTER_SS0_PIN)
#define debug_uart_SPI_MASTER_SS1_PIN     (0u == debug_uart_REMOVE_SPI_MASTER_SS1_PIN)
#define debug_uart_SPI_MASTER_SS2_PIN     (0u == debug_uart_REMOVE_SPI_MASTER_SS2_PIN)
#define debug_uart_SPI_MASTER_SS3_PIN     (0u == debug_uart_REMOVE_SPI_MASTER_SS3_PIN)
#define debug_uart_SPI_SLAVE_PINS         (0u == debug_uart_REMOVE_SPI_SLAVE_PINS)
#define debug_uart_SPI_SLAVE_MOSI_PIN     (0u == debug_uart_REMOVE_SPI_SLAVE_MOSI_PIN)
#define debug_uart_SPI_SLAVE_MISO_PIN     (0u == debug_uart_REMOVE_SPI_SLAVE_MISO_PIN)
#define debug_uart_UART_TX_PIN            (0u == debug_uart_REMOVE_UART_TX_PIN)
#define debug_uart_UART_RX_TX_PIN         (0u == debug_uart_REMOVE_UART_RX_TX_PIN)
#define debug_uart_UART_RX_PIN            (0u == debug_uart_REMOVE_UART_RX_PIN)
#define debug_uart_UART_RX_WAKE_PIN       (0u == debug_uart_REMOVE_UART_RX_WAKE_PIN)
#define debug_uart_UART_RTS_PIN           (0u == debug_uart_REMOVE_UART_RTS_PIN)
#define debug_uart_UART_CTS_PIN           (0u == debug_uart_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (debug_uart_RX_WAKE_SCL_MOSI_PIN)
    #include "debug_uart_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (debug_uart_RX_SCL_MOSI) */

#if (debug_uart_RX_SCL_MOSI_PIN)
    #include "debug_uart_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (debug_uart_RX_SCL_MOSI) */

#if (debug_uart_TX_SDA_MISO_PIN)
    #include "debug_uart_uart_tx_i2c_sda_spi_miso.h"
#endif /* (debug_uart_TX_SDA_MISO) */

#if (debug_uart_CTS_SCLK_PIN)
    #include "debug_uart_uart_cts_spi_sclk.h"
#endif /* (debug_uart_CTS_SCLK) */

#if (debug_uart_RTS_SS0_PIN)
    #include "debug_uart_uart_rts_spi_ss0.h"
#endif /* (debug_uart_RTS_SS0_PIN) */

#if (debug_uart_SS1_PIN)
    #include "debug_uart_spi_ss1.h"
#endif /* (debug_uart_SS1_PIN) */

#if (debug_uart_SS2_PIN)
    #include "debug_uart_spi_ss2.h"
#endif /* (debug_uart_SS2_PIN) */

#if (debug_uart_SS3_PIN)
    #include "debug_uart_spi_ss3.h"
#endif /* (debug_uart_SS3_PIN) */

#if (debug_uart_I2C_PINS)
    #include "debug_uart_scl.h"
    #include "debug_uart_sda.h"
#endif /* (debug_uart_I2C_PINS) */

#if (debug_uart_SPI_MASTER_PINS)
#if (debug_uart_SPI_MASTER_SCLK_PIN)
    #include "debug_uart_sclk_m.h"
#endif /* (debug_uart_SPI_MASTER_SCLK_PIN) */

#if (debug_uart_SPI_MASTER_MOSI_PIN)
    #include "debug_uart_mosi_m.h"
#endif /* (debug_uart_SPI_MASTER_MOSI_PIN) */

#if (debug_uart_SPI_MASTER_MISO_PIN)
    #include "debug_uart_miso_m.h"
#endif /*(debug_uart_SPI_MASTER_MISO_PIN) */
#endif /* (debug_uart_SPI_MASTER_PINS) */

#if (debug_uart_SPI_SLAVE_PINS)
    #include "debug_uart_sclk_s.h"
    #include "debug_uart_ss_s.h"

#if (debug_uart_SPI_SLAVE_MOSI_PIN)
    #include "debug_uart_mosi_s.h"
#endif /* (debug_uart_SPI_SLAVE_MOSI_PIN) */

#if (debug_uart_SPI_SLAVE_MISO_PIN)
    #include "debug_uart_miso_s.h"
#endif /*(debug_uart_SPI_SLAVE_MISO_PIN) */
#endif /* (debug_uart_SPI_SLAVE_PINS) */

#if (debug_uart_SPI_MASTER_SS0_PIN)
    #include "debug_uart_ss0_m.h"
#endif /* (debug_uart_SPI_MASTER_SS0_PIN) */

#if (debug_uart_SPI_MASTER_SS1_PIN)
    #include "debug_uart_ss1_m.h"
#endif /* (debug_uart_SPI_MASTER_SS1_PIN) */

#if (debug_uart_SPI_MASTER_SS2_PIN)
    #include "debug_uart_ss2_m.h"
#endif /* (debug_uart_SPI_MASTER_SS2_PIN) */

#if (debug_uart_SPI_MASTER_SS3_PIN)
    #include "debug_uart_ss3_m.h"
#endif /* (debug_uart_SPI_MASTER_SS3_PIN) */

#if (debug_uart_UART_TX_PIN)
    #include "debug_uart_tx.h"
#endif /* (debug_uart_UART_TX_PIN) */

#if (debug_uart_UART_RX_TX_PIN)
    #include "debug_uart_rx_tx.h"
#endif /* (debug_uart_UART_RX_TX_PIN) */

#if (debug_uart_UART_RX_PIN)
    #include "debug_uart_rx.h"
#endif /* (debug_uart_UART_RX_PIN) */

#if (debug_uart_UART_RX_WAKE_PIN)
    #include "debug_uart_rx_wake.h"
#endif /* (debug_uart_UART_RX_WAKE_PIN) */

#if (debug_uart_UART_RTS_PIN)
    #include "debug_uart_rts.h"
#endif /* (debug_uart_UART_RTS_PIN) */

#if (debug_uart_UART_CTS_PIN)
    #include "debug_uart_cts.h"
#endif /* (debug_uart_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (debug_uart_RX_SCL_MOSI_PIN)
    #define debug_uart_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) debug_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define debug_uart_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) debug_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define debug_uart_RX_SCL_MOSI_HSIOM_MASK      (debug_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define debug_uart_RX_SCL_MOSI_HSIOM_POS       (debug_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define debug_uart_RX_SCL_MOSI_HSIOM_SEL_GPIO  (debug_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define debug_uart_RX_SCL_MOSI_HSIOM_SEL_I2C   (debug_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define debug_uart_RX_SCL_MOSI_HSIOM_SEL_SPI   (debug_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define debug_uart_RX_SCL_MOSI_HSIOM_SEL_UART  (debug_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (debug_uart_RX_WAKE_SCL_MOSI_PIN)
    #define debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define debug_uart_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define debug_uart_RX_WAKE_SCL_MOSI_HSIOM_MASK      (debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define debug_uart_RX_WAKE_SCL_MOSI_HSIOM_POS       (debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define debug_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define debug_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define debug_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define debug_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define debug_uart_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define debug_uart_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) debug_uart_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define debug_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (debug_uart_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define debug_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) debug_uart_INTCFG_TYPE_MASK << \
                                                                           debug_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins debug_uart_RX_SCL_MOSI_PIN or debug_uart_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (debug_uart_RX_SCL_MOSI_PIN) */

#if (debug_uart_TX_SDA_MISO_PIN)
    #define debug_uart_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) debug_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define debug_uart_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) debug_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define debug_uart_TX_SDA_MISO_HSIOM_MASK      (debug_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define debug_uart_TX_SDA_MISO_HSIOM_POS       (debug_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define debug_uart_TX_SDA_MISO_HSIOM_SEL_GPIO  (debug_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define debug_uart_TX_SDA_MISO_HSIOM_SEL_I2C   (debug_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define debug_uart_TX_SDA_MISO_HSIOM_SEL_SPI   (debug_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define debug_uart_TX_SDA_MISO_HSIOM_SEL_UART  (debug_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (debug_uart_TX_SDA_MISO_PIN) */

#if (debug_uart_CTS_SCLK_PIN)
    #define debug_uart_CTS_SCLK_HSIOM_REG   (*(reg32 *) debug_uart_uart_cts_spi_sclk__0__HSIOM)
    #define debug_uart_CTS_SCLK_HSIOM_PTR   ( (reg32 *) debug_uart_uart_cts_spi_sclk__0__HSIOM)
    
    #define debug_uart_CTS_SCLK_HSIOM_MASK      (debug_uart_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define debug_uart_CTS_SCLK_HSIOM_POS       (debug_uart_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define debug_uart_CTS_SCLK_HSIOM_SEL_GPIO  (debug_uart_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define debug_uart_CTS_SCLK_HSIOM_SEL_I2C   (debug_uart_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define debug_uart_CTS_SCLK_HSIOM_SEL_SPI   (debug_uart_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define debug_uart_CTS_SCLK_HSIOM_SEL_UART  (debug_uart_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (debug_uart_CTS_SCLK_PIN) */

#if (debug_uart_RTS_SS0_PIN)
    #define debug_uart_RTS_SS0_HSIOM_REG   (*(reg32 *) debug_uart_uart_rts_spi_ss0__0__HSIOM)
    #define debug_uart_RTS_SS0_HSIOM_PTR   ( (reg32 *) debug_uart_uart_rts_spi_ss0__0__HSIOM)
    
    #define debug_uart_RTS_SS0_HSIOM_MASK      (debug_uart_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define debug_uart_RTS_SS0_HSIOM_POS       (debug_uart_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define debug_uart_RTS_SS0_HSIOM_SEL_GPIO  (debug_uart_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define debug_uart_RTS_SS0_HSIOM_SEL_I2C   (debug_uart_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define debug_uart_RTS_SS0_HSIOM_SEL_SPI   (debug_uart_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
    #define debug_uart_RTS_SS0_HSIOM_SEL_UART  (debug_uart_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */
#endif /* (debug_uart_RTS_SS0_PIN) */

#if (debug_uart_SS1_PIN)
    #define debug_uart_SS1_HSIOM_REG  (*(reg32 *) debug_uart_spi_ss1__0__HSIOM)
    #define debug_uart_SS1_HSIOM_PTR  ( (reg32 *) debug_uart_spi_ss1__0__HSIOM)
    
    #define debug_uart_SS1_HSIOM_MASK     (debug_uart_spi_ss1__0__HSIOM_MASK)
    #define debug_uart_SS1_HSIOM_POS      (debug_uart_spi_ss1__0__HSIOM_SHIFT)
    #define debug_uart_SS1_HSIOM_SEL_GPIO (debug_uart_spi_ss1__0__HSIOM_GPIO)
    #define debug_uart_SS1_HSIOM_SEL_I2C  (debug_uart_spi_ss1__0__HSIOM_I2C)
    #define debug_uart_SS1_HSIOM_SEL_SPI  (debug_uart_spi_ss1__0__HSIOM_SPI)
#endif /* (debug_uart_SS1_PIN) */

#if (debug_uart_SS2_PIN)
    #define debug_uart_SS2_HSIOM_REG     (*(reg32 *) debug_uart_spi_ss2__0__HSIOM)
    #define debug_uart_SS2_HSIOM_PTR     ( (reg32 *) debug_uart_spi_ss2__0__HSIOM)
    
    #define debug_uart_SS2_HSIOM_MASK     (debug_uart_spi_ss2__0__HSIOM_MASK)
    #define debug_uart_SS2_HSIOM_POS      (debug_uart_spi_ss2__0__HSIOM_SHIFT)
    #define debug_uart_SS2_HSIOM_SEL_GPIO (debug_uart_spi_ss2__0__HSIOM_GPIO)
    #define debug_uart_SS2_HSIOM_SEL_I2C  (debug_uart_spi_ss2__0__HSIOM_I2C)
    #define debug_uart_SS2_HSIOM_SEL_SPI  (debug_uart_spi_ss2__0__HSIOM_SPI)
#endif /* (debug_uart_SS2_PIN) */

#if (debug_uart_SS3_PIN)
    #define debug_uart_SS3_HSIOM_REG     (*(reg32 *) debug_uart_spi_ss3__0__HSIOM)
    #define debug_uart_SS3_HSIOM_PTR     ( (reg32 *) debug_uart_spi_ss3__0__HSIOM)
    
    #define debug_uart_SS3_HSIOM_MASK     (debug_uart_spi_ss3__0__HSIOM_MASK)
    #define debug_uart_SS3_HSIOM_POS      (debug_uart_spi_ss3__0__HSIOM_SHIFT)
    #define debug_uart_SS3_HSIOM_SEL_GPIO (debug_uart_spi_ss3__0__HSIOM_GPIO)
    #define debug_uart_SS3_HSIOM_SEL_I2C  (debug_uart_spi_ss3__0__HSIOM_I2C)
    #define debug_uart_SS3_HSIOM_SEL_SPI  (debug_uart_spi_ss3__0__HSIOM_SPI)
#endif /* (debug_uart_SS3_PIN) */

#if (debug_uart_I2C_PINS)
    #define debug_uart_SCL_HSIOM_REG  (*(reg32 *) debug_uart_scl__0__HSIOM)
    #define debug_uart_SCL_HSIOM_PTR  ( (reg32 *) debug_uart_scl__0__HSIOM)
    
    #define debug_uart_SCL_HSIOM_MASK     (debug_uart_scl__0__HSIOM_MASK)
    #define debug_uart_SCL_HSIOM_POS      (debug_uart_scl__0__HSIOM_SHIFT)
    #define debug_uart_SCL_HSIOM_SEL_GPIO (debug_uart_sda__0__HSIOM_GPIO)
    #define debug_uart_SCL_HSIOM_SEL_I2C  (debug_uart_sda__0__HSIOM_I2C)
    
    #define debug_uart_SDA_HSIOM_REG  (*(reg32 *) debug_uart_sda__0__HSIOM)
    #define debug_uart_SDA_HSIOM_PTR  ( (reg32 *) debug_uart_sda__0__HSIOM)
    
    #define debug_uart_SDA_HSIOM_MASK     (debug_uart_sda__0__HSIOM_MASK)
    #define debug_uart_SDA_HSIOM_POS      (debug_uart_sda__0__HSIOM_SHIFT)
    #define debug_uart_SDA_HSIOM_SEL_GPIO (debug_uart_sda__0__HSIOM_GPIO)
    #define debug_uart_SDA_HSIOM_SEL_I2C  (debug_uart_sda__0__HSIOM_I2C)
#endif /* (debug_uart_I2C_PINS) */

#if (debug_uart_SPI_SLAVE_PINS)
    #define debug_uart_SCLK_S_HSIOM_REG   (*(reg32 *) debug_uart_sclk_s__0__HSIOM)
    #define debug_uart_SCLK_S_HSIOM_PTR   ( (reg32 *) debug_uart_sclk_s__0__HSIOM)
    
    #define debug_uart_SCLK_S_HSIOM_MASK      (debug_uart_sclk_s__0__HSIOM_MASK)
    #define debug_uart_SCLK_S_HSIOM_POS       (debug_uart_sclk_s__0__HSIOM_SHIFT)
    #define debug_uart_SCLK_S_HSIOM_SEL_GPIO  (debug_uart_sclk_s__0__HSIOM_GPIO)
    #define debug_uart_SCLK_S_HSIOM_SEL_SPI   (debug_uart_sclk_s__0__HSIOM_SPI)
    
    #define debug_uart_SS0_S_HSIOM_REG    (*(reg32 *) debug_uart_ss0_s__0__HSIOM)
    #define debug_uart_SS0_S_HSIOM_PTR    ( (reg32 *) debug_uart_ss0_s__0__HSIOM)
    
    #define debug_uart_SS0_S_HSIOM_MASK       (debug_uart_ss0_s__0__HSIOM_MASK)
    #define debug_uart_SS0_S_HSIOM_POS        (debug_uart_ss0_s__0__HSIOM_SHIFT)
    #define debug_uart_SS0_S_HSIOM_SEL_GPIO   (debug_uart_ss0_s__0__HSIOM_GPIO)  
    #define debug_uart_SS0_S_HSIOM_SEL_SPI    (debug_uart_ss0_s__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_SLAVE_PINS) */

#if (debug_uart_SPI_SLAVE_MOSI_PIN)
    #define debug_uart_MOSI_S_HSIOM_REG   (*(reg32 *) debug_uart_mosi_s__0__HSIOM)
    #define debug_uart_MOSI_S_HSIOM_PTR   ( (reg32 *) debug_uart_mosi_s__0__HSIOM)
    
    #define debug_uart_MOSI_S_HSIOM_MASK      (debug_uart_mosi_s__0__HSIOM_MASK)
    #define debug_uart_MOSI_S_HSIOM_POS       (debug_uart_mosi_s__0__HSIOM_SHIFT)
    #define debug_uart_MOSI_S_HSIOM_SEL_GPIO  (debug_uart_mosi_s__0__HSIOM_GPIO)
    #define debug_uart_MOSI_S_HSIOM_SEL_SPI   (debug_uart_mosi_s__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_SLAVE_MOSI_PIN) */

#if (debug_uart_SPI_SLAVE_MISO_PIN)
    #define debug_uart_MISO_S_HSIOM_REG   (*(reg32 *) debug_uart_miso_s__0__HSIOM)
    #define debug_uart_MISO_S_HSIOM_PTR   ( (reg32 *) debug_uart_miso_s__0__HSIOM)
    
    #define debug_uart_MISO_S_HSIOM_MASK      (debug_uart_miso_s__0__HSIOM_MASK)
    #define debug_uart_MISO_S_HSIOM_POS       (debug_uart_miso_s__0__HSIOM_SHIFT)
    #define debug_uart_MISO_S_HSIOM_SEL_GPIO  (debug_uart_miso_s__0__HSIOM_GPIO)
    #define debug_uart_MISO_S_HSIOM_SEL_SPI   (debug_uart_miso_s__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_SLAVE_MISO_PIN) */

#if (debug_uart_SPI_MASTER_MISO_PIN)
    #define debug_uart_MISO_M_HSIOM_REG   (*(reg32 *) debug_uart_miso_m__0__HSIOM)
    #define debug_uart_MISO_M_HSIOM_PTR   ( (reg32 *) debug_uart_miso_m__0__HSIOM)
    
    #define debug_uart_MISO_M_HSIOM_MASK      (debug_uart_miso_m__0__HSIOM_MASK)
    #define debug_uart_MISO_M_HSIOM_POS       (debug_uart_miso_m__0__HSIOM_SHIFT)
    #define debug_uart_MISO_M_HSIOM_SEL_GPIO  (debug_uart_miso_m__0__HSIOM_GPIO)
    #define debug_uart_MISO_M_HSIOM_SEL_SPI   (debug_uart_miso_m__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_MASTER_MISO_PIN) */

#if (debug_uart_SPI_MASTER_MOSI_PIN)
    #define debug_uart_MOSI_M_HSIOM_REG   (*(reg32 *) debug_uart_mosi_m__0__HSIOM)
    #define debug_uart_MOSI_M_HSIOM_PTR   ( (reg32 *) debug_uart_mosi_m__0__HSIOM)
    
    #define debug_uart_MOSI_M_HSIOM_MASK      (debug_uart_mosi_m__0__HSIOM_MASK)
    #define debug_uart_MOSI_M_HSIOM_POS       (debug_uart_mosi_m__0__HSIOM_SHIFT)
    #define debug_uart_MOSI_M_HSIOM_SEL_GPIO  (debug_uart_mosi_m__0__HSIOM_GPIO)
    #define debug_uart_MOSI_M_HSIOM_SEL_SPI   (debug_uart_mosi_m__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_MASTER_MOSI_PIN) */

#if (debug_uart_SPI_MASTER_SCLK_PIN)
    #define debug_uart_SCLK_M_HSIOM_REG   (*(reg32 *) debug_uart_sclk_m__0__HSIOM)
    #define debug_uart_SCLK_M_HSIOM_PTR   ( (reg32 *) debug_uart_sclk_m__0__HSIOM)
    
    #define debug_uart_SCLK_M_HSIOM_MASK      (debug_uart_sclk_m__0__HSIOM_MASK)
    #define debug_uart_SCLK_M_HSIOM_POS       (debug_uart_sclk_m__0__HSIOM_SHIFT)
    #define debug_uart_SCLK_M_HSIOM_SEL_GPIO  (debug_uart_sclk_m__0__HSIOM_GPIO)
    #define debug_uart_SCLK_M_HSIOM_SEL_SPI   (debug_uart_sclk_m__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_MASTER_SCLK_PIN) */

#if (debug_uart_SPI_MASTER_SS0_PIN)
    #define debug_uart_SS0_M_HSIOM_REG    (*(reg32 *) debug_uart_ss0_m__0__HSIOM)
    #define debug_uart_SS0_M_HSIOM_PTR    ( (reg32 *) debug_uart_ss0_m__0__HSIOM)
    
    #define debug_uart_SS0_M_HSIOM_MASK       (debug_uart_ss0_m__0__HSIOM_MASK)
    #define debug_uart_SS0_M_HSIOM_POS        (debug_uart_ss0_m__0__HSIOM_SHIFT)
    #define debug_uart_SS0_M_HSIOM_SEL_GPIO   (debug_uart_ss0_m__0__HSIOM_GPIO)
    #define debug_uart_SS0_M_HSIOM_SEL_SPI    (debug_uart_ss0_m__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_MASTER_SS0_PIN) */

#if (debug_uart_SPI_MASTER_SS1_PIN)
    #define debug_uart_SS1_M_HSIOM_REG    (*(reg32 *) debug_uart_ss1_m__0__HSIOM)
    #define debug_uart_SS1_M_HSIOM_PTR    ( (reg32 *) debug_uart_ss1_m__0__HSIOM)
    
    #define debug_uart_SS1_M_HSIOM_MASK       (debug_uart_ss1_m__0__HSIOM_MASK)
    #define debug_uart_SS1_M_HSIOM_POS        (debug_uart_ss1_m__0__HSIOM_SHIFT)
    #define debug_uart_SS1_M_HSIOM_SEL_GPIO   (debug_uart_ss1_m__0__HSIOM_GPIO)
    #define debug_uart_SS1_M_HSIOM_SEL_SPI    (debug_uart_ss1_m__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_MASTER_SS1_PIN) */

#if (debug_uart_SPI_MASTER_SS2_PIN)
    #define debug_uart_SS2_M_HSIOM_REG    (*(reg32 *) debug_uart_ss2_m__0__HSIOM)
    #define debug_uart_SS2_M_HSIOM_PTR    ( (reg32 *) debug_uart_ss2_m__0__HSIOM)
    
    #define debug_uart_SS2_M_HSIOM_MASK       (debug_uart_ss2_m__0__HSIOM_MASK)
    #define debug_uart_SS2_M_HSIOM_POS        (debug_uart_ss2_m__0__HSIOM_SHIFT)
    #define debug_uart_SS2_M_HSIOM_SEL_GPIO   (debug_uart_ss2_m__0__HSIOM_GPIO)
    #define debug_uart_SS2_M_HSIOM_SEL_SPI    (debug_uart_ss2_m__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_MASTER_SS2_PIN) */

#if (debug_uart_SPI_MASTER_SS3_PIN)
    #define debug_uart_SS3_M_HSIOM_REG    (*(reg32 *) debug_uart_ss3_m__0__HSIOM)
    #define debug_uart_SS3_M_HSIOM_PTR    ( (reg32 *) debug_uart_ss3_m__0__HSIOM)
    
    #define debug_uart_SS3_M_HSIOM_MASK      (debug_uart_ss3_m__0__HSIOM_MASK)
    #define debug_uart_SS3_M_HSIOM_POS       (debug_uart_ss3_m__0__HSIOM_SHIFT)
    #define debug_uart_SS3_M_HSIOM_SEL_GPIO  (debug_uart_ss3_m__0__HSIOM_GPIO)
    #define debug_uart_SS3_M_HSIOM_SEL_SPI   (debug_uart_ss3_m__0__HSIOM_SPI)
#endif /* (debug_uart_SPI_MASTER_SS3_PIN) */

#if (debug_uart_UART_RX_PIN)
    #define debug_uart_RX_HSIOM_REG   (*(reg32 *) debug_uart_rx__0__HSIOM)
    #define debug_uart_RX_HSIOM_PTR   ( (reg32 *) debug_uart_rx__0__HSIOM)
    
    #define debug_uart_RX_HSIOM_MASK      (debug_uart_rx__0__HSIOM_MASK)
    #define debug_uart_RX_HSIOM_POS       (debug_uart_rx__0__HSIOM_SHIFT)
    #define debug_uart_RX_HSIOM_SEL_GPIO  (debug_uart_rx__0__HSIOM_GPIO)
    #define debug_uart_RX_HSIOM_SEL_UART  (debug_uart_rx__0__HSIOM_UART)
#endif /* (debug_uart_UART_RX_PIN) */

#if (debug_uart_UART_RX_WAKE_PIN)
    #define debug_uart_RX_WAKE_HSIOM_REG   (*(reg32 *) debug_uart_rx_wake__0__HSIOM)
    #define debug_uart_RX_WAKE_HSIOM_PTR   ( (reg32 *) debug_uart_rx_wake__0__HSIOM)
    
    #define debug_uart_RX_WAKE_HSIOM_MASK      (debug_uart_rx_wake__0__HSIOM_MASK)
    #define debug_uart_RX_WAKE_HSIOM_POS       (debug_uart_rx_wake__0__HSIOM_SHIFT)
    #define debug_uart_RX_WAKE_HSIOM_SEL_GPIO  (debug_uart_rx_wake__0__HSIOM_GPIO)
    #define debug_uart_RX_WAKE_HSIOM_SEL_UART  (debug_uart_rx_wake__0__HSIOM_UART)
#endif /* (debug_uart_UART_WAKE_RX_PIN) */

#if (debug_uart_UART_CTS_PIN)
    #define debug_uart_CTS_HSIOM_REG   (*(reg32 *) debug_uart_cts__0__HSIOM)
    #define debug_uart_CTS_HSIOM_PTR   ( (reg32 *) debug_uart_cts__0__HSIOM)
    
    #define debug_uart_CTS_HSIOM_MASK      (debug_uart_cts__0__HSIOM_MASK)
    #define debug_uart_CTS_HSIOM_POS       (debug_uart_cts__0__HSIOM_SHIFT)
    #define debug_uart_CTS_HSIOM_SEL_GPIO  (debug_uart_cts__0__HSIOM_GPIO)
    #define debug_uart_CTS_HSIOM_SEL_UART  (debug_uart_cts__0__HSIOM_UART)
#endif /* (debug_uart_UART_CTS_PIN) */

#if (debug_uart_UART_TX_PIN)
    #define debug_uart_TX_HSIOM_REG   (*(reg32 *) debug_uart_tx__0__HSIOM)
    #define debug_uart_TX_HSIOM_PTR   ( (reg32 *) debug_uart_tx__0__HSIOM)
    
    #define debug_uart_TX_HSIOM_MASK      (debug_uart_tx__0__HSIOM_MASK)
    #define debug_uart_TX_HSIOM_POS       (debug_uart_tx__0__HSIOM_SHIFT)
    #define debug_uart_TX_HSIOM_SEL_GPIO  (debug_uart_tx__0__HSIOM_GPIO)
    #define debug_uart_TX_HSIOM_SEL_UART  (debug_uart_tx__0__HSIOM_UART)
#endif /* (debug_uart_UART_TX_PIN) */

#if (debug_uart_UART_RX_TX_PIN)
    #define debug_uart_RX_TX_HSIOM_REG   (*(reg32 *) debug_uart_rx_tx__0__HSIOM)
    #define debug_uart_RX_TX_HSIOM_PTR   ( (reg32 *) debug_uart_rx_tx__0__HSIOM)
    
    #define debug_uart_RX_TX_HSIOM_MASK      (debug_uart_rx_tx__0__HSIOM_MASK)
    #define debug_uart_RX_TX_HSIOM_POS       (debug_uart_rx_tx__0__HSIOM_SHIFT)
    #define debug_uart_RX_TX_HSIOM_SEL_GPIO  (debug_uart_rx_tx__0__HSIOM_GPIO)
    #define debug_uart_RX_TX_HSIOM_SEL_UART  (debug_uart_rx_tx__0__HSIOM_UART)
#endif /* (debug_uart_UART_RX_TX_PIN) */

#if (debug_uart_UART_RTS_PIN)
    #define debug_uart_RTS_HSIOM_REG      (*(reg32 *) debug_uart_rts__0__HSIOM)
    #define debug_uart_RTS_HSIOM_PTR      ( (reg32 *) debug_uart_rts__0__HSIOM)
    
    #define debug_uart_RTS_HSIOM_MASK     (debug_uart_rts__0__HSIOM_MASK)
    #define debug_uart_RTS_HSIOM_POS      (debug_uart_rts__0__HSIOM_SHIFT)    
    #define debug_uart_RTS_HSIOM_SEL_GPIO (debug_uart_rts__0__HSIOM_GPIO)
    #define debug_uart_RTS_HSIOM_SEL_UART (debug_uart_rts__0__HSIOM_UART)    
#endif /* (debug_uart_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define debug_uart_HSIOM_DEF_SEL      (0x00u)
#define debug_uart_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for debug_uart_CY_SCBIP_V0 
* and debug_uart_CY_SCBIP_V1. It is not recommended to use them for 
* debug_uart_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define debug_uart_HSIOM_UART_SEL     (0x09u)
#define debug_uart_HSIOM_I2C_SEL      (0x0Eu)
#define debug_uart_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define debug_uart_RX_SCL_MOSI_PIN_INDEX       (0u)
#define debug_uart_TX_SDA_MISO_PIN_INDEX       (1u)
#define debug_uart_CTS_SCLK_PIN_INDEX       (2u)
#define debug_uart_RTS_SS0_PIN_INDEX       (3u)
#define debug_uart_SS1_PIN_INDEX                  (4u)
#define debug_uart_SS2_PIN_INDEX                  (5u)
#define debug_uart_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define debug_uart_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define debug_uart_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << debug_uart_RX_SCL_MOSI_PIN_INDEX)
#define debug_uart_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << debug_uart_TX_SDA_MISO_PIN_INDEX)
#define debug_uart_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << debug_uart_CTS_SCLK_PIN_INDEX)
#define debug_uart_RTS_SS0_PIN_MASK     ((uint32) 0x01u << debug_uart_RTS_SS0_PIN_INDEX)
#define debug_uart_SS1_PIN_MASK                ((uint32) 0x01u << debug_uart_SS1_PIN_INDEX)
#define debug_uart_SS2_PIN_MASK                ((uint32) 0x01u << debug_uart_SS2_PIN_INDEX)
#define debug_uart_SS3_PIN_MASK                ((uint32) 0x01u << debug_uart_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define debug_uart_INTCFG_TYPE_MASK           (0x03u)
#define debug_uart_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define debug_uart_PIN_DM_ALG_HIZ  (0u)
#define debug_uart_PIN_DM_DIG_HIZ  (1u)
#define debug_uart_PIN_DM_OD_LO    (4u)
#define debug_uart_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define debug_uart_DM_MASK    (0x7u)
#define debug_uart_DM_SIZE    (3u)
#define debug_uart_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) debug_uart_DM_MASK << (debug_uart_DM_SIZE * (pos)))) >> \
                                                              (debug_uart_DM_SIZE * (pos)) )

#if (debug_uart_TX_SDA_MISO_PIN)
    #define debug_uart_CHECK_TX_SDA_MISO_PIN_USED \
                (debug_uart_PIN_DM_ALG_HIZ != \
                    debug_uart_GET_P4_PIN_DM(debug_uart_uart_tx_i2c_sda_spi_miso_PC, \
                                                   debug_uart_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (debug_uart_TX_SDA_MISO_PIN) */

#if (debug_uart_RTS_SS0_PIN)
    #define debug_uart_CHECK_RTS_SS0_PIN_USED \
                (debug_uart_PIN_DM_ALG_HIZ != \
                    debug_uart_GET_P4_PIN_DM(debug_uart_uart_rts_spi_ss0_PC, \
                                                   debug_uart_uart_rts_spi_ss0_SHIFT))
#endif /* (debug_uart_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define debug_uart_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define debug_uart_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define debug_uart_SET_HSIOM_SEL(reg, mask, pos, sel) debug_uart_SET_REGISTER_BITS(reg, mask, pos, sel)
#define debug_uart_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        debug_uart_SET_REGISTER_BITS(reg, mask, pos, intType)
#define debug_uart_SET_INP_DIS(reg, mask, val) debug_uart_SET_REGISTER_BIT(reg, mask, val)

/* debug_uart_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  debug_uart_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (debug_uart_CY_SCBIP_V0)
#if (debug_uart_I2C_PINS)
    #define debug_uart_SET_I2C_SCL_DR(val) debug_uart_scl_Write(val)

    #define debug_uart_SET_I2C_SCL_HSIOM_SEL(sel) \
                          debug_uart_SET_HSIOM_SEL(debug_uart_SCL_HSIOM_REG,  \
                                                         debug_uart_SCL_HSIOM_MASK, \
                                                         debug_uart_SCL_HSIOM_POS,  \
                                                         (sel))
    #define debug_uart_WAIT_SCL_SET_HIGH  (0u == debug_uart_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (debug_uart_RX_WAKE_SCL_MOSI_PIN)
    #define debug_uart_SET_I2C_SCL_DR(val) \
                            debug_uart_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define debug_uart_SET_I2C_SCL_HSIOM_SEL(sel) \
                    debug_uart_SET_HSIOM_SEL(debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   debug_uart_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   debug_uart_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define debug_uart_WAIT_SCL_SET_HIGH  (0u == debug_uart_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (debug_uart_RX_SCL_MOSI_PIN)
    #define debug_uart_SET_I2C_SCL_DR(val) \
                            debug_uart_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define debug_uart_SET_I2C_SCL_HSIOM_SEL(sel) \
                            debug_uart_SET_HSIOM_SEL(debug_uart_RX_SCL_MOSI_HSIOM_REG,  \
                                                           debug_uart_RX_SCL_MOSI_HSIOM_MASK, \
                                                           debug_uart_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define debug_uart_WAIT_SCL_SET_HIGH  (0u == debug_uart_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define debug_uart_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define debug_uart_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define debug_uart_WAIT_SCL_SET_HIGH  (0u)
#endif /* (debug_uart_I2C_PINS) */

/* SCB I2C: sda signal */
#if (debug_uart_I2C_PINS)
    #define debug_uart_WAIT_SDA_SET_HIGH  (0u == debug_uart_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (debug_uart_TX_SDA_MISO_PIN)
    #define debug_uart_WAIT_SDA_SET_HIGH  (0u == debug_uart_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define debug_uart_WAIT_SDA_SET_HIGH  (0u)
#endif /* (debug_uart_MOSI_SCL_RX_PIN) */
#endif /* (debug_uart_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (debug_uart_RX_SCL_MOSI_PIN)
    #define debug_uart_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (debug_uart_RX_WAKE_SCL_MOSI_PIN)
    #define debug_uart_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) debug_uart_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(debug_uart_UART_RX_WAKE_PIN)
    #define debug_uart_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) debug_uart_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (debug_uart_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define debug_uart_REMOVE_MOSI_SCL_RX_WAKE_PIN    debug_uart_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define debug_uart_REMOVE_MOSI_SCL_RX_PIN         debug_uart_REMOVE_RX_SCL_MOSI_PIN
#define debug_uart_REMOVE_MISO_SDA_TX_PIN         debug_uart_REMOVE_TX_SDA_MISO_PIN
#ifndef debug_uart_REMOVE_SCLK_PIN
#define debug_uart_REMOVE_SCLK_PIN                debug_uart_REMOVE_CTS_SCLK_PIN
#endif /* debug_uart_REMOVE_SCLK_PIN */
#ifndef debug_uart_REMOVE_SS0_PIN
#define debug_uart_REMOVE_SS0_PIN                 debug_uart_REMOVE_RTS_SS0_PIN
#endif /* debug_uart_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define debug_uart_MOSI_SCL_RX_WAKE_PIN   debug_uart_RX_WAKE_SCL_MOSI_PIN
#define debug_uart_MOSI_SCL_RX_PIN        debug_uart_RX_SCL_MOSI_PIN
#define debug_uart_MISO_SDA_TX_PIN        debug_uart_TX_SDA_MISO_PIN
#ifndef debug_uart_SCLK_PIN
#define debug_uart_SCLK_PIN               debug_uart_CTS_SCLK_PIN
#endif /* debug_uart_SCLK_PIN */
#ifndef debug_uart_SS0_PIN
#define debug_uart_SS0_PIN                debug_uart_RTS_SS0_PIN
#endif /* debug_uart_SS0_PIN */

#if (debug_uart_MOSI_SCL_RX_WAKE_PIN)
    #define debug_uart_MOSI_SCL_RX_WAKE_HSIOM_REG     debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define debug_uart_MOSI_SCL_RX_WAKE_HSIOM_PTR     debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define debug_uart_MOSI_SCL_RX_WAKE_HSIOM_MASK    debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define debug_uart_MOSI_SCL_RX_WAKE_HSIOM_POS     debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define debug_uart_MOSI_SCL_RX_WAKE_INTCFG_REG    debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define debug_uart_MOSI_SCL_RX_WAKE_INTCFG_PTR    debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define debug_uart_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define debug_uart_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (debug_uart_RX_WAKE_SCL_MOSI_PIN) */

#if (debug_uart_MOSI_SCL_RX_PIN)
    #define debug_uart_MOSI_SCL_RX_HSIOM_REG      debug_uart_RX_SCL_MOSI_HSIOM_REG
    #define debug_uart_MOSI_SCL_RX_HSIOM_PTR      debug_uart_RX_SCL_MOSI_HSIOM_PTR
    #define debug_uart_MOSI_SCL_RX_HSIOM_MASK     debug_uart_RX_SCL_MOSI_HSIOM_MASK
    #define debug_uart_MOSI_SCL_RX_HSIOM_POS      debug_uart_RX_SCL_MOSI_HSIOM_POS
#endif /* (debug_uart_MOSI_SCL_RX_PIN) */

#if (debug_uart_MISO_SDA_TX_PIN)
    #define debug_uart_MISO_SDA_TX_HSIOM_REG      debug_uart_TX_SDA_MISO_HSIOM_REG
    #define debug_uart_MISO_SDA_TX_HSIOM_PTR      debug_uart_TX_SDA_MISO_HSIOM_REG
    #define debug_uart_MISO_SDA_TX_HSIOM_MASK     debug_uart_TX_SDA_MISO_HSIOM_REG
    #define debug_uart_MISO_SDA_TX_HSIOM_POS      debug_uart_TX_SDA_MISO_HSIOM_REG
#endif /* (debug_uart_MISO_SDA_TX_PIN_PIN) */

#if (debug_uart_SCLK_PIN)
    #ifndef debug_uart_SCLK_HSIOM_REG
    #define debug_uart_SCLK_HSIOM_REG     debug_uart_CTS_SCLK_HSIOM_REG
    #define debug_uart_SCLK_HSIOM_PTR     debug_uart_CTS_SCLK_HSIOM_PTR
    #define debug_uart_SCLK_HSIOM_MASK    debug_uart_CTS_SCLK_HSIOM_MASK
    #define debug_uart_SCLK_HSIOM_POS     debug_uart_CTS_SCLK_HSIOM_POS
    #endif /* debug_uart_SCLK_HSIOM_REG */
#endif /* (debug_uart_SCLK_PIN) */

#if (debug_uart_SS0_PIN)
    #ifndef debug_uart_SS0_HSIOM_REG
    #define debug_uart_SS0_HSIOM_REG      debug_uart_RTS_SS0_HSIOM_REG
    #define debug_uart_SS0_HSIOM_PTR      debug_uart_RTS_SS0_HSIOM_PTR
    #define debug_uart_SS0_HSIOM_MASK     debug_uart_RTS_SS0_HSIOM_MASK
    #define debug_uart_SS0_HSIOM_POS      debug_uart_RTS_SS0_HSIOM_POS
    #endif /* debug_uart_SS0_HSIOM_REG */
#endif /* (debug_uart_SS0_PIN) */

#define debug_uart_MOSI_SCL_RX_WAKE_PIN_INDEX debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX
#define debug_uart_MOSI_SCL_RX_PIN_INDEX      debug_uart_RX_SCL_MOSI_PIN_INDEX
#define debug_uart_MISO_SDA_TX_PIN_INDEX      debug_uart_TX_SDA_MISO_PIN_INDEX
#ifndef debug_uart_SCLK_PIN_INDEX
#define debug_uart_SCLK_PIN_INDEX             debug_uart_CTS_SCLK_PIN_INDEX
#endif /* debug_uart_SCLK_PIN_INDEX */
#ifndef debug_uart_SS0_PIN_INDEX
#define debug_uart_SS0_PIN_INDEX              debug_uart_RTS_SS0_PIN_INDEX
#endif /* debug_uart_SS0_PIN_INDEX */

#define debug_uart_MOSI_SCL_RX_WAKE_PIN_MASK debug_uart_RX_WAKE_SCL_MOSI_PIN_MASK
#define debug_uart_MOSI_SCL_RX_PIN_MASK      debug_uart_RX_SCL_MOSI_PIN_MASK
#define debug_uart_MISO_SDA_TX_PIN_MASK      debug_uart_TX_SDA_MISO_PIN_MASK
#ifndef debug_uart_SCLK_PIN_MASK
#define debug_uart_SCLK_PIN_MASK             debug_uart_CTS_SCLK_PIN_MASK
#endif /* debug_uart_SCLK_PIN_MASK */
#ifndef debug_uart_SS0_PIN_MASK
#define debug_uart_SS0_PIN_MASK              debug_uart_RTS_SS0_PIN_MASK
#endif /* debug_uart_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_debug_uart_H) */


/* [] END OF FILE */
