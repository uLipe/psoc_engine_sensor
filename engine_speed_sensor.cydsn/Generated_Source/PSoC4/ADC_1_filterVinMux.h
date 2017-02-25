/*******************************************************************************
* File Name: ADC_1_filterVinMux.h
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

#if !defined(CY_AMUX_ADC_1_filterVinMux_H)
#define CY_AMUX_ADC_1_filterVinMux_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void ADC_1_filterVinMux_Start(void) ;
#define ADC_1_filterVinMux_Init() ADC_1_filterVinMux_Start()
void ADC_1_filterVinMux_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void ADC_1_filterVinMux_Stop(void); */
/* void ADC_1_filterVinMux_Select(uint8 channel); */
/* void ADC_1_filterVinMux_Connect(uint8 channel); */
/* void ADC_1_filterVinMux_Disconnect(uint8 channel); */
/* void ADC_1_filterVinMux_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define ADC_1_filterVinMux_CHANNELS  4u
#define ADC_1_filterVinMux_MUXTYPE   1
#define ADC_1_filterVinMux_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define ADC_1_filterVinMux_NULL_CHANNEL 0xFFu
#define ADC_1_filterVinMux_MUX_SINGLE   1
#define ADC_1_filterVinMux_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if ADC_1_filterVinMux_MUXTYPE == ADC_1_filterVinMux_MUX_SINGLE
# if !ADC_1_filterVinMux_ATMOSTONE
#  define ADC_1_filterVinMux_Connect(channel) ADC_1_filterVinMux_Set(channel)
# endif
# define ADC_1_filterVinMux_Disconnect(channel) ADC_1_filterVinMux_Unset(channel)
#else
# if !ADC_1_filterVinMux_ATMOSTONE
void ADC_1_filterVinMux_Connect(uint8 channel) ;
# endif
void ADC_1_filterVinMux_Disconnect(uint8 channel) ;
#endif

#if ADC_1_filterVinMux_ATMOSTONE
# define ADC_1_filterVinMux_Stop() ADC_1_filterVinMux_DisconnectAll()
# define ADC_1_filterVinMux_Select(channel) ADC_1_filterVinMux_FastSelect(channel)
void ADC_1_filterVinMux_DisconnectAll(void) ;
#else
# define ADC_1_filterVinMux_Stop() ADC_1_filterVinMux_Start()
void ADC_1_filterVinMux_Select(uint8 channel) ;
# define ADC_1_filterVinMux_DisconnectAll() ADC_1_filterVinMux_Start()
#endif

#endif /* CY_AMUX_ADC_1_filterVinMux_H */


/* [] END OF FILE */
