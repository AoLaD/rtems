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

#ifndef LIBBSP_ARM_tms570_EMIF
#define LIBBSP_ARM_tms570_EMIF

#include <bsp/utility.h>

typedef struct{
  uint32_t MIDR;              /*Module ID Register*/
  uint32_t AWCC;              /*Asynchronous Wait Cycle Configuration Register*/
  uint32_t SDCR;              /*SDRAM Configuration Register*/
  uint32_t SDRCR;             /*SDRAM Refresh Control Register*/
  uint32_t CE2CFG;            /*Asynchronous 1 Configuration Register*/
  uint32_t CE3CFG;            /*Asynchronous 2 Configuration Register*/
  uint32_t CE4CFG;            /*Asynchronous 3 Configuration Register*/
  uint32_t CE5CFG;            /*Asynchronous 4 Configuration Register*/
  uint32_t SDTIMR;            /*SDRAM Timing Register*/
  uint8_t reserved1 [24];
  uint32_t SDSRETR;           /*SDRAM Self Refresh Exit Timing Register*/
  uint32_t INTRAW;            /*EMIF Interrupt Raw Register*/
  uint32_t INTMSK;            /*EMIF Interrupt Mask Register*/
  uint32_t INTMSKSET;         /*EMIF Interrupt Mask Set Register*/
  uint32_t INTMSKCLR;         /*EMIF Interrupt Mask Clear Register*/
  uint8_t reserved2 [24];
  uint32_t PMCR;              /*Page Mode Control Register*/
} tms570_emif_t;


/*----------------------TMS570_EMIFMIDR----------------------*/
/* field: REV - Module ID of EMIF. See the device-specific data manual. */
#define TMS570_EMIF_MIDR_REV(val) BSP_FLD32(val,0, 31)
#define TMS570_EMIF_MIDR_REV_GET(reg) BSP_FLD32GET(reg,0, 31)
#define TMS570_EMIF_MIDR_REV_SET(reg,val) BSP_FLD32SET(reg, val,0, 31)


/*----------------------TMS570_EMIFAWCC----------------------*/
/* field: WP1 - EMIF_nWAIT[1] polarity bit. This bit defines the polarity of the EMIF_nWAIT[1] pin. */
#define TMS570_EMIF_AWCC_WP1 BSP_FLD32(29)

/* field: WP0 - EMIF_nWAIT[0] polarity bit. This bit defines the polarity of the EMIF_nWAIT[0] pin. */
#define TMS570_EMIF_AWCC_WP0 BSP_FLD32(28)

/* field: CS5_WAIT - Chip Select 5 WAIT signal selection. */
#define TMS570_EMIF_AWCC_CS5_WAIT(val) BSP_FLD32(val,22, 23)
#define TMS570_EMIF_AWCC_CS5_WAIT_GET(reg) BSP_FLD32GET(reg,22, 23)
#define TMS570_EMIF_AWCC_CS5_WAIT_SET(reg,val) BSP_FLD32SET(reg, val,22, 23)

/* field: CS4_WAIT - Chip Select 4 WAIT signal selection. */
#define TMS570_EMIF_AWCC_CS4_WAIT(val) BSP_FLD32(val,20, 21)
#define TMS570_EMIF_AWCC_CS4_WAIT_GET(reg) BSP_FLD32GET(reg,20, 21)
#define TMS570_EMIF_AWCC_CS4_WAIT_SET(reg,val) BSP_FLD32SET(reg, val,20, 21)

/* field: CS3_WAIT - be used for memory accesses to chip select 3 memory space. */
#define TMS570_EMIF_AWCC_CS3_WAIT(val) BSP_FLD32(val,18, 19)
#define TMS570_EMIF_AWCC_CS3_WAIT_GET(reg) BSP_FLD32GET(reg,18, 19)
#define TMS570_EMIF_AWCC_CS3_WAIT_SET(reg,val) BSP_FLD32SET(reg, val,18, 19)

