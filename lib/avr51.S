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
#.func \name
\name:
.endm


.macro ENDF name
.size \name, .-\name
#.endfunc
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


/*******************************************************
       Division 8 / 8 => (result + remainder)
*******************************************************/
#define	r_rem	r25	/* remainder */
#define	r_arg1	r24	/* dividend, quotient */
#define	r_arg2	r22	/* divisor */
#define	r_ucnt	r23	/* loop count */

DEFUN __udivmodqi4
	sub	r_rem,r_rem	; clear remainder and carry
	ldi	r_ucnt,9		; init loop counter
	rjmp	__udivmodqi4_ep	; jump to entry point
__udivmodqi4_loop:
	rol	r_rem		; shift dividend into remainder
	cp	r_rem,r_arg2	; compare remainder & divisor
	brcs	__udivmodqi4_ep	; remainder <= divisor
	sub	r_rem,r_arg2	; restore remainder
__udivmodqi4_ep:
	rol	r_arg1		; shift dividend (with CARRY)
	dec	r_ucnt		; decrement loop counter
	brne	__udivmodqi4_loop
	com	r_arg1		; complement result
				; because C flag was complemented in loop
	ret
ENDF __udivmodqi4


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

/* 
 * The assembly code below implements float32 functions and was slight
 * adapted from avrlibc/libm (https://github.com/avrdudes/avr-libc)
 * by thborges, 29-Sep-2024.
 */

/* Copyright (c) 2002  Michael Stumpf  <mistumpf@de.pepperl-fuchs.com>
   Copyright (c) 2006  Dmitry Xmelkov
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE. */

#define	rB0	r18
#define	rB1	r19
#define	rB2	r20
#define	rB3	r21
#define	rA0	r22
#define	rA1	r23
#define	rA2	r24
#define	rA3	r25
#define	rBE	r26
#define	rAE	r27


DEFUN __subsf3
    subi rB3, 0x80   ; complement sign bit of B
DEFUN __addsf3
    clr rAE
    clr rBE
    rcall __addsf3x
    rjmp __fp_round
ENDF __subsf3




DEFUN __fp_pscA
	clr	r0
	dec	r0
	cp	r1, rA0
	cpc	r1, rA1
	cpc	r1, rA2
	cpc	r0, rA3
	ret
ENDF __fp_pscA


DEFUN __fp_pscB
	clr	r0
	dec	r0
	cp	r1, rB0
	cpc	r1, rB1
	cpc	r1, rB2
	cpc	r0, rB3
	ret
ENDF __fp_pscB


DEFUN __fp_nan
	ldi	rA3, 0xFF
	ldi	rA2, 0xC0
	ret
ENDF __fp_nan


DEFUN __fp_inf
	bld	rA3, 7		; sign
	ori	rA3, 0x7f
	ldi	rA2, 0x80
	ldi	rA1, 0
	ldi	rA0, 0
	ret
ENDF __fp_inf


__addsf3xexit:
    rcall	__fp_pscA
	brcs	.L_nan
	rcall	__fp_pscB
	brcs	.L_nan
	brne	.L_inf		; B is finite --> return A
	cpi	rA3, 255
	brne	.L_infB		; A is finite --> return B
	brtc	.L_inf		; Inf + Inf with the same sign
.L_nan:
	rjmp	__fp_nan
.L_infB:
	brtc	.L_inf
	com	ZL
.L_inf:
	bst	ZL, 7
	rjmp	__fp_inf

DEFUN __addsf3x
	mov	ZL, rA3		; save sign of A
	rcall	__fp_split3
	brcs	__addsf3xexit
  ; compare A and B
	cp	rAE, rBE
	cpc	rA0, rB0
	cpc	rA1, rB1
	cpc	rA2, rB2
	cpc	rA3, rB3
	brlo	2f		; fabs(A) < fabs(B)
	brne	4f		; fabs(A) > fabs(B)
	brtc	.L_add
	rjmp	__fp_zero	; A + (-A) = +0.0
  ; swap A and B
2:	brtc	3f
	com	ZL		; update sign
