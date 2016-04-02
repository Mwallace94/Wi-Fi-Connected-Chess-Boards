/*******************************************************************************
* File Name: Col_6.h  
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

#if !defined(CY_PINS_Col_6_H) /* Pins Col_6_H */
#define CY_PINS_Col_6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Col_6_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Col_6_Write(uint8 value) ;
void    Col_6_SetDriveMode(uint8 mode) ;
uint8   Col_6_ReadDataReg(void) ;
uint8   Col_6_Read(void) ;
uint8   Col_6_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Col_6_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Col_6_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Col_6_DM_RES_UP          PIN_DM_RES_UP
#define Col_6_DM_RES_DWN         PIN_DM_RES_DWN
#define Col_6_DM_OD_LO           PIN_DM_OD_LO
#define Col_6_DM_OD_HI           PIN_DM_OD_HI
#define Col_6_DM_STRONG          PIN_DM_STRONG
#define Col_6_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Col_6_MASK               Col_6__MASK
#define Col_6_SHIFT              Col_6__SHIFT
#define Col_6_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Col_6_PS                     (* (reg8 *) Col_6__PS)
/* Data Register */
#define Col_6_DR                     (* (reg8 *) Col_6__DR)
/* Port Number */
#define Col_6_PRT_NUM                (* (reg8 *) Col_6__PRT) 
/* Connect to Analog Globals */                                                  
#define Col_6_AG                     (* (reg8 *) Col_6__AG)                       
/* Analog MUX bux enable */
#define Col_6_AMUX                   (* (reg8 *) Col_6__AMUX) 
/* Bidirectional Enable */                                                        
#define Col_6_BIE                    (* (reg8 *) Col_6__BIE)
/* Bit-mask for Aliased Register Access */
#define Col_6_BIT_MASK               (* (reg8 *) Col_6__BIT_MASK)
/* Bypass Enable */
#define Col_6_BYP                    (* (reg8 *) Col_6__BYP)
/* Port wide control signals */                                                   
#define Col_6_CTL                    (* (reg8 *) Col_6__CTL)
/* Drive Modes */
#define Col_6_DM0                    (* (reg8 *) Col_6__DM0) 
#define Col_6_DM1                    (* (reg8 *) Col_6__DM1)
#define Col_6_DM2                    (* (reg8 *) Col_6__DM2) 
/* Input Buffer Disable Override */
#define Col_6_INP_DIS                (* (reg8 *) Col_6__INP_DIS)
/* LCD Common or Segment Drive */
#define Col_6_LCD_COM_SEG            (* (reg8 *) Col_6__LCD_COM_SEG)
/* Enable Segment LCD */
#define Col_6_LCD_EN                 (* (reg8 *) Col_6__LCD_EN)
/* Slew Rate Control */
#define Col_6_SLW                    (* (reg8 *) Col_6__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Col_6_PRTDSI__CAPS_SEL       (* (reg8 *) Col_6__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Col_6_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Col_6__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Col_6_PRTDSI__OE_SEL0        (* (reg8 *) Col_6__PRTDSI__OE_SEL0) 
#define Col_6_PRTDSI__OE_SEL1        (* (reg8 *) Col_6__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Col_6_PRTDSI__OUT_SEL0       (* (reg8 *) Col_6__PRTDSI__OUT_SEL0) 
#define Col_6_PRTDSI__OUT_SEL1       (* (reg8 *) Col_6__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Col_6_PRTDSI__SYNC_OUT       (* (reg8 *) Col_6__PRTDSI__SYNC_OUT) 


#if defined(Col_6__INTSTAT)  /* Interrupt Registers */

    #define Col_6_INTSTAT                (* (reg8 *) Col_6__INTSTAT)
    #define Col_6_SNAP                   (* (reg8 *) Col_6__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Col_6_H */


/* [] END OF FILE */
