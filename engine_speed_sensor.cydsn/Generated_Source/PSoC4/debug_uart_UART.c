/***************************************************************************//**
* \file debug_uart_UART.c
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

#include "debug_uart_PVT.h"
#include "debug_uart_SPI_UART_PVT.h"


#if (debug_uart_UART_WAKE_ENABLE_CONST && debug_uart_UART_RX_WAKEUP_IRQ)
    /**
    * \addtogroup group_globals
    * \{
    */
    /** This global variable determines whether to enable Skip Start
    * functionality when debug_uart_Sleep() function is called:
    * 0 – disable, other values – enable. Default value is 1.
    * It is only available when Enable wakeup from Deep Sleep Mode is enabled.
    */
    uint8 debug_uart_skipStart = 1u;
    /** \} globals */
#endif /* (debug_uart_UART_WAKE_ENABLE_CONST && debug_uart_UART_RX_WAKEUP_IRQ) */

#if(debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const debug_uart_UART_INIT_STRUCT debug_uart_configUart =
    {
        debug_uart_UART_SUB_MODE,
        debug_uart_UART_DIRECTION,
        debug_uart_UART_DATA_BITS_NUM,
        debug_uart_UART_PARITY_TYPE,
        debug_uart_UART_STOP_BITS_NUM,
        debug_uart_UART_OVS_FACTOR,
        debug_uart_UART_IRDA_LOW_POWER,
        debug_uart_UART_MEDIAN_FILTER_ENABLE,
        debug_uart_UART_RETRY_ON_NACK,
        debug_uart_UART_IRDA_POLARITY,
        debug_uart_UART_DROP_ON_PARITY_ERR,
        debug_uart_UART_DROP_ON_FRAME_ERR,
        debug_uart_UART_WAKE_ENABLE,
        0u,
        NULL,
        0u,
        NULL,
        debug_uart_UART_MP_MODE_ENABLE,
        debug_uart_UART_MP_ACCEPT_ADDRESS,
        debug_uart_UART_MP_RX_ADDRESS,
        debug_uart_UART_MP_RX_ADDRESS_MASK,
        (uint32) debug_uart_SCB_IRQ_INTERNAL,
        debug_uart_UART_INTR_RX_MASK,
        debug_uart_UART_RX_TRIGGER_LEVEL,
        debug_uart_UART_INTR_TX_MASK,
        debug_uart_UART_TX_TRIGGER_LEVEL,
        (uint8) debug_uart_UART_BYTE_MODE_ENABLE,
        (uint8) debug_uart_UART_CTS_ENABLE,
        (uint8) debug_uart_UART_CTS_POLARITY,
        (uint8) debug_uart_UART_RTS_POLARITY,
        (uint8) debug_uart_UART_RTS_FIFO_LEVEL
    };


    /*******************************************************************************
    * Function Name: debug_uart_UartInit
    ****************************************************************************//**
    *
    *  Configures the debug_uart for UART operation.
    *
    *  This function is intended specifically to be used when the debug_uart
    *  configuration is set to “Unconfigured debug_uart” in the customizer.
    *  After initializing the debug_uart in UART mode using this function,
    *  the component can be enabled using the debug_uart_Start() or
    * debug_uart_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration
    *  settings. This structure contains the same information that would otherwise
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of
    *   fields. These fields match the selections available in the customizer.
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void debug_uart_UartInit(const debug_uart_UART_INIT_STRUCT *config)
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

        #if !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
            /* Add RTS and CTS pins to configure */
            pinsConfig |= (0u != config->rtsRxFifoLevel) ? (debug_uart_UART_RTS_PIN_ENABLE) : (0u);
            pinsConfig |= (0u != config->enableCts)      ? (debug_uart_UART_CTS_PIN_ENABLE) : (0u);
        #endif /* !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */

            /* Configure pins */
            debug_uart_SetPins(debug_uart_SCB_MODE_UART, config->mode, pinsConfig);

            /* Store internal configuration */
            debug_uart_scbMode       = (uint8) debug_uart_SCB_MODE_UART;
            debug_uart_scbEnableWake = (uint8) config->enableWake;
            debug_uart_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            debug_uart_rxBuffer      =         config->rxBuffer;
            debug_uart_rxDataBits    = (uint8) config->dataBits;
            debug_uart_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            debug_uart_txBuffer      =         config->txBuffer;
            debug_uart_txDataBits    = (uint8) config->dataBits;
            debug_uart_txBufferSize  = (uint8) config->txBufferSize;

            /* Configure UART interface */
            if(debug_uart_UART_MODE_IRDA == config->mode)
            {
                /* OVS settings: IrDA */
                debug_uart_CTRL_REG  = ((0u != config->enableIrdaLowPower) ?
                                                (debug_uart_UART_GET_CTRL_OVS_IRDA_LP(config->oversample)) :
                                                (debug_uart_CTRL_OVS_IRDA_OVS16));
            }
            else
            {
                /* OVS settings: UART and SmartCard */
                debug_uart_CTRL_REG  = debug_uart_GET_CTRL_OVS(config->oversample);
            }

            debug_uart_CTRL_REG     |= debug_uart_GET_CTRL_BYTE_MODE  (config->enableByteMode)      |
                                             debug_uart_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr) |
                                             debug_uart_CTRL_UART;

            /* Configure sub-mode: UART, SmartCard or IrDA */
            debug_uart_UART_CTRL_REG = debug_uart_GET_UART_CTRL_MODE(config->mode);

            /* Configure RX direction */
            debug_uart_UART_RX_CTRL_REG = debug_uart_GET_UART_RX_CTRL_MODE(config->stopBits)              |
                                        debug_uart_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx)          |
                                        debug_uart_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc)            |
                                        debug_uart_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr) |
                                        debug_uart_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

            if(debug_uart_UART_PARITY_NONE != config->parity)
            {
               debug_uart_UART_RX_CTRL_REG |= debug_uart_GET_UART_RX_CTRL_PARITY(config->parity) |
                                                    debug_uart_UART_RX_CTRL_PARITY_ENABLED;
            }

            debug_uart_RX_CTRL_REG      = debug_uart_GET_RX_CTRL_DATA_WIDTH(config->dataBits)       |
                                                debug_uart_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                                debug_uart_GET_UART_RX_CTRL_ENABLED(config->direction);

            debug_uart_RX_FIFO_CTRL_REG = debug_uart_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure MP address */
            debug_uart_RX_MATCH_REG     = debug_uart_GET_RX_MATCH_ADDR(config->multiprocAddr) |
                                                debug_uart_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            /* Configure RX direction */
            debug_uart_UART_TX_CTRL_REG = debug_uart_GET_UART_TX_CTRL_MODE(config->stopBits) |
                                                debug_uart_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

            if(debug_uart_UART_PARITY_NONE != config->parity)
            {
               debug_uart_UART_TX_CTRL_REG |= debug_uart_GET_UART_TX_CTRL_PARITY(config->parity) |
                                                    debug_uart_UART_TX_CTRL_PARITY_ENABLED;
            }

            debug_uart_TX_CTRL_REG      = debug_uart_GET_TX_CTRL_DATA_WIDTH(config->dataBits)    |
                                                debug_uart_GET_UART_TX_CTRL_ENABLED(config->direction);

            debug_uart_TX_FIFO_CTRL_REG = debug_uart_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

        #if !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
            debug_uart_UART_FLOW_CTRL_REG = debug_uart_GET_UART_FLOW_CTRL_CTS_ENABLE(config->enableCts) | \
                                            debug_uart_GET_UART_FLOW_CTRL_CTS_POLARITY (config->ctsPolarity)  | \
                                            debug_uart_GET_UART_FLOW_CTRL_RTS_POLARITY (config->rtsPolarity)  | \
                                            debug_uart_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(config->rtsRxFifoLevel);
        #endif /* !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */

            /* Configure interrupt with UART handler but do not enable it */
            CyIntDisable    (debug_uart_ISR_NUMBER);
            CyIntSetPriority(debug_uart_ISR_NUMBER, debug_uart_ISR_PRIORITY);
            (void) CyIntSetVector(debug_uart_ISR_NUMBER, &debug_uart_SPI_UART_ISR);

            /* Configure WAKE interrupt */
        #if(debug_uart_UART_RX_WAKEUP_IRQ)
            CyIntDisable    (debug_uart_RX_WAKE_ISR_NUMBER);
            CyIntSetPriority(debug_uart_RX_WAKE_ISR_NUMBER, debug_uart_RX_WAKE_ISR_PRIORITY);
            (void) CyIntSetVector(debug_uart_RX_WAKE_ISR_NUMBER, &debug_uart_UART_WAKEUP_ISR);
        #endif /* (debug_uart_UART_RX_WAKEUP_IRQ) */

            /* Configure interrupt sources */
            debug_uart_INTR_I2C_EC_MASK_REG = debug_uart_NO_INTR_SOURCES;
            debug_uart_INTR_SPI_EC_MASK_REG = debug_uart_NO_INTR_SOURCES;
            debug_uart_INTR_SLAVE_MASK_REG  = debug_uart_NO_INTR_SOURCES;
            debug_uart_INTR_MASTER_MASK_REG = debug_uart_NO_INTR_SOURCES;
            debug_uart_INTR_RX_MASK_REG     = config->rxInterruptMask;
            debug_uart_INTR_TX_MASK_REG     = config->txInterruptMask;
        
            /* Configure TX interrupt sources to restore. */
            debug_uart_IntrTxMask = LO16(debug_uart_INTR_TX_MASK_REG);

            /* Clear RX buffer indexes */
            debug_uart_rxBufferHead     = 0u;
            debug_uart_rxBufferTail     = 0u;
            debug_uart_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            debug_uart_txBufferHead = 0u;
            debug_uart_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: debug_uart_UartInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the UART operation.
    *
    *******************************************************************************/
    void debug_uart_UartInit(void)
    {
        /* Configure UART interface */
        debug_uart_CTRL_REG = debug_uart_UART_DEFAULT_CTRL;

        /* Configure sub-mode: UART, SmartCard or IrDA */
        debug_uart_UART_CTRL_REG = debug_uart_UART_DEFAULT_UART_CTRL;

        /* Configure RX direction */
        debug_uart_UART_RX_CTRL_REG = debug_uart_UART_DEFAULT_UART_RX_CTRL;
        debug_uart_RX_CTRL_REG      = debug_uart_UART_DEFAULT_RX_CTRL;
        debug_uart_RX_FIFO_CTRL_REG = debug_uart_UART_DEFAULT_RX_FIFO_CTRL;
        debug_uart_RX_MATCH_REG     = debug_uart_UART_DEFAULT_RX_MATCH_REG;

        /* Configure TX direction */
        debug_uart_UART_TX_CTRL_REG = debug_uart_UART_DEFAULT_UART_TX_CTRL;
        debug_uart_TX_CTRL_REG      = debug_uart_UART_DEFAULT_TX_CTRL;
        debug_uart_TX_FIFO_CTRL_REG = debug_uart_UART_DEFAULT_TX_FIFO_CTRL;

    #if !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
        debug_uart_UART_FLOW_CTRL_REG = debug_uart_UART_DEFAULT_FLOW_CTRL;
    #endif /* !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */

        /* Configure interrupt with UART handler but do not enable it */
    #if(debug_uart_SCB_IRQ_INTERNAL)
        CyIntDisable    (debug_uart_ISR_NUMBER);
        CyIntSetPriority(debug_uart_ISR_NUMBER, debug_uart_ISR_PRIORITY);
        (void) CyIntSetVector(debug_uart_ISR_NUMBER, &debug_uart_SPI_UART_ISR);
    #endif /* (debug_uart_SCB_IRQ_INTERNAL) */

        /* Configure WAKE interrupt */
    #if(debug_uart_UART_RX_WAKEUP_IRQ)
        CyIntDisable    (debug_uart_RX_WAKE_ISR_NUMBER);
        CyIntSetPriority(debug_uart_RX_WAKE_ISR_NUMBER, debug_uart_RX_WAKE_ISR_PRIORITY);
        (void) CyIntSetVector(debug_uart_RX_WAKE_ISR_NUMBER, &debug_uart_UART_WAKEUP_ISR);
    #endif /* (debug_uart_UART_RX_WAKEUP_IRQ) */

        /* Configure interrupt sources */
        debug_uart_INTR_I2C_EC_MASK_REG = debug_uart_UART_DEFAULT_INTR_I2C_EC_MASK;
        debug_uart_INTR_SPI_EC_MASK_REG = debug_uart_UART_DEFAULT_INTR_SPI_EC_MASK;
        debug_uart_INTR_SLAVE_MASK_REG  = debug_uart_UART_DEFAULT_INTR_SLAVE_MASK;
        debug_uart_INTR_MASTER_MASK_REG = debug_uart_UART_DEFAULT_INTR_MASTER_MASK;
        debug_uart_INTR_RX_MASK_REG     = debug_uart_UART_DEFAULT_INTR_RX_MASK;
        debug_uart_INTR_TX_MASK_REG     = debug_uart_UART_DEFAULT_INTR_TX_MASK;
    
        /* Configure TX interrupt sources to restore. */
        debug_uart_IntrTxMask = LO16(debug_uart_INTR_TX_MASK_REG);

    #if(debug_uart_INTERNAL_RX_SW_BUFFER_CONST)
        debug_uart_rxBufferHead     = 0u;
        debug_uart_rxBufferTail     = 0u;
        debug_uart_rxBufferOverflow = 0u;
    #endif /* (debug_uart_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(debug_uart_INTERNAL_TX_SW_BUFFER_CONST)
        debug_uart_txBufferHead = 0u;
        debug_uart_txBufferTail = 0u;
    #endif /* (debug_uart_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: debug_uart_UartPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the UART output pins (TX and/or RTS) to be
*  controlled by the SCB UART.
*
*******************************************************************************/
void debug_uart_UartPostEnable(void)
{
#if (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (debug_uart_TX_SDA_MISO_PIN)
        if (debug_uart_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set SCB UART to drive the output pin */
            debug_uart_SET_HSIOM_SEL(debug_uart_TX_SDA_MISO_HSIOM_REG, debug_uart_TX_SDA_MISO_HSIOM_MASK,
                                           debug_uart_TX_SDA_MISO_HSIOM_POS, debug_uart_TX_SDA_MISO_HSIOM_SEL_UART);
        }
    #endif /* (debug_uart_TX_SDA_MISO_PIN_PIN) */

    #if !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
        #if (debug_uart_RTS_SS0_PIN)
            if (debug_uart_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set SCB UART to drive the output pin */
                debug_uart_SET_HSIOM_SEL(debug_uart_RTS_SS0_HSIOM_REG, debug_uart_RTS_SS0_HSIOM_MASK,
                                               debug_uart_RTS_SS0_HSIOM_POS, debug_uart_RTS_SS0_HSIOM_SEL_UART);
            }
        #endif /* (debug_uart_RTS_SS0_PIN) */
    #endif /* !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */

#else
    #if (debug_uart_UART_TX_PIN)
         /* Set SCB UART to drive the output pin */
        debug_uart_SET_HSIOM_SEL(debug_uart_TX_HSIOM_REG, debug_uart_TX_HSIOM_MASK,
                                       debug_uart_TX_HSIOM_POS, debug_uart_TX_HSIOM_SEL_UART);
    #endif /* (debug_uart_UART_TX_PIN) */

    #if (debug_uart_UART_RTS_PIN)
        /* Set SCB UART to drive the output pin */
        debug_uart_SET_HSIOM_SEL(debug_uart_RTS_HSIOM_REG, debug_uart_RTS_HSIOM_MASK,
                                       debug_uart_RTS_HSIOM_POS, debug_uart_RTS_HSIOM_SEL_UART);
    #endif /* (debug_uart_UART_RTS_PIN) */
#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    debug_uart_SetTxInterruptMode(debug_uart_IntrTxMask);
}


/*******************************************************************************
* Function Name: debug_uart_UartStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the UART output pins (TX and/or RTS) to keep
*  them inactive after the block is disabled. The output pins are controlled by
*  the GPIO data register. Also, the function disables the skip start feature
*  to not cause it to trigger after the component is enabled.
*
*******************************************************************************/
void debug_uart_UartStop(void)
{
#if(debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    #if (debug_uart_TX_SDA_MISO_PIN)
        if (debug_uart_CHECK_TX_SDA_MISO_PIN_USED)
        {
            /* Set GPIO to drive output pin */
            debug_uart_SET_HSIOM_SEL(debug_uart_TX_SDA_MISO_HSIOM_REG, debug_uart_TX_SDA_MISO_HSIOM_MASK,
                                           debug_uart_TX_SDA_MISO_HSIOM_POS, debug_uart_TX_SDA_MISO_HSIOM_SEL_GPIO);
        }
    #endif /* (debug_uart_TX_SDA_MISO_PIN_PIN) */

    #if !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
        #if (debug_uart_RTS_SS0_PIN)
            if (debug_uart_CHECK_RTS_SS0_PIN_USED)
            {
                /* Set output pin state after block is disabled */
                debug_uart_uart_rts_spi_ss0_Write(debug_uart_GET_UART_RTS_INACTIVE);

                /* Set GPIO to drive output pin */
                debug_uart_SET_HSIOM_SEL(debug_uart_RTS_SS0_HSIOM_REG, debug_uart_RTS_SS0_HSIOM_MASK,
                                               debug_uart_RTS_SS0_HSIOM_POS, debug_uart_RTS_SS0_HSIOM_SEL_GPIO);
            }
        #endif /* (debug_uart_RTS_SS0_PIN) */
    #endif /* !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */

#else
    #if (debug_uart_UART_TX_PIN)
        /* Set GPIO to drive output pin */
        debug_uart_SET_HSIOM_SEL(debug_uart_TX_HSIOM_REG, debug_uart_TX_HSIOM_MASK,
                                       debug_uart_TX_HSIOM_POS, debug_uart_TX_HSIOM_SEL_GPIO);
    #endif /* (debug_uart_UART_TX_PIN) */

    #if (debug_uart_UART_RTS_PIN)
        /* Set output pin state after block is disabled */
        debug_uart_rts_Write(debug_uart_GET_UART_RTS_INACTIVE);

        /* Set GPIO to drive output pin */
        debug_uart_SET_HSIOM_SEL(debug_uart_RTS_HSIOM_REG, debug_uart_RTS_HSIOM_MASK,
                                       debug_uart_RTS_HSIOM_POS, debug_uart_RTS_HSIOM_SEL_GPIO);
    #endif /* (debug_uart_UART_RTS_PIN) */

#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (debug_uart_UART_WAKE_ENABLE_CONST)
    /* Disable skip start feature used for wakeup */
    debug_uart_UART_RX_CTRL_REG &= (uint32) ~debug_uart_UART_RX_CTRL_SKIP_START;
#endif /* (debug_uart_UART_WAKE_ENABLE_CONST) */

    /* Store TX interrupt sources (exclude level triggered). */
    debug_uart_IntrTxMask = LO16(debug_uart_GetTxInterruptMode() & debug_uart_INTR_UART_TX_RESTORE);
}


/*******************************************************************************
* Function Name: debug_uart_UartSetRxAddress
****************************************************************************//**
*
*  Sets the hardware detectable receiver address for the UART in the
*  Multiprocessor mode.
*
*  \param address: Address for hardware address detection.
*
*******************************************************************************/
void debug_uart_UartSetRxAddress(uint32 address)
{
     uint32 matchReg;

    matchReg = debug_uart_RX_MATCH_REG;

    matchReg &= ((uint32) ~debug_uart_RX_MATCH_ADDR_MASK); /* Clear address bits */
    matchReg |= ((uint32)  (address & debug_uart_RX_MATCH_ADDR_MASK)); /* Set address  */

    debug_uart_RX_MATCH_REG = matchReg;
}


/*******************************************************************************
* Function Name: debug_uart_UartSetRxAddressMask
****************************************************************************//**
*
*  Sets the hardware address mask for the UART in the Multiprocessor mode.
*
*  \param addressMask: Address mask.
*   - Bit value 0 – excludes bit from address comparison.
*   - Bit value 1 – the bit needs to match with the corresponding bit
*     of the address.
*
*******************************************************************************/
void debug_uart_UartSetRxAddressMask(uint32 addressMask)
{
    uint32 matchReg;

    matchReg = debug_uart_RX_MATCH_REG;

    matchReg &= ((uint32) ~debug_uart_RX_MATCH_MASK_MASK); /* Clear address mask bits */
    matchReg |= ((uint32) (addressMask << debug_uart_RX_MATCH_MASK_POS));

    debug_uart_RX_MATCH_REG = matchReg;
}


#if(debug_uart_UART_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: debug_uart_UartGetChar
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
    *   Check debug_uart_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 debug_uart_UartGetChar(void)
    {
        uint32 rxData = 0u;

        /* Reads data only if there is data to read */
        if (0u != debug_uart_SpiUartGetRxBufferSize())
        {
            rxData = debug_uart_SpiUartReadRxData();
        }

        if (debug_uart_CHECK_INTR_RX(debug_uart_INTR_RX_ERR))
        {
            rxData = 0u; /* Error occurred: returns zero */
            debug_uart_ClearRxInterruptSource(debug_uart_INTR_RX_ERR);
        }

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: debug_uart_UartGetByte
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
    *   - debug_uart_UART_RX_OVERFLOW - Attempt to write to a full
    *     receiver FIFO.
    *   - debug_uart_UART_RX_UNDERFLOW	Attempt to read from an empty
    *     receiver FIFO.
    *   - debug_uart_UART_RX_FRAME_ERROR - UART framing error detected.
    *   - debug_uart_UART_RX_PARITY_ERROR - UART parity error detected.
    *
    *  \sideeffect
    *   The errors bits may not correspond with reading characters due to
    *   RX FIFO and software buffer usage.
    *   RX software buffer is enabled: The internal software buffer overflow
    *   is not treated as an error condition.
    *   Check debug_uart_rxBufferOverflow to capture that error condition.
    *
    *******************************************************************************/
    uint32 debug_uart_UartGetByte(void)
    {
        uint32 rxData;
        uint32 tmpStatus;

        #if (debug_uart_CHECK_RX_SW_BUFFER)
        {
            debug_uart_DisableInt();
        }
        #endif

        if (0u != debug_uart_SpiUartGetRxBufferSize())
        {
            /* Enables interrupt to receive more bytes: at least one byte is in
            * buffer.
            */
            #if (debug_uart_CHECK_RX_SW_BUFFER)
            {
                debug_uart_EnableInt();
            }
            #endif

            /* Get received byte */
            rxData = debug_uart_SpiUartReadRxData();
        }
        else
        {
            /* Reads a byte directly from RX FIFO: underflow is raised in the
            * case of empty. Otherwise the first received byte will be read.
            */
            rxData = debug_uart_RX_FIFO_RD_REG;


            /* Enables interrupt to receive more bytes. */
            #if (debug_uart_CHECK_RX_SW_BUFFER)
            {

                /* The byte has been read from RX FIFO. Clear RX interrupt to
                * not involve interrupt handler when RX FIFO is empty.
                */
                debug_uart_ClearRxInterruptSource(debug_uart_INTR_RX_NOT_EMPTY);

                debug_uart_EnableInt();
            }
            #endif
        }

        /* Get and clear RX error mask */
        tmpStatus = (debug_uart_GetRxInterruptSource() & debug_uart_INTR_RX_ERR);
        debug_uart_ClearRxInterruptSource(debug_uart_INTR_RX_ERR);

        /* Puts together data and error status:
        * MP mode and accept address: 9th bit is set to notify mark.
        */
        rxData |= ((uint32) (tmpStatus << 8u));

        return (rxData);
    }


    #if !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: debug_uart_UartSetRtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of RTS output signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of RTS output signal.
        *   - debug_uart_UART_RTS_ACTIVE_LOW  - RTS signal is active low.
        *   - debug_uart_UART_RTS_ACTIVE_HIGH - RTS signal is active high.
        *
        *******************************************************************************/
        void debug_uart_UartSetRtsPolarity(uint32 polarity)
        {
            if(0u != polarity)
            {
                debug_uart_UART_FLOW_CTRL_REG |= (uint32)  debug_uart_UART_FLOW_CTRL_RTS_POLARITY;
            }
            else
            {
                debug_uart_UART_FLOW_CTRL_REG &= (uint32) ~debug_uart_UART_FLOW_CTRL_RTS_POLARITY;
            }
        }


        /*******************************************************************************
        * Function Name: debug_uart_UartSetRtsFifoLevel
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
        void debug_uart_UartSetRtsFifoLevel(uint32 level)
        {
            uint32 uartFlowCtrl;

            uartFlowCtrl = debug_uart_UART_FLOW_CTRL_REG;

            uartFlowCtrl &= ((uint32) ~debug_uart_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
            uartFlowCtrl |= ((uint32) (debug_uart_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK & level));

            debug_uart_UART_FLOW_CTRL_REG = uartFlowCtrl;
        }
    #endif /* !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */

#endif /* (debug_uart_UART_RX_DIRECTION) */


#if(debug_uart_UART_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: debug_uart_UartPutString
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
    void debug_uart_UartPutString(const char8 string[])
    {
        uint32 bufIndex;

        bufIndex = 0u;

        /* Blocks the control flow until all data has been sent */
        while(string[bufIndex] != ((char8) 0))
        {
            debug_uart_UartPutChar((uint32) string[bufIndex]);
            bufIndex++;
        }
    }


    /*******************************************************************************
    * Function Name: debug_uart_UartPutCRLF
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
    void debug_uart_UartPutCRLF(uint32 txDataByte)
    {
        debug_uart_UartPutChar(txDataByte);  /* Blocks control flow until all data has been sent */
        debug_uart_UartPutChar(0x0Du);       /* Blocks control flow until all data has been sent */
        debug_uart_UartPutChar(0x0Au);       /* Blocks control flow until all data has been sent */
    }


    #if !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
        /*******************************************************************************
        * Function Name: debug_uartSCB_UartEnableCts
        ****************************************************************************//**
        *
        *  Enables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void debug_uart_UartEnableCts(void)
        {
            debug_uart_UART_FLOW_CTRL_REG |= (uint32)  debug_uart_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: debug_uart_UartDisableCts
        ****************************************************************************//**
        *
        *  Disables usage of CTS input signal by the UART transmitter.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *******************************************************************************/
        void debug_uart_UartDisableCts(void)
        {
            debug_uart_UART_FLOW_CTRL_REG &= (uint32) ~debug_uart_UART_FLOW_CTRL_CTS_ENABLE;
        }


        /*******************************************************************************
        * Function Name: debug_uart_UartSetCtsPolarity
        ****************************************************************************//**
        *
        *  Sets active polarity of CTS input signal.
        *  Only available for PSoC 4100 BLE / PSoC 4200 BLE / PSoC 4100M / PSoC 4200M /
        *  PSoC 4200L / PSoC 4000S / PSoC 4100S / PSoC Analog Coprocessor devices.
        *
        *  \param polarity: Active polarity of CTS output signal.
        *   - debug_uart_UART_CTS_ACTIVE_LOW  - CTS signal is active low.
        *   - debug_uart_UART_CTS_ACTIVE_HIGH - CTS signal is active high.
        *
        *******************************************************************************/
        void debug_uart_UartSetCtsPolarity(uint32 polarity)
        {
            if (0u != polarity)
            {
                debug_uart_UART_FLOW_CTRL_REG |= (uint32)  debug_uart_UART_FLOW_CTRL_CTS_POLARITY;
            }
            else
            {
                debug_uart_UART_FLOW_CTRL_REG &= (uint32) ~debug_uart_UART_FLOW_CTRL_CTS_POLARITY;
            }
        }
    #endif /* !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */

#endif /* (debug_uart_UART_TX_DIRECTION) */


#if (debug_uart_UART_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: debug_uart_UartSaveConfig
    ****************************************************************************//**
    *
    *  Clears and enables an interrupt on a falling edge of the Rx input. The GPIO
    *  interrupt does not track in the active mode, therefore requires to be 
    *  cleared by this API.
    *
    *******************************************************************************/
    void debug_uart_UartSaveConfig(void)
    {
    #if (debug_uart_UART_RX_WAKEUP_IRQ)
        /* Set SKIP_START if requested (set by default). */
        if (0u != debug_uart_skipStart)
        {
            debug_uart_UART_RX_CTRL_REG |= (uint32)  debug_uart_UART_RX_CTRL_SKIP_START;
        }
        else
        {
            debug_uart_UART_RX_CTRL_REG &= (uint32) ~debug_uart_UART_RX_CTRL_SKIP_START;
        }
        
        /* Clear RX GPIO interrupt status and pending interrupt in NVIC because
        * falling edge on RX line occurs while UART communication in active mode.
        * Enable interrupt: next interrupt trigger should wakeup device.
        */
        debug_uart_CLEAR_UART_RX_WAKE_INTR;
        debug_uart_RxWakeClearPendingInt();
        debug_uart_RxWakeEnableInt();
    #endif /* (debug_uart_UART_RX_WAKEUP_IRQ) */
    }


    /*******************************************************************************
    * Function Name: debug_uart_UartRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the RX GPIO interrupt. Until this function is called the interrupt
    *  remains active and triggers on every falling edge of the UART RX line.
    *
    *******************************************************************************/
    void debug_uart_UartRestoreConfig(void)
    {
    #if (debug_uart_UART_RX_WAKEUP_IRQ)
        /* Disable interrupt: no more triggers in active mode */
        debug_uart_RxWakeDisableInt();
    #endif /* (debug_uart_UART_RX_WAKEUP_IRQ) */
    }


    #if (debug_uart_UART_RX_WAKEUP_IRQ)
        /*******************************************************************************
        * Function Name: debug_uart_UART_WAKEUP_ISR
        ****************************************************************************//**
        *
        *  Handles the Interrupt Service Routine for the SCB UART mode GPIO wakeup
        *  event. This event is configured to trigger on a falling edge of the RX line.
        *
        *******************************************************************************/
        CY_ISR(debug_uart_UART_WAKEUP_ISR)
        {
        #ifdef debug_uart_UART_WAKEUP_ISR_ENTRY_CALLBACK
            debug_uart_UART_WAKEUP_ISR_EntryCallback();
        #endif /* debug_uart_UART_WAKEUP_ISR_ENTRY_CALLBACK */

            debug_uart_CLEAR_UART_RX_WAKE_INTR;

        #ifdef debug_uart_UART_WAKEUP_ISR_EXIT_CALLBACK
            debug_uart_UART_WAKEUP_ISR_ExitCallback();
        #endif /* debug_uart_UART_WAKEUP_ISR_EXIT_CALLBACK */
        }
    #endif /* (debug_uart_UART_RX_WAKEUP_IRQ) */
#endif /* (debug_uart_UART_RX_WAKEUP_IRQ) */


/* [] END OF FILE */
