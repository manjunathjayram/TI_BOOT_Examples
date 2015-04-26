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
 
#ifndef _CHIP_H
#define _CHIP_H
/*******************************************************************************
 * FILE PURPOSE: Defines chip-dependent API and public data definitions  
 *******************************************************************************
 * FILE NAME: CHIP.h  
 *
 * DESCRIPTION: Defines API and public data definitions for chip-dependent 
 *              utilities. Each device must supply the functions defined
 *              by this API.
 *
 ******************************************************************************/

/* System level header files */
#include "types.h"

/****************************************************************************
 * Chip specific macros that are available to higher levels. Originally
 * each device had a file named chipmac.h, with the correct inclusion
 * handled through the makefile path setup. This method was removed from hal,
 * and so a new method is used. The top level make file will create a file
 * called device.h, in the chip.h directory. This file will include the
 * correct lower level file (monticello.h, himalaya.h, etc). The lower level
 * file is required to contain the following macro definition:
 *
 *BOOT_PARAMS_T   BOOT_MODE_xxx (UTOPIA, ETH, I2C, etc as defined in bootconfig.h for
 *                 the specific build).
 *  IFR_GMAC_RX_INT_MASK - a UINT32 containing a parameter used by chipPollIfr
 *  IFR_GMAC_TX_INT_MASK - a UINT32 containing a parameter used by chipPollIfr
 *  CHIP_IO(x) - provide read/write access to an I/O port at address x
 *
 * In addition any of the functions required can be a macro defined in this
 * file.
 ****************************************************************************/
#include "device.h"
#include "device_map.h"

/* CHIP error codes */
enum {
  CHIP_NOERR                    = 0,
  CHIP_ERR_GEN                  = 1,
  CHIP_ERR_ODD_ADDR             = 2,
  CHIP_ERR_INVALID_DATA_RANGE   = 3
};

/*******************************************************************************
 * Definition: Chip events. These events are used to describe the wakeup event
 *             for when the chip is put to sleep in idle mode
 *******************************************************************************/
enum {
  CHIP_EVENT_RIO_INTERRUPT    = 100 ,  /* Rapid I/O interrupt occurs */
  CHIP_EVENT_PCI_INTERRUPT,  /* 101 */ /*     PCI interrupt occurs   */
  CHIP_EVENT_ANY             /* 102 */ /* Any interrupt              */
};

/*******************************************************************************
 * Public function prototypes
 ******************************************************************************/
/*******************************************************************************
 * FUNCTION PURPOSE: Exception Handling
 *******************************************************************************
 * DESCRIPTION: Set the chip state on an unrecoverable error
 *              perform chip-specific operation such as  
 *              - disable interrupts
 *              - turn off Cache
 *              - form an infinite loop        
 *
 * void boot_exception (
 *   UINT16  error_code)      - Error Code 
 *
 *****************************************************************************/
#ifndef chipBootException
void NEAR chipBootException(UINT16 error_code);
#endif

/******************************************************************************
 * Get 16 bits from a 32 bit value
 ******************************************************************************/
#ifndef chipLower16
UINT16 NEAR chipLower16 (UINT32 v);
#endif

#ifndef chipUpper16
UINT16 NEAR chipUpper16 (UINT32 v);
#endif

#ifndef chipLower8
UINT8 NEAR chipLower8 (UINT32 v);
#endif

#ifndef chipUpper8
UINT8 NEAR chipUpper8 (UINT32 v);
#endif

#ifndef chipInsertLower16
UINT32 NEAR chipInsertLower16 (UINT32 v32, UINT32 v16);
#endif


/******************************************************************************
 * Convert 16 bit value to 32 bit value
 ******************************************************************************/
#ifndef chipRet32
UINT32 NEAR chipRet32 (UINT16 v);
#endif

/******************************************************************************
 * Form a 32 bit value from two 16 bit values
 ******************************************************************************/
#ifndef chipForm32
UINT32 NEAR chipForm32 (UINT16 msw, UINT16 lsw);
#endif
/******************************************************************************
 * Form a 16 bit value from 2 8 bit values
 ******************************************************************************/
#ifndef chipForm16_8
UINT16 NEAR chipForm16_8 (UINT8 msb, UINT8 lsb);
#endif

/******************************************************************************
 * Cache enable/disable
 ******************************************************************************/
#ifndef chipCacheInit
SINT16 NEAR chipCacheInit (void);
#endif
#ifndef ChipCacheDisable
SINT16 NEAR ChipCacheDisable(void *scratch);
#endif

/*****************************************************************************
 * Hardware entry/exit status control
 *****************************************************************************/
#ifndef chipSetEntryState
UINT32 NEAR chipSetEntryState (void);
#endif
#ifndef chipSetExitState
void NEAR chipSetExitState (void *params, int numParams);
#endif

#ifndef chipIntGEMCores
void NEAR chipIntGEMCores(void);
#endif

#ifndef chipReadyBootReentry
void NEAR chipReadyBootReentry (void);
#endif

/*****************************************************************************
 * The magic address. If the value becomes non-zero the DSP breaks out of
 * boot and branches to this address.
 *****************************************************************************/
#ifndef chipGetMagicAddr
UINT32 NEAR *chipGetMagicAddr (void);
#endif

#ifndef chipInitEntryAddr
void NEAR chipInitEntryAddr (void);
#endif

/*****************************************************************************
 * The boot exit wrapper
 *****************************************************************************/
#ifndef chipGoodBye
void NEAR chipGoodBye (UINT32 addr);
#endif

/*****************************************************************************
 * Rom Test code
 *****************************************************************************/
#ifndef romTest
void NEAR romTest (void);
#endif

/*****************************************************************************
 * Peripheral power up, power down. ChipPowerPeriph is based on boot mode,
 * chipPowerControl is available if ROM arg calls are enabled
 *****************************************************************************/
#ifndef chipPowerPeriph
SINT16 NEAR chipPowerPeriph (UINT16 bootMode, UINT16 portNum);
#endif

#ifndef chipPowerControl
void NEAR chipPowerControl (UINT32 enable, UINT32 modNum);
#endif

#ifndef chipWriteDspDisableCtl
void NEAR chipWriteDspDisableCtl ();
#endif

/*****************************************************************************
 * Reads from specific registers 
 *****************************************************************************/
#ifndef chipReadEfuse
UINT16 NEAR chipReadEfuse (void);
#endif
#ifndef chipReadMacAddr
void NEAR chipReadMacAddr (UINT16 *addr);
#endif

#ifndef chipReadMmacAddr
void NEAR chipReadMmacAddr (UINT16 *addr);
#endif

#ifndef chipReadHmacAddr
void NEAR chipReadHmacAddr (UINT16 *addr);
#endif

/*****************************************************************************
 * Return the boot mode
 *****************************************************************************/
#ifndef chipPinReadBootMode
UINT16 NEAR chipPinReadBootMode (SINT32 pIdx);
#endif

/*****************************************************************************
 * Initialize the boot parameter tables
 *****************************************************************************/
#ifndef chipInitBootParams
SINT16 NEAR chipInitBootParams (UINT16 bootMode, void *params);
#endif

/*****************************************************************************
 * Initialize the boot parameter tables when there is more then one
 *****************************************************************************/
#ifndef chipInitParamTable
void NEAR chipInitParamTable (SINT32 ordinal, void *params);
#endif

/*****************************************************************************
 * Branch to the main boot function
 *****************************************************************************/
