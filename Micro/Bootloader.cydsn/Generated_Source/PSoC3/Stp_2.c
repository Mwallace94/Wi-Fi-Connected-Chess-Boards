/*******************************************************************************
* File Name: Stp_2.c  
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
#include "Stp_2.h"


/*******************************************************************************
* Function Name: Stp_2_Write
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
void Stp_2_Write(uint8 value) 
{
    uint8 staticBits = (Stp_2_DR & (uint8)(~Stp_2_MASK));
    Stp_2_DR = staticBits | ((uint8)(value << Stp_2_SHIFT) & Stp_2_MASK);
}


/*******************************************************************************
* Function Name: Stp_2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Stp_2_DM_STRONG     Strong Drive 
*  Stp_2_DM_OD_HI      Open Drain, Drives High 
*  Stp_2_DM_OD_LO      Open Drain, Drives Low 
*  Stp_2_DM_RES_UP     Resistive Pull Up 
*  Stp_2_DM_RES_DWN    Resistive Pull Down 
*  Stp_2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Stp_2_DM_DIG_HIZ    High Impedance Digital 
*  Stp_2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Stp_2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Stp_2_0, mode);
}


/*******************************************************************************
* Function Name: Stp_2_Read
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
*  Macro Stp_2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Stp_2_Read(void) 
{
    return (Stp_2_PS & Stp_2_MASK) >> Stp_2_SHIFT;
}


/*******************************************************************************
* Function Name: Stp_2_ReadDataReg
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
uint8 Stp_2_ReadDataReg(void) 
{
    return (Stp_2_DR & Stp_2_MASK) >> Stp_2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Stp_2_INTSTAT) 

    /*******************************************************************************
    * Function Name: Stp_2_ClearInterrupt
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
    uint8 Stp_2_ClearInterrupt(void) 
    {
        return (Stp_2_INTSTAT & Stp_2_MASK) >> Stp_2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
