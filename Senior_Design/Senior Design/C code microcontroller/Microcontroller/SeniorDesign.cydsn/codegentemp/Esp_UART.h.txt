/*******************************************************************************
* File Name: Esp_UART.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_Esp_UART_H)
#define CY_UART_Esp_UART_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define Esp_UART_RX_ENABLED                     (1u)
#define Esp_UART_TX_ENABLED                     (1u)
#define Esp_UART_HD_ENABLED                     (0u)
#define Esp_UART_RX_INTERRUPT_ENABLED           (1u)
#define Esp_UART_TX_INTERRUPT_ENABLED           (1u)
#define Esp_UART_INTERNAL_CLOCK_USED            (1u)
#define Esp_UART_RXHW_ADDRESS_ENABLED           (0u)
#define Esp_UART_OVER_SAMPLE_COUNT              (8u)
#define Esp_UART_PARITY_TYPE                    (0u)
#define Esp_UART_PARITY_TYPE_SW                 (0u)
#define Esp_UART_BREAK_DETECT                   (0u)
#define Esp_UART_BREAK_BITS_TX                  (13u)
#define Esp_UART_BREAK_BITS_RX                  (13u)
#define Esp_UART_TXCLKGEN_DP                    (1u)
#define Esp_UART_USE23POLLING                   (1u)
#define Esp_UART_FLOW_CONTROL                   (0u)
#define Esp_UART_CLK_FREQ                       (0u)
#define Esp_UART_TX_BUFFER_SIZE                 (64u)
#define Esp_UART_RX_BUFFER_SIZE                 (64u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(Esp_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define Esp_UART_CONTROL_REG_REMOVED            (0u)
#else
    #define Esp_UART_CONTROL_REG_REMOVED            (1u)
#endif /* End Esp_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct Esp_UART_backupStruct_
{
    uint8 enableState;

    #if(Esp_UART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End Esp_UART_CONTROL_REG_REMOVED */

} Esp_UART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void Esp_UART_Start(void) ;
void Esp_UART_Stop(void) ;
uint8 Esp_UART_ReadControlRegister(void) ;
void Esp_UART_WriteControlRegister(uint8 control) ;

void Esp_UART_Init(void) ;
void Esp_UART_Enable(void) ;
void Esp_UART_SaveConfig(void) ;
void Esp_UART_RestoreConfig(void) ;
void Esp_UART_Sleep(void) ;
void Esp_UART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) )

    #if (Esp_UART_RX_INTERRUPT_ENABLED)
        #define Esp_UART_EnableRxInt()  CyIntEnable (Esp_UART_RX_VECT_NUM)
        #define Esp_UART_DisableRxInt() CyIntDisable(Esp_UART_RX_VECT_NUM)
        CY_ISR_PROTO(Esp_UART_RXISR);
    #endif /* Esp_UART_RX_INTERRUPT_ENABLED */

    void Esp_UART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void Esp_UART_SetRxAddress1(uint8 address) ;
    void Esp_UART_SetRxAddress2(uint8 address) ;

    void  Esp_UART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 Esp_UART_ReadRxData(void) ;
    uint8 Esp_UART_ReadRxStatus(void) ;
    uint8 Esp_UART_GetChar(void) ;
    uint16 Esp_UART_GetByte(void) ;
    uint8 Esp_UART_GetRxBufferSize(void)
                                                            ;
    void Esp_UART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define Esp_UART_GetRxInterruptSource   Esp_UART_ReadRxStatus

#endif /* End (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) */

/* Only if TX is enabled */
#if(Esp_UART_TX_ENABLED || Esp_UART_HD_ENABLED)

    #if(Esp_UART_TX_INTERRUPT_ENABLED)
        #define Esp_UART_EnableTxInt()  CyIntEnable (Esp_UART_TX_VECT_NUM)
        #define Esp_UART_DisableTxInt() CyIntDisable(Esp_UART_TX_VECT_NUM)
        #define Esp_UART_SetPendingTxInt() CyIntSetPending(Esp_UART_TX_VECT_NUM)
        #define Esp_UART_ClearPendingTxInt() CyIntClearPending(Esp_UART_TX_VECT_NUM)
        CY_ISR_PROTO(Esp_UART_TXISR);
    #endif /* Esp_UART_TX_INTERRUPT_ENABLED */

    void Esp_UART_SetTxInterruptMode(uint8 intSrc) ;
    void Esp_UART_WriteTxData(uint8 txDataByte) ;
    uint8 Esp_UART_ReadTxStatus(void) ;
    void Esp_UART_PutChar(uint8 txDataByte) ;
    void Esp_UART_PutString(const char8 string[]) ;
    void Esp_UART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void Esp_UART_PutCRLF(uint8 txDataByte) ;
    void Esp_UART_ClearTxBuffer(void) ;
    void Esp_UART_SetTxAddressMode(uint8 addressMode) ;
    void Esp_UART_SendBreak(uint8 retMode) ;
    uint8 Esp_UART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define Esp_UART_PutStringConst         Esp_UART_PutString
    #define Esp_UART_PutArrayConst          Esp_UART_PutArray
    #define Esp_UART_GetTxInterruptSource   Esp_UART_ReadTxStatus

