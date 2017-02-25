/***************************************************************************//**
* \file debug_uart.c
* \version 3.20
*
* \brief
*  This file provides the source code to the API for the SCB Component.
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

#if (debug_uart_SCB_MODE_I2C_INC)
    #include "debug_uart_I2C_PVT.h"
#endif /* (debug_uart_SCB_MODE_I2C_INC) */

#if (debug_uart_SCB_MODE_EZI2C_INC)
    #include "debug_uart_EZI2C_PVT.h"
#endif /* (debug_uart_SCB_MODE_EZI2C_INC) */

#if (debug_uart_SCB_MODE_SPI_INC || debug_uart_SCB_MODE_UART_INC)
    #include "debug_uart_SPI_UART_PVT.h"
#endif /* (debug_uart_SCB_MODE_SPI_INC || debug_uart_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 debug_uart_scbMode = debug_uart_SCB_MODE_UNCONFIG;
    uint8 debug_uart_scbEnableWake;
    uint8 debug_uart_scbEnableIntr;

    /* I2C configuration variables */
    uint8 debug_uart_mode;
    uint8 debug_uart_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * debug_uart_rxBuffer;
    uint8  debug_uart_rxDataBits;
    uint32 debug_uart_rxBufferSize;

    volatile uint8 * debug_uart_txBuffer;
    uint8  debug_uart_txDataBits;
    uint32 debug_uart_txBufferSize;

    /* EZI2C configuration variables */
    uint8 debug_uart_numberOfAddr;
    uint8 debug_uart_subAddrSize;
#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** debug_uart_initVar indicates whether the debug_uart 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the debug_uart_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  debug_uart_Init() function can be called before the 
*  debug_uart_Start() or debug_uart_Enable() function.
*/
uint8 debug_uart_initVar = 0u;


#if (! (debug_uart_SCB_MODE_I2C_CONST_CFG || \
        debug_uart_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * debug_uart_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent debug_uart_Enable() call.
    */
    uint16 debug_uart_IntrTxMask = 0u;
#endif /* (! (debug_uart_SCB_MODE_I2C_CONST_CFG || \
              debug_uart_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (debug_uart_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_debug_uart_CUSTOM_INTR_HANDLER)
    void (*debug_uart_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_debug_uart_CUSTOM_INTR_HANDLER) */
