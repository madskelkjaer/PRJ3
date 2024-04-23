/*******************************************************************************
* File Name: sUp.h  
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

#if !defined(CY_PINS_sUp_H) /* Pins sUp_H */
#define CY_PINS_sUp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sUp_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sUp__PORT == 15 && ((sUp__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sUp_Write(uint8 value);
void    sUp_SetDriveMode(uint8 mode);
uint8   sUp_ReadDataReg(void);
uint8   sUp_Read(void);
void    sUp_SetInterruptMode(uint16 position, uint16 mode);
uint8   sUp_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sUp_SetDriveMode() function.
     *  @{
     */
        #define sUp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sUp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sUp_DM_RES_UP          PIN_DM_RES_UP
        #define sUp_DM_RES_DWN         PIN_DM_RES_DWN
        #define sUp_DM_OD_LO           PIN_DM_OD_LO
        #define sUp_DM_OD_HI           PIN_DM_OD_HI
        #define sUp_DM_STRONG          PIN_DM_STRONG
        #define sUp_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sUp_MASK               sUp__MASK
#define sUp_SHIFT              sUp__SHIFT
#define sUp_WIDTH              1u

/* Interrupt constants */
#if defined(sUp__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sUp_SetInterruptMode() function.
     *  @{
     */
        #define sUp_INTR_NONE      (uint16)(0x0000u)
        #define sUp_INTR_RISING    (uint16)(0x0001u)
        #define sUp_INTR_FALLING   (uint16)(0x0002u)
        #define sUp_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sUp_INTR_MASK      (0x01u) 
#endif /* (sUp__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sUp_PS                     (* (reg8 *) sUp__PS)
/* Data Register */
#define sUp_DR                     (* (reg8 *) sUp__DR)
/* Port Number */
#define sUp_PRT_NUM                (* (reg8 *) sUp__PRT) 
/* Connect to Analog Globals */                                                  
#define sUp_AG                     (* (reg8 *) sUp__AG)                       
/* Analog MUX bux enable */
#define sUp_AMUX                   (* (reg8 *) sUp__AMUX) 
/* Bidirectional Enable */                                                        
#define sUp_BIE                    (* (reg8 *) sUp__BIE)
/* Bit-mask for Aliased Register Access */
#define sUp_BIT_MASK               (* (reg8 *) sUp__BIT_MASK)
/* Bypass Enable */
#define sUp_BYP                    (* (reg8 *) sUp__BYP)
/* Port wide control signals */                                                   
#define sUp_CTL                    (* (reg8 *) sUp__CTL)
/* Drive Modes */
#define sUp_DM0                    (* (reg8 *) sUp__DM0) 
#define sUp_DM1                    (* (reg8 *) sUp__DM1)
#define sUp_DM2                    (* (reg8 *) sUp__DM2) 
/* Input Buffer Disable Override */
#define sUp_INP_DIS                (* (reg8 *) sUp__INP_DIS)
/* LCD Common or Segment Drive */
#define sUp_LCD_COM_SEG            (* (reg8 *) sUp__LCD_COM_SEG)
/* Enable Segment LCD */
#define sUp_LCD_EN                 (* (reg8 *) sUp__LCD_EN)
/* Slew Rate Control */
#define sUp_SLW                    (* (reg8 *) sUp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sUp_PRTDSI__CAPS_SEL       (* (reg8 *) sUp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sUp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sUp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sUp_PRTDSI__OE_SEL0        (* (reg8 *) sUp__PRTDSI__OE_SEL0) 
#define sUp_PRTDSI__OE_SEL1        (* (reg8 *) sUp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sUp_PRTDSI__OUT_SEL0       (* (reg8 *) sUp__PRTDSI__OUT_SEL0) 
#define sUp_PRTDSI__OUT_SEL1       (* (reg8 *) sUp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sUp_PRTDSI__SYNC_OUT       (* (reg8 *) sUp__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sUp__SIO_CFG)
    #define sUp_SIO_HYST_EN        (* (reg8 *) sUp__SIO_HYST_EN)
    #define sUp_SIO_REG_HIFREQ     (* (reg8 *) sUp__SIO_REG_HIFREQ)
    #define sUp_SIO_CFG            (* (reg8 *) sUp__SIO_CFG)
    #define sUp_SIO_DIFF           (* (reg8 *) sUp__SIO_DIFF)
#endif /* (sUp__SIO_CFG) */

/* Interrupt Registers */
#if defined(sUp__INTSTAT)
    #define sUp_INTSTAT            (* (reg8 *) sUp__INTSTAT)
    #define sUp_SNAP               (* (reg8 *) sUp__SNAP)
    
	#define sUp_0_INTTYPE_REG 		(* (reg8 *) sUp__0__INTTYPE)
#endif /* (sUp__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sUp_H */


/* [] END OF FILE */
