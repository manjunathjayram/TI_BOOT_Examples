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

#####################################################
Release Notes:
#####################################################

Product Release: 1.00.00.00
Publication date: 4/15/2015

######################################################
Overview
######################################################
This document provides the release information for the latest Keystone II boot examples package
which is used to demonstrate creation and running boot images for Keystone II family devices for 
different boot media.

The boot examples package includes:
*   Source and binaries for Boot utilties
*   Source code for single and multistage boot
*   KeystoneII BootExamples User guide.


== Software Features ==
* Boot Utilities to create and format boot images
* Examples that demonstrate booting K2H and K2E devices from SPI, I2C, UART, Ethernet and NAND. Examples also demonstrate the following features of the BootROM
** Single and Multi-Stage booting.
** Using Boot Parameter tables to speed up booting from a boot media.
** Using Boot Configuration tables to initialize DDR.
* Examples to demonstrate formatting uboot for above mentioned boot modes.

##########################################################
Software Dependencies
##########################################################
*  MCSDK 3.x
*  MinGW with msys and make tools installed for Windows OR  Linux machine with Ubuntu 12.04LTS with wine utility.
*  TI ARM compiler (Typically packaged with [http://processors.wiki.ti.com/index.php/Download_CCS Code composer Studio])

############################################################
Supported Hardware 
############################################################
* K2H EVM rev 1.1 and later 
* K2E EVMs rev 1.0.2.0 and later

###########################################################
New Features added
###########################################################

********************
Release 1.00.00.00
********************
•	Added support for K2H EVM 
•	Added single stage boot examples for both K2E and K2H devices. 
•	Include source for the Boot utilities. (Fix for IR : SDOCM00114650)
•	Added build files to create uboot binaries for i2c, spi, nand, eth and uart boot media. 
•	Modified the directory structure for easy integration for future targets.
•	Updated documentation to walk users through building, flashing and running Boot loader examples. 

********************
Release 00.00.00.99
******************** 
* Initial Release with multistage boot examples for K2E.
* Ethernet boot work around code for the EVM.

########################################
Resolved Incident Reports
########################################

SDOCM00114650: [S2-Major] : Include source for boot utilities and add support for Linux build.


########################################
Licensing
########################################
Please refer to the software Manifest document for details.

#######################################
Installation Instructions.
#######################################
Please refer to the Keystone II boot Examples User guide for details.

########################################################################################
Directory Structure:
########################################################################################
The following directory struct
*docs - directory contains ReadMe documents and the software manifest for the package. 
*common - directory contains source and header files for helper functions that are used by the examples to configure MMU, CACHE, PLLs, UART and to set user defined entry point for their applications. 
*include - directory contains all boot header files that applies to all the devices in the Keystone family.
*examples - directory contains source for single stage and multi stage boot examples for different boot modes. 
**k2e - directory contains boot examples for K2E devices.
***build - directory contains linker command files that specify the memory configuration for each examples
***cfg - directory contains header files that contain ddr configuration tables, boot parameter tables for different boot modes and tiboot.h file defined in the BootROM. 
***[peripheral] - directory contains boot example code for each peripheral (eth, i2c,nand,spi, uart)
**** [example type] - directory contains single stage/mulitstage example binaries. 
***uboot - directory contains build files required to create uboot binaries for different boot media.
**k2h - directory contains boot examples for K2H devices.
***build - directory contains linker command files that specify the memory configuration for each examples
***cfg - directory contains header files that contain ddr configuration tables, boot parameter tables for different boot modes and tiboot.h file defined in the BootROM. 
***[peripheral] - directory contains boot example code for each peripheral (eth, i2c,nand,spi, uart)
**** [example type] - directory contains single stage/mulitstage example binaries. 
***uboot - directory contains build files required to create uboot binaries for different boot media.
**src - directory contains source for sample applications that demonstrate single stage and multistage booting.
***singleStage: directory contains source files for Single stage boot example
***mulitStage: directory contains source files for two stage boot example
*utils - directory contains the utilities for building boot images
**byteswap : directory contains the source and binaries for byteswapccs utility.
**btoccs : directory contains source and binaries for b2ccs,catccs, ccs2bin utilities
**ccsutil: directory contains source and binaries for ccsAddGphdr,ccsAddGptlr,ccspad utilities


########################################################################################
Building the Examples:
########################################################################################
Refer section: Building the Examples in the KeystoneII_BootExamples_UserGuide.pdf 


########################################################################################
Running the Examples
#######################################################################################
EVM Dip Switch Settings
########################################################################################

No Boot: SW1(pin1, pin2, pin3, pin4): off, off, off, on
UART: SW1(pin1, pin2, pin3, pin4): off, on, off, off
NAND: SW1(pin1, pin2, pin3, pin4): off, off, off, off
SPI: SW1(pin1, pin2, pin3, pin4): off, off, on, off
I2C: SW1(pin1, pin2, pin3, pin4): off, off, on, on
Ethernet: SW1(pin1, pin2, pin3, pin4): off, on, off, on

To flash and run the examples please refer to the Flashing and Running boot examples of the KeystoneII_BootExamples_UserGuide.pdf


########################################################################################
Ethernet Boot Example
########################################################################################

This example requires the use of a utility to set up a TFTP server (e.g. tftpd32.303) to transfer the secondary image and a 10/100(/1000) Ethernet switch connected between the EVM and host computer. The TFTP server will load a second stage boot image in binary format. During the process of building the UART example, a copy of that second stage image is moved to the \eth2nd\bin directory (ethernet2ndStage.bin).

########################################################################################
Verifying the Example
########################################################################################

Connect to the EVM via UART (explained in "Loading the Boot Images" section).
Each ARM core will send a message over UART: "Core n standing by..." where n is the ARM core number.
