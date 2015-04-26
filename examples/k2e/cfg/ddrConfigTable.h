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
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


const BOOT_EMIF4V_TBL_T  emif4vCfg =  {

    BOOT_EMIF4V_ENABLE_MSW_pllCtl           | \
    BOOT_EMIF4V_ENABLE_MSW_sdRamConfig      | \
    BOOT_EMIF4V_ENABLE_MSW_sdRamRefreshCtl  | \
    BOOT_EMIF4V_ENABLE_MSW_sdRamTiming1     | \
    BOOT_EMIF4V_ENABLE_MSW_sdRamTiming2     | \
    BOOT_EMIF4V_ENABLE_MSW_sdRamTiming3     | \
    BOOT_EMIF4V_ENABLE_MSW_sdRamTiming4     | \
    BOOT_EMIF4V_ENABLE_MSW_zqConfig,            
    
    BOOT_EMIF_ENABLE_SLSW_config0       | \
    BOOT_EMIF_ENABLE_SLSW_config2       | \
    BOOT_EMIF_ENABLE_SLSW_config3       | \
    BOOT_EMIF_ENABLE_SLSW_config6       | \
    BOOT_EMIF_ENABLE_SLSW_config7       | \
    BOOT_EMIF_ENABLE_SLSW_config9       | \
    BOOT_EMIF_ENABLE_SLSW_config10      | \
    BOOT_EMIF_ENABLE_SLSW_config11      | \
    BOOT_EMIF_ENABLE_SLSW_config12      | \
    BOOT_EMIF_ENABLE_SLSW_config13      | \
    BOOT_EMIF_ENABLE_SLSW_config14      | \
    BOOT_EMIF_ENABLE_SLSW_config15      | \
    BOOT_EMIF_ENABLE_SLSW_config16      | \
    BOOT_EMIF_ENABLE_SLSW_config18      | \
    BOOT_EMIF_ENABLE_SLSW_config28      | \
    BOOT_EMIF_ENABLE_SLSW_config29      | \
    BOOT_EMIF_ENABLE_SLSW_config30      | \
    BOOT_EMIF_ENABLE_SLSW_config31,

    
    0,              /* Config select LSW  */
            
    0,              /* pllPrediv,  Not sure yet */          
    4,              /* pllMult, Not sure yet */ 
    2,              /* pllPostDiv, Not sure yet */  
     
    0x62001462,     /* sdRamConfig, From the gel script */         
    0x00000C34,     /* sdRamRefreshCtl, From the gel script */        
    0x0A385022,     /* sdRamTiming1, From the gel script */   
    0x00001CA5,     /* sdRamTiming2, From the gel script */   
    0x210DFF22,     /* sdRamTiming3, From the gel script */   
    0x533F03FF,     /* sdRamTiming4, From the gel script */   
    0,              /* powerManageCtl, Not used in the gel script */       
    0,              /* vbusmCfg, Not used in the gel script */             
    0,              /* vbusmCfgVal1, Not used in the gel script */         
    0,              /* vbusmCfgVal2, Not used in the gel script */         
    0,              /* iODFTTestLogic, Not used in the gel script */       
    0,              /* performCountCfg, Not used in the gel script */      
    0,              /*performCountMstRegSel, Not used in the gel script */
    0x70073200,     /* zqConfig, From the gel script */          
    0,              /* priClassSvceMap, Not used in the gel script */      
    0,              /* mstId2ClsSvce1Map, Not used in the gel script */    
    0,              /* mstId2ClsSvce2Map, Not used in the gel script */    
    0,              /* eccCtl, Not used in the gel script */               
    0,              /* eccRange1, Not used in the gel script */            
    0,              /* eccRange2, Not used in the gel script */            
    0,              /*rdWrtExcThresh, Not used in the gel script */       
    0x0000FF81,     /* PIR */
    0,              /* PGCR0 */
    0x0280C4A5,     /* PGCR1 */
    0x00F03D09,     /* PGCR2 */
    0,              /* PGSR0 */
    0,              /* PGSR1 */
    0x42C21590,     /* PTR0 */
    0xCFC712B3,     /* PTR1 */
    0,              /* PTR2 */
    0x04430D40,     /* PTR3 */
    0x06413880,     /* PTR4 */
    0x2800040B,     /* DCR */
    0x008F6633,     /* DTPR0 */
    0x12820180,     /* DTPR1 */
    0x50022A00,     /* DTPR2 */
    0x00001620,     /* MR0 */
    0x00000006,     /* MR1 */
    0x00000040,     /* MR2 */
    0x710035C7,     /* DTCR */
    0,              /* DX0GCR */
    0,              /* DX1GCR */
    0,              /* DX2GCR */
    0,              /* DX3GCR */
    0,              /* DX4GCR */
    0,              /* DX5GCR */
    0,              /* DX6GCR */
    0,              /* DX7GCR */
    0,              /* DX8GCR */
    0x000DC000,     /* PLLCR */
    0x0000007B,     /* ZQ0CR1 */
    0x0000007B,     /* ZQ1CR1 */
    0x0000007B,     /* ZQ2CR1 */
    
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0      /* LSW values, none used */
};