/* field: CS2_WAIT - Chip Select 2 WAIT signal selection. */
#define TMS570_EMIF_AWCC_CS2_WAIT(val) BSP_FLD32(val,16, 17)
#define TMS570_EMIF_AWCC_CS2_WAIT_GET(reg) BSP_FLD32GET(reg,16, 17)
#define TMS570_EMIF_AWCC_CS2_WAIT_SET(reg,val) BSP_FLD32SET(reg, val,16, 17)

/* field: MAX_EXT_WAIT - Maximum extended wait cycles. */
#define TMS570_EMIF_AWCC_MAX_EXT_WAIT(val) BSP_FLD32(val,0, 7)
#define TMS570_EMIF_AWCC_MAX_EXT_WAIT_GET(reg) BSP_FLD32GET(reg,0, 7)
#define TMS570_EMIF_AWCC_MAX_EXT_WAIT_SET(reg,val) BSP_FLD32SET(reg, val,0, 7)


/*----------------------TMS570_EMIFSDCR----------------------*/
/* field: SR - Self-Refresh mode bit. */
#define TMS570_EMIF_SDCR_SR BSP_FLD32(31)

/* field: PD - Power Down bit. This bit controls entering and exiting of the power-down mode. */
#define TMS570_EMIF_SDCR_PD BSP_FLD32(30)

/* field: PDWR - Perform refreshes during power down. */
#define TMS570_EMIF_SDCR_PDWR BSP_FLD32(29)

/* field: NM - Narrow mode bit. This bit defines whether a 16- or 32-bit-wide SDRAM is connected to the EMIF. */
#define TMS570_EMIF_SDCR_NM BSP_FLD32(14)

/* field: CL - CAS Latency. */
#define TMS570_EMIF_SDCR_CL(val) BSP_FLD32(val,9, 11)
#define TMS570_EMIF_SDCR_CL_GET(reg) BSP_FLD32GET(reg,9, 11)
#define TMS570_EMIF_SDCR_CL_SET(reg,val) BSP_FLD32SET(reg, val,9, 11)

/* field: BIT11_9LOCK - Bits 11 to 9 lock. CL can only be written if BIT11_9LOCK is simultaneously written with a 1. */
#define TMS570_EMIF_SDCR_BIT11_9LOCK BSP_FLD32(8)

/* field: IBANK - Internal SDRAM Bank size. */
#define TMS570_EMIF_SDCR_IBANK(val) BSP_FLD32(val,4, 6)
#define TMS570_EMIF_SDCR_IBANK_GET(reg) BSP_FLD32GET(reg,4, 6)
#define TMS570_EMIF_SDCR_IBANK_SET(reg,val) BSP_FLD32SET(reg, val,4, 6)

/* field: PAGESIZE - Page Size. This field defines the internal page size of connected SDRAM devices. */
#define TMS570_EMIF_SDCR_PAGESIZE(val) BSP_FLD32(val,0, 2)
#define TMS570_EMIF_SDCR_PAGESIZE_GET(reg) BSP_FLD32GET(reg,0, 2)
#define TMS570_EMIF_SDCR_PAGESIZE_SET(reg,val) BSP_FLD32SET(reg, val,0, 2)


/*----------------------TMS570_EMIFSDRCR----------------------*/
/* field: RR - Refresh Rate. This field is used to define the SDRAM refresh period in terms of EMIF_CLK cycles. */
#define TMS570_EMIF_SDRCR_RR(val) BSP_FLD32(val,0, 12)
#define TMS570_EMIF_SDRCR_RR_GET(reg) BSP_FLD32GET(reg,0, 12)
#define TMS570_EMIF_SDRCR_RR_SET(reg,val) BSP_FLD32SET(reg, val,0, 12)


/*---------------------TMS570_EMIFCE2CFG---------------------*/
/* field: SS - Select Strobe bit. */
#define TMS570_EMIF_CE2CFG_SS BSP_FLD32(31)

/* field: EW - Extend Wait bit. This bit defines whether extended wait cycles will be enabled. See Section 17.2.6. */
#define TMS570_EMIF_CE2CFG_EW BSP_FLD32(30)

