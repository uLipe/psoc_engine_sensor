/*******************************************************************************
* File Name: engine_afe_bias.h  
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

#if !defined(CY_PINS_engine_afe_bias_H) /* Pins engine_afe_bias_H */
#define CY_PINS_engine_afe_bias_H

#include "cytypes.h"
#include "cyfitter.h"
#include "engine_afe_bias_aliases.h"


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
} engine_afe_bias_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   engine_afe_bias_Read(void);
void    engine_afe_bias_Write(uint8 value);
uint8   engine_afe_bias_ReadDataReg(void);
#if defined(engine_afe_bias__PC) || (CY_PSOC4_4200L) 
    void    engine_afe_bias_SetDriveMode(uint8 mode);
#endif
void    engine_afe_bias_SetInterruptMode(uint16 position, uint16 mode);
uint8   engine_afe_bias_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void engine_afe_bias_Sleep(void); 
void engine_afe_bias_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(engine_afe_bias__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define engine_afe_bias_DRIVE_MODE_BITS        (3)
    #define engine_afe_bias_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - engine_afe_bias_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the engine_afe_bias_SetDriveMode() function.
         *  @{
         */
        #define engine_afe_bias_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define engine_afe_bias_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define engine_afe_bias_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define engine_afe_bias_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define engine_afe_bias_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define engine_afe_bias_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define engine_afe_bias_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define engine_afe_bias_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define engine_afe_bias_MASK               engine_afe_bias__MASK
#define engine_afe_bias_SHIFT              engine_afe_bias__SHIFT
#define engine_afe_bias_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in engine_afe_bias_SetInterruptMode() function.
     *  @{
     */
        #define engine_afe_bias_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define engine_afe_bias_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define engine_afe_bias_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define engine_afe_bias_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(engine_afe_bias__SIO)
    #define engine_afe_bias_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(engine_afe_bias__PC) && (CY_PSOC4_4200L)
    #define engine_afe_bias_USBIO_ENABLE               ((uint32)0x80000000u)
    #define engine_afe_bias_USBIO_DISABLE              ((uint32)(~engine_afe_bias_USBIO_ENABLE))
    #define engine_afe_bias_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define engine_afe_bias_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define engine_afe_bias_USBIO_ENTER_SLEEP          ((uint32)((1u << engine_afe_bias_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << engine_afe_bias_USBIO_SUSPEND_DEL_SHIFT)))
    #define engine_afe_bias_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << engine_afe_bias_USBIO_SUSPEND_SHIFT)))
    #define engine_afe_bias_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << engine_afe_bias_USBIO_SUSPEND_DEL_SHIFT)))
    #define engine_afe_bias_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(engine_afe_bias__PC)
    /* Port Configuration */
    #define engine_afe_bias_PC                 (* (reg32 *) engine_afe_bias__PC)
#endif
/* Pin State */
#define engine_afe_bias_PS                     (* (reg32 *) engine_afe_bias__PS)
/* Data Register */
#define engine_afe_bias_DR                     (* (reg32 *) engine_afe_bias__DR)
/* Input Buffer Disable Override */
#define engine_afe_bias_INP_DIS                (* (reg32 *) engine_afe_bias__PC2)

/* Interrupt configuration Registers */
#define engine_afe_bias_INTCFG                 (* (reg32 *) engine_afe_bias__INTCFG)
#define engine_afe_bias_INTSTAT                (* (reg32 *) engine_afe_bias__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define engine_afe_bias_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(engine_afe_bias__SIO)
    #define engine_afe_bias_SIO_REG            (* (reg32 *) engine_afe_bias__SIO)
#endif /* (engine_afe_bias__SIO_CFG) */

/* USBIO registers */
#if !defined(engine_afe_bias__PC) && (CY_PSOC4_4200L)
    #define engine_afe_bias_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define engine_afe_bias_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define engine_afe_bias_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define engine_afe_bias_DRIVE_MODE_SHIFT       (0x00u)
#define engine_afe_bias_DRIVE_MODE_MASK        (0x07u << engine_afe_bias_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins engine_afe_bias_H */


/* [] END OF FILE */
