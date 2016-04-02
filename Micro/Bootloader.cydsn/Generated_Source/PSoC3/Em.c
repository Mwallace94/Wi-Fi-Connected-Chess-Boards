/*******************************************************************************
* File Name: Em.c  
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
#include "Em.h"


/*******************************************************************************
* Function Name: Em_Write
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
void Em_Write(uint8 value) 
{
    uint8 staticBits = (Em_DR & (uint8)(~Em_MASK));
    Em_DR = staticBits | ((uint8)(value << Em_SHIFT) & Em_MASK);
}


/*******************************************************************************
* Function Name: Em_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Em_DM_STRONG     Strong Drive 
*  Em_DM_OD_HI      Open Drain, Drives High 
*  Em_DM_OD_LO      Open Drain, Drives Low 
*  Em_DM_RES_UP     Resistive Pull Up 
*  Em_DM_RES_DWN    Resistive Pull Down 
*  Em_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Em_DM_DIG_HIZ    High Impedance Digital 
*  Em_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Em_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Em_0, mode);
}


/*******************************************************************************
* Function Name: Em_Read
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
*  Macro Em_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Em_Read(void) 
{
    return (Em_PS & Em_MASK) >> Em_SHIFT;
}


/*******************************************************************************
* Function Name: Em_ReadDataReg
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
uint8 Em_ReadDataReg(void) 
{
    return (Em_DR & Em_MASK) >> Em_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Em_INTSTAT) 

    /*******************************************************************************
    * Function Name: Em_ClearInterrupt
    ********************************************************************************
    *
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
    uint8 Em_ClearInterrupt(void) 
    {
        return (Em_INTSTAT & Em_MASK) >> Em_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