/* field: W_SETUP - Write setup width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE2CFG_W_SETUP(val) BSP_FLD32(val,26, 29)
#define TMS570_EMIF_CE2CFG_W_SETUP_GET(reg) BSP_FLD32GET(reg,26, 29)
#define TMS570_EMIF_CE2CFG_W_SETUP_SET(reg,val) BSP_FLD32SET(reg, val,26, 29)

/* field: W_STROBE - Write strobe width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE2CFG_W_STROBE(val) BSP_FLD32(val,20, 25)
#define TMS570_EMIF_CE2CFG_W_STROBE_GET(reg) BSP_FLD32GET(reg,20, 25)
#define TMS570_EMIF_CE2CFG_W_STROBE_SET(reg,val) BSP_FLD32SET(reg, val,20, 25)

/* field: W_HOLD - Write hold width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE2CFG_W_HOLD(val) BSP_FLD32(val,17, 19)
#define TMS570_EMIF_CE2CFG_W_HOLD_GET(reg) BSP_FLD32GET(reg,17, 19)
#define TMS570_EMIF_CE2CFG_W_HOLD_SET(reg,val) BSP_FLD32SET(reg, val,17, 19)

/* field: R_SETUP - Read setup width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE2CFG_R_SETUP(val) BSP_FLD32(val,13, 16)
#define TMS570_EMIF_CE2CFG_R_SETUP_GET(reg) BSP_FLD32GET(reg,13, 16)
#define TMS570_EMIF_CE2CFG_R_SETUP_SET(reg,val) BSP_FLD32SET(reg, val,13, 16)

/* field: R_STROBE - Read strobe width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE2CFG_R_STROBE(val) BSP_FLD32(val,7, 12)
#define TMS570_EMIF_CE2CFG_R_STROBE_GET(reg) BSP_FLD32GET(reg,7, 12)
#define TMS570_EMIF_CE2CFG_R_STROBE_SET(reg,val) BSP_FLD32SET(reg, val,7, 12)

/* field: R_HOLD - Read hold width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE2CFG_R_HOLD(val) BSP_FLD32(val,4, 6)
#define TMS570_EMIF_CE2CFG_R_HOLD_GET(reg) BSP_FLD32GET(reg,4, 6)
#define TMS570_EMIF_CE2CFG_R_HOLD_SET(reg,val) BSP_FLD32SET(reg, val,4, 6)

/* field: TA - Minimum Turn-Around time. */
#define TMS570_EMIF_CE2CFG_TA(val) BSP_FLD32(val,2, 3)
#define TMS570_EMIF_CE2CFG_TA_GET(reg) BSP_FLD32GET(reg,2, 3)
#define TMS570_EMIF_CE2CFG_TA_SET(reg,val) BSP_FLD32SET(reg, val,2, 3)

/* field: ASIZE - Asynchronous Data Bus Width. This field defines the width of the asynchronous device's data bus. */
#define TMS570_EMIF_CE2CFG_ASIZE(val) BSP_FLD32(val,0, 1)
#define TMS570_EMIF_CE2CFG_ASIZE_GET(reg) BSP_FLD32GET(reg,0, 1)
#define TMS570_EMIF_CE2CFG_ASIZE_SET(reg,val) BSP_FLD32SET(reg, val,0, 1)


/*---------------------TMS570_EMIFCE3CFG---------------------*/
/* field: SS - Select Strobe bit. */
#define TMS570_EMIF_CE3CFG_SS BSP_FLD32(31)

/* field: EW - Extend Wait bit. This bit defines whether extended wait cycles will be enabled. See Section 17.2.6. */
#define TMS570_EMIF_CE3CFG_EW BSP_FLD32(30)

