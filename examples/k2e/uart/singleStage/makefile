# Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
#
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHuartER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# ******************************************************************************************
# * FILE PURPOSE: Build the 2nd stage uarternet boot loader fix
# ******************************************************************************************
# * FILE NAME: Makefile
# *
# * DESCRIPTION: Builds the 2nd stage uarternet boot fix for K2E/K2L boot bug
# *
# *  Usage:  make [DEVICE=     --K2E | K2L] \
# *				  [PLATFORM=   --EVM | CUSTOM] \
# *               [REF_CLK=    f50 | f66_66 | f80 | --f100 | f156_25 | f250 | f312_5 | f122_88] \
# *               [PA_CLK=     f50 | f66_66 | f80 | f100 | f156_25 | f250 | f312_5 | f122_88 | --f125] \
# *				  [SGMII=      MASTER | --SLAVE | FORCED]
# *				  [SERDES_REF= --f125 | f156_25]
# *
# *******************************************************************************************

OPTS = -c -g -mv7a8 -as -ss -ml $(AOPTS_LE) --abi=ti_arm9_abi --code_state=32 --diag_warning=225
RTL=$(ARM_LIB_FOLDER)\libc.a
INC= -i$(PDK_PACKAGES) -i$(ARM_INCLUDE_FOLDER) -i$(CSL_LIB_LOC) -i$(LOCAL_INCLUDE_FOLDER) -i$(LOCAL_CONFIG_FOLDER)
vpath % $(COMMON_SOURCE_FOLDER)/mmu

BUILDOPTS=

ifdef DEVICE
 BUILDOPTS+= -DDEVICE=$(DEVICE)
endif

ifdef PLATFORM
 BUILDOPTS+= -DPLATFORM=$(PLATFORM)
endif

ifdef REF_CLK
 BUILDOPTS+= -DREF_CLK=$(REF_CLK)
endif

ifdef PA_CLK
 BUILDOPTS+= -DPA_CLK=$(PA_CLK)
endif

ifdef SGMII
 BUILDOPTS+= -DSGMII=$(SGMII)
endif

ifdef SERDES_REF
 BUILDOPTS+= -DSERDES_REF=$(SERDES_REF)
endif

ifndef DEVICE
 DEVICE=K2E
 export DEVICE
endif

DEVICE_FLAGS=  -D$(DEVICE)
BOOT_FLAGS  =  -DUART -DBLOB 

all: uart_data.bin


uart_data.bin:  
	$(ARM_BIN_FOLDER)/armcl -k $(AOPTS_LE) $(AOPTS) -i$(ARM_INCLUDE_FOLDER) -i$(LOCAL_INCLUDE_FOLDER) -eo.obja $(COMMON_SOURCE_FOLDER)/setEntryPoint.s
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(INC) $(COMMON_SOURCE_FOLDER)/pll/pll.c
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(INC) $(COMMON_SOURCE_FOLDER)/uart/uart.c
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(BOOT_FLAGS) $(INC) -I$(COMMON_SOURCE_FOLDER)/uart -I$(COMMON_SOURCE_FOLDER)/pll $(LOCAL_SOURCE_FOLDER)/singleStage/Stage1.c
	$(ARM_BIN_FOLDER)/armcl -z -muart.map -i$(ARM_LIB_FOLDER) -i$(ARM_INCLUDE_FOLDER) --reread_libs --warn_sections --rom_model -o uart.out  pll.obj uart.obj Stage1.obj setEntryPoint.obja -l"libc.a" $(LOCAL_BUILD_FOLDER)/singleStage_blobBoot.cmd
	$(ARM_BIN_FOLDER)/armhex uart.out $(LOCAL_BUILD_FOLDER)/singleStage_blobBoot.rmd 
	$(LOCAL_UTILS_FOLDER)/btoccs/b2ccs.exe Stage1.hex uart.ccs.dat
	$(LOCAL_UTILS_FOLDER)/btoccs/ccs2bin.exe uart.ccs.dat uart.ccs.dat.bin
	mkdir -p bin
	cp uart.ccs.dat.bin ./bin/uart_data.bin

clean:
	rm -f *.obja *.obj *.map *.asm *.hex *.dat *.gphdr *.gptlr *.combined *.pad ./bin/* uart.out
