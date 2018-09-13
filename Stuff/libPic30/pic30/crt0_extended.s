;; 
;; C Run-time startup module for dsPIC30 C compiler.
;; (c) Copyright 2009 Microchip Technology, All rights reserved
;;
;; Primary version, with data initialization support.
;; The linker loads this version when the --data-init
;; option is selected.
;; 
;; See file crt1.s for the alternate version without
;; data initialization support.
;; 
;; Entry __reset takes control at device reset and
;; performs the following:
;;
;;  1. initialize stack and stack limit register
;;  2. initialize PSV window if __const_length > 0
;;  3. process the data initialization template
;;  4. call the .user_init section, if it exists
;;  5. call the user's _main entry point
;;
;; Assigned to section .init, which may be allocated
;; at a specific address in linker scripts. 
;;
;; If a local copy of this file is customized, be sure
;; to choose a file name other than crt0.s or crt1.s.
;;
	.ifndef ffunction
        .section .init,code
	.else
	.section .init.resetPRI, code
	.endif

        .global __resetPRI
        .ifdef __C30ELF
        .type   __resetPRI,@function
        .endif
__resetPRI:     
        .weak  __reset
        .ifdef __C30ELF
        .type   __reset,@function
        .endif
__reset:
;;
;; Initialize stack, PSV, and data
;; 
;; registers used:  w0
;;
;; Inputs (defined by user or linker):
;;  __SP_init
;;  __SPLIM_init
;; 
;; Outputs:
;;  (does not return - resets the processor)
;; 
;; Calls:
;;  __psv_init
;;  __data_init
;;  _main
;; 

        .weak    __user_init, __has_user_init
        
        mov      #__SP_init,w15    ; initialize w15
	mov      #__SPLIM_init,w14

;; Uncomment to pre-initialize all RAM
;;
;; Start at the beginning of RAM, writing the value __DATA_INIT_VAL to memory
;;   write __STACK_INIT_VAL if the memory is part of stack space
;; cycle through to the end of RAM
;;
;; define initialization values as equate:
;; .global __DATA_INIT_VAL, __STACK_INIT_VAL
;; .equ __DATA_INIT_VAL, 0xDEAD
;; .equ __STACK_INIT_VAL, 0xA1DE
;;

;
;        mov      #__DATA_BASE,w0
;        mov      #__DATA_LENGTH,w1
;        mov      #__DATA_INIT_VAL,w3 ; start of initializing RAM
;        add      w0,w1,w1
;
;1:      cp       w0,w15
;        bra      geu, 2f             ; move to initializing STACK
;        mov      w3,[w0++]
;        cp       w0, w1
;        bra      ltu, 1b
;        bra      1f
;
;2:      mov      #__STACK_INIT_VAL,w3
;        setm     w15
;3:      mov      w3,[w0++]
;        cp       w0,w14
;        bra      nz,3b
;        mov      #__DATA_INIT_VAL,w3
;        cp       w0,w1
;        bra      ltu,1b
;1:      mov      #__SP_init,w15    ; (RE) initialize w15
;
;
;;  end RAM PRE-init

        mov      w14,_SPLIM        ; initialize SPLIM
        nop                        ; wait 1 cycle

        mov      #__enable_fixed, w0
        cp0      w0
        bra      z, CORCON_RESET
        mov      #0x0010,w0
        mov      w0,CORCON         ; enable super saturation and clear IF

CORCON_RESET:
        rcall    __psv_init        ; initialize PSV
        mov      #__dinit_tbloffset,w0 ; w0,w1 = template
        mov      #__dinit_tblpage,w1   ;
        rcall    __data_init_extended  ; initialize data

        mov      #__has_user_init,w0
        cp0      w0                ; user init functions?
        bra      eq,1f             ; br if not
        call     __user_init       ; else call them
1:
        call  _main                ; call user's main()

        .pword 0xDA4000            ; halt the simulator
        reset                      ; reset the processor

	.ifdef ffunction
	.section .init.psv_init, code
	.endif
        .global __psv_init
__psv_init:
;; 
;; Initialize PSV window if _constlen > 0
;; 
;; Registers used:  w0
;; 
;; Inputs (defined by linker):
;;  __const_length
;;  __const_psvpage
;; 
;; Outputs:
;;  (none)
;; 
        mov      #__const_length,w0  ; 
        cp0      w0                  ; test length of constants
        bra      z,1f                ; br if zero

        mov      #__const_psvpage,w0 ; 
        mov      w0,_DSRPAG          ; DSRPAG = psvpage(constants)

1:      return                       ;  and exit

.include "null_signature.s"