/* field: W_SETUP - Write setup width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE3CFG_W_SETUP(val) BSP_FLD32(val,26, 29)
#define TMS570_EMIF_CE3CFG_W_SETUP_GET(reg) BSP_FLD32GET(reg,26, 29)
#define TMS570_EMIF_CE3CFG_W_SETUP_SET(reg,val) BSP_FLD32SET(reg, val,26, 29)

/* field: W_STROBE - Write strobe width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE3CFG_W_STROBE(val) BSP_FLD32(val,20, 25)
#define TMS570_EMIF_CE3CFG_W_STROBE_GET(reg) BSP_FLD32GET(reg,20, 25)
#define TMS570_EMIF_CE3CFG_W_STROBE_SET(reg,val) BSP_FLD32SET(reg, val,20, 25)

/* field: W_HOLD - Write hold width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE3CFG_W_HOLD(val) BSP_FLD32(val,17, 19)
#define TMS570_EMIF_CE3CFG_W_HOLD_GET(reg) BSP_FLD32GET(reg,17, 19)
#define TMS570_EMIF_CE3CFG_W_HOLD_SET(reg,val) BSP_FLD32SET(reg, val,17, 19)

/* field: R_SETUP - Read setup width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE3CFG_R_SETUP(val) BSP_FLD32(val,13, 16)
#define TMS570_EMIF_CE3CFG_R_SETUP_GET(reg) BSP_FLD32GET(reg,13, 16)
#define TMS570_EMIF_CE3CFG_R_SETUP_SET(reg,val) BSP_FLD32SET(reg, val,13, 16)

/* field: R_STROBE - Read strobe width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE3CFG_R_STROBE(val) BSP_FLD32(val,7, 12)
#define TMS570_EMIF_CE3CFG_R_STROBE_GET(reg) BSP_FLD32GET(reg,7, 12)
#define TMS570_EMIF_CE3CFG_R_STROBE_SET(reg,val) BSP_FLD32SET(reg, val,7, 12)

/* field: R_HOLD - Read hold width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE3CFG_R_HOLD(val) BSP_FLD32(val,4, 6)
#define TMS570_EMIF_CE3CFG_R_HOLD_GET(reg) BSP_FLD32GET(reg,4, 6)
#define TMS570_EMIF_CE3CFG_R_HOLD_SET(reg,val) BSP_FLD32SET(reg, val,4, 6)

/* field: TA - Minimum Turn-Around time. */
#define TMS570_EMIF_CE3CFG_TA(val) BSP_FLD32(val,2, 3)
#define TMS570_EMIF_CE3CFG_TA_GET(reg) BSP_FLD32GET(reg,2, 3)
#define TMS570_EMIF_CE3CFG_TA_SET(reg,val) BSP_FLD32SET(reg, val,2, 3)

/* field: ASIZE - Asynchronous Data Bus Width. This field defines the width of the asynchronous device's data bus. */
#define TMS570_EMIF_CE3CFG_ASIZE(val) BSP_FLD32(val,0, 1)
#define TMS570_EMIF_CE3CFG_ASIZE_GET(reg) BSP_FLD32GET(reg,0, 1)
#define TMS570_EMIF_CE3CFG_ASIZE_SET(reg,val) BSP_FLD32SET(reg, val,0, 1)


/*---------------------TMS570_EMIFCE4CFG---------------------*/
/* field: SS - Select Strobe bit. */
#define TMS570_EMIF_CE4CFG_SS BSP_FLD32(31)

/* field: EW - Extend Wait bit. This bit defines whether extended wait cycles will be enabled. See Section 17.2.6. */
#define TMS570_EMIF_CE4CFG_EW BSP_FLD32(30)

