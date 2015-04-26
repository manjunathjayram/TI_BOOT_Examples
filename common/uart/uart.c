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
 
 
#ifndef __ARMv7
    #define __ARMv7
#endif

#include <stdio.h>
#include <stdint.h>

#ifdef K2E
#include <ti/csl/device/k2e/src/cslr_device.h>
#include <ti/csl/cslr_uart.h>
#include <ti/platform/evmk2e/platform_lib/include/evmc66x_uart.h>
#endif

#ifdef K2H
#include <ti/csl/device/k2h/src/cslr_device.h>
#include <ti/csl/cslr_uart.h>
#include <ti/platform/evmk2h/platform_lib/include/evmc66x_uart.h>
#endif


#include <ti/csl/csl_sem.h>
#include <ti/csl/csl_semAux.h>
#include "uart.h"


void UartInit(void) {
    //      Allows access to the divisor latches of the baud generator during a 
    // read or write operation (DLL and DLH)
    CSL_FINS (hUartRegs->LCR, UART_LCR_DLAB, CSL_UART_LCR_DLAB_ENABLE);
    //      Break condition is disabled.
    CSL_FINS (hUartRegs->LCR, UART_LCR_BC,   CSL_UART_LCR_BC_DISABLE);
    //      Stick parity is disabled.
    CSL_FINS (hUartRegs->LCR, UART_LCR_SP,   CSL_UART_LCR_SP_DISABLE);
    //      Odd parity is selected
    CSL_FINS (hUartRegs->LCR, UART_LCR_EPS,  CSL_UART_LCR_EPS_ODD);
    //      No PARITY bit is transmitted or checked
    CSL_FINS (hUartRegs->LCR, UART_LCR_PEN,  CSL_UART_LCR_PEN_DISABLE);    

    // Set the baudrate,for accessing LCR[7] should be enable 
    hUartRegs->DLL  = DLL_VAL;
    hUartRegs->DLH  = DLM_VAL;

    // Allows access to the receiver buffer register (RBR), 
    // the transmitter holding register (THR), and the
    // interrupt enable register (IER) selected.
    CSL_FINS (hUartRegs->LCR, UART_LCR_DLAB, CSL_UART_LCR_DLAB_DISABLE);
    // Even Parity is selected
    CSL_FINS (hUartRegs->LCR, UART_LCR_EPS, CSL_UART_LCR_EPS_EVEN);
    // Parity Enable 
    CSL_FINS (hUartRegs->LCR, UART_LCR_PEN, CSL_UART_LCR_PEN_ENABLE);
 
    // Disable THR, RHR, Receiver line status interrupts
    CSL_FINS (hUartRegs->IER, UART_IER_ERBI,  CSL_UART_IER_ERBI_DISABLE);
    CSL_FINS (hUartRegs->IER, UART_IER_ETBEI, CSL_UART_IER_ETBEI_DISABLE);
    CSL_FINS (hUartRegs->IER, UART_IER_ELSI,  CSL_UART_IER_ELSI_DISABLE);
    CSL_FINS (hUartRegs->IER, UART_IER_EDSSI, CSL_UART_IER_EDSSI_DISABLE);  

    hUartRegs->MCR = 0;

    hUartRegs->PWREMU_MGMT = 0x6001;

    /* Cleanup previous data (rx trigger is also set to 0)*/
    CSL_FINS (hUartRegs->FCR, UART_FCR_FIFOEN,   CSL_UART_FCR_FIFOEN_ENABLE);
    CSL_FINS (hUartRegs->FCR, UART_FCR_TXCLR,    CSL_UART_FCR_TXCLR_CLR);
    CSL_FINS (hUartRegs->FCR, UART_FCR_RXCLR,    CSL_UART_FCR_RXCLR_CLR);
    CSL_FINS (hUartRegs->FCR, UART_FCR_DMAMODE1, CSL_UART_FCR_DMAMODE1_DISABLE);
    CSL_FINS (hUartRegs->FCR, UART_FCR_RXFIFTL,  CSL_UART_FCR_RXFIFTL_CHAR1);

    return;
}

void UartSetBaudRate(uint16_t uiBaudRate) {
    uint8_t uiDLLVal = 0;
    uint8_t uiDLHVal = 0;

    hUartRegs->LCR = 0x80;
    uiDLLVal = (uint8_t )(0x00FF & uiBaudRate);
    uiDLHVal = (uint8_t )(0x00FF & (uiBaudRate  >> 8));

    // Set the baudrate,for accessing LCR[7] should be enable 
    hUartRegs->DLL  = uiDLLVal;
    hUartRegs->DLH  = uiDLHVal;
    hUartRegs->LCR = 0x03;
}

void UartWriteData(uint8_t uchByte) {
	int i;
    while (!(CSL_FEXT(hUartRegs->LSR, UART_LSR_THRE))) {
		for(i = 0; i < 10000; i++);
    }
    
    CSL_FINS(hUartRegs->THR, UART_THR_DATA, uchByte);
    return;
}

unsigned short write_uart(char* msg) {
	uint32_t j;
	volatile uint32_t count = 0;
    uint32_t i;
    uint32_t msg_len = strlen(msg);

    /* Write the message to the UART */
    for (i = 0; i < msg_len; i++)
    {
		for(j = 0; j < 1000; j++)
		{
			count++;
		}
        UartWriteData(msg[i]);
    }

    return TRUE;
}


