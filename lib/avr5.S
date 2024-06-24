/* 
 * Code excerpt from libgcc 
 * vim: syntax=nasm
 */

#define A0 26
#define B0 18
#define C0 22

#define A1 A0+1

#define B1 B0+1
#define B2 B0+2
#define B3 B0+3

#define C1 C0+1
#define C2 C0+2
#define C3 C0+3

#define __zero_reg__ r1
#define __tmp_reg__ r0


.macro DEFUN name
.global \name
.func \name
\name:
.endm


.macro ENDF name
.size \name, .-\name
.endfunc
.endm

.macro	mov_l  r_dest, r_src
movw	\r_dest, \r_src
.endm

.macro	mov_h  r_dest, r_src
; empty
.endm

.macro	wmov  r_dest, r_src
    movw \r_dest,   \r_src
.endm


;;; R25:R22 = (unsigned long) R27:R26 * (unsigned long) R19:R18
;;; C3:C0   = (unsigned long) A1:A0   * (unsigned long) B1:B0
;;; Clobbers: __tmp_reg__
DEFUN __umulhisi3
    mul     A0, B0
    movw    C0, r0
    mul     A1, B1
    movw    C2, r0
    mul     A0, B1
;;#ifdef __AVR_HAVE_JMP_CALL__
    ;; This function is used by many other routines, often multiple times.
    ;; Therefore, if the flash size is not too limited, avoid the RCALL
    ;; and inverst 6 Bytes to speed things up.
    add     C1, r0
    adc     C2, r1
    clr     __zero_reg__
    adc     C3, __zero_reg__
;;#else
;;    rcall   1f
;;#endif
    mul     A1, B0
1:  add     C1, r0
    adc     C2, r1
    clr     __zero_reg__
    adc     C3, __zero_reg__
    ret
ENDF __umulhisi3


;;; R25:R22 = (unsigned long) R27:R26 * R21:R18
;;; (C3:C0) = (unsigned long) A1:A0   * B3:B0
;;; Clobbers: __tmp_reg__
DEFUN __muluhisi3
    call    __umulhisi3
    mul     A0, B3
    add     C3, r0
    mul     A1, B2
    add     C3, r0
    mul     A0, B2
    add     C2, r0
    adc     C3, r1
    clr     __zero_reg__
    ret
ENDF __muluhisi3

/*******************************************************
    Multiplication  32 x 32  with MUL
*******************************************************/

;;; R25:R22 = R25:R22 * R21:R18
;;; (C3:C0) = C3:C0   * B3:B0
;;; Clobbers: R26, R27, __tmp_reg__
DEFUN __mulsi3
    movw    A0, C0
    push    C2
    push    C3
    call    __muluhisi3
    pop     A1
    pop     A0
    ;; A1:A0 now contains the high word of A
    mul     A0, B0
    add     C2, r0
    adc     C3, r1
    mul     A0, B1
    add     C3, r0
    mul     A1, B0
    add     C3, r0
    clr     __zero_reg__
    ret
ENDF __mulsi3

.macro NEG4  reg
    com     \reg+3
    com     \reg+2
    com     \reg+1
.if \reg >= 16
    neg     \reg
    sbci    \reg+1, -1
    sbci    \reg+2, -1
    sbci    \reg+3, -1
.else
    com     \reg
    adc     \reg,   __zero_reg__
    adc     \reg+1, __zero_reg__
    adc     \reg+2, __zero_reg__
    adc     \reg+3, __zero_reg__
.endif
.endm

/*******************************************************
       Division 32 / 32 => (result + remainder)
*******************************************************/
#define	r_remHH	r31	/* remainder High */
#define	r_remHL	r30
#define	r_remH	r27
#define	r_remL	r26	/* remainder Low */

/* return: remainder */
#define	r_arg1HH r25	/* dividend High */
#define	r_arg1HL r24
#define	r_arg1H  r23
#define	r_arg1L  r22	/* dividend Low */

/* return: quotient */
#define	r_arg2HH r21	/* divisor High */
#define	r_arg2HL r20
#define	r_arg2H  r19
#define	r_arg2L  r18	/* divisor Low */
	
#define	r_cnt __zero_reg__  /* loop count (0 after the loop!) */

DEFUN __udivmodsi4
	ldi	r_remL, 33	; init loop counter
	mov	r_cnt, r_remL
	sub	r_remL,r_remL
	sub	r_remH,r_remH	; clear remainder and carry
	mov_l	r_remHL, r_remL
	mov_h	r_remHH, r_remH
	rjmp	__udivmodsi4_ep	; jump to entry point
__udivmodsi4_loop:
        rol	r_remL		; shift dividend into remainder
	rol	r_remH
	rol	r_remHL
	rol	r_remHH
        cp	r_remL,r_arg2L	; compare remainder & divisor
	cpc	r_remH,r_arg2H
	cpc	r_remHL,r_arg2HL
	cpc	r_remHH,r_arg2HH
	brcs	__udivmodsi4_ep	; remainder <= divisor
        sub	r_remL,r_arg2L	; restore remainder
        sbc	r_remH,r_arg2H
        sbc	r_remHL,r_arg2HL
        sbc	r_remHH,r_arg2HH
__udivmodsi4_ep:
        rol	r_arg1L		; shift dividend (with CARRY)
        rol	r_arg1H
        rol	r_arg1HL
        rol	r_arg1HH
        dec	r_cnt		; decrement loop counter
        brne	__udivmodsi4_loop
				; __zero_reg__ now restored (r_cnt == 0)
	com	r_arg1L
	com	r_arg1H
	com	r_arg1HL
	com	r_arg1HH
