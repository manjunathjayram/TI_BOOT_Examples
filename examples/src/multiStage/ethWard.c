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

/*********************************************************************************************************************
 * FILE PURPOSE: First stage boot code to perform a 2nd stage ethernet boot using workaround specified in device Errata
 *********************************************************************************************************************
 * FILE NAME: ethWard.c
 *
 * DESCRIPTION: First stage boot code to enable second stage ethernet boot. This fixes a bug in the 
 *				K2E/K2L boot ROM code which does not initialize a PDPS
 *				register at initial statup
 *
 *
 * BUILD TIME CONFIGURATION: (values with (*) indicate default)
 *              DEVICE=      K2L  |  --*K2E*
 *              PLATFORM=    *EVM* | CUSTOM
 *              REF_CLK=     f50 | f66_66 |  f80 | --f100 | f156_25 | f250 | f312_5 | *f122_88*
 *              PA_CLK=      f50 | f66_66 |  f80 | f100 | f156_25 | f250 | f312_5 | *f122_88* | --f125
 *              SGMII=       MASTER | --*SLAVE* | FORCED
 *              SERDES_REF=  --*f125* | f156_25
 *
 *
 ****************************************************************************************/

#include "tiboot.h"
#include "ddrConfigTable.h"

#include "mmu_api.h"
#include "string.h"


/* Device */
#define K2L     0
#define K2E     1

/* Platform */
#define EVM     0
#define CUSTOM  1

/* Frequencies */
#define f50     0
#define f66_66  1
#define f80     2
#define f100    3
#define f156_25 4
#define f250    5
#define f312_5  6
#define f122_88 7
#define f125    8

/* SGMII connections */
#define MASTER  0
#define SLAVE   1
#define FORCED  2

#ifndef DEVICE
 #define DEVICE K2E
#endif 

#ifndef PLATFORM
 #define PLATFORM EVM
#endif

#ifndef REF_CLK
 #define REF_CLK  f122_88
#endif

#ifndef PA_CLK
 #define PA_CLK f122_88
#endif

#ifndef SGMII
 #define SGMII SLAVE
#endif

#ifndef SERDES_REF
 #define SERDES_REF f125
#endif

#define PHY_CALC_MASK(fieldOffset, fieldLen, mask)                      \
    if ((fieldLen + fieldOffset) >= 16)                                 \
        mask = (0 - (1 << fieldOffset));                                \
    else                                                                \
        mask = (((1 << (fieldLen + fieldOffset))) - (1 << fieldOffset))


/*   Begin Custom Configuration   */
const BOOT_PARAMS_BOOTP_ETHERNET_T myParams = {


    sizeof (BOOT_PARAMS_BOOTP_ETHERNET_T),      /* structure length, in bytes      */
    0,                                          /* checksum, 0 to disable          */
    90,                                         /* Boot mode = ethernet bootp/tftp */
    0,                                          /* Ethernet port number            */

    /* PLLs are enabled in this code, not touched in the 2nd stage boot */
    0,                                          /* swPllCfg_msw */
    0,                                          /* swPllCfg_lsw */
    0,                                          /* swPll2Cfg_msw */
    0,                                          /* swPll2Cfg_lsw */

    /* Device frequencies will be configured at run time */
    0,                                          /* sysFreqMhz   */
    0,                                          /* core FreqMhz */

    1,                                          /* Boot master */

    BOOT_PARAMS_BOOTP_OPTIONS_INIT_FULL <<      /* Options select a full init */
        BOOT_PARAMS_BOOTP_OPTIONS_INIT_SHIFT,

    /* The mac address is read from e-fuse */
    0,
    0,
    0,

    /* The broadcast mac address */
    0xffff,
    0xffff,
    0xffff,

    4000,                                       /* Initial bootp timeout, ms */
    1000,                                       /* Ttfp packet timeout, ms   */
    90,                                         /* Tftp total timeout        */

    10,                                         /* Bootp retry count         */
    10,                                         /* Tftp retry count          */


    /* Bootp vendor string is "TCI c66x Bootp Boot" */

    ('T' << 8) | 'C',       /* 0 */
    ('I' << 8) | ' ',       /* 1 */
    ('C' << 8) | '6',       /* 2 */
    ('6' << 8) | 'x',       /* 3 */
    (' ' << 8) | 'B',       /* 4 */
    ('o' << 8) | 'o',       /* 5 */
    ('t' << 8) | 'p',       /* 6 */
    (' ' << 8) | 'B',       /* 7 */
    ('o' << 8) | 'o',       /* 8 */
    ('t' << 8) |  0,        /* 9 */
    0, 0, 0, 0, 0, 0,       /* 10 - 15 */


    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,               /* Bootp client string is the mac address */


    #if (DEVICE==K2L)                        /* Lane enable mask */
        0xf,
    #else
        0xff,
    #endif

    /* sgmii control and advise ability */
    #if (SGMII==MASTER)
        0x21,                   
        0x9801,
    #elif (SGMII==SLAVE)
        0x1,
        0x1,
    #else
        0x20,
        0x9801
    #endif
    

    0, 0, 0, 0,                                 /* SGMII tx config, rx config */


    #if (SERDES_REF==f125)
        0, 12500,                               /* Aux Cfg */
    #else
        0, 15625,
    #endif

    0, 0,                                       /* Pkt PLL is configured at run time */

    0x8000,                                     /* Blob base */
    0x1000

};


