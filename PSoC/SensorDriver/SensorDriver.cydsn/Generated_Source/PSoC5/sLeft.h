/*******************************************************************************
* File Name: sLeft.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_sLeft_H) /* Pins sLeft_H */
#define CY_PINS_sLeft_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sLeft_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sLeft__PORT == 15 && ((sLeft__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sLeft_Write(uint8 value);
void    sLeft_SetDriveMode(uint8 mode);
uint8   sLeft_ReadDataReg(void);
uint8   sLeft_Read(void);
void    sLeft_SetInterruptMode(uint16 position, uint16 mode);
uint8   sLeft_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sLeft_SetDriveMode() function.
     *  @{
     */
        #define sLeft_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sLeft_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sLeft_DM_RES_UP          PIN_DM_RES_UP
        #define sLeft_DM_RES_DWN         PIN_DM_RES_DWN
        #define sLeft_DM_OD_LO           PIN_DM_OD_LO
        #define sLeft_DM_OD_HI           PIN_DM_OD_HI
        #define sLeft_DM_STRONG          PIN_DM_STRONG
        #define sLeft_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sLeft_MASK               sLeft__MASK
#define sLeft_SHIFT              sLeft__SHIFT
#define sLeft_WIDTH              1u

/* Interrupt constants */
#if defined(sLeft__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sLeft_SetInterruptMode() function.
     *  @{
     */
        #define sLeft_INTR_NONE      (uint16)(0x0000u)
        #define sLeft_INTR_RISING    (uint16)(0x0001u)
        #define sLeft_INTR_FALLING   (uint16)(0x0002u)
        #define sLeft_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sLeft_INTR_MASK      (0x01u) 
#endif /* (sLeft__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sLeft_PS                     (* (reg8 *) sLeft__PS)
/* Data Register */
#define sLeft_DR                     (* (reg8 *) sLeft__DR)
/* Port Number */
#define sLeft_PRT_NUM                (* (reg8 *) sLeft__PRT) 
/* Connect to Analog Globals */                                                  
#define sLeft_AG                     (* (reg8 *) sLeft__AG)                       
/* Analog MUX bux enable */
#define sLeft_AMUX                   (* (reg8 *) sLeft__AMUX) 
/* Bidirectional Enable */                                                        
#define sLeft_BIE                    (* (reg8 *) sLeft__BIE)
/* Bit-mask for Aliased Register Access */
#define sLeft_BIT_MASK               (* (reg8 *) sLeft__BIT_MASK)
/* Bypass Enable */
#define sLeft_BYP                    (* (reg8 *) sLeft__BYP)
/* Port wide control signals */                                                   
#define sLeft_CTL                    (* (reg8 *) sLeft__CTL)
/* Drive Modes */
#define sLeft_DM0                    (* (reg8 *) sLeft__DM0) 
#define sLeft_DM1                    (* (reg8 *) sLeft__DM1)
#define sLeft_DM2                    (* (reg8 *) sLeft__DM2) 
/* Input Buffer Disable Override */
#define sLeft_INP_DIS                (* (reg8 *) sLeft__INP_DIS)
/* LCD Common or Segment Drive */
#define sLeft_LCD_COM_SEG            (* (reg8 *) sLeft__LCD_COM_SEG)
/* Enable Segment LCD */
#define sLeft_LCD_EN                 (* (reg8 *) sLeft__LCD_EN)
/* Slew Rate Control */
#define sLeft_SLW                    (* (reg8 *) sLeft__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sLeft_PRTDSI__CAPS_SEL       (* (reg8 *) sLeft__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sLeft_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sLeft__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sLeft_PRTDSI__OE_SEL0        (* (reg8 *) sLeft__PRTDSI__OE_SEL0) 
#define sLeft_PRTDSI__OE_SEL1        (* (reg8 *) sLeft__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sLeft_PRTDSI__OUT_SEL0       (* (reg8 *) sLeft__PRTDSI__OUT_SEL0) 
#define sLeft_PRTDSI__OUT_SEL1       (* (reg8 *) sLeft__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sLeft_PRTDSI__SYNC_OUT       (* (reg8 *) sLeft__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sLeft__SIO_CFG)
    #define sLeft_SIO_HYST_EN        (* (reg8 *) sLeft__SIO_HYST_EN)
    #define sLeft_SIO_REG_HIFREQ     (* (reg8 *) sLeft__SIO_REG_HIFREQ)
    #define sLeft_SIO_CFG            (* (reg8 *) sLeft__SIO_CFG)
    #define sLeft_SIO_DIFF           (* (reg8 *) sLeft__SIO_DIFF)
#endif /* (sLeft__SIO_CFG) */

/* Interrupt Registers */
#if defined(sLeft__INTSTAT)
    #define sLeft_INTSTAT            (* (reg8 *) sLeft__INTSTAT)
    #define sLeft_SNAP               (* (reg8 *) sLeft__SNAP)
    
	#define sLeft_0_INTTYPE_REG 		(* (reg8 *) sLeft__0__INTTYPE)
#endif /* (sLeft__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sLeft_H */


/* [] END OF FILE */
