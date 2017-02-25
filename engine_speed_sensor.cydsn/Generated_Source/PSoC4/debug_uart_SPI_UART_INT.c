/***************************************************************************//**
* \file debug_uart_SPI_UART_INT.c
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

#include "debug_uart_PVT.h"
#include "debug_uart_SPI_UART_PVT.h"


#if (debug_uart_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: debug_uart_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(debug_uart_SPI_UART_ISR)
{
#if (debug_uart_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (debug_uart_INTERNAL_RX_SW_BUFFER_CONST) */

#if (debug_uart_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (debug_uart_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef debug_uart_SPI_UART_ISR_ENTRY_CALLBACK
    debug_uart_SPI_UART_ISR_EntryCallback();
#endif /* debug_uart_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != debug_uart_customIntrHandler)
    {
        debug_uart_customIntrHandler();
    }

    #if(debug_uart_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        debug_uart_ClearSpiExtClkInterruptSource(debug_uart_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (debug_uart_CHECK_RX_SW_BUFFER)
    {
        if (debug_uart_CHECK_INTR_RX_MASKED(debug_uart_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (debug_uart_rxBufferHead + 1u);

                /* Adjust local head index */
                if (debug_uart_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == debug_uart_rxBufferTail)
                {
                    #if (debug_uart_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        debug_uart_INTR_RX_MASK_REG &= ~debug_uart_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) debug_uart_RX_FIFO_RD_REG;
                        debug_uart_rxBufferOverflow = (uint8) debug_uart_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    debug_uart_PutWordInRxBuffer(locHead, debug_uart_RX_FIFO_RD_REG);

                    /* Move head index */
                    debug_uart_rxBufferHead = locHead;
                }
            }
            while(0u != debug_uart_GET_RX_FIFO_ENTRIES);

            debug_uart_ClearRxInterruptSource(debug_uart_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (debug_uart_CHECK_TX_SW_BUFFER)
    {
        if (debug_uart_CHECK_INTR_TX_MASKED(debug_uart_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (debug_uart_txBufferHead != debug_uart_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (debug_uart_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (debug_uart_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    debug_uart_TX_FIFO_WR_REG = debug_uart_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    debug_uart_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    debug_uart_DISABLE_INTR_TX(debug_uart_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (debug_uart_SPI_UART_FIFO_SIZE != debug_uart_GET_TX_FIFO_ENTRIES);

            debug_uart_ClearTxInterruptSource(debug_uart_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef debug_uart_SPI_UART_ISR_EXIT_CALLBACK
    debug_uart_SPI_UART_ISR_ExitCallback();
#endif /* debug_uart_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (debug_uart_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
