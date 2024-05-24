/*******************************************************************************
* File Name: SolarPanel.h  
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

#if !defined(CY_PINS_SolarPanel_H) /* Pins SolarPanel_H */
#define CY_PINS_SolarPanel_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SolarPanel_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SolarPanel__PORT == 15 && ((SolarPanel__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SolarPanel_Write(uint8 value);
void    SolarPanel_SetDriveMode(uint8 mode);
uint8   SolarPanel_ReadDataReg(void);
uint8   SolarPanel_Read(void);
void    SolarPanel_SetInterruptMode(uint16 position, uint16 mode);
uint8   SolarPanel_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SolarPanel_SetDriveMode() function.
     *  @{
     */
        #define SolarPanel_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SolarPanel_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SolarPanel_DM_RES_UP          PIN_DM_RES_UP
        #define SolarPanel_DM_RES_DWN         PIN_DM_RES_DWN
        #define SolarPanel_DM_OD_LO           PIN_DM_OD_LO
        #define SolarPanel_DM_OD_HI           PIN_DM_OD_HI
        #define SolarPanel_DM_STRONG          PIN_DM_STRONG
        #define SolarPanel_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SolarPanel_MASK               SolarPanel__MASK
#define SolarPanel_SHIFT              SolarPanel__SHIFT
#define SolarPanel_WIDTH              1u

/* Interrupt constants */
#if defined(SolarPanel__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SolarPanel_SetInterruptMode() function.
     *  @{
     */
        #define SolarPanel_INTR_NONE      (uint16)(0x0000u)
        #define SolarPanel_INTR_RISING    (uint16)(0x0001u)
        #define SolarPanel_INTR_FALLING   (uint16)(0x0002u)
        #define SolarPanel_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SolarPanel_INTR_MASK      (0x01u) 
#endif /* (SolarPanel__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SolarPanel_PS                     (* (reg8 *) SolarPanel__PS)
/* Data Register */
#define SolarPanel_DR                     (* (reg8 *) SolarPanel__DR)
/* Port Number */
#define SolarPanel_PRT_NUM                (* (reg8 *) SolarPanel__PRT) 
/* Connect to Analog Globals */                                                  
#define SolarPanel_AG                     (* (reg8 *) SolarPanel__AG)                       
/* Analog MUX bux enable */
#define SolarPanel_AMUX                   (* (reg8 *) SolarPanel__AMUX) 
/* Bidirectional Enable */                                                        
#define SolarPanel_BIE                    (* (reg8 *) SolarPanel__BIE)
/* Bit-mask for Aliased Register Access */
#define SolarPanel_BIT_MASK               (* (reg8 *) SolarPanel__BIT_MASK)
/* Bypass Enable */
#define SolarPanel_BYP                    (* (reg8 *) SolarPanel__BYP)
/* Port wide control signals */                                                   
#define SolarPanel_CTL                    (* (reg8 *) SolarPanel__CTL)
/* Drive Modes */
#define SolarPanel_DM0                    (* (reg8 *) SolarPanel__DM0) 
#define SolarPanel_DM1                    (* (reg8 *) SolarPanel__DM1)
#define SolarPanel_DM2                    (* (reg8 *) SolarPanel__DM2) 
/* Input Buffer Disable Override */
#define SolarPanel_INP_DIS                (* (reg8 *) SolarPanel__INP_DIS)
/* LCD Common or Segment Drive */
#define SolarPanel_LCD_COM_SEG            (* (reg8 *) SolarPanel__LCD_COM_SEG)
/* Enable Segment LCD */
#define SolarPanel_LCD_EN                 (* (reg8 *) SolarPanel__LCD_EN)
/* Slew Rate Control */
#define SolarPanel_SLW                    (* (reg8 *) SolarPanel__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SolarPanel_PRTDSI__CAPS_SEL       (* (reg8 *) SolarPanel__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SolarPanel_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SolarPanel__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SolarPanel_PRTDSI__OE_SEL0        (* (reg8 *) SolarPanel__PRTDSI__OE_SEL0) 
#define SolarPanel_PRTDSI__OE_SEL1        (* (reg8 *) SolarPanel__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SolarPanel_PRTDSI__OUT_SEL0       (* (reg8 *) SolarPanel__PRTDSI__OUT_SEL0) 
#define SolarPanel_PRTDSI__OUT_SEL1       (* (reg8 *) SolarPanel__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SolarPanel_PRTDSI__SYNC_OUT       (* (reg8 *) SolarPanel__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SolarPanel__SIO_CFG)
    #define SolarPanel_SIO_HYST_EN        (* (reg8 *) SolarPanel__SIO_HYST_EN)
    #define SolarPanel_SIO_REG_HIFREQ     (* (reg8 *) SolarPanel__SIO_REG_HIFREQ)
    #define SolarPanel_SIO_CFG            (* (reg8 *) SolarPanel__SIO_CFG)
    #define SolarPanel_SIO_DIFF           (* (reg8 *) SolarPanel__SIO_DIFF)
#endif /* (SolarPanel__SIO_CFG) */

/* Interrupt Registers */
#if defined(SolarPanel__INTSTAT)
    #define SolarPanel_INTSTAT            (* (reg8 *) SolarPanel__INTSTAT)
    #define SolarPanel_SNAP               (* (reg8 *) SolarPanel__SNAP)
    
	#define SolarPanel_0_INTTYPE_REG 		(* (reg8 *) SolarPanel__0__INTTYPE)
#endif /* (SolarPanel__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SolarPanel_H */


/* [] END OF FILE */
