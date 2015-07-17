/* The header file is generated by make_header.py from EFUSE.json */
/* Current script's version can be found at: */
/* https://github.com/AoLaD/rtems-tms570-utils/tree/headers/headers/python */

/*
 * Copyright (c) 2014-2015, Premysl Houdek <kom541000@gmail.com>
 *
 * Czech Technical University in Prague
 * Zikova 1903/4
 * 166 36 Praha 6
 * Czech Republic
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.
*/
#ifndef LIBBSP_ARM_TMS570_EFUSE
#define LIBBSP_ARM_TMS570_EFUSE

#include <bsp/utility.h>

typedef struct{
  uint32_t EFCBOUND;          /*EFC Boundary Control Register*/
  uint8_t reserved1 [12];
  uint32_t EFCPINS;           /*EFC Pins Register*/
  uint8_t reserved2 [12];
  uint32_t EFC_ERR_STAT;      /*EFC Error Status Register*/
  uint8_t reserved3 [8];
  uint32_t EFC_ST_CY;         /*EFC Self Test Cycles Register*/
  uint32_t EFC_ST_SIG;        /*EFC Self Test Signature Register*/
} tms570_efuse_t;


/*-------------------TMS570_EFUSE_EFCBOUND-------------------*/
/* field: EFC_Self_Test_Error - This bit drives the self test error signal when bit 17 (Self Test Error OE) is high. */
#define TMS570_EFUSE_EFCBOUND_EFC_Self_Test_Error BSP_BIT32(21)

/* field: EFC_Single_Bit_Error - This bit drives the single bit error signal when bit 16 (Single bit Error OE) is high. */
#define TMS570_EFUSE_EFCBOUND_EFC_Single_Bit_Error BSP_BIT32(20)

/* field: EFC_Instruction_Error - This bit drives the instruction error signal when bit 15 (Instruction Error OE) is high. */
#define TMS570_EFUSE_EFCBOUND_EFC_Instruction_Error BSP_BIT32(19)

/* field: EFC_Autoload_Error - This bit drives the Autoload Error signal when bit 14 (Autoload Error OE) is high. */
#define TMS570_EFUSE_EFCBOUND_EFC_Autoload_Error BSP_BIT32(18)

/* field: Self_Test_Error_OE - The Self Test Error Output Enable bit determines if the EFC Self Test signal comes from the */
#define TMS570_EFUSE_EFCBOUND_Self_Test_Error_OE BSP_BIT32(17)

/* field: Single_Bit_Error_OE - The single bit error output enable signal determines if the EFC Single Bit Error signal comes */
#define TMS570_EFUSE_EFCBOUND_Single_Bit_Error_OE BSP_BIT32(16)

/* field: Instruction_Error_OE - comes from the eFuse controller or from bit 19 of the boundary register. */
#define TMS570_EFUSE_EFCBOUND_Instruction_Error_OE BSP_BIT32(15)

/* field: Autoload_Error_OE - The autoload error output enable signal determines if the EFC Autoload Error signal comes */
#define TMS570_EFUSE_EFCBOUND_Autoload_Error_OE BSP_BIT32(14)

/* field: EFC_ECC_Selftest - The eFuse Controller ECC Selftest Enable bit starts the selftest of the ECC logic if the four */
#define TMS570_EFUSE_EFCBOUND_EFC_ECC_Selftest BSP_BIT32(13)

/* field: Input_Enable - The eFuse Controller ECC Selftest Enable bit starts the selftest of the ECC logic if the four */
#define TMS570_EFUSE_EFCBOUND_Input_Enable(val) BSP_FLD32(val,0, 3)
#define TMS570_EFUSE_EFCBOUND_Input_Enable_GET(reg) BSP_FLD32GET(reg,0, 3)
#define TMS570_EFUSE_EFCBOUND_Input_Enable_SET(reg,val) BSP_FLD32SET(reg, val,0, 3)


/*--------------------TMS570_EFUSE_EFCPINS--------------------*/
/* field: EFC_Selftest_Done - This bit can be polled to determine when the EFC ECC selftest is complete */
#define TMS570_EFUSE_EFCPINS_EFC_Selftest_Done BSP_BIT32(15)

/* field: EFC_Selftest_Error - This bit indicates the pass/fail status of the EFC ECC Selftest once the EFC Selftest Done */
#define TMS570_EFUSE_EFCPINS_EFC_Selftest_Error BSP_BIT32(14)

/* field: EFC_Single_Bit_Error - This bit indicates if a single bit error was corrected by the ECC logic during the autoload */
#define TMS570_EFUSE_EFCPINS_EFC_Single_Bit_Error BSP_BIT32(12)

/* field: EFC_Instruction_Error - This bit indicates an error occured during a factory test or program operation. */
#define TMS570_EFUSE_EFCPINS_EFC_Instruction_Error BSP_BIT32(11)

/* field: EFC_Autoload_Error - This bit indicates that some non-correctable error occurred during the autoload sequence */
#define TMS570_EFUSE_EFCPINS_EFC_Autoload_Error BSP_BIT32(10)


/*-----------------TMS570_EFUSE_EFC_ERR_STAT-----------------*/
/* field: Instruc_Done - Instruction done. */
#define TMS570_EFUSE_EFC_ERR_STAT_Instruc_Done BSP_BIT32(5)

/* field: Error_Code - The error status of the last instruction executed by the eFuse Controller */
#define TMS570_EFUSE_EFC_ERR_STAT_Error_Code(val) BSP_FLD32(val,0, 4)
#define TMS570_EFUSE_EFC_ERR_STAT_Error_Code_GET(reg) BSP_FLD32GET(reg,0, 4)
#define TMS570_EFUSE_EFC_ERR_STAT_Error_Code_SET(reg,val) BSP_FLD32SET(reg, val,0, 4)


/*-------------------TMS570_EFUSE_EFC_ST_CY-------------------*/
/* field: Cycles - This register is used to determine the number of cycles to run the eFuse controller ECC logic self test. */
/* Whole 32 bits */

/*------------------TMS570_EFUSE_EFC_ST_SIG------------------*/
/* field: Signature - This register is used to hold the expected signature for the eFuse ECC logic self test. */
/* Whole 32 bits */


#endif /* LIBBSP_ARM_TMS570_EFUSE */
