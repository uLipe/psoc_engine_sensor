/***************************************************************************//**
* \file     engine_sensor_pga.c
* \version  1.0
*
* \brief
*  This file provides the source code to the API for the PGA_P4 Component
*
********************************************************************************
* \copyright
* Copyright 2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "engine_sensor_pga_PVT.h"


uint8 engine_sensor_pga_initVar = 0u; /**< Describes the init state of the component */

uint32 engine_sensor_pga_internalGainPower = 0u; /**< Stores component Gain, Power and Enable values */

/***************************************************************************//**
* Compensation table 
*
* There is a feedback compensation capacitor recomended setting (for certain 
* gain and power setting) under the mask 0x0F000000u
* or (engine_sensor_pga_C_FB_MASK)
*
* Also there is an OpAmp compensation recomended setting (for certain 
* gain and power setting) under the mask 0x00000003u
* or (engine_sensor_pga_GET_OA_COMP_TRIM)
*
* There is only 6 values for whole gain range because the recommended 
* values are for each pair of adjacent gain values, e.g.:
* the first (index = 0) value is for gain = 1 and 1.4,
* the second (index = 1) value is for gain = 2 and 2.8,and so on,
* and the sixth (index = 5) value is for gain = 32 only.
*******************************************************************************/
const uint32 engine_sensor_pga_compTab[engine_sensor_pga_COMP_TAB_HEIGHT][engine_sensor_pga_COMP_TAB_WIDTH] =
{
#if (engine_sensor_pga_CHECK_OUTPUT_MODE) /* Class AB */
    {0x0F000002u, 0x0F000002u, 0x0F000002u},
    {0x07000002u, 0x09000002u, 0x09000002u},
    {0x04000002u, 0x04000002u, 0x04000002u},
    {0x03000001u, 0x02000002u, 0x03000002u},
    {0x01000001u, 0x00000002u, 0x00000002u},
    {0x01000001u, 0x01000001u, 0x02000001u}
#else /* Class A */
    {0x0F000002u, 0x0F000002u, 0x0F000002u},
    {0x08000002u, 0x09000002u, 0x09000002u},
    {0x03000001u, 0x05000002u, 0x04000002u},
    {0x00000001u, 0x02000002u, 0x03000002u},
    {0x00000001u, 0x00000002u, 0x01000002u},
    {0x00000001u, 0x00000001u, 0x00000001u}
#endif /* engine_sensor_pga_OUTPUT_MODE */
};


/*******************************************************************************   
* Function Name: engine_sensor_pga_Init
****************************************************************************//**
*
*  Initializes component's parameters to the values set by user in the 
*  customizer of the component placed onto schematic. Usually it is called in 
*  engine_sensor_pga_Start().
*
*******************************************************************************/
void engine_sensor_pga_Init(void)
{
    /* Set default internal variable value */
    engine_sensor_pga_internalGainPower = engine_sensor_pga_DEFAULT_GAIN_POWER;
    
    /* Set default register values */
    engine_sensor_pga_CTB_CTRL_REG |= engine_sensor_pga_DEFAULT_CTB_CTRL;
    engine_sensor_pga_OA_RES_CTRL_REG &= (uint32) ~engine_sensor_pga_DEFAULT_OA_RES_CTRL_MASK;
    engine_sensor_pga_OA_RES_CTRL_REG |= engine_sensor_pga_DEFAULT_OA_RES_CTRL;
    
    #if (engine_sensor_pga_VREF_MODE == engine_sensor_pga_VREF_INTERNAL)
        /* Configure resistor matrix bottom to the internal Vss */
        engine_sensor_pga_OA_SW_REG |= engine_sensor_pga_RBOT_TO_VSSA;
    #endif /* Vref Internal */
    
    /* Check if component has been enabled */
    if((engine_sensor_pga_OA_RES_CTRL_REG & engine_sensor_pga_OA_PWR_MODE_MASK) != 0u)
    {
        /* Set the default power level */
        engine_sensor_pga_Enable();
    }
    
    /* Set default gain and correspondent Cfb and OA_trim values */
    engine_sensor_pga_SetGain(engine_sensor_pga_GAIN);
}


/*******************************************************************************   
* Function Name: engine_sensor_pga_Enable
****************************************************************************//**
*
*  Powers up amplifier (to default power level or restored after 
*  previous engine_sensor_pga_Stop() call).
*  Usually it is called in engine_sensor_pga_Start().
*  
*******************************************************************************/
void engine_sensor_pga_Enable(void)
{
    engine_sensor_pga_OA_RES_CTRL_REG |= engine_sensor_pga_GET_POWER;
}


/*******************************************************************************
* Function Name: engine_sensor_pga_Start
****************************************************************************//**
*
*  Enables the amplifier operation (calls engine_sensor_pga_Enable).
*  Also on the first call (after the system reset) initializes all the component
*  related registers with default values (calls engine_sensor_pga_Init).
*
*  \globalvars
*   The engine_sensor_pga_initVar variable is used to indicate initial
*   configuration of this component. The variable is initialized to zero (0u)
*   and set to one (1u) at the first time engine_sensor_pga_Start() is called.
*   This allows to enable the component without re-initialization in all
*   subsequent calls of the engine_sensor_pga_Start() routine.
*
*******************************************************************************/
void engine_sensor_pga_Start(void)
{
    if(engine_sensor_pga_initVar == 0u)
    {
        engine_sensor_pga_Init();
        engine_sensor_pga_initVar = 1u;
    }

    engine_sensor_pga_Enable();
}


