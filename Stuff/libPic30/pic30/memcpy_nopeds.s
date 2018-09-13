;;
;; __memcpy_nopeds: Copy paged eds memory to paged eds memory for a device
;;                  with no hardware eds
;;
	.ifndef ffunction
        .section .libc,code
	.else
	.section .libc.memcpy_peds, code
	.endif
        .global __memcpy_peds       ; eds->eds
        
__memcpy_peds:
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

__memcpy_peds2dm:
	mov w1,PSVPAG
	cp w5,#1
	bra nz,1f
	; copy byte mode
2:	mov.b [w0++],[w2++]
	dec w4,w4
	bra nz,2b

        pop PSVPAG
        return

1:	; copy in word mode
	mov [w0++],[w2++]
	dec2 w4,w4
	bra nz,1b

        pop PSVPAG
	return

.include "null_signature.s"

