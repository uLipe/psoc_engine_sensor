/*******************************************************************************
* File Name: engine_sensor_transfer.h
* Version 1.0
*
* Description:
*  This file contains all of the channel DMA API functions.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "engine_sensor_transfer.h"

uint8 engine_sensor_transfer_initVar = 0u;


/*******************************************************************************
* Function Name: engine_sensor_transfer_Start
********************************************************************************
*
* Summary:
*  Calls Init() to configure the DMA channel based on the customizer settings if
*  the channel has not been initialized before.
*  Sets source and destination address, validates descriptor 0 and enables the
*  channel. After calling this function the DMA channel is active and waiting
*  for a trigger.
*
* Parameters:
*  srcAddress: Address of DMA transfer source for descriptor 0.
*  dstAddress: Address of DMA transfer destination for descriptor 0.
*                   
* Return:
*  None.
*
*******************************************************************************/
void engine_sensor_transfer_Start(void * srcAddress, void * dstAddress)
{
    if(0u == engine_sensor_transfer_initVar)
    {
        engine_sensor_transfer_Init();
        engine_sensor_transfer_initVar = 1u;
    }
    CyDmaEnable();
    engine_sensor_transfer_SetSrcAddress(0, srcAddress);
    engine_sensor_transfer_SetDstAddress(0, dstAddress);
    engine_sensor_transfer_ValidateDescriptor(0);
    engine_sensor_transfer_ChEnable();
}


/*******************************************************************************
* Function Name: engine_sensor_transfer_Init
********************************************************************************
*
* Summary:
*  Initializes the DMA channel based on the parameters set in the component
*  customizer. It is not necessary to call engine_sensor_transfer_Init() because the
*  engine_sensor_transfer_Start() API calls this function, which is the preferred method
*  to begin component operation.
*
* Parameters:
*  None.
*                   
* Return:
*  None.
*
* Side effect:
*  The first descriptor is set to descriptor 0. This function should not be
*  called while the channel is enabled. All settings will be reset to their
*  initial values.
*
*******************************************************************************/
void engine_sensor_transfer_Init(void)
{
    CYDMA_CH_CTL_BASE.ctl[engine_sensor_transfer_CHANNEL] = engine_sensor_transfer_CHANNEL_CFG;
    CYDMA_DESCR_BASE.descriptor[engine_sensor_transfer_CHANNEL][0].ctl = engine_sensor_transfer_DESCR0_CFG;
    CYDMA_DESCR_BASE.descriptor[engine_sensor_transfer_CHANNEL][1].ctl = engine_sensor_transfer_DESCR1_CFG;

    /* If the Generate IRQ option is selected for descriptor 0 or 1, set the
    * channel bit field in the DMA interrupt mask register.
    */
    #if (0u != ((engine_sensor_transfer_DESCR0_CFG | engine_sensor_transfer_DESCR1_CFG) & CYDMA_GENERATE_IRQ))
        CYDMA_INTR_MASK_REG |= engine_sensor_transfer_CHANNEL_MASK;
    #endif /* (0u != ((engine_sensor_transfer_DESCR0_CFG | engine_sensor_transfer_DESCR1_CFG) & CYDMA_GENERATE_IRQ)) */
}


/* [] END OF FILE */
