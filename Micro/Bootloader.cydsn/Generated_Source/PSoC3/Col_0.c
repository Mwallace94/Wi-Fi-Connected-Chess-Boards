/*******************************************************************************
* File Name: Col_0.c  
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
#include "Col_0.h"


/*******************************************************************************
* Function Name: Col_0_Write
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
void Col_0_Write(uint8 value) 
{
    uint8 staticBits = (Col_0_DR & (uint8)(~Col_0_MASK));
    Col_0_DR = staticBits | ((uint8)(value << Col_0_SHIFT) & Col_0_MASK);
}


/*******************************************************************************
* Function Name: Col_0_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Col_0_DM_STRONG     Strong Drive 
*  Col_0_DM_OD_HI      Open Drain, Drives High 
*  Col_0_DM_OD_LO      Open Drain, Drives Low 
*  Col_0_DM_RES_UP     Resistive Pull Up 
*  Col_0_DM_RES_DWN    Resistive Pull Down 
*  Col_0_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Col_0_DM_DIG_HIZ    High Impedance Digital 
*  Col_0_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Col_0_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Col_0_0, mode);
}


/*******************************************************************************
* Function Name: Col_0_Read
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
*  Macro Col_0_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Col_0_Read(void) 
{
    return (Col_0_PS & Col_0_MASK) >> Col_0_SHIFT;
}


/*******************************************************************************
* Function Name: Col_0_ReadDataReg
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
uint8 Col_0_ReadDataReg(void) 
{
    return (Col_0_DR & Col_0_MASK) >> Col_0_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Col_0_INTSTAT) 

    /*******************************************************************************
    * Function Name: Col_0_ClearInterrupt
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
    uint8 Col_0_ClearInterrupt(void) 
    {
        return (Col_0_INTSTAT & Col_0_MASK) >> Col_0_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
