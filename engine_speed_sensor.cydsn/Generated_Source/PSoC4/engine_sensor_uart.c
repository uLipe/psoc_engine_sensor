/***************************************************************************//**
* \file engine_sensor_uart.c
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

#include "engine_sensor_uart_PVT.h"

#if (engine_sensor_uart_SCB_MODE_I2C_INC)
    #include "engine_sensor_uart_I2C_PVT.h"
#endif /* (engine_sensor_uart_SCB_MODE_I2C_INC) */

#if (engine_sensor_uart_SCB_MODE_EZI2C_INC)
    #include "engine_sensor_uart_EZI2C_PVT.h"
#endif /* (engine_sensor_uart_SCB_MODE_EZI2C_INC) */

#if (engine_sensor_uart_SCB_MODE_SPI_INC || engine_sensor_uart_SCB_MODE_UART_INC)
    #include "engine_sensor_uart_SPI_UART_PVT.h"
#endif /* (engine_sensor_uart_SCB_MODE_SPI_INC || engine_sensor_uart_SCB_MODE_UART_INC) */


/***************************************
*    Run Time Configuration Vars
***************************************/

/* Stores internal component configuration for Unconfigured mode */
#if (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    uint8 engine_sensor_uart_scbMode = engine_sensor_uart_SCB_MODE_UNCONFIG;
    uint8 engine_sensor_uart_scbEnableWake;
    uint8 engine_sensor_uart_scbEnableIntr;

    /* I2C configuration variables */
    uint8 engine_sensor_uart_mode;
    uint8 engine_sensor_uart_acceptAddr;

    /* SPI/UART configuration variables */
    volatile uint8 * engine_sensor_uart_rxBuffer;
    uint8  engine_sensor_uart_rxDataBits;
    uint32 engine_sensor_uart_rxBufferSize;

    volatile uint8 * engine_sensor_uart_txBuffer;
    uint8  engine_sensor_uart_txDataBits;
    uint32 engine_sensor_uart_txBufferSize;

    /* EZI2C configuration variables */
    uint8 engine_sensor_uart_numberOfAddr;
    uint8 engine_sensor_uart_subAddrSize;
#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Common SCB Vars
***************************************/
/**
* \addtogroup group_general
* \{
*/

/** engine_sensor_uart_initVar indicates whether the engine_sensor_uart 
*  component has been initialized. The variable is initialized to 0 
*  and set to 1 the first time SCB_Start() is called. This allows 
*  the component to restart without reinitialization after the first 
*  call to the engine_sensor_uart_Start() routine.
*
*  If re-initialization of the component is required, then the 
*  engine_sensor_uart_Init() function can be called before the 
*  engine_sensor_uart_Start() or engine_sensor_uart_Enable() function.
*/
uint8 engine_sensor_uart_initVar = 0u;


#if (! (engine_sensor_uart_SCB_MODE_I2C_CONST_CFG || \
        engine_sensor_uart_SCB_MODE_EZI2C_CONST_CFG))
    /** This global variable stores TX interrupt sources after 
    * engine_sensor_uart_Stop() is called. Only these TX interrupt sources 
    * will be restored on a subsequent engine_sensor_uart_Enable() call.
    */
    uint16 engine_sensor_uart_IntrTxMask = 0u;
#endif /* (! (engine_sensor_uart_SCB_MODE_I2C_CONST_CFG || \
              engine_sensor_uart_SCB_MODE_EZI2C_CONST_CFG)) */
/** \} globals */

#if (engine_sensor_uart_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_engine_sensor_uart_CUSTOM_INTR_HANDLER)
    void (*engine_sensor_uart_customIntrHandler)(void) = NULL;
#endif /* !defined (CY_REMOVE_engine_sensor_uart_CUSTOM_INTR_HANDLER) */
#endif /* (engine_sensor_uart_SCB_IRQ_INTERNAL) */


/***************************************
*    Private Function Prototypes
***************************************/

static void engine_sensor_uart_ScbEnableIntr(void);
static void engine_sensor_uart_ScbModeStop(void);
static void engine_sensor_uart_ScbModePostEnable(void);


