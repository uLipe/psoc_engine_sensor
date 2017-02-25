/***************************************************************************//**
* \file engine_sensor_uart_PINS.h
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

#if !defined(CY_SCB_PINS_engine_sensor_uart_H)
#define CY_SCB_PINS_engine_sensor_uart_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define engine_sensor_uart_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define engine_sensor_uart_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define engine_sensor_uart_REMOVE_TX_SDA_MISO_PIN      (1u)
#define engine_sensor_uart_REMOVE_CTS_SCLK_PIN      (1u)
#define engine_sensor_uart_REMOVE_RTS_SS0_PIN      (1u)
#define engine_sensor_uart_REMOVE_SS1_PIN                 (1u)
#define engine_sensor_uart_REMOVE_SS2_PIN                 (1u)
#define engine_sensor_uart_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define engine_sensor_uart_REMOVE_I2C_PINS                (1u)
#define engine_sensor_uart_REMOVE_SPI_MASTER_PINS         (1u)
#define engine_sensor_uart_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define engine_sensor_uart_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define engine_sensor_uart_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define engine_sensor_uart_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define engine_sensor_uart_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define engine_sensor_uart_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define engine_sensor_uart_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define engine_sensor_uart_REMOVE_SPI_SLAVE_PINS          (1u)
#define engine_sensor_uart_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define engine_sensor_uart_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define engine_sensor_uart_REMOVE_UART_TX_PIN             (0u)
#define engine_sensor_uart_REMOVE_UART_RX_TX_PIN          (1u)
#define engine_sensor_uart_REMOVE_UART_RX_PIN             (0u)
#define engine_sensor_uart_REMOVE_UART_RX_WAKE_PIN        (1u)
#define engine_sensor_uart_REMOVE_UART_RTS_PIN            (1u)
#define engine_sensor_uart_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN (0u == engine_sensor_uart_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define engine_sensor_uart_RX_SCL_MOSI_PIN     (0u == engine_sensor_uart_REMOVE_RX_SCL_MOSI_PIN)
#define engine_sensor_uart_TX_SDA_MISO_PIN     (0u == engine_sensor_uart_REMOVE_TX_SDA_MISO_PIN)
#define engine_sensor_uart_CTS_SCLK_PIN     (0u == engine_sensor_uart_REMOVE_CTS_SCLK_PIN)
#define engine_sensor_uart_RTS_SS0_PIN     (0u == engine_sensor_uart_REMOVE_RTS_SS0_PIN)
#define engine_sensor_uart_SS1_PIN                (0u == engine_sensor_uart_REMOVE_SS1_PIN)
#define engine_sensor_uart_SS2_PIN                (0u == engine_sensor_uart_REMOVE_SS2_PIN)
#define engine_sensor_uart_SS3_PIN                (0u == engine_sensor_uart_REMOVE_SS3_PIN)

/* Mode defined pins */
#define engine_sensor_uart_I2C_PINS               (0u == engine_sensor_uart_REMOVE_I2C_PINS)
#define engine_sensor_uart_SPI_MASTER_PINS        (0u == engine_sensor_uart_REMOVE_SPI_MASTER_PINS)
#define engine_sensor_uart_SPI_MASTER_SCLK_PIN    (0u == engine_sensor_uart_REMOVE_SPI_MASTER_SCLK_PIN)
#define engine_sensor_uart_SPI_MASTER_MOSI_PIN    (0u == engine_sensor_uart_REMOVE_SPI_MASTER_MOSI_PIN)
#define engine_sensor_uart_SPI_MASTER_MISO_PIN    (0u == engine_sensor_uart_REMOVE_SPI_MASTER_MISO_PIN)
#define engine_sensor_uart_SPI_MASTER_SS0_PIN     (0u == engine_sensor_uart_REMOVE_SPI_MASTER_SS0_PIN)
#define engine_sensor_uart_SPI_MASTER_SS1_PIN     (0u == engine_sensor_uart_REMOVE_SPI_MASTER_SS1_PIN)
#define engine_sensor_uart_SPI_MASTER_SS2_PIN     (0u == engine_sensor_uart_REMOVE_SPI_MASTER_SS2_PIN)
#define engine_sensor_uart_SPI_MASTER_SS3_PIN     (0u == engine_sensor_uart_REMOVE_SPI_MASTER_SS3_PIN)
#define engine_sensor_uart_SPI_SLAVE_PINS         (0u == engine_sensor_uart_REMOVE_SPI_SLAVE_PINS)
#define engine_sensor_uart_SPI_SLAVE_MOSI_PIN     (0u == engine_sensor_uart_REMOVE_SPI_SLAVE_MOSI_PIN)
#define engine_sensor_uart_SPI_SLAVE_MISO_PIN     (0u == engine_sensor_uart_REMOVE_SPI_SLAVE_MISO_PIN)
#define engine_sensor_uart_UART_TX_PIN            (0u == engine_sensor_uart_REMOVE_UART_TX_PIN)
#define engine_sensor_uart_UART_RX_TX_PIN         (0u == engine_sensor_uart_REMOVE_UART_RX_TX_PIN)
#define engine_sensor_uart_UART_RX_PIN            (0u == engine_sensor_uart_REMOVE_UART_RX_PIN)
#define engine_sensor_uart_UART_RX_WAKE_PIN       (0u == engine_sensor_uart_REMOVE_UART_RX_WAKE_PIN)
#define engine_sensor_uart_UART_RTS_PIN           (0u == engine_sensor_uart_REMOVE_UART_RTS_PIN)
#define engine_sensor_uart_UART_CTS_PIN           (0u == engine_sensor_uart_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN)
    #include "engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (engine_sensor_uart_RX_SCL_MOSI) */

#if (engine_sensor_uart_RX_SCL_MOSI_PIN)
    #include "engine_sensor_uart_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (engine_sensor_uart_RX_SCL_MOSI) */

#if (engine_sensor_uart_TX_SDA_MISO_PIN)
    #include "engine_sensor_uart_uart_tx_i2c_sda_spi_miso.h"
#endif /* (engine_sensor_uart_TX_SDA_MISO) */

#if (engine_sensor_uart_CTS_SCLK_PIN)
    #include "engine_sensor_uart_uart_cts_spi_sclk.h"
#endif /* (engine_sensor_uart_CTS_SCLK) */

