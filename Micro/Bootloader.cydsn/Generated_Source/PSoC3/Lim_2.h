/*******************************************************************************
* File Name: Lim_2.h  
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

#if !defined(CY_PINS_Lim_2_H) /* Pins Lim_2_H */
#define CY_PINS_Lim_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Lim_2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Lim_2_Write(uint8 value) ;
void    Lim_2_SetDriveMode(uint8 mode) ;
uint8   Lim_2_ReadDataReg(void) ;
uint8   Lim_2_Read(void) ;
uint8   Lim_2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Lim_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Lim_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Lim_2_DM_RES_UP          PIN_DM_RES_UP
#define Lim_2_DM_RES_DWN         PIN_DM_RES_DWN
#define Lim_2_DM_OD_LO           PIN_DM_OD_LO
#define Lim_2_DM_OD_HI           PIN_DM_OD_HI
#define Lim_2_DM_STRONG          PIN_DM_STRONG
#define Lim_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Lim_2_MASK               Lim_2__MASK
#define Lim_2_SHIFT              Lim_2__SHIFT
#define Lim_2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Lim_2_PS                     (* (reg8 *) Lim_2__PS)
/* Data Register */
#define Lim_2_DR                     (* (reg8 *) Lim_2__DR)
/* Port Number */
#define Lim_2_PRT_NUM                (* (reg8 *) Lim_2__PRT) 
/* Connect to Analog Globals */                                                  
#define Lim_2_AG                     (* (reg8 *) Lim_2__AG)                       
/* Analog MUX bux enable */
#define Lim_2_AMUX                   (* (reg8 *) Lim_2__AMUX) 
/* Bidirectional Enable */                                                        
#define Lim_2_BIE                    (* (reg8 *) Lim_2__BIE)
/* Bit-mask for Aliased Register Access */
#define Lim_2_BIT_MASK               (* (reg8 *) Lim_2__BIT_MASK)
/* Bypass Enable */
#define Lim_2_BYP                    (* (reg8 *) Lim_2__BYP)
/* Port wide control signals */                                                   
#define Lim_2_CTL                    (* (reg8 *) Lim_2__CTL)
/* Drive Modes */
#define Lim_2_DM0                    (* (reg8 *) Lim_2__DM0) 
#define Lim_2_DM1                    (* (reg8 *) Lim_2__DM1)
#define Lim_2_DM2                    (* (reg8 *) Lim_2__DM2) 
/* Input Buffer Disable Override */
#define Lim_2_INP_DIS                (* (reg8 *) Lim_2__INP_DIS)
/* LCD Common or Segment Drive */
#define Lim_2_LCD_COM_SEG            (* (reg8 *) Lim_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Lim_2_LCD_EN                 (* (reg8 *) Lim_2__LCD_EN)
/* Slew Rate Control */
#define Lim_2_SLW                    (* (reg8 *) Lim_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Lim_2_PRTDSI__CAPS_SEL       (* (reg8 *) Lim_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Lim_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Lim_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Lim_2_PRTDSI__OE_SEL0        (* (reg8 *) Lim_2__PRTDSI__OE_SEL0) 
#define Lim_2_PRTDSI__OE_SEL1        (* (reg8 *) Lim_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Lim_2_PRTDSI__OUT_SEL0       (* (reg8 *) Lim_2__PRTDSI__OUT_SEL0) 
#define Lim_2_PRTDSI__OUT_SEL1       (* (reg8 *) Lim_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Lim_2_PRTDSI__SYNC_OUT       (* (reg8 *) Lim_2__PRTDSI__SYNC_OUT) 


#if defined(Lim_2__INTSTAT)  /* Interrupt Registers */

    #define Lim_2_INTSTAT                (* (reg8 *) Lim_2__INTSTAT)
    #define Lim_2_SNAP                   (* (reg8 *) Lim_2__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Lim_2_H */


/* [] END OF FILE */
