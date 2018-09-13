
	.ifndef ffunction
	.section .libc,code
	.else
	.section .libc.memcpypd3, code
	.endif
	.global __memcpypd3
__memcpypd3:
;; 
;; Copy data from program memory to data memory
;; 
;; Registers used:  w0 w1 w2 w3 w4 w5
;; 
;; Inputs:
;;  w0,w1 = source address   (24 bits)
;;  w2 = destination address (16 bits)
;;  w3 = number of bytes (even or odd)
;;  w4 = upper byte flag   (0 = false)
;; 
;; Outputs:
;;  w0,w1 = next source address (24 bits)
;; 

1:      mov      w1,_TBLPAG     ; TBLPAG = tblpage(src)
        mov      w0,w5          ; w5 =   tbloffset(src)
        add      w0,#2,w0       ; src+=2
        addc     w1,#0,w1       ;

        tblrdl.b [w5++],[w2++]  ; dst++ = lo byte
        dec      w3,w3          ; num--
        bra      z,2f           ; br if done

        tblrdl.b [w5--],[w2++]  ; dst++ = hi byte
        dec      w3,w3          ; num--
        bra      z,2f           ; br if done

        cp0      w4             ; test upper flag
        bra      z,1b           ; br if false

        tblrdh.b [w5],[w2++]    ; dst++ = upper byte
        dec      w3,w3          ; num--
        bra      nz,1b          ; br if not done

2:      return                  ; exit


.include "null_signature.s"

