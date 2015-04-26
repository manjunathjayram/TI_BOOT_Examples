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


#include "tiboot.h"
#include "ddrConfigTable.h"
#include "paramTables.h"

#ifdef K2H
#ifdef BLOB
#include "rand1k.h"
#endif
#endif
 
#pragma DATA_SECTION(boot_params, ".bootParams")
BOOT_PARAMS_T boot_params;

#ifdef DDR
#pragma DATA_SECTION(ddr_config, ".ddrConfig")
BOOT_EMIF4V_TBL_T ddr_config;
#endif

#ifdef K2E
#define ARM_MAGIC                   (*(int*)(0x0C1AD000))
#define ARM_MAGIC_BASE              0x0C1AD000
#endif

#ifdef K2H
#define ARM_MAGIC                   (*(int*)(0x0C5AD000))
#define ARM_MAGIC_BASE              0x0C5AD000
#endif

#define ARM_MAGIC_ADDRESS(X)        (ARM_MAGIC_BASE + (X * 0x4))
#define ARM_IDLE_ADDRESS            0x00000000

/********************************************************************************
 * The re-entry function address defined in the command linker file
 ********************************************************************************/
extern unsigned int romtBootReentry_addr;

/* ROM table call to initialize DDR (Only defined in K2E/K2L) */
#ifdef K2E
extern unsigned int romtMainEmif4Cfg_addr;
#endif

main()
{   
	void (*fcn)(void);
	volatile unsigned int  *armMagicAddress;
		
	/* Copy the boot parameter table defined above into place over the existing boot parameter table located at 0x0C1D8500 */
    memcpy (&boot_params, &params, sizeof(params));

#ifdef BLOB

#ifdef DDR	
	/* Configure DDR3 for use */
	memcpy (&ddr_config, &emif4vCfg, sizeof(emif4vCfg));
	fcn = (void (*)(void))&romtMainEmif4Cfg_addr;
	(*fcn)();
#endif


	/* Enable the MMU and enable both the data and instruction cache */
	asm(
		"   mcr     p15, #0, r0, c8, c5, #0 			\t\n"    // ;; ITLBIALL, Instruction TLB invalidate all. Operation ignores Rt value.
		"   mcr     p15, #0, r0, c8, c6, #0    			\t\n" //;; DTLBIALL, Data TLB invalidate all. Operation ignores Rt value.
		"	isb					                 		\t\n"
		"	dsb					                 		\t\n"	
		"	mrc		p15, #0, r0, c1, c0, #0         	\t\n"	
		"	orr		r0,  r0, #1                 		\t\n"	//Bit 0 set enables the mmu
		"	orr		r0,  r0, #(1 << 12)                 \t\n"	//Bit 12 set enables the icache
		"	orr		r0,  r0, #(1 <<  2)         		\t\n"	//Bit 2 set enables the data and unified cache
		"	mcr		p15, #0, r0, c1, c0, #0     		\t\n"	
		"	isb					                 		\t\n"
		"	dsb					                 		\t\n"	
	);
		
#endif
	
	/* Work around for K2H boot as the bootRentry function expects magic address to be zero */
#ifdef K2H

#ifdef BLOB
	/* Invalidate Instruction cache on K2H as bootROM loads both stages at the base of MSMC*/
	hwInvalidateICache(0x0c000000, 0x8000);		
#endif
	
   	/* Zero out the ARM MAGIC Address */
	armMagicAddress = (unsigned int*)ARM_MAGIC_ADDRESS(0);
	*armMagicAddress = ARM_IDLE_ADDRESS;
#endif

	/* Re-enter the boot rom without sampling the boot strap pins again to allow the modified boot parameter table to be used for boot */
    fcn = (void (*)(void))&romtBootReentry_addr;
	(*fcn)();
}
