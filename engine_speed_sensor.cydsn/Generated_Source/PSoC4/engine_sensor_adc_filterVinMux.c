/*******************************************************************************
* File Name: engine_sensor_adc_filterVinMux.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "engine_sensor_adc_filterVinMux.h"

static uint8 engine_sensor_adc_filterVinMux_lastChannel = engine_sensor_adc_filterVinMux_NULL_CHANNEL;


/*******************************************************************************
* Function Name: engine_sensor_adc_filterVinMux_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void engine_sensor_adc_filterVinMux_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < engine_sensor_adc_filterVinMux_CHANNELS ; chan++)
    {
#if (engine_sensor_adc_filterVinMux_MUXTYPE == engine_sensor_adc_filterVinMux_MUX_SINGLE)
        engine_sensor_adc_filterVinMux_Unset(chan);
#else
        engine_sensor_adc_filterVinMux_CYAMUXSIDE_A_Unset(chan);
        engine_sensor_adc_filterVinMux_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    engine_sensor_adc_filterVinMux_lastChannel = engine_sensor_adc_filterVinMux_NULL_CHANNEL;
}


#if (!engine_sensor_adc_filterVinMux_ATMOSTONE)
/*******************************************************************************
* Function Name: engine_sensor_adc_filterVinMux_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void engine_sensor_adc_filterVinMux_Select(uint8 channel) 
{
    engine_sensor_adc_filterVinMux_DisconnectAll();        /* Disconnect all previous connections */
    engine_sensor_adc_filterVinMux_Connect(channel);       /* Make the given selection */
    engine_sensor_adc_filterVinMux_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: engine_sensor_adc_filterVinMux_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void engine_sensor_adc_filterVinMux_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( engine_sensor_adc_filterVinMux_lastChannel != engine_sensor_adc_filterVinMux_NULL_CHANNEL)
    {
        engine_sensor_adc_filterVinMux_Disconnect(engine_sensor_adc_filterVinMux_lastChannel);
    }

    /* Make the new channel connection */
#if (engine_sensor_adc_filterVinMux_MUXTYPE == engine_sensor_adc_filterVinMux_MUX_SINGLE)
    engine_sensor_adc_filterVinMux_Set(channel);
#else
    engine_sensor_adc_filterVinMux_CYAMUXSIDE_A_Set(channel);
    engine_sensor_adc_filterVinMux_CYAMUXSIDE_B_Set(channel);
#endif


    engine_sensor_adc_filterVinMux_lastChannel = channel;   /* Update last channel */
}


#if (engine_sensor_adc_filterVinMux_MUXTYPE == engine_sensor_adc_filterVinMux_MUX_DIFF)
#if (!engine_sensor_adc_filterVinMux_ATMOSTONE)
/*******************************************************************************
* Function Name: engine_sensor_adc_filterVinMux_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void engine_sensor_adc_filterVinMux_Connect(uint8 channel) 
{
    engine_sensor_adc_filterVinMux_CYAMUXSIDE_A_Set(channel);
    engine_sensor_adc_filterVinMux_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: engine_sensor_adc_filterVinMux_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void engine_sensor_adc_filterVinMux_Disconnect(uint8 channel) 
{
    engine_sensor_adc_filterVinMux_CYAMUXSIDE_A_Unset(channel);
    engine_sensor_adc_filterVinMux_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (engine_sensor_adc_filterVinMux_ATMOSTONE)
/*******************************************************************************
* Function Name: engine_sensor_adc_filterVinMux_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void engine_sensor_adc_filterVinMux_DisconnectAll(void) 
{
    if(engine_sensor_adc_filterVinMux_lastChannel != engine_sensor_adc_filterVinMux_NULL_CHANNEL) 
    {
        engine_sensor_adc_filterVinMux_Disconnect(engine_sensor_adc_filterVinMux_lastChannel);
        engine_sensor_adc_filterVinMux_lastChannel = engine_sensor_adc_filterVinMux_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
