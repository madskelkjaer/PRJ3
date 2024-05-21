/*******************************************************************************
* File Name: sunRight.h  
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

#if !defined(CY_PINS_sunRight_H) /* Pins sunRight_H */
#define CY_PINS_sunRight_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sunRight_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sunRight__PORT == 15 && ((sunRight__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sunRight_Write(uint8 value);
void    sunRight_SetDriveMode(uint8 mode);
uint8   sunRight_ReadDataReg(void);
uint8   sunRight_Read(void);
void    sunRight_SetInterruptMode(uint16 position, uint16 mode);
uint8   sunRight_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sunRight_SetDriveMode() function.
     *  @{
     */
        #define sunRight_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sunRight_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sunRight_DM_RES_UP          PIN_DM_RES_UP
        #define sunRight_DM_RES_DWN         PIN_DM_RES_DWN
        #define sunRight_DM_OD_LO           PIN_DM_OD_LO
        #define sunRight_DM_OD_HI           PIN_DM_OD_HI
        #define sunRight_DM_STRONG          PIN_DM_STRONG
        #define sunRight_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sunRight_MASK               sunRight__MASK
#define sunRight_SHIFT              sunRight__SHIFT
#define sunRight_WIDTH              1u

/* Interrupt constants */
#if defined(sunRight__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sunRight_SetInterruptMode() function.
     *  @{
     */
        #define sunRight_INTR_NONE      (uint16)(0x0000u)
        #define sunRight_INTR_RISING    (uint16)(0x0001u)
        #define sunRight_INTR_FALLING   (uint16)(0x0002u)
        #define sunRight_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sunRight_INTR_MASK      (0x01u) 
#endif /* (sunRight__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sunRight_PS                     (* (reg8 *) sunRight__PS)
/* Data Register */
#define sunRight_DR                     (* (reg8 *) sunRight__DR)
/* Port Number */
#define sunRight_PRT_NUM                (* (reg8 *) sunRight__PRT) 
/* Connect to Analog Globals */                                                  
#define sunRight_AG                     (* (reg8 *) sunRight__AG)                       
/* Analog MUX bux enable */
#define sunRight_AMUX                   (* (reg8 *) sunRight__AMUX) 
/* Bidirectional Enable */                                                        
#define sunRight_BIE                    (* (reg8 *) sunRight__BIE)
/* Bit-mask for Aliased Register Access */
#define sunRight_BIT_MASK               (* (reg8 *) sunRight__BIT_MASK)
/* Bypass Enable */
#define sunRight_BYP                    (* (reg8 *) sunRight__BYP)
/* Port wide control signals */                                                   
#define sunRight_CTL                    (* (reg8 *) sunRight__CTL)
/* Drive Modes */
#define sunRight_DM0                    (* (reg8 *) sunRight__DM0) 
#define sunRight_DM1                    (* (reg8 *) sunRight__DM1)
#define sunRight_DM2                    (* (reg8 *) sunRight__DM2) 
/* Input Buffer Disable Override */
#define sunRight_INP_DIS                (* (reg8 *) sunRight__INP_DIS)
/* LCD Common or Segment Drive */
#define sunRight_LCD_COM_SEG            (* (reg8 *) sunRight__LCD_COM_SEG)
/* Enable Segment LCD */
#define sunRight_LCD_EN                 (* (reg8 *) sunRight__LCD_EN)
/* Slew Rate Control */
#define sunRight_SLW                    (* (reg8 *) sunRight__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sunRight_PRTDSI__CAPS_SEL       (* (reg8 *) sunRight__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sunRight_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sunRight__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sunRight_PRTDSI__OE_SEL0        (* (reg8 *) sunRight__PRTDSI__OE_SEL0) 
#define sunRight_PRTDSI__OE_SEL1        (* (reg8 *) sunRight__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sunRight_PRTDSI__OUT_SEL0       (* (reg8 *) sunRight__PRTDSI__OUT_SEL0) 
#define sunRight_PRTDSI__OUT_SEL1       (* (reg8 *) sunRight__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sunRight_PRTDSI__SYNC_OUT       (* (reg8 *) sunRight__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sunRight__SIO_CFG)
    #define sunRight_SIO_HYST_EN        (* (reg8 *) sunRight__SIO_HYST_EN)
    #define sunRight_SIO_REG_HIFREQ     (* (reg8 *) sunRight__SIO_REG_HIFREQ)
    #define sunRight_SIO_CFG            (* (reg8 *) sunRight__SIO_CFG)
    #define sunRight_SIO_DIFF           (* (reg8 *) sunRight__SIO_DIFF)
#endif /* (sunRight__SIO_CFG) */

/* Interrupt Registers */
#if defined(sunRight__INTSTAT)
    #define sunRight_INTSTAT            (* (reg8 *) sunRight__INTSTAT)
    #define sunRight_SNAP               (* (reg8 *) sunRight__SNAP)
    
	#define sunRight_0_INTTYPE_REG 		(* (reg8 *) sunRight__0__INTTYPE)
#endif /* (sunRight__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sunRight_H */


/* [] END OF FILE */