/****************************************************************************************
 * Build time conversions
 ****************************************************************************************/

#define REF_IDX REF_CLK     /* direct map to index */

#if (DEVICE==K2L)
 #define PA_REF_IDX   REF_IDX

#else
 #define PA_REF_IDX   PA_CLK

#endif


/****************************************************************************************
 * System Definitions
 ****************************************************************************************/
#define VAL_EFUSE_BOOTROM  *((UINT32 *)0x02620c90)

#define DEVICE_SYS_PLL_NUM      0
#define DEVICE_ARM_PLL_NUM      4


#define DEVICE_LPSC_MODNUM_PA         7
#define DEVICE_LPSC_MODNUM_ETH        8

/* The reference clocks in MHz * 100 */
const unsigned int refsx100[] = { 5000, 6667, 8000, 10000, 15625, 25000, 32150, 12288 };


/* PA multipliers/dividers correspond to 50, 66.66, 80, 100, 156.25, 250, 312.5, 122.88 and 125 MHz */
const unsigned int paClkf[] =  { 41, 62, 104, 20, 93, 41, 46, 16, 83 };
const unsigned int paClkr[] =  {  0,  1,   3,  0,  6,  4,  6,  0,  4 };


#define DEVICE_REG_MACID1                       *((volatile unsigned int *)0x2620110)
#define DEVICE_REG_MACID2                       *((volatile unsigned int *)0x2620114)

#define PA_PLL_BASE   0x2620358

#if (DEVICE==K2L)

 #define DEVICE_FIELD_EFUSE_DEV_FREQ_MSB     25
 #define DEVICE_FIELD_EFUSE_DEV_FREQ_LSB     16

 #define DEVICE_FIELD_EFUSE_ARM_FREQ_MSB      9
 #define DEVICE_FIELD_EFUSE_ARM_FREQ_LSB      0

 #define MAX_LB                              10

 #define ARM_PLL_BASE  0x2620370

 #define BOOT_PARAM_TABLE_ADDR      0xc1d8500

 /* These tables are for use when the post divider value is 2 (true divider value = 2, register = 1) */
 const unsigned int SysClkr_postDiv2[7][8] = {
    {  0,  0,   0,   0,   3,   4,   7,    0 },   /* 800 MHz */
    {  0,  0,   0,   0,   4,   0,   4,    0 },   /* 1000 MHz */
    {  0,  0,   0,   0,   2,   4,   2,    0 },   /* 1200 MHz */
    {  0,  1,   3,   0,   3,   4,  10,    0 },   /* 1350 MHz */
    {  0,  0,   0,   0,   0,   4,   0,    0 },   /* 1400 MHz */
    {  0,  0,   1,   0,   4,   0,   4,    0 },   /* 1500 MHz */
 };

 const unsigned int SysClkf_postDiv2[7][8] = {
    { 31, 23,  19,  15,  40,  31,  40,   12 },   /* 800 MHz */
    { 39, 29,  24,  19,  63,   7,  31,   16 },   /* 1000 MHz */
    { 47, 35,  29,  23,  45,  47,  22,   19 },   /* 1200 MHz */
    { 53, 80, 134,  26,  68,  53,  94,   21 },   /* 1350 MHz */
    { 55, 41,  34,  27,  17,  55,   8,   22 },   /* 1400 MHz */
    { 59, 44,  74,  29,  95,  11,  47,   24 }    /* 1500 MHz */
 };

 const unsigned int ClkTblIdx[]= { 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 0, 0, };

 #define PA_BASE 0x26000000