3:	mov	r0, rAE
	mov	rAE, rBE
	mov	rBE, r0
	movw	r0, rA0
	movw	rA0, rB0
	movw	rB0, r0
	movw	r0, rA2
	movw	rA2, rB2
	movw	rB2, r0
	clr	r1
4:	clr	ZH
	sub	rB3, rA3
5:	breq	7f		; shift is not needed
	cpi	rB3, -7
	brsh	6f
	cpi	rB3, -32
	brlo	.L_ret
	cp	r1, rBE
	sbci	ZH, 0
	mov	rBE, rB0
	mov	rB0, rB1
	mov	rB1, rB2
	clr	rB2
	subi	rB3, -8
	rjmp	5b

6:	lsr	rB2
	ror	rB1
	ror	rB0
	ror	rBE
	sbci	ZH, 0
	inc	rB3
	brne	6b

7:
  ; direction ?
	brtc	.L_add
  ; A -= B
	cp	r1, ZH
	sbc	rAE, rBE
	sbc	rA0, rB0
	sbc	rA1, rB1
	sbc	rA2, rB2
	brmi	.L_ret
8:	subi	rA3, 1
	breq	9f
	lsl	ZH
	rol	rAE
	rol	rA0
	rol	rA1
	rol	rA2
	brpl	8b
	rjmp	.L_ret

.L_add:
	add	rAE, rBE
	adc	rA0, rB0
	adc	rA1, rB1
	adc	rA2, rB2
	brcc	.L_ret
	ror	rA2
	ror	rA1
	ror	rA0
	ror	rAE
	ror	ZH
	cpi	rA3, 254
	brlo	9f
	rjmp	.L_inf
9:	inc	rA3
.L_ret:
	lsl	rA2
	brcs	1f
	clr	rA3
1:	lsl	ZL		; sign
	ror	rA3
	ror	rA2
	ret
ENDF __addsf3x


DEFUN __fp_zero
	clt
DEFUN __fp_szero
	clr	rAE
	clr	rA0
	clr	rA1
	wmov	rA2, rA0
	bld	rA3, 7
	ret
ENDF __fp_szero


DEFUN __fp_split3
  ; rA3[7] := sign(A) ^ sign(B)
	sbrc	rB3, 7
	subi	rA3, 0x80
  ; split B
	lsl	rB2
	rol	rB3		; exponent
	breq	4f
	cpi	rB3, 0xff	; C = 1, if rB3 != 0xff
	breq	5f
1:	ror	rB2		; restore rB2 and (possible) hidden bit
; <non_standard> __fp_splitA (float A);
DEFUN __fp_splitA
	lsl	rA2
2:	bst	rA3, 7
	rol	rA3
	breq	6f
	cpi	rA3, 0xff
	breq	7f
3:	ror	rA2
	ret

  ; B is zero or subnormal
4:	cp	r1, rB0
	cpc	r1, rB1
	cpc	r1, rB2		; C = 1, if B is not a zero
	rol	rB3		; C = 0
	rjmp	1b
  ; B is not a finite
5:	lsr	rB2
	rcall	__fp_splitA
	rjmp	8f

  ; A is zero or subnormal
6:	cp	r1, rA0
	cpc	r1, rA1
	cpc	r1, rA2
	rol	rA3
	rjmp	3b
  ; A is not a finite
7:	lsr	rA2		; C = 0
	cpc	rA1, r1
	cpc	rA0, r1
8:	sec
	ret
ENDF __fp_split3


DEFUN __fixsfsi
	rcall __fixunssfsi
	set
	cpse	rAE, r1			; error flag
	rjmp	__fp_szero		; return 0x80000000
	ret
ENDF __fixsfsi


DEFUN __fixunssfsi
	rcall	__fp_splitA
	brcs	.L_err
  ; A is finite
	subi	rA3, 127	; exponent field of 1.0
	brlo	.L_zr
  ; fabs(A) >= 1.0
	mov	rAE, rA3
	clr	rA3
	subi	rAE, 23
	brlo	4f		; shift to right
	breq	.L_sign		; no shift
  ; fabs(A) >= 0x0.800000p+25  To reduce code size we will not check
  ; number of shifts. Instead we will check a MSB of result.
