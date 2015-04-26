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



BUILDOPTS=

ifndef DEVICE
 DEVICE=K2E
 export DEVICE
endif

DEVICE_FLAGS=  -D$(DEVICE)
BOOT_FLAGS  =  -DI2C -DGP -DDDR

ifdef PLATFORM
 BUILDOPTS+= -DPLATFORM=$(PLATFORM)
endif

INC= -i$(PDK_PACKAGES) -i$(ARM_INCLUDE_FOLDER) -i$(CSL_LIB_LOC) -i$(LOCAL_INCLUDE_FOLDER) -i$(LOCAL_CONFIG_FOLDER)

all: i2cImage.dat
	
i2cImage.dat: Stage1.ccs.dat.gphdr.gptlr.pad Stage2.ccs.dat.gphdr.gptlr.combined
	$(LOCAL_UTILS_FOLDER)/ccsutil/catccs.exe Stage1.ccs.dat.gphdr.gptlr.pad Stage2.ccs.dat.gphdr.gptlr.combined -out Stage1.Stage2.ccs.dat.combined.dat
	$(LOCAL_UTILS_FOLDER)/byteswap/byteswapccs.exe Stage1.Stage2.ccs.dat.combined.dat ./bin/i2cImage.dat


Stage2.ccs.dat.gphdr.gptlr.combined: $(LOCAL_SOURCE_FOLDER)/multiStage/Stage2.c $(LOCAL_BUILD_FOLDER)/Stage2.rmd $(LOCAL_BUILD_FOLDER)/Stage2.cmd
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(INC) $(COMMON_SOURCE_FOLDER)/pll/pll.c
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(INC) $(COMMON_SOURCE_FOLDER)/uart/uart.c
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(BOOT_FLAGS) $(INC) -I$(COMMON_SOURCE_FOLDER)/uart -I$(COMMON_SOURCE_FOLDER)/pll $(LOCAL_SOURCE_FOLDER)/multiStage/Stage2.c
	$(ARM_BIN_FOLDER)/armcl -z -mStage2.map -i$(ARM_LIB_FOLDER) -i$(PDK_PACKAGES) -i$(ARM_INCLUDE_FOLDER) -i$(CSL_LIB_LOC) -i$(LOCAL_INCLUDE_FOLDER) --reread_libs --warn_sections --rom_model -o Stage2.out pll.obj uart.obj Stage2.obj setEntryPoint.obja -l"libc.a" $(LOCAL_BUILD_FOLDER)/Stage2.cmd
	$(ARM_BIN_FOLDER)/armhex $(LOCAL_BUILD_FOLDER)/Stage2.rmd
	$(LOCAL_UTILS_FOLDER)/btoccs/b2ccs.exe ddrConfigStage2.hex ddrConfigStage2.ccs.dat
	$(LOCAL_UTILS_FOLDER)/btoccs/b2ccs.exe Stage2.hex Stage2.ccs.dat
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGphdr.exe -infile ddrConfigStage2.ccs.dat -outfile ddrConfigStage2.ccs.dat.gphdr -headerEndian BE
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGphdr.exe -infile Stage2.ccs.dat -outfile Stage2.ccs.dat.gphdr -headerEndian BE
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGptlr.exe -infile Stage2.ccs.dat.gphdr -outfile Stage2.ccs.dat.gphdr.gptlr
	$(LOCAL_UTILS_FOLDER)/ccsutil/catccs.exe ddrConfigStage2.ccs.dat.gphdr Stage2.ccs.dat.gphdr.gptlr -out Stage2.ccs.dat.gphdr.gptlr.combined


Stage1.ccs.dat.gphdr.gptlr.pad: $(LOCAL_SOURCE_FOLDER)/multiStage/Stage1.c $(COMMON_SOURCE_FOLDER)/setEntryPoint.s $(LOCAL_BUILD_FOLDER)/Stage1.cmd $(LOCAL_BUILD_FOLDER)/Stage1.rmd
	$(ARM_BIN_FOLDER)/armcl -k $(AOPTS_LE) $(AOPTS) -i$(ARM_INCLUDE_FOLDER) -i$(LOCAL_INCLUDE_FOLDER) -eo.obja $(COMMON_SOURCE_FOLDER)/setEntryPoint.s
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(BOOT_FLAGS) $(INC) $(LOCAL_SOURCE_FOLDER)/multiStage/Stage1.c
	$(ARM_BIN_FOLDER)/armcl -z -mStage1.map -i$(ARM_LIB_FOLDER) -i$(ARM_INCLUDE_FOLDER) -i$(LOCAL_INCLUDE_FOLDER) --reread_libs --warn_sections --rom_model -o Stage1.out  Stage1.obj setEntryPoint.obja -l"libc.a" $(LOCAL_BUILD_FOLDER)/Stage1.cmd
	$(ARM_BIN_FOLDER)/armhex $(LOCAL_BUILD_FOLDER)/Stage1.rmd
	$(LOCAL_UTILS_FOLDER)/btoccs/b2ccs.exe Stage1.hex Stage1.ccs.dat
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGphdr.exe -infile Stage1.ccs.dat -outfile Stage1.ccs.dat.gphdr -headerEndian BE
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGptlr.exe -infile Stage1.ccs.dat.gphdr -outfile Stage1.ccs.dat.gphdr.gptlr
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccspad.exe Stage1.ccs.dat.gphdr.gptlr Stage1.ccs.dat.gphdr.gptlr.pad 0 2048


clean:
	rm -f *.obja *.obj *.map *.out *.asm *.hex *.dat *.gphdr *.gptlr *.combined *.pad