#else

 #define DEVICE_FIELD_EFUSE_DEV_FREQ_MSB     27
 #define DEVICE_FIELD_EFUSE_DEV_FREQ_LSB     16

 #define MAX_LB                              12


 #define BOOT_PARAM_TABLE_ADDR      0xc1b0500

    
 /* These tables are for use when the post divider value is 2 (true divider value = 2, register = 1) */
 const unsigned int SysClkr_postDiv2[7][8] = {
    {  0,  0,   0,   0,   3,   4,   7,    0 },   /* 800 MHz */
    {  0,  1,   3,   0,   7,   4,  15,    5 },   /* 850 MHz */
    {  0,  0,   0,   0,   4,   0,   4,    3 },   /* 1000 MHz */
    {  0,  1,   3,   0,   0,   0,   0,    0 },   /* 1250 MHz */
    {  0,  1,   3,   0,   3,   4,  10,    0 },   /* 1350 MHz */
    {  0,  0,   0,   0,   0,   4,   0,    0 },   /* 1400 MHz */
    {  0,  0,   1,   0,   4,   0,   4,    0 },   /* 1500 MHz */
 };

 const unsigned int SysClkf_postDiv2[7][8] = {
    { 31, 23,  19,  15,  40,  31,  40,   12 },   /* 800 MHz */
    { 33, 50,  84,  16,  86,  33,  86,   82 },   /* 850 MHz */
    { 39, 29,  24,  19,  63,   7,  31,   64 },   /* 1000 MHz */
    { 49, 74, 124,  24,  15,   9,   7,   19 },   /* 1250 MHz */
    { 53, 80, 134,  26,  68,  53,  94,   21 },   /* 1350 MHz */
    { 55, 41,  34,  27,  17,  55,   8,   22 },   /* 1400 MHz */
    { 59, 44,  74,  29,  95,  11,  47,   24 }    /* 1500 MHz */
 };

 const unsigned int ClkTblIdx[]= { 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0 };

 #define PA_BASE 0x24000000
#endif


/********************************************************************************
 * Prototypes for ROM call tabled functions
 ********************************************************************************/
void romtConfigPll (unsigned int pllNum, 
                    unsigned int prediv, 
                    unsigned int mult, 
                    unsigned int postdiv, 
                    unsigned int sysFreqMhz, 
                    unsigned int coreFreqMhz);


void romtPscEnableModule (unsigned int modNum);

void romtReEntry ();


void romtDelay32 (unsigned int count);

/********************************************************************************
 * FUNCTION PURPOSE: Return the bit number where the left most bit appears
 ********************************************************************************
 * DESCRIPTION: An implementation of the lmbd command available for dsps
 ********************************************************************************/
UINT32 chipLmbd (UINT32 val, UINT32 target)
{
    UINT32 i;

    val = val & 1;

    for (i = 0; i < 32; i++)  
        if ( ((target >> (31-i)) & 1) == val)
            return (i);

    return (32);

}


/*********************************************************************************************************
 * FUNCTION PURPOSE: Configure and enable a pll residing in config space
 *********************************************************************************************************
 * DESCRIPTION: The PLL is unconditionally configured. 
 *********************************************************************************************************/