1:	lsl	rA0
	rol	rA1
	rol	rA2
	rol	rA3
	brmi	2f		; next shift is impossible: data lost
	dec	rAE
	brne	1b
	rjmp	.L_sign

2:	cpi	rAE, 1
	breq	.L_sign		; rAE: overflow for 'signed long' usage

.L_err:	rcall __fp_zero
	ldi	rAE, 1		; error flag
	ret

.L_zr:	rjmp __fp_zero	; return 0x00000000, clear rAE

  ; fabs(A) <= 0x0.ffffffp+23
  ; Shift A to right by 1 (rA3==-1) .. 23 (rA3==-23) positions.

3:	mov	rA0, rA1
	mov	rA1, rA2
	clr	rA2
	subi	rAE, -8
	breq	.L_sign

4:	cpi	rAE, -7
	brlt	3b		; quick shift is possible

5:	lsr	rA2
	ror	rA1
	ror	rA0
	inc	rAE
	brne	5b

  ; restore the sign and return
.L_sign:
	brtc	6f
	com	rA3
	com	rA2
	com	rA1
	neg	rA0
	sbci	rA1, -1
	sbci	rA2, -1
	sbci	rA3, -1
6:	ret

ENDF __fixunssfsi


DEFUN __fp_round
  ; is A finite ?
	mov	r0, rA3
	inc	r0
	lsl	r0
	brne	1f
	tst	rA2
	brmi	3f		; no, A is not a finite number
  ; rounding
1:	lsl	rAE
	brcc	3f
	or	rAE, ZH
	brne	2f
	sbrs	rA0, 0		; round to even
	rjmp	3f
2:	subi	rA0, -1
	sbci	rA1, -1
	sbci	rA2, -1
	sbci	rA3, -1

3:	ret
ENDF __fp_round

#define	ret_lo	r24
DEFUN   __cmpsf2
DEFUN   __eqsf2
DEFUN   __nesf2
DEFUN   __ltsf2
DEFUN   __lesf2
	rcall __fp_cmp
	brcc	1f
	ldi	ret_lo, 1
1:	ret
ENDF __cmpsf2

DEFUN __fp_cmp
	lsl	rA3
	sbc	r0, r0		; r0 = (A < 0) ? -1 : 0
	lsl	rB3
	sbc	rBE, rBE	; rBE = (B < 0) ? -1 : 0
  ; isnan(A) ?
	ldi	ZL, 0x80	; NaN: 0x{f/7}f800001..0x{f/7}fffffff
	ldi	ZH, 0xfe
	cp	r1, rA0
	cpc	r1, rA1
	cpc	ZL, rA2
	cpc	ZH, rA3
	brlo	9f		; branch, if C == 1
  ; isnan(B) ?
	cp	r1, rB0
	cpc	r1, rB1
	cpc	ZL, rB2
	cpc	ZH, rB3
	brlo	9f		; branch, if C == 1
  ; compare
	sub	rA0, rB0
	sbc	rA1, rB1
	sbc	rA2, rB2
	sbc	rA3, rB3	; C is set, if A < B
	brne	1f
  ; absolute values are equal, check signs
	eor	r0, rBE
	breq	9f		; if branch, rA2 = 0, C = 0
  ; force -0.0 == +0.0
	or	rB0, rB1
	or	rB0, rB2
	or	rB0, rB3
	brne	2f		; evaluate sign(B)
	ret
  ; view argument signes
1:	eor	r0, rBE		; C is not changed
	brne	2f		; signs are different
	sbci	rBE, 1		; rBE[0] = (A < B && A > 0) ? 0 : 1
2:	lsr	rBE		; C = above result OR sign(B)
  ; build return value, C is set, if A > B
	ldi	rA2, -1
	adc	rA2, r1
	adc	rA2, r1		; C = 0 at any case
9:	ret
ENDF __fp_cmp


DEFUN __unordsf2
	rcall __fp_cmp	; return C=1, if any of args is NaN
	sbc	r24, r24
	sbc	r25, r25
	ret
