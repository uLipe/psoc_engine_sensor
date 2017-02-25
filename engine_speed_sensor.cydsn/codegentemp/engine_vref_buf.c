/*******************************************************************************
* File Name: engine_vref_buf.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the Opamp (Analog Buffer)
*  Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "engine_vref_buf.h"

uint8 engine_vref_buf_initVar = 0u; /* Defines if component was initialized */
static uint32 engine_vref_buf_internalPower = 0u; /* Defines component Power value */


/*******************************************************************************
* Function Name: engine_vref_buf_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void engine_vref_buf_Init(void)
{
    engine_vref_buf_internalPower = engine_vref_buf_POWER;
    engine_vref_buf_CTB_CTRL_REG = engine_vref_buf_DEFAULT_CTB_CTRL;
    engine_vref_buf_OA_RES_CTRL_REG = engine_vref_buf_DEFAULT_OA_RES_CTRL;
    engine_vref_buf_OA_COMP_TRIM_REG = engine_vref_buf_DEFAULT_OA_COMP_TRIM_REG;
}


/*******************************************************************************
* Function Name: engine_vref_buf_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void engine_vref_buf_Enable(void)
{
    engine_vref_buf_OA_RES_CTRL_REG |= engine_vref_buf_internalPower | \
                                        engine_vref_buf_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: engine_vref_buf_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables power 
*  to the block. The first time the routine is executed, the Power level, Mode, 
*  and Output mode are set. When called to restart the Opamp following a Stop() call, 
*  the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  engine_vref_buf_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void engine_vref_buf_Start(void)
{
    if( 0u == engine_vref_buf_initVar)
    {
        engine_vref_buf_Init();
        engine_vref_buf_initVar = 1u;
    }
    engine_vref_buf_Enable();
}


/*******************************************************************************
* Function Name: engine_vref_buf_Stop
********************************************************************************
*
* Summary:
*  Turn off the Opamp block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void engine_vref_buf_Stop(void)
{
    engine_vref_buf_OA_RES_CTRL_REG &= ((uint32)~(engine_vref_buf_OA_PWR_MODE_MASK | \
                                                   engine_vref_buf_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: engine_vref_buf_SetPower
********************************************************************************
*
* Summary:
*  Sets the Opamp to one of the three power levels.
*
* Parameters:
*  power: power levels.
*   engine_vref_buf_LOW_POWER - Lowest active power
*   engine_vref_buf_MED_POWER - Medium power
*   engine_vref_buf_HIGH_POWER - Highest active power
*
* Return:
*  None
*
**********************************************************************************/
void engine_vref_buf_SetPower(uint32 power)
{
    uint32 tmp;
    
    engine_vref_buf_internalPower = engine_vref_buf_GET_OA_PWR_MODE(power);
    tmp = engine_vref_buf_OA_RES_CTRL_REG & \
           (uint32)~engine_vref_buf_OA_PWR_MODE_MASK;
    engine_vref_buf_OA_RES_CTRL_REG = tmp | engine_vref_buf_internalPower;
}


/*******************************************************************************
* Function Name: engine_vref_buf_PumpControl
********************************************************************************
*
* Summary:
*  Allows the user to turn the Opamp's boost pump on or off. By Default the Start() 
*  function turns on the pump. Use this API to turn it off. The boost must be 
*  turned on when the supply is less than 2.7 volts and off if the supply is more 
*  than 4 volts.
*
* Parameters:
*  onOff: Control the pump.
*   engine_vref_buf_PUMP_OFF - Turn off the pump
*   engine_vref_buf_PUMP_ON - Turn on the pump
*
* Return:
*  None
*
**********************************************************************************/
void engine_vref_buf_PumpControl(uint32 onOff)
{
    
    if(0u != onOff)
    {
        engine_vref_buf_OA_RES_CTRL |= engine_vref_buf_OA_PUMP_EN;    
    }
    else
    {
        engine_vref_buf_OA_RES_CTRL &= (uint32)~engine_vref_buf_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
