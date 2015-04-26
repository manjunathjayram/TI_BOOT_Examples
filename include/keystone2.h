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
 
#ifndef _KEYSTONE_H
#define _KEYSTONE_H
/***********************************************************************************
 * FILE PURPOSE: Provide Keystone boot specific definitions
 ***********************************************************************************
 * FILE NAME: keystone.h
 *
 * DESCRIPTION: Public API definition for chip dependent functions
 *
 ***********************************************************************************/

/* System header files */
#include "types.h"

#ifdef _CHIP_H
#error chip.h should not be included before keystone.h
#endif

/******************************************************************************
 * Boot Mode Values (not the values latched into devstat)
 ******************************************************************************/
#define BOOT_MODE_ETH               10
#define BOOT_MODE_RAPIDIO           20
#define BOOT_MODE_PCIE              30
#define BOOT_MODE_I2C               40
#define BOOT_MODE_I2C_PASSIVE       41
#define BOOT_MODE_I2C_MASTER_WRITE  42
#define BOOT_MODE_SPI               50
#define BOOT_MODE_VUSR              60
#define BOOT_MODE_EMIF25            70
#define BOOT_MODE_NAND              80
#define BOOT_MODE_BOOTP_TFTP        90
#define BOOT_MODE_SLEEP            100
#define BOOT_MODE_UART             110
#define BOOT_MODE_ERR              120
#define BOOT_MODE_HIB_RECOVERY     130



/****************************************************************************
 * DEVSTAT Field Definitions
 ****************************************************************************/
 
/* Bit 22 is the ARM endian configuration bit */
#define DEVSTAT_BITS_ARM_ENDIAN_MSB     22
#define DEVSTAT_BITS_ARM_ENDIAN_LSB     22
#define DEVSTAT_FIELD_ARM_ENDIAN_BIG     0
#define DEVSTAT_FIELD_ARM_ENDIAN_LITTLE  1


/* Bit 19 is the PLL postdiv selection value. 
 * The value 0 means divide by 2 (the default)
 * the value 1 means divide by 1 (backup in case of PLL problem) */
#define DEVSTAT_BITS_PLL_POSTDIV_SEL_MSB    19
#define DEVSTAT_BITS_PLL_POSTDIV_SEL_LSB    19
#define DEVSTAT_FIELD_POSTDIV_2             0
#define DEVSTAT_FIELD_POSTDIV_1             1

 
 
/* System endian */
#define DEVSTAT_BITS_ENDIAN_MSB             0
#define DEVSTAT_BITS_ENDIAN_LSB             0
#define DEVSTAT_FIELD_ENDIAN_BIG_ENDIAN     0
#define DEVSTAT_FIELD_ENDIAN_LITTLE_ENDIAN  1
 
/* Boot master */
#define DEVSTAT_BITS_BOOT_MASTER_MSB     8
#define DEVSTAT_BITS_BOOT_MASTER_LSB     8
#define DEVSTAT_FIELD_BOOT_MASTER_ARM    0
#define DEVSTAT_FIELD_BOOT_MASTER_GEM    1

/* System PLL, for all modes that configure the PLL */
#define DEVSTAT_BITS_SYS_PLL_MSB     7
#define DEVSTAT_BITS_SYS_PLL_LSB     5

/* ARM PLL, for all modes that configure the ARM PLL */
#define DEVSTAT_BITS_ARM_PLL_MSB                11
#define DEVSTAT_BITS_ARM_PLL_LSB                 9

/* Sub field boot device selections */
#define DEVSTAT_BITS_BOOTDEV_XIP_NAND_SEL_MSB  16
#define DEVSTAT_BITS_BOOTDEV_XIP_NAND_SEL_LSB  16
#define DEVSTAT_FIELD_BOOTDEV_SEL_XIP           0
#define DEVSTAT_FIELD_BOOTDEV_SEL_NAND          1

#define DEVSTAT_BITS_BOOTDEV_PCIE_HYPER_SEL_MSB   4
#define DEVSTAT_BITS_BOOTDEV_PCIE_HYPER_SEL_LSB   4
#define DEVSTAT_FIELD_BOOTDEV_SEL_PCIE            0
#define DEVSTAT_FIELD_BOOTDEV_SEL_HYPERLINK       1

#define DEVSTAT_BITS_SLEEP_I2C_SLAVE_SEL_MSB     14
#define DEVSTAT_BITS_SLEEP_I2C_SLAVE_SEL_LSB     14
#define DEVSTAT_FIELD_SLEEP_I2C_SLAVE_SEL_SLEEP   0
#define DEVSTAT_FIELD_SLEEP_I2C_SLAVE_SEL_I2CS    1

/* Minimum pin configuration pin */
#define DEVSTAT_BITS_MIN_PIN_MSB                  4
#define DEVSTAT_BITS_MIN_PIN_LSB                  4
#define DEVSTAT_FIELD_MIN_PIN_NOT_ENABLED         0
#define DEVSTAT_FIELD_MIN_PIN_ENABLED             1


/* PLL Default values (do not apply to I2C master or SPI min mode) */
#define DEVICE_SYS_PLL_MIN_SELECT_VAL               4       /* 156.25 MHz ref clock is pin select 4 */
#define DEVICE_ARM_PLL_MIN_SELECT_VAL               4       /* 156.25 MHz ref clock is pin select 4 */


/* I2c passive min pin default values */
#define DEVICE_I2C_PASSIVE_MIN_DEFAULT_PORT     0
 
/* I2c master min pin default values */
#define DEVICE_I2C_MIN_DEFAULT_PORT                 0
#define DEVICE_I2C_MIN_DEFAULT_PARAM_INDEX          0    /* The index value, not the byte address */
#define DEVICE_I2C_MIN_DEFAULT_GP_OFFSET_IDX        0    /* The index value, not the byte address */
#define DEVICE_I2C_MIN_DEFAULT_BUS_ADDR             0x50
#define DEVICE_I2C_MIN_DEFAULT_OWN_ID               0x10

/* Eth/Bootp min pin default values */
#define DEVICE_ETH_MIN_DEFAULT_PA_REF_IDX         8    /* This corresponds to a 125 MHz PA ref clock */
#define DEVICE_ETH_MIN_DEFAULT_EXT_CON_IDX        1    /* Slave, with auto negotiation */
#define DEVICE_ETH_MIN_DEFAULT_SERDES_REF_IDX     0    /* The default is a 125 MHz serdes reference clock */

/* SPI min pin default values */
#define DEVICE_SPI_MIN_DEFAULT_WIDTH              1       /* Default is 24 bit address width */
#define DEVICE_SPI_MIN_DEFAULT_NPIN               1       /* Default is to drive the max number of pins */
#define DEVICE_SPI_MIN_DEFAULT_CSEL               0xfffe  /* CS0 is the default (bit 0 set to 0) */
#define DEVICE_SPI_MIN_DEFAULT_MODE               2       /* Data output on rising clock edge, latched on falling edge */
#define DEVICE_SPI_MIN_DEFAULT_PORT               0

/* NAND min pin default values */
#define DEVICE_NAND_MIN_DEFAULT_CLEAR             BOOT_PARAMS_NAND_OPTIONS_NOT_CLEAR
#define DEVICE_NAND_MIN_DEFAULT_FIRST_BLOCK       0
#define DEVICE_NAND_MIN_DEFAULT_CS                BOOT_PARAMS_NAND_CS_2

/* SRIO min pin default values */
#define DEVICE_SRIO_MIN_DEFAULT_LANE              BOOT_PARAMS_RIO_LPS_1X_1X_1X_1X
#define DEVICE_SRIO_MIN_DEFAULT_REF_CLKx100       15625
#define DEVICE_SRIO_MIN_DEFAULT_RATE_MHZ          5000

/* UART min pin default values */
#define DEVICE_UART_MIN_DEFAULT_PORT              0

/****************************************************************************
 * The PWRSTATECTL Register bit fields are defined by the boot ROM and 
 * have the following fields defined.
 ****************************************************************************
/-----------------------------------------------------------------------------------------------------------------------\
|  31               10 |   9   |  8   |       7      | 6               5  | 4             3 |   2  |     1       |  0   |
| Post Hib Branch Addr | width | wait | recov master | local reset action | stored SR index | mode | hibernation | rsvd |
\-----------------------------------------------------------------------------------------------------------------------/
***/

#define PWRSTATECTL_BITS_BRANCH_MSB                 31
#define PWRSTATECTL_BITS_BRANCH_LSB                 10

#define PWRSTATECTL_BITS_LOCAL_RESET_ACTION_MSB      6
#define PWRSTATECTL_BITS_LOCAL_RESET_ACTION_LSB      5
#define PWRSTATECTL_FIELD_LRESET_SLEEP               0
#define PWRSTATECTL_FIELD_LRESET_BASE_MSMC           1
#define PWRSTATECTL_FIELD_LRESET_BASE_DDR            2
#define PWRSTATECTL_FIELD_LRESET_BASE_L2             3

#define PWRSTATECTL_BITS_WIDTH_MSB                   9
#define PWRSTATECTL_BITS_WIDTH_LSB                   9
#define PWRSTATECTL_FIELD_WIDTH_8_BITS               0
#define PWRSTATECTL_FIELD_WIDTH_16_BITS              1

#define PWRSTATECTL_BITS_WAIT_MSB                    8
#define PWRSTATECTL_BITS_WAIT_LSB                    8
#define PWRSTATECTL_FIELD_WAIT_DISABLE               0
#define PWRSTATECTL_FIELD_WAIT_ENABLE                1

#define PWRSTATECTL_BITS_RECOVERY_MASTER_MSB         7
#define PWRSTATECTL_BITS_RECOVERY_MASTER_LSB         7
#define PWRSTATECTL_FIELD_RECOVERY_MASTER_GEM        0
#define PWRSTATECTL_FIELD_RECOVERY_MASTER_ARM        1

#define PWRSTATECTL_BITS_SR_INDEX_MSB                4
#define PWRSTATECTL_BITS_SR_INDEX_LSB                3

#define PWRSTATECTL_BITS_MODE_MSB                    2
#define PWRSTATECTL_BITS_MODE_LSB                    2
#define PWRSTATECTL_FIELD_HIBERNATION_MODE_1         0
#define PWRSTATECTL_FIELD_HIBERNATION_MODE_2         1