#if (engine_sensor_uart_RTS_SS0_PIN)
    #include "engine_sensor_uart_uart_rts_spi_ss0.h"
#endif /* (engine_sensor_uart_RTS_SS0_PIN) */

#if (engine_sensor_uart_SS1_PIN)
    #include "engine_sensor_uart_spi_ss1.h"
#endif /* (engine_sensor_uart_SS1_PIN) */

#if (engine_sensor_uart_SS2_PIN)
    #include "engine_sensor_uart_spi_ss2.h"
#endif /* (engine_sensor_uart_SS2_PIN) */

#if (engine_sensor_uart_SS3_PIN)
    #include "engine_sensor_uart_spi_ss3.h"
#endif /* (engine_sensor_uart_SS3_PIN) */

#if (engine_sensor_uart_I2C_PINS)
    #include "engine_sensor_uart_scl.h"
    #include "engine_sensor_uart_sda.h"
#endif /* (engine_sensor_uart_I2C_PINS) */

#if (engine_sensor_uart_SPI_MASTER_PINS)
#if (engine_sensor_uart_SPI_MASTER_SCLK_PIN)
    #include "engine_sensor_uart_sclk_m.h"
#endif /* (engine_sensor_uart_SPI_MASTER_SCLK_PIN) */

#if (engine_sensor_uart_SPI_MASTER_MOSI_PIN)
    #include "engine_sensor_uart_mosi_m.h"
#endif /* (engine_sensor_uart_SPI_MASTER_MOSI_PIN) */

#if (engine_sensor_uart_SPI_MASTER_MISO_PIN)
    #include "engine_sensor_uart_miso_m.h"
#endif /*(engine_sensor_uart_SPI_MASTER_MISO_PIN) */
#endif /* (engine_sensor_uart_SPI_MASTER_PINS) */

#if (engine_sensor_uart_SPI_SLAVE_PINS)
    #include "engine_sensor_uart_sclk_s.h"
    #include "engine_sensor_uart_ss_s.h"

#if (engine_sensor_uart_SPI_SLAVE_MOSI_PIN)
    #include "engine_sensor_uart_mosi_s.h"
#endif /* (engine_sensor_uart_SPI_SLAVE_MOSI_PIN) */

#if (engine_sensor_uart_SPI_SLAVE_MISO_PIN)
    #include "engine_sensor_uart_miso_s.h"
#endif /*(engine_sensor_uart_SPI_SLAVE_MISO_PIN) */
#endif /* (engine_sensor_uart_SPI_SLAVE_PINS) */

#if (engine_sensor_uart_SPI_MASTER_SS0_PIN)
    #include "engine_sensor_uart_ss0_m.h"
#endif /* (engine_sensor_uart_SPI_MASTER_SS0_PIN) */

#if (engine_sensor_uart_SPI_MASTER_SS1_PIN)
    #include "engine_sensor_uart_ss1_m.h"
#endif /* (engine_sensor_uart_SPI_MASTER_SS1_PIN) */

#if (engine_sensor_uart_SPI_MASTER_SS2_PIN)
    #include "engine_sensor_uart_ss2_m.h"
#endif /* (engine_sensor_uart_SPI_MASTER_SS2_PIN) */

#if (engine_sensor_uart_SPI_MASTER_SS3_PIN)
    #include "engine_sensor_uart_ss3_m.h"
#endif /* (engine_sensor_uart_SPI_MASTER_SS3_PIN) */

#if (engine_sensor_uart_UART_TX_PIN)
    #include "engine_sensor_uart_tx.h"
#endif /* (engine_sensor_uart_UART_TX_PIN) */

#if (engine_sensor_uart_UART_RX_TX_PIN)
    #include "engine_sensor_uart_rx_tx.h"
#endif /* (engine_sensor_uart_UART_RX_TX_PIN) */

#if (engine_sensor_uart_UART_RX_PIN)
    #include "engine_sensor_uart_rx.h"
#endif /* (engine_sensor_uart_UART_RX_PIN) */

#if (engine_sensor_uart_UART_RX_WAKE_PIN)
    #include "engine_sensor_uart_rx_wake.h"
#endif /* (engine_sensor_uart_UART_RX_WAKE_PIN) */

#if (engine_sensor_uart_UART_RTS_PIN)
    #include "engine_sensor_uart_rts.h"
#endif /* (engine_sensor_uart_UART_RTS_PIN) */

#if (engine_sensor_uart_UART_CTS_PIN)
    #include "engine_sensor_uart_cts.h"
#endif /* (engine_sensor_uart_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (engine_sensor_uart_RX_SCL_MOSI_PIN)
    #define engine_sensor_uart_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) engine_sensor_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define engine_sensor_uart_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define engine_sensor_uart_RX_SCL_MOSI_HSIOM_MASK      (engine_sensor_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define engine_sensor_uart_RX_SCL_MOSI_HSIOM_POS       (engine_sensor_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define engine_sensor_uart_RX_SCL_MOSI_HSIOM_SEL_GPIO  (engine_sensor_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define engine_sensor_uart_RX_SCL_MOSI_HSIOM_SEL_I2C   (engine_sensor_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define engine_sensor_uart_RX_SCL_MOSI_HSIOM_SEL_SPI   (engine_sensor_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define engine_sensor_uart_RX_SCL_MOSI_HSIOM_SEL_UART  (engine_sensor_uart_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_MASK      (engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_POS       (engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define engine_sensor_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) engine_sensor_uart_INTCFG_TYPE_MASK << \
                                                                           engine_sensor_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins engine_sensor_uart_RX_SCL_MOSI_PIN or engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (engine_sensor_uart_RX_SCL_MOSI_PIN) */

#if (engine_sensor_uart_TX_SDA_MISO_PIN)
    #define engine_sensor_uart_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) engine_sensor_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define engine_sensor_uart_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define engine_sensor_uart_TX_SDA_MISO_HSIOM_MASK      (engine_sensor_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define engine_sensor_uart_TX_SDA_MISO_HSIOM_POS       (engine_sensor_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_GPIO  (engine_sensor_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_I2C   (engine_sensor_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_SPI   (engine_sensor_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_UART  (engine_sensor_uart_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (engine_sensor_uart_TX_SDA_MISO_PIN) */

