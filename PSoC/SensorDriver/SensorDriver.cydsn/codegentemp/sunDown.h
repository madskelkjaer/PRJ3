/*******************************************************************************
* File Name: sunDown.h  
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

#if !defined(CY_PINS_sunDown_H) /* Pins sunDown_H */
#define CY_PINS_sunDown_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "sunDown_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 sunDown__PORT == 15 && ((sunDown__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    sunDown_Write(uint8 value);
void    sunDown_SetDriveMode(uint8 mode);
uint8   sunDown_ReadDataReg(void);
uint8   sunDown_Read(void);
void    sunDown_SetInterruptMode(uint16 position, uint16 mode);
uint8   sunDown_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the sunDown_SetDriveMode() function.
     *  @{
     */
        #define sunDown_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define sunDown_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define sunDown_DM_RES_UP          PIN_DM_RES_UP
        #define sunDown_DM_RES_DWN         PIN_DM_RES_DWN
        #define sunDown_DM_OD_LO           PIN_DM_OD_LO
        #define sunDown_DM_OD_HI           PIN_DM_OD_HI
        #define sunDown_DM_STRONG          PIN_DM_STRONG
        #define sunDown_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define sunDown_MASK               sunDown__MASK
#define sunDown_SHIFT              sunDown__SHIFT
#define sunDown_WIDTH              1u

/* Interrupt constants */
#if defined(sunDown__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in sunDown_SetInterruptMode() function.
     *  @{
     */
        #define sunDown_INTR_NONE      (uint16)(0x0000u)
        #define sunDown_INTR_RISING    (uint16)(0x0001u)
        #define sunDown_INTR_FALLING   (uint16)(0x0002u)
        #define sunDown_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define sunDown_INTR_MASK      (0x01u) 
#endif /* (sunDown__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define sunDown_PS                     (* (reg8 *) sunDown__PS)
/* Data Register */
#define sunDown_DR                     (* (reg8 *) sunDown__DR)
/* Port Number */
#define sunDown_PRT_NUM                (* (reg8 *) sunDown__PRT) 
/* Connect to Analog Globals */                                                  
#define sunDown_AG                     (* (reg8 *) sunDown__AG)                       
/* Analog MUX bux enable */
#define sunDown_AMUX                   (* (reg8 *) sunDown__AMUX) 
/* Bidirectional Enable */                                                        
#define sunDown_BIE                    (* (reg8 *) sunDown__BIE)
/* Bit-mask for Aliased Register Access */
#define sunDown_BIT_MASK               (* (reg8 *) sunDown__BIT_MASK)
/* Bypass Enable */
#define sunDown_BYP                    (* (reg8 *) sunDown__BYP)
/* Port wide control signals */                                                   
#define sunDown_CTL                    (* (reg8 *) sunDown__CTL)
/* Drive Modes */
#define sunDown_DM0                    (* (reg8 *) sunDown__DM0) 
#define sunDown_DM1                    (* (reg8 *) sunDown__DM1)
#define sunDown_DM2                    (* (reg8 *) sunDown__DM2) 
/* Input Buffer Disable Override */
#define sunDown_INP_DIS                (* (reg8 *) sunDown__INP_DIS)
/* LCD Common or Segment Drive */
#define sunDown_LCD_COM_SEG            (* (reg8 *) sunDown__LCD_COM_SEG)
/* Enable Segment LCD */
#define sunDown_LCD_EN                 (* (reg8 *) sunDown__LCD_EN)
/* Slew Rate Control */
#define sunDown_SLW                    (* (reg8 *) sunDown__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define sunDown_PRTDSI__CAPS_SEL       (* (reg8 *) sunDown__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define sunDown_PRTDSI__DBL_SYNC_IN    (* (reg8 *) sunDown__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define sunDown_PRTDSI__OE_SEL0        (* (reg8 *) sunDown__PRTDSI__OE_SEL0) 
#define sunDown_PRTDSI__OE_SEL1        (* (reg8 *) sunDown__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define sunDown_PRTDSI__OUT_SEL0       (* (reg8 *) sunDown__PRTDSI__OUT_SEL0) 
#define sunDown_PRTDSI__OUT_SEL1       (* (reg8 *) sunDown__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define sunDown_PRTDSI__SYNC_OUT       (* (reg8 *) sunDown__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(sunDown__SIO_CFG)
    #define sunDown_SIO_HYST_EN        (* (reg8 *) sunDown__SIO_HYST_EN)
    #define sunDown_SIO_REG_HIFREQ     (* (reg8 *) sunDown__SIO_REG_HIFREQ)
    #define sunDown_SIO_CFG            (* (reg8 *) sunDown__SIO_CFG)
    #define sunDown_SIO_DIFF           (* (reg8 *) sunDown__SIO_DIFF)
#endif /* (sunDown__SIO_CFG) */

/* Interrupt Registers */
#if defined(sunDown__INTSTAT)
    #define sunDown_INTSTAT            (* (reg8 *) sunDown__INTSTAT)
    #define sunDown_SNAP               (* (reg8 *) sunDown__SNAP)
    
	#define sunDown_0_INTTYPE_REG 		(* (reg8 *) sunDown__0__INTTYPE)
#endif /* (sunDown__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_sunDown_H */


/* [] END OF FILE */