#define PWRSTATECTL_BITS_HIBERNATION_MSB             1
#define PWRSTATECTL_BITS_HIBERNATION_LSB             1
#define PWRSTATECTL_FIELD_HIBERNATION_OFF            0
#define PWRSTATECTL_FIELD_HIBERNATION_ON             1

/* The following fields are used in the bootup assembly */
#define PWRSTATECTL_MASK_HIB_TYPE               0x00000006
#define PWRSTATECTL_VAL_HIB_H1                  0x00000002

/****************************************************************************
 * Boot Progress register definitions
 ****************************************************************************
 /----------------------------------------------------------------------------------\
 |    31    | 30       27 | 26  25 |   24  | 23      22 |  21 | 20                0 |
 | Complete | Active Mode | Status | Sleep | Reset Type |  H  |  Mode Specific Info |
 \----------------------------------------------------------------------------------/
 ***/
 

#define BOOTPROG_BITS_ALL_COMPLETE_MSB          31
#define BOOTPROG_BITS_ALL_COMPLETE_LSB          31

#define BOOTPROG_BITS_ALL_ACTIVE_MODE_MSB       30
#define BOOTPROG_BITS_ALL_ACTIVE_MODE_LSB       27
#define BOOTPROG_FIELD_ACTIVE_MODE_SETUP         0
#define BOOTPROG_FIELD_ACTIVE_MODE_SLEEP         1
#define BOOTPROG_FIELD_ACTIVE_MODE_ETHERNET      2
#define BOOTPROG_FIELD_ACTIVE_MODE_SRIO          3
#define BOOTPROG_FIELD_ACTIVE_MODE_PCIE          4
#define BOOTPROG_FIELD_ACTIVE_MODE_I2C_MASTER    5
#define BOOTPROG_FIELD_ACTIVE_MODE_I2C_SLAVE     6
#define BOOTPROG_FIELD_ACTIVE_MODE_I2C_BCAST     7
#define BOOTPROG_FIELD_ACTIVE_MODE_SPI           8
#define BOOTPROG_FIELD_ACTIVE_MODE_HYPERLINK     9
#define BOOTPROG_FIELD_ACTIVE_MODE_EMIF16       10
#define BOOTPROG_FIELD_ACTIVE_MODE_HIB1         11
#define BOOTPROG_FIELD_ACTIVE_MODE_HIB2         12
#define BOOTPROG_FIELD_ACTIVE_MODE_UART         13
#define BOOTPROG_FIELD_ACTIVE_MODE_BOOTP        14
#define BOOTPROG_FIELD_ACTIVE_MODE_NAND         15

#define BOOTPROG_BITS_ALL_STATUS_MSB            26
#define BOOTPROG_BITS_ALL_STATUS_LSB            25

#define BOOTPROG_FIELD_ALL_STATUS_NO_WARN        0
#define BOOTPROG_FIELD_ALL_STATUS_WARN           1
#define BOOTPROG_FIELD_ALL_STATUS_SEVERE         2
#define BOOTPROG_FIELD_ALL_STATUS_FATAL          3

#define BOOTPROG_BITS_ALL_SLEEP_MSB             24
#define BOOTPROG_BITS_ALL_SLEEP_LSB             24
#define BOOTPROG_FIELD_ALL_SLEEP_AWAKE           0
#define BOOTPROG_FIELD_ALL_SLEEP_ASLEEP          1

#define BOOTPROG_BITS_ALL_RESET_TYPE_MSB        23
#define BOOTPROG_BITS_ALL_RESET_TYPE_LSB        22
#define BOOTPROG_FIELD_ALL_RSTYPE_POR            0
#define BOOTPROG_FIELD_ALL_RSTYPE_HARD           1
#define BOOTPROG_FIELD_ALL_RSTYPE_SOFT           2
#define BOOTPROG_FIELD_ALL_RSTYPE_INVALID        3

#define BOOTPROG_BITS_ALL_HIBERNATION_MSB       21
#define BOOTPROG_BITS_ALL_HIBERNATION_LSB       21
#define BOOTPROG_FIELD_ALL_NOT_HIBERNATING       0
#define BOOTPROG_FIELD_ALL_HIBERNATING           1

#define BOOTPROG_FCN_ALL_STATUS_SET_COMPLETE(x,y)     (x) = BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_ALL_COMPLETE_MSB,     BOOTPROG_BITS_ALL_COMPLETE_LSB)
#define BOOTPROG_FCN_ALL_STATUS_SET_ACTIVE(x,y)       (x) = BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_ALL_ACTIVE_MODE_MSB,  BOOTPROG_BITS_ALL_ACTIVE_MODE_LSB)
#define BOOTPROG_FCN_ALL_STATUS_SET_STATUS(x,y)       (x) = BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_ALL_STATUS_MSB,       BOOTPROG_BITS_ALL_STATUS_LSB)
#define BOOTPROG_FCN_ALL_STATUS_SET_SLEEP(x,y)        (x) = BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_ALL_SLEEP_MSB,        BOOTPROG_BITS_ALL_SLEEP_LSB)

#define BOOTPROG_FCN_ALL_STATUS_SET_RESET_TYPE(x,y)   (x) = BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_ALL_RESET_TYPE_MSB,   BOOTPROG_BITS_ALL_RESET_TYPE_LSB)
#define chipSetResetType(x)                           chipSetBPField ((x), BOOTPROG_BITS_ALL_RESET_TYPE_MSB, BOOTPROG_BITS_ALL_RESET_TYPE_LSB)

#define BOOTPROG_FCN_ALL_STATUS_SET_HIBERNATION(x,y)  (x) = BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_ALL_HIBERNATION_MSB,  BOOTPROG_BITS_ALL_HIBERNATION_LSB)

#define BOOTPROG_FCN_ALL_STATUS_GET_ACTIVE(x)         BOOT_READ_BITFIELD(x,BOOTPROG_BITS_ALL_ACTIVE_MODE_MSB,  BOOTPROG_BITS_ALL_ACTIVE_MODE_LSB)
#define BOOTPROG_FCN_ALL_STATUS_GET_STATUS(x)         BOOT_READ_BITFIELD(x,BOOTPROG_BITS_ALL_STATUS_MSB,       BOOTPROG_BITS_ALL_STATUS_LSB)
#define chipBootProgressSleep(x)                      chipSetBPField ((x), BOOTPROG_BITS_ALL_SLEEP_MSB,        BOOTPROG_BITS_ALL_SLEEP_LSB)

    /* The stick bits are boot complete, status, sleep, reset type, and hib */
#define BOOT_STATUS_STICKY_BITS           (BOOTBITMASK(BOOTPROG_BITS_ALL_COMPLETE_MSB,    BOOTPROG_BITS_ALL_COMPLETE_LSB)      |   \
                                          BOOTBITMASK(BOOTPROG_BITS_ALL_STATUS_MSB,      BOOTPROG_BITS_ALL_STATUS_LSB)        |   \
                                          BOOTBITMASK(BOOTPROG_BITS_ALL_SLEEP_MSB,       BOOTPROG_BITS_ALL_SLEEP_LSB)         |   \
                                          BOOTBITMASK(BOOTPROG_BITS_ALL_RESET_TYPE_MSB,  BOOTPROG_BITS_ALL_RESET_TYPE_LSB)    |   \
                                          BOOTBITMASK(BOOTPROG_BITS_ALL_HIBERNATION_MSB, BOOTPROG_BITS_ALL_HIBERNATION_LSB))

/***  Boot Progress Register, Boot Setup Mode ***
 /----------------------------------------\
 | 20   8 |   7    |  6   |  5   | 4    0 |
 |  rsvd  | master |  GS  |  RS  |  Stage |
 \----------------------------------------/
 ***/
 
#define BOOTPROG_BITS_SETUP_MASTER_MSB          7
#define BOOTPROG_BITS_SETUP_MASTER_LSB          7
#define BOOTPROG_FIELD_SETUP_MASTER_GEM         0
#define BOOTPROG_FIELD_SETUP_MASTER_ARM         1
 
#define BOOTPROG_BITS_SETUP_GS_MSB              6
#define BOOTPROG_BITS_SETUP_GS_LSB              6
#define BOOTPROG_FIELD_SETUP_GS_VALID_RESET     0
#define BOOTPROG_FIELD_SETUP_GS_INVALID_RESET   1

#define BOOTPROG_BITS_SETUP_RS_MSB                  5
#define BOOTPROG_BITS_SETUP_RS_LSB                  5
#define BOOTPROG_FIELD_SETUP_RESET_DETECTED         0
#define BOOTPROG_FIELD_SETUP_RESET_NOT_DETECTED     1

#define BOOTPROG_BITS_SETUP_STAGE_MSB           4
#define BOOTPROG_BITS_SETUP_STAGE_LSB           0

#define BOOTPROG_STATUS_INIT_STAGE_ROM_ENTERED                      0
#define BOOTPROG_STATUS_INIT_STAGE_MEM_SCRUB_COMPLETE               1
#define BOOTPROG_STATUS_INIT_STAGE_BOOT_MAIN_ENTERED                2
#define BOOTPROG_STATUS_INIT_STAGE_RAM_TABLE_COMPLETE               3
#define BOOTPROG_STATUS_INIT_STAGE_CHIP_SETUP_COMPLETE              4
#define BOOTPROG_STATUS_INIT_STAGE_BOOT_PARAM_TABLE_INIT_COMPLETE   5
#define BOOTPROG_STATUS_INIT_STAGE_BOOT_MAIN_COLD_DONE              6
#define BOOTPROG_STATUS_INIT_STAGE_BOOT_REENTRY                     7
#define BOOTPROG_STATUS_INIT_STAGE_STACK_RESET_COMPLETE             8
#define BOOTPROG_STATUS_INIT_STAGE_PLL_SETUP_COMPLETE               9
#define BOOTPROG_STATUS_INIT_STAGE_BOOT_DEVICE_POWERED_UP          10 