#endif /* End Esp_UART_TX_ENABLED || Esp_UART_HD_ENABLED */

#if(Esp_UART_HD_ENABLED)
    void Esp_UART_LoadRxConfig(void) ;
    void Esp_UART_LoadTxConfig(void) ;
#endif /* End Esp_UART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Esp_UART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    Esp_UART_CyBtldrCommStart(void) CYSMALL ;
    void    Esp_UART_CyBtldrCommStop(void) CYSMALL ;
    void    Esp_UART_CyBtldrCommReset(void) CYSMALL ;
    cystatus Esp_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus Esp_UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Esp_UART)
        #define CyBtldrCommStart    Esp_UART_CyBtldrCommStart
        #define CyBtldrCommStop     Esp_UART_CyBtldrCommStop
        #define CyBtldrCommReset    Esp_UART_CyBtldrCommReset
        #define CyBtldrCommWrite    Esp_UART_CyBtldrCommWrite
        #define CyBtldrCommRead     Esp_UART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Esp_UART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define Esp_UART_BYTE2BYTE_TIME_OUT (25u)
    #define Esp_UART_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define Esp_UART_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define Esp_UART_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define Esp_UART_SET_SPACE      (0x00u)
#define Esp_UART_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (Esp_UART_TX_ENABLED) || (Esp_UART_HD_ENABLED) )
    #if(Esp_UART_TX_INTERRUPT_ENABLED)
        #define Esp_UART_TX_VECT_NUM            (uint8)Esp_UART_TXInternalInterrupt__INTC_NUMBER
        #define Esp_UART_TX_PRIOR_NUM           (uint8)Esp_UART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Esp_UART_TX_INTERRUPT_ENABLED */

    #define Esp_UART_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define Esp_UART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define Esp_UART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(Esp_UART_TX_ENABLED)
        #define Esp_UART_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (Esp_UART_HD_ENABLED) */
        #define Esp_UART_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (Esp_UART_TX_ENABLED) */

    #define Esp_UART_TX_STS_COMPLETE            (uint8)(0x01u << Esp_UART_TX_STS_COMPLETE_SHIFT)
    #define Esp_UART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << Esp_UART_TX_STS_FIFO_EMPTY_SHIFT)
    #define Esp_UART_TX_STS_FIFO_FULL           (uint8)(0x01u << Esp_UART_TX_STS_FIFO_FULL_SHIFT)
    #define Esp_UART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << Esp_UART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (Esp_UART_TX_ENABLED) || (Esp_UART_HD_ENABLED)*/

#if( (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) )
    #if(Esp_UART_RX_INTERRUPT_ENABLED)
        #define Esp_UART_RX_VECT_NUM            (uint8)Esp_UART_RXInternalInterrupt__INTC_NUMBER
        #define Esp_UART_RX_PRIOR_NUM           (uint8)Esp_UART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* Esp_UART_RX_INTERRUPT_ENABLED */
    #define Esp_UART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define Esp_UART_RX_STS_BREAK_SHIFT             (0x01u)
    #define Esp_UART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define Esp_UART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define Esp_UART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define Esp_UART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define Esp_UART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define Esp_UART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define Esp_UART_RX_STS_MRKSPC           (uint8)(0x01u << Esp_UART_RX_STS_MRKSPC_SHIFT)
    #define Esp_UART_RX_STS_BREAK            (uint8)(0x01u << Esp_UART_RX_STS_BREAK_SHIFT)
    #define Esp_UART_RX_STS_PAR_ERROR        (uint8)(0x01u << Esp_UART_RX_STS_PAR_ERROR_SHIFT)
    #define Esp_UART_RX_STS_STOP_ERROR       (uint8)(0x01u << Esp_UART_RX_STS_STOP_ERROR_SHIFT)
    #define Esp_UART_RX_STS_OVERRUN          (uint8)(0x01u << Esp_UART_RX_STS_OVERRUN_SHIFT)
    #define Esp_UART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << Esp_UART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define Esp_UART_RX_STS_ADDR_MATCH       (uint8)(0x01u << Esp_UART_RX_STS_ADDR_MATCH_SHIFT)
    #define Esp_UART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << Esp_UART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define Esp_UART_RX_HW_MASK                     (0x7Fu)
