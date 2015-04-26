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
 
#include <stdio.h>
#include <stdint.h>
 
#include "pll.h"

unsigned int delay = 2000;
unsigned int delay2 = 2000;
unsigned int delay3a = 50000;
unsigned int read_val;

void Set_Pll1(void) {
    int i;
    unsigned int BYPASS_val;
    unsigned int BWADJ_val;
    unsigned int OD_val;
	float CLKIN_val;
    unsigned int PLLM_val;
    unsigned int PLLD_val;
    unsigned int PLLDIV3_val; //example value for SYSCLK2 (from 6614 spec) Default /2 - Fast Peripherals, (L2, MSMC, DDR3 EMIF, EDMA0...)
    unsigned int PLLDIV4_val; //example value for SYSCLK3 (from 6614 spec) Default /3 - Switch Fabric
    unsigned int PLLDIV7_val; //example value for SYSCLK6 (from 6614 spec) Defualt /6 - Slow Peripherals (UART, SPI, I2C, GPIO...)

	/* Device specific clocking for the EVMs */
#ifdef K2E
	CLKIN_val   = 100;         // setup CLKIN to 100.00 MHz
	PLLM_val    = 20;           // setup PLLM (PLL multiplier) to x20
	PLLD_val    = 1;            // setup PLLD (reference divider) to /1
	OD_val      = 2;            // setup OD to a fixed /2
#endif
	
#ifdef K2H
	CLKIN_val   = 122.88;         // setup CLKIN to 122.88 MHz
	PLLM_val    = 16;           // setup PLLM (PLL multiplier) to x20
	PLLD_val    = 1;            // setup PLLD (reference divider) to /1
	OD_val      = 2;            // setup OD to a fixed /2
#endif

    PLLDIV3_val = 3;            // setup PLL output divider 3 to /3
    PLLDIV4_val = 5;            // setup PLL output divider 4 to /3
    PLLDIV7_val = 6;            // setup PLL output divider 7 to /6

    BYPASS_val      = PLL1_SECCTL & ~BYPASS_MASK;   // get value of the BYPASS field
    BWADJ_val       = (PLLM_val) >> 1;              // setup BWADJ to be 1/2 the value of PLLM
    OD_val          = 2;                            // setup OD to a fixed /2

    /* Step 1: Unlock Boot Config Registers */
    KICK0 = KICK0_UNLOCK;
    KICK1 = KICK1_UNLOCK;

    /* Step 2: Check if SECCTL bypass is low or high indicating what state the Main PLL is currently in. if
       the Main PLL is in bypass still (not yet setup) execute the following steps.  */

    if(BYPASS_val != 0x00000000){ // PLL bypass enabled - Execute PLL setup for PLL fresh out of power on reset
        /* Step 2a: Set MAINPLLCTL1[ENSAT] = 1 - This enables proper biasing of PLL analog circuitry */
        MAINPLLCTL1 |= (1 << MAIN_ENSAT_OFFSET);

        /* Step 2b: Set PLLCTL[PLLEN] = 0 This enables bypass in PLL controller MUX */
        PLL1_PLLCTL &= ~(1 << PLLEN_OFFSET);

        /* Step 2c: Set PLLCTL[PLLENSRC] = 0 - This enables PLLEN to control PLL controller MUX */
        PLL1_PLLCTL &= ~(1 << PLLENSRC_OFFSET);

        /* Step 2d: Wait 4 reference clock cycles (slowest of ALTCORE or SYSCLK) to make sure
           that the PLL controller MUX switches properly to bypass. */
        for(i = 0; i < delay; i++); // this delay is much more than required

        /* Step 2e: Set SECCTL[BYPASS] = 1 - enables bypass in PLL MUX */
        PLL1_SECCTL |= (1 << BYPASS_OFFSET);

        /* Step 2f: Set PLLCTL[PLLPWRDN] = 1 - power down the PLL */
        PLL1_PLLCTL |= (1 << PLLPWRDN_OFFSET);

        /* Step 2g: Wait for at least 5us for the PLL to power down */
        for(i = 0; i < delay; i++); // this delay is much more than required

        /* Step 2h: Set PLLCTL[PLLPWRDN] = 0 - Power the PLL back up */
        PLL1_PLLCTL &= ~(1 << PLLPWRDN_OFFSET);

    }
    else { // PLL bypass disabled - Execute PLL setup for PLL that has previously been locked (skip to Step 3)

        /* Step 3a: Set PLLCTL[PLLEN] = 0 This enables bypass in PLL controller MUX */
        PLL1_PLLCTL &= ~(1 << PLLEN_OFFSET);

        /* Step 3b: Set PLLCTL[PLLENSRC] = 0 - This enables PLLEN to control PLL controller MUX */
        PLL1_PLLCTL &= ~(1 << PLLENSRC_OFFSET);

        /* Step 3c: Wait 4 reference clock cycles (slowest of ALTCORE or SYSCLK) to make sure
           that the PLL controller MUX switches properly to bypass. */
        for(i = 0; i < delay; i++); // this delay is much more than required

    }


    /* Step 4: Programming PLLM[5:0] in the PLLM register of the PLL controller and
       programming PLLM[12:6] in the MAINPLLCTL0 register */
    PLL1_PLLM &= PLLM_MASK;             // clear the PLLM[5:0] bit field
    PLL1_PLLM |= ~PLLM_MASK & (PLLM_val - 1);   // set the PLLM[5:0] bit field to the 6 LSB of PLLM_val

    MAINPLLCTL0 &= MAIN_PLLM_MASK;      // clear the PLLM[12:6] bit field
    MAINPLLCTL0 |= ~MAIN_PLLM_MASK & (( (PLLM_val - 1) >> 6) << MAIN_PLLM_OFFSET);  // set the PLLM[12:6] bit field to the 7 MSB of PLL_val

    /* Step 5: Programming BWADJ[7:0] in the MAINPLLCTL0 register and BWADJ[11:8] in MAINPLLCTL1 register */
    MAINPLLCTL0 &= MAIN_BWADJ0_MASK;    // clear the MAIN_BWADJ0 bit field
    MAINPLLCTL0 |= ~MAIN_BWADJ0_MASK & ((BWADJ_val - 1) << MAIN_BWADJ0_OFFSET); // set the MAIN_BWADJ[7:0] bit field to the 8 LSB of BWADJ_val

    MAINPLLCTL1 &= MAIN_BWADJ1_MASK;    // clear the MAIN_BWADJ1 bit field
    MAINPLLCTL1 |= ~MAIN_BWADJ1_MASK & (( (BWADJ_val - 1) >> 8) << MAIN_BWADJ1_OFFSET); // set the MAIN_BWADJ[11:8] bit field to the 4 MSB of BWADJ_val

    /* Step 6: Programming PLLD[5:0] in the MAINPLLCTL0 register */
    MAINPLLCTL0 &= MAIN_PLLD_MASK;      // clear the PLLD bit field
    MAINPLLCTL0 |= ~MAIN_PLLD_MASK & (PLLD_val - 1);    // set the PLLD[5:0] bit field of PLLD to PLLD_val


    /* Step 7: Programming OD[3:0] in the SECCTL register */
    PLL1_SECCTL &= OUTPUT_DIVIDE_MASK;  // clear the OD bit field
    PLL1_SECCTL |= ~OUTPUT_DIVIDE_MASK & (OD_val - 1) << OUTPUT_DIVIDE_OFFSET;  // set the OD[3:0] bit field of PLLD to OD_val


    /* Step 8: Following steps are needed to change the default output dividers */

    /* Step 8a: Check that the GOSTAT bit in PLLSTAT is cleared to show that no GO
       operation is currently in progress*/
    while((PLL1_STAT) & 0x00000001);

    /* Step 8b: Program the RATIO field in PLLDIVn to the desired new divide-down rate.
       If RATIO field is changed, the PLL controller will flag the change in the
       corresponding bit of DCHANGE*/
    PLL1_DIV3 = (PLLDIV3_val-1) | 0x8000;  //Set PLLDIV3
    PLL1_DIV4 = (PLLDIV4_val-1) | 0x8000;  //Set PLLDIV4
    PLL1_DIV7 = (PLLDIV7_val-1) | 0x8000;  //Set PLLDIV7

    /* Step 8c: Set GOSET bit in PLLCMD to initiate the GO operation to change the divide
       values and align the SYSCLKs as programmed */
    PLL1_CMD |= 0x00000001;

    /*Step 8d/e: Read the GOSTAT bit in PLLSTAT to make sure the bit returns to 0 to
      indicate that the GO operation has completed */
    while((PLL1_STAT) & 0x00000001);

    /* Step 9: Set PLLCTL[PLLRST] = 1 - Assert PLL reset (Previously Step 3)*/
    PLL1_PLLCTL |= (1 << PLLRST_OFFSET);

    /* Step 10: Wait for the at least 7us for the PLL reset properly (128 CLKIN1 cycles) */
    for(i=0;i<delay;i++);

    /* Step 11: Set PLLCTL[PLLRST] = 0 - De-Assert PLL reset */
    PLL1_PLLCTL &= ~(1 << PLLRST_OFFSET);

    /* Step 12: Wait for PLL to lock (2000 CLKIN1 cycles) */
    for(i=0;i<delay;i++);

    /* Step 13: In SECCTL, write BYPASS = 0 (enable PLL mux to switch to PLL mode) */
    PLL1_SECCTL &= ~(1 << BYPASS_OFFSET);

	for(i=0;i<delay;i++);

	for(i=0;i<delay;i++);

    /* Step 14: In PLLCTL, write PLLEN = 1 to enable PLL mode */
    PLL1_PLLCTL |= (1 << PLLEN_OFFSET);

    /* Step 15: Lock Boot Config Registers */
    KICK0 = 0x00000000;
    KICK1 = 0x00000000;
}

