/*******************************************************************************
* File Name: sunUp.h  
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

#if !defined(CY_PINS_sunUp_H) /* Pins sunUp_H */
#define CY_PINS_sunUp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sunUp_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sunUp__PORT == 15 && ((sunUp__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sunUp_Write(uint8 value);
void    sunUp_SetDriveMode(uint8 mode);
uint8   sunUp_ReadDataReg(void);
uint8   sunUp_Read(void);
void    sunUp_SetInterruptMode(uint16 position, uint16 mode);
uint8   sunUp_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sunUp_SetDriveMode() function.
     *  @{
     */
        #define sunUp_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sunUp_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sunUp_DM_RES_UP          PIN_DM_RES_UP
        #define sunUp_DM_RES_DWN         PIN_DM_RES_DWN
        #define sunUp_DM_OD_LO           PIN_DM_OD_LO
        #define sunUp_DM_OD_HI           PIN_DM_OD_HI
        #define sunUp_DM_STRONG          PIN_DM_STRONG
        #define sunUp_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sunUp_MASK               sunUp__MASK
#define sunUp_SHIFT              sunUp__SHIFT
#define sunUp_WIDTH              1u

/* Interrupt constants */
#if defined(sunUp__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sunUp_SetInterruptMode() function.
     *  @{
     */
        #define sunUp_INTR_NONE      (uint16)(0x0000u)
        #define sunUp_INTR_RISING    (uint16)(0x0001u)
        #define sunUp_INTR_FALLING   (uint16)(0x0002u)
        #define sunUp_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sunUp_INTR_MASK      (0x01u) 
#endif /* (sunUp__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sunUp_PS                     (* (reg8 *) sunUp__PS)
/* Data Register */
#define sunUp_DR                     (* (reg8 *) sunUp__DR)
/* Port Number */
#define sunUp_PRT_NUM                (* (reg8 *) sunUp__PRT) 
/* Connect to Analog Globals */                                                  
#define sunUp_AG                     (* (reg8 *) sunUp__AG)                       
/* Analog MUX bux enable */
#define sunUp_AMUX                   (* (reg8 *) sunUp__AMUX) 
/* Bidirectional Enable */                                                        
#define sunUp_BIE                    (* (reg8 *) sunUp__BIE)
/* Bit-mask for Aliased Register Access */
#define sunUp_BIT_MASK               (* (reg8 *) sunUp__BIT_MASK)
/* Bypass Enable */
#define sunUp_BYP                    (* (reg8 *) sunUp__BYP)
/* Port wide control signals */                                                   
#define sunUp_CTL                    (* (reg8 *) sunUp__CTL)
/* Drive Modes */
#define sunUp_DM0                    (* (reg8 *) sunUp__DM0) 
#define sunUp_DM1                    (* (reg8 *) sunUp__DM1)
#define sunUp_DM2                    (* (reg8 *) sunUp__DM2) 
/* Input Buffer Disable Override */
#define sunUp_INP_DIS                (* (reg8 *) sunUp__INP_DIS)
/* LCD Common or Segment Drive */
#define sunUp_LCD_COM_SEG            (* (reg8 *) sunUp__LCD_COM_SEG)
/* Enable Segment LCD */
#define sunUp_LCD_EN                 (* (reg8 *) sunUp__LCD_EN)
/* Slew Rate Control */
#define sunUp_SLW                    (* (reg8 *) sunUp__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sunUp_PRTDSI__CAPS_SEL       (* (reg8 *) sunUp__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sunUp_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sunUp__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sunUp_PRTDSI__OE_SEL0        (* (reg8 *) sunUp__PRTDSI__OE_SEL0) 
#define sunUp_PRTDSI__OE_SEL1        (* (reg8 *) sunUp__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sunUp_PRTDSI__OUT_SEL0       (* (reg8 *) sunUp__PRTDSI__OUT_SEL0) 
#define sunUp_PRTDSI__OUT_SEL1       (* (reg8 *) sunUp__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sunUp_PRTDSI__SYNC_OUT       (* (reg8 *) sunUp__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sunUp__SIO_CFG)
    #define sunUp_SIO_HYST_EN        (* (reg8 *) sunUp__SIO_HYST_EN)
    #define sunUp_SIO_REG_HIFREQ     (* (reg8 *) sunUp__SIO_REG_HIFREQ)
    #define sunUp_SIO_CFG            (* (reg8 *) sunUp__SIO_CFG)
    #define sunUp_SIO_DIFF           (* (reg8 *) sunUp__SIO_DIFF)
#endif /* (sunUp__SIO_CFG) */

/* Interrupt Registers */
#if defined(sunUp__INTSTAT)
    #define sunUp_INTSTAT            (* (reg8 *) sunUp__INTSTAT)
    #define sunUp_SNAP               (* (reg8 *) sunUp__SNAP)
    
	#define sunUp_0_INTTYPE_REG 		(* (reg8 *) sunUp__0__INTTYPE)
#endif /* (sunUp__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sunUp_H */


/* [] END OF FILE */
