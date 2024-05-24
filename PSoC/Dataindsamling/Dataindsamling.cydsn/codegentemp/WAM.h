/*******************************************************************************
* File Name: WAM.h  
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

#if !defined(CY_PINS_WAM_H) /* Pins WAM_H */
#define CY_PINS_WAM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "WAM_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 WAM__PORT == 15 && ((WAM__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    WAM_Write(uint8 value);
void    WAM_SetDriveMode(uint8 mode);
uint8   WAM_ReadDataReg(void);
uint8   WAM_Read(void);
void    WAM_SetInterruptMode(uint16 position, uint16 mode);
uint8   WAM_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the WAM_SetDriveMode() function.
     *  @{
     */
        #define WAM_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define WAM_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define WAM_DM_RES_UP          PIN_DM_RES_UP
        #define WAM_DM_RES_DWN         PIN_DM_RES_DWN
        #define WAM_DM_OD_LO           PIN_DM_OD_LO
        #define WAM_DM_OD_HI           PIN_DM_OD_HI
        #define WAM_DM_STRONG          PIN_DM_STRONG
        #define WAM_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define WAM_MASK               WAM__MASK
#define WAM_SHIFT              WAM__SHIFT
#define WAM_WIDTH              1u

/* Interrupt constants */
#if defined(WAM__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WAM_SetInterruptMode() function.
     *  @{
     */
        #define WAM_INTR_NONE      (uint16)(0x0000u)
        #define WAM_INTR_RISING    (uint16)(0x0001u)
        #define WAM_INTR_FALLING   (uint16)(0x0002u)
        #define WAM_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define WAM_INTR_MASK      (0x01u) 
#endif /* (WAM__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define WAM_PS                     (* (reg8 *) WAM__PS)
/* Data Register */
#define WAM_DR                     (* (reg8 *) WAM__DR)
/* Port Number */
#define WAM_PRT_NUM                (* (reg8 *) WAM__PRT) 
/* Connect to Analog Globals */                                                  
#define WAM_AG                     (* (reg8 *) WAM__AG)                       
/* Analog MUX bux enable */
#define WAM_AMUX                   (* (reg8 *) WAM__AMUX) 
/* Bidirectional Enable */                                                        
#define WAM_BIE                    (* (reg8 *) WAM__BIE)
/* Bit-mask for Aliased Register Access */
#define WAM_BIT_MASK               (* (reg8 *) WAM__BIT_MASK)
/* Bypass Enable */
#define WAM_BYP                    (* (reg8 *) WAM__BYP)
/* Port wide control signals */                                                   
#define WAM_CTL                    (* (reg8 *) WAM__CTL)
/* Drive Modes */
#define WAM_DM0                    (* (reg8 *) WAM__DM0) 
#define WAM_DM1                    (* (reg8 *) WAM__DM1)
#define WAM_DM2                    (* (reg8 *) WAM__DM2) 
/* Input Buffer Disable Override */
#define WAM_INP_DIS                (* (reg8 *) WAM__INP_DIS)
/* LCD Common or Segment Drive */
#define WAM_LCD_COM_SEG            (* (reg8 *) WAM__LCD_COM_SEG)
/* Enable Segment LCD */
#define WAM_LCD_EN                 (* (reg8 *) WAM__LCD_EN)
/* Slew Rate Control */
#define WAM_SLW                    (* (reg8 *) WAM__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define WAM_PRTDSI__CAPS_SEL       (* (reg8 *) WAM__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define WAM_PRTDSI__DBL_SYNC_IN    (* (reg8 *) WAM__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define WAM_PRTDSI__OE_SEL0        (* (reg8 *) WAM__PRTDSI__OE_SEL0) 
#define WAM_PRTDSI__OE_SEL1        (* (reg8 *) WAM__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define WAM_PRTDSI__OUT_SEL0       (* (reg8 *) WAM__PRTDSI__OUT_SEL0) 
#define WAM_PRTDSI__OUT_SEL1       (* (reg8 *) WAM__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define WAM_PRTDSI__SYNC_OUT       (* (reg8 *) WAM__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(WAM__SIO_CFG)
    #define WAM_SIO_HYST_EN        (* (reg8 *) WAM__SIO_HYST_EN)
    #define WAM_SIO_REG_HIFREQ     (* (reg8 *) WAM__SIO_REG_HIFREQ)
    #define WAM_SIO_CFG            (* (reg8 *) WAM__SIO_CFG)
    #define WAM_SIO_DIFF           (* (reg8 *) WAM__SIO_DIFF)
#endif /* (WAM__SIO_CFG) */

/* Interrupt Registers */
#if defined(WAM__INTSTAT)
    #define WAM_INTSTAT            (* (reg8 *) WAM__INTSTAT)
    #define WAM_SNAP               (* (reg8 *) WAM__SNAP)
    
	#define WAM_0_INTTYPE_REG 		(* (reg8 *) WAM__0__INTTYPE)
#endif /* (WAM__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_WAM_H */


/* [] END OF FILE */
