/* Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

/************************************************************************************
 * FILE PURPOSE: The K2E/K2L 2nd stage ethernet bug fix program
 ************************************************************************************
 * FILE NAME: Stage1_ethWard.cmd
 *
 * DESCRIPTION: The 2nd stage ethernet boot rom fix
 *
 *************************************************************************************/

ethWard.oc 
mmu.oa 
armstart.oa

-e _c_int00_supervisor 

-c
-a
-stack 0x400

_romtDelay32=         	0x0000101c;
_romtConfigPll=       	0x00001018;
_romtPscEnableModule= 	0x00001008;
_romtReEntry=         	0x00001004;
_romtMainEmif4Cfg=		0x00001034;

MEMORY
{
	DLD  :  origin = 0x0c000000, length = 0x2000
	DATA :  origin = 0x0c002000, length = 0x2000
	DDR3_CFG   		:  	origin = 0x0C1A6E00 	length = 0x0000016C


}


SECTIONS
{

	GROUP  > DLD  START(_blob_start) SIZE(_blob_size)
	{
		.bstart
		.text
		.const
		.switch
		.cinit
	}

	.stack  > DATA
	.far    > DATA
	.bss    > DATA
	.ddrConfig			> DDR3_CFG

}