/* field: W_SETUP - Write setup width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE4CFG_W_SETUP(val) BSP_FLD32(val,26, 29)
#define TMS570_EMIF_CE4CFG_W_SETUP_GET(reg) BSP_FLD32GET(reg,26, 29)
#define TMS570_EMIF_CE4CFG_W_SETUP_SET(reg,val) BSP_FLD32SET(reg, val,26, 29)

/* field: W_STROBE - Write strobe width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE4CFG_W_STROBE(val) BSP_FLD32(val,20, 25)
#define TMS570_EMIF_CE4CFG_W_STROBE_GET(reg) BSP_FLD32GET(reg,20, 25)
#define TMS570_EMIF_CE4CFG_W_STROBE_SET(reg,val) BSP_FLD32SET(reg, val,20, 25)

/* field: W_HOLD - Write hold width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE4CFG_W_HOLD(val) BSP_FLD32(val,17, 19)
#define TMS570_EMIF_CE4CFG_W_HOLD_GET(reg) BSP_FLD32GET(reg,17, 19)
#define TMS570_EMIF_CE4CFG_W_HOLD_SET(reg,val) BSP_FLD32SET(reg, val,17, 19)

/* field: R_SETUP - Read setup width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE4CFG_R_SETUP(val) BSP_FLD32(val,13, 16)
#define TMS570_EMIF_CE4CFG_R_SETUP_GET(reg) BSP_FLD32GET(reg,13, 16)
#define TMS570_EMIF_CE4CFG_R_SETUP_SET(reg,val) BSP_FLD32SET(reg, val,13, 16)

/* field: R_STROBE - Read strobe width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE4CFG_R_STROBE(val) BSP_FLD32(val,7, 12)
#define TMS570_EMIF_CE4CFG_R_STROBE_GET(reg) BSP_FLD32GET(reg,7, 12)
#define TMS570_EMIF_CE4CFG_R_STROBE_SET(reg,val) BSP_FLD32SET(reg, val,7, 12)

/* field: R_HOLD - Read hold width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE4CFG_R_HOLD(val) BSP_FLD32(val,4, 6)
#define TMS570_EMIF_CE4CFG_R_HOLD_GET(reg) BSP_FLD32GET(reg,4, 6)
#define TMS570_EMIF_CE4CFG_R_HOLD_SET(reg,val) BSP_FLD32SET(reg, val,4, 6)

/* field: TA - Minimum Turn-Around time. */
#define TMS570_EMIF_CE4CFG_TA(val) BSP_FLD32(val,2, 3)
#define TMS570_EMIF_CE4CFG_TA_GET(reg) BSP_FLD32GET(reg,2, 3)
#define TMS570_EMIF_CE4CFG_TA_SET(reg,val) BSP_FLD32SET(reg, val,2, 3)

/* field: ASIZE - Asynchronous Data Bus Width. This field defines the width of the asynchronous device's data bus. */
#define TMS570_EMIF_CE4CFG_ASIZE(val) BSP_FLD32(val,0, 1)
#define TMS570_EMIF_CE4CFG_ASIZE_GET(reg) BSP_FLD32GET(reg,0, 1)
#define TMS570_EMIF_CE4CFG_ASIZE_SET(reg,val) BSP_FLD32SET(reg, val,0, 1)


/*---------------------TMS570_EMIFCE5CFG---------------------*/
/* field: SS - Select Strobe bit. */
#define TMS570_EMIF_CE5CFG_SS BSP_FLD32(31)

/* field: EW - Extend Wait bit. This bit defines whether extended wait cycles will be enabled. See Section 17.2.6. */
#define TMS570_EMIF_CE5CFG_EW BSP_FLD32(30)

