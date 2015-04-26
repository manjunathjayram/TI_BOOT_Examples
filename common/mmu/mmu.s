;/* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
; *
; *
; *  Redistribution and use in source and binary forms, with or without
; *  modification, are permitted provided that the following conditions
; *  are met:
; *
; *    Redistributions of source code must retain the above copyright
; *    notice, this list of conditions and the following disclaimer.
; *
; *    Redistributions in binary form must reproduce the above copyright
; *    notice, this list of conditions and the following disclaimer in the
; *    documentation and/or other materials provided with the
; *    distribution.
; *
; *    Neither the name of Texas Instruments Incorporated nor the names of
; *    its contributors may be used to endorse or promote products derived
; *    from this software without specific prior written permission.
; *
; *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
; *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
; *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
; *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
; *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
; *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
; *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
; *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
; *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
; * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
;/************************************************************************************
; * FILE PURPOSE: Low level MMU driver
; ************************************************************************************
; * FILE NAME: mmu.s
; *
; * DESCRIPTION: The low level MMU driver
; *
; *************************************************************************************


;;		C usage: bool hwArmMmuDisable (void);  -> returns TRUE if the MMU was currently enabled

	.global hwArmMmuDisable
	.global _hwArmMmuDisable

hwArmMmuDisable:
_hwArmMmuDisable:

		mrc		p15, #0, r1, c1, c0, #0
		and		r0,  r1, #1					;; Bit 0 holds the MMU state. Return 1 if MMU was enabled
		bic     r1,  r1, #1					;; Clear bit 1 disables the MMU
		bic		r1,  r1, #(1 << 12) 		;; Clear bit 12 disables the i-cache
		bic		r1,  r1, #(1 <<  2)			;; Clear bit 2 disables the data and unified cache
		mcr		p15, #0, r1, c1, c0, #0
		dsb


		bx		lr



;;		C usage: hwArmMmuEnable (void);

	.global hwArmMmuEnable
	.global _hwArmMmuEnable


hwArmMmuEnable:
_hwArmMmuEnable:

		mrc		p15, #0, r0, c1, c0, #0
		orr		r0,  r0, #1					;; Bit 0 set enables the mmu
		orr		r0,  r0, #(1 << 12)			;; Bit 12 set enables the icache
		orr		r0,  r0, #(1 <<  2)			;; Bit 2 set enables the data and unified cache
		mcr		p15, #0, r0, c1, c0, #0
		dsb

		bx		lr
