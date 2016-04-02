/*******************************************************************************
* File Name: Col_3.h  
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

#if !defined(CY_PINS_Col_3_H) /* Pins Col_3_H */
#define CY_PINS_Col_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Col_3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Col_3_Write(uint8 value) ;
void    Col_3_SetDriveMode(uint8 mode) ;
uint8   Col_3_ReadDataReg(void) ;
uint8   Col_3_Read(void) ;
uint8   Col_3_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Col_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Col_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Col_3_DM_RES_UP          PIN_DM_RES_UP
#define Col_3_DM_RES_DWN         PIN_DM_RES_DWN
#define Col_3_DM_OD_LO           PIN_DM_OD_LO
#define Col_3_DM_OD_HI           PIN_DM_OD_HI
#define Col_3_DM_STRONG          PIN_DM_STRONG
#define Col_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Col_3_MASK               Col_3__MASK
#define Col_3_SHIFT              Col_3__SHIFT
#define Col_3_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Col_3_PS                     (* (reg8 *) Col_3__PS)
/* Data Register */
#define Col_3_DR                     (* (reg8 *) Col_3__DR)
/* Port Number */
#define Col_3_PRT_NUM                (* (reg8 *) Col_3__PRT) 
/* Connect to Analog Globals */                                                  
#define Col_3_AG                     (* (reg8 *) Col_3__AG)                       
/* Analog MUX bux enable */
#define Col_3_AMUX                   (* (reg8 *) Col_3__AMUX) 
/* Bidirectional Enable */                                                        
#define Col_3_BIE                    (* (reg8 *) Col_3__BIE)
/* Bit-mask for Aliased Register Access */
#define Col_3_BIT_MASK               (* (reg8 *) Col_3__BIT_MASK)
/* Bypass Enable */
#define Col_3_BYP                    (* (reg8 *) Col_3__BYP)
/* Port wide control signals */                                                   
#define Col_3_CTL                    (* (reg8 *) Col_3__CTL)
/* Drive Modes */
#define Col_3_DM0                    (* (reg8 *) Col_3__DM0) 
#define Col_3_DM1                    (* (reg8 *) Col_3__DM1)
#define Col_3_DM2                    (* (reg8 *) Col_3__DM2) 
/* Input Buffer Disable Override */
#define Col_3_INP_DIS                (* (reg8 *) Col_3__INP_DIS)
/* LCD Common or Segment Drive */
#define Col_3_LCD_COM_SEG            (* (reg8 *) Col_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Col_3_LCD_EN                 (* (reg8 *) Col_3__LCD_EN)
/* Slew Rate Control */
#define Col_3_SLW                    (* (reg8 *) Col_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Col_3_PRTDSI__CAPS_SEL       (* (reg8 *) Col_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Col_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Col_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Col_3_PRTDSI__OE_SEL0        (* (reg8 *) Col_3__PRTDSI__OE_SEL0) 
#define Col_3_PRTDSI__OE_SEL1        (* (reg8 *) Col_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Col_3_PRTDSI__OUT_SEL0       (* (reg8 *) Col_3__PRTDSI__OUT_SEL0) 
#define Col_3_PRTDSI__OUT_SEL1       (* (reg8 *) Col_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Col_3_PRTDSI__SYNC_OUT       (* (reg8 *) Col_3__PRTDSI__SYNC_OUT) 


#if defined(Col_3__INTSTAT)  /* Interrupt Registers */

    #define Col_3_INTSTAT                (* (reg8 *) Col_3__INTSTAT)
    #define Col_3_SNAP                   (* (reg8 *) Col_3__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Col_3_H */


/* [] END OF FILE */
