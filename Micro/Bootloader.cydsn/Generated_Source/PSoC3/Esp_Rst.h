/*******************************************************************************
* File Name: Esp_Rst.h  
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

#if !defined(CY_PINS_Esp_Rst_H) /* Pins Esp_Rst_H */
#define CY_PINS_Esp_Rst_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Esp_Rst_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Esp_Rst_Write(uint8 value) ;
void    Esp_Rst_SetDriveMode(uint8 mode) ;
uint8   Esp_Rst_ReadDataReg(void) ;
uint8   Esp_Rst_Read(void) ;
uint8   Esp_Rst_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Esp_Rst_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Esp_Rst_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Esp_Rst_DM_RES_UP          PIN_DM_RES_UP
#define Esp_Rst_DM_RES_DWN         PIN_DM_RES_DWN
#define Esp_Rst_DM_OD_LO           PIN_DM_OD_LO
#define Esp_Rst_DM_OD_HI           PIN_DM_OD_HI
#define Esp_Rst_DM_STRONG          PIN_DM_STRONG
#define Esp_Rst_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Esp_Rst_MASK               Esp_Rst__MASK
#define Esp_Rst_SHIFT              Esp_Rst__SHIFT
#define Esp_Rst_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Esp_Rst_PS                     (* (reg8 *) Esp_Rst__PS)
/* Data Register */
#define Esp_Rst_DR                     (* (reg8 *) Esp_Rst__DR)
/* Port Number */
#define Esp_Rst_PRT_NUM                (* (reg8 *) Esp_Rst__PRT) 
/* Connect to Analog Globals */                                                  
#define Esp_Rst_AG                     (* (reg8 *) Esp_Rst__AG)                       
/* Analog MUX bux enable */
#define Esp_Rst_AMUX                   (* (reg8 *) Esp_Rst__AMUX) 
/* Bidirectional Enable */                                                        
#define Esp_Rst_BIE                    (* (reg8 *) Esp_Rst__BIE)
/* Bit-mask for Aliased Register Access */
#define Esp_Rst_BIT_MASK               (* (reg8 *) Esp_Rst__BIT_MASK)
/* Bypass Enable */
#define Esp_Rst_BYP                    (* (reg8 *) Esp_Rst__BYP)
/* Port wide control signals */                                                   
#define Esp_Rst_CTL                    (* (reg8 *) Esp_Rst__CTL)
/* Drive Modes */
#define Esp_Rst_DM0                    (* (reg8 *) Esp_Rst__DM0) 
#define Esp_Rst_DM1                    (* (reg8 *) Esp_Rst__DM1)
#define Esp_Rst_DM2                    (* (reg8 *) Esp_Rst__DM2) 
/* Input Buffer Disable Override */
#define Esp_Rst_INP_DIS                (* (reg8 *) Esp_Rst__INP_DIS)
/* LCD Common or Segment Drive */
#define Esp_Rst_LCD_COM_SEG            (* (reg8 *) Esp_Rst__LCD_COM_SEG)
/* Enable Segment LCD */
#define Esp_Rst_LCD_EN                 (* (reg8 *) Esp_Rst__LCD_EN)
/* Slew Rate Control */
#define Esp_Rst_SLW                    (* (reg8 *) Esp_Rst__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Esp_Rst_PRTDSI__CAPS_SEL       (* (reg8 *) Esp_Rst__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Esp_Rst_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Esp_Rst__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Esp_Rst_PRTDSI__OE_SEL0        (* (reg8 *) Esp_Rst__PRTDSI__OE_SEL0) 
#define Esp_Rst_PRTDSI__OE_SEL1        (* (reg8 *) Esp_Rst__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Esp_Rst_PRTDSI__OUT_SEL0       (* (reg8 *) Esp_Rst__PRTDSI__OUT_SEL0) 
#define Esp_Rst_PRTDSI__OUT_SEL1       (* (reg8 *) Esp_Rst__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Esp_Rst_PRTDSI__SYNC_OUT       (* (reg8 *) Esp_Rst__PRTDSI__SYNC_OUT) 


#if defined(Esp_Rst__INTSTAT)  /* Interrupt Registers */

    #define Esp_Rst_INTSTAT                (* (reg8 *) Esp_Rst__INTSTAT)
    #define Esp_Rst_SNAP                   (* (reg8 *) Esp_Rst__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Esp_Rst_H */


/* [] END OF FILE */
