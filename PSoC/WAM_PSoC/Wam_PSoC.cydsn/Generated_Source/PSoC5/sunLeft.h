/*******************************************************************************
* File Name: sunLeft.h  
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

#if !defined(CY_PINS_sunLeft_H) /* Pins sunLeft_H */
#define CY_PINS_sunLeft_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sunLeft_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sunLeft__PORT == 15 && ((sunLeft__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sunLeft_Write(uint8 value);
void    sunLeft_SetDriveMode(uint8 mode);
uint8   sunLeft_ReadDataReg(void);
uint8   sunLeft_Read(void);
void    sunLeft_SetInterruptMode(uint16 position, uint16 mode);
uint8   sunLeft_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sunLeft_SetDriveMode() function.
     *  @{
     */
        #define sunLeft_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sunLeft_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sunLeft_DM_RES_UP          PIN_DM_RES_UP
        #define sunLeft_DM_RES_DWN         PIN_DM_RES_DWN
        #define sunLeft_DM_OD_LO           PIN_DM_OD_LO
        #define sunLeft_DM_OD_HI           PIN_DM_OD_HI
        #define sunLeft_DM_STRONG          PIN_DM_STRONG
        #define sunLeft_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sunLeft_MASK               sunLeft__MASK
#define sunLeft_SHIFT              sunLeft__SHIFT
#define sunLeft_WIDTH              1u

/* Interrupt constants */
#if defined(sunLeft__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sunLeft_SetInterruptMode() function.
     *  @{
     */
        #define sunLeft_INTR_NONE      (uint16)(0x0000u)
        #define sunLeft_INTR_RISING    (uint16)(0x0001u)
        #define sunLeft_INTR_FALLING   (uint16)(0x0002u)
        #define sunLeft_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sunLeft_INTR_MASK      (0x01u) 
#endif /* (sunLeft__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sunLeft_PS                     (* (reg8 *) sunLeft__PS)
/* Data Register */
#define sunLeft_DR                     (* (reg8 *) sunLeft__DR)
/* Port Number */
#define sunLeft_PRT_NUM                (* (reg8 *) sunLeft__PRT) 
/* Connect to Analog Globals */                                                  
#define sunLeft_AG                     (* (reg8 *) sunLeft__AG)                       
/* Analog MUX bux enable */
#define sunLeft_AMUX                   (* (reg8 *) sunLeft__AMUX) 
/* Bidirectional Enable */                                                        
#define sunLeft_BIE                    (* (reg8 *) sunLeft__BIE)
/* Bit-mask for Aliased Register Access */
#define sunLeft_BIT_MASK               (* (reg8 *) sunLeft__BIT_MASK)
/* Bypass Enable */
#define sunLeft_BYP                    (* (reg8 *) sunLeft__BYP)
/* Port wide control signals */                                                   
#define sunLeft_CTL                    (* (reg8 *) sunLeft__CTL)
/* Drive Modes */
#define sunLeft_DM0                    (* (reg8 *) sunLeft__DM0) 
#define sunLeft_DM1                    (* (reg8 *) sunLeft__DM1)
#define sunLeft_DM2                    (* (reg8 *) sunLeft__DM2) 
/* Input Buffer Disable Override */
#define sunLeft_INP_DIS                (* (reg8 *) sunLeft__INP_DIS)
/* LCD Common or Segment Drive */
#define sunLeft_LCD_COM_SEG            (* (reg8 *) sunLeft__LCD_COM_SEG)
/* Enable Segment LCD */
#define sunLeft_LCD_EN                 (* (reg8 *) sunLeft__LCD_EN)
/* Slew Rate Control */
#define sunLeft_SLW                    (* (reg8 *) sunLeft__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sunLeft_PRTDSI__CAPS_SEL       (* (reg8 *) sunLeft__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sunLeft_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sunLeft__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sunLeft_PRTDSI__OE_SEL0        (* (reg8 *) sunLeft__PRTDSI__OE_SEL0) 
#define sunLeft_PRTDSI__OE_SEL1        (* (reg8 *) sunLeft__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sunLeft_PRTDSI__OUT_SEL0       (* (reg8 *) sunLeft__PRTDSI__OUT_SEL0) 
#define sunLeft_PRTDSI__OUT_SEL1       (* (reg8 *) sunLeft__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sunLeft_PRTDSI__SYNC_OUT       (* (reg8 *) sunLeft__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sunLeft__SIO_CFG)
    #define sunLeft_SIO_HYST_EN        (* (reg8 *) sunLeft__SIO_HYST_EN)
    #define sunLeft_SIO_REG_HIFREQ     (* (reg8 *) sunLeft__SIO_REG_HIFREQ)
    #define sunLeft_SIO_CFG            (* (reg8 *) sunLeft__SIO_CFG)
    #define sunLeft_SIO_DIFF           (* (reg8 *) sunLeft__SIO_DIFF)
#endif /* (sunLeft__SIO_CFG) */

/* Interrupt Registers */
#if defined(sunLeft__INTSTAT)
    #define sunLeft_INTSTAT            (* (reg8 *) sunLeft__INTSTAT)
    #define sunLeft_SNAP               (* (reg8 *) sunLeft__SNAP)
    
	#define sunLeft_0_INTTYPE_REG 		(* (reg8 *) sunLeft__0__INTTYPE)
#endif /* (sunLeft__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sunLeft_H */


/* [] END OF FILE */