/* field: W_SETUP - Write setup width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE5CFG_W_SETUP(val) BSP_FLD32(val,26, 29)
#define TMS570_EMIF_CE5CFG_W_SETUP_GET(reg) BSP_FLD32GET(reg,26, 29)
#define TMS570_EMIF_CE5CFG_W_SETUP_SET(reg,val) BSP_FLD32SET(reg, val,26, 29)

/* field: W_STROBE - Write strobe width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE5CFG_W_STROBE(val) BSP_FLD32(val,20, 25)
#define TMS570_EMIF_CE5CFG_W_STROBE_GET(reg) BSP_FLD32GET(reg,20, 25)
#define TMS570_EMIF_CE5CFG_W_STROBE_SET(reg,val) BSP_FLD32SET(reg, val,20, 25)

/* field: W_HOLD - Write hold width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE5CFG_W_HOLD(val) BSP_FLD32(val,17, 19)
#define TMS570_EMIF_CE5CFG_W_HOLD_GET(reg) BSP_FLD32GET(reg,17, 19)
#define TMS570_EMIF_CE5CFG_W_HOLD_SET(reg,val) BSP_FLD32SET(reg, val,17, 19)

/* field: R_SETUP - Read setup width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE5CFG_R_SETUP(val) BSP_FLD32(val,13, 16)
#define TMS570_EMIF_CE5CFG_R_SETUP_GET(reg) BSP_FLD32GET(reg,13, 16)
#define TMS570_EMIF_CE5CFG_R_SETUP_SET(reg,val) BSP_FLD32SET(reg, val,13, 16)

/* field: R_STROBE - Read strobe width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE5CFG_R_STROBE(val) BSP_FLD32(val,7, 12)
#define TMS570_EMIF_CE5CFG_R_STROBE_GET(reg) BSP_FLD32GET(reg,7, 12)
#define TMS570_EMIF_CE5CFG_R_STROBE_SET(reg,val) BSP_FLD32SET(reg, val,7, 12)

/* field: R_HOLD - Read hold width in EMIF_CLK cycles, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE5CFG_R_HOLD(val) BSP_FLD32(val,4, 6)
#define TMS570_EMIF_CE5CFG_R_HOLD_GET(reg) BSP_FLD32GET(reg,4, 6)
#define TMS570_EMIF_CE5CFG_R_HOLD_SET(reg,val) BSP_FLD32SET(reg, val,4, 6)

/* field: TA - and writes, minus one cycle. See Section 17.2.6.3 for details. */
#define TMS570_EMIF_CE5CFG_TA(val) BSP_FLD32(val,2, 3)
#define TMS570_EMIF_CE5CFG_TA_GET(reg) BSP_FLD32GET(reg,2, 3)
#define TMS570_EMIF_CE5CFG_TA_SET(reg,val) BSP_FLD32SET(reg, val,2, 3)

/* field: ASIZE - Asynchronous Data Bus Width. This field defines the width of the asynchronous device's data bus. */
#define TMS570_EMIF_CE5CFG_ASIZE(val) BSP_FLD32(val,0, 1)
#define TMS570_EMIF_CE5CFG_ASIZE_GET(reg) BSP_FLD32GET(reg,0, 1)
#define TMS570_EMIF_CE5CFG_ASIZE_SET(reg,val) BSP_FLD32SET(reg, val,0, 1)


/*---------------------TMS570_EMIFSDTIMR---------------------*/
/* field: T_RFC - Specifies the Trfc value of the SDRAM. */
#define TMS570_EMIF_SDTIMR_T_RFC(val) BSP_FLD32(val,27, 31)
#define TMS570_EMIF_SDTIMR_T_RFC_GET(reg) BSP_FLD32GET(reg,27, 31)
#define TMS570_EMIF_SDTIMR_T_RFC_SET(reg,val) BSP_FLD32SET(reg, val,27, 31)

/* field: T_RP - Precharge (PRE) to Activate (ACTV) or Refresh (REFR) command, minus 1: */
#define TMS570_EMIF_SDTIMR_T_RP(val) BSP_FLD32(val,24, 26)
#define TMS570_EMIF_SDTIMR_T_RP_GET(reg) BSP_FLD32GET(reg,24, 26)
#define TMS570_EMIF_SDTIMR_T_RP_SET(reg,val) BSP_FLD32SET(reg, val,24, 26)

/* field: T_RCD - Specifies the Trcd value of the SDRAM. */
#define TMS570_EMIF_SDTIMR_T_RCD(val) BSP_FLD32(val,20, 22)
#define TMS570_EMIF_SDTIMR_T_RCD_GET(reg) BSP_FLD32GET(reg,20, 22)
#define TMS570_EMIF_SDTIMR_T_RCD_SET(reg,val) BSP_FLD32SET(reg, val,20, 22)

/* field: T_WR - Specifies the Twr value of the SDRAM. */
#define TMS570_EMIF_SDTIMR_T_WR(val) BSP_FLD32(val,16, 18)
#define TMS570_EMIF_SDTIMR_T_WR_GET(reg) BSP_FLD32GET(reg,16, 18)
#define TMS570_EMIF_SDTIMR_T_WR_SET(reg,val) BSP_FLD32SET(reg, val,16, 18)

