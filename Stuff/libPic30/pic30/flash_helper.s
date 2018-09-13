;;
;; Copyright 2008-2011 Microchip Technology, Inc. All rights reserved
;; 
;; This file defines flash erase/write helper functions.
;; The external interface to these functions is defined
;; in libpic30.h
;;
;; Updated 9 May 2008 for Device ID errata
;; Updated 3 January 2011 for 33E and 24E devices
;;
;; Projects built with MPLAB C v3.11 (B) or earlier
;; should include this source file to incorporate
;; the Device ID errata work-around.
;;

;;
;; __flash_helper: Erase and write to program memory
;;
;; entry 1: erase a page
;; entry 2: write a row w/ 16-bit data
;; entry 3: write a row w/ 24-bit data
;; entry 4: write a 16-bit word
;; entry 5: write a 24-bit word
;; entry 6: erase the general or secure segment
;;
	.ifdef ffunction
	.section .libc.flash_helper123456,code
	.else
        .section .libc,code
	.endif
        .global __flash_helper1, __flash_helper2
        .global __flash_helper3, __flash_helper4
        .global __flash_helper5, __flash_helper6
        .global __flash_helper10, __flash_helper11

        .equ    WR,15                         ; write control bit in NVMCON
        .equ    _FLASH_WRITE_ROW_CODE,0x4001  ; for all device families
        .equ    _FLASH_WRITE_WORD_CODE,0x4003 ; for all that support it
        .equ    _SET_NVMADDR,0

.ifdef __PIC24E 
        .equ    _FLASH_WRITE_ROW_CODE,0x4002  ; for all dsPIC24E families
        .equ    _FLASH_WRITE_WORD_CODE,0x4001
        .equ    _SET_NVMADDR,1
.endif
.ifdef __PIC33E
        .equ    _FLASH_WRITE_ROW_CODE,0x4002  ; for all dsPIC33E families
        .equ    _FLASH_WRITE_WORD_CODE,0x4001 
    	.equ    _SET_NVMADDR,1
.endif

;;
;; If DEVICE_ID_ERRATA = 1
;;  enable write latch workaround
;; 
        .equ    DEVICE_ID_ERRATA,1


__flash_helper1:
;;
;; Erase a page of flash memory.
;; 
;; Registers used:  w0 w1 w2
;;                  (preserves TBLPAG)
;; Inputs:
;;  w0,w1 = destination address   (24 bits)
;;  w2 = erase code
;; 
;; Outputs: None
;; 
        push    TBLPAG
        mov     w2,_NVMCON      ; set erase code
.if _SET_NVMADDR == 0
        mov     w1,_TBLPAG      ; TBLPAG = tblpage(dest)
        tblwtl  w0,[w0]         ; set base address of erase block
.else
        mov     w0,_NVMADR      ; set base address into memory
        mov     w1,_NVMADRU     ; address registers
.endif
        
finish: disi    #5              ; block level 0-6 interrupts
        mov     #0x55, w1       ; 
        mov     w1, NVMKEY      ; 
        mov     #0xAA, w1       ; 
        mov     w1, NVMKEY      ; unlock sequence
        bset    NVMCON, #15     ; begin erase/write
        nop
        nop
        pop     TBLPAG
        return

__flash_helper2:
;;
;; Write a row of flash memory with 16-bit data
;; 
;; Registers used:  w0 w1 w2 w3 w4
;;                  (preserves TBLPAG)
;; Inputs:
;;  w0,w1 = destination address   (24 bits)
;;  w2 = source address (16 bits)
;;  w3 = number of words
;; 
;; Outputs: None
;; 
        bclr    w4,#0           ; flag = 16-bit mode
        bra     1f              ; br to continue

__flash_helper3:
;;
;; Write a row of flash memory with 24-bit data
;; 
;; Registers used:  w0 w1 w2 w3 w4
;;                  (preserves TBLPAG)
;; Inputs:
;;  w0,w1 = destination address   (24 bits)
;;  w2 = source address (16 bits)
;;  w3 = number of words
;; 
;; Outputs: None
;; 
        bset    w4,#0           ; flag = 24-bit mode
1:      push    TBLPAG

.if _SET_NVMADDR == 0
        mov     w1,_TBLPAG      ; TBLPAG = tblpage(dest)
.else
        mov     w0,_NVMADR      ; set base address into memory
        mov     w1,_NVMADRU     ; address registers

        mov 	#0xFA, w0
        mov 	w0, TBLPAG
        clr  	w0