#endif /* (debug_uart_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void debug_uart_ScbEnableIntr(void);
static void debug_uart_ScbModeStop(void);
static void debug_uart_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: debug_uart_Init
****************************************************************************//**
*
*  Initializes the debug_uart component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  debug_uart_I2CInit, debug_uart_SpiInit, 
*  debug_uart_UartInit or debug_uart_EzI2CInit.
*
*******************************************************************************/
void debug_uart_Init(void)
{
#if (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    if (debug_uart_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        debug_uart_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (debug_uart_SCB_MODE_I2C_CONST_CFG)
    debug_uart_I2CInit();

#elif (debug_uart_SCB_MODE_SPI_CONST_CFG)
    debug_uart_SpiInit();

#elif (debug_uart_SCB_MODE_UART_CONST_CFG)
    debug_uart_UartInit();

#elif (debug_uart_SCB_MODE_EZI2C_CONST_CFG)
    debug_uart_EzI2CInit();

#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: debug_uart_Enable
****************************************************************************//**
*
*  Enables debug_uart component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  debug_uart_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The debug_uart configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured debug_uart”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void debug_uart_Enable(void)
{
#if (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!debug_uart_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        debug_uart_CTRL_REG |= debug_uart_CTRL_ENABLED;

        debug_uart_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        debug_uart_ScbModePostEnable();
    }
#else
    debug_uart_CTRL_REG |= debug_uart_CTRL_ENABLED;

    debug_uart_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    debug_uart_ScbModePostEnable();
#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: debug_uart_Start
****************************************************************************//**
*
*  Invokes debug_uart_Init() and debug_uart_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  debug_uart_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void debug_uart_Start(void)
{
    if (0u == debug_uart_initVar)
    {
        debug_uart_Init();
        debug_uart_initVar = 1u; /* Component was initialized */
    }

    debug_uart_Enable();
}


/*******************************************************************************
* Function Name: debug_uart_Stop
****************************************************************************//**
*
*  Disables the debug_uart component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function debug_uart_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void debug_uart_Stop(void)
{
#if (debug_uart_SCB_IRQ_INTERNAL)
    debug_uart_DisableInt();
#endif /* (debug_uart_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    debug_uart_ScbModeStop();

    /* Disable SCB IP */
    debug_uart_CTRL_REG &= (uint32) ~debug_uart_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    debug_uart_SetTxInterruptMode(debug_uart_NO_INTR_SOURCES);

#if (debug_uart_SCB_IRQ_INTERNAL)
    debug_uart_ClearPendingInt();
#endif /* (debug_uart_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: debug_uart_SetRxFifoLevel
****************************************************************************//**
*
*  Sets level in the RX FIFO to generate a RX level interrupt.
*  When the RX FIFO has more entries than the RX FIFO level an RX level
*  interrupt request is generated.
*
*  \param level: Level in the RX FIFO to generate RX level interrupt.
*   The range of valid level values is between 0 and RX FIFO depth - 1.
*
*******************************************************************************/
void debug_uart_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = debug_uart_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~debug_uart_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (debug_uart_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    debug_uart_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: debug_uart_SetTxFifoLevel
****************************************************************************//**
*
*  Sets level in the TX FIFO to generate a TX level interrupt.
*  When the TX FIFO has less entries than the TX FIFO level an TX level
*  interrupt request is generated.
*
*  \param level: Level in the TX FIFO to generate TX level interrupt.
*   The range of valid level values is between 0 and TX FIFO depth - 1.
*
*******************************************************************************/
void debug_uart_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = debug_uart_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~debug_uart_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (debug_uart_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    debug_uart_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (debug_uart_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: debug_uart_SetCustomInterruptHandler
    ****************************************************************************//**
    *
    *  Registers a function to be called by the internal interrupt handler.
    *  First the function that is registered is called, then the internal interrupt
    *  handler performs any operation such as software buffer management functions
    *  before the interrupt returns.  It is the user's responsibility not to break
    *  the software buffer operations. Only one custom handler is supported, which
    *  is the function provided by the most recent call.
    *  At the initialization time no custom handler is registered.
    *
    *  \param func: Pointer to the function to register.
    *        The value NULL indicates to remove the current custom interrupt
    *        handler.
    *
    *******************************************************************************/
    void debug_uart_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_debug_uart_CUSTOM_INTR_HANDLER)
        debug_uart_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_debug_uart_CUSTOM_INTR_HANDLER) */
    }
#endif /* (debug_uart_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: debug_uart_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void debug_uart_ScbEnableIntr(void)
{
#if (debug_uart_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != debug_uart_scbEnableIntr)
        {
            debug_uart_EnableInt();
        }

    #else
        debug_uart_EnableInt();

    #endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (debug_uart_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: debug_uart_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void debug_uart_ScbModePostEnable(void)
{
#if (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!debug_uart_CY_SCBIP_V1)
    if (debug_uart_SCB_MODE_SPI_RUNTM_CFG)
    {
        debug_uart_SpiPostEnable();
    }
    else if (debug_uart_SCB_MODE_UART_RUNTM_CFG)
    {
        debug_uart_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!debug_uart_CY_SCBIP_V1) */

#elif (debug_uart_SCB_MODE_SPI_CONST_CFG)
    debug_uart_SpiPostEnable();

#elif (debug_uart_SCB_MODE_UART_CONST_CFG)
    debug_uart_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: debug_uart_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void debug_uart_ScbModeStop(void)
{
#if (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    if (debug_uart_SCB_MODE_I2C_RUNTM_CFG)
    {
        debug_uart_I2CStop();
    }
    else if (debug_uart_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        debug_uart_EzI2CStop();
    }
#if (!debug_uart_CY_SCBIP_V1)
    else if (debug_uart_SCB_MODE_SPI_RUNTM_CFG)
    {
        debug_uart_SpiStop();
    }
    else if (debug_uart_SCB_MODE_UART_RUNTM_CFG)
    {
        debug_uart_UartStop();
    }
#endif /* (!debug_uart_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (debug_uart_SCB_MODE_I2C_CONST_CFG)
    debug_uart_I2CStop();

#elif (debug_uart_SCB_MODE_EZI2C_CONST_CFG)
    debug_uart_EzI2CStop();

#elif (debug_uart_SCB_MODE_SPI_CONST_CFG)
    debug_uart_SpiStop();

#elif (debug_uart_SCB_MODE_UART_CONST_CFG)
    debug_uart_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: debug_uart_SetPins
    ****************************************************************************//**
    *
    *  Sets the pins settings accordingly to the selected operation mode.
    *  Only available in the Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when a specific mode of operation
    *  is selected in design time.
    *
    *  \param mode:      Mode of SCB operation.
    *  \param subMode:   Sub-mode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  \param uartEnableMask: enables TX or RX direction and RTS and CTS signals.
    *
    *******************************************************************************/
    void debug_uart_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[debug_uart_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!debug_uart_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!debug_uart_CY_SCBIP_V1) */
        
        uint32 hsiomSel[debug_uart_SCB_PINS_NUMBER] = 
        {
            debug_uart_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            debug_uart_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (debug_uart_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (debug_uart_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < debug_uart_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = debug_uart_PIN_DM_ALG_HIZ;
        }

        if ((debug_uart_SCB_MODE_I2C   == mode) ||
            (debug_uart_SCB_MODE_EZI2C == mode))
        {
        #if (debug_uart_RX_SCL_MOSI_PIN)
            hsiomSel[debug_uart_RX_SCL_MOSI_PIN_INDEX] = debug_uart_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [debug_uart_RX_SCL_MOSI_PIN_INDEX] = debug_uart_PIN_DM_OD_LO;
        #elif (debug_uart_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = debug_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = debug_uart_PIN_DM_OD_LO;
        #else
        #endif /* (debug_uart_RX_SCL_MOSI_PIN) */
        
        #if (debug_uart_TX_SDA_MISO_PIN)
            hsiomSel[debug_uart_TX_SDA_MISO_PIN_INDEX] = debug_uart_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [debug_uart_TX_SDA_MISO_PIN_INDEX] = debug_uart_PIN_DM_OD_LO;
        #endif /* (debug_uart_TX_SDA_MISO_PIN) */
        }
    #if (!debug_uart_CY_SCBIP_V1)
        else if (debug_uart_SCB_MODE_SPI == mode)
        {
        #if (debug_uart_RX_SCL_MOSI_PIN)
            hsiomSel[debug_uart_RX_SCL_MOSI_PIN_INDEX] = debug_uart_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (debug_uart_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = debug_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (debug_uart_RX_SCL_MOSI_PIN) */
        
        #if (debug_uart_TX_SDA_MISO_PIN)
            hsiomSel[debug_uart_TX_SDA_MISO_PIN_INDEX] = debug_uart_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (debug_uart_TX_SDA_MISO_PIN) */
        
        #if (debug_uart_CTS_SCLK_PIN)
            hsiomSel[debug_uart_CTS_SCLK_PIN_INDEX] = debug_uart_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (debug_uart_CTS_SCLK_PIN) */

            if (debug_uart_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[debug_uart_RX_SCL_MOSI_PIN_INDEX] = debug_uart_PIN_DM_DIG_HIZ;
                pinsDm[debug_uart_TX_SDA_MISO_PIN_INDEX] = debug_uart_PIN_DM_STRONG;
                pinsDm[debug_uart_CTS_SCLK_PIN_INDEX] = debug_uart_PIN_DM_DIG_HIZ;

            #if (debug_uart_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[debug_uart_RTS_SS0_PIN_INDEX] = debug_uart_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [debug_uart_RTS_SS0_PIN_INDEX] = debug_uart_PIN_DM_DIG_HIZ;
            #endif /* (debug_uart_RTS_SS0_PIN) */

            #if (debug_uart_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= debug_uart_TX_SDA_MISO_PIN_MASK;
            #endif /* (debug_uart_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[debug_uart_RX_SCL_MOSI_PIN_INDEX] = debug_uart_PIN_DM_STRONG;
                pinsDm[debug_uart_TX_SDA_MISO_PIN_INDEX] = debug_uart_PIN_DM_DIG_HIZ;
                pinsDm[debug_uart_CTS_SCLK_PIN_INDEX] = debug_uart_PIN_DM_STRONG;

            #if (debug_uart_RTS_SS0_PIN)
                hsiomSel [debug_uart_RTS_SS0_PIN_INDEX] = debug_uart_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [debug_uart_RTS_SS0_PIN_INDEX] = debug_uart_PIN_DM_STRONG;
                pinsInBuf |= debug_uart_RTS_SS0_PIN_MASK;
            #endif /* (debug_uart_RTS_SS0_PIN) */

            #if (debug_uart_SS1_PIN)
                hsiomSel [debug_uart_SS1_PIN_INDEX] = debug_uart_SS1_HSIOM_SEL_SPI;
                pinsDm   [debug_uart_SS1_PIN_INDEX] = debug_uart_PIN_DM_STRONG;
                pinsInBuf |= debug_uart_SS1_PIN_MASK;
            #endif /* (debug_uart_SS1_PIN) */

            #if (debug_uart_SS2_PIN)
                hsiomSel [debug_uart_SS2_PIN_INDEX] = debug_uart_SS2_HSIOM_SEL_SPI;
                pinsDm   [debug_uart_SS2_PIN_INDEX] = debug_uart_PIN_DM_STRONG;
                pinsInBuf |= debug_uart_SS2_PIN_MASK;
            #endif /* (debug_uart_SS2_PIN) */

            #if (debug_uart_SS3_PIN)
                hsiomSel [debug_uart_SS3_PIN_INDEX] = debug_uart_SS3_HSIOM_SEL_SPI;
                pinsDm   [debug_uart_SS3_PIN_INDEX] = debug_uart_PIN_DM_STRONG;
                pinsInBuf |= debug_uart_SS3_PIN_MASK;
            #endif /* (debug_uart_SS3_PIN) */

                /* Disable input buffers */
            #if (debug_uart_RX_SCL_MOSI_PIN)
                pinsInBuf |= debug_uart_RX_SCL_MOSI_PIN_MASK;
            #elif (debug_uart_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= debug_uart_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (debug_uart_RX_SCL_MOSI_PIN) */

            #if (debug_uart_CTS_SCLK_PIN)
                pinsInBuf |= debug_uart_CTS_SCLK_PIN_MASK;
            #endif /* (debug_uart_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (debug_uart_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (debug_uart_TX_SDA_MISO_PIN)
                hsiomSel[debug_uart_TX_SDA_MISO_PIN_INDEX] = debug_uart_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [debug_uart_TX_SDA_MISO_PIN_INDEX] = debug_uart_PIN_DM_OD_LO;
            #endif /* (debug_uart_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (debug_uart_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (debug_uart_RX_SCL_MOSI_PIN)
                    hsiomSel[debug_uart_RX_SCL_MOSI_PIN_INDEX] = debug_uart_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [debug_uart_RX_SCL_MOSI_PIN_INDEX] = debug_uart_PIN_DM_DIG_HIZ;
                #elif (debug_uart_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = debug_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = debug_uart_PIN_DM_DIG_HIZ;
                #else
                #endif /* (debug_uart_RX_SCL_MOSI_PIN) */
                }

                if (0u != (debug_uart_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (debug_uart_TX_SDA_MISO_PIN)
                    hsiomSel[debug_uart_TX_SDA_MISO_PIN_INDEX] = debug_uart_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [debug_uart_TX_SDA_MISO_PIN_INDEX] = debug_uart_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= debug_uart_TX_SDA_MISO_PIN_MASK;
                #endif /* (debug_uart_TX_SDA_MISO_PIN) */
                }

            #if !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
                if (debug_uart_UART_MODE_STD == subMode)
                {
                    if (0u != (debug_uart_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (debug_uart_CTS_SCLK_PIN)
                        hsiomSel[debug_uart_CTS_SCLK_PIN_INDEX] = debug_uart_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [debug_uart_CTS_SCLK_PIN_INDEX] = debug_uart_PIN_DM_DIG_HIZ;
                    #endif /* (debug_uart_CTS_SCLK_PIN) */
                    }

                    if (0u != (debug_uart_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (debug_uart_RTS_SS0_PIN)
                        hsiomSel[debug_uart_RTS_SS0_PIN_INDEX] = debug_uart_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [debug_uart_RTS_SS0_PIN_INDEX] = debug_uart_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= debug_uart_RTS_SS0_PIN_MASK;
                    #endif /* (debug_uart_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */
            }
        }
    #endif /* (!debug_uart_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (debug_uart_RX_SCL_MOSI_PIN)
        debug_uart_SET_HSIOM_SEL(debug_uart_RX_SCL_MOSI_HSIOM_REG,
                                       debug_uart_RX_SCL_MOSI_HSIOM_MASK,
                                       debug_uart_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[debug_uart_RX_SCL_MOSI_PIN_INDEX]);

        debug_uart_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[debug_uart_RX_SCL_MOSI_PIN_INDEX]);

        #if (!debug_uart_CY_SCBIP_V1)
            debug_uart_SET_INP_DIS(debug_uart_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         debug_uart_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & debug_uart_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!debug_uart_CY_SCBIP_V1) */
    
    #elif (debug_uart_RX_WAKE_SCL_MOSI_PIN)
        debug_uart_SET_HSIOM_SEL(debug_uart_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       debug_uart_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       debug_uart_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        debug_uart_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[debug_uart_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        debug_uart_SET_INP_DIS(debug_uart_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     debug_uart_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & debug_uart_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        debug_uart_SET_INCFG_TYPE(debug_uart_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        debug_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        debug_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        debug_uart_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (debug_uart_RX_WAKE_SCL_MOSI_PIN) */

    #if (debug_uart_TX_SDA_MISO_PIN)
        debug_uart_SET_HSIOM_SEL(debug_uart_TX_SDA_MISO_HSIOM_REG,
                                       debug_uart_TX_SDA_MISO_HSIOM_MASK,
                                       debug_uart_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[debug_uart_TX_SDA_MISO_PIN_INDEX]);

        debug_uart_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[debug_uart_TX_SDA_MISO_PIN_INDEX]);

    #if (!debug_uart_CY_SCBIP_V1)
        debug_uart_SET_INP_DIS(debug_uart_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     debug_uart_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & debug_uart_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!debug_uart_CY_SCBIP_V1) */
    #endif /* (debug_uart_RX_SCL_MOSI_PIN) */

    #if (debug_uart_CTS_SCLK_PIN)
        debug_uart_SET_HSIOM_SEL(debug_uart_CTS_SCLK_HSIOM_REG,
                                       debug_uart_CTS_SCLK_HSIOM_MASK,
                                       debug_uart_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[debug_uart_CTS_SCLK_PIN_INDEX]);

        debug_uart_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[debug_uart_CTS_SCLK_PIN_INDEX]);

        debug_uart_SET_INP_DIS(debug_uart_uart_cts_spi_sclk_INP_DIS,
                                     debug_uart_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & debug_uart_CTS_SCLK_PIN_MASK)));
    #endif /* (debug_uart_CTS_SCLK_PIN) */

    #if (debug_uart_RTS_SS0_PIN)
        debug_uart_SET_HSIOM_SEL(debug_uart_RTS_SS0_HSIOM_REG,
                                       debug_uart_RTS_SS0_HSIOM_MASK,
                                       debug_uart_RTS_SS0_HSIOM_POS,
                                       hsiomSel[debug_uart_RTS_SS0_PIN_INDEX]);

        debug_uart_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[debug_uart_RTS_SS0_PIN_INDEX]);

        debug_uart_SET_INP_DIS(debug_uart_uart_rts_spi_ss0_INP_DIS,
                                     debug_uart_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & debug_uart_RTS_SS0_PIN_MASK)));
    #endif /* (debug_uart_RTS_SS0_PIN) */

    #if (debug_uart_SS1_PIN)
        debug_uart_SET_HSIOM_SEL(debug_uart_SS1_HSIOM_REG,
                                       debug_uart_SS1_HSIOM_MASK,
                                       debug_uart_SS1_HSIOM_POS,
                                       hsiomSel[debug_uart_SS1_PIN_INDEX]);

        debug_uart_spi_ss1_SetDriveMode((uint8) pinsDm[debug_uart_SS1_PIN_INDEX]);

        debug_uart_SET_INP_DIS(debug_uart_spi_ss1_INP_DIS,
                                     debug_uart_spi_ss1_MASK,
                                     (0u != (pinsInBuf & debug_uart_SS1_PIN_MASK)));
    #endif /* (debug_uart_SS1_PIN) */

    #if (debug_uart_SS2_PIN)
        debug_uart_SET_HSIOM_SEL(debug_uart_SS2_HSIOM_REG,
                                       debug_uart_SS2_HSIOM_MASK,
                                       debug_uart_SS2_HSIOM_POS,
                                       hsiomSel[debug_uart_SS2_PIN_INDEX]);

        debug_uart_spi_ss2_SetDriveMode((uint8) pinsDm[debug_uart_SS2_PIN_INDEX]);

        debug_uart_SET_INP_DIS(debug_uart_spi_ss2_INP_DIS,
                                     debug_uart_spi_ss2_MASK,
                                     (0u != (pinsInBuf & debug_uart_SS2_PIN_MASK)));
    #endif /* (debug_uart_SS2_PIN) */

    #if (debug_uart_SS3_PIN)
        debug_uart_SET_HSIOM_SEL(debug_uart_SS3_HSIOM_REG,
                                       debug_uart_SS3_HSIOM_MASK,
                                       debug_uart_SS3_HSIOM_POS,
                                       hsiomSel[debug_uart_SS3_PIN_INDEX]);

        debug_uart_spi_ss3_SetDriveMode((uint8) pinsDm[debug_uart_SS3_PIN_INDEX]);

        debug_uart_SET_INP_DIS(debug_uart_spi_ss3_INP_DIS,
                                     debug_uart_spi_ss3_MASK,
                                     (0u != (pinsInBuf & debug_uart_SS3_PIN_MASK)));
    #endif /* (debug_uart_SS3_PIN) */
    }

#endif /* (debug_uart_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: debug_uart_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void debug_uart_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (debug_uart_CTRL_REG & debug_uart_CTRL_EC_AM_MODE)) &&
            (0u == (debug_uart_I2C_CTRL_REG & debug_uart_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            debug_uart_CTRL_REG &= ~debug_uart_CTRL_EC_AM_MODE;
            debug_uart_CTRL_REG |=  debug_uart_CTRL_EC_AM_MODE;
        }

        debug_uart_I2C_SLAVE_CMD_REG = debug_uart_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (debug_uart_CY_SCBIP_V0 || debug_uart_CY_SCBIP_V1) */


/* [] END OF FILE */
