/*******************************************************************************
* File Name: Row.c  
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
#include "Row.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Row__PORT == 15 && ((Row__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Row_Write
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
void Row_Write(uint8 value) 
{
    uint8 staticBits = (Row_DR & (uint8)(~Row_MASK));
    Row_DR = staticBits | ((uint8)(value << Row_SHIFT) & Row_MASK);
}


/*******************************************************************************
* Function Name: Row_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Row_DM_STRONG     Strong Drive 
*  Row_DM_OD_HI      Open Drain, Drives High 
*  Row_DM_OD_LO      Open Drain, Drives Low 
*  Row_DM_RES_UP     Resistive Pull Up 
*  Row_DM_RES_DWN    Resistive Pull Down 
*  Row_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Row_DM_DIG_HIZ    High Impedance Digital 
*  Row_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Row_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Row_0, mode);
	CyPins_SetPinDriveMode(Row_1, mode);
	CyPins_SetPinDriveMode(Row_2, mode);
	CyPins_SetPinDriveMode(Row_3, mode);
	CyPins_SetPinDriveMode(Row_4, mode);
	CyPins_SetPinDriveMode(Row_5, mode);
	CyPins_SetPinDriveMode(Row_6, mode);
	CyPins_SetPinDriveMode(Row_7, mode);
}


/*******************************************************************************
* Function Name: Row_Read
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
*  Macro Row_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Row_Read(void) 
{
    return (Row_PS & Row_MASK) >> Row_SHIFT;
}


/*******************************************************************************
* Function Name: Row_ReadDataReg
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
uint8 Row_ReadDataReg(void) 
{
    return (Row_DR & Row_MASK) >> Row_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Row_INTSTAT) 

    /*******************************************************************************
    * Function Name: Row_ClearInterrupt
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
    uint8 Row_ClearInterrupt(void) 
    {
        return (Row_INTSTAT & Row_MASK) >> Row_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
