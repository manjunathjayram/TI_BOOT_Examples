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
BUILDOPTS+= -DDEVICE=$(DEVICE) 


ifdef PLATFORM
 BUILDOPTS+= -DPLATFORM=$(PLATFORM)
endif

INC= -i$(PDK_PACKAGES) -i$(ARM_INCLUDE_FOLDER) -i$(CSL_LIB_LOC) -i$(LOCAL_INCLUDE_FOLDER) -i$(LOCAL_CONFIG_FOLDER)

all: i2cImage.dat


i2cImage.dat: 
	$(ARM_BIN_FOLDER)/armcl -k $(AOPTS_LE) $(AOPTS) -i$(PDK_PACKAGES) -i$(ARM_INCLUDE_FOLDER) -i$(CSL_LIB_LOC) -i$(LOCAL_INCLUDE_FOLDER) -eo.obja $(COMMON_SOURCE_FOLDER)/setEntryPoint.s
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(INC) $(COMMON_SOURCE_FOLDER)/pll/pll.c
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(INC) $(COMMON_SOURCE_FOLDER)/uart/uart.c
	$(ARM_BIN_FOLDER)/armcl -k $(DEVICE_FLAGS) $(AOPTS_LE) $(AOPTS) $(BUILDOPTS) $(INC) -I$(COMMON_SOURCE_FOLDER)/uart -I$(COMMON_SOURCE_FOLDER)/pll $(LOCAL_SOURCE_FOLDER)/singleStage/Stage1.c
	$(ARM_BIN_FOLDER)/armcl -z -m i2c.map -i$(ARM_LIB_FOLDER) -i$(PDK_PACKAGES) -i$(ARM_INCLUDE_FOLDER) -i$(LOCAL_INCLUDE_FOLDER) -i$(CSL_LIB_LOC) --reread_libs --warn_sections --rom_model -o i2c.out  pll.obj uart.obj Stage1.obj setEntryPoint.obja -l"libc.a" $(LOCAL_BUILD_FOLDER)/singleStage.cmd
	$(ARM_BIN_FOLDER)/armhex i2c.out $(LOCAL_BUILD_FOLDER)/singleStage.rmd
	$(LOCAL_UTILS_FOLDER)/btoccs/b2ccs.exe Stage1.hex i2c.ccs.dat
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGphdr.exe -infile i2c.ccs.dat -outfile i2c.ccs.dat.gphdr -headerEndian BE
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGptlr.exe -infile i2c.ccs.dat.gphdr -outfile i2c.ccs.dat.gphdr.gptlr
	$(LOCAL_UTILS_FOLDER)/byteswap/byteswapccs.exe i2c.ccs.dat.gphdr.gptlr ./bin/i2cImage.dat
		
clean:
	rm -f *.obja *.obj *.map *.out *.asm *.hex *.dat *.gphdr *.gptlr *.combined *.pad