#define BOOTPROG_FCN_INIT_SET_MASTER(x,y)    (x)=BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_SETUP_MASTER_MSB, BOOTPROG_BITS_SETUP_MASTER_LSB)
#define BOOTPROG_FCN_INIT_SET_GS(x,y)        (x)=BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_SETUP_GS_MSB,     BOOTPROG_BITS_SETUP_GS_LSB)
#define BOOTPROG_FCN_INIT_SET_STAGE(x,y)     (x)=BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_SETUP_STAGE_MSB,  BOOTPROG_BITS_SETUP_STAGE_LSB)
#define BOOTPROG_FCN_INIT_SET_RS(x,y)        (x)=BOOT_SET_BITFIELD(x,y,BOOTPROG_BITS_SETUP_RS_MSB,     BOOTPROG_BITS_SETUP_RS_LSB)

/*** Boot Progress Register, Ethernet Boot ***
/------------------------------------------------------------\
|  20  | 19    16 | 15      12 | 11         8 | 7          0 |
| link | rejected | dscr empty | sequence err | sequence num |
\------------------------------------------------------------/
***/
#define BOOTPROG_BITS_ETH_LINK_MSB          20
#define BOOTPROG_BITS_ETH_LINK_LSB          20

#define BOOTPROG_BITS_ETH_REJECTED_MSB      19
#define BOOTPROG_BITS_ETH_REJECTED_LSB      16

#define BOOTPROG_BITS_ETH_DESCR_EMPTY_MSB   15
#define BOOTPROG_BITS_ETH_DESCR_EMPTY_LSB   12

#define BOOTPROG_BITS_ETH_SEQ_ERR_MSB       11
#define BOOTPROG_BITS_ETH_SEQ_ERR_LSB        8

#define BOOTPROG_BITS_ETH_SEQNUM_MSB         7
#define BOOTPROG_BITS_ETH_SEQNUM_LSB         0

#define chipStatusEthLinkUp_m() chipSetBPField(1, BOOTPROG_BITS_ETH_LINK_MSB, BOOTPROG_BITS_ETH_LINK_LSB)

#define chipStatusEthReject()   chipIncBPField(BOOTPROG_BITS_ETH_REJECTED_MSB,  \
                                               BOOTPROG_BITS_ETH_REJECTED_LSB); \
                                chipPromoteBootStatus (BOOT_STATUS_STATUS_WARN)
                                
#define chipStatusEthMisSequenced()     chipIncBPField(BOOTPROG_BITS_ETH_SEQ_ERR_MSB,    \
                                                       BOOTPROG_BITS_ETH_SEQ_ERR_LSB);   \
                                        chipPromoteBootStatus (BOOT_STATUS_STATUS_SEVERE)

#define chipStatusEthExpectedSeqNum(x)  chipSetBPField((x), BOOTPROG_BITS_ETH_SEQNUM_MSB, BOOTPROG_BITS_ETH_SEQNUM_LSB)




/*** Boot Progress Register, SRIO Boot ***
/----------------------------------------------------------------------------------\
|  20  |  19  |   18    |  17  | 16      14 | 13      11 | 10        8 | 7       0 |
| Mode | tout | Port Ok | Lock | Bad Chksum | Bad Length | Empty Descr | Msg Count |
\----------------------------------------------------------------------------------/
***/
#define BOOTPROG_BITS_SRIO_MODE_MSW         20
#define BOOTPROG_BITS_SRIO_MODE_LSW         20
#define BOOTPROG_FIELD_SRIO_MODE_HOST        0
#define BOOTPROG_FIELD_SRIO_MODE_MSG         1

#define BOOTPROG_BITS_SRIO_TIMEOUT_MSW      19
#define BOOTPROG_BITS_SRIO_TIMEOUT_LSW      19

#define BOOTPROG_BITS_SRIO_PORT_OK_MSB      18
#define BOOTPROG_BITS_SRIO_PORT_OK_LSB      18

#define BOOTPROG_BITS_SRIO_LOCK_MSB         17
#define BOOTPROG_BITS_SRIO_LOCK_LSB         17

#define BOOTPROG_BITS_SRIO_BAD_CHKSUM_MSB   16
#define BOOTPROG_BITS_SRIO_BAD_CHKSUM_LSB   14

#define BOOTPROG_BITS_SRIO_BAD_LENGTH_MSB   13
#define BOOTPROG_BITS_SRIO_BAD_LENGTH_LSB   11

#define BOOTPROG_BITS_SRIO_EMPTY_DESCR_MSB  10
#define BOOTPROG_BITS_SRIO_EMPTY_DESCR_LSB   8

#define BOOTPROG_BITS_SRIO_MSG_CNT_MSB       7
#define BOOTPROG_BITS_SRIO_MSG_CNT_LSB       0


#define chipStatusRioBadChksum()      chipIncBPField (BOOTPROG_BITS_SRIO_BAD_CHKSUM_MSB,   BOOTPROG_BITS_SRIO_BAD_CHKSUM_LSB)
#define chipStatusRioBadLength()      chipIncBPField (BOOTPROG_BITS_SRIO_BAD_LENGTH_MSB,   BOOTPROG_BITS_SRIO_BAD_LENGTH_LSB)
#define chipStatusRioDescrEmpty()     chipIncBPField (BOOTPROG_BITS_SRIO_EMPTY_DESCR_MSB,  BOOTPROG_BITS_SRIO_EMPTY_DESCR_LSB)
#define chipStatusRioPacket()         chipIncBPField (BOOTPROG_BITS_SRIO_MSG_CNT_MSB,      BOOTPROG_BITS_SRIO_MSG_CNT_LSB)
#define chipStatusRioPktMode()        chipSetBPField (1, BOOTPROG_BITS_SRIO_MODE_MSW,      BOOTPROG_BITS_SRIO_MODE_LSW)
#define chipStatusRioHostMode()       chipSetBPField (0, BOOTPROG_BITS_SRIO_MODE_MSW,      BOOTPROG_BITS_SRIO_MODE_LSW)
#define chipStatusRioPortOkVal(x)     chipSetBPField ((x), BOOTPROG_BITS_SRIO_PORT_OK_MSB, BOOTPROG_BITS_SRIO_PORT_OK_LSB)
#define chipStatusRioSerdesLockval(x) chipSetBPField ((x), BOOTPROG_BITS_SRIO_LOCK_MSB,    BOOTPROG_BITS_SRIO_LOCK_LSB)
#define chipStatusRioTimeout_m()      chipSetBPField (1, BOOTPROG_BITS_SRIO_TIMEOUT_MSW,   BOOTPROG_BITS_SRIO_TIMEOUT_LSW)


/*** Boot Progress Register, PCIe Boot ***
 /--------------------------------------------------------\
 |   20     |   19    |  18  |  17  |  16  | 15         0 |
 | Inv Mode | Inv Cfg | lock | link | tout |  wake count  |
 \--------------------------------------------------------/
***/
#define BOOTPROG_BITS_PCIE_INV_MODE_MSB     20
#define BOOTPROG_BITS_PCIE_INV_MODE_LSB     20

#define BOOTPROG_BITS_PCIE_INV_CFG_MSB      19
#define BOOTPROG_BITS_PCIE_INV_CFG_LSB      19

#define BOOTPROG_BITS_PCIE_LOCK_MSB         18
#define BOOTPROG_BITS_PCIE_LOCK_LSB         18

#define BOOTPROG_BITS_PCIE_LINK_MSB         17
#define BOOTPROG_BITS_PCIE_LINK_LSB         17

#define BOOTPROG_BITS_PCIE_TIMEOUT_MSB      16
#define BOOTPROG_BITS_PCIE_TIMEOUT_LSB      16

#define BOOTPROG_BITS_PCIE_WAKE_CNT_MSB     15
#define BOOTPROG_BITS_PCIE_WAKE_CNT_LSB      0


#define chipStatusPcieIncWakeCount()  chipIncBPField (BOOTPROG_BITS_PCIE_WAKE_CNT_MSB,    BOOTPROG_BITS_PCIE_WAKE_CNT_LSB)
#define chipStatusPcieModeInvalid()   chipSetBPField (1, BOOTPROG_BITS_PCIE_INV_MODE_MSB, BOOTPROG_BITS_PCIE_INV_MODE_LSB)
#define chipStatusPcieCfgInvalid()    chipSetBPField (1, BOOTPROG_BITS_PCIE_INV_CFG_MSB,  BOOTPROG_BITS_PCIE_INV_CFG_LSB)
#define chipStatusPcieLockDetected()  chipSetBPField (1, BOOTPROG_BITS_PCIE_LOCK_MSB,     BOOTPROG_BITS_PCIE_LOCK_LSB)
#define chipStatusPcieLinkDetected()  chipSetBPField (1, BOOTPROG_BITS_PCIE_LINK_MSB,     BOOTPROG_BITS_PCIE_LINK_LSB)
#define chipStatusPcieTimeout()       chipSetBPField (1, BOOTPROG_BITS_PCIE_TIMEOUT_MSB,  BOOTPROG_BITS_PCIE_TIMEOUT_LSB)


/*** Boot Progress Register, I2C Master, Master Broadcast Boot ***
 /------------------------------------\
 |  20   | 19          16 | 15      0 |
 | Retry |  Extended Addr | Read Addr |
 \------------------------------------/
 ***/
#define BOOTPROG_BITS_I2CM_RETRY_MSB        20
#define BOOTPROG_BITS_I2CM_RETRY_LSB        20

#define BOOTPROG_BITS_I2CM_EXT_ADDR_MSB     19
#define BOOTPROG_BITS_I2CM_EXT_ADDR_LSB     16

#define BOOTPROG_BITS_I2CM_READ_ADDR_MSB    15
#define BOOTPROG_BITS_I2CM_READ_ADDR_LSB     0

/*** Boot Progress Register, I2C Slave ***
 /-------------------------\
 | 20 18 | 17 16 | 15    0 |
 | Retry |  Mode |  Count  |
 \-------------------------/
 ***/
#define BOOTPROG_BITS_I2CS_RETRY_MSB        20
#define BOOTPROG_BITS_I2CS_RETRY_LSB        18

#define BOOTPROG_BITS_I2CS_MODE_MSB         17
#define BOOTPROG_BITS_I2CS_MODE_LSB         16
#define BOOTPROG_FIELD_I2CS_MODE_WAIT_OPTS   0
#define BOOTPROG_FIELD_I2CS_MODE_BTBL        1
#define BOOTPROG_FIELD_I2CS_MODE_BCFG        2

#define BOOTPROG_BITS_I2CS_COUNT_MSB        15
#define BOOTPROG_BITS_I2CS_COUNT_LSB         0


