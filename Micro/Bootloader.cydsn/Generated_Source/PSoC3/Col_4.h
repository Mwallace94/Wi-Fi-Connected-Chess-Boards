/*******************************************************************************
* File Name: Col_4.h  
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

#if !defined(CY_PINS_Col_4_H) /* Pins Col_4_H */
#define CY_PINS_Col_4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Col_4_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Col_4_Write(uint8 value) ;
void    Col_4_SetDriveMode(uint8 mode) ;
uint8   Col_4_ReadDataReg(void) ;
uint8   Col_4_Read(void) ;
uint8   Col_4_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Col_4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Col_4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Col_4_DM_RES_UP          PIN_DM_RES_UP
#define Col_4_DM_RES_DWN         PIN_DM_RES_DWN
#define Col_4_DM_OD_LO           PIN_DM_OD_LO
#define Col_4_DM_OD_HI           PIN_DM_OD_HI
#define Col_4_DM_STRONG          PIN_DM_STRONG
#define Col_4_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Col_4_MASK               Col_4__MASK
#define Col_4_SHIFT              Col_4__SHIFT
#define Col_4_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Col_4_PS                     (* (reg8 *) Col_4__PS)
/* Data Register */
#define Col_4_DR                     (* (reg8 *) Col_4__DR)
/* Port Number */
#define Col_4_PRT_NUM                (* (reg8 *) Col_4__PRT) 
/* Connect to Analog Globals */                                                  
#define Col_4_AG                     (* (reg8 *) Col_4__AG)                       
/* Analog MUX bux enable */
#define Col_4_AMUX                   (* (reg8 *) Col_4__AMUX) 
/* Bidirectional Enable */                                                        
#define Col_4_BIE                    (* (reg8 *) Col_4__BIE)
/* Bit-mask for Aliased Register Access */
#define Col_4_BIT_MASK               (* (reg8 *) Col_4__BIT_MASK)
/* Bypass Enable */
#define Col_4_BYP                    (* (reg8 *) Col_4__BYP)
/* Port wide control signals */                                                   
#define Col_4_CTL                    (* (reg8 *) Col_4__CTL)
/* Drive Modes */
#define Col_4_DM0                    (* (reg8 *) Col_4__DM0) 
#define Col_4_DM1                    (* (reg8 *) Col_4__DM1)
#define Col_4_DM2                    (* (reg8 *) Col_4__DM2) 
/* Input Buffer Disable Override */
#define Col_4_INP_DIS                (* (reg8 *) Col_4__INP_DIS)
/* LCD Common or Segment Drive */
#define Col_4_LCD_COM_SEG            (* (reg8 *) Col_4__LCD_COM_SEG)
/* Enable Segment LCD */
#define Col_4_LCD_EN                 (* (reg8 *) Col_4__LCD_EN)
/* Slew Rate Control */
#define Col_4_SLW                    (* (reg8 *) Col_4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Col_4_PRTDSI__CAPS_SEL       (* (reg8 *) Col_4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Col_4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Col_4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Col_4_PRTDSI__OE_SEL0        (* (reg8 *) Col_4__PRTDSI__OE_SEL0) 
#define Col_4_PRTDSI__OE_SEL1        (* (reg8 *) Col_4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Col_4_PRTDSI__OUT_SEL0       (* (reg8 *) Col_4__PRTDSI__OUT_SEL0) 
#define Col_4_PRTDSI__OUT_SEL1       (* (reg8 *) Col_4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Col_4_PRTDSI__SYNC_OUT       (* (reg8 *) Col_4__PRTDSI__SYNC_OUT) 


#if defined(Col_4__INTSTAT)  /* Interrupt Registers */

    #define Col_4_INTSTAT                (* (reg8 *) Col_4__INTSTAT)
    #define Col_4_SNAP                   (* (reg8 *) Col_4__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Col_4_H */


/* [] END OF FILE */