#ifndef chipEnterMainBoot
SINT32 NEAR chipEnterMainBoot (void *bparams);
#endif

/*****************************************************************************
 * The CPU frequency
 *****************************************************************************/
#ifndef chipCoreFreqMhz
UINT16 NEAR chipCoreFreqMhz(void);
#endif

#ifndef chipEfuseFreqMhz
UINT16 NEAR chipEfuseFreqMhz (void);
#endif


#ifndef chipDefaultPll
UINT32 NEAR chipDefaultPll (BOOL isMinValid);
#endif

#ifndef chipExternalPrediv
BOOL NEAR chipExternalPrediv (UINT16 pllNum);
#endif

#ifndef chipPllExternalSetEnsat
void NEAR chipPllExternalSetEnsat (UINT16 pllNum);
#endif

#ifndef chipPllExternalBwAdj
SINT16 NEAR chipPllExternalBwAdj (UINT16 pllNum, UINT16 mult);
#endif

#ifndef chipPllSetExternalPrediv
SINT16 NEAR chipPllSetExternalPrediv(UINT16 pllNum, UINT32 predivRegVal);
#endif

#ifndef chipPllExternalMult
UINT32 NEAR chipPllExternalMult (UINT16 pllNum, UINT16 mult);
#endif

#ifndef chipPllExternalInit
void NEAR chipPllExternalInit (void);
#endif


/*****************************************************************************
 * Boot register locking/unlocking
 *****************************************************************************/
#ifndef chipKickUnlock
void NEAR chipKickUnlock(void);
#endif

#ifndef chipKickLock
void NEAR chipKickLock(void);
#endif

#ifndef chipKickOpenSerdes
void NEAR chipKickOpenSerdes(UINT32 base);
#endif

#ifndef chipKickClosedSerdes
void NEAR chipKickClosedSerdes(UINT32 base);
#endif

/*****************************************************************************
 * Return the uphy
 *****************************************************************************/
#ifndef chipReadUphy
UINT16 NEAR chipReadUphy (void);
#endif

/******************************************************************************
 * Return the rapid I/O addr
 ******************************************************************************/
#ifndef chipReadRioAddr
UINT32 NEAR chipReadRioAddr (BOOL *useDefault);
#endif

/*****************************************************************************
 * Return the rapid I/O table to use
 *****************************************************************************/
#ifndef chipGetRioTable
UINT32 NEAR chipGetRioTable (void);
#endif

/*****************************************************************************
 * Rapid I/O chip level system setup
 *****************************************************************************/
#ifndef chipLevelSrioConfig
SINT16 NEAR chipLevelSrioConfig (UINT32 cppiBase, UINT32 cppiMemSizeUint16, UINT32 pktBase, 
                            UINT32 pktMemSizeUint16, UINT32 pktBufUint16);
#endif                            

#ifndef chipSrioGetPkt
UINT16 NEAR *chipSrioGetPkt (void **vcppi, UINT16 *len);
#endif

#ifndef chipSrioRxReturn
SINT16 NEAR chipSrioRxReturn (void *vcppi);
#endif


#ifndef chipSrioPktDone
SINT16 NEAR chipSrioPktDone (void *vcppi);
#endif
                            
#ifndef chipSrioSetPortLaneMaster
void NEAR chipSrioSetPortLaneMaster (void *sdCfg, UINT16 portLane);
#endif

#ifndef chipStatusRioTimeout
void chipStatusRioTimeout(void);
#endif

/*****************************************************************************
 * This was defined to work around endianness compile issues. Normally this
 * is defined in the chip header file to simply return it's argument
 *****************************************************************************/
#ifndef chipReturnArg
UINT32 NEAR chipReturnArg (UINT32 size);
#endif

/*****************************************************************************
 * Global data copy 
 *****************************************************************************/
#ifndef chipCopyData
UINT16 NEAR chipCopyData(UINT32 dest_addr, UINT16* p_data, UINT32 size, UINT16 start_vector);
#endif
                   
/*****************************************************************************
 * Core startup
 *****************************************************************************/
#ifndef chipStartCore
UINT16 NEAR chipStartCore(UINT32 start_addr, UINT32 magic_addr, UINT16 start_vector);
#endif

/*******************************************************************************
 * Route the gmac interrupts to the core
 ******************************************************************************/
#ifndef chipRouteGmacInt
void NEAR chipRouteGmacInt (UINT16 port, UINT16 core);
#endif

/*******************************************************************************
 * Route the utopia interrupts to the core
 *******************************************************************************/
#ifndef chipRouteUtopiaInt
void NEAR chipRouteUtopiaInt (void);
#endif

/*******************************************************************************
 * Route the rapid I/O interrupt to the core
 *******************************************************************************/
#ifndef chipRouteRapidIoInt
void NEAR chipRouteRapidIoInt (void);
#endif

/*******************************************************************************
 * Route the HPI interrupt to the core
 *******************************************************************************/
#ifndef chipRouteHpiInt
void NEAR chipRouteHpiInt (void);
#endif

/*******************************************************************************
 * Read the uphy address
 *******************************************************************************/
#ifndef chipReadUphy
UINT16 NEAR chipReadUphy(void); 
#endif

/*******************************************************************************
 * Read the core ID
 ******************************************************************************/
#ifndef chipReadCoreId
UINT16 NEAR chipReadCoreId(void);
#endif

/*****************************************************************************
 * Poll for an IFR flag
 ****************************************************************************/
#ifndef chipPollIfr
bool NEAR chipPollIfr (UINT16 port, UINT32 ifrdat);
#endif

/*****************************************************************************
 * Poll for mac packets
 *****************************************************************************/
#ifndef chipPollRxMac
bool NEAR chipPollRxMac (UINT16 port);
#endif

/****************************************************************************
 * Poll for tx descriptor returns
 ****************************************************************************/
#ifndef chipPollTxMac
void NEAR chipPollTxMac (UINT16 portNum);
#endif

/****************************************************************************
 * Read the number of cores on the device
 ****************************************************************************/
#ifndef chipReadNumCores
UINT16 NEAR chipReadNumCores(void);
#endif

#ifndef chipReadNumArms
SINT32 NEAR chipReadNumArms (void);
#endif

#ifndef chipReadNumGems
SINT32 NEAR chipReadNumGems (void);
#endif

/*******************************************************************************
 * Provide specified delay in cycles
 ******************************************************************************/
#ifndef chipDelay
void NEAR chipDelay(UINT16 cycles);
#endif

#ifndef chipDelay32
void NEAR chipDelay32 (UINT32 cycles);
#endif

/*****************************************************************************
 * Perform writes to I/O addresses
 *****************************************************************************/
#ifndef chipIoWrite
void NEAR chipIoWrite(UINT16 addr, UINT16 data);
#endif

/****************************************************************************
 * Setup the version information in local memory
 ****************************************************************************/
#ifndef copyVersion
void NEAR copyVersion (UINT16 *dest, UINT16 size);
#endif

/****************************************************************************
 * I2C setup
 ****************************************************************************/