#endif /* End (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) */

/* Control Register definitions */
#define Esp_UART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define Esp_UART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define Esp_UART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define Esp_UART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define Esp_UART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define Esp_UART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define Esp_UART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define Esp_UART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define Esp_UART_CTRL_HD_SEND               (uint8)(0x01u << Esp_UART_CTRL_HD_SEND_SHIFT)
#define Esp_UART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << Esp_UART_CTRL_HD_SEND_BREAK_SHIFT)
#define Esp_UART_CTRL_MARK                  (uint8)(0x01u << Esp_UART_CTRL_MARK_SHIFT)
#define Esp_UART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << Esp_UART_CTRL_PARITY_TYPE0_SHIFT)
#define Esp_UART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << Esp_UART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define Esp_UART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define Esp_UART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define Esp_UART_SEND_BREAK                         (0x00u)
#define Esp_UART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define Esp_UART_REINIT                             (0x02u)
#define Esp_UART_SEND_WAIT_REINIT                   (0x03u)

#define Esp_UART_OVER_SAMPLE_8                      (8u)
#define Esp_UART_OVER_SAMPLE_16                     (16u)

#define Esp_UART_BIT_CENTER                         (Esp_UART_OVER_SAMPLE_COUNT - 2u)

#define Esp_UART_FIFO_LENGTH                        (4u)
#define Esp_UART_NUMBER_OF_START_BIT                (1u)
#define Esp_UART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define Esp_UART_TXBITCTR_BREAKBITS8X   ((Esp_UART_BREAK_BITS_TX * Esp_UART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define Esp_UART_TXBITCTR_BREAKBITS ((Esp_UART_BREAK_BITS_TX * Esp_UART_OVER_SAMPLE_COUNT) - 1u)

#define Esp_UART_HALF_BIT_COUNT   \
                            (((Esp_UART_OVER_SAMPLE_COUNT / 2u) + (Esp_UART_USE23POLLING * 1u)) - 2u)
#if (Esp_UART_OVER_SAMPLE_COUNT == Esp_UART_OVER_SAMPLE_8)
    #define Esp_UART_HD_TXBITCTR_INIT   (((Esp_UART_BREAK_BITS_TX + \
                            Esp_UART_NUMBER_OF_START_BIT) * Esp_UART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define Esp_UART_RXBITCTR_INIT  ((((Esp_UART_BREAK_BITS_RX + Esp_UART_NUMBER_OF_START_BIT) \
                            * Esp_UART_OVER_SAMPLE_COUNT) + Esp_UART_HALF_BIT_COUNT) - 1u)

#else /* Esp_UART_OVER_SAMPLE_COUNT == Esp_UART_OVER_SAMPLE_16 */
    #define Esp_UART_HD_TXBITCTR_INIT   ((8u * Esp_UART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define Esp_UART_RXBITCTR_INIT      (((7u * Esp_UART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      Esp_UART_HALF_BIT_COUNT)
#endif /* End Esp_UART_OVER_SAMPLE_COUNT */

#define Esp_UART_HD_RXBITCTR_INIT                   Esp_UART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 Esp_UART_initVar;
#if (Esp_UART_TX_INTERRUPT_ENABLED && Esp_UART_TX_ENABLED)
    extern volatile uint8 Esp_UART_txBuffer[Esp_UART_TX_BUFFER_SIZE];
    extern volatile uint8 Esp_UART_txBufferRead;
    extern uint8 Esp_UART_txBufferWrite;
#endif /* (Esp_UART_TX_INTERRUPT_ENABLED && Esp_UART_TX_ENABLED) */
#if (Esp_UART_RX_INTERRUPT_ENABLED && (Esp_UART_RX_ENABLED || Esp_UART_HD_ENABLED))
    extern uint8 Esp_UART_errorStatus;
    extern volatile uint8 Esp_UART_rxBuffer[Esp_UART_RX_BUFFER_SIZE];
    extern volatile uint8 Esp_UART_rxBufferRead;
    extern volatile uint8 Esp_UART_rxBufferWrite;
    extern volatile uint8 Esp_UART_rxBufferLoopDetect;
    extern volatile uint8 Esp_UART_rxBufferOverflow;
    #if (Esp_UART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 Esp_UART_rxAddressMode;
        extern volatile uint8 Esp_UART_rxAddressDetected;
    #endif /* (Esp_UART_RXHW_ADDRESS_ENABLED) */
