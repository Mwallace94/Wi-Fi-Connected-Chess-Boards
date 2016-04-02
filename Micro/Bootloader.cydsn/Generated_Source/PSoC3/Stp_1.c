/*******************************************************************************
* File Name: Stp_1.c  
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
#include "Stp_1.h"


/*******************************************************************************
* Function Name: Stp_1_Write
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
void Stp_1_Write(uint8 value) 
{
    uint8 staticBits = (Stp_1_DR & (uint8)(~Stp_1_MASK));
    Stp_1_DR = staticBits | ((uint8)(value << Stp_1_SHIFT) & Stp_1_MASK);
}


/*******************************************************************************
* Function Name: Stp_1_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Stp_1_DM_STRONG     Strong Drive 
*  Stp_1_DM_OD_HI      Open Drain, Drives High 
*  Stp_1_DM_OD_LO      Open Drain, Drives Low 
*  Stp_1_DM_RES_UP     Resistive Pull Up 
*  Stp_1_DM_RES_DWN    Resistive Pull Down 
*  Stp_1_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Stp_1_DM_DIG_HIZ    High Impedance Digital 
*  Stp_1_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Stp_1_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Stp_1_0, mode);
}


/*******************************************************************************
* Function Name: Stp_1_Read
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
*  Macro Stp_1_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Stp_1_Read(void) 
{
    return (Stp_1_PS & Stp_1_MASK) >> Stp_1_SHIFT;
}


/*******************************************************************************
* Function Name: Stp_1_ReadDataReg
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
uint8 Stp_1_ReadDataReg(void) 
{
    return (Stp_1_DR & Stp_1_MASK) >> Stp_1_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Stp_1_INTSTAT) 

    /*******************************************************************************
    * Function Name: Stp_1_ClearInterrupt
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
    uint8 Stp_1_ClearInterrupt(void) 
    {
        return (Stp_1_INTSTAT & Stp_1_MASK) >> Stp_1_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