#ifndef chipDefaultI2cCoreFreqMhz
UINT16 NEAR chipDefaultI2cCoreFreqMhz (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipDefaultI2cSysFreqMhz
UINT16 NEAR chipDefaultI2cSysFreqMhz (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipDefaultI2cFreqKhz
UINT16 NEAR chipDefaultI2cFreqKhz (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipDefaultI2cAddressDelay
UINT16 NEAR chipDefaultI2cAddressDelay (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipDefaultI2cPhysPort
UINT16 NEAR chipDefaultI2cPhysPort (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipDefaultI2cPll
UINT32 NEAR chipDefaultI2cPll (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipDefaultI2cPll2
UINT32 NEAR chipDefaultI2cPll2 (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipI2cModuleDivisor
UINT16 NEAR chipI2cModuleDivisor (void);
#endif

#ifndef chipDefaultI2CEepromAddr
UINT16 NEAR chipDefaultI2CEepromAddr (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipDefaultI2cOptions
UINT16 NEAR chipDefaultI2cOptions (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipDefaultI2CDevAddr
UINT16 NEAR chipDefaultI2CDevAddr (SINT32 tblIdx, UINT16 bootMode);
#endif

#ifndef chipDefaultI2cOwnId
UINT16 NEAR chipDefaultI2cOwnId (SINT32 tblIdx, UINT16 bootMode);
#endif

/****************************************************************************
 * Device reporting of I2C statistics
 ****************************************************************************/
#ifndef chipStatusUpdateI2c
void NEAR chipStatusUpdateI2c (UINT32 addr);
#endif

#ifndef chipStatusIncI2cRetry
void NEAR chipStatusIncI2cRetry (UINT16);
#endif

#ifndef chipStatusIncI2cPassiveBlocks
void NEAR chipStatusIncI2cPassiveBlocks (void);
#endif

#ifndef chipUpdateI2cPassiveModeBootConfig
void NEAR chipStatusI2cPassiveModeBootConfig (void);
#endif


#ifndef chipStatusI2cPassiveSubMode
void NEAR chipStatusI2cPassiveSubMode (UINT16 subMode);
#endif

/***************************************************************************
 * Device reporting of ethernet statistics
 ***************************************************************************/
#ifndef chipStatusEthReject
void NEAR chipStatusEthReject (void);
#endif

#ifndef chipStatusEthMisSequenced
void NEAR chipStatusEthMisSequenced (void);
#endif

#ifndef chipIncBPField
void NEAR chipIncBPField (UINT32 msb, UINT32 lsb);
#endif

#ifndef chipDecBPField
void NEAR chipDecBPField (UINT32 msb, UINT32 lsb);
#endif

#ifndef chipSetBPField
void NEAR chipSetBPField (UINT32 value, UINT32 msb, UINT32 lsb);
#endif

/****************************************************************************
 * Device reporting of utopia statistics
 ****************************************************************************/
#ifndef chipStatusIncUtCells
void NEAR chipStatusIncUtCells (void);
#endif

#ifndef chipStatusIncUtFail
void NEAR chipStatusIncUtFail (void);
#endif

/****************************************************************************
 * Boot complete reporting
 ****************************************************************************/
#ifndef chipStatusBootComplete
void NEAR chipStatusBootComplete (void);
#endif


/****************************************************************************
 * Utopia configuration
 ****************************************************************************/
#ifndef chipGetDefaultUtopiaPortNum
UINT16 NEAR chipGetDefaultUtopiaPortNum (void);
#endif

#ifndef chipGetDefaultUtopiaPll
UINT32 NEAR chipGetDefaultUtopiaPll (void);
#endif

#ifndef chipGetDefaultUtopiaCellSize
UINT16 NEAR chipGetDefaultUtopiaCellSize (void);
#endif

#ifndef chipGetDefaultUtopiaBusWidth
UINT16 NEAR chipGetDefaultUtopiaBusWidth (void);
#endif

#ifndef chipGetDefaultUtopiaPhyId
UINT16 NEAR chipGetDefaultUtopiaPhyId (void);
#endif

#ifndef chipGetDefaultUtopiaCoreFreq
UINT16 NEAR chipGetDefaultUtopiaCoreFreq (void);
#endif


/***************************************************************************
 * Rapid I/O configuration 
 ***************************************************************************/
#ifndef chipGetDefaultRapidIoPortNum
UINT16 NEAR chipGetDefaultRapidIoPortNum (void);
#endif

#ifndef chipGetDefaultRapidIoPll
UINT32 NEAR chipGetDefaultRapidIoPll (void);
#endif

#ifndef chipGetDefaultRapidIoOpts
UINT16 NEAR chipGetDefaultRapidIoOpts (void);
#endif

#ifndef chipGetDefaultRapidIoIndex
UINT16 NEAR chipGetDefaultRapidIoIndex (void);
#endif

#ifndef chipGetDefaultRapidIoNodeId
UINT16 NEAR chipGetDefaultRapidIoNodeId (void);
#endif

#ifndef chipGetDefaultRapidIoRefClk
UINT16 NEAR chipGetDefaultRapidIoRefClk (void);
#endif

#ifndef chipGetDefaultRapidIoLinkRate
UINT16 NEAR chipGetDefaultRapidIoLinkRate (void);
#endif

#ifndef chipGetDefaultRapidIoPfLow
UINT16 NEAR chipGetDefaultRapidIoPfLow (void);
#endif

#ifndef chipGetDefaultRapidIoPfHigh
UINT16 NEAR chipGetDefaultRapidIoPfHigh (void);
#endif

#ifndef chipGetDefaultRapidIoSetup
SINT16 NEAR chipGetDefaultRapidIoSetup(UINT16 *serdes_ref_clk_mhz_x_100, UINT16 *link_rate_mbs);
#endif

#ifndef chipGetDefaultRapidIoLanePortSetup
UINT16 NEAR chipGetDefaultRapidIoLanePortSetup(void);
#endif

/***************************************************************************
 * HPI Configuration
 ***************************************************************************/
#ifndef chipGetDefaultHpiPll
UINT32 NEAR chipGetDefaultHpiPll (void);
#endif

#ifndef chipIsHpiBootTbl
bool NEAR chipIsHpiBootTbl (void);
#endif

/****************************************************************************
 * Hibernation Recovery Configuration
 ****************************************************************************/
#ifndef chipEmif25Select
UINT32 NEAR chipEmif25Select (UINT32 addr);
#endif

#ifndef chipDefaultHibRecoveryPll
UINT32 NEAR chipDefaultHibRecoveryPll (void);
#endif

#ifndef chipDefaultHibRecoveryPll2
UINT32 NEAR chipDefaultHibRecoveryPll2 (void);
#endif

#ifndef chipDefaultHibRecoveryType
UINT16 NEAR chipDefaultHibRecoveryType (void);        
#endif

#ifndef chipDefaultHibRecoveryAddr
UINT32 NEAR chipDefaultHibRecoveryAddr (void);
#endif

#ifndef chipDefaultHibRecoveryXipWidth
UINT16 NEAR chipDefaultHibRecoveryXipWidth (void);
#endif

#ifndef chipDefaultHibRecoveryXipWait
UINT16 NEAR chipDefaultHibRecoveryXipWait  (void);
#endif

#ifndef chipDefaultHibRecoverySysFreqMhz
void NEAR chipDefaultHibRecoverySysFreqMhz(void);
#endif

#ifndef chipDefaultHibRecoveryCoreFreqMhz
void NEAR chipDefaultHibRecoveryCoreFreqMhz(void);
#endif

/****************************************************************************
 * Sleep Configuration
 ****************************************************************************/
#ifndef chipDefaultSleepPll
UINT32 NEAR chipDefaultSleepPll (void *params, SINT32 tblIndex);
#endif

#ifndef chipDefaultSleepPll2
UINT32 NEAR chipDefaultSleepPll2 (void *params, SINT32 tblIndex);
#endif

#ifndef chipDefaultSleepSysFreqMhz
UINT16 NEAR chipDefaultSleepSysFreqMhz (void *params, SINT32 tblIndex);
#endif

#ifndef chipDefaultSleepCoreFreqMhz
UINT16 NEAR chipDefaultSleepCoreFreqMhz (void *params, SINT32 tblIndex);
#endif

#ifndef chipSleepRouteInterrupt
void NEAR chipSleepRouteInterrupt (void);
#endif

#ifndef chipSleepCleanupInterrupt
void NEAR chipSleepCleanupInterrupt (void);
#endif

/****************************************************************************
 * Memory Location
 ****************************************************************************/
#ifndef chipAddressIsMsmc
BOOL NEAR chipAddressIsMsmc (UINT32 addr);
#endif

#ifndef chipAddressIsExt
BOOL NEAR chipAddressIsExt  (UINT32 addr);
#endif

#ifndef chipAddressIsXip
BOOL NEAR chipAddressIsXip  (UINT32 addr);
#endif


/****************************************************************************
 * Mac configuration 
 ****************************************************************************/
#ifndef chipDefaultEthPort
UINT16 NEAR chipDefaultEthPort (void);
#endif

#ifndef chipDefaultNetCpPort
UINT16 NEAR chipDefaultNetCpPort (void);
#endif

#ifndef chipDefaultEthPll
UINT32 NEAR chipDefaultEthPll (void);
#endif

#ifndef chipDefaultEthIf
UINT16 NEAR chipDefaultEthIf (UINT16 port);
#endif

#ifndef chipDefaultEthSrcPort
UINT16 NEAR chipDefaultEthSrcPort (void);
#endif

#ifndef chipDefaultEthDstPort
UINT16 NEAR chipDefaultEthDstPort (void);
#endif

#ifndef chipDefaultEthDevId
void NEAR chipDefaultEthDevId (UINT16 port, UINT16 *id12, UINT16 *id34);
#endif

#ifndef chipDefaultSgmiiConfig
UINT16 NEAR chipDefaultSgmiiConfig (void);
#endif

#ifndef chipGetDefaultSGMIISetup
SINT16 NEAR chipGetDefaultSGMIISetup(void *p_sgmiiConfig);
#endif

#ifndef chipDefaultEthInit
UINT16 NEAR chipDefaultEthInit (UINT16 port);
#endif

#ifndef chipRgmiiPin
bool NEAR chipRgmiiPin (UINT16 port);
#endif

#ifndef chipMacPreConfigHandle
void NEAR chipMacPreConfigHandle (UINT16 port);
#endif

#ifndef chipMacPostConfigHandle
void NEAR chipMacPostConfigHandle (UINT16 port);
#endif

#ifndef chipNetifInit
SINT16  NEAR chipNetifInit (UINT32 netCpPort, UINT32 initLevel, void *nf, void *sgCfg, UINT32 coreFreqMhz);
#endif

#ifndef chipEthIsrRx
void NEAR *chipEthIsrRx (void);
#endif

#ifndef chipGetPacket
SINT16 NEAR chipGetPacket (void *vcppi, word *dstBuf, UINT16 *packetSizeBytes);
#endif

#ifndef chipEthRxReturn
SINT16 NEAR chipEthRxReturn (void *vcppi);
#endif

#ifndef chipStatusEthCppiFull
void NEAR chipStatusEthCppiFull (UINT16 cppiEmpty);
#endif

#ifndef chipEthTx
void NEAR chipEthTx (word *txBuf, UINT16 packetSizeBytes, word *cppiMem);
#endif

#ifndef chipFormTx
void NEAR chipFormTx (word *heap, SINT16 heapSizeUint16, word **txBuf, SINT16 *txBufSizeUint16, word **cppi);
#endif

#ifndef chipDefaultPktPll
UINT32 NEAR chipDefaultPktPll (void);
#endif

#ifndef chipConfigEthPll
SINT16 NEAR chipConfigEthPll (UINT32 initLevel, UINT32 pllConfig);
#endif

#ifndef chipSetupEthTimer
SINT16 NEAR chipSetupEthTimer (UINT32 sysFreqMhz);
#endif

#ifndef chipEthTimerExpired
bool NEAR chipEthTimerExpired (UINT32 sysFreqMhz);
#endif

#ifndef chipDisableEthTimer
SINT16 NEAR chipDisableEthTimer (void);
#endif

#ifndef chipEthChannelOpen
SINT16 NEAR chipEthChannelOpen (UINT16 port, UINT16 dir);
#endif

#ifndef chipMaxEthPktSize
UINT16 NEAR chipMaxEthPktSize(void);
#endif

#ifndef chipGetDefaultEthLaneEnableMask
UINT16 NEAR chipGetDefaultEthLaneEnableMask (void);
#endif

#ifndef chipEthSerdesLaneIsActive
BOOL chipEthSerdesLaneIsActive(UINT32 lane);
#endif

#ifndef chipEthSerdesBlockIsActive
BOOL chipEthSerdesBlockIsActive(UINT32 block);
#endif

/****************************************************************************
 * NAND configuration 
 ****************************************************************************/
#ifndef chipDefaultNandPortNum
UINT16 NEAR chipDefaultNandPortNum (void);
#endif

#ifndef chipDefaultNandPll
UINT32 NEAR chipDefaultNandPll (void);
#endif

#ifndef chipDefaultNandPll2
UINT32 NEAR chipDefaultNandPll2 (void);
#endif

#ifndef chipDefaultNandClearMode
UINT16 NEAR chipDefaultNandClearMode (void);
#endif

#ifndef chipDefaultNandNumColumnAddrBytes
UINT16 chipDefaultNandNumColumnAddrBytes (void);
#endif

#ifndef chipDefaultNandNumRowAddrBytes
UINT16 chipDefaultNandNumRowAddrBytes (void);
#endif

#ifndef chipDefaultNandNumDataBytesPerPage
UINT32 chipDefaultNandNumDataBytesPerPage (void);
#endif

#ifndef chipDefaultNandNumPagesPerBlock
UINT32 chipDefaultNandNumPagesPerBlock (void);
#endif

#ifndef chipDefaultNandBusWidth
UINT16 chipDefaultNandBusWidth (void);
#endif

#ifndef chipDefaultNandNumSpareBytesPerPage
UINT16 chipDefaultNandNumSpareBytesPerPage (void);
#endif


#ifndef chipDefaultNandcsNum
UINT16 NEAR chipDefaultNandcsNum (void);
#endif
  
#ifndef chipDefaultNandFirstBlock
UINT16 NEAR chipDefaultNandFirstBlock (void);
#endif

#ifndef chipSystemNand
void chipSystemNand(void);
#endif
        
/****************************************************************************
 * Generic dummy function 
 ****************************************************************************/
#ifndef chipDummy
void NEAR chipDummy (void *dummy);
#endif

/****************************************************************************
 * PCI auto-initialization status. Returns True if pci auto-initialization
 * is required.
 ****************************************************************************/
#ifndef chipIsPciEeai
bool NEAR chipIsPciEeai (void);
#endif

/****************************************************************************
 * Chip sleep. The device idles until the specified event occurs.
 ****************************************************************************/
#ifndef chipSleepUntilEvent
void NEAR chipSleepUntilEvent (UINT16 event, BOOL bootMaster);
#endif


/****************************************************************************
 * Chip event branch address. Where to branch to on an event wakeup
 ****************************************************************************/
#ifndef chipEventExitAddress
UINT32 NEAR chipEventExitAddress (void);
#endif

/****************************************************************************
 * Emif boot exit address. Where to boot to on emif boot
 ****************************************************************************/
#ifndef chipEmifBootAddress
void NEAR chipEmifBootAddress (void);
#endif

/****************************************************************************
 * Emif enable
 ****************************************************************************/
#ifndef chipPowerEmif4
 SINT32 NEAR chipPowerEmif4 (void);
#endif

/****************************************************************************
 * Chip Pll setup 
 ****************************************************************************/
#ifndef chipConfigPll
SINT16 NEAR chipConfigPll (UINT32 pllNum, UINT32 prediv, UINT32 mult, UINT32 postdiv, UINT32 sysFreqMhz, UINT32 coreFreqMhz);
#endif

#ifndef chipDisablePll
SINT16 NEAR chipDisablePll (UINT32 pllNum);
#endif

#ifndef chipGetPllState
UINT16 NEAR chipGetPllState (UINT32 pllNum);
#endif

#ifndef chipPllLookup
UINT32 NEAR chipPllLookup (UINT32 freqBits, UINT32 selectBits, UINT32 postdivVal);
#endif


/*****************************************************************************
 * Function to read a 32 bit word. Used on 64x to read non-aligned words
 *****************************************************************************/
#ifndef chipReadUint32
UINT32 NEAR chipReadUint32 (void *x);
#endif

/*****************************************************************************
 * The initial I2C boot parameter block address in ROM
 *****************************************************************************/
#ifndef chipGetI2CBaseBootParamsAddr
UINT16 NEAR chipGetI2CBaseBootParamsAddr (void);
#endif

/*****************************************************************************
 * Boot Table padding (hex conversion tools dependent)
 *****************************************************************************/
#ifndef chipAddBtblUint16Pad
UINT32 NEAR chipAddBtblUint16Padd (UINT32 x);
#endif

/*****************************************************************************
 * Read the device id and variant from the device ID or jtag ID register
 *****************************************************************************/
#ifndef chipGetPartIdVariant
void NEAR chipGetPartIdVariant (UINT32 *partId, UINT32 *variant);
#endif

/*****************************************************************************
 * Memory padding required at the front of the boot table buffer for
 * device specific processing/alignment.
 *****************************************************************************/
#ifndef CHIP_BTBL_RSVD_SIZE_UINT16
#define CHIP_BTBL_RSVD_SIZE_UINT16     0
#endif

/*****************************************************************************
 * Local/Global address translations.
 *****************************************************************************/
#ifndef chipMapLocalToGlobal
UINT32 NEAR chipMapLocalToGlobal (UINT32 local);
#endif

#ifndef chipMapGlobalToLocal
UINT32 NEAR chipMapGlobalToLocal (UINT32 global);
#endif

#ifndef chipFormGlobal
UINT32 NEAR chipFormGlobal (UINT32 core, UINT32 local);
#endif

/********************************************************************************
 * Stack pointer reset
 ********************************************************************************/
#ifndef chipResetStack
void NEAR chipResetStack (void);
#endif

/********************************************************************************
 * A small stack is used for some boot modes. If not available this is defined
 * to an empty statement
 ********************************************************************************/
#ifndef chipSwitchToSmallStack
void NEAR chipSwitchToSmallStack (void);
#endif


/********************************************************************************
 * Internal chip register for boot tracking.
 ********************************************************************************/
#ifndef chipInitStatusReg
void NEAR chipInitStatusReg (UINT32 initVal);
#endif

#ifndef chipUpdateStatus
UINT32 NEAR chipUpdateStatus (UINT32 errLevel, UINT32 status);
#endif

#ifndef chipStatusNewMode
UINT32 NEAR chipStatusNewMode (void *bparams);
#endif

#ifndef chipPromoteBootStatus
UINT32 NEAR chipPromoteBootStatus (UINT32 status);
#endif


/******************************************************************************
 * Device level enable functions. These are used to configure chip level
 * pulls on pins that are not part of the peripheral registers set, but the
 * device register set.
 ******************************************************************************/
#ifndef chipLevelMacEnable
void NEAR chipLevelMacEnable (UINT16 port);
#endif
 
#ifndef chipLevelUtopiaEnable
void NEAR chipLevelUtopiaEnable (UINT16 busWidthBits);
#endif

#ifndef chipLevelHpiEnable
void NEAR chipLevelHpiEnable (void);
#endif

/******************************************************************************
 * Endian swap functions
 ******************************************************************************/
#ifndef chipEndianSwap32
UINT32 NEAR chipEndianSwap32 (UINT32 a);
#endif

/******************************************************************************
 * Macros to read formatted values from a big endian word stream 
 ******************************************************************************/
#ifndef chipReadUint32FromBeWordStream
UINT32 NEAR chipReadUint32FromBeWordStream (word *w);
#endif

#ifndef chipCopyBEWordStreamToUint16Stream
void NEAR chipCopyBEWordStreamToUint16Stream (UINT16 *dest, word *src, UINT32 numWords);
#endif

/*******************************************************************************
 * Macros to indicate that the DSP is ready to receive data
 *******************************************************************************/
#ifndef chipIndReadyToHost
void NEAR chipIndReadyToHost (void);
#endif

/*********************************************************************************
 * Ethernet driver Delay. Used if a delay is required between mac enable and
 * first packet transmission
 *********************************************************************************/
#ifndef chipEthTxEnableDelay
void NEAR chipEthTxEnableDelay(void);
#endif

/********************************************************************************
 * PCIe mode
 ********************************************************************************/
#ifndef chipVerifyPcieBootMode
SINT16 NEAR chipVerifyPcieBootMode (UINT32 portNum);
#endif

#ifndef chipRoutePcieInterrupt
void NEAR chipRoutePcieInterrupt (UINT32 portNum);
#endif

#ifndef chipClearPcieInterrupt
void NEAR chipClearPcieInterrupt (UINT32 portNum);
#endif

#ifndef chipDefaultPciePort
UINT16 NEAR chipDefaultPciePort (void);
#endif

#ifndef chipDefaultPciePll
UINT32 NEAR chipDefaultPciePll (void);
#endif

#ifndef chipDefaultPcieOptions
UINT16 NEAR chipDefaultPcieOptions (void);
#endif

#ifndef chipDefaultPcieAddressWidth
UINT16 NEAR chipDefaultPcieAddressWidth (void);
#endif

#ifndef chipDefaultPcieLinkRateMhz
UINT16 NEAR chipDefaultPcieLinkRateMhz (void);
#endif

#ifndef chipDefaultPcieRefClock10kHz
UINT16 NEAR chipDefaultPcieRefClock10kHz (void);
#endif

#ifndef chipDefaultPcieWindowSize
UINT16 NEAR chipDefaultPcieWindowSize (UINT32 win);
#endif

#ifndef chipDefaultPcieWindow0Size
UINT16 NEAR chipDefaultPcieWindow0Size (void);
#endif

#ifndef chipDefaultPcieWindow1Size
UINT16 NEAR chipDefaultPcieWindow1Size (void);
#endif

#ifndef chipDefaultPcieWindow2Size
UINT16 NEAR chipDefaultPcieWindow2Size (void);
#endif

#ifndef chipDefaultPcieWindow3Size
UINT16 NEAR chipDefaultPcieWindow3Size (void);
#endif

#ifndef chipDefaultPcieWindow4Size
UINT16 NEAR chipDefaultPcieWindow4Size (void);
#endif

#ifndef chipDefaultPcieWindow5Size
UINT16 NEAR chipDefaultPcieWindow5Size (void);
#endif

#ifndef chipDefaultPcieSerdesCfg
UINT32 NEAR chipDefaultPcieSerdesCfg (void);
#endif

#ifndef chipDefaultPcieLane0Cfg
UINT32 NEAR chipDefaultPcieLane0Cfg (void);
#endif

#ifndef chipStatusPcieCfgInvalid
void NEAR chipStatusPcieCfgInvalid (void);
#endif

#ifndef chipStatusPcieModeInvalid
void NEAR chipStatusPcieModeInvalid (void);
#endif

#ifndef chipInitPcieSerdesVal
UINT32 NEAR chipInitPcieSerdesVal (void);
#endif

#ifndef chipPcieEventOccurredj
BOOL NEAR chipPcieEventOccurred (void);
#endif

#ifndef chipPcieTimerSetup
void NEAR chipPcieTimerSetup (UINT32 timeoutSeconds);
#endif

#ifndef chipPcieTimerExpired
BOOL NEAR chipPcieTimerExpired (void);
#endif

#ifndef chipPcieTimerDisable
void NEAR chipPcieTimerDisable (void);
#endif

#ifndef chipPcieDeviceVendorId
UINT32 NEAR chipPcieDeviceVendorId (void);
#endif

#ifndef chipStatusPcieTimeOut
void NEAR chipStatusPcieTimeOut(void);
#endif

#ifndef chipPcieSystemConfig
SINT32 NEAR chipPcieSystemConfig (void *params, BOOL *lockDetected);
#endif

#ifndef chipStatusPcieIncWakeCount
void NEAR chipStatusPcieIncWakeCount(void);
#endif

#ifndef chipIsPcieMuxSet
BOOL NEAR chipIsPcieMuxSet (UINT32 portNum);
#endif


/*********************************************************************************
 * EMIF mode
 *********************************************************************************/
#ifndef chipDefaultEmifPll
UINT32 NEAR chipDefaultEmifPll (UINT16 key);
#endif

#ifndef chipDefaultEmifOptions
UINT16 NEAR chipDefaultEmifOptions (UINT16 key);
#endif

#ifndef chipDefaultEmifType
UINT16 NEAR chipDefaultEmifType (UINT16 key);
#endif

#ifndef chipDefaultEmifBranchAddr
UINT32 NEAR chipDefaultEmifBranchAddr (UINT16 key);
#endif

#ifndef chipDefaultCsNum
UINT16 NEAR chipDefaultEmifCsNum (UINT16 key);
#endif

#ifndef chipDefaultMemWidth
UINT16 NEAR chipDefaultEmifMemWidth (UINT16 key);
#endif

#ifndef chipDefaultEmifNorWaitEnable
UINT16 NEAR chipDefaultEmifNorWaitEnable (UINT16 key);
#endif

#ifndef chipDefaultEmifNorAsyncCfg
UINT32 NEAR chipDefaultEmifNorAsyncCfg (UINT16 key);
#endif

#ifndef chipEmif25DataSizeBytes
UINT32 NEAR chipEmif25DataSizeBytes (void);
#endif

#ifndef chipDefaultEmif4Table
void NEAR chipDefaultEmif4Table (void *vtbl);
#endif

#ifndef chipEmif25Init
void NEAR chipEmif25Init (void);
#endif

/*********************************************************************************
 * VUSR mode
 *********************************************************************************/
#ifndef chipDefaultHyperSerdesCfg
UINT32 NEAR chipDefaultHyperSerdesCfg (void);
#endif

#ifndef chipDefaultHyperSerdesCfgRxLane0
UINT32 NEAR chipDefaultHyperSerdesCfgRxLane0 (void);
#endif

#ifndef chipDefaultHyperSerdesCfgRxLane1
UINT32 NEAR chipDefaultHyperSerdesCfgRxLane1 (void);
#endif

#ifndef chipDefaultHyperSerdesCfgRxLane2
UINT32 NEAR chipDefaultHyperSerdesCfgRxLane2 (void);
#endif

#ifndef chipDefaultHyperSerdesCfgRxLane3
UINT32 NEAR chipDefaultHyperSerdesCfgRxLane3 (void);
#endif

#ifndef chipDefaultHyperSerdesCfgTxLane0
UINT32 NEAR chipDefaultHyperSerdesCfgTxLane0 (void);
#endif

#ifndef chipDefaultHyperSerdesCfgTxLane1
UINT32 NEAR chipDefaultHyperSerdesCfgTxLane1 (void);
#endif

#ifndef chipDefaultHyperSerdesCfgTxLane2
UINT32 NEAR chipDefaultHyperSerdesCfgTxLane2 (void);
#endif

#ifndef chipDefaultHyperSerdesCfgTxLane3
UINT32 NEAR chipDefaultHyperSerdesCfgTxLane3 (void);
#endif

#ifndef chipDefaultHyperPort
UINT16 NEAR chipDefaultHyperPort (void);
#endif

#ifndef chipDefaultHyperPll
UINT32 NEAR chipDefaultHyperPll (void);
#endif

#ifndef chipDefaultHyperPll2
UINT32 NEAR chipDefaultHyperPll2 (void);
#endif

#ifndef chipDefaultHyperOptions
UINT16 NEAR chipDefaultHyperOptions (void);
#endif

#ifndef chipDefaultHyperNlanes
UINT16 NEAR chipDefaultHyperNlanes (void);
#endif

#ifndef chipHyperSystemConfig
SINT32 NEAR chipHyperSystemConfig (void *params);
#endif

#ifndef chipConfigHyperSerdes
void NEAR chipConfigHyperSerdes (void *vparams);
#endif


/*********************************************************************************
 * VUSR defs
 *********************************************************************************/
#ifndef chipRouteHyperInterrupt
void NEAR chipRouteHyperInterrupt (UINT16 port);
#endif

#ifndef chipClearHyperInterrupt
void NEAR chipClearHyperInterrupt (UINT16 port);
#endif

#ifndef chipStatusHyperSerdesFail
void NEAR chipStatusHyperSerdesFail(void);
#endif

#ifndef chipStatusHyperSetupFail
void NEAR chipStatusHyperSetupFail (void);
#endif

#ifndef chipStatusHyperTimeout
void chipStatusHyperTimeout (void);
#endif


/*********************************************************************************
 * SPI defs
 *********************************************************************************/
#ifndef chipDefaultSpiPortNum
UINT16 NEAR chipDefaultSpiPortNum(void);
#endif

#ifndef chipDefaultSpiPll
UINT32 NEAR chipDefaultSpiPll(void);
#endif

#ifndef chipDefaultSpiOptions
UINT16 NEAR chipDefaultSpiOptions(void);
#endif

#ifndef chipDefaultSpiAddrWidth
UINT16 NEAR chipDefaultSpiAddrWidth(void);
#endif

#ifndef chipDefaultSpiNPins
UINT16 NEAR chipDefaultSpiNPins(void);
#endif

#ifndef chipDefaultSpiCsel
UINT16 NEAR chipDefaultSpiCsel(void);
#endif

#ifndef chipDefaultSpiMode
UINT16 NEAR chipDefaultSpiMode(void);
#endif

#ifndef chipDefaultSpiSysFreqMhz
UINT16 NEAR chipDefaultSpiSysFreqMhz(void);
#endif

#ifndef chipDefaultSpiBusFreqMhz
UINT16 NEAR chipDefaultSpiBusFreqMhz(void);
#endif

#ifndef chipDefaultSpiBusFreqKhz
UINT16 NEAR chipDefaultSpiBusFreqKhz(void);
#endif

#ifndef chipDefaultSpiReadAddr
UINT32 NEAR chipDefaultSpiReadAddr(void);
#endif

#ifndef chipStatusSpiSetupFail
void NEAR chipStatusSpiSetupFail(void);
#endif

#ifndef chipUpdateSpiAddress
void NEAR chipUpdateSpiAddress(UINT32 addr);
#endif

#ifndef chipIncSpiRetries
void NEAR chipIncSpiRetries(void);
#endif

#ifndef chipDefaultSpiNextCsel
UINT16 NEAR chipDefaultSpiNextCsel(void);
#endif

#ifndef chipDefaultSpiNextReadAddr
UINT32 NEAR chipDefaultSpiNextReadAddr(void);
#endif

#ifndef chipDefaultSpiC2tDelay
UINT16 NEAR chipDefaultSpiC2tDelay(void);
#endif

#ifndef chipDefaultSpiCoreFreqMhz
UINT16 NEAR chipDefaultSpiCoreFreqMhz (void);
#endif

#ifndef chipSpiInit
void NEAR chipSpiInit (UINT16 port);
#endif

/*********************************************************************************
 * Uart defs
 *********************************************************************************/
#ifndef chipDefaultUartPort
UINT16 NEAR chipDefaultUartPort(void);
#endif

#ifndef chipDefaultUartPll
UINT32 NEAR chipDefaultUartPll (void);
#endif

#ifndef chipDefaultUartOptions
UINT16 NEAR chipDefaultUartOptions(void);
#endif

#ifndef chipDefaultUartProtocol
UINT16 NEAR chipDefaultUartProtocol(void);
#endif

#ifndef chipDefaultUartDataFormat
UINT16 chipDefaultUartDataFormat(void);
#endif

#ifndef chipDefaultUartInitialNackCount
UINT16 NEAR chipDefaultUartInitialNackCount(void);
#endif

#ifndef chipDefaultUartNackTimeoutSec
UINT16 NEAR chipDefaultUartNackTimeoutSec(void);
#endif

#ifndef chipDefaultUartCharTimeoutMsec
UINT16 NEAR chipDefaultUartCharTimeoutMsec(void);
#endif

#ifndef chipDefaultUartNDataBits
UINT16 NEAR chipDefaultUartNDataBits(void);
#endif

#ifndef chipDefaultUartParity
UINT16 NEAR chipDefaultUartParity(void);
#endif
    
#ifndef chipDefaultUartNStopBitsx2
UINT16 NEAR chipDefaultUartNStopBitsx2(void);
#endif
    
#ifndef chipDefaultUartOverSampleFactor
UINT16 NEAR chipDefaultUartOverSampleFactor(void);
#endif

#ifndef chipDefaultUartFlowControl
UINT16 NEAR chipDefaultUartFlowConrol(void);
#endif

#ifndef chipDefaultUartDataRate
UINT32 NEAR chipDefaultUartDataRate(void);
#endif

#ifndef chipDefaultUartMaxErrCount
UINT16 NEAR chipDefaultUartMaxErrCount(void);
#endif

#ifndef chipStatusUartErr
void NEAR chipStatusUartErr(void);
#endif

#ifndef chipUartTimerSetup
void NEAR chipUartTimerSetup (UINT32 miliseconds, UINT32 refClkMhz);
#endif

#ifndef chipUartTimerExpired
BOOL NEAR chipUartTimerExpired(void);
#endif

#ifndef chipUartTimerDisable
void NEAR chipUartTimerDisable (void);
#endif

#ifndef chipStatusUartInitFail
void NEAR chipStatusUartInitFail (void);
#endif

#ifndef chipStatusUartInitSuccess
void NEAR chipStatusUartInitSuccess(void);
#endif

#ifndef chipStatusUartIncPingCount
void NEAR chipStatusUartIncPingCount(void);
#endif

#ifndef chipStatusUartIncCmdTimeout
void NEAR chipStatusUartIncCmdTimeout(void);
#endif

#ifndef chipStatusUartIncCharTimeout
void NEAR chipStatusUartIncCharTimeout(void);
#endif

#ifndef chipStatusUartIncCrcErr
void NEAR chipStatusUartIncCrcErr(void);
#endif

#ifndef chipStatusUartIncGoodFrames
void NEAR chipStatusUartIncGoodFrames(void);
#endif

#ifndef chipUartInit
void NEAR chipUartInit (UINT16 port);
#endif

/*********************************************************************************
 * QM defs 
 *********************************************************************************/
#ifndef chipDisableQm
void NEAR chipDisableQm (void *vparams);
#endif

/*********************************************************************************
 * Switch to a small stack
 *********************************************************************************/
#ifndef chipSwitchToSmallStack
void NEAR chipSwitchToSmallStack (void);
#endif

/*********************************************************************************
 * DDR3 configuration
 *********************************************************************************/
#ifndef mainGetExtMemParams
SINT16 NEAR mainGetExtMemParams(void);
#endif

#ifndef mainExtMemConfig
SINT16 NEAR mainExtMemConfig(void);
#endif

#ifndef chipPowerEmif
SINT16 NEAR chipPowerEmif(void);
#endif

#ifndef chipDefaultEmif4configSelect
UINT32 NEAR chipDefaultEmif4configSelect(void);
#endif

#ifndef chipDefaultEmif4sdRamConfig
UINT32 NEAR chipDefaultEmif4sdRamConfig(void);
#endif

#ifndef chipDefaultEmif4sdRamConfig2
UINT32 NEAR chipDefaultEmif4sdRamConfig2(void);
#endif

#ifndef chipDefaultEmif4sdRamRefreshCtl
UINT32 NEAR chipDefaultEmif4sdRamRefreshCtl(void);
#endif

#ifndef chipDefaultEmif4sdRamTiming1
UINT32 NEAR chipDefaultEmif4sdRamTiming1(void);
#endif

#ifndef chipDefaultEmif4sdRamTiming2
UINT32 NEAR chipDefaultEmif4sdRamTiming2(void);
#endif

#ifndef chipDefaultEmif4sdRamTiming3
UINT32 NEAR chipDefaultEmif4sdRamTiming3(void);
#endif

#ifndef chipDefaultEmif4lpDdrNumTiming
UINT32 NEAR chipDefaultEmif4lpDdrNumTiming(void);
#endif

#ifndef chipDefaultEmif4powerManageCtl
UINT32 NEAR chipDefaultEmif4powerManageCtl(void);
#endif

#ifndef chipDefaultEmif4iODFTTestLogic
UINT32 NEAR chipDefaultEmif4iODFTTestLogic(void);
#endif

#ifndef chipDefaultEmif4performCountCfg
UINT32 NEAR chipDefaultEmif4performCountCfg(void);
#endif


#ifndef chipDefaultEmif4performCountMstRegSel
UINT32 NEAR chipDefaultEmif4performCountMstRegSel(void);
#endif

#ifndef chipDefaultEmif4readIdleCtl
UINT32 NEAR chipDefaultEmif4readIdleCtl(void);
#endif

#ifndef chipDefaultEmif4sysVbusmIntEnSet
UINT32 NEAR chipDefaultEmif4sysVbusmIntEnSet(void);
#endif

#ifndef chipDefaultEmif4sdRamOutImpdedCalCfg
UINT32 NEAR chipDefaultEmif4sdRamOutImpdedCalCfg(void);
#endif

#ifndef chipDefaultEmif4tempAlterCfg
UINT32 NEAR chipDefaultEmif4tempAlterCfg(void);
#endif

#ifndef chipDefaultEmif4ddrPhyCtl1
UINT32 NEAR chipDefaultEmif4ddrPhyCtl1(void);
#endif

#ifndef chipDefaultEmif4ddrPhyCtl2
UINT32 NEAR chipDefaultEmif4ddrPhyCtl2(void);
#endif

#ifndef chipDefaultEmif4priClassSvceMap
UINT32 NEAR chipDefaultEmif4priClassSvceMap(void);
#endif

#ifndef chipDefaultEmif4mstId2ClsSvce1Map
UINT32 NEAR chipDefaultEmif4mstId2ClsSvce1Map(void);
#endif

#ifndef chipDefaultEmif4mstId2ClsSvce2Map
UINT32 NEAR chipDefaultEmif4mstId2ClsSvce2Map(void);
#endif

#ifndef chipDefaultEmif4eccCtl
UINT32 NEAR chipDefaultEmif4eccCtl(void);
#endif

#ifndef chipDefaultEmif4eccRange1
UINT32 NEAR chipDefaultEmif4eccRange1(void);
#endif

#ifndef chipDefaultEmif4eccRange2
UINT32 NEAR chipDefaultEmif4eccRange2(void);
#endif

#ifndef chipDefaultEmif4rdWrtExcThresh
UINT32 NEAR chipDefaultEmif4rdWrtExcThresh(void);
#endif

#ifndef chipCfgDdrPll
SINT16 NEAR chipCfgDdrPll (UINT32 base, UINT16 prediv, UINT16 mult, UINT16 postdiv, UINT32 chipFreqMhz, UINT32 pllFreqMhz);
#endif

#ifndef chipEmifCfg
void NEAR chipEmifCfg (void);   /* Check to see if the emif configuration table has been done */
#endif

#ifndef chipDdr3FirstEnable
void NEAR chipDdr3FirstEnable (UINT32 base);
#endif

/*********************************************************************************
 * Post boot table block processing. A function to call after every boot table
 * block has been processed.
 *********************************************************************************/
#ifndef chipBtblBlockDone
SINT16 NEAR chipBtblBlockDone(void);
#endif

/*********************************************************************************
 * Return the status as boot master
 *********************************************************************************/
#ifndef chipIsBootMaster
BOOL NEAR chipIsBootMaster (BOOL sdev);
#endif

/**********************************************************************************
 * Branch to the rom re-entry point
 **********************************************************************************/
#ifndef chipBootReentry
void NEAR chipBootReentry (void);
#endif

/**********************************************************************************
 * Bootp functions
 **********************************************************************************/
#ifndef chipBootpTimerSetup
void NEAR chipBootpTimerSetup (UINT32 refFreqMhz, UINT32 timeoutMilliSeconds);
#endif

#ifndef chipBootpTimerExpired
BOOL NEAR chipBootpTimerExpired (void);
#endif

#ifndef chipBootpTimerDisable
void NEAR chipBootpTimerDisable (void);
#endif

#ifndef chipBootpTimerReset
void NEAR chipBootpTimerReset (void);
#endif

#ifndef chipBootpTimerDeltaMs
UINT32 NEAR chipBootpTimerDeltaMs (UINT32 refFreqMhz);
#endif

#ifndef chipDefaultBootpDevString
void NEAR chipDefaultBootpDevString (UINT16 *dst, UINT32 sizeUint16);
#endif

#ifndef chipDefaultBootpIdString
void NEAR chipDefaultBootpIdString (UINT16 *dst, UINT32 sizeUint16);
#endif

#ifndef chipGetDefaultBootpSgmiiParams
void NEAR chipGetDefaultBootpSgmiiParams (UINT32 *txCfg, UINT32 *rxCfg, UINT32 *auxCfg, UINT16 *adv, UINT16 *ctl);
#endif

#ifndef chipDefaultBootpPktPll
UINT32 NEAR chipDefaultBootpPktPll (void);
#endif

#ifndef chipSendPacket
SINT32 NEAR chipSendPacket(void *pkt, UINT32 pktLenBytes);
#endif

#ifndef chipDefaultBootpOptions
UINT16 NEAR chipDefaultBootpOptions (void);
#endif

/************************************************************************************************
 * Timer functions
 ************************************************************************************************/
#ifndef chipTimerSetupSeconds
void NEAR chipTimerSetupSeconds (UINT32 timeoutSeconds, UINT32 refClkMhz);
#endif

#ifndef chipTimerSetupMiliSeconds
void NEAR chipTimerSetupMiliSeconds (UINT32 timeoutMiliSeconds, UINT32 refClkMhz);
#endif

#ifndef chipTimerExpired
BOOL NEAR chipTimerExpired (void);
#endif

#ifndef chipTimerDisable
void NEAR chipTimerDisable (void);
#endif

#ifndef chipTimerGetLsw
UINT32 NEAR chipTimerGetLsw (void);
#endif

/************************************************************************************************
 * Non aligned 32bit word stores / reads
 ************************************************************************************************/
#ifndef chipStoreWord
void NEAR chipStoreWord (UINT32 *addr, UINT32 value);
#endif

#ifndef chipReadWord
UINT32 NEAR chipReadWord (UINT32 *addr);
#endif

/************************************************************************************************
 * boot memory sanity check
 ************************************************************************************************/
#ifndef chipSanityCheckMemRange
BOOL NEAR chipSanityCheckMemRange (UINT32 start, UINT32 sizeBytes);
#endif

/************************************************************************************************
 * Cache control
 ************************************************************************************************/
#ifndef chipFlushCache
void NEAR chipFlushCache (void);
#endif

#ifndef chipInvalidateCache
void NEAR chipInvalidateCache (UINT32 addr);
#endif

/************************************************************************************************
 * Hardware device reset
 ************************************************************************************************/
#ifndef chipHwReset
void NEAR chipHwReset (void);
#endif

/************************************************************************************************
 * Interrupt control
 ************************************************************************************************/
#ifndef chipDisableInts
void NEAR chipDisableInts (void);
#endif

/************************************************************************************************
 * Phy configuration
 ************************************************************************************************/
#ifndef chipConfigEmif4Phy
SINT32 NEAR chipConfigEmif4Phy (void *vtbl);
#endif

/************************************************************************************************
 * DDR3 configuration
 ************************************************************************************************/
#ifndef chipConfigEmif4Phy
SINT32 chipConfigEmif4Phy (void *emif4Table);
#endif

/************************************************************************************************
 * cache calls
 ************************************************************************************************/

#ifndef chipInvCache
UINT16 NEAR chipInvCache(UINT32 addr, UINT32 sizeBytes);
#endif

#ifndef chipCacheWriteBack
UINT16 NEAR chipCacheWriteBack(UINT32 addr, UINT32 sizeBytes);
#endif




#endif /* _CHIP_H */

/* Nothing past this point */
