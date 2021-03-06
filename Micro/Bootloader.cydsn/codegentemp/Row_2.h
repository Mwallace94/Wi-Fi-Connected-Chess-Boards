/*******************************************************************************
* File Name: Row_2.h  
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

#if !defined(CY_PINS_Row_2_H) /* Pins Row_2_H */
#define CY_PINS_Row_2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Row_2_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Row_2__PORT == 15 && ((Row_2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Row_2_Write(uint8 value) ;
void    Row_2_SetDriveMode(uint8 mode) ;
uint8   Row_2_ReadDataReg(void) ;
uint8   Row_2_Read(void) ;
uint8   Row_2_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Row_2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Row_2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Row_2_DM_RES_UP          PIN_DM_RES_UP
#define Row_2_DM_RES_DWN         PIN_DM_RES_DWN
#define Row_2_DM_OD_LO           PIN_DM_OD_LO
#define Row_2_DM_OD_HI           PIN_DM_OD_HI
#define Row_2_DM_STRONG          PIN_DM_STRONG
#define Row_2_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Row_2_MASK               Row_2__MASK
#define Row_2_SHIFT              Row_2__SHIFT
#define Row_2_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Row_2_PS                     (* (reg8 *) Row_2__PS)
/* Data Register */
#define Row_2_DR                     (* (reg8 *) Row_2__DR)
/* Port Number */
#define Row_2_PRT_NUM                (* (reg8 *) Row_2__PRT) 
/* Connect to Analog Globals */                                                  
#define Row_2_AG                     (* (reg8 *) Row_2__AG)                       
/* Analog MUX bux enable */
#define Row_2_AMUX                   (* (reg8 *) Row_2__AMUX) 
/* Bidirectional Enable */                                                        
#define Row_2_BIE                    (* (reg8 *) Row_2__BIE)
/* Bit-mask for Aliased Register Access */
#define Row_2_BIT_MASK               (* (reg8 *) Row_2__BIT_MASK)
/* Bypass Enable */
#define Row_2_BYP                    (* (reg8 *) Row_2__BYP)
/* Port wide control signals */                                                   
#define Row_2_CTL                    (* (reg8 *) Row_2__CTL)
/* Drive Modes */
#define Row_2_DM0                    (* (reg8 *) Row_2__DM0) 
#define Row_2_DM1                    (* (reg8 *) Row_2__DM1)
#define Row_2_DM2                    (* (reg8 *) Row_2__DM2) 
/* Input Buffer Disable Override */
#define Row_2_INP_DIS                (* (reg8 *) Row_2__INP_DIS)
/* LCD Common or Segment Drive */
#define Row_2_LCD_COM_SEG            (* (reg8 *) Row_2__LCD_COM_SEG)
/* Enable Segment LCD */
#define Row_2_LCD_EN                 (* (reg8 *) Row_2__LCD_EN)
/* Slew Rate Control */
#define Row_2_SLW                    (* (reg8 *) Row_2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Row_2_PRTDSI__CAPS_SEL       (* (reg8 *) Row_2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Row_2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Row_2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Row_2_PRTDSI__OE_SEL0        (* (reg8 *) Row_2__PRTDSI__OE_SEL0) 
#define Row_2_PRTDSI__OE_SEL1        (* (reg8 *) Row_2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Row_2_PRTDSI__OUT_SEL0       (* (reg8 *) Row_2__PRTDSI__OUT_SEL0) 
#define Row_2_PRTDSI__OUT_SEL1       (* (reg8 *) Row_2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Row_2_PRTDSI__SYNC_OUT       (* (reg8 *) Row_2__PRTDSI__SYNC_OUT) 


#if defined(Row_2__INTSTAT)  /* Interrupt Registers */

    #define Row_2_INTSTAT                (* (reg8 *) Row_2__INTSTAT)
    #define Row_2_SNAP                   (* (reg8 *) Row_2__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Row_2_H */


/* [] END OF FILE */
