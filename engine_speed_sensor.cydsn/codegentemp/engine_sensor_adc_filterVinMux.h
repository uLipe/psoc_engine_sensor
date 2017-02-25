/*******************************************************************************
* File Name: engine_sensor_adc_filterVinMux.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_engine_sensor_adc_filterVinMux_H)
#define CY_AMUX_engine_sensor_adc_filterVinMux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void engine_sensor_adc_filterVinMux_Start(void) ;
#define engine_sensor_adc_filterVinMux_Init() engine_sensor_adc_filterVinMux_Start()
void engine_sensor_adc_filterVinMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void engine_sensor_adc_filterVinMux_Stop(void); */
/* void engine_sensor_adc_filterVinMux_Select(uint8 channel); */
/* void engine_sensor_adc_filterVinMux_Connect(uint8 channel); */
/* void engine_sensor_adc_filterVinMux_Disconnect(uint8 channel); */
/* void engine_sensor_adc_filterVinMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define engine_sensor_adc_filterVinMux_CHANNELS  4u
#define engine_sensor_adc_filterVinMux_MUXTYPE   1
#define engine_sensor_adc_filterVinMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define engine_sensor_adc_filterVinMux_NULL_CHANNEL 0xFFu
#define engine_sensor_adc_filterVinMux_MUX_SINGLE   1
#define engine_sensor_adc_filterVinMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if engine_sensor_adc_filterVinMux_MUXTYPE == engine_sensor_adc_filterVinMux_MUX_SINGLE
# if !engine_sensor_adc_filterVinMux_ATMOSTONE
#  define engine_sensor_adc_filterVinMux_Connect(channel) engine_sensor_adc_filterVinMux_Set(channel)
# endif
# define engine_sensor_adc_filterVinMux_Disconnect(channel) engine_sensor_adc_filterVinMux_Unset(channel)
#else
# if !engine_sensor_adc_filterVinMux_ATMOSTONE
void engine_sensor_adc_filterVinMux_Connect(uint8 channel) ;
# endif
void engine_sensor_adc_filterVinMux_Disconnect(uint8 channel) ;
#endif

#if engine_sensor_adc_filterVinMux_ATMOSTONE
# define engine_sensor_adc_filterVinMux_Stop() engine_sensor_adc_filterVinMux_DisconnectAll()
# define engine_sensor_adc_filterVinMux_Select(channel) engine_sensor_adc_filterVinMux_FastSelect(channel)
void engine_sensor_adc_filterVinMux_DisconnectAll(void) ;
#else
# define engine_sensor_adc_filterVinMux_Stop() engine_sensor_adc_filterVinMux_Start()
void engine_sensor_adc_filterVinMux_Select(uint8 channel) ;
# define engine_sensor_adc_filterVinMux_DisconnectAll() engine_sensor_adc_filterVinMux_Start()
#endif

#endif /* CY_AMUX_engine_sensor_adc_filterVinMux_H */


/* [] END OF FILE */
