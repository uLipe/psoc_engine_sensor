/***************************************************************************//**
* \file engine_sensor_ref.c
* \version 1.0
*
* \brief
*  This file provides the source code to the API for the Programmable
*  Voltage Reference component.
*
* Note:
*  None
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "engine_sensor_ref.h"

uint8 engine_sensor_ref_initVar = 0u;


/*******************************************************************************
* Function Name: engine_sensor_ref_Init
****************************************************************************//**
*
*  Initialize/Restore the default Voltage Reference configuration as defined
*  in the customizer. If the reference is set to Vdda, it will enable all
*  Vdda-based references.
*
* \sideeffect
*  If the reference is Vdda-based, the function will enable all Vdda-based
*  references because they share the same resistor tree.
*
*******************************************************************************/
void engine_sensor_ref_Init(void)
{
    engine_sensor_ref_PRB_CTRL_REG |= engine_sensor_ref_PRB_CTRL_REG_INIT;
    engine_sensor_ref_PRB_REF_REG = engine_sensor_ref_PRB_REF_REG_INIT;
}


/*******************************************************************************
* Function Name: engine_sensor_ref_Enable
****************************************************************************//**
*
*  Enables the Voltage Reference.
*
*******************************************************************************/
void engine_sensor_ref_Enable(void)
{
    engine_sensor_ref_PRB_REF_REG |= engine_sensor_ref_VREF_ENABLE;
}


/*******************************************************************************
* Function Name: engine_sensor_ref_Start
****************************************************************************//**
*
*  Initializes all parameters required to setup the component as defined in the
*  customizer. If the reference is set to Vdda, it will enable all Vdda based
*  references.
*
* \globalvars
*  \ref engine_sensor_ref_initVar - This variable is used to indicate the initial
*  configuration of this component. The variable is initialized to zero and
*  set to 1 the first time engine_sensor_ref_Start() is called. This allows
*  the component initialization without re-initialization in all subsequent
*  calls to the engine_sensor_ref_Start() routine.
*
* \sideeffect
*  If the reference is Vdda-based, the function will enable all Vdda-based
*  references because they share the same resistor tree.
*
*******************************************************************************/
void engine_sensor_ref_Start(void)
{
    /* If not Initialized, then initialize all required hardware and software. */
    if (engine_sensor_ref_initVar == 0u)
    {
        engine_sensor_ref_initVar = 1u;
        engine_sensor_ref_Init();
    }

    engine_sensor_ref_Enable();
}


/*******************************************************************************
* Function Name: engine_sensor_ref_Stop
****************************************************************************//**
*
*  Disables the Voltage Reference.
*
*******************************************************************************/
void engine_sensor_ref_Stop(void)
{
    engine_sensor_ref_PRB_REF_REG &= ~engine_sensor_ref_VREF_ENABLE;
}


/*******************************************************************************
* Function Name: engine_sensor_ref_SetTap
****************************************************************************//**
*
*  Selects which of the equally spaced resistor divider taps will be used for
*  the reference. The output will range in 1/16th steps between Vref/16 to Vref.
*
*  \param
*  dividerTap:    One of the 16-tap voltage dividers to select a voltage
*                 between 1/16 of the reference source to the full reference
*                 source in steps of 1/16.
* * 1   :    1/16 Vref
* * ... :    ...
* * 16  :    Vref
*
*******************************************************************************/
void engine_sensor_ref_SetTap(uint32 dividerTap)
{
    engine_sensor_ref_PRB_REF_REG = (engine_sensor_ref_PRB_REF_REG & ~engine_sensor_ref_VREF_LEVEL_SEL_MASK) |
        (((dividerTap - 1u) << engine_sensor_ref_VREF_LEVEL_SEL_MASK_POS) & engine_sensor_ref_VREF_LEVEL_SEL_MASK);
}


/*******************************************************************************
* Function Name: engine_sensor_ref_SetVRefSrc
****************************************************************************//**
*
*  Selects whether the reference at the top of the resistor divider is based
*  on the bandgap or Vdda.
*
*  \param
*  reference:    The reference source.
* * engine_sensor_ref_BANDGAP_REFERENCE :    Bandgap reference
* * engine_sensor_ref_VDDA_REFERENCE    :    Vdda reference
*
* \sideeffect
*  If the reference is based on Vdda, it will affect all Vdda-based references
*  because they share the same resistor tree.
*
*******************************************************************************/
void engine_sensor_ref_SetVRefSrc(uint32 reference)
{
    if (engine_sensor_ref_BANDGAP_REFERENCE == reference)
    {
        engine_sensor_ref_PRB_REF_REG &= ~engine_sensor_ref_VREF_SUPPLY_SEL;
    }
    else /* Vdda reference source */
    {
        engine_sensor_ref_PRB_CTRL_REG |= engine_sensor_ref_VDDA_ENABLE;
        engine_sensor_ref_PRB_REF_REG |= engine_sensor_ref_VREF_SUPPLY_SEL;
    }
}


/* [] END OF FILE */