#define chipStatusIncI2cPassiveBlocks()         chipIncBPField (BOOTPROG_BITS_I2CS_COUNT_MSB, BOOTPROG_BITS_I2CS_COUNT_LSB)

/*** Boot Progress Register, SPI Mode ***
 /----------------------------\
 | 20     18 |  17  | 16    0 |
 |  Retries  | Init | Address |
 \----------------------------/
 ***/
#define BOOTPROG_BITS_SPI_RETRY_MSB         20
#define BOOTPROG_BITS_SPI_RETRY_LSB         18

#define BOOTPROG_BITS_SPI_INIT_MSB          17
#define BOOTPROG_BITS_SPI_INIT_LSB          17

#define BOOTPROG_BITS_SPI_ADDR_MSB          16
#define BOOTPROG_BITS_SPI_ADDR_LSB           0


#define chipStatusSpiInitFail()           chipSetBPField (1, BOOTPROG_BITS_SPI_INIT_MSB, BOOTPROG_BITS_SPI_INIT_LSB)
#define chipStatusSpiInitSuccess()        chipSetBPField (0, BOOTPROG_BITS_SPI_INIT_MSB, BOOTPROG_BITS_SPI_INIT_LSB)
#define chipStatusSpiUpdateAddress(v)     chipSetBPField (v, BOOTPROG_BITS_SPI_ADDR_MSB, BOOTPROG_BITS_SPI_ADDR_LSB)
#define chipStatusSpiIncRetries()         chipIncBPField (BOOTPROG_BITS_SPI_RETRY_MSB,   BOOTPROG_BITS_SPI_RETRY_LSB)

/*** Boot Progress Register, Hyperlink Mode ***
 /---------------------------------------------------\
 |      20     |  19  | 18 17 |    16   | 15       0 |
 | Serdes Lock | Link |  Port | Timeout | Wake Count |
 \---------------------------------------------------/
 ***/
#define BOOTPROG_BITS_HYPER_LOCK_MSB         20
#define BOOTPROG_BITS_HYPER_LOCK_LSB         20

#define BOOTPROG_BITS_HYPER_LINK_MSB         19
#define BOOTPROG_BITS_HYPER_LINK_LSB         19

#define BOOTPROG_BITS_HYPER_PORT_MSB        18
#define BOOTPROG_BITS_HYPER_PORT_LSB        17

#define BOOTPROG_BITS_HYPER_TIMEOUT_MSB     16
#define BOOTPROG_BITS_HYPER_TIMEOUT_LSB     16

#define BOOTPROG_BITS_HYPER_WAKE_CNT_MSB     15
#define BOOTPROG_BITS_HYPER_WAKE_CNT_LSB      0


#define chipStatusHyperIncWakeCount()  chipIncBPField (     BOOTPROG_BITS_HYPER_WAKE_CNT_MSB, BOOTPROG_BITS_HYPER_WAKE_CNT_LSB)
#define chipStatusHyperSerdesLock()    chipSetBPField (1,   BOOTPROG_BITS_HYPER_LOCK_MSB,     BOOTPROG_BITS_HYPER_LOCK_LSB)
#define chipStatusHyperLink()          chipSetBPField (1,   BOOTPROG_BITS_HYPER_LINK_MSB,     BOOTPROG_BITS_HYPER_LINK_LSB)
#define chipStatusHyperSetPort(x)      chipSetBPField ((x), BOOTPROG_BITS_HYPER_PORT_MSB,     BOOTPROG_BITS_HYPER_PORT_LSB)
#define chipStatusHyperTimeout_m()     chipSetBPField (1,   BOOTPROG_BITS_HYPER_TIMEOUT_MSB,  BOOTPROG_BITS_HYPER_TIMEOUT_LSB)

/*** Boot Progress Register, EMIF16 Mode ***
 /-----------------------------------\
 | 20     19 | 18 16 | 15          0 |
 | CS Region | rsvd  | Branch Offset |
 \-----------------------------------/
 ***/
#define BOOTPROG_BITS_EMIF16_CS_MSB             20
#define BOOTPROG_BITS_EMIF16_CS_LSB             19

#define BOOTPROG_BITS_EMIF16_BRANCH_OFFSET_MSB  15
#define BOOTPROG_BITS_EMIF16_BRANCH_OFFSET_LSB   0

#define chipStatusEmif25SetCsRegion(x)    chipSetBPField (((x) - 2),   BOOTPROG_BITS_EMIF16_CS_MSB,            BOOTPROG_BITS_EMIF16_CS_LSB)
#define chipStatusEmif25SetOffset(x)      chipSetBPField (((x) >> 12), BOOTPROG_BITS_EMIF16_BRANCH_OFFSET_MSB, BOOTPROG_BITS_EMIF16_BRANCH_OFFSET_LSB)

/*** Boot Progress Register, UART Boot ***
 /---------------------------------------------------------------------------------------------------------------\
 |  20  |        19       |        18          | 17      15 | 14       11 | 10         8 | 7     5 | 4         0 |
 | port | port setup done | port setup success | ping count | cmd timeout | char timeout | crc err | good frames |
 \---------------------------------------------------------------------------------------------------------------/
 ***/
 
#define BOOTPROG_BITS_UART_PORT_MSB             20
#define BOOTPROG_BITS_UART_PORT_LSB             20

#define BOOTPROG_BITS_UART_SETUP_DONE_MSB       19
#define BOOTPROG_BITS_UART_SETUP_DONE_LSB       19

#define BOOTPROG_BITS_UART_SETUP_SUCCESS_MSB    18
#define BOOTPROG_BITS_UART_SETUP_SUCCESS_LSB    18

#define BOOTPROG_BITS_UART_PING_COUNT_MSB       17
#define BOOTPROG_BITS_UART_PING_COUNT_LSB       15

#define BOOTPROG_BITS_UART_CMD_TIMEOUT_MSB      14
#define BOOTPROG_BITS_UART_CMD_TIMEOUT_LSB      11

#define BOOTPROG_BITS_UART_CHAR_TIMEOUT_MSB     10
#define BOOTPROG_BITS_UART_CHAR_TIMEOUT_LSB      8

#define BOOTPROG_BITS_UART_CRC_ERR_MSB           7
#define BOOTPROG_BITS_UART_CRC_ERR_LSB           5

#define BOOTPROG_BITS_UART_GOOD_FRAMES_MSB       4
#define BOOTPROG_BITS_UART_GOOD_FRAMES_LSB       0

#define chipStatusUartSetPort(x)      chipSetBPField ((x), BOOTPROG_BITS_UART_PORT_MSB,          BOOTPROG_BITS_UART_PORT_LSB)
#define chipStatusUartInitSuccess()   chipSetBPField (1,   BOOTPROG_BITS_UART_SETUP_DONE_MSB,    BOOTPROG_BITS_UART_SETUP_DONE_LSB); \
                                      chipSetBPField (1,   BOOTPROG_BITS_UART_SETUP_SUCCESS_MSB, BOOTPROG_BITS_UART_SETUP_SUCCESS_LSB)

#define chipStatusUartInitFail()      chipSetBPField (1,   BOOTPROG_BITS_UART_SETUP_DONE_MSB,    BOOTPROG_BITS_UART_SETUP_DONE_LSB); \
                                      chipSetBPField (0,   BOOTPROG_BITS_UART_SETUP_SUCCESS_MSB, BOOTPROG_BITS_UART_SETUP_SUCCESS_LSB)
                                      
#define chipStatusUartIncPingCount()   chipIncBPField (BOOTPROG_BITS_UART_PING_COUNT_MSB,   BOOTPROG_BITS_UART_PING_COUNT_LSB)

#define chipStatusUartIncCmdTimeout()  chipIncBPField (BOOTPROG_BITS_UART_CMD_TIMEOUT_MSB,  BOOTPROG_BITS_UART_CMD_TIMEOUT_LSB)

#define chipStatusUartIncCharTimeout() chipIncBPField (BOOTPROG_BITS_UART_CHAR_TIMEOUT_MSB, BOOTPROG_BITS_UART_CHAR_TIMEOUT_LSB)

#define chipStatusUartIncCrcErr()      chipIncBPField (BOOTPROG_BITS_UART_CRC_ERR_MSB,      BOOTPROG_BITS_UART_CRC_ERR_LSB)

#define chipStatusUartIncGoodFrames()  chipIncBPField (BOOTPROG_BITS_UART_GOOD_FRAMES_MSB,  BOOTPROG_BITS_UART_GOOD_FRAMES_LSB)
#define chipStatusUartDecGoodFrames()  chipDecBPField (BOOTPROG_BITS_UART_GOOD_FRAMES_MSB,  BOOTPROG_BITS_UART_GOOD_FRAMES_LSB)


#define chipStatusUartErr()            chipPromoteBootStatus (BOOT_STATUS_STATUS_WARN)

/*** Boot Progress Register, NAND Boot ***
 /---------------------------------------------------------------------------------------------------\
 | 20     19 |  18  | 17         14 | 13        10 | 9             7 | 6       4 | 3               0 |
 | CS Region | ONFI | Current Block | Current Page | Pages per Block | Page Size | ECC Failure Count |
 \---------------------------------------------------------------------------------------------------/
 ***/
 
#define BOOTPROG_BITS_NAND_CS_REGION_MSB        20
#define BOOTPROG_BITS_NAND_CS_REGION_LSB        19

#define BOOTPROG_BITS_NAND_ONFI_MSB             18
#define BOOTPROG_BITS_NAND_ONFI_LSB             18
#define BOOTPROG_FIELD_NAND_NOT_ONFI             0
#define BOOTPROG_FIELD_NAND_IS_ONFI              1

#define BOOTPROG_BITS_NAND_BLOCK_MSB            17
#define BOOTPROG_BITS_NAND_BLOCK_LSB            14
#define BOOTPROG_FIELD_NAND_MAX_BLOCK           ((1 << (BOOTPROG_BITS_NAND_BLOCK_MSB - BOOTPROG_BITS_NAND_BLOCK_LSB + 1)) - 1)
#define BOOTPROG_FIELD_NAND_SETBLOCK(x)         ((x) > BOOTPROG_FIELD_NAND_MAX_BLOCK ? BOOTPROG_FIELD_NAND_MAX_BLOCK : (x))