void hwCfgPllEnable (unsigned int base,        unsigned int prediv, 
                     unsigned int mult,        unsigned int postdiv, 
                     unsigned int chipFreqMhz, unsigned int pllFreqMhz, 
                     BOOL outsrc)
{
    UINT32 reg;
    UINT32 regb;
    UINT32 bwAdj;

    /* bwAdj is based only on the mult value */
    bwAdj = (mult >> 1) - 1;

    /* Multiplier / divider values are input as 1 less then the desired value */
    if (prediv > 0)
        prediv -= 1;

    if (mult > 0)
        mult -= 1;

    if (postdiv > 0)
        postdiv -= 1;

    reg =  DEVICE_REG32_R (base);
    regb = DEVICE_REG32_R (base + 4);

    /* Set ensat */
    regb = BOOT_SET_BITFIELD(regb, 1, 6, 6);
    DEVICE_REG32_W (base + 4, regb);

    /* Enable the bypass */
    reg = BOOT_SET_BITFIELD (reg, 1, 23, 23);   /* The value 1 enables the bypass */
    DEVICE_REG32_W (base, reg);


    /* Setup the PLL. Assert bypass */
    reg = BOOT_SET_BITFIELD (reg, prediv,          5,  0);
    reg = BOOT_SET_BITFIELD (reg, mult,           18,  6);
    reg = BOOT_SET_BITFIELD (reg, postdiv,        22, 19);
    reg = BOOT_SET_BITFIELD (reg, 1,              23, 23);   /* Bypass must be enabled */
    reg = BOOT_SET_BITFIELD (reg, (bwAdj & 0xff), 31, 24);

    DEVICE_REG32_W (base, reg);

    /* The 4 MS Bits of bwadj */
    regb = BOOT_SET_BITFIELD (regb, (bwAdj >> 8), 3, 0);

    /* Set bit 14 in register 1 to disable the PLL (assert reset) */
    regb = BOOT_SET_BITFIELD(regb, 1, 14, 14);
    DEVICE_REG32_W (base + 4, regb);

    /* Reset must be asserted for at least 5us. Give a huge amount of padding here to be safe
     * (the factor of 100) */
    romtDelay32 (5 * chipFreqMhz * 100);

    /* Clear the internal bypass if present */
    regb = BOOT_SET_BITFIELD(regb, 0, 15, 15);

    /* Clear bit 14 in register 1 to re-enable the pll */
    regb = BOOT_SET_BITFIELD(regb, 0, 14, 14);
    DEVICE_REG32_W (base + 4, regb);

    /* Need to wait 100,000 output PLL cycles before releasing bypass and setting 
     * up the clk output */
    romtDelay32 (chipFreqMhz * 100000 / pllFreqMhz);


    /* Disable the bypass */
    reg = BOOT_SET_BITFIELD (reg, 0, 23, 23);   /* The value 0 disables the bypass */
    DEVICE_REG32_W (base, reg);


    if (outsrc == TRUE)  {
        /* Enable the output source (set bit 13) */
        regb = BOOT_SET_BITFIELD(regb, 1, 13, 13);
        DEVICE_REG32_W (base + 4, regb);
    }

} /* hwCfgPllEnable */




/****************************************************************************************
 * FUNCTION PURPOSE: Configure the system PLL
 ****************************************************************************************
 * DESCRIPTION: The main PLL is setup based on the reference clock and e-fused system
 *              speed.
 ****************************************************************************************/
void setupSysPll (unsigned int sysFreqMhz, unsigned int coreFreqMhz)
{
    unsigned int freqBits, v;
    int lb;
    unsigned int idx;

    v = VAL_EFUSE_BOOTROM;

    freqBits = BOOT_READ_BITFIELD (v,
                                   DEVICE_FIELD_EFUSE_DEV_FREQ_MSB,
                                   DEVICE_FIELD_EFUSE_DEV_FREQ_LSB);


    lb = 32 - chipLmbd(1, freqBits);
    if (lb > MAX_LB)
        lb = MAX_LB;


    idx = ClkTblIdx[lb];


    romtConfigPll (DEVICE_SYS_PLL_NUM,                  /* PLL number      */
                   SysClkr_postDiv2[idx][REF_IDX] + 1,  /* Pre-divider     */
                   SysClkf_postDiv2[idx][REF_IDX] + 1,  /* multiplier      */
                   2,                                   /* Post divider    */
                   sysFreqMhz,                          /* System frequency */
                   coreFreqMhz);                        /* Core Frequency  */


}

/****************************************************************************************
 * FUNCTION PURPOSE: Estimate the system frequency after PLL enable
 ****************************************************************************************
 * DESCRIPTION: An estimate is made based on the ref clock and PLL setup
 ****************************************************************************************/
