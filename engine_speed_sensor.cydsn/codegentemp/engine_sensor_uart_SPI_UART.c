/***************************************************************************//**
* \file engine_sensor_uart_SPI_UART.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
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

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 engine_sensor_uart_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 engine_sensor_uart_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  engine_sensor_uart_rxBufferOverflow;
    /** \} globals */
#endif /* (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST) */

#if(engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 engine_sensor_uart_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 engine_sensor_uart_txBufferTail;
#endif /* (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST) */

#if(engine_sensor_uart_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 engine_sensor_uart_rxBufferInternal[engine_sensor_uart_INTERNAL_RX_BUFFER_SIZE];
#endif /* (engine_sensor_uart_INTERNAL_RX_SW_BUFFER) */

#if(engine_sensor_uart_INTERNAL_TX_SW_BUFFER)
    volatile uint8 engine_sensor_uart_txBufferInternal[engine_sensor_uart_TX_BUFFER_SIZE];
#endif /* (engine_sensor_uart_INTERNAL_TX_SW_BUFFER) */


#if(engine_sensor_uart_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: engine_sensor_uart_SpiUartReadRxData
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * \return
    *  Next data element from the receive buffer. 
    *  The amount of data bits to be received depends on RX data bits selection 
    *  (the data bit counting starts from LSB of return value).
    *
    * \globalvars
    *  engine_sensor_uart_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  engine_sensor_uart_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 engine_sensor_uart_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (engine_sensor_uart_CHECK_RX_SW_BUFFER)
        {
            if (engine_sensor_uart_rxBufferHead != engine_sensor_uart_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (engine_sensor_uart_rxBufferTail + 1u);

                if (engine_sensor_uart_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = engine_sensor_uart_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                engine_sensor_uart_rxBufferTail = locTail;

                #if (engine_sensor_uart_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (engine_sensor_uart_INTR_RX_MASK_REG & engine_sensor_uart_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        engine_sensor_uart_INTR_RX_MASK_REG |= engine_sensor_uart_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = engine_sensor_uart_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_SpiUartGetRxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * \return
    *  Number of received data elements.
    *
    * \globalvars
    *  engine_sensor_uart_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  engine_sensor_uart_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 engine_sensor_uart_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (engine_sensor_uart_CHECK_RX_SW_BUFFER)
        {
            locHead = engine_sensor_uart_rxBufferHead;

            if(locHead >= engine_sensor_uart_rxBufferTail)
            {
                size = (locHead - engine_sensor_uart_rxBufferTail);
            }
            else
            {
                size = (locHead + (engine_sensor_uart_INTERNAL_RX_BUFFER_SIZE - engine_sensor_uart_rxBufferTail));
            }
        }
        #else
        {
            size = engine_sensor_uart_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  engine_sensor_uart_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  engine_sensor_uart_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void engine_sensor_uart_SpiUartClearRxBuffer(void)
    {
        #if (engine_sensor_uart_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            engine_sensor_uart_DisableInt();

            /* Flush RX software buffer */
            engine_sensor_uart_rxBufferHead = engine_sensor_uart_rxBufferTail;
            engine_sensor_uart_rxBufferOverflow = 0u;

            engine_sensor_uart_CLEAR_RX_FIFO;
            engine_sensor_uart_ClearRxInterruptSource(engine_sensor_uart_INTR_RX_ALL);

            #if (engine_sensor_uart_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                engine_sensor_uart_INTR_RX_MASK_REG |= engine_sensor_uart_INTR_RX_NOT_EMPTY;
            }
            #endif
            
            /* Release lock */
            engine_sensor_uart_EnableInt();
        }
        #else
        {
            engine_sensor_uart_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (engine_sensor_uart_RX_DIRECTION) */


#if(engine_sensor_uart_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: engine_sensor_uart_SpiUartWriteTxData
    ****************************************************************************//**
    *
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *   The amount of data bits to be transmitted depends on TX data bits selection 
    *   (the data bit counting starts from LSB of txDataByte).
    *
    * \globalvars
    *  engine_sensor_uart_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  engine_sensor_uart_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void engine_sensor_uart_SpiUartWriteTxData(uint32 txData)
    {
    #if (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (engine_sensor_uart_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((engine_sensor_uart_txBufferHead == engine_sensor_uart_txBufferTail) &&
                (engine_sensor_uart_SPI_UART_FIFO_SIZE != engine_sensor_uart_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                engine_sensor_uart_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (engine_sensor_uart_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (engine_sensor_uart_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == engine_sensor_uart_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                engine_sensor_uart_ClearTxInterruptSource(engine_sensor_uart_INTR_TX_NOT_FULL);

                engine_sensor_uart_PutWordInTxBuffer(locHead, txData);

                engine_sensor_uart_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (engine_sensor_uart_INTR_TX_MASK_REG & engine_sensor_uart_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    engine_sensor_uart_INTR_TX_MASK_REG |= (uint32) engine_sensor_uart_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (engine_sensor_uart_SPI_UART_FIFO_SIZE == engine_sensor_uart_GET_TX_FIFO_ENTRIES)
            {
            }

            engine_sensor_uart_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_SpiUartPutArray
    ****************************************************************************//**
    *
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * \param wrBuf: pointer to an array of data to be placed in transmit buffer. 
    *  The width of the data to be transmitted depends on TX data width selection 
    *  (the data bit counting starts from LSB for each array element).
    * \param count: number of data elements to be placed in the transmit buffer.
    *
    * \globalvars
    *  engine_sensor_uart_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  engine_sensor_uart_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void engine_sensor_uart_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            engine_sensor_uart_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_SpiUartGetTxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of elements currently in the transmit buffer.
    *   - TX software buffer is disabled: returns the number of used entries in
    *     TX FIFO.
    *   - TX software buffer is enabled: returns the number of elements currently
    *     used in the transmit buffer. This number does not include used entries in
    *     the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *     not full.
    *
    * \return
    *  Number of data elements ready to transmit.
    *
    * \globalvars
    *  engine_sensor_uart_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  engine_sensor_uart_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 engine_sensor_uart_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (engine_sensor_uart_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = engine_sensor_uart_txBufferTail;

            if (engine_sensor_uart_txBufferHead >= locTail)
            {
                size = (engine_sensor_uart_txBufferHead - locTail);
            }
            else
            {
                size = (engine_sensor_uart_txBufferHead + (engine_sensor_uart_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = engine_sensor_uart_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  engine_sensor_uart_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  engine_sensor_uart_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void engine_sensor_uart_SpiUartClearTxBuffer(void)
    {
        #if (engine_sensor_uart_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            engine_sensor_uart_DisableInt();

            /* Flush TX software buffer */
            engine_sensor_uart_txBufferHead = engine_sensor_uart_txBufferTail;

            engine_sensor_uart_INTR_TX_MASK_REG &= (uint32) ~engine_sensor_uart_INTR_TX_NOT_FULL;
            engine_sensor_uart_CLEAR_TX_FIFO;
            engine_sensor_uart_ClearTxInterruptSource(engine_sensor_uart_INTR_TX_ALL);

            /* Release lock */
            engine_sensor_uart_EnableInt();
        }
        #else
        {
            engine_sensor_uart_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (engine_sensor_uart_TX_DIRECTION) */


/*******************************************************************************
* Function Name: engine_sensor_uart_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 engine_sensor_uart_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = engine_sensor_uart_GetRxInterruptMode();

    engine_sensor_uart_SetRxInterruptMode(engine_sensor_uart_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: engine_sensor_uart_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 engine_sensor_uart_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = engine_sensor_uart_GetTxInterruptMode();

    engine_sensor_uart_SetTxInterruptMode(engine_sensor_uart_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: engine_sensor_uart_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void engine_sensor_uart_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (engine_sensor_uart_ONE_BYTE_WIDTH == engine_sensor_uart_rxDataBits)
        {
            engine_sensor_uart_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            engine_sensor_uart_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            engine_sensor_uart_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 engine_sensor_uart_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (engine_sensor_uart_ONE_BYTE_WIDTH == engine_sensor_uart_rxDataBits)
        {
            value = engine_sensor_uart_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) engine_sensor_uart_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)engine_sensor_uart_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void engine_sensor_uart_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (engine_sensor_uart_ONE_BYTE_WIDTH == engine_sensor_uart_txDataBits)
        {
            engine_sensor_uart_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            engine_sensor_uart_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            engine_sensor_uart_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: engine_sensor_uart_GetWordFromTxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx: index to get data byte/word from the TX buffer.
    *
    *  \return
    *   Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 engine_sensor_uart_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (engine_sensor_uart_ONE_BYTE_WIDTH == engine_sensor_uart_txDataBits)
        {
            value = (uint32) engine_sensor_uart_txBuffer[idx];
        }
        else
        {
            value  = (uint32) engine_sensor_uart_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) engine_sensor_uart_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
