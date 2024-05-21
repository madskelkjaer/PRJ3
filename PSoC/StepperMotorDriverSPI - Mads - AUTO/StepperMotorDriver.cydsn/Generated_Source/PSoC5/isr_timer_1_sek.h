/*******************************************************************************
* File Name: isr_timer_1_sek.h
* Version 1.71
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_timer_1_sek_H)
#define CY_ISR_isr_timer_1_sek_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_timer_1_sek_Start(void);
void isr_timer_1_sek_StartEx(cyisraddress address);
void isr_timer_1_sek_Stop(void);

CY_ISR_PROTO(isr_timer_1_sek_Interrupt);

void isr_timer_1_sek_SetVector(cyisraddress address);
cyisraddress isr_timer_1_sek_GetVector(void);

void isr_timer_1_sek_SetPriority(uint8 priority);
uint8 isr_timer_1_sek_GetPriority(void);

void isr_timer_1_sek_Enable(void);
uint8 isr_timer_1_sek_GetState(void);
void isr_timer_1_sek_Disable(void);

void isr_timer_1_sek_SetPending(void);
void isr_timer_1_sek_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_timer_1_sek ISR. */
#define isr_timer_1_sek_INTC_VECTOR            ((reg32 *) isr_timer_1_sek__INTC_VECT)

/* Address of the isr_timer_1_sek ISR priority. */
#define isr_timer_1_sek_INTC_PRIOR             ((reg8 *) isr_timer_1_sek__INTC_PRIOR_REG)

/* Priority of the isr_timer_1_sek interrupt. */
#define isr_timer_1_sek_INTC_PRIOR_NUMBER      isr_timer_1_sek__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_timer_1_sek interrupt. */
#define isr_timer_1_sek_INTC_SET_EN            ((reg32 *) isr_timer_1_sek__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_timer_1_sek interrupt. */
#define isr_timer_1_sek_INTC_CLR_EN            ((reg32 *) isr_timer_1_sek__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_timer_1_sek interrupt state to pending. */
#define isr_timer_1_sek_INTC_SET_PD            ((reg32 *) isr_timer_1_sek__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_timer_1_sek interrupt. */
#define isr_timer_1_sek_INTC_CLR_PD            ((reg32 *) isr_timer_1_sek__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_timer_1_sek_H */


/* [] END OF FILE */