#define BOOTPROG_BITS_NAND_PAGE_MSB             13
#define BOOTPROG_BITS_NAND_PAGE_LSB             10
#define BOOTPROG_FIELD_NAND_MAX_PAGE            ((1 << (BOOTPROG_BITS_NAND_PAGE_MSB - BOOTPROG_BITS_NAND_PAGE_LSB + 1)) - 1)
#define BOOTPROG_FIELD_NAND_SETPAGE(x)          ((x) > BOOTPROG_FIELD_NAND_MAX_PAGE ? BOOTPROG_FIELD_NAND_MAX_PAGE : (x))

/* Pages per block field is the value n in (2^(n+6)) */
#define BOOTPROG_BITS_NAND_PAGES_PER_BLOCK_MSB   9
#define BOOTPROG_BITS_NAND_PAGES_PER_BLOCK_LSB   7
#define BOOTPROG_FIELD_NAND_PAGEPERBLOCK(x)      ((31 - chipLmbd(1,(x))) > 5 ? (31 - chipLmbd(1,(x)) - 6) : 0)

/* Page size field is size_bytes / 512 */
#define BOOTPROG_BITS_NAND_PAGE_SIZE_MSB         6
#define BOOTPROG_BITS_NAND_PAGE_SIZE_LSB         4
#define BOOTPROG_FIELD_NAND_PAGESIZE(x)          ((x) >> 9)


#define BOOTPROG_BITS_NAND_ECC_FAILURES_MSB      3
#define BOOTPROG_BITS_NAND_ECC_FAILURES_LSB      0

#define chipStatusNandSetCSRegion(x)      chipSetBPField ((x),                                 BOOTPROG_BITS_NAND_CS_REGION_MSB,       BOOTPROG_BITS_NAND_CS_REGION_LSB)
#define chipStatusNandSetOnfi(x)          chipSetBPField ((x),                                 BOOTPROG_BITS_NAND_ONFI_MSB,            BOOTPROG_BITS_NAND_ONFI_LSB)
#define chipStatusNandSetBlock(x)         chipSetBPField (BOOTPROG_FIELD_NAND_SETBLOCK(x),     BOOTPROG_BITS_NAND_BLOCK_MSB,           BOOTPROG_BITS_NAND_BLOCK_LSB)
#define chipStatusNandSetPage(x)          chipSetBPField (BOOTPROG_FIELD_NAND_SETPAGE(x),      BOOTPROG_BITS_NAND_PAGE_MSB,            BOOTPROG_BITS_NAND_PAGE_LSB)
#define chipStatusNandSetPagesPerBlock(x) chipSetBPField (BOOTPROG_FIELD_NAND_PAGEPERBLOCK(x), BOOTPROG_BITS_NAND_PAGES_PER_BLOCK_MSB, BOOTPROG_BITS_NAND_PAGES_PER_BLOCK_LSB)
#define chipStatusNandSetPageSize(x)      chipSetBPField (BOOTPROG_FIELD_NAND_PAGESIZE(x),     BOOTPROG_BITS_NAND_PAGE_SIZE_MSB,       BOOTPROG_BITS_NAND_PAGE_SIZE_LSB)
#define chipStatusNandIncEccFail()        chipIncBPField (                                     BOOTPROG_BITS_NAND_ECC_FAILURES_MSB,    BOOTPROG_BITS_NAND_ECC_FAILURES_MSB)


/*** Boot Progress Register, Bootp Boot ***
 /------------------------------------------------------------------------\
 | 20   18 |    17   | 16   14 |     13   | 12         9 | 8            0 |
 | xmt cnt | bp rcvd | ARP xmt | ARP rcvd | TFTP re-xmit | TFTP block Num |
 \------------------------------------------------------------------------/
 ***/
#define BOOTPROG_BITS_BOOTP_XMT_CNT_MSB         20
#define BOOTPROG_BITS_BOOTP_XMT_CNT_LSB         18

#define BOOTPROG_BITS_BOOTP_BP_RCVD_MSB         17
#define BOOTPROG_BITS_BOOTP_BP_RCVD_LSB         17

#define BOOTPROG_BITS_BOOTP_ARP_XMT_CNT_MSB     16
#define BOOTPROG_BITS_BOOTP_ARP_XMT_CNT_LSB     14

#define BOOTPROG_BITS_BOOTP_ARM_RCVD_MSB        13
#define BOOTPROG_BITS_BOOTP_ARM_RCVD_LSB        13

#define BOOTPROG_BITS_BOOTP_TFTP_RE_XMT_MSB     12
#define BOOTPROG_BITS_BOOTP_TFTP_RE_XMT_LSB      9

#define BOOTPROG_BITS_BOOTP_TFTP_BLOCK_MSB       8
#define BOOTPROG_BITS_BOOTP_TFTP_BLOCK_LSB       0
#define BOOTPROG_FIELD_BOOTP_MAX_BLOCK           ((1 << (BOOTPROG_BITS_BOOTP_TFTP_BLOCK_MSB - BOOTPROG_BITS_BOOTP_TFTP_BLOCK_LSB + 1)) - 1)
#define BOOTPROG_FIELD_BOOTP_BLOCK(x)            ((x) > BOOTPROG_FIELD_BOOTP_MAX_BLOCK ? BOOTPROG_FIELD_BOOTP_MAX_BLOCK : (x))

#define chipStatusBootpIncBootpXmtCnt()          chipIncBPField (                               BOOTPROG_BITS_BOOTP_XMT_CNT_MSB,     BOOTPROG_BITS_BOOTP_XMT_CNT_LSB)
#define chipStatusBootpSetBpRcvd()               chipSetBPField (1,                             BOOTPROG_BITS_BOOTP_BP_RCVD_MSB,     BOOTPROG_BITS_BOOTP_BP_RCVD_LSB)
#define chipStatusBootpSetArpRcvd()              chipSetBPField (1,                             BOOTPROG_BITS_BOOTP_ARM_RCVD_MSB,    BOOTPROG_BITS_BOOTP_ARM_RCVD_LSB)
#define chipStatusBootpIncArpXmtCnt()            chipIncBPField (                               BOOTPROG_BITS_BOOTP_ARP_XMT_CNT_MSB, BOOTPROG_BITS_BOOTP_ARP_XMT_CNT_LSB)
#define chipStatusBootpIncTftpReXmtCnt()         chipIncBPField (                               BOOTPROG_BITS_BOOTP_TFTP_RE_XMT_MSB, BOOTPROG_BITS_BOOTP_TFTP_RE_XMT_LSB)
#define chipStatusBootpSetTftpBlockNum(x)        chipSetBPField (BOOTPROG_FIELD_BOOTP_BLOCK(x), BOOTPROG_BITS_BOOTP_TFTP_BLOCK_MSB,  BOOTPROG_BITS_BOOTP_TFTP_BLOCK_LSB)



/*** Boot Progress Register, Hibernation Recover ***
 /---------------------\
 | 20   9 | 8        0 |
 |  Rsvd  | Error Code |
 \---------------------/
 ***/
#define BOOTPROG_BITS_HIB_ERR_CODE_MSB       8
#define BOOTPROG_BITS_HIB_ERR_CODE_LSB       0
#define BOOTPROG_FIELD_HIB_NO_ERR            0
#define BOOTPROG_FIELD_HIB_INV_ADDR          1



/****************************************************************************
 * jtag communication register, data out
 *
 *  /----------------------------------------------------------\
 *  | 31       24 |  23 | 22      20 | 19      16 | 15       0 |
 *  | receive map | p/f | heart beat | word index | die id val |
 *  \----------------------------------------------------------/
 *
 ****************************************************************************/
#define JTAG_OUT_BITS_RCV_MAP_MSB      31
#define JTAG_OUT_BITS_RCV_MAP_LSB      24

#define JTAG_OUT_BITS_PASS_FAIL_MSB    23
#define JTAG_OUT_BITS_PASS_FAIL_LSB    23
#define JTAG_OUT_FIELD_PASS_FAIL_FAIL   0
#define JTAG_OUT_FIELD_PASS_FAIL_PASS   1

#define JTAG_OUT_BITS_HEART_BEAT_MSB   22
#define JTAG_OUT_BITS_HEART_BEAT_LSB   20
 
#define JTAG_OUT_BITS_WORD_IDX_MSB     19
#define JTAG_OUT_BITS_WORD_IDX_LSB     16

#define JTAG_OUT_BITS_ID_VAL_MSB       15
#define JTAG_OUT_BITS_ID_VAL_LSB        0

/*****************************************************************************
 * jtag communication register, data in
 *
 *  /----------------------------------------------\
 *  | 31    20 | 19      16 | 15                 0 |
 *  |   rsvd   | word index | encrypted die id val |
 *  \----------------------------------------------/
 *
 ******************************************************************************/
#define JTAG_IN_BITS_WORD_IDX_MSB   19
#define JTAG_IN_BITS_WORD_IDX_LSB   16

#define JTAG_IN_BITS_ID_VAL_MSB     15
#define JTAG_IN_BITS_ID_VAL_LSB      0


/****************************************************************************
 * Jtag communication register, data out for public key hash out
 *
 *  /------------------------------------------------------\
 *  | 31  21 | 20             16 | 15                    0 |
 *  |  rsvd  |  word index (1-n) | hash value (big endian) |
 *  \------------------------------------------------------/
 *
 ****************************************************************************/
#define JTAG_OUT_HASH_BITS_INDEX_MSB    20
#define JTAG_OUT_HASH_BITS_INDEX_LSB    16

#define JTAG_OUT_HASH_BITS_VAL_MSB      15
#define JTAG_OUT_HASH_BITS_VAL_LSB       0

 

/****************************************************************************
 * Definition: Macro to access non-core peripheral registers.
 *             Uses direct access
 ****************************************************************************/
#define DEVICE_REG32_W(x,y)   *(volatile unsigned int *)(x)=((unsigned int)y)
#define DEVICE_REG32_R(x)    (*(volatile unsigned int *)(x))


/****************************************************************************
 * Definition: The DNUM value for ARM. Used for setting the bit in the
 *             boot complete register
 ****************************************************************************/
#ifdef __TMS470__
 #define DNUM       (chipReadArmDnum() + 8)
 #define ARMNUM     chipReadArmDnum()
#endif

/****************************************************************************
 * Definition: The c64x boot table tools will always pad boot table
 *             entries to 32 bit elements. The boot table works in 16 bit
 *             element sizes. If the size is not an even number of 16 bit
 *             elements, add one word of padding.
 ****************************************************************************/