#endif /* (Esp_UART_RX_INTERRUPT_ENABLED && (Esp_UART_RX_ENABLED || Esp_UART_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define Esp_UART__B_UART__AM_SW_BYTE_BYTE 1
#define Esp_UART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define Esp_UART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define Esp_UART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define Esp_UART__B_UART__AM_NONE 0

#define Esp_UART__B_UART__NONE_REVB 0
#define Esp_UART__B_UART__EVEN_REVB 1
#define Esp_UART__B_UART__ODD_REVB 2
#define Esp_UART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define Esp_UART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define Esp_UART_NUMBER_OF_STOP_BITS    (1u)

#if (Esp_UART_RXHW_ADDRESS_ENABLED)
    #define Esp_UART_RX_ADDRESS_MODE    (0u)
    #define Esp_UART_RX_HW_ADDRESS1     (0u)
    #define Esp_UART_RX_HW_ADDRESS2     (0u)
#endif /* (Esp_UART_RXHW_ADDRESS_ENABLED) */

#define Esp_UART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << Esp_UART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << Esp_UART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << Esp_UART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << Esp_UART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << Esp_UART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << Esp_UART_RX_STS_BREAK_SHIFT) \
                                        | (0 << Esp_UART_RX_STS_OVERRUN_SHIFT))

