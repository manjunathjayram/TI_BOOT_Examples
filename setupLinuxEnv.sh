#!/bin/bash
# ******************************************************************************
# * FILE PURPOSE: Boot examples setup environment
# ******************************************************************************
# * FILE NAME: setupLinuxEnvr.sh
# *
# * DESCRIPTION: 
# *  The shell script file sets path for compiler and PDK packages.
# *
# * Copyright (C) 2012, Texas Instruments, Inc.
# *****************************************************************************
export ARM_COMPILER_FOLDER=$HOME/ti/ccsv5/tools/compiler/arm_5.0.4
echo "ARM_COMPILER_FOLDER set to $ARM_COMPILER_FOLDER"

export PDK_PACKAGES=$HOME/ti/pdk_keystone2_3_01_00_03/packages
echo "PDK_PACKAGES set to $PDK_PACKAGES"

export UBOOT_DIR=C:/Users/a0272049/Desktop/Security/Bootloader/K2H_boot/Benchmarks/k2h_eth