#if (engine_sensor_uart_CTS_SCLK_PIN)
    #define engine_sensor_uart_CTS_SCLK_HSIOM_REG   (*(reg32 *) engine_sensor_uart_uart_cts_spi_sclk__0__HSIOM)
    #define engine_sensor_uart_CTS_SCLK_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_uart_cts_spi_sclk__0__HSIOM)
    
    #define engine_sensor_uart_CTS_SCLK_HSIOM_MASK      (engine_sensor_uart_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define engine_sensor_uart_CTS_SCLK_HSIOM_POS       (engine_sensor_uart_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define engine_sensor_uart_CTS_SCLK_HSIOM_SEL_GPIO  (engine_sensor_uart_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define engine_sensor_uart_CTS_SCLK_HSIOM_SEL_I2C   (engine_sensor_uart_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define engine_sensor_uart_CTS_SCLK_HSIOM_SEL_SPI   (engine_sensor_uart_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define engine_sensor_uart_CTS_SCLK_HSIOM_SEL_UART  (engine_sensor_uart_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (engine_sensor_uart_CTS_SCLK_PIN) */

#if (engine_sensor_uart_RTS_SS0_PIN)
    #define engine_sensor_uart_RTS_SS0_HSIOM_REG   (*(reg32 *) engine_sensor_uart_uart_rts_spi_ss0__0__HSIOM)
    #define engine_sensor_uart_RTS_SS0_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_uart_rts_spi_ss0__0__HSIOM)
    
    #define engine_sensor_uart_RTS_SS0_HSIOM_MASK      (engine_sensor_uart_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define engine_sensor_uart_RTS_SS0_HSIOM_POS       (engine_sensor_uart_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define engine_sensor_uart_RTS_SS0_HSIOM_SEL_GPIO  (engine_sensor_uart_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define engine_sensor_uart_RTS_SS0_HSIOM_SEL_I2C   (engine_sensor_uart_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define engine_sensor_uart_RTS_SS0_HSIOM_SEL_SPI   (engine_sensor_uart_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
    #define engine_sensor_uart_RTS_SS0_HSIOM_SEL_UART  (engine_sensor_uart_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */
#endif /* (engine_sensor_uart_RTS_SS0_PIN) */

#if (engine_sensor_uart_SS1_PIN)
    #define engine_sensor_uart_SS1_HSIOM_REG  (*(reg32 *) engine_sensor_uart_spi_ss1__0__HSIOM)
    #define engine_sensor_uart_SS1_HSIOM_PTR  ( (reg32 *) engine_sensor_uart_spi_ss1__0__HSIOM)
    
    #define engine_sensor_uart_SS1_HSIOM_MASK     (engine_sensor_uart_spi_ss1__0__HSIOM_MASK)
    #define engine_sensor_uart_SS1_HSIOM_POS      (engine_sensor_uart_spi_ss1__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SS1_HSIOM_SEL_GPIO (engine_sensor_uart_spi_ss1__0__HSIOM_GPIO)
    #define engine_sensor_uart_SS1_HSIOM_SEL_I2C  (engine_sensor_uart_spi_ss1__0__HSIOM_I2C)
    #define engine_sensor_uart_SS1_HSIOM_SEL_SPI  (engine_sensor_uart_spi_ss1__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SS1_PIN) */

#if (engine_sensor_uart_SS2_PIN)
    #define engine_sensor_uart_SS2_HSIOM_REG     (*(reg32 *) engine_sensor_uart_spi_ss2__0__HSIOM)
    #define engine_sensor_uart_SS2_HSIOM_PTR     ( (reg32 *) engine_sensor_uart_spi_ss2__0__HSIOM)
    
    #define engine_sensor_uart_SS2_HSIOM_MASK     (engine_sensor_uart_spi_ss2__0__HSIOM_MASK)
    #define engine_sensor_uart_SS2_HSIOM_POS      (engine_sensor_uart_spi_ss2__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SS2_HSIOM_SEL_GPIO (engine_sensor_uart_spi_ss2__0__HSIOM_GPIO)
    #define engine_sensor_uart_SS2_HSIOM_SEL_I2C  (engine_sensor_uart_spi_ss2__0__HSIOM_I2C)
    #define engine_sensor_uart_SS2_HSIOM_SEL_SPI  (engine_sensor_uart_spi_ss2__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SS2_PIN) */

#if (engine_sensor_uart_SS3_PIN)
    #define engine_sensor_uart_SS3_HSIOM_REG     (*(reg32 *) engine_sensor_uart_spi_ss3__0__HSIOM)
    #define engine_sensor_uart_SS3_HSIOM_PTR     ( (reg32 *) engine_sensor_uart_spi_ss3__0__HSIOM)
    
    #define engine_sensor_uart_SS3_HSIOM_MASK     (engine_sensor_uart_spi_ss3__0__HSIOM_MASK)
    #define engine_sensor_uart_SS3_HSIOM_POS      (engine_sensor_uart_spi_ss3__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SS3_HSIOM_SEL_GPIO (engine_sensor_uart_spi_ss3__0__HSIOM_GPIO)
    #define engine_sensor_uart_SS3_HSIOM_SEL_I2C  (engine_sensor_uart_spi_ss3__0__HSIOM_I2C)
    #define engine_sensor_uart_SS3_HSIOM_SEL_SPI  (engine_sensor_uart_spi_ss3__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SS3_PIN) */

#if (engine_sensor_uart_I2C_PINS)
    #define engine_sensor_uart_SCL_HSIOM_REG  (*(reg32 *) engine_sensor_uart_scl__0__HSIOM)
    #define engine_sensor_uart_SCL_HSIOM_PTR  ( (reg32 *) engine_sensor_uart_scl__0__HSIOM)
    
    #define engine_sensor_uart_SCL_HSIOM_MASK     (engine_sensor_uart_scl__0__HSIOM_MASK)
    #define engine_sensor_uart_SCL_HSIOM_POS      (engine_sensor_uart_scl__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SCL_HSIOM_SEL_GPIO (engine_sensor_uart_sda__0__HSIOM_GPIO)
    #define engine_sensor_uart_SCL_HSIOM_SEL_I2C  (engine_sensor_uart_sda__0__HSIOM_I2C)
    
    #define engine_sensor_uart_SDA_HSIOM_REG  (*(reg32 *) engine_sensor_uart_sda__0__HSIOM)
    #define engine_sensor_uart_SDA_HSIOM_PTR  ( (reg32 *) engine_sensor_uart_sda__0__HSIOM)
    
    #define engine_sensor_uart_SDA_HSIOM_MASK     (engine_sensor_uart_sda__0__HSIOM_MASK)
    #define engine_sensor_uart_SDA_HSIOM_POS      (engine_sensor_uart_sda__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SDA_HSIOM_SEL_GPIO (engine_sensor_uart_sda__0__HSIOM_GPIO)
    #define engine_sensor_uart_SDA_HSIOM_SEL_I2C  (engine_sensor_uart_sda__0__HSIOM_I2C)
