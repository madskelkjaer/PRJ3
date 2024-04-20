/*******************************************************************************
* File Name: Azimuth_Limit_Up.h  
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

#if !defined(CY_PINS_Azimuth_Limit_Up_H) /* Pins Azimuth_Limit_Up_H */
#define CY_PINS_Azimuth_Limit_Up_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Azimuth_Limit_Up_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Azimuth_Limit_Up__PORT == 15 && ((Azimuth_Limit_Up__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Azimuth_Limit_Up_Write(uint8 value);
void    Azimuth_Limit_Up_SetDriveMode(uint8 mode);
uint8   Azimuth_Limit_Up_ReadDataReg(void);
uint8   Azimuth_Limit_Up_Read(void);
void    Azimuth_Limit_Up_SetInterruptMode(uint16 position, uint16 mode);
uint8   Azimuth_Limit_Up_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Azimuth_Limit_Up_SetDriveMode() function.
     *  @{
     */
        #define Azimuth_Limit_Up_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Azimuth_Limit_Up_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Azimuth_Limit_Up_DM_RES_UP          PIN_DM_RES_UP
        #define Azimuth_Limit_Up_DM_RES_DWN         PIN_DM_RES_DWN
        #define Azimuth_Limit_Up_DM_OD_LO           PIN_DM_OD_LO
        #define Azimuth_Limit_Up_DM_OD_HI           PIN_DM_OD_HI
        #define Azimuth_Limit_Up_DM_STRONG          PIN_DM_STRONG
        #define Azimuth_Limit_Up_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Azimuth_Limit_Up_MASK               Azimuth_Limit_Up__MASK
#define Azimuth_Limit_Up_SHIFT              Azimuth_Limit_Up__SHIFT
#define Azimuth_Limit_Up_WIDTH              1u

/* Interrupt constants */
#if defined(Azimuth_Limit_Up__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Azimuth_Limit_Up_SetInterruptMode() function.
     *  @{
     */
        #define Azimuth_Limit_Up_INTR_NONE      (uint16)(0x0000u)
        #define Azimuth_Limit_Up_INTR_RISING    (uint16)(0x0001u)
        #define Azimuth_Limit_Up_INTR_FALLING   (uint16)(0x0002u)
        #define Azimuth_Limit_Up_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Azimuth_Limit_Up_INTR_MASK      (0x01u) 
#endif /* (Azimuth_Limit_Up__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Azimuth_Limit_Up_PS                     (* (reg8 *) Azimuth_Limit_Up__PS)
/* Data Register */
#define Azimuth_Limit_Up_DR                     (* (reg8 *) Azimuth_Limit_Up__DR)
/* Port Number */
#define Azimuth_Limit_Up_PRT_NUM                (* (reg8 *) Azimuth_Limit_Up__PRT) 
/* Connect to Analog Globals */                                                  
#define Azimuth_Limit_Up_AG                     (* (reg8 *) Azimuth_Limit_Up__AG)                       
/* Analog MUX bux enable */
#define Azimuth_Limit_Up_AMUX                   (* (reg8 *) Azimuth_Limit_Up__AMUX) 
/* Bidirectional Enable */                                                        
#define Azimuth_Limit_Up_BIE                    (* (reg8 *) Azimuth_Limit_Up__BIE)
/* Bit-mask for Aliased Register Access */
#define Azimuth_Limit_Up_BIT_MASK               (* (reg8 *) Azimuth_Limit_Up__BIT_MASK)
/* Bypass Enable */
#define Azimuth_Limit_Up_BYP                    (* (reg8 *) Azimuth_Limit_Up__BYP)
/* Port wide control signals */                                                   
#define Azimuth_Limit_Up_CTL                    (* (reg8 *) Azimuth_Limit_Up__CTL)
/* Drive Modes */
#define Azimuth_Limit_Up_DM0                    (* (reg8 *) Azimuth_Limit_Up__DM0) 
#define Azimuth_Limit_Up_DM1                    (* (reg8 *) Azimuth_Limit_Up__DM1)
#define Azimuth_Limit_Up_DM2                    (* (reg8 *) Azimuth_Limit_Up__DM2) 
/* Input Buffer Disable Override */
#define Azimuth_Limit_Up_INP_DIS                (* (reg8 *) Azimuth_Limit_Up__INP_DIS)
/* LCD Common or Segment Drive */
#define Azimuth_Limit_Up_LCD_COM_SEG            (* (reg8 *) Azimuth_Limit_Up__LCD_COM_SEG)
/* Enable Segment LCD */
#define Azimuth_Limit_Up_LCD_EN                 (* (reg8 *) Azimuth_Limit_Up__LCD_EN)
/* Slew Rate Control */
#define Azimuth_Limit_Up_SLW                    (* (reg8 *) Azimuth_Limit_Up__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Azimuth_Limit_Up_PRTDSI__CAPS_SEL       (* (reg8 *) Azimuth_Limit_Up__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Azimuth_Limit_Up_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Azimuth_Limit_Up__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Azimuth_Limit_Up_PRTDSI__OE_SEL0        (* (reg8 *) Azimuth_Limit_Up__PRTDSI__OE_SEL0) 
#define Azimuth_Limit_Up_PRTDSI__OE_SEL1        (* (reg8 *) Azimuth_Limit_Up__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Azimuth_Limit_Up_PRTDSI__OUT_SEL0       (* (reg8 *) Azimuth_Limit_Up__PRTDSI__OUT_SEL0) 
#define Azimuth_Limit_Up_PRTDSI__OUT_SEL1       (* (reg8 *) Azimuth_Limit_Up__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Azimuth_Limit_Up_PRTDSI__SYNC_OUT       (* (reg8 *) Azimuth_Limit_Up__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Azimuth_Limit_Up__SIO_CFG)
    #define Azimuth_Limit_Up_SIO_HYST_EN        (* (reg8 *) Azimuth_Limit_Up__SIO_HYST_EN)
    #define Azimuth_Limit_Up_SIO_REG_HIFREQ     (* (reg8 *) Azimuth_Limit_Up__SIO_REG_HIFREQ)
    #define Azimuth_Limit_Up_SIO_CFG            (* (reg8 *) Azimuth_Limit_Up__SIO_CFG)
    #define Azimuth_Limit_Up_SIO_DIFF           (* (reg8 *) Azimuth_Limit_Up__SIO_DIFF)
#endif /* (Azimuth_Limit_Up__SIO_CFG) */

/* Interrupt Registers */
#if defined(Azimuth_Limit_Up__INTSTAT)
    #define Azimuth_Limit_Up_INTSTAT            (* (reg8 *) Azimuth_Limit_Up__INTSTAT)
    #define Azimuth_Limit_Up_SNAP               (* (reg8 *) Azimuth_Limit_Up__SNAP)
    
	#define Azimuth_Limit_Up_0_INTTYPE_REG 		(* (reg8 *) Azimuth_Limit_Up__0__INTTYPE)
#endif /* (Azimuth_Limit_Up__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Azimuth_Limit_Up_H */


/* [] END OF FILE */
