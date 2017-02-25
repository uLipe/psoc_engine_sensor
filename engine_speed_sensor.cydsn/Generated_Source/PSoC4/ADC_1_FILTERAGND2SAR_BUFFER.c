/*******************************************************************************
* File Name: ADC_1_FILTERAGND2SAR_BUFFER.c
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

#include "ADC_1_FILTERAGND2SAR_BUFFER.h"

uint8 ADC_1_FILTERAGND2SAR_BUFFER_initVar = 0u; /* Defines if component was initialized */
static uint32 ADC_1_FILTERAGND2SAR_BUFFER_internalPower = 0u; /* Defines component Power value */


/*******************************************************************************
* Function Name: ADC_1_FILTERAGND2SAR_BUFFER_Init
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
void ADC_1_FILTERAGND2SAR_BUFFER_Init(void)
{
    ADC_1_FILTERAGND2SAR_BUFFER_internalPower = ADC_1_FILTERAGND2SAR_BUFFER_POWER;
    ADC_1_FILTERAGND2SAR_BUFFER_CTB_CTRL_REG = ADC_1_FILTERAGND2SAR_BUFFER_DEFAULT_CTB_CTRL;
    ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_REG = ADC_1_FILTERAGND2SAR_BUFFER_DEFAULT_OA_RES_CTRL;
    ADC_1_FILTERAGND2SAR_BUFFER_OA_COMP_TRIM_REG = ADC_1_FILTERAGND2SAR_BUFFER_DEFAULT_OA_COMP_TRIM_REG;
}


/*******************************************************************************
* Function Name: ADC_1_FILTERAGND2SAR_BUFFER_Enable
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
void ADC_1_FILTERAGND2SAR_BUFFER_Enable(void)
{
    ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_REG |= ADC_1_FILTERAGND2SAR_BUFFER_internalPower | \
                                        ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: ADC_1_FILTERAGND2SAR_BUFFER_Start
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
*  ADC_1_FILTERAGND2SAR_BUFFER_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void ADC_1_FILTERAGND2SAR_BUFFER_Start(void)
{
    if( 0u == ADC_1_FILTERAGND2SAR_BUFFER_initVar)
    {
        ADC_1_FILTERAGND2SAR_BUFFER_Init();
        ADC_1_FILTERAGND2SAR_BUFFER_initVar = 1u;
    }
    ADC_1_FILTERAGND2SAR_BUFFER_Enable();
}


/*******************************************************************************
* Function Name: ADC_1_FILTERAGND2SAR_BUFFER_Stop
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
void ADC_1_FILTERAGND2SAR_BUFFER_Stop(void)
{
    ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_REG &= ((uint32)~(ADC_1_FILTERAGND2SAR_BUFFER_OA_PWR_MODE_MASK | \
                                                   ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: ADC_1_FILTERAGND2SAR_BUFFER_SetPower
********************************************************************************
*
* Summary:
*  Sets the Opamp to one of the three power levels.
*
* Parameters:
*  power: power levels.
*   ADC_1_FILTERAGND2SAR_BUFFER_LOW_POWER - Lowest active power
*   ADC_1_FILTERAGND2SAR_BUFFER_MED_POWER - Medium power
*   ADC_1_FILTERAGND2SAR_BUFFER_HIGH_POWER - Highest active power
*
* Return:
*  None
*
**********************************************************************************/
void ADC_1_FILTERAGND2SAR_BUFFER_SetPower(uint32 power)
{
    uint32 tmp;
    
    ADC_1_FILTERAGND2SAR_BUFFER_internalPower = ADC_1_FILTERAGND2SAR_BUFFER_GET_OA_PWR_MODE(power);
    tmp = ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_REG & \
           (uint32)~ADC_1_FILTERAGND2SAR_BUFFER_OA_PWR_MODE_MASK;
    ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL_REG = tmp | ADC_1_FILTERAGND2SAR_BUFFER_internalPower;
}


/*******************************************************************************
* Function Name: ADC_1_FILTERAGND2SAR_BUFFER_PumpControl
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
*   ADC_1_FILTERAGND2SAR_BUFFER_PUMP_OFF - Turn off the pump
*   ADC_1_FILTERAGND2SAR_BUFFER_PUMP_ON - Turn on the pump
*
* Return:
*  None
*
**********************************************************************************/
void ADC_1_FILTERAGND2SAR_BUFFER_PumpControl(uint32 onOff)
{
    
    if(0u != onOff)
    {
        ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL |= ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_EN;    
    }
    else
    {
        ADC_1_FILTERAGND2SAR_BUFFER_OA_RES_CTRL &= (uint32)~ADC_1_FILTERAGND2SAR_BUFFER_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
