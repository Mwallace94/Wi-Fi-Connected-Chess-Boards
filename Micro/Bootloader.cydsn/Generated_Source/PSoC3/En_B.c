/*******************************************************************************
* File Name: En_B.c  
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
#include "En_B.h"


/*******************************************************************************
* Function Name: En_B_Write
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
void En_B_Write(uint8 value) 
{
    uint8 staticBits = (En_B_DR & (uint8)(~En_B_MASK));
    En_B_DR = staticBits | ((uint8)(value << En_B_SHIFT) & En_B_MASK);
}


/*******************************************************************************
* Function Name: En_B_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  En_B_DM_STRONG     Strong Drive 
*  En_B_DM_OD_HI      Open Drain, Drives High 
*  En_B_DM_OD_LO      Open Drain, Drives Low 
*  En_B_DM_RES_UP     Resistive Pull Up 
*  En_B_DM_RES_DWN    Resistive Pull Down 
*  En_B_DM_RES_UPDWN  Resistive Pull Up/Down 
*  En_B_DM_DIG_HIZ    High Impedance Digital 
*  En_B_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void En_B_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(En_B_0, mode);
}


/*******************************************************************************
* Function Name: En_B_Read
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
*  Macro En_B_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 En_B_Read(void) 
{
    return (En_B_PS & En_B_MASK) >> En_B_SHIFT;
}


/*******************************************************************************
* Function Name: En_B_ReadDataReg
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
uint8 En_B_ReadDataReg(void) 
{
    return (En_B_DR & En_B_MASK) >> En_B_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(En_B_INTSTAT) 

    /*******************************************************************************
    * Function Name: En_B_ClearInterrupt
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
    uint8 En_B_ClearInterrupt(void) 
    {
        return (En_B_INTSTAT & En_B_MASK) >> En_B_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
