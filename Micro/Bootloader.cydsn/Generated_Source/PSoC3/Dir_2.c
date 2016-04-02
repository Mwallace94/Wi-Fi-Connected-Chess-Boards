/*******************************************************************************
* File Name: Dir_2.c  
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
#include "Dir_2.h"


/*******************************************************************************
* Function Name: Dir_2_Write
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
void Dir_2_Write(uint8 value) 
{
    uint8 staticBits = (Dir_2_DR & (uint8)(~Dir_2_MASK));
    Dir_2_DR = staticBits | ((uint8)(value << Dir_2_SHIFT) & Dir_2_MASK);
}


/*******************************************************************************
* Function Name: Dir_2_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Dir_2_DM_STRONG     Strong Drive 
*  Dir_2_DM_OD_HI      Open Drain, Drives High 
*  Dir_2_DM_OD_LO      Open Drain, Drives Low 
*  Dir_2_DM_RES_UP     Resistive Pull Up 
*  Dir_2_DM_RES_DWN    Resistive Pull Down 
*  Dir_2_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Dir_2_DM_DIG_HIZ    High Impedance Digital 
*  Dir_2_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Dir_2_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Dir_2_0, mode);
}


/*******************************************************************************
* Function Name: Dir_2_Read
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
*  Macro Dir_2_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Dir_2_Read(void) 
{
    return (Dir_2_PS & Dir_2_MASK) >> Dir_2_SHIFT;
}


/*******************************************************************************
* Function Name: Dir_2_ReadDataReg
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
uint8 Dir_2_ReadDataReg(void) 
{
    return (Dir_2_DR & Dir_2_MASK) >> Dir_2_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Dir_2_INTSTAT) 

    /*******************************************************************************
    * Function Name: Dir_2_ClearInterrupt
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
    uint8 Dir_2_ClearInterrupt(void) 
    {
        return (Dir_2_INTSTAT & Dir_2_MASK) >> Dir_2_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
