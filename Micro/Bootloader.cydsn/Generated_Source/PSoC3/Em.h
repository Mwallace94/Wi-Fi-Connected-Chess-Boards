/*******************************************************************************
* File Name: Em.h  
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

#if !defined(CY_PINS_Em_H) /* Pins Em_H */
#define CY_PINS_Em_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Em_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Em_Write(uint8 value) ;
void    Em_SetDriveMode(uint8 mode) ;
uint8   Em_ReadDataReg(void) ;
uint8   Em_Read(void) ;
uint8   Em_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Em_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Em_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Em_DM_RES_UP          PIN_DM_RES_UP
#define Em_DM_RES_DWN         PIN_DM_RES_DWN
#define Em_DM_OD_LO           PIN_DM_OD_LO
#define Em_DM_OD_HI           PIN_DM_OD_HI
#define Em_DM_STRONG          PIN_DM_STRONG
#define Em_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Em_MASK               Em__MASK
#define Em_SHIFT              Em__SHIFT
#define Em_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Em_PS                     (* (reg8 *) Em__PS)
/* Data Register */
#define Em_DR                     (* (reg8 *) Em__DR)
/* Port Number */
#define Em_PRT_NUM                (* (reg8 *) Em__PRT) 
/* Connect to Analog Globals */                                                  
#define Em_AG                     (* (reg8 *) Em__AG)                       
/* Analog MUX bux enable */
#define Em_AMUX                   (* (reg8 *) Em__AMUX) 
/* Bidirectional Enable */                                                        
#define Em_BIE                    (* (reg8 *) Em__BIE)
/* Bit-mask for Aliased Register Access */
#define Em_BIT_MASK               (* (reg8 *) Em__BIT_MASK)
/* Bypass Enable */
#define Em_BYP                    (* (reg8 *) Em__BYP)
/* Port wide control signals */                                                   
#define Em_CTL                    (* (reg8 *) Em__CTL)
/* Drive Modes */
#define Em_DM0                    (* (reg8 *) Em__DM0) 
#define Em_DM1                    (* (reg8 *) Em__DM1)
#define Em_DM2                    (* (reg8 *) Em__DM2) 
/* Input Buffer Disable Override */
#define Em_INP_DIS                (* (reg8 *) Em__INP_DIS)
/* LCD Common or Segment Drive */
#define Em_LCD_COM_SEG            (* (reg8 *) Em__LCD_COM_SEG)
/* Enable Segment LCD */
#define Em_LCD_EN                 (* (reg8 *) Em__LCD_EN)
/* Slew Rate Control */
#define Em_SLW                    (* (reg8 *) Em__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Em_PRTDSI__CAPS_SEL       (* (reg8 *) Em__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Em_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Em__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Em_PRTDSI__OE_SEL0        (* (reg8 *) Em__PRTDSI__OE_SEL0) 
#define Em_PRTDSI__OE_SEL1        (* (reg8 *) Em__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Em_PRTDSI__OUT_SEL0       (* (reg8 *) Em__PRTDSI__OUT_SEL0) 
#define Em_PRTDSI__OUT_SEL1       (* (reg8 *) Em__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Em_PRTDSI__SYNC_OUT       (* (reg8 *) Em__PRTDSI__SYNC_OUT) 


#if defined(Em__INTSTAT)  /* Interrupt Registers */

    #define Em_INTSTAT                (* (reg8 *) Em__INTSTAT)
    #define Em_SNAP                   (* (reg8 *) Em__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Em_H */


/* [] END OF FILE */