#define chipAddBtblUint16Pad(x)     (((x)+1) & 0xfffffffe)


/****************************************************************************
 * The number of sgmii configuration tables stored in the ROM
 ****************************************************************************/
#define DEVICE_SGMII_N_CFG_TABLES   4


/****************************************************************
 * EMIF25 available on Keystone 
 ****************************************************************/
#define chipEmif25Available()   TRUE

/****************************************************************
 * Fixed number of GEM cores in Keystone
 ****************************************************************/
#define chipReadNumCores()                 8

/****************************************************************
 * Maximum frequency - used to compute delays 
 ****************************************************************/
#define DEVICE_MAX_FREQ_MHZ         1536
#define DEVICE_MAX_REF_FREQ_MHZ     312

/****************************************************************
 * NAND Timeout loop counter
 ****************************************************************/
#define DEVICE_NAND_TIMEOUT                     (DEVICE_MAX_FREQ_MHZ * 10)
#define DEVICE_NAND_INITIAL_READY_TIMEOUT       (0x7fffffff)        /* maximum timeout (signed int) */

/*********************************************************************************
 * Definition: Define a minimum delay of 0.1ms at the maximum device frequency
 *********************************************************************************/
#define DEVICE_SERDES_LOCK_DELAY    (DEVICE_MAX_FREQ_MHZ * 100)


/******************************************************************************
 * Initial mapping of the device into PCIe memory map
 ******************************************************************************/
#define DEVICE_PCIE_INITIAL_BAR0_LO     0x0000
#define DEVICE_PCIE_INITIAL_BAR0_HI     0x0000

#define DEVICE_PCIE_INITIAL_BAR_64BIT_LO(x)     0x00000000
#define DEVICE_PCIE_INITIAL_BAR_64BIT_HI(x)     0x00000000

/* Local L2 for cores 0-2, MSMC */
#define DEVICE_PCIE_INITIAL_BAR_32BIT(x)  0x00000000



/****************************************************************************
 * Definition: Boot status return values. These values must match the
 *             boot progress status values, and higher values must
 *             indicate higher severity.
 ****************************************************************************/
#define  BOOT_RET_SUCCESS       BOOTPROG_FIELD_ALL_STATUS_NO_WARN
#define  BOOT_RET_WARN          BOOTPROG_FIELD_ALL_STATUS_WARN
#define  BOOT_RET_WARN_SEVERE   BOOTPROG_FIELD_ALL_STATUS_SEVERE
#define  BOOT_RET_FATAL         BOOTPROG_FIELD_ALL_STATUS_FATAL

/***************************************************************************
 * Definition: These are the values returned by the bethpr module.
 *             They are defined to the same meaning in the boot progress register
 ***************************************************************************/
#define  BOOT_STATUS_STATUS_SUCCESS BOOTPROG_FIELD_ALL_STATUS_NO_WARN
#define  BOOT_STATUS_STATUS_WARN    BOOTPROG_FIELD_ALL_STATUS_WARN
#define  BOOT_STATUS_STATUS_SEVERE  BOOTPROG_FIELD_ALL_STATUS_SEVERE
#define  BOOT_STATUS_STATUS_FATAL   BOOTPROG_FIELD_ALL_STATUS_FATAL


/* Pll Disable directly tied to the pll driver */
#define chipDisablePll      hwPllDisable


/******************************************************************************
 * Definition: The default multicast and host mac address for ethernet boot,
 *             and default udp ports. The default interface is SGMII because
 *             it is the only interface available.
 ******************************************************************************/
#define chipReadMmacAddr(x)        ((x)[0] = (x)[1] = (x)[2] = 0xffff)
#define chipReadHmacAddr(x)        ((x)[0] = (x)[1] = (x)[2] = 0xffff)
#define chipDefaultEthSrcPort()    0
#define chipDefaultEthDstPort()    9
#define chipDefaultEthIf(x)        BOOT_PARAMS_ETH_OPTIONS_SGMII
#define chipRouteGmacInt(x,y)       
#define chipReadEepromType()       I2C_EEPROM_32_1024
#define chipEthTxEnableDelay()     chipDelay32 (DEVICE_MAX_FREQ_MHZ * 650)  /* About 650us at Max clock */
#define chipDefaultEthPll()        chipDefaultPll(TRUE)     /* True indicates min pin is valid */
#define chipEthIsrTx()             /* Empty - there is no software recovery required */
#define chipMaxEthPktSize()        BOOTCONFIG_ETH_MAX_PKTLEN_UINT8
#define chipDefaultEthPort()       0   /* There is only one port (but multple lanes) */
#define chipGetDefaultSGMIISetup   chipGetDefaultSgmiiParams
#define chipDefaultEthPll2()       chipDefaultArmPll(TRUE)  /* True indicates min pin is valid */
#define chipDefaultSgmiiConfig()   BOOT_PARAMS_SGMII_CONFIG_DIRECT_CONFIG


/****************************************************************************
 * Definition: Ethernet bootp definitions
 ****************************************************************************/
#define chipDefaultEthBootpPort()         0      /* Both sgmii ports enabled */
#define chipDefaultBootpTimeoutMs()       4000   /* Initial timeout = 4s     */
#define chipDefaultTftpAckTimeoutMs()     1000   /* Read timeout = 1s        */
#define chipDefaultTftpTimeoutSec()       90     /* 60 second boot limit     */
#define chipDefaultBootpRetryCount()      10
#define chipDefaultTftpRetryCount()       10
#define chipGetDefaultBootpSgmiiParams    chipGetDefaultSgmiiParams



/* SGMII */
#define DEVICE_MAC_SGMII
#define DEVICE_C0RX_MAC_EOI_VECTOR          0   /* Not used in Keystone */
#define DEVICE_C0TX_MAC_EOI_VECTOR          0   /* Not used in Keystone */
#define DEVICE_MAC_RX_INTMASK_REG_VALUE     0   /* Not used in Keystone */
#define DEVICE_MAC_TX_INTMASK_REG_VALUE     0   /* Not used in Keystone */

/* The gmac interrupts are not used, so defined to an illegal IFR value */
#define DEVICE_GMAC_IFR_RX              16      /* !!! This value is intentionally illegal ( >15 ) */
#define DEVICE_IFR_GMAC_RX_INT_MASK     0
#define DEVICE_IFR_GMAC_TX_INT_MASK     0

/* The gmac uses a timer for resending ERA frames. The timer is polled, interrupts are not used */
#define DEVICE_IFR_GMAC_TIMER_TX_INT        16
#define DEVICE_IFR_GMAC_TIMER_TX_INT_MASK   0


#define chipBootpTimerExpired   chipTimerExpired
#define chipBootpTimerDisable   chipTimerDisable

#define DEVICE_MAX_SGMII_RETRY  2500     /* Each cycle through is 100 us, so total delay is about 250 msec */

/****************************************************************************
 * Definition: The size of the CPPI descriptors used for ethernet and srio.
 *             The descriptors must be a multiple of 16 bytes.
 ****************************************************************************/
#define DEVICE_CPPI_SIZE_UINT8        (QM_DESC_SIZE_BYTES)             /* SRIO uses these directly */
#define DEVICE_CPPI_SIZE_UINT16       (QM_DESC_SIZE_BYTES >> 1)

#define DEVICE_ETH_CPPI_SIZE_UINT8     DEVICE_CPPI_SIZE_UINT8
#define DEVICE_ETH_CPPI_SIZE_UINT16    DEVICE_CPPI_SIZE_UINT16

#define DEVICE_SRIO_CPPI_SIZE_UINT8    DEVICE_CPPI_SIZE_UINT8
#define DEVICE_SRIO_CPPI_SIZE_UINT16   DEVICE_CPPI_SIZE_UINT16



/*******************************************************************************
 * The SRIO node id is always set for discovery, and by default always 
 * in boot table mode.
 *******************************************************************************/
#define chipGetDefaultRapidIoNodeId()           0xffff
#define chipGetDefaultRapidIoOpts_Secure        keystoneDefaultRapidIoOpts
#define chipGetDefaultRapidIoOpts_NonSec        keystoneDefaultRapidIoOpts
#define chipGetDefaultRapidIoPfLow()            0
#define chipGetDefaultRapidIoPfHigh()           0
#define chipGetDefaultRapidIoPll()              chipDefaultPll(TRUE)    /* TRUE indicates the min pin is valid */
#define chipGetDefaultRapidIoPll2()             chipDefaultArmPll(TRUE)
#define chipGetDefaultRapidIoIndex()            0
#define chipGetDefaultRapidIoPortNum()          BOOT_PARAMS_ALL_PORTS
#define chipGetDefaultRapidIoPromiscuousMask()  ((1 << DEVICE_RIO_N_LANES) - 1) 
#define chipGetDefaultRapidIoTimeout()          0

#define NYSH_SET_SRIO_SERDES_MASTER_BIT(v,x)  (v) = BOOT_SET_BITFIELD(v,x,20,20)
#define DEVICE_SRIO_PORT_OK_LOOP_COUNT      10000  /* Each iteration is 10us, so this gives a max of 100 msec */

#define chipSrioTimerExpired                chipTimerExpired
#define chipSrioTimerDisable                chipTimerDisable
#define chipSrioTimerSetup                  chipTimerSetupSeconds

#define chipSrioSetPortLaneMaster(x,y)      /* Empty for snowbush */

#define DEVICE_SRIO_VMIN_VAL              0xf        /* The value placed into the srio vmin field */
#define DEVICE_SRIO_SP0_WATERMARK_VALUE   0x3f       /* The value placed in the srio watermakr regs */

/********************************************************************************
 * PCIe boot mode
 ********************************************************************************/
#define chipDefaultPciePll()                chipDefaultPll(FALSE)       /* False means the min pin is not valid */
#define chipDefaultPciePll2()               chipDefaultArmPll(FALSE)
#define chipDefaultPcieOptions()            0
#define chipDefaultPcieSerdesCfg            hwSerdesFormCfg
#define chipDefaultPcieLinkRateMhz()        2500         /* Always 2.5GBs. PCIe will convert to 5.0GBs for gen2 */
#define chipDefaultPcieLane0Cfg()           0x00062320   /* Not a standard draco register, but in PCIe */
#define chipDefaultPcieLane1Cfg()           0x00022320
#define chipInitPcieSerdesVal()             0x00000100   /* Enable endiv clock by default */

 /* PCIe device ID. It is stored in a chip level register intialized by the boot code at chipSetEntryState */
