/*******************************************************************************
* File Name: Col_11.c  
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
#include "Col_11.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 Col_11__PORT == 15 && ((Col_11__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: Col_11_Write
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
void Col_11_Write(uint8 value) 
{
    uint8 staticBits = (Col_11_DR & (uint8)(~Col_11_MASK));
    Col_11_DR = staticBits | ((uint8)(value << Col_11_SHIFT) & Col_11_MASK);
}


/*******************************************************************************
* Function Name: Col_11_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Col_11_DM_STRONG     Strong Drive 
*  Col_11_DM_OD_HI      Open Drain, Drives High 
*  Col_11_DM_OD_LO      Open Drain, Drives Low 
*  Col_11_DM_RES_UP     Resistive Pull Up 
*  Col_11_DM_RES_DWN    Resistive Pull Down 
*  Col_11_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Col_11_DM_DIG_HIZ    High Impedance Digital 
*  Col_11_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Col_11_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Col_11_0, mode);
}


/*******************************************************************************
* Function Name: Col_11_Read
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
*  Macro Col_11_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Col_11_Read(void) 
{
    return (Col_11_PS & Col_11_MASK) >> Col_11_SHIFT;
}


/*******************************************************************************
* Function Name: Col_11_ReadDataReg
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
uint8 Col_11_ReadDataReg(void) 
{
    return (Col_11_DR & Col_11_MASK) >> Col_11_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Col_11_INTSTAT) 

    /*******************************************************************************
    * Function Name: Col_11_ClearInterrupt
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
    uint8 Col_11_ClearInterrupt(void) 
    {
        return (Col_11_INTSTAT & Col_11_MASK) >> Col_11_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