/* field: T_RAS - Specifies the Tras value of the SDRAM. */
#define TMS570_EMIF_SDTIMR_T_RAS(val) BSP_FLD32(val,12, 15)
#define TMS570_EMIF_SDTIMR_T_RAS_GET(reg) BSP_FLD32GET(reg,12, 15)
#define TMS570_EMIF_SDTIMR_T_RAS_SET(reg,val) BSP_FLD32SET(reg, val,12, 15)

/* field: T_RC - Specifies the Trc value of the SDRAM. */
#define TMS570_EMIF_SDTIMR_T_RC(val) BSP_FLD32(val,8, 11)
#define TMS570_EMIF_SDTIMR_T_RC_GET(reg) BSP_FLD32GET(reg,8, 11)
#define TMS570_EMIF_SDTIMR_T_RC_SET(reg,val) BSP_FLD32SET(reg, val,8, 11)

/* field: T_RRD - Specifies the Trrd value of the SDRAM. */
#define TMS570_EMIF_SDTIMR_T_RRD(val) BSP_FLD32(val,4, 6)
#define TMS570_EMIF_SDTIMR_T_RRD_GET(reg) BSP_FLD32GET(reg,4, 6)
#define TMS570_EMIF_SDTIMR_T_RRD_SET(reg,val) BSP_FLD32SET(reg, val,4, 6)


/*---------------------TMS570_EMIFSDSRETR---------------------*/
/* field: T_XS - This field specifies the minimum number of ECLKOUT cycles from Self-Refresh exit to any command, */
#define TMS570_EMIF_SDSRETR_T_XS(val) BSP_FLD32(val,0, 4)
#define TMS570_EMIF_SDSRETR_T_XS_GET(reg) BSP_FLD32GET(reg,0, 4)
#define TMS570_EMIF_SDSRETR_T_XS_SET(reg,val) BSP_FLD32SET(reg, val,0, 4)


/*---------------------TMS570_EMIFINTRAW---------------------*/
/* field: WR - Wait Rise. */
#define TMS570_EMIF_INTRAW_WR BSP_FLD32(2)

/* field: LT - Line Trap. Set to 1 by hardware to indicate illegal memory access type or invalid cache line size. */
#define TMS570_EMIF_INTRAW_LT BSP_FLD32(1)

/* field: AT - Asynchronous Timeout. */
#define TMS570_EMIF_INTRAW_AT BSP_FLD32(0)


/*---------------------TMS570_EMIFINTMSK---------------------*/
/* field: WR_MASKED - Wait Rise Masked. */
#define TMS570_EMIF_INTMSK_WR_MASKED BSP_FLD32(2)

/* field: LT_MASKED - Masked Line Trap. */
#define TMS570_EMIF_INTMSK_LT_MASKED BSP_FLD32(1)

/* field: AT_MASKED - Asynchronous Timeout Masked. */
#define TMS570_EMIF_INTMSK_AT_MASKED BSP_FLD32(0)


/*--------------------TMS570_EMIFINTMSKSET--------------------*/
/* field: WR_MASK_SET - Wait Rise Mask Set. This bit determines whether or not the wait rise Interrupt is enabled. */
#define TMS570_EMIF_INTMSKSET_WR_MASK_SET BSP_FLD32(2)

/* field: LT_MASK_SET - LT_MASK_SET Mask set for LT_MASKED bit in the EMIF interrupt mask register (INTMSK). */
#define TMS570_EMIF_INTMSKSET_LT_MASK_SET BSP_FLD32(1)

/* field: AT_MASK_SET - Asynchronous Timeout Mask Set. */
#define TMS570_EMIF_INTMSKSET_AT_MASK_SET BSP_FLD32(0)


/*--------------------TMS570_EMIFINTMSKCLR--------------------*/
/* field: WR_MASK_CLR - Wait Rise Mask Clear. This bit determines whether or not the wait rise interrupt is enabled. */
#define TMS570_EMIF_INTMSKCLR_WR_MASK_CLR BSP_FLD32(2)

/* field: LT_MASK_CLR - 1 to this bit clears this bit, clears the LT_MASK_SET bit in the EMIF interrupt mask set register */
#define TMS570_EMIF_INTMSKCLR_LT_MASK_CLR BSP_FLD32(1)