; div/mod results to return registers, as for the ldiv() function
	mov_l	r_arg2L,  r_arg1L	; quotient
	mov_h	r_arg2H,  r_arg1H
	mov_l	r_arg2HL, r_arg1HL
	mov_h	r_arg2HH, r_arg1HH
	mov_l	r_arg1L,  r_remL	; remainder
	mov_h	r_arg1H,  r_remH
	mov_l	r_arg1HL, r_remHL
	mov_h	r_arg1HH, r_remHH
	ret
ENDF __udivmodsi4


DEFUN __negsi2
    NEG4    22
    ret
ENDF __negsi2


DEFUN __divmodsi4
    mov     __tmp_reg__,r_arg2HH
    bst     r_arg1HH,7          ; store sign of dividend
    brtc    0f
    com     __tmp_reg__         ; r0.7 is sign of result
    call    __negsi2            ; dividend negative: negate
0:
    sbrc    r_arg2HH,7
    rcall   __divmodsi4_neg2    ; divisor negative: negate
    call    __udivmodsi4        ; do the unsigned div/mod
    sbrc    __tmp_reg__, 7      ; correct quotient sign
    rcall   __divmodsi4_neg2
    brtc    __divmodsi4_exit    ; correct remainder sign
    jmp     __negsi2
__divmodsi4_neg2:
    ;; correct divisor/quotient sign
    com     r_arg2HH
    com     r_arg2HL
    com     r_arg2H
    neg     r_arg2L
    sbci    r_arg2H,0xff
    sbci    r_arg2HL,0xff
    sbci    r_arg2HH,0xff
__divmodsi4_exit:
    ret
ENDF __divmodsi4

#undef r_remHH
#undef r_remHL
#undef r_remH
#undef r_remL
#undef r_arg1HH
#undef r_arg1HL
#undef r_arg1H
#undef r_arg1L
#undef r_arg2HH
#undef r_arg2HL
#undef r_arg2H
#undef r_arg2L
#undef r_cnt

/*******************************************************
       Division 16 / 16 => (result + remainder)
*******************************************************/
#define	r_remL	r26	/* remainder Low */
#define	r_remH	r27	/* remainder High */

/* return: remainder */
#define	r_arg1L	r24	/* dividend Low */
#define	r_arg1H	r25	/* dividend High */

/* return: quotient */
#define	r_arg2L	r22	/* divisor Low */
#define	r_arg2H	r23	/* divisor High */
	
#define	r_cnt	r21	/* loop count */

DEFUN __udivmodhi4
	sub	r_remL,r_remL
	sub	r_remH,r_remH	; clear remainder and carry
	ldi	r_cnt,17	; init loop counter
	rjmp	__udivmodhi4_ep	; jump to entry point
__udivmodhi4_loop:
        rol	r_remL		; shift dividend into remainder
	rol	r_remH
        cp	r_remL,r_arg2L	; compare remainder & divisor
	cpc	r_remH,r_arg2H
        brcs	__udivmodhi4_ep	; remainder < divisor
        sub	r_remL,r_arg2L	; restore remainder
        sbc	r_remH,r_arg2H
__udivmodhi4_ep:
        rol	r_arg1L		; shift dividend (with CARRY)
        rol	r_arg1H
        dec	r_cnt		; decrement loop counter
        brne	__udivmodhi4_loop
	com	r_arg1L
	com	r_arg1H
; div/mod results to return registers, as for the div() function
	mov_l	r_arg2L, r_arg1L	; quotient
	mov_h	r_arg2H, r_arg1H
	mov_l	r_arg1L, r_remL		; remainder
	mov_h	r_arg1H, r_remH
	ret
ENDF __udivmodhi4

DEFUN __divmodhi4
    .global _div
_div:
    bst     r_arg1H,7           ; store sign of dividend
    mov     __tmp_reg__,r_arg2H
    brtc    0f
    com     __tmp_reg__         ; r0.7 is sign of result
    rcall   __divmodhi4_neg1    ; dividend negative: negate
0:
    sbrc    r_arg2H,7
    rcall   __divmodhi4_neg2    ; divisor negative: negate
    call    __udivmodhi4        ; do the unsigned div/mod
    sbrc    __tmp_reg__,7
    rcall   __divmodhi4_neg2    ; correct remainder sign
    brtc    __divmodhi4_exit
__divmodhi4_neg1:
    ;; correct dividend/remainder sign
    com     r_arg1H
    neg     r_arg1L
    sbci    r_arg1H,0xff
    ret
__divmodhi4_neg2:
    ;; correct divisor/result sign
    com     r_arg2H
    neg     r_arg2L
    sbci    r_arg2H,0xff
__divmodhi4_exit:
    ret
ENDF __divmodhi4


/* memset function for avr, based on avr libc */
#define dest_hi r25
#define dest_lo r24
#define val_lo r22
#define len_hi r21
#define len_lo r20

DEFUN memset
    movw  XL, dest_lo
    sbrs    len_lo, 0
    rjmp    .L_memset_start
    rjmp    .L_memset_odd
.L_memset_loop:
    st  X+, val_lo
.L_memset_odd:
    st  X+, val_lo
.L_memset_start:
    subi    len_lo, lo8(2)
    sbci    len_hi, hi8(2)
    brcc    .L_memset_loop
    ret
ENDF memset