unsigned int getSystemFreqMhz(void)
{

    unsigned int freqBits, v;
    int lb;
    unsigned int idx;
    unsigned int mult, div;

    v = VAL_EFUSE_BOOTROM;

    freqBits = BOOT_READ_BITFIELD (v,
                                   DEVICE_FIELD_EFUSE_DEV_FREQ_MSB,
                                   DEVICE_FIELD_EFUSE_DEV_FREQ_LSB);


    lb = 32 - chipLmbd(1, freqBits);
    if (lb > MAX_LB)
        lb = MAX_LB;


    idx  = ClkTblIdx[lb];
    div  = (SysClkr_postDiv2[idx][REF_IDX] + 1) * 2; /* post div by 2 is used */
    mult = SysClkf_postDiv2[idx][REF_IDX] + 1;

    return ( (refsx100[REF_IDX] *  mult) / (100 * div) );

}


/****************************************************************************************
 * FUNCTION PURPOSE: Estimate the ARM core frequency after PLL enable
 ****************************************************************************************
 * DESCRIPTION: An estimate is made based on the ref clock and PLL setup
 ****************************************************************************************/
unsigned int getCoreFreqMhz (void)
{

 #if (DEVICE==K2L)

    unsigned int freqBits, v;
    int lb;
    unsigned int idx;
    unsigned int mult, div;

    v = VAL_EFUSE_BOOTROM;

    freqBits = BOOT_READ_BITFIELD (v,
                                   DEVICE_FIELD_EFUSE_ARM_FREQ_MSB,
                                   DEVICE_FIELD_EFUSE_ARM_FREQ_LSB);


    lb = 32 - chipLmbd(1, freqBits);
    if (lb > MAX_LB)
        lb = MAX_LB;


    idx  = ClkTblIdx[lb];
    div  = (SysClkr_postDiv2[idx][REF_IDX] + 1) * 2; /* post div by 2 is used */
    mult = SysClkf_postDiv2[idx][REF_IDX] + 1;

    return ( (refsx100[REF_IDX] *  mult) / (100 * div) );

 #else

   return (getSystemFreqMhz());

 #endif

}


/****************************************************************************************
 * FUNCTION PURPOSE: Setup the ARM PLL
 ****************************************************************************************
 * DESCRIPTION: K2L has a seperate ARM PLL
 ****************************************************************************************/
void setupArmPll (unsigned int coreFreqMhz)
{

 #if (DEVICE==K2L)

    unsigned int freqBits, v;
    int lb;
    unsigned int idx;

    v = VAL_EFUSE_BOOTROM;

    freqBits = BOOT_READ_BITFIELD (v,
                                   DEVICE_FIELD_EFUSE_ARM_FREQ_MSB,
                                   DEVICE_FIELD_EFUSE_ARM_FREQ_LSB);


    lb = 32 - chipLmbd(1, freqBits);
    if (lb > MAX_LB)
        lb = MAX_LB;


    idx = ClkTblIdx[lb];


    hwCfgPllEnable (ARM_PLL_BASE,                       /* PLL base        */
                   SysClkr_postDiv2[idx][REF_IDX] + 1,  /* Pre-divider     */
                   SysClkf_postDiv2[idx][REF_IDX] + 1,  /* multiplier      */
                   2,                                   /* post divider    */
                   coreFreqMhz,                         /* core speed      */
                   coreFreqMhz,                         /* pll output      */
                   FALSE );                             /* No outsrc       */

#endif

}


/****************************************************************************************
 * FUNCTION PURPOSE: Setup the PA PLL
 ****************************************************************************************
 * DESCRIPTION: K2L has a seperate ARM PLL
 ****************************************************************************************/
void setupPaPll (unsigned int coreFreqMhz)
{

    hwCfgPllEnable (PA_PLL_BASE,                        /* PLL base        */
                   paClkr[PA_REF_IDX] + 1,              /* Pre-divider     */
                   paClkf[PA_REF_IDX] + 1,              /* multiplier      */
                   2,                                   /* post divider    */
                   coreFreqMhz,                         /* core speed      */
                   1050,                                /* pll output      */
                   TRUE );                              /* No outsrc       */

}


/****************************************************************************************
 * FUNCTION PURPOSE: Power up the NETCP subsystem
 ****************************************************************************************
 * DESCRIPTION: The NetCP and switch are powered up
 ****************************************************************************************/
void powerUpPa (void)
{
    romtPscEnableModule (DEVICE_LPSC_MODNUM_PA);
    romtPscEnableModule (DEVICE_LPSC_MODNUM_ETH);

}

