;;
;; __flash_helper: Erase and write to program memory
;;   on PIC24FxxK devices
;;
;; entry 7: erase rows
;; entry 8: write a row w/ 16-bit data
;; entry 9: write a row w/ 24-bit data
;;
	.ifdef ffunction
	.section .libc.flash_helper789,code
	.else
        .section .libc,code
	.endif
        .global __flash_helper7, __flash_helper8
        .global __flash_helper9

        .equ    WR,15              ; write control bit in NVMCON

        .equ    _FLASH_ERASE_ROW_CODE,0x4058
        .equ    _FLASH_ERASE_2ROW_CODE,0x4059
        .equ    _FLASH_ERASE_4ROW_CODE,0x405A
        .equ    _FLASH_WRITE_ROW_CODE,0x4004

        .equ    _FLASH_ROW,32
        .equ    _FLASH_2ROWS,64
        .equ    _FLASH_4ROWS,128


__flash_helper7:
;;
;; Erase rows of flash memory.
;; 
;; Registers used:  w0 w1 w2
;;                  (preserves TBLPAG)
;; Inputs:
;;  w0,w1 = destination address   (24 bits)
;;  w2 = len (_FLASH_ROW, _FLASH_2ROWS, or _FLASH_4ROWS)
;; 
;; Outputs: None
;; 
        push    TBLPAG
        mov     w1,_TBLPAG        ; TBLPAG = tblpage(dest)
        tblwtl  w0,[w0]           ; set base address of erase block

        mov     #_FLASH_ROW,w0
        mov     #_FLASH_ERASE_ROW_CODE,w1
        cp      w2,w0             ; erase 1 row mode?
        bra     eq,1f             ; br if so

        mov     #_FLASH_2ROWS,w0
        mov     #_FLASH_ERASE_2ROW_CODE,w1
        cp      w2,w0             ; erase 2 rows mode?
        bra     eq,1f             ; br if so

        mov     #_FLASH_4ROWS,w0
        mov     #_FLASH_ERASE_4ROW_CODE,w1
        cp      w2,w0             ; erase 4 rows mode?
        bra     nz,2f             ; br if no

1:      mov     w1,NVMCON         ; set erase code
        
finish: disi    #5                ; block level 0-6 interrupts
        mov     #0x55, w1         ; 
        mov     w1, NVMKEY        ; 
        mov     #0xAA, w1         ; 
        mov     w1, NVMKEY        ; unlock sequence
        bset    NVMCON, #WR       ; begin erase/write
        nop
        nop
2:      pop     TBLPAG
        return

__flash_helper8:
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

__flash_helper9:
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
        mov     w1,_TBLPAG      ; TBLPAG = tblpage(dest)
        mov     #_FLASH_WRITE_ROW_CODE,w1
        mov     w1,NVMCON       ; set row write mode
        mov     #0xFF,w1        ; default value for upper byte

4:      tblwtl  [w2++],[w0]     ; write lower 16 bits
        btsc    w4,#0           ; 24 bit mode? (skip if no)
        mov     [w2++],w1       ; yes; load more data
        
        tblwth  w1,[w0++]       ; write upper byte & phantom
        dec     w3,w3
        bra     nz,4b           ; loop until done
        
        bra     finish


.include "null_signature.s"

