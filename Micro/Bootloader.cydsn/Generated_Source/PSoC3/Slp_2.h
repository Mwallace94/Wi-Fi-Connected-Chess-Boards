/*******************************************************************************
* File Name: Slp_2.h  
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

#if !defined(CY_PINS_Slp_2_H) /* Pins Slp_2_H */
#define CY_PINS_Slp_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Slp_2_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Slp_2_Write(uint8 value) ;
void    Slp_2_SetDriveMode(uint8 mode) ;
uint8   Slp_2_ReadDataReg(void) ;
uint8   Slp_2_Read(void) ;
uint8   Slp_2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Slp_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Slp_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Slp_2_DM_RES_UP          PIN_DM_RES_UP
#define Slp_2_DM_RES_DWN         PIN_DM_RES_DWN
#define Slp_2_DM_OD_LO           PIN_DM_OD_LO
#define Slp_2_DM_OD_HI           PIN_DM_OD_HI
#define Slp_2_DM_STRONG          PIN_DM_STRONG
#define Slp_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Slp_2_MASK               Slp_2__MASK
#define Slp_2_SHIFT              Slp_2__SHIFT
#define Slp_2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Slp_2_PS                     (* (reg8 *) Slp_2__PS)
/* Data Register */
#define Slp_2_DR                     (* (reg8 *) Slp_2__DR)
/* Port Number */
#define Slp_2_PRT_NUM                (* (reg8 *) Slp_2__PRT) 
/* Connect to Analog Globals */                                                  
#define Slp_2_AG                     (* (reg8 *) Slp_2__AG)                       
/* Analog MUX bux enable */
#define Slp_2_AMUX                   (* (reg8 *) Slp_2__AMUX) 
/* Bidirectional Enable */                                                        
#define Slp_2_BIE                    (* (reg8 *) Slp_2__BIE)
/* Bit-mask for Aliased Register Access */
#define Slp_2_BIT_MASK               (* (reg8 *) Slp_2__BIT_MASK)
/* Bypass Enable */
#define Slp_2_BYP                    (* (reg8 *) Slp_2__BYP)
/* Port wide control signals */                                                   
#define Slp_2_CTL                    (* (reg8 *) Slp_2__CTL)
/* Drive Modes */
#define Slp_2_DM0                    (* (reg8 *) Slp_2__DM0) 
#define Slp_2_DM1                    (* (reg8 *) Slp_2__DM1)
#define Slp_2_DM2                    (* (reg8 *) Slp_2__DM2) 
/* Input Buffer Disable Override */
#define Slp_2_INP_DIS                (* (reg8 *) Slp_2__INP_DIS)
/* LCD Common or Segment Drive */
#define Slp_2_LCD_COM_SEG            (* (reg8 *) Slp_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Slp_2_LCD_EN                 (* (reg8 *) Slp_2__LCD_EN)
/* Slew Rate Control */
#define Slp_2_SLW                    (* (reg8 *) Slp_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Slp_2_PRTDSI__CAPS_SEL       (* (reg8 *) Slp_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Slp_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Slp_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Slp_2_PRTDSI__OE_SEL0        (* (reg8 *) Slp_2__PRTDSI__OE_SEL0) 
#define Slp_2_PRTDSI__OE_SEL1        (* (reg8 *) Slp_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Slp_2_PRTDSI__OUT_SEL0       (* (reg8 *) Slp_2__PRTDSI__OUT_SEL0) 
#define Slp_2_PRTDSI__OUT_SEL1       (* (reg8 *) Slp_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Slp_2_PRTDSI__SYNC_OUT       (* (reg8 *) Slp_2__PRTDSI__SYNC_OUT) 


#if defined(Slp_2__INTSTAT)  /* Interrupt Registers */

    #define Slp_2_INTSTAT                (* (reg8 *) Slp_2__INTSTAT)
    #define Slp_2_SNAP                   (* (reg8 *) Slp_2__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Slp_2_H */


/* [] END OF FILE */
