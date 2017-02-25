/*******************************************************************************
* File Name: filter_in_plus.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "filter_in_plus.h"

static filter_in_plus_BACKUP_STRUCT  filter_in_plus_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: filter_in_plus_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet filter_in_plus_SUT.c usage_filter_in_plus_Sleep_Wakeup
*******************************************************************************/
void filter_in_plus_Sleep(void)
{
    #if defined(filter_in_plus__PC)
        filter_in_plus_backup.pcState = filter_in_plus_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            filter_in_plus_backup.usbState = filter_in_plus_CR1_REG;
            filter_in_plus_USB_POWER_REG |= filter_in_plus_USBIO_ENTER_SLEEP;
            filter_in_plus_CR1_REG &= filter_in_plus_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(filter_in_plus__SIO)
        filter_in_plus_backup.sioState = filter_in_plus_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        filter_in_plus_SIO_REG &= (uint32)(~filter_in_plus_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: filter_in_plus_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to filter_in_plus_Sleep() for an example usage.
*******************************************************************************/
void filter_in_plus_Wakeup(void)
{
    #if defined(filter_in_plus__PC)
        filter_in_plus_PC = filter_in_plus_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            filter_in_plus_USB_POWER_REG &= filter_in_plus_USBIO_EXIT_SLEEP_PH1;
            filter_in_plus_CR1_REG = filter_in_plus_backup.usbState;
            filter_in_plus_USB_POWER_REG &= filter_in_plus_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(filter_in_plus__SIO)
        filter_in_plus_SIO_REG = filter_in_plus_backup.sioState;
    #endif
}


/* [] END OF FILE */
