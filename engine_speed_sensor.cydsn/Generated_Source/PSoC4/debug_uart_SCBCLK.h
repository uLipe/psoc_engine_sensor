/*******************************************************************************
* File Name: debug_uart_SCBCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_debug_uart_SCBCLK_H)
#define CY_CLOCK_debug_uart_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void debug_uart_SCBCLK_StartEx(uint32 alignClkDiv);
#define debug_uart_SCBCLK_Start() \
    debug_uart_SCBCLK_StartEx(debug_uart_SCBCLK__PA_DIV_ID)

#else

void debug_uart_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void debug_uart_SCBCLK_Stop(void);

void debug_uart_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 debug_uart_SCBCLK_GetDividerRegister(void);
uint8  debug_uart_SCBCLK_GetFractionalDividerRegister(void);

#define debug_uart_SCBCLK_Enable()                         debug_uart_SCBCLK_Start()
#define debug_uart_SCBCLK_Disable()                        debug_uart_SCBCLK_Stop()
#define debug_uart_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    debug_uart_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define debug_uart_SCBCLK_SetDivider(clkDivider)           debug_uart_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define debug_uart_SCBCLK_SetDividerValue(clkDivider)      debug_uart_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define debug_uart_SCBCLK_DIV_ID     debug_uart_SCBCLK__DIV_ID

#define debug_uart_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define debug_uart_SCBCLK_CTRL_REG   (*(reg32 *)debug_uart_SCBCLK__CTRL_REGISTER)
#define debug_uart_SCBCLK_DIV_REG    (*(reg32 *)debug_uart_SCBCLK__DIV_REGISTER)

#define debug_uart_SCBCLK_CMD_DIV_SHIFT          (0u)
#define debug_uart_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define debug_uart_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define debug_uart_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define debug_uart_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << debug_uart_SCBCLK_CMD_DISABLE_SHIFT))
#define debug_uart_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << debug_uart_SCBCLK_CMD_ENABLE_SHIFT))

#define debug_uart_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define debug_uart_SCBCLK_DIV_FRAC_SHIFT (3u)
#define debug_uart_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define debug_uart_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define debug_uart_SCBCLK_DIV_REG        (*(reg32 *)debug_uart_SCBCLK__REGISTER)
#define debug_uart_SCBCLK_ENABLE_REG     debug_uart_SCBCLK_DIV_REG
#define debug_uart_SCBCLK_DIV_FRAC_MASK  debug_uart_SCBCLK__FRAC_MASK
#define debug_uart_SCBCLK_DIV_FRAC_SHIFT (16u)
#define debug_uart_SCBCLK_DIV_INT_MASK   debug_uart_SCBCLK__DIVIDER_MASK
#define debug_uart_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_debug_uart_SCBCLK_H) */

/* [] END OF FILE */
