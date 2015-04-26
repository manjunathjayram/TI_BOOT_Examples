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

//Boot config kick register addresses
#define CHIP_LEVEL_REG              0x02620000
#define KICK0                       (*(int*)(0x02620038))
#define KICK1                       (*(int*)(0x0262003C))

/******************* PLL registers **********************************/
#define KICK0_UNLOCK                (0x83E70B13)
#define KICK1_UNLOCK                (0x95A4F1E0)
#define KICK_LOCK                   0
#define TINPSEL                     *(unsigned int*)(CHIP_LEVEL_REG + 0x0300)
#define TOUTPSEL                    *(unsigned int*)(CHIP_LEVEL_REG + 0x0304)
#define MAINPLLCTL0                 *(unsigned int*)(CHIP_LEVEL_REG + 0x0350) //0x0328)
#define MAINPLLCTL1                 *(unsigned int*)(CHIP_LEVEL_REG + 0x0354) //0x032C)
#define MAIN_PLLD_OFFSET            0
#define MAIN_PLLD_MASK              0xFFFFFFC0
#define MAIN_PLLM_OFFSET            12
#define MAIN_PLLM_MASK              0xFFF80FFF
#define MAIN_BWADJ0_OFFSET          24
#define MAIN_BWADJ0_MASK            0x00FFFFFF
#define MAIN_ENSAT_OFFSET           6
#define MAIN_ENSAT_MASK             0xFFFFFFBF
#define MAIN_BWADJ1_OFFSET          0
#define MAIN_BWADJ1_MASK            0xFFFFFFF0


//******************************************************
// PLL 1 definitions (DSP and ARM clock and subsystems)
#define PLL1_BASE                   0x02310000
#define PLL1_PLLCTL                 (*(unsigned int*)(PLL1_BASE + 0x100))   // PLL1 Control
#define PLL1_SECCTL                 (*(unsigned int*)(PLL1_BASE + 0x108))   // PLL1 Secondary Control
#define PLL1_PLLM                   (*(unsigned int*)(PLL1_BASE + 0x110))   // PLL1 Multiplier
#define PLL1_DIV1                   (*(unsigned int*)(PLL1_BASE + 0x118))   // DIV1 divider
#define PLL1_DIV2                   (*(unsigned int*)(PLL1_BASE + 0x11C))   // DIV2 divider
#define PLL1_DIV3                   (*(unsigned int*)(PLL1_BASE + 0x120))   // DIV3 divider
#define PLL1_CMD                    (*(unsigned int*)(PLL1_BASE + 0x138))   // CMD control
#define PLL1_STAT                   (*(unsigned int*)(PLL1_BASE + 0x13C))   // STAT control
#define PLL1_ALNCTL                 (*(unsigned int*)(PLL1_BASE + 0x140))   // ALNCTL control
#define PLL1_DCHANGE                (*(unsigned int*)(PLL1_BASE + 0x144))   // DCHANGE status
#define PLL1_CKEN                   (*(unsigned int*)(PLL1_BASE + 0x148))   // CKEN control
#define PLL1_CKSTAT                 (*(unsigned int*)(PLL1_BASE + 0x14C))   // CKSTAT status
#define PLL1_SYSTAT                 (*(unsigned int*)(PLL1_BASE + 0x150))   // SYSTAT status
#define PLL1_DIV4                   (*(unsigned int*)(PLL1_BASE + 0x160))   // DIV4 divider
#define PLL1_DIV5                   (*(unsigned int*)(PLL1_BASE + 0x164))   // DIV5 divider
#define PLL1_DIV6                   (*(unsigned int*)(PLL1_BASE + 0x168))   // DIV6 divider
#define PLL1_DIV7                   (*(unsigned int*)(PLL1_BASE + 0x16C))   // DIV7 divider
#define PLL1_DIV8                   (*(unsigned int*)(PLL1_BASE + 0x170))   // DIV8 divider
#define PLL1_DIV9                   (*(unsigned int*)(PLL1_BASE + 0x174))   // DIV9 divider
#define PLL1_DIV10                  (*(unsigned int*)(PLL1_BASE + 0x178))   // DIV10 divider
#define PLL1_DIV11                  (*(unsigned int*)(PLL1_BASE + 0x17C))   // DIV11 divider
#define PLL1_DIV12                  (*(unsigned int*)(PLL1_BASE + 0x180))   // DIV12 divider
#define PLL1_DIV13                  (*(unsigned int*)(PLL1_BASE + 0x184))   // DIV13 divider
#define PLL1_DIV14                  (*(unsigned int*)(PLL1_BASE + 0x188))   // DIV14 divider
#define PLL1_DIV15                  (*(unsigned int*)(PLL1_BASE + 0x18C))   // DIV15 divider
#define PLL1_DIV16                  (*(unsigned int*)(PLL1_BASE + 0x190))   // DIV16 divider
#define PLLPWRDN_OFFSET             1
#define PLLPWRDN_MASK               0xFFFFFFFD
#define PLLRST_OFFSET               3
#define PLLRST_MASK                 0xFFFFFFF7
#define PLLENSRC_OFFSET             5
#define PLLENSRC_MASK               0xFFFFFFDF
#define PLLEN_OFFSET                0
#define PLLEN_MASK                  0xFFFFFFFE
#define OUTPUT_DIVIDE_OFFSET        19
#define OUTPUT_DIVIDE_MASK          0xFF87FFFF
#define BYPASS_OFFSET               23
#define BYPASS_MASK                 0xFF7FFFFF
#define PLLM_OFFSET                 0
#define PLLM_MASK                   0xFFFFFFC0
#define GOSET_OFFSET                0
#define GOSET_MASK                  0xFFFFFFFE
#define GOSTAT_OFFSET               0
#define GOSTAT_MASK                 0xFFFFFFFE

/*Prototype*/
void Set_Pll1(void);