.endif
        
        mov     #_FLASH_WRITE_ROW_CODE,w1
        mov     w1,NVMCON       ; set row write mode
        mov     #0xFF,w1        ; default value for upper byte

4:      tblwtl  [w2++],[w0]     ; write lower 16 bits
        btsc    w4,#0           ; 24 bit mode? (skip if no)
        mov     [w2++],w1       ; yes; load more data
        
        tblwth  w1,[w0++]       ; write upper byte & phantom
.if _SET_NVMADDR == 1
        inc2    _NVMADRU
.endif
        dec     w3,w3
        bra     nz,4b           ; loop until done
        
       ; At this point, we have finished loading a row of latches
       ;  and the FLASH address ends in xx80
       ;
       ; The RAM address ends in xx80 if we're in 16-bit mode,
       ;  or x100 if we're in 24-bit mode
       .if     DEVICE_ID_ERRATA
       sub     w2,#8,w2       ; rewind src addr (RAM)
       btsc    w4,#0          ; 24 bit mode? (skip if no)
       sub     w2,#8,w2       ; rewind some more

       sub     w0,#8,w0       ; rewind dst addr (FLASH)
       tblwtl  [w2],[w0]      ; load latch again
       .endif

        bra     finish

__flash_helper4:
;; 
;; Write a 16-bit word to flash.
;;
;; Registers used:  w0 w1 w2 w3
;;                  (preserves TBLPAG)
;; Inputs:
;;  w0,w1 = destination address   (24 bits)
;;  w2    = word data
;; 
;; Outputs: None 
;; 
        mov     #0xFF,w3       ; fall through to next function

__flash_helper5:
;; 
;; Write a 24-bit word to flash.
;;
;; Registers used:  w0 w1 w2 w3
;;                  (preserves TBLPAG)
;; Inputs:
;;  w0,w1 = destination address   (24 bits)
;;  w2,w3 = long data
;; 
;; Outputs: None 
;; 
        push    TBLPAG

.if  _SET_NVMADDR == 1
        mov     w0,_NVMADR      ; set base address into memory
        mov     w1,_NVMADRU     ; address registers
.endif

        mov     w1,_TBLPAG      ; TBLPAG = tblpage(dest)
        mov     #_FLASH_WRITE_WORD_CODE,w1
        mov     w1,NVMCON       ; set word write mode

        tblwtl  w2,[w0]         ; write 16 bits
        tblwth  w3,[w0]         ; write 8 more bits
        bra     finish

__flash_helper6:
;; 
;; Erase the general or secure segment, with 
;; corresponding config word
;;
;; Registers used:  w0,w1
;;                  (preserves TBLPAG)
;; Inputs:
;;  w0 = erase code
;; 
;; Outputs: None
;;
        push    TBLPAG
        mov     w0,NVMCON       ; set erase mode
        bra     finish


.if _SET_NVMADDR == 1
__flash_helper10:
;; 
;; Write a 32-bit word to flash.
;;
;; Registers used:  w0 w1 w2 w3 w4 w5
;;                  (preserves TBLPAG)
;; Inputs:
;;  w0,w1 = destination address   (24 bits)
;;  w2 = int data
;;  w3 = empty
;;  w4 = int data
;;  w5 = empty
;; 
;; Outputs: None 
;; 

         mov     #0xFF,w3       ; fall through to next function
         mov     #0xFF,w5      

__flash_helper11:
;; 
;; Write a 48-bit word to flash.
;;
;; Registers used:  w0 w1 w2 w3 w4 w5
;;                  (preserves TBLPAG)
;; Inputs:
;;  w0,w1 = destination address   (24 bits)
;;  w2,w3 = long data
;;  w4,w5 = long data
;; 
;; Outputs: None 
;; 
        push    TBLPAG

        mov     w0,_NVMADR      ; set base address into memory
        mov     w1,_NVMADRU     ; address registers

        mov 	#0xFA, w0
        mov 	w0, TBLPAG
        clr  	w0
       
        tblwtl  w2,[w0]         ; write 16 bits
        tblwth  w3,[w0++]       ; write 8 bits
        tblwtl  w4,[w0]         ; next word write 16 bits
        tblwth  w5,[w0++]       ; next word write 8 bits

        mov     #_FLASH_WRITE_WORD_CODE,w1
        mov     w1,NVMCON       

        bra     finish
.endif

.include "null_signature.s"

