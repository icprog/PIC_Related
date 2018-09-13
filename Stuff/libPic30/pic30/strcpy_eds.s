;;
;; __strcpy_eds: Copy eds memory to eds memory
;;
	.ifndef ffunction
        .section .libc,code
	.else
	.section .libc.strcpy_eds, code
	.endif
	.global __strcpy_eds       ; eds->eds
	.global __strncpy_eds

;; 
;; Registers used:  w0 w1 w2 w3 w4 w5 w6 w7
;; 
;; Inputs:
;;  w0,w1 = source address   (24 bits)
;;  w2,w3 = destination address (24 bits)
;;  w4 = number of bytes (even or odd) (for strncpy)
;; 
;;  This can be improved

__strcpy_eds: 
	setm w4               ; strcpy copies the max

__strncpy_eds:
	clr  w5               ; make a zero for later add
        push DSWPAG
        push DSRPAG
        btss w2,#15
        inc w3,w3             ; set up for first overflow into 0x8000
	mov w3,DSWPAG

        btss w0,#15
        inc w1,w1             ; set up for first overflow into 0x8000
	mov w1,DSRPAG

	; copy byte mode
2:	add.b w5,[w0],[w2]    ; do the copy - but can now check for 0 too
	bra z,4f
	dec w4,w4
	bra z,4f
	add w2,#1,w2
	bra nc,3f
	inc DSWPAG
	mov #0x8000,w2
3:	add w0,#1,w0
	bra nc,2b
	inc DSRPAG
	mov #0x8000,w0
	bra 2b 

4:	pop DSRPAG
        pop DSWPAG
        return

.include "null_signature.s"

