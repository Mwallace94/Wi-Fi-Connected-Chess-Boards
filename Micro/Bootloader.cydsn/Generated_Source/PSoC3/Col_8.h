/*******************************************************************************
* File Name: Col_8.h  
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

#if !defined(CY_PINS_Col_8_H) /* Pins Col_8_H */
#define CY_PINS_Col_8_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Col_8_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Col_8_Write(uint8 value) ;
void    Col_8_SetDriveMode(uint8 mode) ;
uint8   Col_8_ReadDataReg(void) ;
uint8   Col_8_Read(void) ;
uint8   Col_8_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Col_8_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Col_8_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Col_8_DM_RES_UP          PIN_DM_RES_UP
#define Col_8_DM_RES_DWN         PIN_DM_RES_DWN
#define Col_8_DM_OD_LO           PIN_DM_OD_LO
#define Col_8_DM_OD_HI           PIN_DM_OD_HI
#define Col_8_DM_STRONG          PIN_DM_STRONG
#define Col_8_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Col_8_MASK               Col_8__MASK
#define Col_8_SHIFT              Col_8__SHIFT
#define Col_8_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Col_8_PS                     (* (reg8 *) Col_8__PS)
/* Data Register */
#define Col_8_DR                     (* (reg8 *) Col_8__DR)
/* Port Number */
#define Col_8_PRT_NUM                (* (reg8 *) Col_8__PRT) 
/* Connect to Analog Globals */                                                  
#define Col_8_AG                     (* (reg8 *) Col_8__AG)                       
/* Analog MUX bux enable */
#define Col_8_AMUX                   (* (reg8 *) Col_8__AMUX) 
/* Bidirectional Enable */                                                        
#define Col_8_BIE                    (* (reg8 *) Col_8__BIE)
/* Bit-mask for Aliased Register Access */
#define Col_8_BIT_MASK               (* (reg8 *) Col_8__BIT_MASK)
/* Bypass Enable */
#define Col_8_BYP                    (* (reg8 *) Col_8__BYP)
/* Port wide control signals */                                                   
#define Col_8_CTL                    (* (reg8 *) Col_8__CTL)
/* Drive Modes */
#define Col_8_DM0                    (* (reg8 *) Col_8__DM0) 
#define Col_8_DM1                    (* (reg8 *) Col_8__DM1)
#define Col_8_DM2                    (* (reg8 *) Col_8__DM2) 
/* Input Buffer Disable Override */
#define Col_8_INP_DIS                (* (reg8 *) Col_8__INP_DIS)
/* LCD Common or Segment Drive */
#define Col_8_LCD_COM_SEG            (* (reg8 *) Col_8__LCD_COM_SEG)
/* Enable Segment LCD */
#define Col_8_LCD_EN                 (* (reg8 *) Col_8__LCD_EN)
/* Slew Rate Control */
#define Col_8_SLW                    (* (reg8 *) Col_8__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Col_8_PRTDSI__CAPS_SEL       (* (reg8 *) Col_8__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Col_8_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Col_8__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Col_8_PRTDSI__OE_SEL0        (* (reg8 *) Col_8__PRTDSI__OE_SEL0) 
#define Col_8_PRTDSI__OE_SEL1        (* (reg8 *) Col_8__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Col_8_PRTDSI__OUT_SEL0       (* (reg8 *) Col_8__PRTDSI__OUT_SEL0) 
#define Col_8_PRTDSI__OUT_SEL1       (* (reg8 *) Col_8__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Col_8_PRTDSI__SYNC_OUT       (* (reg8 *) Col_8__PRTDSI__SYNC_OUT) 


#if defined(Col_8__INTSTAT)  /* Interrupt Registers */

    #define Col_8_INTSTAT                (* (reg8 *) Col_8__INTSTAT)
    #define Col_8_SNAP                   (* (reg8 *) Col_8__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Col_8_H */


/* [] END OF FILE */