#define chipDefaultPcieDeviceId()           chipUpper16(DEVICE_REG_PCIE_VENDOR_ID)
#define chipDefaultPcieVendorId()           chipLower16(DEVICE_REG_PCIE_VENDOR_ID)
#define chipDefaultPcieClassCodeRevId()     0x04800001   /* Class 4 */

#define chipDefaultPcieWindow1Size()        chipDefaultPcieWindowSize(1)
#define chipDefaultPcieWindow2Size()        chipDefaultPcieWindowSize(2)
#define chipDefaultPcieWindow3Size()        chipDefaultPcieWindowSize(3)
#define chipDefaultPcieWindow4Size()        chipDefaultPcieWindowSize(4)
#define chipDefaultPcieWindow5Size()        chipDefaultPcieWindowSize(4)    /* Window 5 is always the same as window 4 */

#define chipDefaultPcieTimerRefMHz          chipSysFreqMhz
#define chipDefaultPcieTimeout()            0                   /* Timeout disabled by default */

#define DEVICE_PCIE_LINK_UP_LOOP_COUNT      10000  /* Each iteration is 10us, so this gives a max of 100 msec */

#define chipPcieTimerExpired                chipTimerExpired
#define chipPcieTimerDisable                chipTimerDisable
#define chipPcieTimerSetup                  chipTimerSetupSeconds


/* For both PCIe and hyperlink mode the direct download size is input to the bootProc function.
 * For non-secure modes this is entirely unused, for arm master secure this is the size of the 
 * TOC image The maximum size must be big enough to cover any toc in MSMC */
#define DEVICE_BOOTPROC_SIZE_DIRECT_WRITE   0x40000000



/*******************************************************************************
 * NAND boot mode
 *******************************************************************************/
#define chipDefaultNandPll()                    chipDefaultPll(TRUE)        /* TRUE indicates the min pin is valid */
#define chipDefaultNandPll2()                   chipDefaultArmPll(TRUE)
#define chipDefaultNandPortNum()                0
#define chipDefaultNandNumColumnAddrBytes()     0
#define chipDefaultNandNumRowAddrBytes()        0
#define chipDefaultNandNumDataBytesPerPage()    0
#define chipDefaultNandNumPagesPerBlock()       0
#define chipDefaultNandNumPagesPerBlock()       0
#define chipDefaultNandBusWidth()               0
#define chipDefaultNandNumSpareBytesPerPage()   0

#define CHIP_NAND_FIRST_BLOCK_STEP          16      /* The first block can be 0, 16, 32, etc */

/*******************************************************************************
 * Hibernation recovery
 *******************************************************************************/
#define chipDefaultHibRecoveryPll()       ((BOOT_PARAMS_PLL_CFG_CTL_NO_INIT << BOOT_PARAMS_PLL_CFG_CTL_SHIFT) << 16)
#define chipDefaultHibRecoveryPll2()      ((BOOT_PARAMS_PLL_CFG_CTL_NO_INIT << BOOT_PARAMS_PLL_CFG_CTL_SHIFT) << 16)
#define chipDefaultHibRecoveryType()       (chipReadPwrStateBits (PWRSTATECTL_BITS_MODE_MSB,   PWRSTATECTL_BITS_MODE_LSB)   + BOOT_PARAMS_RECOVERY_TYPE_1)
#define chipDefaultHibRecoveryAddr()       (chipReadPwrStateBits (PWRSTATECTL_BITS_BRANCH_MSB, PWRSTATECTL_BITS_BRANCH_LSB) << PWRSTATECTL_BITS_BRANCH_LSB)
#define chipDefaultHibRecoveryXipWidth()  ((chipReadPwrStateBits (PWRSTATECTL_BITS_WIDTH_MSB,  PWRSTATECTL_BITS_WIDTH_LSB)  * 8) + 8)
#define chipDefaultHibRecoveryXipWait()    (chipReadPwrStateBits (PWRSTATECTL_BITS_WAIT_MSB,   PWRSTATECTL_BITS_WAIT_LSB) == PWRSTATECTL_FIELD_WAIT_ENABLE)
#define chipDefaultHibRecoverySysFreqMhz()  DEVICE_MAX_REF_FREQ_MHZ
#define chipDefaultHibRecoveryCoreFreqMhz() DEVICE_MAX_REF_FREQ_MHZ

#define chipDisableEmifSelfRefresh()      hwEmif4SetSelfRefresh(DEVICE_EMIF4_BASE, FALSE)
#define chipEmif4PhyHibRecovery()         phyRestore (DEVICE_EMIF4_PHY_BASE)

#define DEVICE_PHY_RESTORE_MAX_RETRIES      3


/*******************************************************************************
 * Sleep
 *******************************************************************************/

/*******************************************************************************
 * Definition: The minimum frequency of the DDR, in MHz. This is used to 
 *             compute a delay needed for PLL lock
 *
 *             800 MHz is the typical operation, but 400 is the minimum
 *******************************************************************************/
#define DEVICE_MIN_DDR_FREQ_MHZ     400

/**********************************************************************************
 * Default DDR3 config
 **********************************************************************************/
#define mainGetExtMemParams                         mainEmif4Params
#define mainExtMemConfig                            mainEmif4Cfg
#define chipConfigEmif4                             hwConfigEmif4v

/* Phy timeout values */
#define DEVICE_DDR3_POLL_LOOP_COUNT                  1000
#define DEVICE_DDR3_POLL_LOOP_CYCLE_DELAY_VAL        DEVICE_MAX_FREQ_MHZ

/**************************************************************************
 * After every boot table block is complete check if the DDR config table
 * has been modified, and if the PCIe table has been modified.
 **************************************************************************/
#define chipPciBlockDone()    mainEmif4Cfg(); chipPcieBlockProcess()
#define chipRioBlockDone()    mainEmif4Cfg(); chipPcieBlockProcess()
#define chipHyperBlockDone()  mainEmif4Cfg(); chipPcieBlockProcess()

#ifdef _TMS320C6X
 #define chipBtblBlockDone()  mainEmif4Cfg(); chipPcieBlockProcess()
#else

 #ifdef __TMS470__
  #define chipBtblBlockDone()
 #endif
 
#endif

/* Both the ARM and DSP support the emif4 table from TOC and from GP headers */
#define chipEmifCfg    mainEmif4Cfg


/*********************************************************************************
 * Definition: The keystone DDR PLL is controlled through the chip pll driver
 *********************************************************************************/
#define chipCfgDdrPll           hwCfgPllEnable
#define chipCfgDdrPllIsEnabled  hwCfgPllIsEnabled


/*******************************************************************************
 * Connect chipDelay to the assembly function chipDelay32
 *******************************************************************************/
#define chipDelay(x)            chipDelay32(x)


/*******************************************************************************
 * Definition: The timer disable is directly connected to the hardware call
 *******************************************************************************/
#define chipDisableEthTimer         hwTimer64Disable

/********************************************************************************
 * Definition: The minimum frequency of the PA, in MHz. This is used to
 *             compute a delay needed for the PLL lock
 *
 *             The PA should run at 350 MHz, but use 300 for safety
 ********************************************************************************/
#define DEVICE_MIN_PA_FREQ_MHZ      300

/***************************************************************************
 * Disable chip unlocks due to cross core issues
 ***************************************************************************/
#define chipKickUnlock()
#define chipKickLock()

/*******************************************************************************
 * The primary PLL controller requires chip level registers for some
 * configuration.
 *******************************************************************************/
#define chipPllExternalPrediv(x)    TRUE

/*******************************************************************************
 * No secondary core cleanup required
 *******************************************************************************/
#define chipSecCleanup()        /* empty */

/*******************************************************************************
 * Set the boot complete in the boot status register
 *******************************************************************************/ 
#define chipStatusBootComplete()          chipSetBPField(1,                                     \
                                                         BOOTPROG_BITS_ALL_COMPLETE_MSB,        \
                                                         BOOTPROG_BITS_ALL_COMPLETE_LSB)

/****************************************************************************
 * Definition: Max number of times the boot code will attempt to write
 *             to the boot complete register before giving up.
 ****************************************************************************/
#define DEVICE_MAX_BC_RETRY     100

/* The wake any interrupt flag must not conflict with a single interrupt value */
#define DEVICE_SLEEP_ANY_FAST_WAKEUP    0xffff


/******************************************************************************* 
 * Macros for default I2C configuration. These will override the prototypes in
 * chip.h. 
 *******************************************************************************/
#define chipDefaultI2cAddressDelay(x,y)     0x200
#define chipI2cModuleDivisor()              6
#define chipDefaultI2cFreqKhz(x,y)          20
#define chipDefaultI2cXmitId(x,y)           0x11
#define DEVICE_I2C_ADDRESS_WHEN_MASTER      0x10
#define DEVICE_I2C_ADDRESS_MULTIPLIER       0x10    /* 0x10 times the pin value is the slave addr */
#define DEVICE_I2C_GP_OFFSET_FACTOR         0x2000  /* Index into i2c when in GP header mode */

/*********************************************************************************
 * SPI boot mode
 *********************************************************************************/
#define chipDefaultSpiBusFreq100Khz()       5   /* 500 kHz default */
#define chipDefaultSpiNextCsel()            0
#define chipDefaultSpiNextReadAddr()        0
#define chipDefaultSpiC2tDelay()            1
#define chipDefaultSpiPll                   chipDefaultSpiPll_common
#define chipDefaultSpiPll2                  chipDefaultSpiPll_common

/*********************************************************************************
 * VUSR boot mode
 *********************************************************************************/
