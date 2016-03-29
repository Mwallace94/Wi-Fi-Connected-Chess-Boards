/*******************************************************************************
* File Name: En_Sw.h  
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

#if !defined(CY_PINS_En_Sw_H) /* Pins En_Sw_H */
#define CY_PINS_En_Sw_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "En_Sw_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    En_Sw_Write(uint8 value) ;
void    En_Sw_SetDriveMode(uint8 mode) ;
uint8   En_Sw_ReadDataReg(void) ;
uint8   En_Sw_Read(void) ;
uint8   En_Sw_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define En_Sw_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define En_Sw_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define En_Sw_DM_RES_UP          PIN_DM_RES_UP
#define En_Sw_DM_RES_DWN         PIN_DM_RES_DWN
#define En_Sw_DM_OD_LO           PIN_DM_OD_LO
#define En_Sw_DM_OD_HI           PIN_DM_OD_HI
#define En_Sw_DM_STRONG          PIN_DM_STRONG
#define En_Sw_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define En_Sw_MASK               En_Sw__MASK
#define En_Sw_SHIFT              En_Sw__SHIFT
#define En_Sw_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define En_Sw_PS                     (* (reg8 *) En_Sw__PS)
/* Data Register */
#define En_Sw_DR                     (* (reg8 *) En_Sw__DR)
/* Port Number */
#define En_Sw_PRT_NUM                (* (reg8 *) En_Sw__PRT) 
/* Connect to Analog Globals */                                                  
#define En_Sw_AG                     (* (reg8 *) En_Sw__AG)                       
/* Analog MUX bux enable */
#define En_Sw_AMUX                   (* (reg8 *) En_Sw__AMUX) 
/* Bidirectional Enable */                                                        
#define En_Sw_BIE                    (* (reg8 *) En_Sw__BIE)
/* Bit-mask for Aliased Register Access */
#define En_Sw_BIT_MASK               (* (reg8 *) En_Sw__BIT_MASK)
/* Bypass Enable */
#define En_Sw_BYP                    (* (reg8 *) En_Sw__BYP)
/* Port wide control signals */                                                   
#define En_Sw_CTL                    (* (reg8 *) En_Sw__CTL)
/* Drive Modes */
#define En_Sw_DM0                    (* (reg8 *) En_Sw__DM0) 
#define En_Sw_DM1                    (* (reg8 *) En_Sw__DM1)
#define En_Sw_DM2                    (* (reg8 *) En_Sw__DM2) 
/* Input Buffer Disable Override */
#define En_Sw_INP_DIS                (* (reg8 *) En_Sw__INP_DIS)
/* LCD Common or Segment Drive */
#define En_Sw_LCD_COM_SEG            (* (reg8 *) En_Sw__LCD_COM_SEG)
/* Enable Segment LCD */
#define En_Sw_LCD_EN                 (* (reg8 *) En_Sw__LCD_EN)
/* Slew Rate Control */
#define En_Sw_SLW                    (* (reg8 *) En_Sw__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define En_Sw_PRTDSI__CAPS_SEL       (* (reg8 *) En_Sw__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define En_Sw_PRTDSI__DBL_SYNC_IN    (* (reg8 *) En_Sw__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define En_Sw_PRTDSI__OE_SEL0        (* (reg8 *) En_Sw__PRTDSI__OE_SEL0) 
#define En_Sw_PRTDSI__OE_SEL1        (* (reg8 *) En_Sw__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define En_Sw_PRTDSI__OUT_SEL0       (* (reg8 *) En_Sw__PRTDSI__OUT_SEL0) 
#define En_Sw_PRTDSI__OUT_SEL1       (* (reg8 *) En_Sw__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define En_Sw_PRTDSI__SYNC_OUT       (* (reg8 *) En_Sw__PRTDSI__SYNC_OUT) 


#if defined(En_Sw__INTSTAT)  /* Interrupt Registers */

    #define En_Sw_INTSTAT                (* (reg8 *) En_Sw__INTSTAT)
    #define En_Sw_SNAP                   (* (reg8 *) En_Sw__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins En_Sw_H */


/* [] END OF FILE */