#endif /* (engine_sensor_uart_I2C_PINS) */

#if (engine_sensor_uart_SPI_SLAVE_PINS)
    #define engine_sensor_uart_SCLK_S_HSIOM_REG   (*(reg32 *) engine_sensor_uart_sclk_s__0__HSIOM)
    #define engine_sensor_uart_SCLK_S_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_sclk_s__0__HSIOM)
    
    #define engine_sensor_uart_SCLK_S_HSIOM_MASK      (engine_sensor_uart_sclk_s__0__HSIOM_MASK)
    #define engine_sensor_uart_SCLK_S_HSIOM_POS       (engine_sensor_uart_sclk_s__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SCLK_S_HSIOM_SEL_GPIO  (engine_sensor_uart_sclk_s__0__HSIOM_GPIO)
    #define engine_sensor_uart_SCLK_S_HSIOM_SEL_SPI   (engine_sensor_uart_sclk_s__0__HSIOM_SPI)
    
    #define engine_sensor_uart_SS0_S_HSIOM_REG    (*(reg32 *) engine_sensor_uart_ss0_s__0__HSIOM)
    #define engine_sensor_uart_SS0_S_HSIOM_PTR    ( (reg32 *) engine_sensor_uart_ss0_s__0__HSIOM)
    
    #define engine_sensor_uart_SS0_S_HSIOM_MASK       (engine_sensor_uart_ss0_s__0__HSIOM_MASK)
    #define engine_sensor_uart_SS0_S_HSIOM_POS        (engine_sensor_uart_ss0_s__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SS0_S_HSIOM_SEL_GPIO   (engine_sensor_uart_ss0_s__0__HSIOM_GPIO)  
    #define engine_sensor_uart_SS0_S_HSIOM_SEL_SPI    (engine_sensor_uart_ss0_s__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_SLAVE_PINS) */

#if (engine_sensor_uart_SPI_SLAVE_MOSI_PIN)
    #define engine_sensor_uart_MOSI_S_HSIOM_REG   (*(reg32 *) engine_sensor_uart_mosi_s__0__HSIOM)
    #define engine_sensor_uart_MOSI_S_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_mosi_s__0__HSIOM)
    
    #define engine_sensor_uart_MOSI_S_HSIOM_MASK      (engine_sensor_uart_mosi_s__0__HSIOM_MASK)
    #define engine_sensor_uart_MOSI_S_HSIOM_POS       (engine_sensor_uart_mosi_s__0__HSIOM_SHIFT)
    #define engine_sensor_uart_MOSI_S_HSIOM_SEL_GPIO  (engine_sensor_uart_mosi_s__0__HSIOM_GPIO)
    #define engine_sensor_uart_MOSI_S_HSIOM_SEL_SPI   (engine_sensor_uart_mosi_s__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_SLAVE_MOSI_PIN) */

#if (engine_sensor_uart_SPI_SLAVE_MISO_PIN)
    #define engine_sensor_uart_MISO_S_HSIOM_REG   (*(reg32 *) engine_sensor_uart_miso_s__0__HSIOM)
    #define engine_sensor_uart_MISO_S_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_miso_s__0__HSIOM)
    
    #define engine_sensor_uart_MISO_S_HSIOM_MASK      (engine_sensor_uart_miso_s__0__HSIOM_MASK)
    #define engine_sensor_uart_MISO_S_HSIOM_POS       (engine_sensor_uart_miso_s__0__HSIOM_SHIFT)
    #define engine_sensor_uart_MISO_S_HSIOM_SEL_GPIO  (engine_sensor_uart_miso_s__0__HSIOM_GPIO)
    #define engine_sensor_uart_MISO_S_HSIOM_SEL_SPI   (engine_sensor_uart_miso_s__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_SLAVE_MISO_PIN) */

#if (engine_sensor_uart_SPI_MASTER_MISO_PIN)
    #define engine_sensor_uart_MISO_M_HSIOM_REG   (*(reg32 *) engine_sensor_uart_miso_m__0__HSIOM)
    #define engine_sensor_uart_MISO_M_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_miso_m__0__HSIOM)
    
    #define engine_sensor_uart_MISO_M_HSIOM_MASK      (engine_sensor_uart_miso_m__0__HSIOM_MASK)
    #define engine_sensor_uart_MISO_M_HSIOM_POS       (engine_sensor_uart_miso_m__0__HSIOM_SHIFT)
    #define engine_sensor_uart_MISO_M_HSIOM_SEL_GPIO  (engine_sensor_uart_miso_m__0__HSIOM_GPIO)
    #define engine_sensor_uart_MISO_M_HSIOM_SEL_SPI   (engine_sensor_uart_miso_m__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_MASTER_MISO_PIN) */

#if (engine_sensor_uart_SPI_MASTER_MOSI_PIN)
    #define engine_sensor_uart_MOSI_M_HSIOM_REG   (*(reg32 *) engine_sensor_uart_mosi_m__0__HSIOM)
    #define engine_sensor_uart_MOSI_M_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_mosi_m__0__HSIOM)
    
    #define engine_sensor_uart_MOSI_M_HSIOM_MASK      (engine_sensor_uart_mosi_m__0__HSIOM_MASK)
    #define engine_sensor_uart_MOSI_M_HSIOM_POS       (engine_sensor_uart_mosi_m__0__HSIOM_SHIFT)
    #define engine_sensor_uart_MOSI_M_HSIOM_SEL_GPIO  (engine_sensor_uart_mosi_m__0__HSIOM_GPIO)
    #define engine_sensor_uart_MOSI_M_HSIOM_SEL_SPI   (engine_sensor_uart_mosi_m__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_MASTER_MOSI_PIN) */