/*******************************************************************************
* Function Name: engine_sensor_pga_Stop
****************************************************************************//**
*
*  Powers down the amplifier.
*
*******************************************************************************/
void engine_sensor_pga_Stop(void)
{ 
    engine_sensor_pga_OA_RES_CTRL_REG &= (uint32)~engine_sensor_pga_OA_PWR_MODE_MASK;
}


/*******************************************************************************
* Function Name: engine_sensor_pga_SetPower
****************************************************************************//**
*
*  Sets the power level of amplifier.
*
* \param powerLevel
*  The power level setting of amplifier. Possible values:
*   * engine_sensor_pga_LOW - The lowest power consumption.
*   * engine_sensor_pga_MED - The middle setting.
*   * engine_sensor_pga_HIGH - The highest amplifier bandwidth.
*
*  \internal
*   The engine_sensor_pga_internalGainPower variable is used to store the
*   current gain and power level to set appropriate compensation settings.
*
*******************************************************************************/
void engine_sensor_pga_SetPower(uint32 powerLevel)
{
    uint32 locTmp;
    
    /* Save the powerLevel */
    engine_sensor_pga_internalGainPower &= (uint32) ~engine_sensor_pga_OA_PWR_MODE_MASK;
    engine_sensor_pga_internalGainPower |= powerLevel & engine_sensor_pga_OA_PWR_MODE_MASK;
    
    /* Save the rest of register bitfields */
    locTmp = engine_sensor_pga_OA_RES_CTRL_REG &
        (uint32)~(engine_sensor_pga_OA_PWR_MODE_MASK | engine_sensor_pga_C_FB_MASK);
           
    /* Set the power and the feedback capacitor values into the control register */
    engine_sensor_pga_OA_RES_CTRL_REG  = locTmp | engine_sensor_pga_GET_POWER | engine_sensor_pga_GET_C_FB;
    
    /* Set the OA compensation capacitor value */
    engine_sensor_pga_OA_COMP_TRIM_REG = engine_sensor_pga_GET_OA_COMP_TRIM;
}


/*******************************************************************************
* Function Name: engine_sensor_pga_SetGain
****************************************************************************//**
*
*  Sets values of the input and feedback resistors to set a 
*  specific gain of the amplifier.
*
* \param gainLevel
*  The gain setting of amplifier. Possible values:
*   * engine_sensor_pga_GAIN_1    - gain 1.0.
*   * engine_sensor_pga_GAIN_1_4  - gain 1.4.
*   * engine_sensor_pga_GAIN_2    - gain 2.0.
*   * engine_sensor_pga_GAIN_2_8  - gain 2.8.
*   * engine_sensor_pga_GAIN_4    - gain 4.0.
*   * engine_sensor_pga_GAIN_5_8  - gain 5.8.
*   * engine_sensor_pga_GAIN_8    - gain 8.0.
*   * engine_sensor_pga_GAIN_10_7 - gain 10.7.
*   * engine_sensor_pga_GAIN_16   - gain 16.0
*   * engine_sensor_pga_GAIN_21_3 - gain 21.3.
*   * engine_sensor_pga_GAIN_32   - gain 32.0.
*
*  \internal
*   The engine_sensor_pga_internalGainPower variable is used to store the
*   current gain and power level to set appropriate compensation settings.
*
*******************************************************************************/
void engine_sensor_pga_SetGain(uint32 gainLevel)
{
    uint32 locTmp;
    
    /* Save the gainLevel */
    engine_sensor_pga_internalGainPower &= (uint32) ~engine_sensor_pga_RES_TAP_MASK;
    engine_sensor_pga_internalGainPower |= ((uint32)(gainLevel << engine_sensor_pga_RES_TAP_SHIFT)) &
                                                                 engine_sensor_pga_RES_TAP_MASK;
    /* Save the rest of register bitfields */
    locTmp = engine_sensor_pga_OA_RES_CTRL_REG &
        (uint32)~(engine_sensor_pga_RES_TAP_MASK | engine_sensor_pga_C_FB_MASK);
    
    /* Set the gain and the feedback capacitor values into the control register */
    engine_sensor_pga_OA_RES_CTRL_REG = locTmp | (engine_sensor_pga_internalGainPower &
        engine_sensor_pga_RES_TAP_MASK) | engine_sensor_pga_GET_C_FB;
    
    /* Set the OA compensation capacitor value */
    engine_sensor_pga_OA_COMP_TRIM_REG = engine_sensor_pga_GET_OA_COMP_TRIM;
}


/*******************************************************************************
* Function Name: engine_sensor_pga_PumpControl
****************************************************************************//**
*
*  Allows the user to turn the amplifier's boost pump on or off.
*  By Default the engine_sensor_pga_Init() function turns the pump on.
*  
* \param onOff
*  The boost pump setting. Possible values:
*   * engine_sensor_pga_BOOST_OFF - Turn off the pump.
*   * engine_sensor_pga_BOOST_ON  - Turn on the pump.
*
**********************************************************************************/
void engine_sensor_pga_PumpControl(uint32 onOff)
{
    if(onOff == engine_sensor_pga_BOOST_ON)
    {
        engine_sensor_pga_OA_RES_CTRL_REG |= engine_sensor_pga_OA_PUMP_EN;
    }
    else
    {
        engine_sensor_pga_OA_RES_CTRL_REG &= (uint32)~engine_sensor_pga_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
