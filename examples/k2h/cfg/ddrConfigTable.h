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
            
    1,              /* pllPrediv,  Not sure yet */          
    16,             /* pllMult, Not sure yet */ 
    8,              /* pllPostDiv, Not sure yet */  
     
    0x62001462,     /* sdRamConfig, From the gel script */         
    0x00000C34,     /* sdRamRefreshCtl, From the gel script */        
    0x0a384c23,     /* sdRamTiming1, From the gel script */   
    0x00001CA5,     /* sdRamTiming2, From the gel script */   
    0x21ADFF32,     /* sdRamTiming3, From the gel script */   
    0x533F03FF,     /* sdRamTiming4, From the gel script */   
    0,              /* powerManageCtl, Not used in the gel script */       
    0,              /* vbusmCfg, Not used in the gel script */             
    0,              /* vbusmCfgVal1, Not used in the gel script */         
    0,              /* vbusmCfgVal2, Not used in the gel script */         
    0,              /* iODFTTestLogic, Not used in the gel script */       
    0,              /* performCountCfg, Not used in the gel script */      
    0,              /*performCountMstRegSel, Not used in the gel script */
    0xf0073200, //0x70073200,     /* zqConfig, From the gel script */       
	
    0,              /* priClassSvceMap, Not used in the gel script */      
    0,              /* mstId2ClsSvce1Map, Not used in the gel script */    
    0,              /* mstId2ClsSvce2Map, Not used in the gel script */    
    0,              /* eccCtl, Not used in the gel script */               
    0,              /* eccRange1, Not used in the gel script */            
    0,              /* eccRange2, Not used in the gel script */            
    0,              /*rdWrtExcThresh, Not used in the gel script */       
    0x00000F81,     /* PIR , from gel. different from k2e */
    0,              /* PGCR0 */
    0x0280C485,//0x0280C4A5,     /* PGCR1 may need to be changed. gel comment says 0x280C485*/
    0x00F03D09,     /* PGCR2 */
    0,              /* PGSR0 */
    0,              /* PGSR1 */
    0x42C21590,     /* PTR0 */
    0xD05612C0,     /* PTR1 */
    0,              /* PTR2 */
    0x06C30D40,     /* PTR3 */
    0x06413880,     /* PTR4 */
    (1 <<10) | (1 << 27) | (1 << 29) | 0xb, /* DCR */
	//0x2800040B,     /* DCR may need to be changed. gel comment says 0x280C485. gel uses bit manipulation*/
    0x50CF6644,     /* DTPR0 */
    0x12834180,     /* DTPR1 */
    0x50022A00,     /* DTPR2 */
    0x00001420,     /* MR0 */
    0x00000006,     /* MR1 */
    0, //0x00000040,     /* MR2 may need to be changed. gel has this commented out to leave it at default  */
    0x730035c7,//0x710035C7,     /* DTCR */
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
    0x0000005D,     /* ZQ0CR1 */
    0x0000005B,     /* ZQ1CR1 */
    0x0000005B,     /* ZQ2CR1 */
    
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0      /* LSW values, none used */
};


// const BOOT_EMIF4V_TBL_T  emif4vCfg =  {

    // 0,
    
  // 0,

    
    // 0,              /* Config select LSW  */
            
    // 0,              /* pllPrediv,  Not sure yet */          
    // 0,             /* pllMult, Not sure yet */ 
    // 0,              /* pllPostDiv, Not sure yet */  
     
    // 0,     /* sdRamConfig, From the gel script */         
    // 0,     /* sdRamRefreshCtl, From the gel script */        
    // 0,     /* sdRamTiming1, From the gel script */   
    // 0,     /* sdRamTiming2, From the gel script */   
    // 0,     /* sdRamTiming3, From the gel script */   
    // 0,     /* sdRamTiming4, From the gel script */   
    // 0,              /* powerManageCtl, Not used in the gel script */       
    // 0,              /* vbusmCfg, Not used in the gel script */             
    // 0,              /* vbusmCfgVal1, Not used in the gel script */         
    // 0,              /* vbusmCfgVal2, Not used in the gel script */         
    // 0,              /* iODFTTestLogic, Not used in the gel script */       
    // 0,              /* performCountCfg, Not used in the gel script */      
    // 0,              /*performCountMstRegSel, Not used in the gel script */
    // 0,     /* zqConfig, From the gel script */          
    // 0,              /* priClassSvceMap, Not used in the gel script */      
    // 0,              /* mstId2ClsSvce1Map, Not used in the gel script */    
    // 0,              /* mstId2ClsSvce2Map, Not used in the gel script */    
    // 0,              /* eccCtl, Not used in the gel script */               
    // 0,              /* eccRange1, Not used in the gel script */            
    // 0,              /* eccRange2, Not used in the gel script */            
    // 0,              /*rdWrtExcThresh, Not used in the gel script */       
    // 0,     /* PIR , from gel. different from k2e */
    // 0,              /* PGCR0 */
    // 0,     /* PGCR1 may need to be changed. gel comment says 0x280C485*/
    // 0,     /* PGCR2 */
    // 0,              /* PGSR0 */
    // 0,              /* PGSR1 */
    // 0,     /* PTR0 */
    // 0,     /* PTR1 */
    // 0,              /* PTR2 */
    // 0,     /* PTR3 */
    // 0,     /* PTR4 */
    // 0,     /* DCR may need to be changed. gel comment says 0x280C485. gel uses bit manipulation*/
    // 0,     /* DTPR0 */
    // 0,     /* DTPR1 */
    // 0,     /* DTPR2 */
    // 0,     /* MR0 */
    // 0,     /* MR1 */
    // 0,     /* MR2 may need to be changed. gel has this commented out to leave it at default  */
    // 0,     /* DTCR */
    // 0,              /* DX0GCR */
    // 0,              /* DX1GCR */
    // 0,              /* DX2GCR */
    // 0,              /* DX3GCR */
    // 0,              /* DX4GCR */
    // 0,              /* DX5GCR */
    // 0,              /* DX6GCR */
    // 0,              /* DX7GCR */
    // 0,              /* DX8GCR */
    // 0,     /* PLLCR */
    // 0,     /* ZQ0CR1 */
    // 0,     /* ZQ1CR1 */
    // 0,     /* ZQ2CR1 */
    
    // 0, 0, 0, 0, 0, 0, 0, 0,
    // 0, 0, 0, 0, 0, 0, 0, 0,
    // 0, 0, 0, 0, 0, 0, 0, 0,
    // 0, 0, 0, 0, 0, 0, 0, 0      /* LSW values, none used */
// };