#if (engine_sensor_uart_SPI_MASTER_SCLK_PIN)
    #define engine_sensor_uart_SCLK_M_HSIOM_REG   (*(reg32 *) engine_sensor_uart_sclk_m__0__HSIOM)
    #define engine_sensor_uart_SCLK_M_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_sclk_m__0__HSIOM)
    
    #define engine_sensor_uart_SCLK_M_HSIOM_MASK      (engine_sensor_uart_sclk_m__0__HSIOM_MASK)
    #define engine_sensor_uart_SCLK_M_HSIOM_POS       (engine_sensor_uart_sclk_m__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SCLK_M_HSIOM_SEL_GPIO  (engine_sensor_uart_sclk_m__0__HSIOM_GPIO)
    #define engine_sensor_uart_SCLK_M_HSIOM_SEL_SPI   (engine_sensor_uart_sclk_m__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_MASTER_SCLK_PIN) */

#if (engine_sensor_uart_SPI_MASTER_SS0_PIN)
    #define engine_sensor_uart_SS0_M_HSIOM_REG    (*(reg32 *) engine_sensor_uart_ss0_m__0__HSIOM)
    #define engine_sensor_uart_SS0_M_HSIOM_PTR    ( (reg32 *) engine_sensor_uart_ss0_m__0__HSIOM)
    
    #define engine_sensor_uart_SS0_M_HSIOM_MASK       (engine_sensor_uart_ss0_m__0__HSIOM_MASK)
    #define engine_sensor_uart_SS0_M_HSIOM_POS        (engine_sensor_uart_ss0_m__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SS0_M_HSIOM_SEL_GPIO   (engine_sensor_uart_ss0_m__0__HSIOM_GPIO)
    #define engine_sensor_uart_SS0_M_HSIOM_SEL_SPI    (engine_sensor_uart_ss0_m__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_MASTER_SS0_PIN) */

#if (engine_sensor_uart_SPI_MASTER_SS1_PIN)
    #define engine_sensor_uart_SS1_M_HSIOM_REG    (*(reg32 *) engine_sensor_uart_ss1_m__0__HSIOM)
    #define engine_sensor_uart_SS1_M_HSIOM_PTR    ( (reg32 *) engine_sensor_uart_ss1_m__0__HSIOM)
    
    #define engine_sensor_uart_SS1_M_HSIOM_MASK       (engine_sensor_uart_ss1_m__0__HSIOM_MASK)
    #define engine_sensor_uart_SS1_M_HSIOM_POS        (engine_sensor_uart_ss1_m__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SS1_M_HSIOM_SEL_GPIO   (engine_sensor_uart_ss1_m__0__HSIOM_GPIO)
    #define engine_sensor_uart_SS1_M_HSIOM_SEL_SPI    (engine_sensor_uart_ss1_m__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_MASTER_SS1_PIN) */

#if (engine_sensor_uart_SPI_MASTER_SS2_PIN)
    #define engine_sensor_uart_SS2_M_HSIOM_REG    (*(reg32 *) engine_sensor_uart_ss2_m__0__HSIOM)
    #define engine_sensor_uart_SS2_M_HSIOM_PTR    ( (reg32 *) engine_sensor_uart_ss2_m__0__HSIOM)
    
    #define engine_sensor_uart_SS2_M_HSIOM_MASK       (engine_sensor_uart_ss2_m__0__HSIOM_MASK)
    #define engine_sensor_uart_SS2_M_HSIOM_POS        (engine_sensor_uart_ss2_m__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SS2_M_HSIOM_SEL_GPIO   (engine_sensor_uart_ss2_m__0__HSIOM_GPIO)
    #define engine_sensor_uart_SS2_M_HSIOM_SEL_SPI    (engine_sensor_uart_ss2_m__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_MASTER_SS2_PIN) */

#if (engine_sensor_uart_SPI_MASTER_SS3_PIN)
    #define engine_sensor_uart_SS3_M_HSIOM_REG    (*(reg32 *) engine_sensor_uart_ss3_m__0__HSIOM)
    #define engine_sensor_uart_SS3_M_HSIOM_PTR    ( (reg32 *) engine_sensor_uart_ss3_m__0__HSIOM)
    
    #define engine_sensor_uart_SS3_M_HSIOM_MASK      (engine_sensor_uart_ss3_m__0__HSIOM_MASK)
    #define engine_sensor_uart_SS3_M_HSIOM_POS       (engine_sensor_uart_ss3_m__0__HSIOM_SHIFT)
    #define engine_sensor_uart_SS3_M_HSIOM_SEL_GPIO  (engine_sensor_uart_ss3_m__0__HSIOM_GPIO)
    #define engine_sensor_uart_SS3_M_HSIOM_SEL_SPI   (engine_sensor_uart_ss3_m__0__HSIOM_SPI)
#endif /* (engine_sensor_uart_SPI_MASTER_SS3_PIN) */

#if (engine_sensor_uart_UART_RX_PIN)
    #define engine_sensor_uart_RX_HSIOM_REG   (*(reg32 *) engine_sensor_uart_rx__0__HSIOM)
    #define engine_sensor_uart_RX_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_rx__0__HSIOM)
    
    #define engine_sensor_uart_RX_HSIOM_MASK      (engine_sensor_uart_rx__0__HSIOM_MASK)
    #define engine_sensor_uart_RX_HSIOM_POS       (engine_sensor_uart_rx__0__HSIOM_SHIFT)
    #define engine_sensor_uart_RX_HSIOM_SEL_GPIO  (engine_sensor_uart_rx__0__HSIOM_GPIO)
    #define engine_sensor_uart_RX_HSIOM_SEL_UART  (engine_sensor_uart_rx__0__HSIOM_UART)
#endif /* (engine_sensor_uart_UART_RX_PIN) */

#if (engine_sensor_uart_UART_RX_WAKE_PIN)
    #define engine_sensor_uart_RX_WAKE_HSIOM_REG   (*(reg32 *) engine_sensor_uart_rx_wake__0__HSIOM)
    #define engine_sensor_uart_RX_WAKE_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_rx_wake__0__HSIOM)
    
    #define engine_sensor_uart_RX_WAKE_HSIOM_MASK      (engine_sensor_uart_rx_wake__0__HSIOM_MASK)
    #define engine_sensor_uart_RX_WAKE_HSIOM_POS       (engine_sensor_uart_rx_wake__0__HSIOM_SHIFT)
    #define engine_sensor_uart_RX_WAKE_HSIOM_SEL_GPIO  (engine_sensor_uart_rx_wake__0__HSIOM_GPIO)
    #define engine_sensor_uart_RX_WAKE_HSIOM_SEL_UART  (engine_sensor_uart_rx_wake__0__HSIOM_UART)