/*******************************************************************************
* Function Name: engine_sensor_uart_Init
****************************************************************************//**
*
*  Initializes the engine_sensor_uart component to operate in one of the selected
*  configurations: I2C, SPI, UART or EZI2C.
*  When the configuration is set to "Unconfigured SCB", this function does
*  not do any initialization. Use mode-specific initialization APIs instead:
*  engine_sensor_uart_I2CInit, engine_sensor_uart_SpiInit, 
*  engine_sensor_uart_UartInit or engine_sensor_uart_EzI2CInit.
*
*******************************************************************************/
void engine_sensor_uart_Init(void)
{
#if (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    if (engine_sensor_uart_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        engine_sensor_uart_initVar = 0u;
    }
    else
    {
        /* Initialization was done before this function call */
    }

#elif (engine_sensor_uart_SCB_MODE_I2C_CONST_CFG)
    engine_sensor_uart_I2CInit();

#elif (engine_sensor_uart_SCB_MODE_SPI_CONST_CFG)
    engine_sensor_uart_SpiInit();

#elif (engine_sensor_uart_SCB_MODE_UART_CONST_CFG)
    engine_sensor_uart_UartInit();

#elif (engine_sensor_uart_SCB_MODE_EZI2C_CONST_CFG)
    engine_sensor_uart_EzI2CInit();

