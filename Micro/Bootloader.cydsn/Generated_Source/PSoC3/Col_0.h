/*******************************************************************************
* File Name: Col_0.h  
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

#if !defined(CY_PINS_Col_0_H) /* Pins Col_0_H */
#define CY_PINS_Col_0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Col_0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Col_0_Write(uint8 value) ;
void    Col_0_SetDriveMode(uint8 mode) ;
uint8   Col_0_ReadDataReg(void) ;
uint8   Col_0_Read(void) ;
uint8   Col_0_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Col_0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Col_0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Col_0_DM_RES_UP          PIN_DM_RES_UP
#define Col_0_DM_RES_DWN         PIN_DM_RES_DWN
#define Col_0_DM_OD_LO           PIN_DM_OD_LO
#define Col_0_DM_OD_HI           PIN_DM_OD_HI
#define Col_0_DM_STRONG          PIN_DM_STRONG
#define Col_0_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Col_0_MASK               Col_0__MASK
#define Col_0_SHIFT              Col_0__SHIFT
#define Col_0_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Col_0_PS                     (* (reg8 *) Col_0__PS)
/* Data Register */
#define Col_0_DR                     (* (reg8 *) Col_0__DR)
/* Port Number */
#define Col_0_PRT_NUM                (* (reg8 *) Col_0__PRT) 
/* Connect to Analog Globals */                                                  
#define Col_0_AG                     (* (reg8 *) Col_0__AG)                       
/* Analog MUX bux enable */
#define Col_0_AMUX                   (* (reg8 *) Col_0__AMUX) 
/* Bidirectional Enable */                                                        
#define Col_0_BIE                    (* (reg8 *) Col_0__BIE)
/* Bit-mask for Aliased Register Access */
#define Col_0_BIT_MASK               (* (reg8 *) Col_0__BIT_MASK)
/* Bypass Enable */
#define Col_0_BYP                    (* (reg8 *) Col_0__BYP)
/* Port wide control signals */                                                   
#define Col_0_CTL                    (* (reg8 *) Col_0__CTL)
/* Drive Modes */
#define Col_0_DM0                    (* (reg8 *) Col_0__DM0) 
#define Col_0_DM1                    (* (reg8 *) Col_0__DM1)
#define Col_0_DM2                    (* (reg8 *) Col_0__DM2) 
/* Input Buffer Disable Override */
#define Col_0_INP_DIS                (* (reg8 *) Col_0__INP_DIS)
/* LCD Common or Segment Drive */
#define Col_0_LCD_COM_SEG            (* (reg8 *) Col_0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Col_0_LCD_EN                 (* (reg8 *) Col_0__LCD_EN)
/* Slew Rate Control */
#define Col_0_SLW                    (* (reg8 *) Col_0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Col_0_PRTDSI__CAPS_SEL       (* (reg8 *) Col_0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Col_0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Col_0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Col_0_PRTDSI__OE_SEL0        (* (reg8 *) Col_0__PRTDSI__OE_SEL0) 
#define Col_0_PRTDSI__OE_SEL1        (* (reg8 *) Col_0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Col_0_PRTDSI__OUT_SEL0       (* (reg8 *) Col_0__PRTDSI__OUT_SEL0) 
#define Col_0_PRTDSI__OUT_SEL1       (* (reg8 *) Col_0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Col_0_PRTDSI__SYNC_OUT       (* (reg8 *) Col_0__PRTDSI__SYNC_OUT) 


#if defined(Col_0__INTSTAT)  /* Interrupt Registers */

    #define Col_0_INTSTAT                (* (reg8 *) Col_0__INTSTAT)
    #define Col_0_SNAP                   (* (reg8 *) Col_0__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Col_0_H */


/* [] END OF FILE */