#endif /* (engine_sensor_uart_UART_WAKE_RX_PIN) */

#if (engine_sensor_uart_UART_CTS_PIN)
    #define engine_sensor_uart_CTS_HSIOM_REG   (*(reg32 *) engine_sensor_uart_cts__0__HSIOM)
    #define engine_sensor_uart_CTS_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_cts__0__HSIOM)
    
    #define engine_sensor_uart_CTS_HSIOM_MASK      (engine_sensor_uart_cts__0__HSIOM_MASK)
    #define engine_sensor_uart_CTS_HSIOM_POS       (engine_sensor_uart_cts__0__HSIOM_SHIFT)
    #define engine_sensor_uart_CTS_HSIOM_SEL_GPIO  (engine_sensor_uart_cts__0__HSIOM_GPIO)
    #define engine_sensor_uart_CTS_HSIOM_SEL_UART  (engine_sensor_uart_cts__0__HSIOM_UART)
#endif /* (engine_sensor_uart_UART_CTS_PIN) */

#if (engine_sensor_uart_UART_TX_PIN)
    #define engine_sensor_uart_TX_HSIOM_REG   (*(reg32 *) engine_sensor_uart_tx__0__HSIOM)
    #define engine_sensor_uart_TX_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_tx__0__HSIOM)
    
    #define engine_sensor_uart_TX_HSIOM_MASK      (engine_sensor_uart_tx__0__HSIOM_MASK)
    #define engine_sensor_uart_TX_HSIOM_POS       (engine_sensor_uart_tx__0__HSIOM_SHIFT)
    #define engine_sensor_uart_TX_HSIOM_SEL_GPIO  (engine_sensor_uart_tx__0__HSIOM_GPIO)
    #define engine_sensor_uart_TX_HSIOM_SEL_UART  (engine_sensor_uart_tx__0__HSIOM_UART)
#endif /* (engine_sensor_uart_UART_TX_PIN) */

#if (engine_sensor_uart_UART_RX_TX_PIN)
    #define engine_sensor_uart_RX_TX_HSIOM_REG   (*(reg32 *) engine_sensor_uart_rx_tx__0__HSIOM)
    #define engine_sensor_uart_RX_TX_HSIOM_PTR   ( (reg32 *) engine_sensor_uart_rx_tx__0__HSIOM)
    
    #define engine_sensor_uart_RX_TX_HSIOM_MASK      (engine_sensor_uart_rx_tx__0__HSIOM_MASK)
    #define engine_sensor_uart_RX_TX_HSIOM_POS       (engine_sensor_uart_rx_tx__0__HSIOM_SHIFT)
    #define engine_sensor_uart_RX_TX_HSIOM_SEL_GPIO  (engine_sensor_uart_rx_tx__0__HSIOM_GPIO)
    #define engine_sensor_uart_RX_TX_HSIOM_SEL_UART  (engine_sensor_uart_rx_tx__0__HSIOM_UART)
#endif /* (engine_sensor_uart_UART_RX_TX_PIN) */

#if (engine_sensor_uart_UART_RTS_PIN)
    #define engine_sensor_uart_RTS_HSIOM_REG      (*(reg32 *) engine_sensor_uart_rts__0__HSIOM)
    #define engine_sensor_uart_RTS_HSIOM_PTR      ( (reg32 *) engine_sensor_uart_rts__0__HSIOM)
    
    #define engine_sensor_uart_RTS_HSIOM_MASK     (engine_sensor_uart_rts__0__HSIOM_MASK)
    #define engine_sensor_uart_RTS_HSIOM_POS      (engine_sensor_uart_rts__0__HSIOM_SHIFT)    
    #define engine_sensor_uart_RTS_HSIOM_SEL_GPIO (engine_sensor_uart_rts__0__HSIOM_GPIO)
    #define engine_sensor_uart_RTS_HSIOM_SEL_UART (engine_sensor_uart_rts__0__HSIOM_UART)    
#endif /* (engine_sensor_uart_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define engine_sensor_uart_HSIOM_DEF_SEL      (0x00u)
#define engine_sensor_uart_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for engine_sensor_uart_CY_SCBIP_V0 
* and engine_sensor_uart_CY_SCBIP_V1. It is not recommended to use them for 
* engine_sensor_uart_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define engine_sensor_uart_HSIOM_UART_SEL     (0x09u)
#define engine_sensor_uart_HSIOM_I2C_SEL      (0x0Eu)
#define engine_sensor_uart_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX       (0u)
#define engine_sensor_uart_TX_SDA_MISO_PIN_INDEX       (1u)
#define engine_sensor_uart_CTS_SCLK_PIN_INDEX       (2u)
#define engine_sensor_uart_RTS_SS0_PIN_INDEX       (3u)
#define engine_sensor_uart_SS1_PIN_INDEX                  (4u)
#define engine_sensor_uart_SS2_PIN_INDEX                  (5u)
#define engine_sensor_uart_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define engine_sensor_uart_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX)
#define engine_sensor_uart_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << engine_sensor_uart_TX_SDA_MISO_PIN_INDEX)
#define engine_sensor_uart_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << engine_sensor_uart_CTS_SCLK_PIN_INDEX)
#define engine_sensor_uart_RTS_SS0_PIN_MASK     ((uint32) 0x01u << engine_sensor_uart_RTS_SS0_PIN_INDEX)
#define engine_sensor_uart_SS1_PIN_MASK                ((uint32) 0x01u << engine_sensor_uart_SS1_PIN_INDEX)
#define engine_sensor_uart_SS2_PIN_MASK                ((uint32) 0x01u << engine_sensor_uart_SS2_PIN_INDEX)
#define engine_sensor_uart_SS3_PIN_MASK                ((uint32) 0x01u << engine_sensor_uart_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define engine_sensor_uart_INTCFG_TYPE_MASK           (0x03u)
#define engine_sensor_uart_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define engine_sensor_uart_PIN_DM_ALG_HIZ  (0u)
#define engine_sensor_uart_PIN_DM_DIG_HIZ  (1u)
#define engine_sensor_uart_PIN_DM_OD_LO    (4u)
#define engine_sensor_uart_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define engine_sensor_uart_DM_MASK    (0x7u)
#define engine_sensor_uart_DM_SIZE    (3u)
#define engine_sensor_uart_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) engine_sensor_uart_DM_MASK << (engine_sensor_uart_DM_SIZE * (pos)))) >> \
                                                              (engine_sensor_uart_DM_SIZE * (pos)) )

