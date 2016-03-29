/*******************************************************************************
* File Name: Row.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Row_H) /* Pins Row_H */
#define CY_PINS_Row_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Row_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Row_Write(uint8 value) ;
void    Row_SetDriveMode(uint8 mode) ;
uint8   Row_ReadDataReg(void) ;
uint8   Row_Read(void) ;
uint8   Row_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Row_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Row_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Row_DM_RES_UP          PIN_DM_RES_UP
#define Row_DM_RES_DWN         PIN_DM_RES_DWN
#define Row_DM_OD_LO           PIN_DM_OD_LO
#define Row_DM_OD_HI           PIN_DM_OD_HI
#define Row_DM_STRONG          PIN_DM_STRONG
#define Row_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Row_MASK               Row__MASK
#define Row_SHIFT              Row__SHIFT
#define Row_WIDTH              8u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Row_PS                     (* (reg8 *) Row__PS)
/* Data Register */
#define Row_DR                     (* (reg8 *) Row__DR)
/* Port Number */
#define Row_PRT_NUM                (* (reg8 *) Row__PRT) 
/* Connect to Analog Globals */                                                  
#define Row_AG                     (* (reg8 *) Row__AG)                       
/* Analog MUX bux enable */
#define Row_AMUX                   (* (reg8 *) Row__AMUX) 
/* Bidirectional Enable */                                                        
#define Row_BIE                    (* (reg8 *) Row__BIE)
/* Bit-mask for Aliased Register Access */
#define Row_BIT_MASK               (* (reg8 *) Row__BIT_MASK)
/* Bypass Enable */
#define Row_BYP                    (* (reg8 *) Row__BYP)
/* Port wide control signals */                                                   
#define Row_CTL                    (* (reg8 *) Row__CTL)
/* Drive Modes */
#define Row_DM0                    (* (reg8 *) Row__DM0) 
#define Row_DM1                    (* (reg8 *) Row__DM1)
#define Row_DM2                    (* (reg8 *) Row__DM2) 
/* Input Buffer Disable Override */
#define Row_INP_DIS                (* (reg8 *) Row__INP_DIS)
/* LCD Common or Segment Drive */
#define Row_LCD_COM_SEG            (* (reg8 *) Row__LCD_COM_SEG)
/* Enable Segment LCD */
#define Row_LCD_EN                 (* (reg8 *) Row__LCD_EN)
/* Slew Rate Control */
#define Row_SLW                    (* (reg8 *) Row__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Row_PRTDSI__CAPS_SEL       (* (reg8 *) Row__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Row_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Row__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Row_PRTDSI__OE_SEL0        (* (reg8 *) Row__PRTDSI__OE_SEL0) 
#define Row_PRTDSI__OE_SEL1        (* (reg8 *) Row__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Row_PRTDSI__OUT_SEL0       (* (reg8 *) Row__PRTDSI__OUT_SEL0) 
#define Row_PRTDSI__OUT_SEL1       (* (reg8 *) Row__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Row_PRTDSI__SYNC_OUT       (* (reg8 *) Row__PRTDSI__SYNC_OUT) 


#if defined(Row__INTSTAT)  /* Interrupt Registers */

    #define Row_INTSTAT                (* (reg8 *) Row__INTSTAT)
    #define Row_SNAP                   (* (reg8 *) Row__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Row_H */


/* [] END OF FILE */