ENDF __unordsf2


DEFUN __mulsf3
	rcall __mulsf3x
	rjmp __fp_round
ENDF __mulsf3


__mulsf3x_exit:
0:	rcall __fp_pscA
	brcs	1f
	rcall __fp_pscB
	brcs	1f
	and	rA3, rB3		; one of args is 0xff
	breq	1f
	rjmp __fp_inf		; nonzero * Inf --> Inf
1:	rjmp __fp_nan		; 0 * Inf --> NaN
2:	clr	r1			; after 'mul rA3,rB3'
	rjmp __fp_szero

DEFUN __mulsf3x
	rcall __fp_split3
	brcs	0b

DEFUN __mulsf3_pse			; post split entry
  ; check zero
	mul	rA3, rB3		; r1 would be clean
	breq	2b
  ; rB3.rA3 := rA3 + rB3
	add	rA3, rB3
	ldi	rB3, 0
	adc	rB3, rB3

  ; multiplication:  rA2.rA1.rA0 * rB2.rB1.rB0  -->  rA2.rA1.rA0.rAE.ZH.ZL

  ; ZH.ZL = rA0 * rB0
	mul	rA0, rB0
	movw	ZL, r0
  ; rAE.ZH += rA1 * rB0
	mul	rA1, rB0
	clr	rAE
	add	ZH, r0
	adc	rAE, r1
  ; rBE.rAE.ZH = rAE.ZH + rA0 * rB1
	mul	rA0, rB1
	clr	rBE
	add	ZH, r0
	adc	rAE, r1
	adc	rBE, rBE
  ; rA0.rBE.rAE = rBE.rAE + rA0 * rB2
	mul	rA0, rB2
	clr	rA0
	add	rAE, r0
	adc	rBE, r1
	adc	rA0, rA0
  ; rA0.rBE.rAE += rA2 * rB0
	mul	rA2, rB0
	clr	rB0
	add	rAE, r0
	adc	rBE, r1
	adc	rA0, rB0
  ; rA0.rBE.rAE += rA1 * rB1
	mul	rA1, rB1
	add	rAE, r0
	adc	rBE, r1
	adc	rA0, rB0	; rB0 == 0
  ; rB0.rA0.rBE = rA0.rBE + rA2 * rB1
	mul	rA2, rB1
	add	rBE, r0
	adc	rA0, r1
	adc	rB0, rB0	; rB0 was 0
  ; rB0.rA0.rBE += rA1 * rB2
	mul	rA1, rB2
	clr	rB1
	add	rBE, r0
	adc	rA0, r1
	adc	rB0, rB1
  ; rB0.rA0 += rA2 * rB2
	mul	rA2, rB2
	add	rA0, r0
	adc	rB0, r1
  ; move result:  rA2.rA1.rA0.rAE.ZH.ZL = rB0.rA0.rBE.rAE.ZH.ZL
	mov	rA2, rB0
	mov	rA1, rA0
	mov	rA0, rBE
  ; __zero_reg__
	clr	r1

  ; exponent -= 127	(Why not 126?  For compare convenience.)
	subi	rA3, 0x7F ;lo8(127)
	sbci	rB3, 0x00 ;hi8(127)
	brmi	13f		; denormalization is needed
	breq	15f		; normalization is impossible
  ; result exponent > min ==> normalization is possible
10:	tst	rA2
	brmi	11f		; mantissa is normal
  ; mantissa <<= 1
	lsl	ZL
	rol	ZH
	rol	rAE
	rol	rA0
	rol	rA1
	rol	rA2
  ; exponent -= 1
	subi	rA3, 0x01 ;lo8(1)
	sbci	rB3, 0x00 ;hi8(1)
	brne	10b
  ; check to overflow
11:	cpi	rA3, 254
	cpc	rB3, r1
	brlo	15f
	rjmp __fp_inf
  ; check lowest value of exponent to avoid long operation
12:	rjmp __fp_szero
13:	cpi	rB3, 0xFF  ;hi8(-24)		; here rB3 < 0
	brlt	12b
	cpi	rA3, 0XE8  ;lo8(-24)
	brlt	12b
  ; mantissa >>= -rA3
