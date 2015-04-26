#/*
# *
# * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/ 
# * 
# * 
# *  Redistribution and use in source and binary forms, with or without 
# *  modification, are permitted provided that the following conditions 
# *  are met:
# *
# *    Redistributions of source code must retain the above copyright 
# *    notice, this list of conditions and the following disclaimer.
# *
# *    Redistributions in binary form must reproduce the above copyright
# *    notice, this list of conditions and the following disclaimer in the 
# *    documentation and/or other materials provided with the   
# *    distribution.
# *
# *    Neither the name of Texas Instruments Incorporated nor the names of
# *    its contributors may be used to endorse or promote products derived
# *    from this software without specific prior written permission.
# *
# *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
# *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
# *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
# *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
# *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
# *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
# *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
# *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# *
#*/

TARGETS= ccsutil.o catccs.exe ccsAddGphdr.exe ccsAddGptlr.execcspad.exe

all: $(TARGETS)


ccsutil.o: ccsutil.c ccsutil.h
	gcc -g -c ccsutil.c

ccspad.exe: ccspad.c ccsutil.o
	gcc -g -o $@ $< ccsutil.o

catccs.exe: catccs.c ccsutil.o
	gcc -g -o catccs catccs.c ccsutil.o


ccsAddGphdr.exe: ccsAddGphdr.c ccsutil.o
	gcc -g -o $@ ccsAddGphdr.c ccsutil.o

ccsAddGptlr.exe: ccsAddGptlr.c ccsutil.o
	gcc -g -o $@ ccsAddGptlr.c ccsutil.o

