/*******************************************************************************
* File Name: engine_sensor_uart_SCBCLK.h
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

#if !defined(CY_CLOCK_engine_sensor_uart_SCBCLK_H)
#define CY_CLOCK_engine_sensor_uart_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void engine_sensor_uart_SCBCLK_StartEx(uint32 alignClkDiv);
#define engine_sensor_uart_SCBCLK_Start() \
    engine_sensor_uart_SCBCLK_StartEx(engine_sensor_uart_SCBCLK__PA_DIV_ID)

#else

void engine_sensor_uart_SCBCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void engine_sensor_uart_SCBCLK_Stop(void);

void engine_sensor_uart_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 engine_sensor_uart_SCBCLK_GetDividerRegister(void);
uint8  engine_sensor_uart_SCBCLK_GetFractionalDividerRegister(void);

#define engine_sensor_uart_SCBCLK_Enable()                         engine_sensor_uart_SCBCLK_Start()
#define engine_sensor_uart_SCBCLK_Disable()                        engine_sensor_uart_SCBCLK_Stop()
#define engine_sensor_uart_SCBCLK_SetDividerRegister(clkDivider, reset)  \
    engine_sensor_uart_SCBCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define engine_sensor_uart_SCBCLK_SetDivider(clkDivider)           engine_sensor_uart_SCBCLK_SetDividerRegister((clkDivider), 1u)
#define engine_sensor_uart_SCBCLK_SetDividerValue(clkDivider)      engine_sensor_uart_SCBCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define engine_sensor_uart_SCBCLK_DIV_ID     engine_sensor_uart_SCBCLK__DIV_ID

#define engine_sensor_uart_SCBCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define engine_sensor_uart_SCBCLK_CTRL_REG   (*(reg32 *)engine_sensor_uart_SCBCLK__CTRL_REGISTER)
#define engine_sensor_uart_SCBCLK_DIV_REG    (*(reg32 *)engine_sensor_uart_SCBCLK__DIV_REGISTER)

#define engine_sensor_uart_SCBCLK_CMD_DIV_SHIFT          (0u)
#define engine_sensor_uart_SCBCLK_CMD_PA_DIV_SHIFT       (8u)
#define engine_sensor_uart_SCBCLK_CMD_DISABLE_SHIFT      (30u)
#define engine_sensor_uart_SCBCLK_CMD_ENABLE_SHIFT       (31u)

#define engine_sensor_uart_SCBCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << engine_sensor_uart_SCBCLK_CMD_DISABLE_SHIFT))
#define engine_sensor_uart_SCBCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << engine_sensor_uart_SCBCLK_CMD_ENABLE_SHIFT))

#define engine_sensor_uart_SCBCLK_DIV_FRAC_MASK  (0x000000F8u)
#define engine_sensor_uart_SCBCLK_DIV_FRAC_SHIFT (3u)
#define engine_sensor_uart_SCBCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define engine_sensor_uart_SCBCLK_DIV_INT_SHIFT  (8u)

#else 

#define engine_sensor_uart_SCBCLK_DIV_REG        (*(reg32 *)engine_sensor_uart_SCBCLK__REGISTER)
#define engine_sensor_uart_SCBCLK_ENABLE_REG     engine_sensor_uart_SCBCLK_DIV_REG
#define engine_sensor_uart_SCBCLK_DIV_FRAC_MASK  engine_sensor_uart_SCBCLK__FRAC_MASK
#define engine_sensor_uart_SCBCLK_DIV_FRAC_SHIFT (16u)
#define engine_sensor_uart_SCBCLK_DIV_INT_MASK   engine_sensor_uart_SCBCLK__DIVIDER_MASK
#define engine_sensor_uart_SCBCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_engine_sensor_uart_SCBCLK_H) */

/* [] END OF FILE */