/* field: AT_MASK_CLR - Asynchronous Timeout Mask Clear. */
#define TMS570_EMIF_INTMSKCLR_AT_MASK_CLR BSP_FLD32(0)


/*----------------------TMS570_EMIFPMCR----------------------*/
/* field: CS5_PG_DEL - Page access delay for NOR Flash connected on CS5. CS5 is not available on this device. */
#define TMS570_EMIF_PMCR_CS5_PG_DEL(val) BSP_FLD32(val,26, 31)
#define TMS570_EMIF_PMCR_CS5_PG_DEL_GET(reg) BSP_FLD32GET(reg,26, 31)
#define TMS570_EMIF_PMCR_CS5_PG_DEL_SET(reg,val) BSP_FLD32SET(reg, val,26, 31)

/* field: CS5_PG_SIZE - Page Size for NOR Flash connected on CS5. CS5 is not available on this device. */
#define TMS570_EMIF_PMCR_CS5_PG_SIZE BSP_FLD32(25)

/* field: CS5_PG_MD_EN - Page Mode enable for NOR Flash connected on CS5. CS5 is not available on this device. */
#define TMS570_EMIF_PMCR_CS5_PG_MD_EN BSP_FLD32(24)

/* field: CS4_PG_DEL - Page access delay for NOR Flash connected on CS4. */
#define TMS570_EMIF_PMCR_CS4_PG_DEL(val) BSP_FLD32(val,18, 23)
#define TMS570_EMIF_PMCR_CS4_PG_DEL_GET(reg) BSP_FLD32GET(reg,18, 23)
#define TMS570_EMIF_PMCR_CS4_PG_DEL_SET(reg,val) BSP_FLD32SET(reg, val,18, 23)

/* field: CS4_PG_SIZE - Page Size for NOR Flash connected on CS4. */
#define TMS570_EMIF_PMCR_CS4_PG_SIZE BSP_FLD32(17)

/* field: CS4_PG_MD_EN - Page Mode enable for NOR Flash connected on CS4. */
#define TMS570_EMIF_PMCR_CS4_PG_MD_EN BSP_FLD32(16)

/* field: CS3_PG_DEL - the page read data to be valid, minus one cycle. This value must not be cleared to 0. */
#define TMS570_EMIF_PMCR_CS3_PG_DEL(val) BSP_FLD32(val,10, 15)
#define TMS570_EMIF_PMCR_CS3_PG_DEL_GET(reg) BSP_FLD32GET(reg,10, 15)
#define TMS570_EMIF_PMCR_CS3_PG_DEL_SET(reg,val) BSP_FLD32SET(reg, val,10, 15)

/* field: CS3_PG_SIZE - Page Size for NOR Flash connected on CS3. */
#define TMS570_EMIF_PMCR_CS3_PG_SIZE BSP_FLD32(9)

/* field: CS3_PG_MD_EN - Page Mode enable for NOR Flash connected on CS3. */
#define TMS570_EMIF_PMCR_CS3_PG_MD_EN BSP_FLD32(8)

/* field: CS2_PG_DEL - Page access delay for NOR Flash connected on CS2. */
#define TMS570_EMIF_PMCR_CS2_PG_DEL(val) BSP_FLD32(val,2, 7)
#define TMS570_EMIF_PMCR_CS2_PG_DEL_GET(reg) BSP_FLD32GET(reg,2, 7)
#define TMS570_EMIF_PMCR_CS2_PG_DEL_SET(reg,val) BSP_FLD32SET(reg, val,2, 7)

/* field: CS2_PG_SIZE - Page Size for NOR Flash connected on CS2. */
#define TMS570_EMIF_PMCR_CS2_PG_SIZE BSP_FLD32(1)

/* field: CS2_PG_MD_EN - Page Mode enable for NOR Flash connected on CS2. */
#define TMS570_EMIF_PMCR_CS2_PG_MD_EN BSP_FLD32(0)



#endif /* LIBBSP_ARM_tms570_EMIF */