14:	lsr	rA2
	ror	rA1
	ror	rA0
	ror	rAE
	ror	ZH
	ror	ZL
	subi	rA3, -1
	brne	14b
  ; for rounding
15:	or	ZH, ZL
  ; pack
	lsl	rA2
	adc	rA3, r1		; restore exponent for normal values
	lsr	rA3
	ror	rA2
	bld	rA3, 7		; sign
	ret
ENDF __mulsf3x


DEFUN __gesf2
DEFUN __gtsf2
	rcall __fp_cmp
	brcc	1f
	ldi	ret_lo, -1
1:	ret
ENDF __gesf2


DEFUN __divsf3
	rcall __divsf3x
	rjmp __fp_round
ENDF __divsf3


__divsf3x_exit:
0:	rcall __fp_pscB
	brcs	.L_nan_div
	rcall __fp_pscA
	brcs	.L_nan_div
	brne	.L_zr_div		; finite / Inf --> 0
.L_infA:
	cpi	rB3, 255
	breq	.L_nan_div		; Inf / Inf --> NaN
.L_inf_div:
	rjmp __fp_inf
1:
	cpse	rB3, r1		; 0/finite --> 0,  0/0 --> NaN
.L_zr_div:	rjmp __fp_szero
.L_nan_div:	rjmp __fp_nan

DEFUN __divsf3x
	rcall __fp_split3
	brcs	0b

DEFUN __divsf3_pse		; post split entry
	tst	rA3
	breq	1b
	tst	rB3
	breq	.L_inf_div		; finite / 0.0 --> Inf

	sub	rA3, rB3
	sbc	rB3, rB3

/* Prepare to division:
     A:  rAE.rA2.rA1.rA0	0x00000001..0x00FFFFFF
     B:  rBE.rB2.rB1.rB0	0x00000002..0x01FFFFFE
     A < B
 */
	clr	rAE
	clr	rBE
2:	cp	rA0, rB0
	cpc	rA1, rB1
	cpc	rA2, rB2
	brlo	3f
	subi	rA3, 0xFF ;lo8(-1)
	sbci	rB3, 0xFF ;hi8(-1)
	lsl	rB0
	rol	rB1
	rol	rB2
	rol	rBE
	breq	2b
3:
	rcall	.L_div
	mov	r0, ZL
	brmi	5f		; N is result of 'com ZL' from .L_div

4:	ldi	ZL, 0x80
	rcall	.L_div1
	subi	rA3, 0x01 ;lo8(1)
	sbci	rB3, 0x00 ;hi8(1)
	lsr	ZL
	rol	r0
	brpl	4b

5:	rcall	.L_div
	mov	ZH, ZL
	rcall	.L_div

	lsl	rA0
	rol	rA1
	rol	rA2
	rol	rAE
	cp	rB0, rA0
	cpc	rB1, rA1
	cpc	rB2, rA2
	cpc	rBE, rAE
	ldi	rAE, 0x80
	breq	4f
	sbc	rAE, rAE

4:	mov	rA2, r0
	wmov	rA0, ZL
	clr	ZH

  ; exponent += 125
	subi	rA3, 0x83 ;lo8(-125)
	sbci	rB3, 0xFF ;hi8(-125)
	brmi	13f		; denormalization is needed
  ; check to overflow
11:	cpi	rA3, 254
	cpc	rB3, r1
	brlo	15f
	rjmp __fp_inf
  ; check lowest value of exponent to avoid long operation
12:	rjmp __fp_szero
13:	cpi	rB3, 0xFF ;hi8(-24)		; here rB3 < 0
	brlt	12b
	cpi	rA3, 0xE8 ;lo8(-24)
	brlt	12b
  ; mantissa >>= -rA3
14:	lsr	rA2
	ror	rA1
	ror	rA0
	ror	rAE
	ror	ZH
	subi	rA3, -1
	brne	14b
  ; pack
