/***************************************************************************//**
* \file engine_sensor_uart_UART.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  UART mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "engine_sensor_uart_PVT.h"
#include "engine_sensor_uart_SPI_UART_PVT.h"


#if (engine_sensor_uart_UART_WAKE_ENABLE_CONST && engine_sensor_uart_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when engine_sensor_uart_Sleep() function is called:
    * 0 � disable, other values � enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 engine_sensor_uart_skipStart = 1u;
    /** \} globals */
#endif /* (engine_sensor_uart_UART_WAKE_ENABLE_CONST && engine_sensor_uart_UART_RX_WAKEUP_IRQ) */

#if(engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const engine_sensor_uart_UART_INIT_STRUCT engine_sensor_uart_configUart =
    {
        engine_sensor_uart_UART_SUB_MODE,
        engine_sensor_uart_UART_DIRECTION,
        engine_sensor_uart_UART_DATA_BITS_NUM,
        engine_sensor_uart_UART_PARITY_TYPE,
        engine_sensor_uart_UART_STOP_BITS_NUM,
        engine_sensor_uart_UART_OVS_FACTOR,
        engine_sensor_uart_UART_IRDA_LOW_POWER,
        engine_sensor_uart_UART_MEDIAN_FILTER_ENABLE,
        engine_sensor_uart_UART_RETRY_ON_NACK,
        engine_sensor_uart_UART_IRDA_POLARITY,
        engine_sensor_uart_UART_DROP_ON_PARITY_ERR,
        engine_sensor_uart_UART_DROP_ON_FRAME_ERR,
        engine_sensor_uart_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        engine_sensor_uart_UART_MP_MODE_ENABLE,
        engine_sensor_uart_UART_MP_ACCEPT_ADDRESS,
        engine_sensor_uart_UART_MP_RX_ADDRESS,
        engine_sensor_uart_UART_MP_RX_ADDRESS_MASK,
        (uint32) engine_sensor_uart_SCB_IRQ_INTERNAL,
        engine_sensor_uart_UART_INTR_RX_MASK,
        engine_sensor_uart_UART_RX_TRIGGER_LEVEL,
        engine_sensor_uart_UART_INTR_TX_MASK,
        engine_sensor_uart_UART_TX_TRIGGER_LEVEL,
        (uint8) engine_sensor_uart_UART_BYTE_MODE_ENABLE,
        (uint8) engine_sensor_uart_UART_CTS_ENABLE,
        (uint8) engine_sensor_uart_UART_CTS_POLARITY,
        (uint8) engine_sensor_uart_UART_RTS_POLARITY,
        (uint8) engine_sensor_uart_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: engine_sensor_uart_UartInit
    ****************************************************************************//**
    *
    *  Configures the engine_sensor_uart for UART operation.
    *
    *  This function is intended specifically to be used when the engine_sensor_uart
    *  configuration is set to �Unconfigured engine_sensor_uart� in the customizer.
    *  After initializing the engine_sensor_uart in UART mode using this function,
    *  the component can be enabled using the engine_sensor_uart_Start() or
    * engine_sensor_uart_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void engine_sensor_uart_UartInit(const engine_sensor_uart_UART_INIT_STRUCT *config)
    {
        uint32 pinsConfig;

        if (NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Get direction to configure UART pins: TX, RX or TX+RX */
            pinsConfig  = config->direction;

        #if !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (engine_sensor_uart_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (engine_sensor_uart_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */

            /* Configure pins */
            engine_sensor_uart_SetPins(engine_sensor_uart_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            engine_sensor_uart_scbMode       = (uint8) engine_sensor_uart_SCB_MODE_UART;
            engine_sensor_uart_scbEnableWake = (uint8) config->enableWake;
            engine_sensor_uart_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            engine_sensor_uart_rxBuffer      =         config->rxBuffer;
            engine_sensor_uart_rxDataBits    = (uint8) config->dataBits;
            engine_sensor_uart_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            engine_sensor_uart_txBuffer      =         config->txBuffer;
            engine_sensor_uart_txDataBits    = (uint8) config->dataBits;
            engine_sensor_uart_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(engine_sensor_uart_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                engine_sensor_uart_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (engine_sensor_uart_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (engine_sensor_uart_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                engine_sensor_uart_CTRL_REG  = engine_sensor_uart_GET_CTRL_OVS(config->oversample);
            }

            engine_sensor_uart_CTRL_REG     |= engine_sensor_uart_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             engine_sensor_uart_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             engine_sensor_uart_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            engine_sensor_uart_UART_CTRL_REG = engine_sensor_uart_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            engine_sensor_uart_UART_RX_CTRL_REG = engine_sensor_uart_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        engine_sensor_uart_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        engine_sensor_uart_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        engine_sensor_uart_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        engine_sensor_uart_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(engine_sensor_uart_UART_PARITY_NONE != config->parity)
            {
               engine_sensor_uart_UART_RX_CTRL_REG |= engine_sensor_uart_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    engine_sensor_uart_UART_RX_CTRL_PARITY_ENABLED;
            }

            engine_sensor_uart_RX_CTRL_REG      = engine_sensor_uart_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                engine_sensor_uart_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                engine_sensor_uart_GET_UART_RX_CTRL_ENABLED(config->direction);

            engine_sensor_uart_RX_FIFO_CTRL_REG = engine_sensor_uart_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            engine_sensor_uart_RX_MATCH_REG     = engine_sensor_uart_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                engine_sensor_uart_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            engine_sensor_uart_UART_TX_CTRL_REG = engine_sensor_uart_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                engine_sensor_uart_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(engine_sensor_uart_UART_PARITY_NONE != config->parity)
            {
               engine_sensor_uart_UART_TX_CTRL_REG |= engine_sensor_uart_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    engine_sensor_uart_UART_TX_CTRL_PARITY_ENABLED;
            }

            engine_sensor_uart_TX_CTRL_REG      = engine_sensor_uart_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                engine_sensor_uart_GET_UART_TX_CTRL_ENABLED(config->direction);

            engine_sensor_uart_TX_FIFO_CTRL_REG = engine_sensor_uart_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
            engine_sensor_uart_UART_FLOW_CTRL_REG = engine_sensor_uart_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            engine_sensor_uart_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            engine_sensor_uart_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            engine_sensor_uart_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (engine_sensor_uart_ISR_NUMBER);
            CyIntSetPriority(engine_sensor_uart_ISR_NUMBER, engine_sensor_uart_ISR_PRIORITY);
            (void) CyIntSetVector(engine_sensor_uart_ISR_NUMBER, &engine_sensor_uart_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(engine_sensor_uart_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (engine_sensor_uart_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(engine_sensor_uart_RX_WAKE_ISR_NUMBER, engine_sensor_uart_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(engine_sensor_uart_RX_WAKE_ISR_NUMBER, &engine_sensor_uart_UART_WAKEUP_ISR);
        #endif /* (engine_sensor_uart_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            engine_sensor_uart_INTR_I2C_EC_MASK_REG = engine_sensor_uart_NO_INTR_SOURCES;
            engine_sensor_uart_INTR_SPI_EC_MASK_REG = engine_sensor_uart_NO_INTR_SOURCES;
            engine_sensor_uart_INTR_SLAVE_MASK_REG  = engine_sensor_uart_NO_INTR_SOURCES;
            engine_sensor_uart_INTR_MASTER_MASK_REG = engine_sensor_uart_NO_INTR_SOURCES;
            engine_sensor_uart_INTR_RX_MASK_REG     = config->rxInterruptMask;
            engine_sensor_uart_INTR_TX_MASK_REG     = config->txInterruptMask;
        
            /* Configure TX interrupt sources to restore. */
            engine_sensor_uart_IntrTxMask = LO16(engine_sensor_uart_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            engine_sensor_uart_rxBufferHead     = 0u;
            engine_sensor_uart_rxBufferTail     = 0u;
            engine_sensor_uart_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            engine_sensor_uart_txBufferHead = 0u;
            engine_sensor_uart_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: engine_sensor_uart_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void engine_sensor_uart_UartInit(void)
    {
        /* Configure UART interface */
        engine_sensor_uart_CTRL_REG = engine_sensor_uart_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        engine_sensor_uart_UART_CTRL_REG = engine_sensor_uart_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        engine_sensor_uart_UART_RX_CTRL_REG = engine_sensor_uart_UART_DEFAULT_UART_RX_CTRL;
        engine_sensor_uart_RX_CTRL_REG      = engine_sensor_uart_UART_DEFAULT_RX_CTRL;
        engine_sensor_uart_RX_FIFO_CTRL_REG = engine_sensor_uart_UART_DEFAULT_RX_FIFO_CTRL;
        engine_sensor_uart_RX_MATCH_REG     = engine_sensor_uart_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        engine_sensor_uart_UART_TX_CTRL_REG = engine_sensor_uart_UART_DEFAULT_UART_TX_CTRL;
        engine_sensor_uart_TX_CTRL_REG      = engine_sensor_uart_UART_DEFAULT_TX_CTRL;
        engine_sensor_uart_TX_FIFO_CTRL_REG = engine_sensor_uart_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
        engine_sensor_uart_UART_FLOW_CTRL_REG = engine_sensor_uart_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(engine_sensor_uart_SCB_IRQ_INTERNAL)
        CyIntDisable    (engine_sensor_uart_ISR_NUMBER);
        CyIntSetPriority(engine_sensor_uart_ISR_NUMBER, engine_sensor_uart_ISR_PRIORITY);
        (void) CyIntSetVector(engine_sensor_uart_ISR_NUMBER, &engine_sensor_uart_SPI_UART_ISR);
    #endif /* (engine_sensor_uart_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(engine_sensor_uart_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (engine_sensor_uart_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(engine_sensor_uart_RX_WAKE_ISR_NUMBER, engine_sensor_uart_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(engine_sensor_uart_RX_WAKE_ISR_NUMBER, &engine_sensor_uart_UART_WAKEUP_ISR);
    #endif /* (engine_sensor_uart_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        engine_sensor_uart_INTR_I2C_EC_MASK_REG = engine_sensor_uart_UART_DEFAULT_INTR_I2C_EC_MASK;
        engine_sensor_uart_INTR_SPI_EC_MASK_REG = engine_sensor_uart_UART_DEFAULT_INTR_SPI_EC_MASK;
        engine_sensor_uart_INTR_SLAVE_MASK_REG  = engine_sensor_uart_UART_DEFAULT_INTR_SLAVE_MASK;
        engine_sensor_uart_INTR_MASTER_MASK_REG = engine_sensor_uart_UART_DEFAULT_INTR_MASTER_MASK;
        engine_sensor_uart_INTR_RX_MASK_REG     = engine_sensor_uart_UART_DEFAULT_INTR_RX_MASK;
        engine_sensor_uart_INTR_TX_MASK_REG     = engine_sensor_uart_UART_DEFAULT_INTR_TX_MASK;
    
        /* Configure TX interrupt sources to restore. */
        engine_sensor_uart_IntrTxMask = LO16(engine_sensor_uart_INTR_TX_MASK_REG);

    #if(engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST)
        engine_sensor_uart_rxBufferHead     = 0u;
        engine_sensor_uart_rxBufferTail     = 0u;
        engine_sensor_uart_rxBufferOverflow = 0u;
    #endif /* (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST)
        engine_sensor_uart_txBufferHead = 0u;
        engine_sensor_uart_txBufferTail = 0u;
    #endif /* (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: engine_sensor_uart_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void engine_sensor_uart_UartPostEnable(void)
{
#if (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (engine_sensor_uart_TX_SDA_MISO_PIN)
        if (engine_sensor_uart_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_TX_SDA_MISO_HSIOM_REG, engine_sensor_uart_TX_SDA_MISO_HSIOM_MASK,
                                           engine_sensor_uart_TX_SDA_MISO_HSIOM_POS, engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_UART);
        }
    #endif /* (engine_sensor_uart_TX_SDA_MISO_PIN_PIN) */

    #if !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
        #if (engine_sensor_uart_RTS_SS0_PIN)
            if (engine_sensor_uart_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_RTS_SS0_HSIOM_REG, engine_sensor_uart_RTS_SS0_HSIOM_MASK,
                                               engine_sensor_uart_RTS_SS0_HSIOM_POS, engine_sensor_uart_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (engine_sensor_uart_RTS_SS0_PIN) */
    #endif /* !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */

#else
    #if (engine_sensor_uart_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_TX_HSIOM_REG, engine_sensor_uart_TX_HSIOM_MASK,
                                       engine_sensor_uart_TX_HSIOM_POS, engine_sensor_uart_TX_HSIOM_SEL_UART);
    #endif /* (engine_sensor_uart_UART_TX_PIN) */

    #if (engine_sensor_uart_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_RTS_HSIOM_REG, engine_sensor_uart_RTS_HSIOM_MASK,
                                       engine_sensor_uart_RTS_HSIOM_POS, engine_sensor_uart_RTS_HSIOM_SEL_UART);
    #endif /* (engine_sensor_uart_UART_RTS_PIN) */
#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    engine_sensor_uart_SetTxInterruptMode(engine_sensor_uart_IntrTxMask);
}


/*******************************************************************************
* Function Name: engine_sensor_uart_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void engine_sensor_uart_UartStop(void)
{
#if(engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (engine_sensor_uart_TX_SDA_MISO_PIN)
        if (engine_sensor_uart_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_TX_SDA_MISO_HSIOM_REG, engine_sensor_uart_TX_SDA_MISO_HSIOM_MASK,
                                           engine_sensor_uart_TX_SDA_MISO_HSIOM_POS, engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (engine_sensor_uart_TX_SDA_MISO_PIN_PIN) */

    #if !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
        #if (engine_sensor_uart_RTS_SS0_PIN)
            if (engine_sensor_uart_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                engine_sensor_uart_uart_rts_spi_ss0_Write(engine_sensor_uart_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_RTS_SS0_HSIOM_REG, engine_sensor_uart_RTS_SS0_HSIOM_MASK,
                                               engine_sensor_uart_RTS_SS0_HSIOM_POS, engine_sensor_uart_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (engine_sensor_uart_RTS_SS0_PIN) */
    #endif /* !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */

#else
    #if (engine_sensor_uart_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_TX_HSIOM_REG, engine_sensor_uart_TX_HSIOM_MASK,
                                       engine_sensor_uart_TX_HSIOM_POS, engine_sensor_uart_TX_HSIOM_SEL_GPIO);
    #endif /* (engine_sensor_uart_UART_TX_PIN) */

    #if (engine_sensor_uart_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        engine_sensor_uart_rts_Write(engine_sensor_uart_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_RTS_HSIOM_REG, engine_sensor_uart_RTS_HSIOM_MASK,
                                       engine_sensor_uart_RTS_HSIOM_POS, engine_sensor_uart_RTS_HSIOM_SEL_GPIO);
    #endif /* (engine_sensor_uart_UART_RTS_PIN) */

#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (engine_sensor_uart_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    engine_sensor_uart_UART_RX_CTRL_REG &= (uint32) ~engine_sensor_uart_UART_RX_CTRL_SKIP_START;
#endif /* (engine_sensor_uart_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    engine_sensor_uart_IntrTxMask = LO16(engine_sensor_uart_GetTxInterruptMode() & engine_sensor_uart_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: engine_sensor_uart_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void engine_sensor_uart_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = engine_sensor_uart_RX_MATCH_REG;

    matchReg &= ((uint32) ~engine_sensor_uart_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & engine_sensor_uart_RX_MATCH_ADDR_MASK)); /* Set address  */

    engine_sensor_uart_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: engine_sensor_uart_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 � excludes bit from address comparison.
*   - Bit value 1 � the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void engine_sensor_uart_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = engine_sensor_uart_RX_MATCH_REG;

    matchReg &= ((uint32) ~engine_sensor_uart_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << engine_sensor_uart_RX_MATCH_MASK_POS));

    engine_sensor_uart_RX_MATCH_REG = matchReg;
}


#if(engine_sensor_uart_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: engine_sensor_uart_UartGetChar
    ****************************************************************************//**
    *
    *  Retrieves next data element from receive buffer.
    *  This function is designed for ASCII characters and returns a char where
    *  1 to 255 are valid characters and 0 indicates an error occurred or no data
    *  is present.
    *  - RX software buffer is disabled: Returns data element retrieved from RX
    *    FIFO.
    *  - RX software buffer is enabled: Returns data element from the software
    *    receive buffer.
    *
    *  \return
    *   Next data element from the receive buffer. ASCII character values from
    *   1 to 255 are valid. A returned zero signifies an error condition or no
    *   data available.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check engine_sensor_uart_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 engine_sensor_uart_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != engine_sensor_uart_SpiUartGetRxBufferSize())
        {
            rxData = engine_sensor_uart_SpiUartReadRxData();
        }

        if (engine_sensor_uart_CHECK_INTR_RX(engine_sensor_uart_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            engine_sensor_uart_ClearRxInterruptSource(engine_sensor_uart_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_UartGetByte
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer, returns the
    *  received byte and error condition.
    *   - The RX software buffer is disabled: returns the data element retrieved
    *     from the RX FIFO. Undefined data will be returned if the RX FIFO is
    *     empty.
    *   - The RX software buffer is enabled: returns data element from the
    *     software receive buffer.
    *
    *  \return
    *   Bits 7-0 contain the next data element from the receive buffer and
    *   other bits contain the error condition.
    *   - engine_sensor_uart_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - engine_sensor_uart_UART_RX_UNDERFLOW	Attempt to read from an empty
    *     receiver FIFO.
    *   - engine_sensor_uart_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - engine_sensor_uart_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check engine_sensor_uart_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 engine_sensor_uart_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (engine_sensor_uart_CHECK_RX_SW_BUFFER)
        {
            engine_sensor_uart_DisableInt();
        }
        #endif

        if (0u != engine_sensor_uart_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (engine_sensor_uart_CHECK_RX_SW_BUFFER)
            {
                engine_sensor_uart_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = engine_sensor_uart_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = engine_sensor_uart_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (engine_sensor_uart_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                engine_sensor_uart_ClearRxInterruptSource(engine_sensor_uart_INTR_RX_NOT_EMPTY);

                engine_sensor_uart_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (engine_sensor_uart_GetRxInterruptSource() & engine_sensor_uart_INTR_RX_ERR);
        engine_sensor_uart_ClearRxInterruptSource(engine_sensor_uart_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: engine_sensor_uart_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - engine_sensor_uart_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - engine_sensor_uart_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void engine_sensor_uart_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                engine_sensor_uart_UART_FLOW_CTRL_REG |= (uint32)  engine_sensor_uart_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                engine_sensor_uart_UART_FLOW_CTRL_REG &= (uint32) ~engine_sensor_uart_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: engine_sensor_uart_UartSetRtsFifoLevel
        ****************************************************************************//**
        *
        *  Sets level in the RX FIFO for RTS signal activation.
        *  While the RX FIFO has fewer entries than the RX FIFO level the RTS signal
        *  remains active, otherwise the RTS signal becomes inactive.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param level: Level in the RX FIFO for RTS signal activation.
        *   The range of valid level values is between 0 and RX FIFO depth - 1.
        *   Setting level value to 0 disables RTS signal activation.
        *
        *******************************************************************************/
        void engine_sensor_uart_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = engine_sensor_uart_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~engine_sensor_uart_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (engine_sensor_uart_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            engine_sensor_uart_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */

#endif /* (engine_sensor_uart_UART_RX_DIRECTION) */


#if(engine_sensor_uart_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: engine_sensor_uart_UartPutString
    ****************************************************************************//**
    *
    *  Places a NULL terminated string in the transmit buffer to be sent at the
    *  next available bus time.
    *  This function is blocking and waits until there is a space available to put
    *  requested data in transmit buffer.
    *
    *  \param string: pointer to the null terminated string array to be placed in the
    *   transmit buffer.
    *
    *******************************************************************************/
    void engine_sensor_uart_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            engine_sensor_uart_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_UartPutCRLF
    ****************************************************************************//**
    *
    *  Places byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) in the transmit buffer.
    *  This function is blocking and waits until there is a space available to put
    *  all requested data in transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *
    *******************************************************************************/
    void engine_sensor_uart_UartPutCRLF(uint32 txDataByte)
    {
        engine_sensor_uart_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        engine_sensor_uart_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        engine_sensor_uart_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: engine_sensor_uartSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void engine_sensor_uart_UartEnableCts(void)
        {
            engine_sensor_uart_UART_FLOW_CTRL_REG |= (uint32)  engine_sensor_uart_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: engine_sensor_uart_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void engine_sensor_uart_UartDisableCts(void)
        {
            engine_sensor_uart_UART_FLOW_CTRL_REG &= (uint32) ~engine_sensor_uart_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: engine_sensor_uart_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of CTS output signal.
        *   - engine_sensor_uart_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - engine_sensor_uart_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void engine_sensor_uart_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                engine_sensor_uart_UART_FLOW_CTRL_REG |= (uint32)  engine_sensor_uart_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                engine_sensor_uart_UART_FLOW_CTRL_REG &= (uint32) ~engine_sensor_uart_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */

#endif /* (engine_sensor_uart_UART_TX_DIRECTION) */


#if (engine_sensor_uart_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: engine_sensor_uart_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be 
    *  cleared by this API.
    *
    *******************************************************************************/
    void engine_sensor_uart_UartSaveConfig(void)
    {
    #if (engine_sensor_uart_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != engine_sensor_uart_skipStart)
        {
            engine_sensor_uart_UART_RX_CTRL_REG |= (uint32)  engine_sensor_uart_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            engine_sensor_uart_UART_RX_CTRL_REG &= (uint32) ~engine_sensor_uart_UART_RX_CTRL_SKIP_START;
        }
        
        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        engine_sensor_uart_CLEAR_UART_RX_WAKE_INTR;
        engine_sensor_uart_RxWakeClearPendingInt();
        engine_sensor_uart_RxWakeEnableInt();
    #endif /* (engine_sensor_uart_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void engine_sensor_uart_UartRestoreConfig(void)
    {
    #if (engine_sensor_uart_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        engine_sensor_uart_RxWakeDisableInt();
    #endif /* (engine_sensor_uart_UART_RX_WAKEUP_IRQ) */
    }


    #if (engine_sensor_uart_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: engine_sensor_uart_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(engine_sensor_uart_UART_WAKEUP_ISR)
        {
        #ifdef engine_sensor_uart_UART_WAKEUP_ISR_ENTRY_CALLBACK
            engine_sensor_uart_UART_WAKEUP_ISR_EntryCallback();
        #endif /* engine_sensor_uart_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            engine_sensor_uart_CLEAR_UART_RX_WAKE_INTR;

        #ifdef engine_sensor_uart_UART_WAKEUP_ISR_EXIT_CALLBACK
            engine_sensor_uart_UART_WAKEUP_ISR_ExitCallback();
        #endif /* engine_sensor_uart_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (engine_sensor_uart_UART_RX_WAKEUP_IRQ) */
#endif /* (engine_sensor_uart_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
