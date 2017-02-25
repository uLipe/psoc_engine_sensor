/*******************************************************************************
* File Name: engine_sensor_adc_INT.c
* Version 1.20
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2015-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "engine_sensor_adc.h"


/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START engine_sensor_adc_SYS_VAR`  */

/* `#END`  */

#if(engine_sensor_adc_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: engine_sensor_adc_ISR
    *******************************************************************************
    *
    * \brief Handle Interrupt Service Routine.
    *
    * \param None
    *
    * \return None
    *
    * \sideeffect None
    *
    ******************************************************************************/
    CY_ISR( engine_sensor_adc_ISR )
    {
        uint32 intr_status;

        /* Read interrupt status register */
        intr_status = engine_sensor_adc_SAR_INTR_REG;

        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
        /* `#START MAIN_engine_sensor_adc_ISR`  */

        /* `#END`  */

        /* Clear handled interrupt */
        engine_sensor_adc_SAR_INTR_REG = intr_status;
    }

#endif   /* End engine_sensor_adc_IRQ_REMOVE */


/* [] END OF FILE */