15:	lsl	rA2
	adc	rA3, r1		; restore exponent for normal values
	lsr	rA3
	ror	rA2
	bld	rA3, 7
	ret

.L_div:
	ldi	ZL, 1
.L_div1:
	lsl	rA0
	rol	rA1
	rol	rA2
	rol	rAE
	cp	rA0, rB0
	cpc	rA1, rB1
	cpc	rA2, rB2
	cpc	rAE, rBE
	brcs	2f
	sub	rA0, rB0
	sbc	rA1, rB1
	sbc	rA2, rB2
	sbc	rAE, rBE
2:	rol	ZL
	brcc	.L_div1
	com	ZL
	ret
ENDF __divsf3x


DEFUN __floatdisf
	bst	rA3, 7		; sign
	brtc	1f
	rcall __fp_negdi
1:	rjmp __fp_di2sf
ENDF __floatdisf


DEFUN __fp_negdi
	com	rA3
	com	rA2
	com	rA1
	com	rA0
	com	rB3
	com	rB2
	com	rB1
	neg	rB0
	sbci	rB1, -1
	sbci	rB2, -1
	sbci	rB3, -1
	sbci	rA0, -1
	sbci	rA1, -1
	sbci	rA2, -1
	sbci	rA3, -1
	ret
ENDF __fp_negdi


DEFUN __floatundisf
	clt			; result sign

DEFUN __fp_di2sf
	mov	ZH, rA3
	ldi	rA3, 127 + 55	; exponent for 00.80.00.00.00.00.00.00
	tst	ZH
	breq	.L_tstA2

/* Shift to right is needed by 1..8 positions.
   Optimization: accumulate an info about tail into rB2.	*/
	cp	r1, rB0
	cpc	r1, rB1
	cpc	r1, rB2
	sbc	rB2, rB2
  ; shift to right
1:	inc	rA3		; exponent += 1
	lsr	ZH
	ror	rA2
	ror	rA1
	ror	rA0
	ror	rB3
	sbci	rB2, 0		; set rB2[7] if C was 1
	tst	ZH
	brne	1b
	rjmp	.L_round

  ; x == 0
2:	clr	rA3
	ret
  ; check: is fast shift possible?
.L_tstA2:
	tst	rA2
	brne	4f
  ; fast shift to left
3:	subi	rA3, 8
	brpl	2b		; 127+55 - 7*8 --> 126
	or	rA2, rA1	; obtain Z flag
	mov	rA1, rA0
	mov	rA0, rB3
	mov	rB3, rB2
	mov	rB2, rB1
	mov	rB1, rB0
	ldi	rB0, 0
	breq	3b		; Z is result of 'or rA2,rA1'

/* rA2 is not 0.  It is needed shift to left by 0..7 positions.
   Optimization: rB2..rB0 are not shifted. Instead, save an info
   about tail in rB2.	*/
4:	cp	r1, rB0
	cpc	r1, rB1
	cpc	r1, rB2
	sbc	rB2, rB2
	tst	rA2
	brmi	.L_round
5:	dec	rA3		; exponent -= 1
	lsl	rB2
	rol	rB3
	rol	rA0
	rol	rA1
	rol	rA2
	brpl	5b

/* Round and pack. Now we have:
     rA3		- mantissa
     rA2.rA1.rA0.rB3	- fraction
     rB2		- is negative if tail is not equal 0	*/
.L_round:
	tst	rB3
	brpl	7f
	lsl	rB2
	rol	rB3
	brne	6f
	sbrs	rA0, 0		; round to even
	rjmp	7f
6:	subi	rA0, -1
	sbci	rA1, -1
	sbci	rA2, -1
	sbci	rA3, -1
  ; pack
7:	lsl	rA2
	lsr	rA3
	ror	rA2
	bld	rA3, 7		; sign
	ret
ENDF __floatundisf


DEFUN	__fixsfdi
	ldi	rAE, 62
	rcall	.L_sf2di
	brcc	1f
	ldi	rA3, 0x80
1:	ret

DEFUN	__fixunssfdi
	ldi	rAE, 63

