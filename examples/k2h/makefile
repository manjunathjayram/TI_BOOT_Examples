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

export AOPTS_LE = --endian=little
export AOPTS_BE =  --endian=big
export AOPTS = -mv7A8 --code_state=32 -g --abi=ti_arm9_abi --diag_warning=225
export ARM_BIN_FOLDER = $(ARM_COMPILER_FOLDER)/bin
export ARM_LIB_FOLDER = $(ARM_COMPILER_FOLDER)/lib
export ARM_INCLUDE_FOLDER = $(ARM_COMPILER_FOLDER)/include
export LOCAL_INCLUDE_FOLDER = ../../../../include
export COMMON_SOURCE_FOLDER = ../../../../common
export LOCAL_SOURCE_FOLDER = ../../../src
export LOCAL_UTILS_FOLDER = ../../../../utils
export LOCAL_CONFIG_FOLDER = ../../cfg
export LOCAL_BUILD_FOLDER = ../../build
export CSL_LIB_LOC = $(PDK_PACKAGES)/ti/csl/lib/k2h/c66


all: singleStage multiStage

singleStage:
	$(MAKE) DEVICE=K2H -C ./eth/singleStage
	$(MAKE) DEVICE=K2H -C ./i2c/singleStage
	$(MAKE) DEVICE=K2H -C ./nand/singleStage
	$(MAKE) DEVICE=K2H -C ./spi/singleStage
	$(MAKE) DEVICE=K2H -C ./uart/singleStage

multiStage:
	$(MAKE) DEVICE=K2H -C ./i2c/multiStage
	$(MAKE) DEVICE=K2H -C ./spi/multiStage
	$(MAKE) DEVICE=K2H -C ./uart/multiStage
	$(MAKE) DEVICE=K2H -C ./eth/multiStage
	
u-boot:
	$(MAKE) DEVICE=K2H -C ./uboot all
	
clean:
	$(MAKE) clean -C ./eth/singleStage
	$(MAKE) clean -C ./i2c/singleStage
	$(MAKE) clean -C ./nand/singleStage
	$(MAKE) clean -C ./spi/singleStage
	$(MAKE) clean -C ./uart/singleStage
	$(MAKE) clean -C ./i2c/multiStage
	$(MAKE) clean -C ./eth/multiStage
	$(MAKE) clean -C ./spi/multiStage
	$(MAKE) clean -C ./uart/multiStage
	$(MAKE) clean -C ./uboot