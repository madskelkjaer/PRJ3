/*******************************************************************************
* File Name: Limit_Right.h  
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

#if !defined(CY_PINS_Limit_Right_H) /* Pins Limit_Right_H */
#define CY_PINS_Limit_Right_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Limit_Right_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Limit_Right__PORT == 15 && ((Limit_Right__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Limit_Right_Write(uint8 value);
void    Limit_Right_SetDriveMode(uint8 mode);
uint8   Limit_Right_ReadDataReg(void);
uint8   Limit_Right_Read(void);
void    Limit_Right_SetInterruptMode(uint16 position, uint16 mode);
uint8   Limit_Right_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Limit_Right_SetDriveMode() function.
     *  @{
     */
        #define Limit_Right_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Limit_Right_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Limit_Right_DM_RES_UP          PIN_DM_RES_UP
        #define Limit_Right_DM_RES_DWN         PIN_DM_RES_DWN
        #define Limit_Right_DM_OD_LO           PIN_DM_OD_LO
        #define Limit_Right_DM_OD_HI           PIN_DM_OD_HI
        #define Limit_Right_DM_STRONG          PIN_DM_STRONG
        #define Limit_Right_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Limit_Right_MASK               Limit_Right__MASK
#define Limit_Right_SHIFT              Limit_Right__SHIFT
#define Limit_Right_WIDTH              1u

/* Interrupt constants */
#if defined(Limit_Right__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Limit_Right_SetInterruptMode() function.
     *  @{
     */
        #define Limit_Right_INTR_NONE      (uint16)(0x0000u)
        #define Limit_Right_INTR_RISING    (uint16)(0x0001u)
        #define Limit_Right_INTR_FALLING   (uint16)(0x0002u)
        #define Limit_Right_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Limit_Right_INTR_MASK      (0x01u) 
#endif /* (Limit_Right__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Limit_Right_PS                     (* (reg8 *) Limit_Right__PS)
/* Data Register */
#define Limit_Right_DR                     (* (reg8 *) Limit_Right__DR)
/* Port Number */
#define Limit_Right_PRT_NUM                (* (reg8 *) Limit_Right__PRT) 
/* Connect to Analog Globals */                                                  
#define Limit_Right_AG                     (* (reg8 *) Limit_Right__AG)                       
/* Analog MUX bux enable */
#define Limit_Right_AMUX                   (* (reg8 *) Limit_Right__AMUX) 
/* Bidirectional Enable */                                                        
#define Limit_Right_BIE                    (* (reg8 *) Limit_Right__BIE)
/* Bit-mask for Aliased Register Access */
#define Limit_Right_BIT_MASK               (* (reg8 *) Limit_Right__BIT_MASK)
/* Bypass Enable */
#define Limit_Right_BYP                    (* (reg8 *) Limit_Right__BYP)
/* Port wide control signals */                                                   
#define Limit_Right_CTL                    (* (reg8 *) Limit_Right__CTL)
/* Drive Modes */
#define Limit_Right_DM0                    (* (reg8 *) Limit_Right__DM0) 
#define Limit_Right_DM1                    (* (reg8 *) Limit_Right__DM1)
#define Limit_Right_DM2                    (* (reg8 *) Limit_Right__DM2) 
/* Input Buffer Disable Override */
#define Limit_Right_INP_DIS                (* (reg8 *) Limit_Right__INP_DIS)
/* LCD Common or Segment Drive */
#define Limit_Right_LCD_COM_SEG            (* (reg8 *) Limit_Right__LCD_COM_SEG)
/* Enable Segment LCD */
#define Limit_Right_LCD_EN                 (* (reg8 *) Limit_Right__LCD_EN)
/* Slew Rate Control */
#define Limit_Right_SLW                    (* (reg8 *) Limit_Right__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Limit_Right_PRTDSI__CAPS_SEL       (* (reg8 *) Limit_Right__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Limit_Right_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Limit_Right__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Limit_Right_PRTDSI__OE_SEL0        (* (reg8 *) Limit_Right__PRTDSI__OE_SEL0) 
#define Limit_Right_PRTDSI__OE_SEL1        (* (reg8 *) Limit_Right__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Limit_Right_PRTDSI__OUT_SEL0       (* (reg8 *) Limit_Right__PRTDSI__OUT_SEL0) 
#define Limit_Right_PRTDSI__OUT_SEL1       (* (reg8 *) Limit_Right__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Limit_Right_PRTDSI__SYNC_OUT       (* (reg8 *) Limit_Right__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Limit_Right__SIO_CFG)
    #define Limit_Right_SIO_HYST_EN        (* (reg8 *) Limit_Right__SIO_HYST_EN)
    #define Limit_Right_SIO_REG_HIFREQ     (* (reg8 *) Limit_Right__SIO_REG_HIFREQ)
    #define Limit_Right_SIO_CFG            (* (reg8 *) Limit_Right__SIO_CFG)
    #define Limit_Right_SIO_DIFF           (* (reg8 *) Limit_Right__SIO_DIFF)
#endif /* (Limit_Right__SIO_CFG) */

/* Interrupt Registers */
#if defined(Limit_Right__INTSTAT)
    #define Limit_Right_INTSTAT            (* (reg8 *) Limit_Right__INTSTAT)
    #define Limit_Right_SNAP               (* (reg8 *) Limit_Right__SNAP)
    
	#define Limit_Right_0_INTTYPE_REG 		(* (reg8 *) Limit_Right__0__INTTYPE)
#endif /* (Limit_Right__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Limit_Right_H */


/* [] END OF FILE */
