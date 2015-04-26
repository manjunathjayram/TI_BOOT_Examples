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
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */


#ifndef __ARMv7
    #define __ARMv7
#endif

#include <stdio.h>
#include <stdint.h>
#include "tiboot.h"
#include "ddrConfigTable.h"
#include "uart.h"
#include "pll.h"


#ifdef K2E
#include <ti/csl/device/k2e/src/cslr_device.h>
#endif

#ifdef K2H
#include <ti/csl/device/k2h/src/cslr_device.h>
#endif

#include <ti/csl/csl_sem.h>
#include <ti/csl/csl_semAux.h>

/* Device Specific BootROM defined details */
#ifdef K2E
#define ARM_MAGIC                   (*(int*)(0x0C1AD000))
#define ARM_MAGIC_BASE              0x0C1AD000
#endif

#ifdef K2H
#define ARM_MAGIC                   (*(int*)(0x0C5AD000))
#define ARM_MAGIC_BASE              0x0C5AD000
#endif

//Addresses used to set the secondary ARM cores' boot magic addresses
#define NUM_ARM_CORES               4
#define ARM_MAGIC_ADDRESS(X)        (ARM_MAGIC_BASE + (X * 0x4))

//Addresses used to power on the secondary ARM cores
#define TETRIS_BASE                 0x01E80000
#define TETRIS_PTCMD_CPU(X)         *(unsigned int*)(TETRIS_BASE + 0x400 + (X * 0xC))
#define TETRIS_PDSTAT_CPU(X)         *(unsigned int*)(TETRIS_BASE + 0x404 + (X * 0xC))
#define TETRIS_PDCTL_CPU(X)         *(unsigned int*)(TETRIS_BASE + 0x408 + (X * 0xC))

//Boot config kick register addresses
#define CHIP_LEVEL_REG              0x02620000
#define KICK0                       (*(int*)(0x02620038))
#define KICK1                       (*(int*)(0x0262003C))
    
#ifdef DDR
#define ARM_IDLE_ADDRESS            0x80005000
#else	
#define ARM_IDLE_ADDRESS            0x0c002000
#endif

extern hwFlushCache(void);
extern unsigned int romtBootReentry_addr;
extern unsigned int romtArmNum_addr;

char * messages[4] = {  "Core 0 standing by... \n\r", 
                        "Core 1 standing by... \n\r", 
                        "Core 2 standing by... \n\r",
                        "Core 3 standing by... \n\r" };
volatile int coreSync = 0;


#pragma CODE_SECTION (armIdle, ".armIdle");
void armIdle() {

    unsigned int (*func)(void);
    int i = 0;
    int j = 0;
    uint16_t brate = 90;
    
    unsigned short num = 0;
    func = (unsigned int (*)(void))&romtArmNum_addr;    // Get ARM core number
    num = (*func)();

    Set_Pll1();
    UartInit();
    
    UartSetBaudRate(brate);

    while (1) {

        while(coreSync != num);
        while((CSL_semAcquireDirect(5)) == 0);
        write_uart(messages[num]);

        if (coreSync == 3) {
            coreSync =  0;
        }
        else {
            coreSync++;
        }
        CSL_semReleaseSemaphore (5);

        for (i = 0; i < 100000; i++) {
            for (j = 0; j < 20; j++) {}     // Some delay
        }
    }
}

#ifdef DDR
#pragma  DATA_SECTION (emif4vCfg, ".emif4vCfg") /* Places the DDR configuration table from ddrConfigTableK2E.h into correct memory space */
#endif

/********************************************************************************
 * The re-entry function address defined in the command linker file
 ********************************************************************************/

main() {

	void (*fcn)(void);

    ARM_MAGIC = 0x0;

	int i;
	volatile unsigned int  *bootMagicAddress, *interruptAddress, *armMagicAddress;
	
	/* Unlock the kick registers so that we can generate the DSP IPC interrupts */
	KICK0 = 0x83E70B13;
	KICK1 = 0x95A4F1E0;
	
	for(i = 1; i < NUM_ARM_CORES; i++)
	{
		//update ARM Core(i)'s boot magic address 
		armMagicAddress = (unsigned int*)ARM_MAGIC_ADDRESS(i);
		*armMagicAddress = ARM_IDLE_ADDRESS;
		
		//power on ARM Core(i)
		TETRIS_PDCTL_CPU(i)   = 0x00000000;
		TETRIS_PTCMD_CPU(i)   = 0x00000001;
	}

	armIdle();
	
}


