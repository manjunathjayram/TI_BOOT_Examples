;; Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
;;
;;
;;  Redistribution and use in source and binary forms, with or without
;;  modification, are permitted provided that the following conditions
;;  are met:
;;
;;    Redistributions of source code must retain the above copyright
;;    notice, this list of conditions and the following disclaimer.
;;
;;    Redistributions in binary form must reproduce the above copyright
;;    notice, this list of conditions and the following disclaimer in the
;;    documentation and/or other materials provided with the
;;    distribution.
;;
;;    Neither the name of Texas Instruments Incorporated nor the names of
;;    its contributors may be used to endorse or promote products derived
;;    from this software without specific prior written permission.
;;
;;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
;;  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
;;  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;;  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
;;  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
;;  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
;;  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;;  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;;  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;;  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
;;  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


	.global	 armNum
	.global  _c_int00_supervisor                
	.global  myStart

	.ref    _main
	.ref    __TI_auto_init
	.ref    _main_func_sp

	.sect ".myStart"
myStart:
	b	_c_int00_supervisor

	
;;  Each core gets its own supervisor stack
STACK_SIZE	.set	0x100
MAXARMS		.set	0x2
stacks		.usect	".stacks", 	MAXARMS * STACK_SIZE

;;  Use the TI standard library functions for setting up cinit and bss

	.text
val_stacks		.word	stacks
c_mf_sp			.word	_main_func_sp
c_ti_auto		.word	__TI_auto_init

_c_int00_supervisor:

	;;   Set the initial endianness
	.if .TMS470_BIG
		setend 	BE
	.else
		setend	LE
	.endif

	;; Setup the stack
	bl		armNum				;; Read the ARM core number
	add		r0, r0, #1			;; Make the core number start at 1 

	movw	r1,  #STACK_SIZE	;; the size of the stack
	mul		r0,  r0, r1			;; Then end offset of the stack for this core
	ldr		r1,  val_stacks		;; The base address of the stack
	add		r13, r1, r0			;; The end of the stack
	sub		r13, r13, #4		;; Back up one word

	ldr		r0,  c_mf_sp		;; Save the stack value for auto-init
	mov		r7,  r13
	str		r7,  [r0]

	
	;; use the TI library to setup cinit and bss
	ldr  r1, c_ti_auto
	adr  lr, _cret1

	bx r1

	
_cret1:
	b _main

	
mtrap:  b mtrap


;; *********************************************************************************
;; * FUNCTION PURPOSE: Return the ARM core number
;; *********************************************************************************
;; * DESCRIPTION: Reads the multi-processor ID and returns it
;; *********************************************************************************

armNum:
	mrc		p15, #0, r0, c0, c0, #5		;;  Read the multi-processor affinity register
	and		r0,  r0, #3					;;   The core number
	bx		lr	


;; *********************************************************************************
;; * FUNCTION PURPOSE: Read the system control reg
;; *********************************************************************************
;; * DESCRIPTION: This register is banked, so the version returned corresponds 
;; *              to whatever secure state is active
;; *********************************************************************************

		.global readSysCtl
readSysCtl:
		mrc		p15, #0, r0, c1, c0, #0
		bx		lr

;; ********************************************************************************************
;; * FUNCTION PURPOSE: Invalidate program cache at a specified address and size
;; ********************************************************************************************
;; * DESCRIPTION: A subset of the program cache is invalidated
;; *
;; *  C usage: void hwInvalidateICache (UINT32 addr, UINT32 sizeBytes)
;; *
;; ********************************************************************************************

   .global _hwInvalidateICache

_hwInvalidateICache:

    ;; Find the cache line size in bytes
    mrc  p15, #0, r2, c0, c0, #1          ;; Read CTR into r2

    mov  r2,  r2, lsr #16                 ;; Bits 16-19 is log2 of the cache line size in words
    and  r2,  r2, #0xf

    mov  r3,  #1                          ;; Get the cache line size in words
    lsl  r3,  r3, r2

    lsl  r3,  r3, #2                      ;; And finally the cache line size in bytes

    rsb  r2,  r3, #0                      ;; invert the mask
    
    add  r1,  r0, r1                      ;; r1 holds the end address
                                          ;; 
    mcr  p15, #0, r0, c7, c5, #1          ;; ICIMVAU 

    and  r0, r0, r2                       ;; Get the address cache line aligned       
    add  r0, r0, r3                       ;; Move to the next cache line

iiloop0:

    cmp  r0, r1
   bge  iiloop1

    mcr  p15, #0, r0, c7, c5, #1          ;; ICIMVAU
    add  r0,  r0, r3
    b    iiloop0

iiloop1:

    dsb

    bx   lr
