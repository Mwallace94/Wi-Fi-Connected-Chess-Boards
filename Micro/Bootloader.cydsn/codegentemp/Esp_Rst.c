/*******************************************************************************
* File Name: Esp_Rst.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Esp_Rst.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Esp_Rst__PORT == 15 && ((Esp_Rst__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Esp_Rst_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void Esp_Rst_Write(uint8 value) 
{
    uint8 staticBits = (Esp_Rst_DR & (uint8)(~Esp_Rst_MASK));
    Esp_Rst_DR = staticBits | ((uint8)(value << Esp_Rst_SHIFT) & Esp_Rst_MASK);
}


/*******************************************************************************
* Function Name: Esp_Rst_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Esp_Rst_DM_STRONG     Strong Drive 
*  Esp_Rst_DM_OD_HI      Open Drain, Drives High 
*  Esp_Rst_DM_OD_LO      Open Drain, Drives Low 
*  Esp_Rst_DM_RES_UP     Resistive Pull Up 
*  Esp_Rst_DM_RES_DWN    Resistive Pull Down 
*  Esp_Rst_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Esp_Rst_DM_DIG_HIZ    High Impedance Digital 
*  Esp_Rst_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Esp_Rst_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Esp_Rst_0, mode);
}


/*******************************************************************************
* Function Name: Esp_Rst_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Esp_Rst_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Esp_Rst_Read(void) 
{
    return (Esp_Rst_PS & Esp_Rst_MASK) >> Esp_Rst_SHIFT;
}


/*******************************************************************************
* Function Name: Esp_Rst_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Esp_Rst_ReadDataReg(void) 
{
    return (Esp_Rst_DR & Esp_Rst_MASK) >> Esp_Rst_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Esp_Rst_INTSTAT) 

    /*******************************************************************************
    * Function Name: Esp_Rst_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Esp_Rst_ClearInterrupt(void) 
    {
        return (Esp_Rst_INTSTAT & Esp_Rst_MASK) >> Esp_Rst_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