#if (engine_sensor_uart_TX_SDA_MISO_PIN)
    #define engine_sensor_uart_CHECK_TX_SDA_MISO_PIN_USED \
                (engine_sensor_uart_PIN_DM_ALG_HIZ != \
                    engine_sensor_uart_GET_P4_PIN_DM(engine_sensor_uart_uart_tx_i2c_sda_spi_miso_PC, \
                                                   engine_sensor_uart_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (engine_sensor_uart_TX_SDA_MISO_PIN) */

#if (engine_sensor_uart_RTS_SS0_PIN)
    #define engine_sensor_uart_CHECK_RTS_SS0_PIN_USED \
                (engine_sensor_uart_PIN_DM_ALG_HIZ != \
                    engine_sensor_uart_GET_P4_PIN_DM(engine_sensor_uart_uart_rts_spi_ss0_PC, \
                                                   engine_sensor_uart_uart_rts_spi_ss0_SHIFT))
#endif /* (engine_sensor_uart_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define engine_sensor_uart_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define engine_sensor_uart_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define engine_sensor_uart_SET_HSIOM_SEL(reg, mask, pos, sel) engine_sensor_uart_SET_REGISTER_BITS(reg, mask, pos, sel)
#define engine_sensor_uart_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        engine_sensor_uart_SET_REGISTER_BITS(reg, mask, pos, intType)
#define engine_sensor_uart_SET_INP_DIS(reg, mask, val) engine_sensor_uart_SET_REGISTER_BIT(reg, mask, val)

/* engine_sensor_uart_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  engine_sensor_uart_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (engine_sensor_uart_CY_SCBIP_V0)
#if (engine_sensor_uart_I2C_PINS)
    #define engine_sensor_uart_SET_I2C_SCL_DR(val) engine_sensor_uart_scl_Write(val)

    #define engine_sensor_uart_SET_I2C_SCL_HSIOM_SEL(sel) \
                          engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_SCL_HSIOM_REG,  \
                                                         engine_sensor_uart_SCL_HSIOM_MASK, \
                                                         engine_sensor_uart_SCL_HSIOM_POS,  \
                                                         (sel))
    #define engine_sensor_uart_WAIT_SCL_SET_HIGH  (0u == engine_sensor_uart_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN)
    #define engine_sensor_uart_SET_I2C_SCL_DR(val) \
                            engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define engine_sensor_uart_SET_I2C_SCL_HSIOM_SEL(sel) \
                    engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define engine_sensor_uart_WAIT_SCL_SET_HIGH  (0u == engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (engine_sensor_uart_RX_SCL_MOSI_PIN)
    #define engine_sensor_uart_SET_I2C_SCL_DR(val) \
                            engine_sensor_uart_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define engine_sensor_uart_SET_I2C_SCL_HSIOM_SEL(sel) \
                            engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_RX_SCL_MOSI_HSIOM_REG,  \
                                                           engine_sensor_uart_RX_SCL_MOSI_HSIOM_MASK, \
                                                           engine_sensor_uart_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define engine_sensor_uart_WAIT_SCL_SET_HIGH  (0u == engine_sensor_uart_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define engine_sensor_uart_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define engine_sensor_uart_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define engine_sensor_uart_WAIT_SCL_SET_HIGH  (0u)
#endif /* (engine_sensor_uart_I2C_PINS) */

/* SCB I2C: sda signal */
#if (engine_sensor_uart_I2C_PINS)
    #define engine_sensor_uart_WAIT_SDA_SET_HIGH  (0u == engine_sensor_uart_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (engine_sensor_uart_TX_SDA_MISO_PIN)
    #define engine_sensor_uart_WAIT_SDA_SET_HIGH  (0u == engine_sensor_uart_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define engine_sensor_uart_WAIT_SDA_SET_HIGH  (0u)
#endif /* (engine_sensor_uart_MOSI_SCL_RX_PIN) */
#endif /* (engine_sensor_uart_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (engine_sensor_uart_RX_SCL_MOSI_PIN)
    #define engine_sensor_uart_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN)
    #define engine_sensor_uart_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(engine_sensor_uart_UART_RX_WAKE_PIN)
    #define engine_sensor_uart_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) engine_sensor_uart_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (engine_sensor_uart_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define engine_sensor_uart_REMOVE_MOSI_SCL_RX_WAKE_PIN    engine_sensor_uart_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define engine_sensor_uart_REMOVE_MOSI_SCL_RX_PIN         engine_sensor_uart_REMOVE_RX_SCL_MOSI_PIN
#define engine_sensor_uart_REMOVE_MISO_SDA_TX_PIN         engine_sensor_uart_REMOVE_TX_SDA_MISO_PIN
#ifndef engine_sensor_uart_REMOVE_SCLK_PIN
#define engine_sensor_uart_REMOVE_SCLK_PIN                engine_sensor_uart_REMOVE_CTS_SCLK_PIN
#endif /* engine_sensor_uart_REMOVE_SCLK_PIN */
#ifndef engine_sensor_uart_REMOVE_SS0_PIN
#define engine_sensor_uart_REMOVE_SS0_PIN                 engine_sensor_uart_REMOVE_RTS_SS0_PIN
#endif /* engine_sensor_uart_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define engine_sensor_uart_MOSI_SCL_RX_WAKE_PIN   engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN
#define engine_sensor_uart_MOSI_SCL_RX_PIN        engine_sensor_uart_RX_SCL_MOSI_PIN
#define engine_sensor_uart_MISO_SDA_TX_PIN        engine_sensor_uart_TX_SDA_MISO_PIN
#ifndef engine_sensor_uart_SCLK_PIN
#define engine_sensor_uart_SCLK_PIN               engine_sensor_uart_CTS_SCLK_PIN
#endif /* engine_sensor_uart_SCLK_PIN */
#ifndef engine_sensor_uart_SS0_PIN
#define engine_sensor_uart_SS0_PIN                engine_sensor_uart_RTS_SS0_PIN
#endif /* engine_sensor_uart_SS0_PIN */

#if (engine_sensor_uart_MOSI_SCL_RX_WAKE_PIN)
    #define engine_sensor_uart_MOSI_SCL_RX_WAKE_HSIOM_REG     engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define engine_sensor_uart_MOSI_SCL_RX_WAKE_HSIOM_PTR     engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define engine_sensor_uart_MOSI_SCL_RX_WAKE_HSIOM_MASK    engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define engine_sensor_uart_MOSI_SCL_RX_WAKE_HSIOM_POS     engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define engine_sensor_uart_MOSI_SCL_RX_WAKE_INTCFG_REG    engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define engine_sensor_uart_MOSI_SCL_RX_WAKE_INTCFG_PTR    engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define engine_sensor_uart_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define engine_sensor_uart_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN) */

#if (engine_sensor_uart_MOSI_SCL_RX_PIN)
    #define engine_sensor_uart_MOSI_SCL_RX_HSIOM_REG      engine_sensor_uart_RX_SCL_MOSI_HSIOM_REG
    #define engine_sensor_uart_MOSI_SCL_RX_HSIOM_PTR      engine_sensor_uart_RX_SCL_MOSI_HSIOM_PTR
    #define engine_sensor_uart_MOSI_SCL_RX_HSIOM_MASK     engine_sensor_uart_RX_SCL_MOSI_HSIOM_MASK
    #define engine_sensor_uart_MOSI_SCL_RX_HSIOM_POS      engine_sensor_uart_RX_SCL_MOSI_HSIOM_POS
#endif /* (engine_sensor_uart_MOSI_SCL_RX_PIN) */

#if (engine_sensor_uart_MISO_SDA_TX_PIN)
    #define engine_sensor_uart_MISO_SDA_TX_HSIOM_REG      engine_sensor_uart_TX_SDA_MISO_HSIOM_REG
    #define engine_sensor_uart_MISO_SDA_TX_HSIOM_PTR      engine_sensor_uart_TX_SDA_MISO_HSIOM_REG
    #define engine_sensor_uart_MISO_SDA_TX_HSIOM_MASK     engine_sensor_uart_TX_SDA_MISO_HSIOM_REG
    #define engine_sensor_uart_MISO_SDA_TX_HSIOM_POS      engine_sensor_uart_TX_SDA_MISO_HSIOM_REG
#endif /* (engine_sensor_uart_MISO_SDA_TX_PIN_PIN) */

#if (engine_sensor_uart_SCLK_PIN)
    #ifndef engine_sensor_uart_SCLK_HSIOM_REG
    #define engine_sensor_uart_SCLK_HSIOM_REG     engine_sensor_uart_CTS_SCLK_HSIOM_REG
    #define engine_sensor_uart_SCLK_HSIOM_PTR     engine_sensor_uart_CTS_SCLK_HSIOM_PTR
    #define engine_sensor_uart_SCLK_HSIOM_MASK    engine_sensor_uart_CTS_SCLK_HSIOM_MASK
    #define engine_sensor_uart_SCLK_HSIOM_POS     engine_sensor_uart_CTS_SCLK_HSIOM_POS
    #endif /* engine_sensor_uart_SCLK_HSIOM_REG */
#endif /* (engine_sensor_uart_SCLK_PIN) */

#if (engine_sensor_uart_SS0_PIN)
    #ifndef engine_sensor_uart_SS0_HSIOM_REG
    #define engine_sensor_uart_SS0_HSIOM_REG      engine_sensor_uart_RTS_SS0_HSIOM_REG
    #define engine_sensor_uart_SS0_HSIOM_PTR      engine_sensor_uart_RTS_SS0_HSIOM_PTR
    #define engine_sensor_uart_SS0_HSIOM_MASK     engine_sensor_uart_RTS_SS0_HSIOM_MASK
    #define engine_sensor_uart_SS0_HSIOM_POS      engine_sensor_uart_RTS_SS0_HSIOM_POS
    #endif /* engine_sensor_uart_SS0_HSIOM_REG */
#endif /* (engine_sensor_uart_SS0_PIN) */

#define engine_sensor_uart_MOSI_SCL_RX_WAKE_PIN_INDEX engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX
#define engine_sensor_uart_MOSI_SCL_RX_PIN_INDEX      engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX
#define engine_sensor_uart_MISO_SDA_TX_PIN_INDEX      engine_sensor_uart_TX_SDA_MISO_PIN_INDEX
#ifndef engine_sensor_uart_SCLK_PIN_INDEX
#define engine_sensor_uart_SCLK_PIN_INDEX             engine_sensor_uart_CTS_SCLK_PIN_INDEX
#endif /* engine_sensor_uart_SCLK_PIN_INDEX */
#ifndef engine_sensor_uart_SS0_PIN_INDEX
#define engine_sensor_uart_SS0_PIN_INDEX              engine_sensor_uart_RTS_SS0_PIN_INDEX
#endif /* engine_sensor_uart_SS0_PIN_INDEX */

#define engine_sensor_uart_MOSI_SCL_RX_WAKE_PIN_MASK engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_MASK
#define engine_sensor_uart_MOSI_SCL_RX_PIN_MASK      engine_sensor_uart_RX_SCL_MOSI_PIN_MASK
#define engine_sensor_uart_MISO_SDA_TX_PIN_MASK      engine_sensor_uart_TX_SDA_MISO_PIN_MASK
#ifndef engine_sensor_uart_SCLK_PIN_MASK
#define engine_sensor_uart_SCLK_PIN_MASK             engine_sensor_uart_CTS_SCLK_PIN_MASK
#endif /* engine_sensor_uart_SCLK_PIN_MASK */
#ifndef engine_sensor_uart_SS0_PIN_MASK
#define engine_sensor_uart_SS0_PIN_MASK              engine_sensor_uart_RTS_SS0_PIN_MASK
#endif /* engine_sensor_uart_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_engine_sensor_uart_H) */


/* [] END OF FILE */