.L_sf2di:
  ; clear LSBytes
	clr	rB0
	clr	rB1
	movw	rB2, rB0
  ; split
	rcall	__fp_splitA
	brcs	.L_ovfl		; is not finite

	subi	rA3, 127	; 1.0 exponent field
	brlo	.L_zero		; too small

	cp	rAE, rA3
	brlo	.L_ovfl		; fabs(A) >= 2**64 (or 2**63)
	ldi	rAE, 63
	sub	rAE, rA3
	/* Now rAE is, for example:
	     63 - exponent was 127+0, shift >>55 is needed,
	      0 - exponent was 127+63, shift <<8 is needed.	*/
	clr	rA3
	subi	rAE, 8		; rAE= -8..+55
	brpl	3f
  ; fabs(A) >= 1.0 * 2**56  Shift to left is needed.
	/* Shift to 8 is not optimized specially as an exotic.	*/
2:	lsl	rA0
	rol	rA1
	rol	rA2
	rol	rA3
	inc	rAE
	brmi	2b
	rjmp	.L_sign2
  ; Shift to right is needed
3:	/* Now rAE:
	     55 - exponent was 127+0, shift >>55 is needed,
	      1 - exponent was 127+54, shift >>1 is needed,
	      0 - exponent was 127+55, no shift is needed.	*/
	subi	rAE, 8
	brmi	5f
  ; quick shift by 8
4:	mov	rB0, rB1
	mov	rB1, rB2
	mov	rB2, rB3
	mov	rB3, rA0
	mov	rA0, rA1
	mov	rA1, rA2
	clr	rA2
	subi	rAE, 8
	brpl	4b

5:	subi	rAE, -8		; rAE = 0..7
	breq	.L_sign2
  ; shift to 1..7 positions
6:	lsr	rA2
	ror	rA1
	ror	rA0
	ror	rB3
	ror	rB2
	ror	rB1
	ror	rB0
	dec	rAE
	brne	6b
.L_sign2:
	brtc	7f
	rcall	__fp_negdi
7:	clc
	ret

.L_zero:
	clc
.L_ovfl:			  ; overflow, C is set already
	ldi	rA0, 0
	ldi	rA1, 0
	movw	rA2, rA0
	ret
ENDF __fixsfdi


DEFUN   __floatunsisf
	clt
	rjmp	1f

DEFUN   __floatsisf
	bst	rA3, 7		; sign
	brtc	1f
  ; negate A
	com	rA3
	com	rA2
	com	rA1
	neg	rA0
	sbci	rA1, -1
	sbci	rA2, -1
	sbci	rA3, -1
1:
	tst	rA3
	breq	4f
  ; shift to right
	mov	ZH, rA3
	ldi	rA3, 127 + 23	; exponent
	clr	rAE
2:	inc	rA3
	lsr	ZH
	ror	rA2
	ror	rA1
	ror	rA0
	ror	rAE
	cpse	ZH, r1
	rjmp	2b
  ; rounding
	brpl	.L_pack		; flags from 'ror rAE'
	lsl	rAE
	brne	3f
	sbrs	rA0, 0		; round to even
	rjmp	.L_pack
3:	subi	rA0, -1
	sbci	rA1, -1
	sbci	rA2, -1
	sbci	rA3, -1
	rjmp	.L_pack

4:	tst	rA2
	breq	5f
	ldi	rA3, 127 + 23
	rjmp	8f

5:	tst	rA1
	breq	6f
	ldi	rA3, 127 + 15
	mov	rA2, rA1
	mov	rA1, rA0
	rjmp	7f

6:	tst	rA0
	breq	9f		; 0.0
	ldi	rA3, 127 + 7
	mov	rA2, rA0
	ldi	rA1, 0
7:
	ldi	rA0, 0
	brmi	.L_pack		; flag from 'tst rA*'
  ; shift to left by 1..7 positions
10:	dec	rA3
	lsl	rA0
	rol	rA1
	rol	rA2
8:	brpl	10b

.L_pack:
	lsl	rA2
	lsr	rA3
	ror	rA2
	bld	rA3, 7		; sign
9:	ret
ENDF __floatunsisf
