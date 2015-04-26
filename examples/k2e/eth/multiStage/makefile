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
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# ******************************************************************************************
# * FILE PURPOSE: Build the 2nd stage ethernet boot loader fix
# ******************************************************************************************
# * FILE NAME: Makefile
# *
# * DESCRIPTION: Builds the 2nd stage ethernet boot fix for K2E/K2L boot bug
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
RTL=$(ARM_LIB_FOLDER)/libc.a
INC= -I$(COMMON_SOURCE_FOLDER)/mmu -I$(ARM_INCLUDE_FOLDER) -I$(LOCAL_INCLUDE_FOLDER) -i$(LOCAL_CONFIG_FOLDER)
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


all: cdefdep ethWard.gphdr.word.ccs ethWard.gphdr.byte.ccs ethWard.blob.bin


ethWard.blob.bin: ethWard.blob.ccs
	$(LOCAL_UTILS_FOLDER)/btoccs/ccs2bin.exe $< $@
	cp ethWard.blob.bin ./bin/ethernetUART.bin

ethWard.gphdr.byte.ccs: ethWard.blob.ccs
	$(LOCAL_UTILS_FOLDER)/byteswap/byteswapccs.exe $< tmp.ccs
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGphdr.exe -infile tmp.ccs -outfile tmp2.ccs
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGptlr.exe -infile tmp2.ccs -outfile $@
	cp ethWard.gphdr.byte.ccs ./bin/ethernetI2C.dat


ethWard.gphdr.word.ccs: ethWard.blob.ccs
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGphdr.exe -infile $< -outfile tmp.ccs
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGptlr.exe -infile tmp.ccs -outfile $@

ethWard.blob.ccs: ethWard.out
	$(ARM_BIN_FOLDER)/armhex $(LOCAL_BUILD_FOLDER)/Stage1_ethWard.rmd
	$(LOCAL_UTILS_FOLDER)/btoccs/b2ccs.exe blob.b ethWard.blob.ccs
	

ethWard.out: $(LOCAL_BUILD_FOLDER)/Stage1_ethWard.cmd ethWard.oc mmu.oa armstart.oa
	$(ARM_BIN_FOLDER)/armcl -z -o $@  $< -m ethWard.map $(RTL)

ethWard.oc: $(LOCAL_SOURCE_FOLDER)/multiStage/ethWard.c cdefdep
	$(ARM_BIN_FOLDER)/armcl $(OPTS) $(INC) -eo.oc $< $(BUILDOPTS)


mmu.oa: $(COMMON_SOURCE_FOLDER)/mmu/mmu.s
	$(ARM_BIN_FOLDER)/armcl $(OPTS) -eo.oa $<

armstart.oa: $(COMMON_SOURCE_FOLDER)/armstart.s
	$(ARM_BIN_FOLDER)/armcl $(OPTS) -eo.oa $<

cdefdep:
	@echo $(PLATFORM) $(REF_CLK) $(PA_CLK) $(SGMII) $(SERDES_REF) > cdefdep.tmp

clean:
	rm -f ethWard.oc ethWard.out ethWard.map mmu.oa armstart.oa
	rm -f blob.b blob.ccs ethWard.blob.bin
	rm -f ethWard.gphdr.word.ccs ethWard.blob.ccs tmp.ccs tmp2.ccs ethWard.asm
	rm -f cdefdep cdefdep.tmp ethWard.gphdr.byte.ccs
