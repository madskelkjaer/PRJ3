/*******************************************************************************
* File Name: sDown.h  
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

#if !defined(CY_PINS_sDown_H) /* Pins sDown_H */
#define CY_PINS_sDown_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sDown_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sDown__PORT == 15 && ((sDown__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sDown_Write(uint8 value);
void    sDown_SetDriveMode(uint8 mode);
uint8   sDown_ReadDataReg(void);
uint8   sDown_Read(void);
void    sDown_SetInterruptMode(uint16 position, uint16 mode);
uint8   sDown_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sDown_SetDriveMode() function.
     *  @{
     */
        #define sDown_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sDown_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sDown_DM_RES_UP          PIN_DM_RES_UP
        #define sDown_DM_RES_DWN         PIN_DM_RES_DWN
        #define sDown_DM_OD_LO           PIN_DM_OD_LO
        #define sDown_DM_OD_HI           PIN_DM_OD_HI
        #define sDown_DM_STRONG          PIN_DM_STRONG
        #define sDown_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sDown_MASK               sDown__MASK
#define sDown_SHIFT              sDown__SHIFT
#define sDown_WIDTH              1u

/* Interrupt constants */
#if defined(sDown__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sDown_SetInterruptMode() function.
     *  @{
     */
        #define sDown_INTR_NONE      (uint16)(0x0000u)
        #define sDown_INTR_RISING    (uint16)(0x0001u)
        #define sDown_INTR_FALLING   (uint16)(0x0002u)
        #define sDown_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sDown_INTR_MASK      (0x01u) 
#endif /* (sDown__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sDown_PS                     (* (reg8 *) sDown__PS)
/* Data Register */
#define sDown_DR                     (* (reg8 *) sDown__DR)
/* Port Number */
#define sDown_PRT_NUM                (* (reg8 *) sDown__PRT) 
/* Connect to Analog Globals */                                                  
#define sDown_AG                     (* (reg8 *) sDown__AG)                       
/* Analog MUX bux enable */
#define sDown_AMUX                   (* (reg8 *) sDown__AMUX) 
/* Bidirectional Enable */                                                        
#define sDown_BIE                    (* (reg8 *) sDown__BIE)
/* Bit-mask for Aliased Register Access */
#define sDown_BIT_MASK               (* (reg8 *) sDown__BIT_MASK)
/* Bypass Enable */
#define sDown_BYP                    (* (reg8 *) sDown__BYP)
/* Port wide control signals */                                                   
#define sDown_CTL                    (* (reg8 *) sDown__CTL)
/* Drive Modes */
#define sDown_DM0                    (* (reg8 *) sDown__DM0) 
#define sDown_DM1                    (* (reg8 *) sDown__DM1)
#define sDown_DM2                    (* (reg8 *) sDown__DM2) 
/* Input Buffer Disable Override */
#define sDown_INP_DIS                (* (reg8 *) sDown__INP_DIS)
/* LCD Common or Segment Drive */
#define sDown_LCD_COM_SEG            (* (reg8 *) sDown__LCD_COM_SEG)
/* Enable Segment LCD */
#define sDown_LCD_EN                 (* (reg8 *) sDown__LCD_EN)
/* Slew Rate Control */
#define sDown_SLW                    (* (reg8 *) sDown__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sDown_PRTDSI__CAPS_SEL       (* (reg8 *) sDown__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sDown_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sDown__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sDown_PRTDSI__OE_SEL0        (* (reg8 *) sDown__PRTDSI__OE_SEL0) 
#define sDown_PRTDSI__OE_SEL1        (* (reg8 *) sDown__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sDown_PRTDSI__OUT_SEL0       (* (reg8 *) sDown__PRTDSI__OUT_SEL0) 
#define sDown_PRTDSI__OUT_SEL1       (* (reg8 *) sDown__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sDown_PRTDSI__SYNC_OUT       (* (reg8 *) sDown__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sDown__SIO_CFG)
    #define sDown_SIO_HYST_EN        (* (reg8 *) sDown__SIO_HYST_EN)
    #define sDown_SIO_REG_HIFREQ     (* (reg8 *) sDown__SIO_REG_HIFREQ)
    #define sDown_SIO_CFG            (* (reg8 *) sDown__SIO_CFG)
    #define sDown_SIO_DIFF           (* (reg8 *) sDown__SIO_DIFF)
#endif /* (sDown__SIO_CFG) */

/* Interrupt Registers */
#if defined(sDown__INTSTAT)
    #define sDown_INTSTAT            (* (reg8 *) sDown__INTSTAT)
    #define sDown_SNAP               (* (reg8 *) sDown__SNAP)
    
	#define sDown_0_INTTYPE_REG 		(* (reg8 *) sDown__0__INTTYPE)
#endif /* (sDown__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sDown_H */


/* [] END OF FILE */
