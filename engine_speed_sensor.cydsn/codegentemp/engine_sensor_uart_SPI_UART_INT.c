/***************************************************************************//**
* \file engine_sensor_uart_SPI_UART_INT.c
* \version 3.20
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
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

#include "engine_sensor_uart_PVT.h"
#include "engine_sensor_uart_SPI_UART_PVT.h"


#if (engine_sensor_uart_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: engine_sensor_uart_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(engine_sensor_uart_SPI_UART_ISR)
{
#if (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (engine_sensor_uart_INTERNAL_RX_SW_BUFFER_CONST) */

#if (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (engine_sensor_uart_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef engine_sensor_uart_SPI_UART_ISR_ENTRY_CALLBACK
    engine_sensor_uart_SPI_UART_ISR_EntryCallback();
#endif /* engine_sensor_uart_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != engine_sensor_uart_customIntrHandler)
    {
        engine_sensor_uart_customIntrHandler();
    }

    #if(engine_sensor_uart_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        engine_sensor_uart_ClearSpiExtClkInterruptSource(engine_sensor_uart_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (engine_sensor_uart_CHECK_RX_SW_BUFFER)
    {
        if (engine_sensor_uart_CHECK_INTR_RX_MASKED(engine_sensor_uart_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (engine_sensor_uart_rxBufferHead + 1u);

                /* Adjust local head index */
                if (engine_sensor_uart_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == engine_sensor_uart_rxBufferTail)
                {
                    #if (engine_sensor_uart_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        engine_sensor_uart_INTR_RX_MASK_REG &= ~engine_sensor_uart_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) engine_sensor_uart_RX_FIFO_RD_REG;
                        engine_sensor_uart_rxBufferOverflow = (uint8) engine_sensor_uart_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    engine_sensor_uart_PutWordInRxBuffer(locHead, engine_sensor_uart_RX_FIFO_RD_REG);

                    /* Move head index */
                    engine_sensor_uart_rxBufferHead = locHead;
                }
            }
            while(0u != engine_sensor_uart_GET_RX_FIFO_ENTRIES);

            engine_sensor_uart_ClearRxInterruptSource(engine_sensor_uart_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (engine_sensor_uart_CHECK_TX_SW_BUFFER)
    {
        if (engine_sensor_uart_CHECK_INTR_TX_MASKED(engine_sensor_uart_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (engine_sensor_uart_txBufferHead != engine_sensor_uart_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (engine_sensor_uart_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (engine_sensor_uart_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    engine_sensor_uart_TX_FIFO_WR_REG = engine_sensor_uart_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    engine_sensor_uart_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    engine_sensor_uart_DISABLE_INTR_TX(engine_sensor_uart_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (engine_sensor_uart_SPI_UART_FIFO_SIZE != engine_sensor_uart_GET_TX_FIFO_ENTRIES);

            engine_sensor_uart_ClearTxInterruptSource(engine_sensor_uart_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef engine_sensor_uart_SPI_UART_ISR_EXIT_CALLBACK
    engine_sensor_uart_SPI_UART_ISR_ExitCallback();
#endif /* engine_sensor_uart_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (engine_sensor_uart_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
