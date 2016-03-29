;*******************************************************************************
; FILENAME: Bootloader_psoc3.a51
; Version 1.40
;
;  DESCRIPTION:
;    Means to jump to an instruction in the Application and clear the stack on
;    our way over.
;
;   C DECLARATIONS:
;       extern void JumpToAddr(uint32 addr)
;
;*******************************************************************************
; Copyright 2009-2014, Cypress Semiconductor Corporation.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions,
; disclaimers, and limitations in the end user license agreement accompanying
; the software package with which this file was provided.
;*******************************************************************************
$NOMOD51

;* PSoC Register definitions.
$INCLUDE (PSoC3_8051.inc)

EXTERN XDATA:BYTE (CyResetStatus)

;*******************************************************************************
;* Symbols
;*******************************************************************************
NAME CYBLMEM

PUBLIC _Bootloader_LaunchBootloadable

SP_RESET_VALUE EQU 1h

;*******************************************************************************
;* void Bootloader_LaunchBootloadable(uint32 *);
;* Jump to memory in CODE
;* Parameters:
;* R4: Bits [31:24] IGNORED
;* R5: Bits [23:16] IGNORED
;* R6: Bits [15:8] of start address
;* R7: Bits [7:0] of start address
;*******************************************************************************
?PR?CYMEMZERO?CYBLMEM SEGMENT CODE
RSEG ?PR?CYMEMZERO?CYBLMEM
_Bootloader_LaunchBootloadable:
    MOV     DPTR, #CyResetStatus
    MOVX    A, @DPTR
    MOV     R2, A

    MOV     DPH, R6
    MOV     DPL, R7
    MOV     A, #0h
    MOV     SP, #SP_RESET_VALUE
    JMP     @A+DPTR
_Bootloader_LaunchBootloadable_end:


END
