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


#include "tiboot.h"


#ifdef SPI

#define SYS_PLL_CONFIG					0x40290802
#define SEC_PLL_CONFIG					0x00000000
#define STAGE_2_BRANCH_ADDRESS			0x00001000

const BOOT_PARAMS_SPI_T params = {
	
	sizeof(BOOT_PARAMS_SPI_T),					/* length */
	0,											/* checksum */
	50,											/* boot_mode */
	0,											/* portNum (used to be 1) */
	(SYS_PLL_CONFIG >> 16) & 0xffff,			/* CPU PLL configuration, MSW */
	(SYS_PLL_CONFIG & 0xffff),     				/* CPU PLL configuration, LSW */
												
	(SEC_PLL_CONFIG >> 16) & 0xffff,			/* CPU PLL configuration, MSW  */
	(SEC_PLL_CONFIG & 0xffff),      			/* CPU PLL configuration, LSW  */
												
	0x04E2,										/* System clock frequency, MHz */ 
	0x04E2,										/* Core clock frequency, MHz   */ 
												
	1,											/* True if the core is the boot master */
													
	BOOT_PARAMS_SPI_OPTIONS_GPHDR,				/* Options */
												/*
												* SPI Specific Options
												* Bit 01-00: BT:                                      
												*            00 - Boot Parameter Mode                            
												*            01 - Boot Table Mode                     
												*            10 - Boot Config mode
												*            11 - GP header blob
												* Other bits:  Reserved 
												*/ 
	24,											/* 16 or 24 are the only valid values */
	0x0008,										/* 4 or 5 pins are the only valid values */
	0xFFFE,										/* only values 0b10 (cs0 low) or 0b01 (cs1 low) are valid 0xE = 1110 = CS0 (0xB = 1011 = CS2) */
	0,											/* Clock phase/polarity. These are the standard SPI modes 0-3 */
	1,											/* Setup time between chip select assert and the transaction */
													
	5,											/* The SPI bus frequency in units of 100 kHz */
											
	(STAGE_2_BRANCH_ADDRESS >> 16) & 0xffff,	/* The base address to read from the SPI, upper 16 bits */
	(STAGE_2_BRANCH_ADDRESS & 0xffff),      	/* The base address to read from the SPI, lower 16 bits */
											
	0x0000,										/* The next chip select to use if in boot config mode, when the config is complete */
	0x0000,										/* The next read address to use if in boot config mode */
	0x0000,										/* The next read address to use if in boot config mode */
             
};    

#endif

#ifdef I2C

#define SYS_PLL_CONFIG					0x40290802
#define SEC_PLL_CONFIG					0x00000000

const BOOT_PARAMS_I2C_T params = {
	
	sizeof(BOOT_PARAMS_I2C_T),					/* length */
	0,											/* checksum */
	40,											/* boot_mode */
	0,											/* portNum */
	(SYS_PLL_CONFIG >> 16) & 0xffff,			/* CPU PLL configuration, MSW */
	(SYS_PLL_CONFIG & 0xffff),     				/* CPU PLL configuration, LSW */
												
	(SEC_PLL_CONFIG >> 16) & 0xffff,			/* CPU PLL configuration, MSW  */
	(SEC_PLL_CONFIG & 0xffff),      			/* CPU PLL configuration, LSW  */
												
	0x04E2,										/* System clock frequency, MHz */ 
	0x04E2,										/* Core clock frequency, MHz   */ 
												
	1,											/* True if the core is the boot master */
													
	BOOT_PARAMS_I2C_OPTIONS_GP,					/* Options */
												/*
												* I2C Specific Options
												* Bit 02-00: BT:                                     
												*			000 - Boot Parameter Mode                           
												*			001 - Boot Table Mode                    
												*			010 - Boot Config mode
												*			011 - GP header Mode
												*			100 - Slave receive options
												* Other bits:  Reserved
												*/     
    0x2000,			          					/* 16-bit device address (low) */
    0x50,      									/* 16-bit extended device address (high) 
												* set to zero if not used
												* Note: some I2C device requires 32-bit 
												* address
												*/ 
    0x11,      									/* Multi device master write boot ID */
    0x10,         								/* This parts I2C address            */
    250,  										/* Desired I2C clock frequency, kHz  */
    0x0,     									/* Used only for the boot config mode.         */
    0x0, 										/* Copied into dev_addr* after config complete */
    0x200,     									/* Rough number of cycles delay between address write
												* and read to the i2c eeprom */
};    


#endif



#ifdef UART

#define SYS_PLL_CONFIG					0x40190102
#define SEC_PLL_CONFIG					0x00000000

#define SYS_CLK_FRQ						 0x04E2 
#define CORE_CLK_FRQ					 0x04E2

const BOOT_PARAMS_UART_T params = {
	
	sizeof(BOOT_PARAMS_UART_T),			/* length (should be 0x32 for K2K EVM) 0x36 for K2E/K2L */
	0,									/* checksum */
	0x6E,								/* boot_mode */
	0,									/* portNum */
	(SYS_PLL_CONFIG >> 16) & 0xffff,	/* CPU PLL configuration, MSW */
	(SYS_PLL_CONFIG & 0xffff),			/* CPU PLL configuration, LSW */
	(SEC_PLL_CONFIG >> 16) & 0xffff,	/* CPU PLL configuration, MSW  */
	(SEC_PLL_CONFIG & 0xffff),			/* CPU PLL configuration, LSW  */
	SYS_CLK_FRQ,						/* System clock frequency, MHz */
	CORE_CLK_FRQ,						/* Core clock frequency, MHz   */
	1,									/* True if the core is the boot master */
	0,									/* Options */
	BOOT_PARAMS_UART_DATA_FORMAT_BLOB,	/* Boot Data Format (Blob or Boot Table) */
	BOOT_PARAMS_UART_PROTOCOL_XMODEM,	/* Transfer Protocol */
	0xA,								/* Number of nacks to send at start before giving up */
	0xA,								/* Max number of consecutive receive errors */
	0x3,								/* Number of seconds for a nack timeout */
	2,									/* Inter-character timeout, milli-seconds */
	8,									/* Number of data bits, currently only 8 supported */
	BOOT_PARAMS_UART_PARITY_NONE,		/* Parity */
	2,									/* Number of stop bits x2. Valid values are 2, 3, and 4 for 1, 1.5 and 2 stop bits */
	0x10,								/* Valid values are 13 and 16 times oversampling */
	BOOT_PARAMS_FLOW_CONTROL_NONE,		/* Flow Control (None or RTS CTS) */
	0x0001,								/* Baud rate, MSW 0x0001, 0x0011, 0x0011, 0x0006*/
	0xC200,								/* Baud rate, LSW 0xC200, 0xF396, 0xA5A3, 0xE75A*/
	0x8000,								/* Image destination, msw, applies only for blob data type */
	0x1000,								/* Image destination, lsw */
};

#endif