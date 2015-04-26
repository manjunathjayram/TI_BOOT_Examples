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

; /**************************************************************************************
;  * FILE PURPOSE: ARM start code
;  **************************************************************************************
;  * FILE NAME: armStart.s
;  *
;  * DESCRIPTION: Provides assembly support functions 
;  *
;  ***************************************************************************************


	.ref    __TI_auto_init
	.ref    _main_func_sp
	.ref    __stack
	.ref    __STACK_SIZE
	.ref    __args_main
	.ref	_exit

	.sect ".bstart"
	
	.global _c_int00_supervisor


_c_int00_supervisor:


	ldr		r0,  val_ssize		;; stack size
	ldr		r1,  val_stacks		;; The base address of the stack
	add		r13, r1, r0			;; The end of the stack
	sub		r13, r13, #4		;; Back up one word

	;; use the TI library initialization
	ldr		r0,  c_mf_sp		;; Save the stack value for auto-init
	str	    r13, [r0]
	bl      __TI_auto_init
	bl      __args_main
	mov		r0, #1
	bl      _exit


mtrap:  b mtrap


val_stacks		.word	__stack
val_ssize		.word	__STACK_SIZE
c_mf_sp			.word	_main_func_sp