#define chipDefaultHyperPll()                chipDefaultPll(FALSE)          /* False means MIN pin not valid */
#define chipDefaultHyperPll2()               chipDefaultArmPll(FALSE)
#define chipDefaultHyperOptions()            0
#define chipDefaultHyperTimeoutSec()         0
#define chipDefaultHyperNlanes()             4
#define chipDefaultHyperSerdesCfgRxLane0     chipDefaultHyperSerdesRxCfg
#define chipDefaultHyperSerdesCfgRxLane1     chipDefaultHyperSerdesRxCfg
#define chipDefaultHyperSerdesCfgRxLane2     chipDefaultHyperSerdesRxCfg
#define chipDefaultHyperSerdesCfgRxLane3     chipDefaultHyperSerdesRxCfg
#define chipDefaultHyperSerdesCfgTxLane0()  (chipDefaultHyperSerdesTxCfg() | (1 << 20))  /* Master sync only for lane 0 */
#define chipDefaultHyperSerdesCfgTxLane1     chipDefaultHyperSerdesTxCfg
#define chipDefaultHyperSerdesCfgTxLane2     chipDefaultHyperSerdesTxCfg
#define chipDefaultHyperSerdesCfgTxLane3     chipDefaultHyperSerdesTxCfg
#define chipDefaultHyperSerdesTxCfg()        0
#define chipDefaultHyperSerdesRxCfg()        0

#define chipHyperTimerExpired                chipTimerExpired
#define chipHyperTimerDisable                chipTimerDisable
#define chipHyperTimerSetup                  chipTimerSetupSeconds

/*********************************************************************************
 * EMIF boot mode
 *********************************************************************************/
#define chipDefaultEmifOptions(x)           0
#define chipDefaultEmifType(x)              BOOT_PARAMS_EMIF_TYPE_NOR
#define chipDefaultEmifNorAsyncCfg(x)       0
#define chipEmif25DataSizeBytes()           0x04000000  /* 64 Mb in each cs region */
#define CHIP_EMIF25_OFFSET_INC              0x01000000  /* 16 Mb offset increments */
#define chipDefaultEmifPll()                chipDefaultPll(FALSE)      /* FALSE indicates the min pin is not valid */ 
#define chipDefaultEmifPll2()               chipDefaultArmPll(FALSE)

/*******************************************************************************
 * UART boot mode
 *******************************************************************************/
#define chipDefaultUartPll()                chipDefaultPll(TRUE)        /* TRUE indicates the min pin is valid */
#define chipDefaultUartPll2()               chipDefaultArmPll(TRUE)
#define chipDefaultUartOptions()            0
#define chipDefaultUartProtocol()           BOOT_PARAMS_UART_PROTOCOL_XMODEM
#define chipDefaultUartInitialNackCount()   10
#define chipDefaultUartMaxErrorCount()      10
#define chipDefaultUartNackTimeoutSec()     3
#define chipDefaultUartCharTimeoutMsec()    2
#define chipDefaultUartNDataBits()          8
#define chipDefaultUartNStopBitsx2()        2
#define chipDefaultUartOverSampleFactor()   16
#define chipDefaultUartFlowControl()        BOOT_PARAMS_FLOW_CONTROL_NONE
#define chipDefaultUartDataRate()           115200
#define chipDefaultUartParity()             BOOT_PARAMS_UART_PARITY_NONE

#define chipUartTimerSetup(x,y)             chipTimerSetupMiliSeconds(x,y); while (chipTimerGetLsw() == 0);
#define chipUartTimerExpired                chipTimerExpired
#define chipUartTimerDisable                chipTimerDisable


/*******************************************************************************
 * There is no default exit address. It must always be set during boot
 *******************************************************************************/
#define chipEventExitAddress()      *p_boot_entry_addr


/**************************************************************************
 * Only one kick mechanism. Disabled during boot due to cross
 * core issues.
 **************************************************************************/
#define chipKickOpenSerdes(x)
#define chipKickClosedSerdes(x)


/******************************************************************************
 * Definition: The command value received through the jtag communication
 *             register which will have the boot code return any error codes
 ******************************************************************************/
#define DEVICE_JTAG_CMD_SHOW_BOOT_ERROR     1

/******************************************************************************
 * Definition: Return the arg. Required on some compilers to remove 
 *             endian problems
 ******************************************************************************/
#define chipReturnArg(x)    (x)

/******************************************************************************
 * Definition: The number of GEM cores on the device
 ******************************************************************************/
#define DEVICE_NGEMS   8

/******************************************************************************
 * Definition: The cache commands plug directly into the driver
 ******************************************************************************/
#define chipFlushCache        hwFlushCache
#define chipInvalidateCache   hwInvalidateCache
#define chipCleanCache        hwCleanCacheByAddr

/******************************************************************************
 * Definition: Disable interrupts
 ******************************************************************************/
#ifdef _TMS320C6X
 #define chipDisableInts()  IER=1
#else

 #ifndef __TMS470__
  #error Unknown processor type
 #endif
 
#endif

/******************************************************************************
 * Definition: Disable the SRIO reset isolation. A full chip reset is
 *             being done and SRIO must be reset as well
 ******************************************************************************/
#define chipDisableSrioResetIso()   pscClearResetIso (DEVICE_LPSC_MODNUM_SRIO)

/******************************************************************************
 * Definition: Hardware chip reset is done through the pll controller
 ******************************************************************************/
#define chipHwReset hwPllDeviceReset


/******************************************************************************
 * Definition: The ARM non secure interrupt priority. It set to the highest
 *             non-secure priority level of 0x80
 ******************************************************************************/
#define DEVICE_GIC_INT_BOOT_NONSEC_PRIORITY   0x80


/******************************************************************************
 * Definition: The ROM key access values
 ******************************************************************************/
#define DEVICE_INITIAL_SEC_KEY_CTL_VAL          (SEC_FIELD_KEY_CTL_MEK_ACCESS_RW   | SEC_FIELD_KEY_CTL_KEK_ACCESS_RW)
#define DEVICE_TI_KEYS_ACTIVE                   (SEC_FIELD_KEY_CTL_MEK_ACCESS_RW   | SEC_FIELD_KEY_CTL_KEK_ACCESS_RW | SEC_FIELD_KEY_CTL_LOCK)
#define DEVICE_DISABLE_TI_MEK_SEC_KEY_CTL_VAL   (SEC_FIELD_KEY_CTL_MEK_ACCESS_NONE | SEC_FIELD_KEY_CTL_KEK_ACCESS_RW | SEC_FIELD_KEY_CTL_LOCK)
#define DEVICE_DISABLE_ALL_SEC_KEY_CTL_VAL      (SEC_FIELD_KEY_CTL_KEY_DISABLE     | SEC_FIELD_KEY_CTL_LOCK)


/******************************************************************************
 * ARM translation table block sizes. These serve as placeholders for
 * the linker and locate the block in memory for the code.
 ******************************************************************************/
#define DEVICE_ARM_TTBL_L0_BLOCK_SIZE_BYTES     0x0020
#define DEVICE_ARM_TTBL_L1_BLOCK_SIZE_BYTES     0x1000
#define DEVICE_ARM_PAGE_TBL_BLOCK_SIZE_BYTES    0x1000

/******************************************************************************
 * The local memory block size. Each core gets this memory block remapped
 * from the unique physical address to the common virtual address.
 ******************************************************************************/
#define DEVICE_ARM_LOCAL_VA_SIZE_BYTES          0x04000
#define DEVICE_ARM_LOCAL_SEC_VA_SIZE_BYTES      0x08000

/******************************************************************************
 * The amount of stack memory needed to create the snowbush serdes configuration.
 * The value is verfied at compile time
 ******************************************************************************/
#define SNOWBUSH_MAX_CONFIG_SIZE_32        (58 * sizeof(sbCfg_t))    /* 58 entries */


/******************************************************************************
 * Prototype: The ARM monitor function. Used to execute a function from the
 *            monitor state.
 ******************************************************************************/
void monitorFunction (void (*fcn)(), ...);

/******************************************************************************
 * Top level Snowbush serdes api
 ******************************************************************************/
#define SB_INVALID_REF          -1
#define SB_INVALID_RATE         -2
#define SB_INVALID_PERIPH       -3
#define SNOWBUSH_PERIPH_PCIE    100
#define SNOWBUSH_PERIPH_ETH     101
#define SNOWBUSH_PERIPH_SRIO    102
#define SNOWBUSH_PERIPH_HYPER   103

/******************************************************************************
 * The chipIsMaster function as a macro. 
 *     xfn becomes the name of the function. 
 *     lxfn is the call to the assembly function amIBootMaster in the
 *       correct context
 *
 * Defined as a macro so two identical copies can be made, for different
 * contexts
 *
 *   !For GEM only!
 ******************************************************************************/
 #define HIB_REG   DEVICE_REG_POWER_STATE_CTL
 #define HIB_MSB   PWRSTATECTL_BITS_HIBERNATION_MSB
 #define HIB_LSB   PWRSTATECTL_BITS_HIBERNATION_LSB
 
 #define MSTR_REG  DEVICE_REG_POWER_STATE_CTL
 #define MSTR_MSB  PWRSTATECTL_BITS_RECOVERY_MASTER_MSB
 #define MSTR_LSB  PWRSTATECTL_BITS_RECOVERY_MASTER_LSB
 


 
#define CHIP_IS_BOOT_MASTER(xfn, lxfn)                                                      \
 
        
/******************************************************************************
 * Globals defined in keystone.c but shared between DSP and ARM
 ******************************************************************************/
extern UINT32 magicAddr;
extern UINT32 armMagicAddr[];

/************************************************************************************************
 * the chipReadNumArms function is inlined in keystone2_inline.h. But the default definition
 * is in chip.h. By defining the function here to be empty it prevents the default definition
 * from conflicting with the inline function
 ************************************************************************************************/
#define chipReadNumArms

/************************************************************************************************
 * QmQueue configuration
 ************************************************************************************************/
#ifndef chipQueuePush
void chipQueuePush  (void *hd, UINT32 qnum, UINT32 descrSize);
#endif

#ifndef chipQueuePop
void *chipQueuePop (UINT32 qnum);
#endif

#ifdef _TMS320C6X
#define chipSystemNand()
#else
#define chipSystemNand() hwDisableDCache()
#endif


/**************************************************************************************************
 * Function written for arm startup that do not use the stack
 **************************************************************************************************/
#define  ARM_NO_STACK_NOT_MASTER        FALSE
#define  ARM_NO_STACK_MASTER            TRUE
#define  ARM_NO_STACK_KEEP_CHECKING     2

/******************************************************************************************
 * Definition: Powered down GEM values. The IPC bit 4 is used
 ******************************************************************************************/
#define DEVICE_GEM_PDOWN_VAL    (1 << 4)

#endif /* _KEYSTONE_H */



