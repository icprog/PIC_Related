;;
;; __memcpy_eds: Copy eds memory to eds memory
;;
	.ifndef ffunction
        .section .libc,code
	.else
	.section .libc.memcpy_eds, code
	.endif
        .global __memcpy_eds       ; eds->eds
        
__memcpy_eds:
;; 
;; Registers used:  w0 w1 w2 w3 w4 w5 w6 w7
;; 
;; Inputs:
;;  w0,w1 = source address   (24 bits)
;;  w2,w3 = destination address (24 bits)
;;  w4 = number of bytes (even or odd)
;;  w5 = align
;; 
;;  This can be improved

        push PSVPAG

__memcpy_eds2dm:
	mov w1,PSVPAG
	cp w5,#1
	bra nz,1f
	; copy byte mode
2:	mov.b [w0],[w2++]
	dec w4,w4
	bra z,4f
3:	add w0,#1,w0
	bra nc,2b
	inc PSVPAG
	mov #0x8000,w0
	bra 2b 

1:	; copy in word mode
	mov [w0],[w2++]
	dec2 w4,w4
	bra z,4f
3:	add w0,#2,w0
	bra nc,1b
	inc PSVPAG
	mov #0x8000,w0
	bra 1b

4:	pop PSVPAG
        return

.include "null_signature.s"

