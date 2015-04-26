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

export ARM_BIN_FOLDER = $(ARM_COMPILER_FOLDER)/bin
export ARM_LIB_FOLDER = $(ARM_COMPILER_FOLDER)/lib
export ARM_INCLUDE_FOLDER = $(ARM_COMPILER_FOLDER)/include
export LOCAL_UTILS_FOLDER = ../../../utils

all: uboot.hex uboot_blob.bin uboot_gp.bin

uboot.hex: 
	cp $(UBOOT_DIR)/uboot ./uboot.out
	$(ARM_BIN_FOLDER)/armhex uboot.rmd
	
uboot_blob.bin: uboot.hex
	$(LOCAL_UTILS_FOLDER)/btoccs/b2ccs.exe uboot.hex blob.ccs.dat
	$(LOCAL_UTILS_FOLDER)/btoccs/ccs2bin.exe blob.ccs.dat blob.ccs.dat.bin
	mkdir -p bin
	cp -f blob.ccs.dat.bin ./bin/uboot_eth.bin
	cp -f blob.ccs.dat.bin ./bin/uboot_uart.bin

uboot_gp.bin:  uboot.hex
	$(LOCAL_UTILS_FOLDER)/btoccs/b2ccs.exe uboot.hex gp.ccs.dat
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGphdr.exe -infile gp.ccs.dat -outfile gp.ccs.dat.gphdr -headerEndian BE
	$(LOCAL_UTILS_FOLDER)/ccsutil/ccsAddGptlr.exe -infile gp.ccs.dat.gphdr -outfile gp.ccs.dat.gphdr.gptlr
	$(LOCAL_UTILS_FOLDER)/btoccs/ccs2bin.exe gp.ccs.dat.gphdr.gptlr uboot.bin
	mkdir -p bin
	cp -f gp.ccs.dat.gphdr.gptlr ./bin/uboot_spi.dat
	cp -f gp.ccs.dat.gphdr.gptlr ./bin/uboot_nand.dat
	$(LOCAL_UTILS_FOLDER)/byteswap/byteswapccs.exe gp.ccs.dat.gphdr.gptlr ./bin/uboot_i2c.dat
	
	

clean:
	rm -f *.obja *.obj *.map *.asm *.hex *.dat *.gphdr *.gptlr *.combined *.pad *.bin ./bin/* uboot.out