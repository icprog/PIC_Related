;;
;; __memcpy_helper: Copy program memory to data memory
;;
	.ifndef ffunction
        .section .libc,code
	.else
	.section .libc.memcpy_helper, code
	.endif
        .global __memcpy_helper
        
__memcpy_helper:
;; 
;; Registers used:  w0 w1 w2 w3 w4 w5
;;                  (preserves TBLPAG)
;; 
;; Inputs:
;;  w0,w1 = source address   (24 bits)
;;  w2 = destination address (16 bits)
;;  w3 = number of bytes (even or odd)
;;  w4 = flags
;;         bit 0: copy upper byte
;;         bit 1: terminate after NULL
;; 
;; Outputs:
;;  w0,w1 = next source address (24 bits)
;;
;; Notes:
;;  1. Source address is always even, and
;;     increments by 2 for a program word.
;;  2. Data is always aligned to the least
;;     significant byte of a program word.
;; 
;; 

        push     _TBLPAG
1:      mov      w1,_TBLPAG     ; TBLPAG = tblpage(src)
        mov      w0,w5          ; w5 =   tbloffset(src)
        add      w0,#2,w0       ; src+=2
        addc     w1,#0,w1       ;

        tblrdl.b [w5++],[w2]    ; dst = lo byte
        cp0.b    [w2++]         ; is dst++ NULL?
        btsc     w4, #1         ; do we care?
        bra      z, 2f          ;   exit early if we do
        dec      w3,w3          ; num--
        bra      z,2f           ; br if done

        tblrdl.b [w5--],[w2]    ; dst = hi byte
        cp0.b    [w2++]         ; is dst++ NULL?
        btsc     w4, #1         ; do we care?
        bra      z, 2f          ;   exit early if we do
        dec      w3,w3          ; num--
        bra      z,2f           ; br if done

        btst.z   w4,#0          ; test upper flag
        bra      z,1b           ; br if false

        tblrdh.b [w5],[w2]      ; dst = upper byte
        cp0.b    [w2++]         ; is dst++ NULL?
        btsc     w4, #1         ; do we care?
        bra      z, 2f          ;   exit early if we do
        dec      w3,w3          ; num--
        bra      nz,1b          ; br if not done

2:      pop      _TBLPAG
        return

.include "null_signature.s"

