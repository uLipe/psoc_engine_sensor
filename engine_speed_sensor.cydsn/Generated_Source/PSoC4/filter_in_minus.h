/*******************************************************************************
* File Name: filter_in_minus.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_filter_in_minus_H) /* Pins filter_in_minus_H */
#define CY_PINS_filter_in_minus_H

#include "cytypes.h"
#include "cyfitter.h"
#include "filter_in_minus_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} filter_in_minus_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   filter_in_minus_Read(void);
void    filter_in_minus_Write(uint8 value);
uint8   filter_in_minus_ReadDataReg(void);
#if defined(filter_in_minus__PC) || (CY_PSOC4_4200L) 
    void    filter_in_minus_SetDriveMode(uint8 mode);
#endif
void    filter_in_minus_SetInterruptMode(uint16 position, uint16 mode);
uint8   filter_in_minus_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void filter_in_minus_Sleep(void); 
void filter_in_minus_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(filter_in_minus__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define filter_in_minus_DRIVE_MODE_BITS        (3)
    #define filter_in_minus_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - filter_in_minus_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the filter_in_minus_SetDriveMode() function.
         *  @{
         */
        #define filter_in_minus_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define filter_in_minus_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define filter_in_minus_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define filter_in_minus_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define filter_in_minus_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define filter_in_minus_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define filter_in_minus_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define filter_in_minus_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define filter_in_minus_MASK               filter_in_minus__MASK
#define filter_in_minus_SHIFT              filter_in_minus__SHIFT
#define filter_in_minus_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in filter_in_minus_SetInterruptMode() function.
     *  @{
     */
        #define filter_in_minus_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define filter_in_minus_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define filter_in_minus_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define filter_in_minus_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(filter_in_minus__SIO)
    #define filter_in_minus_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(filter_in_minus__PC) && (CY_PSOC4_4200L)
    #define filter_in_minus_USBIO_ENABLE               ((uint32)0x80000000u)
    #define filter_in_minus_USBIO_DISABLE              ((uint32)(~filter_in_minus_USBIO_ENABLE))
    #define filter_in_minus_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define filter_in_minus_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define filter_in_minus_USBIO_ENTER_SLEEP          ((uint32)((1u << filter_in_minus_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << filter_in_minus_USBIO_SUSPEND_DEL_SHIFT)))
    #define filter_in_minus_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << filter_in_minus_USBIO_SUSPEND_SHIFT)))
    #define filter_in_minus_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << filter_in_minus_USBIO_SUSPEND_DEL_SHIFT)))
    #define filter_in_minus_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(filter_in_minus__PC)
    /* Port Configuration */
    #define filter_in_minus_PC                 (* (reg32 *) filter_in_minus__PC)
#endif
/* Pin State */
#define filter_in_minus_PS                     (* (reg32 *) filter_in_minus__PS)
/* Data Register */
#define filter_in_minus_DR                     (* (reg32 *) filter_in_minus__DR)
/* Input Buffer Disable Override */
#define filter_in_minus_INP_DIS                (* (reg32 *) filter_in_minus__PC2)

/* Interrupt configuration Registers */
#define filter_in_minus_INTCFG                 (* (reg32 *) filter_in_minus__INTCFG)
#define filter_in_minus_INTSTAT                (* (reg32 *) filter_in_minus__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define filter_in_minus_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(filter_in_minus__SIO)
    #define filter_in_minus_SIO_REG            (* (reg32 *) filter_in_minus__SIO)
#endif /* (filter_in_minus__SIO_CFG) */

/* USBIO registers */
#if !defined(filter_in_minus__PC) && (CY_PSOC4_4200L)
    #define filter_in_minus_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define filter_in_minus_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define filter_in_minus_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define filter_in_minus_DRIVE_MODE_SHIFT       (0x00u)
#define filter_in_minus_DRIVE_MODE_MASK        (0x07u << filter_in_minus_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins filter_in_minus_H */


/* [] END OF FILE */