#define Esp_UART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << Esp_UART_TX_STS_COMPLETE_SHIFT) \
                                        | (1 << Esp_UART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << Esp_UART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << Esp_UART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef Esp_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Esp_UART_CONTROL_REG \
                            (* (reg8 *) Esp_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define Esp_UART_CONTROL_PTR \
                            (  (reg8 *) Esp_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End Esp_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Esp_UART_TX_ENABLED)
    #define Esp_UART_TXDATA_REG          (* (reg8 *) Esp_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define Esp_UART_TXDATA_PTR          (  (reg8 *) Esp_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define Esp_UART_TXDATA_AUX_CTL_REG  (* (reg8 *) Esp_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Esp_UART_TXDATA_AUX_CTL_PTR  (  (reg8 *) Esp_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define Esp_UART_TXSTATUS_REG        (* (reg8 *) Esp_UART_BUART_sTX_TxSts__STATUS_REG)
    #define Esp_UART_TXSTATUS_PTR        (  (reg8 *) Esp_UART_BUART_sTX_TxSts__STATUS_REG)
    #define Esp_UART_TXSTATUS_MASK_REG   (* (reg8 *) Esp_UART_BUART_sTX_TxSts__MASK_REG)
    #define Esp_UART_TXSTATUS_MASK_PTR   (  (reg8 *) Esp_UART_BUART_sTX_TxSts__MASK_REG)
    #define Esp_UART_TXSTATUS_ACTL_REG   (* (reg8 *) Esp_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define Esp_UART_TXSTATUS_ACTL_PTR   (  (reg8 *) Esp_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(Esp_UART_TXCLKGEN_DP)
        #define Esp_UART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Esp_UART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define Esp_UART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define Esp_UART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define Esp_UART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Esp_UART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define Esp_UART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Esp_UART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define Esp_UART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define Esp_UART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) Esp_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* Esp_UART_TXCLKGEN_DP */

#endif /* End Esp_UART_TX_ENABLED */

#if(Esp_UART_HD_ENABLED)

    #define Esp_UART_TXDATA_REG             (* (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define Esp_UART_TXDATA_PTR             (  (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define Esp_UART_TXDATA_AUX_CTL_REG     (* (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define Esp_UART_TXDATA_AUX_CTL_PTR     (  (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Esp_UART_TXSTATUS_REG           (* (reg8 *) Esp_UART_BUART_sRX_RxSts__STATUS_REG )
    #define Esp_UART_TXSTATUS_PTR           (  (reg8 *) Esp_UART_BUART_sRX_RxSts__STATUS_REG )
    #define Esp_UART_TXSTATUS_MASK_REG      (* (reg8 *) Esp_UART_BUART_sRX_RxSts__MASK_REG )
    #define Esp_UART_TXSTATUS_MASK_PTR      (  (reg8 *) Esp_UART_BUART_sRX_RxSts__MASK_REG )
    #define Esp_UART_TXSTATUS_ACTL_REG      (* (reg8 *) Esp_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Esp_UART_TXSTATUS_ACTL_PTR      (  (reg8 *) Esp_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End Esp_UART_HD_ENABLED */

#if( (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) )
    #define Esp_UART_RXDATA_REG             (* (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define Esp_UART_RXDATA_PTR             (  (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define Esp_UART_RXADDRESS1_REG         (* (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define Esp_UART_RXADDRESS1_PTR         (  (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define Esp_UART_RXADDRESS2_REG         (* (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define Esp_UART_RXADDRESS2_PTR         (  (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define Esp_UART_RXDATA_AUX_CTL_REG     (* (reg8 *) Esp_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define Esp_UART_RXBITCTR_PERIOD_REG    (* (reg8 *) Esp_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Esp_UART_RXBITCTR_PERIOD_PTR    (  (reg8 *) Esp_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define Esp_UART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) Esp_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Esp_UART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) Esp_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define Esp_UART_RXBITCTR_COUNTER_REG   (* (reg8 *) Esp_UART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define Esp_UART_RXBITCTR_COUNTER_PTR   (  (reg8 *) Esp_UART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define Esp_UART_RXSTATUS_REG           (* (reg8 *) Esp_UART_BUART_sRX_RxSts__STATUS_REG )
    #define Esp_UART_RXSTATUS_PTR           (  (reg8 *) Esp_UART_BUART_sRX_RxSts__STATUS_REG )
    #define Esp_UART_RXSTATUS_MASK_REG      (* (reg8 *) Esp_UART_BUART_sRX_RxSts__MASK_REG )
    #define Esp_UART_RXSTATUS_MASK_PTR      (  (reg8 *) Esp_UART_BUART_sRX_RxSts__MASK_REG )
    #define Esp_UART_RXSTATUS_ACTL_REG      (* (reg8 *) Esp_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define Esp_UART_RXSTATUS_ACTL_PTR      (  (reg8 *) Esp_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) */

#if(Esp_UART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define Esp_UART_INTCLOCK_CLKEN_REG     (* (reg8 *) Esp_UART_IntClock__PM_ACT_CFG)
    #define Esp_UART_INTCLOCK_CLKEN_PTR     (  (reg8 *) Esp_UART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define Esp_UART_INTCLOCK_CLKEN_MASK    Esp_UART_IntClock__PM_ACT_MSK
#endif /* End Esp_UART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(Esp_UART_TX_ENABLED)
    #define Esp_UART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End Esp_UART_TX_ENABLED */

#if(Esp_UART_HD_ENABLED)
    #define Esp_UART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End Esp_UART_HD_ENABLED */

#if( (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) )
    #define Esp_UART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define Esp_UART_WAIT_1_MS      Esp_UART_BL_CHK_DELAY_MS   

#define Esp_UART_TXBUFFERSIZE   Esp_UART_TX_BUFFER_SIZE
#define Esp_UART_RXBUFFERSIZE   Esp_UART_RX_BUFFER_SIZE

#if (Esp_UART_RXHW_ADDRESS_ENABLED)
    #define Esp_UART_RXADDRESSMODE  Esp_UART_RX_ADDRESS_MODE
    #define Esp_UART_RXHWADDRESS1   Esp_UART_RX_HW_ADDRESS1
    #define Esp_UART_RXHWADDRESS2   Esp_UART_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define Esp_UART_RXAddressMode  Esp_UART_RXADDRESSMODE
#endif /* (Esp_UART_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define Esp_UART_initvar                    Esp_UART_initVar

#define Esp_UART_RX_Enabled                 Esp_UART_RX_ENABLED
#define Esp_UART_TX_Enabled                 Esp_UART_TX_ENABLED
#define Esp_UART_HD_Enabled                 Esp_UART_HD_ENABLED
#define Esp_UART_RX_IntInterruptEnabled     Esp_UART_RX_INTERRUPT_ENABLED
#define Esp_UART_TX_IntInterruptEnabled     Esp_UART_TX_INTERRUPT_ENABLED
#define Esp_UART_InternalClockUsed          Esp_UART_INTERNAL_CLOCK_USED
#define Esp_UART_RXHW_Address_Enabled       Esp_UART_RXHW_ADDRESS_ENABLED
#define Esp_UART_OverSampleCount            Esp_UART_OVER_SAMPLE_COUNT
#define Esp_UART_ParityType                 Esp_UART_PARITY_TYPE

#if( Esp_UART_TX_ENABLED && (Esp_UART_TXBUFFERSIZE > Esp_UART_FIFO_LENGTH))
    #define Esp_UART_TXBUFFER               Esp_UART_txBuffer
    #define Esp_UART_TXBUFFERREAD           Esp_UART_txBufferRead
    #define Esp_UART_TXBUFFERWRITE          Esp_UART_txBufferWrite
#endif /* End Esp_UART_TX_ENABLED */
#if( ( Esp_UART_RX_ENABLED || Esp_UART_HD_ENABLED ) && \
     (Esp_UART_RXBUFFERSIZE > Esp_UART_FIFO_LENGTH) )
    #define Esp_UART_RXBUFFER               Esp_UART_rxBuffer
    #define Esp_UART_RXBUFFERREAD           Esp_UART_rxBufferRead
    #define Esp_UART_RXBUFFERWRITE          Esp_UART_rxBufferWrite
    #define Esp_UART_RXBUFFERLOOPDETECT     Esp_UART_rxBufferLoopDetect
    #define Esp_UART_RXBUFFER_OVERFLOW      Esp_UART_rxBufferOverflow
#endif /* End Esp_UART_RX_ENABLED */

#ifdef Esp_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define Esp_UART_CONTROL                Esp_UART_CONTROL_REG
#endif /* End Esp_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(Esp_UART_TX_ENABLED)
    #define Esp_UART_TXDATA                 Esp_UART_TXDATA_REG
    #define Esp_UART_TXSTATUS               Esp_UART_TXSTATUS_REG
    #define Esp_UART_TXSTATUS_MASK          Esp_UART_TXSTATUS_MASK_REG
    #define Esp_UART_TXSTATUS_ACTL          Esp_UART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(Esp_UART_TXCLKGEN_DP)
        #define Esp_UART_TXBITCLKGEN_CTR        Esp_UART_TXBITCLKGEN_CTR_REG
        #define Esp_UART_TXBITCLKTX_COMPLETE    Esp_UART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define Esp_UART_TXBITCTR_PERIOD        Esp_UART_TXBITCTR_PERIOD_REG
        #define Esp_UART_TXBITCTR_CONTROL       Esp_UART_TXBITCTR_CONTROL_REG
        #define Esp_UART_TXBITCTR_COUNTER       Esp_UART_TXBITCTR_COUNTER_REG
    #endif /* Esp_UART_TXCLKGEN_DP */
#endif /* End Esp_UART_TX_ENABLED */

#if(Esp_UART_HD_ENABLED)
    #define Esp_UART_TXDATA                 Esp_UART_TXDATA_REG
    #define Esp_UART_TXSTATUS               Esp_UART_TXSTATUS_REG
    #define Esp_UART_TXSTATUS_MASK          Esp_UART_TXSTATUS_MASK_REG
    #define Esp_UART_TXSTATUS_ACTL          Esp_UART_TXSTATUS_ACTL_REG
#endif /* End Esp_UART_HD_ENABLED */

#if( (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) )
    #define Esp_UART_RXDATA                 Esp_UART_RXDATA_REG
    #define Esp_UART_RXADDRESS1             Esp_UART_RXADDRESS1_REG
    #define Esp_UART_RXADDRESS2             Esp_UART_RXADDRESS2_REG
    #define Esp_UART_RXBITCTR_PERIOD        Esp_UART_RXBITCTR_PERIOD_REG
    #define Esp_UART_RXBITCTR_CONTROL       Esp_UART_RXBITCTR_CONTROL_REG
    #define Esp_UART_RXBITCTR_COUNTER       Esp_UART_RXBITCTR_COUNTER_REG
    #define Esp_UART_RXSTATUS               Esp_UART_RXSTATUS_REG
    #define Esp_UART_RXSTATUS_MASK          Esp_UART_RXSTATUS_MASK_REG
    #define Esp_UART_RXSTATUS_ACTL          Esp_UART_RXSTATUS_ACTL_REG
#endif /* End  (Esp_UART_RX_ENABLED) || (Esp_UART_HD_ENABLED) */

#if(Esp_UART_INTERNAL_CLOCK_USED)
    #define Esp_UART_INTCLOCK_CLKEN         Esp_UART_INTCLOCK_CLKEN_REG
#endif /* End Esp_UART_INTERNAL_CLOCK_USED */

#define Esp_UART_WAIT_FOR_COMLETE_REINIT    Esp_UART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_Esp_UART_H */


/* [] END OF FILE */
