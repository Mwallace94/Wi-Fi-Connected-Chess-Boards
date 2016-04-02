/*******************************************************************************
* File Name: Col_9.h  
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

#if !defined(CY_PINS_Col_9_H) /* Pins Col_9_H */
#define CY_PINS_Col_9_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Col_9_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Col_9_Write(uint8 value) ;
void    Col_9_SetDriveMode(uint8 mode) ;
uint8   Col_9_ReadDataReg(void) ;
uint8   Col_9_Read(void) ;
uint8   Col_9_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Col_9_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Col_9_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Col_9_DM_RES_UP          PIN_DM_RES_UP
#define Col_9_DM_RES_DWN         PIN_DM_RES_DWN
#define Col_9_DM_OD_LO           PIN_DM_OD_LO
#define Col_9_DM_OD_HI           PIN_DM_OD_HI
#define Col_9_DM_STRONG          PIN_DM_STRONG
#define Col_9_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Col_9_MASK               Col_9__MASK
#define Col_9_SHIFT              Col_9__SHIFT
#define Col_9_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Col_9_PS                     (* (reg8 *) Col_9__PS)
/* Data Register */
#define Col_9_DR                     (* (reg8 *) Col_9__DR)
/* Port Number */
#define Col_9_PRT_NUM                (* (reg8 *) Col_9__PRT) 
/* Connect to Analog Globals */                                                  
#define Col_9_AG                     (* (reg8 *) Col_9__AG)                       
/* Analog MUX bux enable */
#define Col_9_AMUX                   (* (reg8 *) Col_9__AMUX) 
/* Bidirectional Enable */                                                        
#define Col_9_BIE                    (* (reg8 *) Col_9__BIE)
/* Bit-mask for Aliased Register Access */
#define Col_9_BIT_MASK               (* (reg8 *) Col_9__BIT_MASK)
/* Bypass Enable */
#define Col_9_BYP                    (* (reg8 *) Col_9__BYP)
/* Port wide control signals */                                                   
#define Col_9_CTL                    (* (reg8 *) Col_9__CTL)
/* Drive Modes */
#define Col_9_DM0                    (* (reg8 *) Col_9__DM0) 
#define Col_9_DM1                    (* (reg8 *) Col_9__DM1)
#define Col_9_DM2                    (* (reg8 *) Col_9__DM2) 
/* Input Buffer Disable Override */
#define Col_9_INP_DIS                (* (reg8 *) Col_9__INP_DIS)
/* LCD Common or Segment Drive */
#define Col_9_LCD_COM_SEG            (* (reg8 *) Col_9__LCD_COM_SEG)
/* Enable Segment LCD */
#define Col_9_LCD_EN                 (* (reg8 *) Col_9__LCD_EN)
/* Slew Rate Control */
#define Col_9_SLW                    (* (reg8 *) Col_9__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Col_9_PRTDSI__CAPS_SEL       (* (reg8 *) Col_9__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Col_9_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Col_9__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Col_9_PRTDSI__OE_SEL0        (* (reg8 *) Col_9__PRTDSI__OE_SEL0) 
#define Col_9_PRTDSI__OE_SEL1        (* (reg8 *) Col_9__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Col_9_PRTDSI__OUT_SEL0       (* (reg8 *) Col_9__PRTDSI__OUT_SEL0) 
#define Col_9_PRTDSI__OUT_SEL1       (* (reg8 *) Col_9__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Col_9_PRTDSI__SYNC_OUT       (* (reg8 *) Col_9__PRTDSI__SYNC_OUT) 


#if defined(Col_9__INTSTAT)  /* Interrupt Registers */

    #define Col_9_INTSTAT                (* (reg8 *) Col_9__INTSTAT)
    #define Col_9_SNAP                   (* (reg8 *) Col_9__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Col_9_H */


/* [] END OF FILE */