/****************************************************************************************
 * FUNCTION PURPOSE: Execute the ROM code bug fix
 ****************************************************************************************
 * DESCRIPTION: The PDSP registers are cleared. The splitter combiner is initialized
 *              to match the boot rom settings, although not really required.
 ****************************************************************************************/
void romBugFix (void)
{

    memset ((unsigned int *)(PA_BASE+0x408400), 0, 32 * sizeof(unsigned int));  /* PDSP 0 */
    memset ((unsigned int *)(PA_BASE+0x418400), 0, 32 * sizeof(unsigned int));  /* PDSP 0 */

    *((unsigned int *)(PA_BASE+0x409814)) = 0x10;
    *((unsigned int *)(PA_BASE+0x409820)) = 0x4000;
    *((unsigned int *)(PA_BASE+0x409824)) = 0xfffc0000;
    *((unsigned int *)(PA_BASE+0x409810)) = 0x80000600;


}


/**********************************************************************************************
 * FUNCTION PURPOSE: Convert a 4 bit value to a character
 **********************************************************************************************
 * DESCRIPTION: A simple conversion
 **********************************************************************************************/
UINT8 toChar (UINT8 v)
{
    if (v < 10)
        return (v + '0');

    return ((v - 10) + 'a');

}


/**********************************************************************************************
 * FUNCTION PURPOSE: Convert a byte into 2 characters packed into a 16 bit value
 **********************************************************************************************
 * DESCRIPTION: A simple utility
 **********************************************************************************************/
UINT16 byte2chars (UINT8 v)
{
    UINT8  vh, vl;
    UINT16 ret;

    vh = (v >> 4) & 0xf;
    vh = toChar (vh);

    vl = (v >> 0) & 0xf;
    vl = toChar (vl);

    ret = (vh << 8) | vl;

    return (ret);

} /* byte2chars */

/**********************************************************************************************
 * FUNCTION PURPOSE: Pack a 32 bit value into a 16 bit packed string representation
 **********************************************************************************************
 * DESCRIPTION: The 32 bit value is converted to 8 bytes packed into 4 16 bit words. The
 *              sprintf function could be used, but that function is huge and what is needed
 *              here is very small.
 **********************************************************************************************/
void packString (UINT16 *d, UINT32 v)
{
    UINT32 i;

    for (i = 0; i < 4; i++) 
        d[i] = byte2chars ((v >> (24 - (i * 8))) & 0xff);

} /* packString */
        

/**********************************************************************************************
 * FUNCTION PURPOSE: Return the client ID string used for the bootp request
 **********************************************************************************************
 * DESCRIPTION: The string is created from the e-fuse mac address
 **********************************************************************************************/
void defaultBootpIdString (UINT16 *dst, UINT32 sizeUint16)
{
    UINT32 idreg;
    UINT32 i;
    UINT16 tmp[8];

    memset (tmp, 0, sizeof(tmp));

    idreg = ((DEVICE_REG_MACID2 & 0xffff) << 16);
    packString (tmp, idreg);

    idreg = DEVICE_REG_MACID1;
    packString (&tmp[2], idreg);

    for (i = 0; i < sizeof(tmp)/sizeof(UINT16); i++)
        dst[i] = tmp[i];

} /* defaultBootpIdString */


/****************************************************************************************
 * FUNCTION PURPOSE: Install the new parameter table
 ****************************************************************************************
 * DESCRIPTION: The new boot parameter table is installed
 ****************************************************************************************/
void copyParamTable (unsigned int sysFreqMhz, unsigned int coreFreqMhz)
{
    unsigned int mac1, mac2; 

    BOOT_PARAMS_BOOTP_ETHERNET_T *bparams = (BOOT_PARAMS_BOOTP_ETHERNET_T *)BOOT_PARAM_TABLE_ADDR;

    memcpy (bparams, &myParams, sizeof (BOOT_PARAMS_BOOTP_ETHERNET_T));

    /* Update the parameter table */
    bparams->sysFreqMhz  = sysFreqMhz;
    bparams->coreFreqMhz = coreFreqMhz;

    mac1 = DEVICE_REG_MACID1;
    mac2 = DEVICE_REG_MACID2;

    bparams->mac_addr_h = mac2 & 0xffff;
    bparams->mac_addr_m = (mac1 >> 16) & 0xffff;
    bparams->mac_addr_l = mac1 & 0xffff;

    defaultBootpIdString (bparams->clientIdString, CLIENT_ID_STRING_SIZE_UINT16);

}