#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: engine_sensor_uart_Enable
****************************************************************************//**
*
*  Enables engine_sensor_uart component operation: activates the hardware and 
*  internal interrupt. It also restores TX interrupt sources disabled after the 
*  engine_sensor_uart_Stop() function was called (note that level-triggered TX 
*  interrupt sources remain disabled to not cause code lock-up).
*  For I2C and EZI2C modes the interrupt is internal and mandatory for 
*  operation. For SPI and UART modes the interrupt can be configured as none, 
*  internal or external.
*  The engine_sensor_uart configuration should be not changed when the component
*  is enabled. Any configuration changes should be made after disabling the 
*  component.
*  When configuration is set to “Unconfigured engine_sensor_uart”, the component 
*  must first be initialized to operate in one of the following configurations: 
*  I2C, SPI, UART or EZ I2C, using the mode-specific initialization API. 
*  Otherwise this function does not enable the component.
*
*******************************************************************************/
void engine_sensor_uart_Enable(void)
{
#if (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Enable SCB block, only if it is already configured */
    if (!engine_sensor_uart_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        engine_sensor_uart_CTRL_REG |= engine_sensor_uart_CTRL_ENABLED;

        engine_sensor_uart_ScbEnableIntr();

        /* Call PostEnable function specific to current operation mode */
        engine_sensor_uart_ScbModePostEnable();
    }
#else
    engine_sensor_uart_CTRL_REG |= engine_sensor_uart_CTRL_ENABLED;

    engine_sensor_uart_ScbEnableIntr();

    /* Call PostEnable function specific to current operation mode */
    engine_sensor_uart_ScbModePostEnable();
#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: engine_sensor_uart_Start
****************************************************************************//**
*
*  Invokes engine_sensor_uart_Init() and engine_sensor_uart_Enable().
*  After this function call, the component is enabled and ready for operation.
*  When configuration is set to "Unconfigured SCB", the component must first be
*  initialized to operate in one of the following configurations: I2C, SPI, UART
*  or EZI2C. Otherwise this function does not enable the component.
*
* \globalvars
*  engine_sensor_uart_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void engine_sensor_uart_Start(void)
{
    if (0u == engine_sensor_uart_initVar)
    {
        engine_sensor_uart_Init();
        engine_sensor_uart_initVar = 1u; /* Component was initialized */
    }

    engine_sensor_uart_Enable();
}


/*******************************************************************************
* Function Name: engine_sensor_uart_Stop
****************************************************************************//**
*
*  Disables the engine_sensor_uart component: disable the hardware and internal 
*  interrupt. It also disables all TX interrupt sources so as not to cause an 
*  unexpected interrupt trigger because after the component is enabled, the 
*  TX FIFO is empty.
*  Refer to the function engine_sensor_uart_Enable() for the interrupt 
*  configuration details.
*  This function disables the SCB component without checking to see if 
*  communication is in progress. Before calling this function it may be 
*  necessary to check the status of communication to make sure communication 
*  is complete. If this is not done then communication could be stopped mid 
*  byte and corrupted data could result.
*
*******************************************************************************/
void engine_sensor_uart_Stop(void)
{
#if (engine_sensor_uart_SCB_IRQ_INTERNAL)
    engine_sensor_uart_DisableInt();
#endif /* (engine_sensor_uart_SCB_IRQ_INTERNAL) */

    /* Call Stop function specific to current operation mode */
    engine_sensor_uart_ScbModeStop();

    /* Disable SCB IP */
    engine_sensor_uart_CTRL_REG &= (uint32) ~engine_sensor_uart_CTRL_ENABLED;

    /* Disable all TX interrupt sources so as not to cause an unexpected
    * interrupt trigger after the component will be enabled because the 
    * TX FIFO is empty.
    * For SCB IP v0, it is critical as it does not mask-out interrupt
    * sources when it is disabled. This can cause a code lock-up in the
    * interrupt handler because TX FIFO cannot be loaded after the block
    * is disabled.
    */
    engine_sensor_uart_SetTxInterruptMode(engine_sensor_uart_NO_INTR_SOURCES);

#if (engine_sensor_uart_SCB_IRQ_INTERNAL)
    engine_sensor_uart_ClearPendingInt();
#endif /* (engine_sensor_uart_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: engine_sensor_uart_SetRxFifoLevel
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
void engine_sensor_uart_SetRxFifoLevel(uint32 level)
{
    uint32 rxFifoCtrl;

    rxFifoCtrl = engine_sensor_uart_RX_FIFO_CTRL_REG;

    rxFifoCtrl &= ((uint32) ~engine_sensor_uart_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    rxFifoCtrl |= ((uint32) (engine_sensor_uart_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    engine_sensor_uart_RX_FIFO_CTRL_REG = rxFifoCtrl;
}


/*******************************************************************************
* Function Name: engine_sensor_uart_SetTxFifoLevel
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
void engine_sensor_uart_SetTxFifoLevel(uint32 level)
{
    uint32 txFifoCtrl;

    txFifoCtrl = engine_sensor_uart_TX_FIFO_CTRL_REG;

    txFifoCtrl &= ((uint32) ~engine_sensor_uart_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK); /* Clear level mask bits */
    txFifoCtrl |= ((uint32) (engine_sensor_uart_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK & level));

    engine_sensor_uart_TX_FIFO_CTRL_REG = txFifoCtrl;
}


#if (engine_sensor_uart_SCB_IRQ_INTERNAL)
    /*******************************************************************************
    * Function Name: engine_sensor_uart_SetCustomInterruptHandler
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
    void engine_sensor_uart_SetCustomInterruptHandler(void (*func)(void))
    {
    #if !defined (CY_REMOVE_engine_sensor_uart_CUSTOM_INTR_HANDLER)
        engine_sensor_uart_customIntrHandler = func; /* Register interrupt handler */
    #else
        if (NULL != func)
        {
            /* Suppress compiler warning */
        }
    #endif /* !defined (CY_REMOVE_engine_sensor_uart_CUSTOM_INTR_HANDLER) */
    }
#endif /* (engine_sensor_uart_SCB_IRQ_INTERNAL) */


/*******************************************************************************
* Function Name: engine_sensor_uart_ScbModeEnableIntr
****************************************************************************//**
*
*  Enables an interrupt for a specific mode.
*
*******************************************************************************/
static void engine_sensor_uart_ScbEnableIntr(void)
{
#if (engine_sensor_uart_SCB_IRQ_INTERNAL)
    /* Enable interrupt in NVIC */
    #if (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
        if (0u != engine_sensor_uart_scbEnableIntr)
        {
            engine_sensor_uart_EnableInt();
        }

    #else
        engine_sensor_uart_EnableInt();

    #endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (engine_sensor_uart_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: engine_sensor_uart_ScbModePostEnable
****************************************************************************//**
*
*  Calls the PostEnable function for a specific operation mode.
*
*******************************************************************************/
static void engine_sensor_uart_ScbModePostEnable(void)
{
#if (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
#if (!engine_sensor_uart_CY_SCBIP_V1)
    if (engine_sensor_uart_SCB_MODE_SPI_RUNTM_CFG)
    {
        engine_sensor_uart_SpiPostEnable();
    }
    else if (engine_sensor_uart_SCB_MODE_UART_RUNTM_CFG)
    {
        engine_sensor_uart_UartPostEnable();
    }
    else
    {
        /* Unknown mode: do nothing */
    }
#endif /* (!engine_sensor_uart_CY_SCBIP_V1) */

#elif (engine_sensor_uart_SCB_MODE_SPI_CONST_CFG)
    engine_sensor_uart_SpiPostEnable();

#elif (engine_sensor_uart_SCB_MODE_UART_CONST_CFG)
    engine_sensor_uart_UartPostEnable();

#else
    /* Unknown mode: do nothing */
#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: engine_sensor_uart_ScbModeStop
****************************************************************************//**
*
*  Calls the Stop function for a specific operation mode.
*
*******************************************************************************/
static void engine_sensor_uart_ScbModeStop(void)
{
#if (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    if (engine_sensor_uart_SCB_MODE_I2C_RUNTM_CFG)
    {
        engine_sensor_uart_I2CStop();
    }
    else if (engine_sensor_uart_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        engine_sensor_uart_EzI2CStop();
    }
#if (!engine_sensor_uart_CY_SCBIP_V1)
    else if (engine_sensor_uart_SCB_MODE_SPI_RUNTM_CFG)
    {
        engine_sensor_uart_SpiStop();
    }
    else if (engine_sensor_uart_SCB_MODE_UART_RUNTM_CFG)
    {
        engine_sensor_uart_UartStop();
    }
#endif /* (!engine_sensor_uart_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
#elif (engine_sensor_uart_SCB_MODE_I2C_CONST_CFG)
    engine_sensor_uart_I2CStop();

#elif (engine_sensor_uart_SCB_MODE_EZI2C_CONST_CFG)
    engine_sensor_uart_EzI2CStop();

#elif (engine_sensor_uart_SCB_MODE_SPI_CONST_CFG)
    engine_sensor_uart_SpiStop();

#elif (engine_sensor_uart_SCB_MODE_UART_CONST_CFG)
    engine_sensor_uart_UartStop();

#else
    /* Unknown mode: do nothing */
#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: engine_sensor_uart_SetPins
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
    void engine_sensor_uart_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask)
    {
        uint32 pinsDm[engine_sensor_uart_SCB_PINS_NUMBER];
        uint32 i;
        
    #if (!engine_sensor_uart_CY_SCBIP_V1)
        uint32 pinsInBuf = 0u;
    #endif /* (!engine_sensor_uart_CY_SCBIP_V1) */
        
        uint32 hsiomSel[engine_sensor_uart_SCB_PINS_NUMBER] = 
        {
            engine_sensor_uart_RX_SCL_MOSI_HSIOM_SEL_GPIO,
            engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_GPIO,
            0u,
            0u,
            0u,
            0u,
            0u,
        };

    #if (engine_sensor_uart_CY_SCBIP_V1)
        /* Supress compiler warning. */
        if ((0u == subMode) || (0u == uartEnableMask))
        {
        }
    #endif /* (engine_sensor_uart_CY_SCBIP_V1) */

        /* Set default HSIOM to GPIO and Drive Mode to Analog Hi-Z */
        for (i = 0u; i < engine_sensor_uart_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = engine_sensor_uart_PIN_DM_ALG_HIZ;
        }

        if ((engine_sensor_uart_SCB_MODE_I2C   == mode) ||
            (engine_sensor_uart_SCB_MODE_EZI2C == mode))
        {
        #if (engine_sensor_uart_RX_SCL_MOSI_PIN)
            hsiomSel[engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_RX_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_PIN_DM_OD_LO;
        #elif (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C;
            pinsDm  [engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_PIN_DM_OD_LO;
        #else
        #endif /* (engine_sensor_uart_RX_SCL_MOSI_PIN) */
        
        #if (engine_sensor_uart_TX_SDA_MISO_PIN)
            hsiomSel[engine_sensor_uart_TX_SDA_MISO_PIN_INDEX] = engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_I2C;
            pinsDm  [engine_sensor_uart_TX_SDA_MISO_PIN_INDEX] = engine_sensor_uart_PIN_DM_OD_LO;
        #endif /* (engine_sensor_uart_TX_SDA_MISO_PIN) */
        }
    #if (!engine_sensor_uart_CY_SCBIP_V1)
        else if (engine_sensor_uart_SCB_MODE_SPI == mode)
        {
        #if (engine_sensor_uart_RX_SCL_MOSI_PIN)
            hsiomSel[engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_RX_SCL_MOSI_HSIOM_SEL_SPI;
        #elif (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN)
            hsiomSel[engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI;
        #else
        #endif /* (engine_sensor_uart_RX_SCL_MOSI_PIN) */
        
        #if (engine_sensor_uart_TX_SDA_MISO_PIN)
            hsiomSel[engine_sensor_uart_TX_SDA_MISO_PIN_INDEX] = engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_SPI;
        #endif /* (engine_sensor_uart_TX_SDA_MISO_PIN) */
        
        #if (engine_sensor_uart_CTS_SCLK_PIN)
            hsiomSel[engine_sensor_uart_CTS_SCLK_PIN_INDEX] = engine_sensor_uart_CTS_SCLK_HSIOM_SEL_SPI;
        #endif /* (engine_sensor_uart_CTS_SCLK_PIN) */

            if (engine_sensor_uart_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_PIN_DM_DIG_HIZ;
                pinsDm[engine_sensor_uart_TX_SDA_MISO_PIN_INDEX] = engine_sensor_uart_PIN_DM_STRONG;
                pinsDm[engine_sensor_uart_CTS_SCLK_PIN_INDEX] = engine_sensor_uart_PIN_DM_DIG_HIZ;

            #if (engine_sensor_uart_RTS_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[engine_sensor_uart_RTS_SS0_PIN_INDEX] = engine_sensor_uart_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm  [engine_sensor_uart_RTS_SS0_PIN_INDEX] = engine_sensor_uart_PIN_DM_DIG_HIZ;
            #endif /* (engine_sensor_uart_RTS_SS0_PIN) */

            #if (engine_sensor_uart_TX_SDA_MISO_PIN)
                /* Disable input buffer */
                 pinsInBuf |= engine_sensor_uart_TX_SDA_MISO_PIN_MASK;
            #endif /* (engine_sensor_uart_TX_SDA_MISO_PIN) */
            }
            else 
            {
                /* (Master) */
                pinsDm[engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_PIN_DM_STRONG;
                pinsDm[engine_sensor_uart_TX_SDA_MISO_PIN_INDEX] = engine_sensor_uart_PIN_DM_DIG_HIZ;
                pinsDm[engine_sensor_uart_CTS_SCLK_PIN_INDEX] = engine_sensor_uart_PIN_DM_STRONG;

            #if (engine_sensor_uart_RTS_SS0_PIN)
                hsiomSel [engine_sensor_uart_RTS_SS0_PIN_INDEX] = engine_sensor_uart_RTS_SS0_HSIOM_SEL_SPI;
                pinsDm   [engine_sensor_uart_RTS_SS0_PIN_INDEX] = engine_sensor_uart_PIN_DM_STRONG;
                pinsInBuf |= engine_sensor_uart_RTS_SS0_PIN_MASK;
            #endif /* (engine_sensor_uart_RTS_SS0_PIN) */

            #if (engine_sensor_uart_SS1_PIN)
                hsiomSel [engine_sensor_uart_SS1_PIN_INDEX] = engine_sensor_uart_SS1_HSIOM_SEL_SPI;
                pinsDm   [engine_sensor_uart_SS1_PIN_INDEX] = engine_sensor_uart_PIN_DM_STRONG;
                pinsInBuf |= engine_sensor_uart_SS1_PIN_MASK;
            #endif /* (engine_sensor_uart_SS1_PIN) */

            #if (engine_sensor_uart_SS2_PIN)
                hsiomSel [engine_sensor_uart_SS2_PIN_INDEX] = engine_sensor_uart_SS2_HSIOM_SEL_SPI;
                pinsDm   [engine_sensor_uart_SS2_PIN_INDEX] = engine_sensor_uart_PIN_DM_STRONG;
                pinsInBuf |= engine_sensor_uart_SS2_PIN_MASK;
            #endif /* (engine_sensor_uart_SS2_PIN) */

            #if (engine_sensor_uart_SS3_PIN)
                hsiomSel [engine_sensor_uart_SS3_PIN_INDEX] = engine_sensor_uart_SS3_HSIOM_SEL_SPI;
                pinsDm   [engine_sensor_uart_SS3_PIN_INDEX] = engine_sensor_uart_PIN_DM_STRONG;
                pinsInBuf |= engine_sensor_uart_SS3_PIN_MASK;
            #endif /* (engine_sensor_uart_SS3_PIN) */

                /* Disable input buffers */
            #if (engine_sensor_uart_RX_SCL_MOSI_PIN)
                pinsInBuf |= engine_sensor_uart_RX_SCL_MOSI_PIN_MASK;
            #elif (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN)
                pinsInBuf |= engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_MASK;
            #else
            #endif /* (engine_sensor_uart_RX_SCL_MOSI_PIN) */

            #if (engine_sensor_uart_CTS_SCLK_PIN)
                pinsInBuf |= engine_sensor_uart_CTS_SCLK_PIN_MASK;
            #endif /* (engine_sensor_uart_CTS_SCLK_PIN) */
            }
        }
        else /* UART */
        {
            if (engine_sensor_uart_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
            #if (engine_sensor_uart_TX_SDA_MISO_PIN)
                hsiomSel[engine_sensor_uart_TX_SDA_MISO_PIN_INDEX] = engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_UART;
                pinsDm  [engine_sensor_uart_TX_SDA_MISO_PIN_INDEX] = engine_sensor_uart_PIN_DM_OD_LO;
            #endif /* (engine_sensor_uart_TX_SDA_MISO_PIN) */
            }
            else /* Standard or IrDA */
            {
                if (0u != (engine_sensor_uart_UART_RX_PIN_ENABLE & uartEnableMask))
                {
                #if (engine_sensor_uart_RX_SCL_MOSI_PIN)
                    hsiomSel[engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_RX_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_PIN_DM_DIG_HIZ;
                #elif (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN)
                    hsiomSel[engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART;
                    pinsDm  [engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX] = engine_sensor_uart_PIN_DM_DIG_HIZ;
                #else
                #endif /* (engine_sensor_uart_RX_SCL_MOSI_PIN) */
                }

                if (0u != (engine_sensor_uart_UART_TX_PIN_ENABLE & uartEnableMask))
                {
                #if (engine_sensor_uart_TX_SDA_MISO_PIN)
                    hsiomSel[engine_sensor_uart_TX_SDA_MISO_PIN_INDEX] = engine_sensor_uart_TX_SDA_MISO_HSIOM_SEL_UART;
                    pinsDm  [engine_sensor_uart_TX_SDA_MISO_PIN_INDEX] = engine_sensor_uart_PIN_DM_STRONG;
                    
                    /* Disable input buffer */
                    pinsInBuf |= engine_sensor_uart_TX_SDA_MISO_PIN_MASK;
                #endif /* (engine_sensor_uart_TX_SDA_MISO_PIN) */
                }

            #if !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
                if (engine_sensor_uart_UART_MODE_STD == subMode)
                {
                    if (0u != (engine_sensor_uart_UART_CTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* CTS input is multiplexed with SCLK */
                    #if (engine_sensor_uart_CTS_SCLK_PIN)
                        hsiomSel[engine_sensor_uart_CTS_SCLK_PIN_INDEX] = engine_sensor_uart_CTS_SCLK_HSIOM_SEL_UART;
                        pinsDm  [engine_sensor_uart_CTS_SCLK_PIN_INDEX] = engine_sensor_uart_PIN_DM_DIG_HIZ;
                    #endif /* (engine_sensor_uart_CTS_SCLK_PIN) */
                    }

                    if (0u != (engine_sensor_uart_UART_RTS_PIN_ENABLE & uartEnableMask))
                    {
                        /* RTS output is multiplexed with SS0 */
                    #if (engine_sensor_uart_RTS_SS0_PIN)
                        hsiomSel[engine_sensor_uart_RTS_SS0_PIN_INDEX] = engine_sensor_uart_RTS_SS0_HSIOM_SEL_UART;
                        pinsDm  [engine_sensor_uart_RTS_SS0_PIN_INDEX] = engine_sensor_uart_PIN_DM_STRONG;
                        
                        /* Disable input buffer */
                        pinsInBuf |= engine_sensor_uart_RTS_SS0_PIN_MASK;
                    #endif /* (engine_sensor_uart_RTS_SS0_PIN) */
                    }
                }
            #endif /* !(engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */
            }
        }
    #endif /* (!engine_sensor_uart_CY_SCBIP_V1) */

    /* Configure pins: set HSIOM, DM and InputBufEnable */
    /* Note: the DR register settings do not effect the pin output if HSIOM is other than GPIO */

    #if (engine_sensor_uart_RX_SCL_MOSI_PIN)
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_RX_SCL_MOSI_HSIOM_REG,
                                       engine_sensor_uart_RX_SCL_MOSI_HSIOM_MASK,
                                       engine_sensor_uart_RX_SCL_MOSI_HSIOM_POS,
                                        hsiomSel[engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX]);

        engine_sensor_uart_uart_rx_i2c_scl_spi_mosi_SetDriveMode((uint8) pinsDm[engine_sensor_uart_RX_SCL_MOSI_PIN_INDEX]);

        #if (!engine_sensor_uart_CY_SCBIP_V1)
            engine_sensor_uart_SET_INP_DIS(engine_sensor_uart_uart_rx_i2c_scl_spi_mosi_INP_DIS,
                                         engine_sensor_uart_uart_rx_i2c_scl_spi_mosi_MASK,
                                         (0u != (pinsInBuf & engine_sensor_uart_RX_SCL_MOSI_PIN_MASK)));
        #endif /* (!engine_sensor_uart_CY_SCBIP_V1) */
    
    #elif (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN)
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_REG,
                                       engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_MASK,
                                       engine_sensor_uart_RX_WAKE_SCL_MOSI_HSIOM_POS,
                                       hsiomSel[engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi_SetDriveMode((uint8)
                                                               pinsDm[engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_INDEX]);

        engine_sensor_uart_SET_INP_DIS(engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi_INP_DIS,
                                     engine_sensor_uart_uart_rx_wake_i2c_scl_spi_mosi_MASK,
                                     (0u != (pinsInBuf & engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN_MASK)));

         /* Set interrupt on falling edge */
        engine_sensor_uart_SET_INCFG_TYPE(engine_sensor_uart_RX_WAKE_SCL_MOSI_INTCFG_REG,
                                        engine_sensor_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK,
                                        engine_sensor_uart_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS,
                                        engine_sensor_uart_INTCFG_TYPE_FALLING_EDGE);
    #else
    #endif /* (engine_sensor_uart_RX_WAKE_SCL_MOSI_PIN) */

    #if (engine_sensor_uart_TX_SDA_MISO_PIN)
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_TX_SDA_MISO_HSIOM_REG,
                                       engine_sensor_uart_TX_SDA_MISO_HSIOM_MASK,
                                       engine_sensor_uart_TX_SDA_MISO_HSIOM_POS,
                                        hsiomSel[engine_sensor_uart_TX_SDA_MISO_PIN_INDEX]);

        engine_sensor_uart_uart_tx_i2c_sda_spi_miso_SetDriveMode((uint8) pinsDm[engine_sensor_uart_TX_SDA_MISO_PIN_INDEX]);

    #if (!engine_sensor_uart_CY_SCBIP_V1)
        engine_sensor_uart_SET_INP_DIS(engine_sensor_uart_uart_tx_i2c_sda_spi_miso_INP_DIS,
                                     engine_sensor_uart_uart_tx_i2c_sda_spi_miso_MASK,
                                    (0u != (pinsInBuf & engine_sensor_uart_TX_SDA_MISO_PIN_MASK)));
    #endif /* (!engine_sensor_uart_CY_SCBIP_V1) */
    #endif /* (engine_sensor_uart_RX_SCL_MOSI_PIN) */

    #if (engine_sensor_uart_CTS_SCLK_PIN)
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_CTS_SCLK_HSIOM_REG,
                                       engine_sensor_uart_CTS_SCLK_HSIOM_MASK,
                                       engine_sensor_uart_CTS_SCLK_HSIOM_POS,
                                       hsiomSel[engine_sensor_uart_CTS_SCLK_PIN_INDEX]);

        engine_sensor_uart_uart_cts_spi_sclk_SetDriveMode((uint8) pinsDm[engine_sensor_uart_CTS_SCLK_PIN_INDEX]);

        engine_sensor_uart_SET_INP_DIS(engine_sensor_uart_uart_cts_spi_sclk_INP_DIS,
                                     engine_sensor_uart_uart_cts_spi_sclk_MASK,
                                     (0u != (pinsInBuf & engine_sensor_uart_CTS_SCLK_PIN_MASK)));
    #endif /* (engine_sensor_uart_CTS_SCLK_PIN) */

    #if (engine_sensor_uart_RTS_SS0_PIN)
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_RTS_SS0_HSIOM_REG,
                                       engine_sensor_uart_RTS_SS0_HSIOM_MASK,
                                       engine_sensor_uart_RTS_SS0_HSIOM_POS,
                                       hsiomSel[engine_sensor_uart_RTS_SS0_PIN_INDEX]);

        engine_sensor_uart_uart_rts_spi_ss0_SetDriveMode((uint8) pinsDm[engine_sensor_uart_RTS_SS0_PIN_INDEX]);

        engine_sensor_uart_SET_INP_DIS(engine_sensor_uart_uart_rts_spi_ss0_INP_DIS,
                                     engine_sensor_uart_uart_rts_spi_ss0_MASK,
                                     (0u != (pinsInBuf & engine_sensor_uart_RTS_SS0_PIN_MASK)));
    #endif /* (engine_sensor_uart_RTS_SS0_PIN) */

    #if (engine_sensor_uart_SS1_PIN)
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_SS1_HSIOM_REG,
                                       engine_sensor_uart_SS1_HSIOM_MASK,
                                       engine_sensor_uart_SS1_HSIOM_POS,
                                       hsiomSel[engine_sensor_uart_SS1_PIN_INDEX]);

        engine_sensor_uart_spi_ss1_SetDriveMode((uint8) pinsDm[engine_sensor_uart_SS1_PIN_INDEX]);

        engine_sensor_uart_SET_INP_DIS(engine_sensor_uart_spi_ss1_INP_DIS,
                                     engine_sensor_uart_spi_ss1_MASK,
                                     (0u != (pinsInBuf & engine_sensor_uart_SS1_PIN_MASK)));
    #endif /* (engine_sensor_uart_SS1_PIN) */

    #if (engine_sensor_uart_SS2_PIN)
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_SS2_HSIOM_REG,
                                       engine_sensor_uart_SS2_HSIOM_MASK,
                                       engine_sensor_uart_SS2_HSIOM_POS,
                                       hsiomSel[engine_sensor_uart_SS2_PIN_INDEX]);

        engine_sensor_uart_spi_ss2_SetDriveMode((uint8) pinsDm[engine_sensor_uart_SS2_PIN_INDEX]);

        engine_sensor_uart_SET_INP_DIS(engine_sensor_uart_spi_ss2_INP_DIS,
                                     engine_sensor_uart_spi_ss2_MASK,
                                     (0u != (pinsInBuf & engine_sensor_uart_SS2_PIN_MASK)));
    #endif /* (engine_sensor_uart_SS2_PIN) */

    #if (engine_sensor_uart_SS3_PIN)
        engine_sensor_uart_SET_HSIOM_SEL(engine_sensor_uart_SS3_HSIOM_REG,
                                       engine_sensor_uart_SS3_HSIOM_MASK,
                                       engine_sensor_uart_SS3_HSIOM_POS,
                                       hsiomSel[engine_sensor_uart_SS3_PIN_INDEX]);

        engine_sensor_uart_spi_ss3_SetDriveMode((uint8) pinsDm[engine_sensor_uart_SS3_PIN_INDEX]);

        engine_sensor_uart_SET_INP_DIS(engine_sensor_uart_spi_ss3_INP_DIS,
                                     engine_sensor_uart_spi_ss3_MASK,
                                     (0u != (pinsInBuf & engine_sensor_uart_SS3_PIN_MASK)));
    #endif /* (engine_sensor_uart_SS3_PIN) */
    }

#endif /* (engine_sensor_uart_SCB_MODE_UNCONFIG_CONST_CFG) */


#if (engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: engine_sensor_uart_I2CSlaveNackGeneration
    ****************************************************************************//**
    *
    *  Sets command to generate NACK to the address or data.
    *
    *******************************************************************************/
    void engine_sensor_uart_I2CSlaveNackGeneration(void)
    {
        /* Check for EC_AM toggle condition: EC_AM and clock stretching for address are enabled */
        if ((0u != (engine_sensor_uart_CTRL_REG & engine_sensor_uart_CTRL_EC_AM_MODE)) &&
            (0u == (engine_sensor_uart_I2C_CTRL_REG & engine_sensor_uart_I2C_CTRL_S_NOT_READY_ADDR_NACK)))
        {
            /* Toggle EC_AM before NACK generation */
            engine_sensor_uart_CTRL_REG &= ~engine_sensor_uart_CTRL_EC_AM_MODE;
            engine_sensor_uart_CTRL_REG |=  engine_sensor_uart_CTRL_EC_AM_MODE;
        }

        engine_sensor_uart_I2C_SLAVE_CMD_REG = engine_sensor_uart_I2C_SLAVE_CMD_S_NACK;
    }
#endif /* (engine_sensor_uart_CY_SCBIP_V0 || engine_sensor_uart_CY_SCBIP_V1) */


/* [] END OF FILE */
