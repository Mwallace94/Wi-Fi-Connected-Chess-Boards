/*******************************************************************************
* File Name: Esp_UART_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Esp_UART.h"


/***************************************
* Local data allocation
***************************************/

static Esp_UART_BACKUP_STRUCT  Esp_UART_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: Esp_UART_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the Esp_UART_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Esp_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Esp_UART_SaveConfig(void)
{
    #if(Esp_UART_CONTROL_REG_REMOVED == 0u)
        Esp_UART_backup.cr = Esp_UART_CONTROL_REG;
    #endif /* End Esp_UART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Esp_UART_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Esp_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling Esp_UART_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void Esp_UART_RestoreConfig(void)
{
    #if(Esp_UART_CONTROL_REG_REMOVED == 0u)
        Esp_UART_CONTROL_REG = Esp_UART_backup.cr;
    #endif /* End Esp_UART_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: Esp_UART_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The Esp_UART_Sleep() API saves the current component state. Then it
*  calls the Esp_UART_Stop() function and calls 
*  Esp_UART_SaveConfig() to save the hardware configuration.
*  Call the Esp_UART_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Esp_UART_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Esp_UART_Sleep(void)
{
    #if(Esp_UART_RX_ENABLED || Esp_UART_HD_ENABLED)
        if((Esp_UART_RXSTATUS_ACTL_REG  & Esp_UART_INT_ENABLE) != 0u)
        {
            Esp_UART_backup.enableState = 1u;
        }
        else
        {
            Esp_UART_backup.enableState = 0u;
        }
    #else
        if((Esp_UART_TXSTATUS_ACTL_REG  & Esp_UART_INT_ENABLE) !=0u)
        {
            Esp_UART_backup.enableState = 1u;
        }
        else
        {
            Esp_UART_backup.enableState = 0u;
        }
    #endif /* End Esp_UART_RX_ENABLED || Esp_UART_HD_ENABLED*/

    Esp_UART_Stop();
    Esp_UART_SaveConfig();
}


/*******************************************************************************
* Function Name: Esp_UART_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  Esp_UART_Sleep() was called. The Esp_UART_Wakeup() function
*  calls the Esp_UART_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  Esp_UART_Sleep() function was called, the Esp_UART_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  Esp_UART_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void Esp_UART_Wakeup(void)
{
    Esp_UART_RestoreConfig();
    #if( (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) )
        Esp_UART_ClearRxBuffer();
    #endif /* End (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) */
    #if(Esp_UART_TX_ENABLED || Esp_UART_HD_ENABLED)
        Esp_UART_ClearTxBuffer();
    #endif /* End Esp_UART_TX_ENABLED || Esp_UART_HD_ENABLED */

    if(Esp_UART_backup.enableState != 0u)
    {
        Esp_UART_Enable();
    }
}


/* [] END OF FILE */