#if (PLATFORM==EVM) /* This code is needed for use on EVM for PHY fix based on errata */

/* EVM PHY Workaround */

 /**************************************
  ** MDIO Registers / Masks / Values ***
  **************************************/
 #define MDIO_VERSION_REG                            (*(unsigned int *) (PA_BASE + 0x00200F00 + 0x00))
 /* mdio_user_access_reg */
 #define MDIO_USER_ACCESS_REG                        (*(unsigned int *) (PA_BASE + 0x00200F00 + 0x80))
 #define MDIO_USER_CONTROL_REG                       (*(unsigned int *) (PA_BASE + 0x00200F00 + 0x04))
 #define MDIO_USER_INT_MASK_REG                      (*(unsigned int *) (PA_BASE + 0x00200F00 + 0x28))
 
 /* shift and mask for MDIO_USER_ACCESS_REG */
 #define CSL_MDIO_USER_ACCESS_REG_DATA_MASK          (0x0000FFFF)
 #define CSL_MDIO_USER_ACCESS_REG_DATA_SHIFT         (0x00000000)
 #define CSL_MDIO_USER_ACCESS_REG_DATA_RESETVAL      (0x00000000)
 
 #define CSL_MDIO_USER_ACCESS_REG_PHYADR_MASK        (0x001F0000)
 #define CSL_MDIO_USER_ACCESS_REG_PHYADR_SHIFT       (0x00000010)
 #define CSL_MDIO_USER_ACCESS_REG_PHYADR_RESETVAL    (0x00000000)
 
 #define CSL_MDIO_USER_ACCESS_REG_REGADR_MASK        (0x03E00000)
 #define CSL_MDIO_USER_ACCESS_REG_REGADR_SHIFT       (0x00000015)
 #define CSL_MDIO_USER_ACCESS_REG_REGADR_RESETVAL    (0x00000000)
 
 #define CSL_MDIO_USER_ACCESS_REG_ACK_MASK           (0x20000000)
 #define CSL_MDIO_USER_ACCESS_REG_ACK_SHIFT          (0x0000001D)
 #define CSL_MDIO_USER_ACCESS_REG_ACK_RESETVAL       (0x00000000)
 
 #define CSL_MDIO_USER_ACCESS_REG_WRITE_MASK         (0x40000000)
 #define CSL_MDIO_USER_ACCESS_REG_WRITE_SHIFT        (0x0000001E)
 #define CSL_MDIO_USER_ACCESS_REG_WRITE_RESETVAL     (0x00000000)
 
 #define CSL_MDIO_USER_ACCESS_REG_GO_MASK            (0x80000000)
 #define CSL_MDIO_USER_ACCESS_REG_GO_SHIFT           (0x0000001F)
 #define CSL_MDIO_USER_ACCESS_REG_GO_RESETVAL        (0x00000000)
 
 /* the Field MaKe macro */
 #define CSL_FMK(SHIFT, MASK, val)       (((val) << SHIFT) & MASK)
 
 /* the Field EXTract macro */
 #define CSL_FEXT(reg, SHIFT, MASK)      (((reg) & MASK) >> SHIFT)
 
 /****************************************************************************************
  * FUNCTION PURPOSE: Write Value to MDIO Register
  ****************************************************************************************
  * DESCRIPTION: Writes values to MDIO registers as part of the PHY fix
  ****************************************************************************************/
 phy_hwwrite(UINT16 phy_addr, UINT16 addr, UINT16 val)
 {
     UINT32 retVal=1;
     volatile UINT32 i, delay=2000;
     
     MDIO_USER_ACCESS_REG   =  CSL_FMK (CSL_MDIO_USER_ACCESS_REG_GO_SHIFT, CSL_MDIO_USER_ACCESS_REG_GO_MASK, 1) |
             CSL_FMK (CSL_MDIO_USER_ACCESS_REG_WRITE_SHIFT, CSL_MDIO_USER_ACCESS_REG_WRITE_MASK, 1) |
             CSL_FMK (CSL_MDIO_USER_ACCESS_REG_REGADR_SHIFT, CSL_MDIO_USER_ACCESS_REG_REGADR_MASK, addr) |
             CSL_FMK (CSL_MDIO_USER_ACCESS_REG_PHYADR_SHIFT, CSL_MDIO_USER_ACCESS_REG_PHYADR_MASK, phy_addr) |
             CSL_FMK (CSL_MDIO_USER_ACCESS_REG_DATA_SHIFT, CSL_MDIO_USER_ACCESS_REG_DATA_MASK, val);
 
     
     while(1)
     {
         retVal=CSL_FEXT(MDIO_USER_ACCESS_REG, CSL_MDIO_USER_ACCESS_REG_GO_SHIFT, CSL_MDIO_USER_ACCESS_REG_GO_MASK);
         if(retVal == 0)
             break;
 
         for(i = 0; i < delay; i++); // this delay is much more than required   
 
     }
 }
 
 
 /****************************************************************************************
  * FUNCTION PURPOSE: Fix Marvell PHY based on errata
  ****************************************************************************************
  * DESCRIPTION: Fixes an issue with Marvell PHY
  ****************************************************************************************/
 setup_Marvell_Phy(UINT16 phyaddr)
 {
     volatile unsigned short i, j;
 
     MDIO_USER_CONTROL_REG = (1 << 30) | 0xFA;
     MDIO_USER_INT_MASK_REG = 0x00;
 
     /* Register settings as per RN section 3.1 */
     phy_hwwrite(phyaddr, 22, 0x00ff);
     phy_hwwrite(phyaddr, 17, 0x214B);
     phy_hwwrite(phyaddr, 16, 0x2144);
     phy_hwwrite(phyaddr, 17, 0x0C28);
     phy_hwwrite(phyaddr, 16, 0x2146);
     phy_hwwrite(phyaddr, 17, 0xB233);
     phy_hwwrite(phyaddr, 16, 0x214D);
     phy_hwwrite(phyaddr, 17, 0xCC0C);
     phy_hwwrite(phyaddr, 16, 0x2159);
     phy_hwwrite(phyaddr, 22, 0x0000);
     phy_hwwrite(phyaddr, 9, 0x1800); //Set master
 
     /* Set SGMII to Copper mode Page 18, Reg 20.2:0 = 1  */
     phy_hwwrite(phyaddr, 22, 18);
     phy_hwwrite(phyaddr, 20, 0x1);
     /* PHY Reset Page 18, Reg 20.15 = 1  */
     phy_hwwrite(phyaddr, 20, 0x8201);
     phy_hwwrite(phyaddr, 22, 00);
 
     for (i = 0; i < 10000; i++) { 
         for (j = 0; j < 10000; j++);
     }
 }
