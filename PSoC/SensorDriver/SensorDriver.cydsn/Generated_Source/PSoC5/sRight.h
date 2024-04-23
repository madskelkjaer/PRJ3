/*******************************************************************************
* File Name: sRight.h  
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

#if !defined(CY_PINS_sRight_H) /* Pins sRight_H */
#define CY_PINS_sRight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sRight_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sRight__PORT == 15 && ((sRight__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sRight_Write(uint8 value);
void    sRight_SetDriveMode(uint8 mode);
uint8   sRight_ReadDataReg(void);
uint8   sRight_Read(void);
void    sRight_SetInterruptMode(uint16 position, uint16 mode);
uint8   sRight_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sRight_SetDriveMode() function.
     *  @{
     */
        #define sRight_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sRight_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sRight_DM_RES_UP          PIN_DM_RES_UP
        #define sRight_DM_RES_DWN         PIN_DM_RES_DWN
        #define sRight_DM_OD_LO           PIN_DM_OD_LO
        #define sRight_DM_OD_HI           PIN_DM_OD_HI
        #define sRight_DM_STRONG          PIN_DM_STRONG
        #define sRight_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sRight_MASK               sRight__MASK
#define sRight_SHIFT              sRight__SHIFT
#define sRight_WIDTH              1u

/* Interrupt constants */
#if defined(sRight__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sRight_SetInterruptMode() function.
     *  @{
     */
        #define sRight_INTR_NONE      (uint16)(0x0000u)
        #define sRight_INTR_RISING    (uint16)(0x0001u)
        #define sRight_INTR_FALLING   (uint16)(0x0002u)
        #define sRight_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sRight_INTR_MASK      (0x01u) 
#endif /* (sRight__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sRight_PS                     (* (reg8 *) sRight__PS)
/* Data Register */
#define sRight_DR                     (* (reg8 *) sRight__DR)
/* Port Number */
#define sRight_PRT_NUM                (* (reg8 *) sRight__PRT) 
/* Connect to Analog Globals */                                                  
#define sRight_AG                     (* (reg8 *) sRight__AG)                       
/* Analog MUX bux enable */
#define sRight_AMUX                   (* (reg8 *) sRight__AMUX) 
/* Bidirectional Enable */                                                        
#define sRight_BIE                    (* (reg8 *) sRight__BIE)
/* Bit-mask for Aliased Register Access */
#define sRight_BIT_MASK               (* (reg8 *) sRight__BIT_MASK)
/* Bypass Enable */
#define sRight_BYP                    (* (reg8 *) sRight__BYP)
/* Port wide control signals */                                                   
#define sRight_CTL                    (* (reg8 *) sRight__CTL)
/* Drive Modes */
#define sRight_DM0                    (* (reg8 *) sRight__DM0) 
#define sRight_DM1                    (* (reg8 *) sRight__DM1)
#define sRight_DM2                    (* (reg8 *) sRight__DM2) 
/* Input Buffer Disable Override */
#define sRight_INP_DIS                (* (reg8 *) sRight__INP_DIS)
/* LCD Common or Segment Drive */
#define sRight_LCD_COM_SEG            (* (reg8 *) sRight__LCD_COM_SEG)
/* Enable Segment LCD */
#define sRight_LCD_EN                 (* (reg8 *) sRight__LCD_EN)
/* Slew Rate Control */
#define sRight_SLW                    (* (reg8 *) sRight__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sRight_PRTDSI__CAPS_SEL       (* (reg8 *) sRight__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sRight_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sRight__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sRight_PRTDSI__OE_SEL0        (* (reg8 *) sRight__PRTDSI__OE_SEL0) 
#define sRight_PRTDSI__OE_SEL1        (* (reg8 *) sRight__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sRight_PRTDSI__OUT_SEL0       (* (reg8 *) sRight__PRTDSI__OUT_SEL0) 
#define sRight_PRTDSI__OUT_SEL1       (* (reg8 *) sRight__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sRight_PRTDSI__SYNC_OUT       (* (reg8 *) sRight__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sRight__SIO_CFG)
    #define sRight_SIO_HYST_EN        (* (reg8 *) sRight__SIO_HYST_EN)
    #define sRight_SIO_REG_HIFREQ     (* (reg8 *) sRight__SIO_REG_HIFREQ)
    #define sRight_SIO_CFG            (* (reg8 *) sRight__SIO_CFG)
    #define sRight_SIO_DIFF           (* (reg8 *) sRight__SIO_DIFF)
#endif /* (sRight__SIO_CFG) */

/* Interrupt Registers */
#if defined(sRight__INTSTAT)
    #define sRight_INTSTAT            (* (reg8 *) sRight__INTSTAT)
    #define sRight_SNAP               (* (reg8 *) sRight__SNAP)
    
	#define sRight_0_INTTYPE_REG 		(* (reg8 *) sRight__0__INTTYPE)
#endif /* (sRight__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sRight_H */


/* [] END OF FILE */
