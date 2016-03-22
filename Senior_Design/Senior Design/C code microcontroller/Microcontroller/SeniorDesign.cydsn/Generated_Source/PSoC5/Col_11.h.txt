/*******************************************************************************
* File Name: Col_11.h  
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

#if !defined(CY_PINS_Col_11_H) /* Pins Col_11_H */
#define CY_PINS_Col_11_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Col_11_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Col_11__PORT == 15 && ((Col_11__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    Col_11_Write(uint8 value) ;
void    Col_11_SetDriveMode(uint8 mode) ;
uint8   Col_11_ReadDataReg(void) ;
uint8   Col_11_Read(void) ;
uint8   Col_11_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Col_11_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Col_11_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Col_11_DM_RES_UP          PIN_DM_RES_UP
#define Col_11_DM_RES_DWN         PIN_DM_RES_DWN
#define Col_11_DM_OD_LO           PIN_DM_OD_LO
#define Col_11_DM_OD_HI           PIN_DM_OD_HI
#define Col_11_DM_STRONG          PIN_DM_STRONG
#define Col_11_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Col_11_MASK               Col_11__MASK
#define Col_11_SHIFT              Col_11__SHIFT
#define Col_11_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Col_11_PS                     (* (reg8 *) Col_11__PS)
/* Data Register */
#define Col_11_DR                     (* (reg8 *) Col_11__DR)
/* Port Number */
#define Col_11_PRT_NUM                (* (reg8 *) Col_11__PRT) 
/* Connect to Analog Globals */                                                  
#define Col_11_AG                     (* (reg8 *) Col_11__AG)                       
/* Analog MUX bux enable */
#define Col_11_AMUX                   (* (reg8 *) Col_11__AMUX) 
/* Bidirectional Enable */                                                        
#define Col_11_BIE                    (* (reg8 *) Col_11__BIE)
/* Bit-mask for Aliased Register Access */
#define Col_11_BIT_MASK               (* (reg8 *) Col_11__BIT_MASK)
/* Bypass Enable */
#define Col_11_BYP                    (* (reg8 *) Col_11__BYP)
/* Port wide control signals */                                                   
#define Col_11_CTL                    (* (reg8 *) Col_11__CTL)
/* Drive Modes */
#define Col_11_DM0                    (* (reg8 *) Col_11__DM0) 
#define Col_11_DM1                    (* (reg8 *) Col_11__DM1)
#define Col_11_DM2                    (* (reg8 *) Col_11__DM2) 
/* Input Buffer Disable Override */
#define Col_11_INP_DIS                (* (reg8 *) Col_11__INP_DIS)
/* LCD Common or Segment Drive */
#define Col_11_LCD_COM_SEG            (* (reg8 *) Col_11__LCD_COM_SEG)
/* Enable Segment LCD */
#define Col_11_LCD_EN                 (* (reg8 *) Col_11__LCD_EN)
/* Slew Rate Control */
#define Col_11_SLW                    (* (reg8 *) Col_11__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Col_11_PRTDSI__CAPS_SEL       (* (reg8 *) Col_11__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Col_11_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Col_11__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Col_11_PRTDSI__OE_SEL0        (* (reg8 *) Col_11__PRTDSI__OE_SEL0) 
#define Col_11_PRTDSI__OE_SEL1        (* (reg8 *) Col_11__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Col_11_PRTDSI__OUT_SEL0       (* (reg8 *) Col_11__PRTDSI__OUT_SEL0) 
#define Col_11_PRTDSI__OUT_SEL1       (* (reg8 *) Col_11__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Col_11_PRTDSI__SYNC_OUT       (* (reg8 *) Col_11__PRTDSI__SYNC_OUT) 


#if defined(Col_11__INTSTAT)  /* Interrupt Registers */

    #define Col_11_INTSTAT                (* (reg8 *) Col_11__INTSTAT)
    #define Col_11_SNAP                   (* (reg8 *) Col_11__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Col_11_H */


/* [] END OF FILE */