#endif

/* End of EVM PHY Workaround */


#pragma DATA_SECTION(ddr_config, ".ddrConfig")
BOOT_EMIF4V_TBL_T ddr_config;

/****************************************************************************************
 * FUNCTION PURPOSE: Configure the system for ROM ethernet boot
 ****************************************************************************************
 * DESCRIPTION: The PA subystem is powered up, the cluster 0 PDSP registers are
 *              initialized, and the system is reconfigured for boot ROM restart
 ****************************************************************************************/
extern unsigned int romtMainEmif4Cfg;

void main (void)
{
    unsigned int sysFreqMhz, coreFreqMhz;

    /* Enable the MMU. It will speed up the rest of the code execution */
    hwArmMmuEnable();

    /* Get an estimate of the system frequency after PLL enable */
    sysFreqMhz  = getSystemFreqMhz();
    coreFreqMhz = getCoreFreqMhz ();

    /* Configure the system PLL  */
    setupSysPll (sysFreqMhz, coreFreqMhz);

    /* Configure the ARM PLL (only done for K2L) */
    setupArmPll (coreFreqMhz);

    /* Power up the NETCP sub-system */
    powerUpPa();

    /* Setup the PA PLL */
    setupPaPll(coreFreqMhz);

    /* Do the ROM bug fix */
    romBugFix();

    /* Copy the new boot parameter table into place */
    copyParamTable(sysFreqMhz, coreFreqMhz);
    
    /* Configure DDR3 for use */
    void (*fcn)(void);
    memcpy (&ddr_config, &emif4vCfg, sizeof(emif4vCfg));
    fcn = (void (*)(void))&romtMainEmif4Cfg;
    (*fcn)();

#if (PLATFORM==EVM)
    setup_Marvell_Phy(1);
#endif

    /* Re-execute the ROM boot loader */
    romtReEntry();

}
