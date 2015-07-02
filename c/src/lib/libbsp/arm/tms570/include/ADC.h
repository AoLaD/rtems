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

#ifndef LIBBSP_ARM_tms570_ADC
#define LIBBSP_ARM_tms570_ADC

#include <bsp/utility.h>

typedef struct{
  uint32_t BUF0;              /*Group 0-2 result buffer 0 register*/
  uint32_t BUF1;              /*Group 0-2 result buffer 1 register*/
  uint32_t BUF2;              /*Group 0-2 result buffer 2 register*/
  uint32_t BUF3;              /*Group 0-2 result buffer 3 register*/
  uint32_t BUF4;              /*Group 0-2 result buffer 4 register*/
  uint32_t BUF5;              /*Group 0-2 result buffer 5 register*/
  uint32_t BUF6;              /*Group 0-2 result buffer 6 register*/
  uint32_t BUF7;              /*Group 0-2 result buffer 7 register*/
} tms570_gxbuf_t;

typedef struct{
  uint32_t RSTCR;             /*ADC Reset Control Register*/
  uint32_t OPMODECR;          /*ADC Operating Mode Control Register*/
  uint32_t CLOCKCR;           /*ADC Clock Control Register*/
  uint32_t CALCR;             /*ADC Calibration Mode Control Register*/
  uint32_t GxMODECR[3];       /*ADC Event Group Operating Mode Control Register*/
  uint32_t EVSRC;             /*ADC Trigger Source Select Register*/
  uint32_t G1SRC;             /*ADC Group1 Trigger Source Select Register*/
  uint32_t G2SRC;             /*ADC Group2 Trigger Source Select Register*/
  uint32_t GxINTENA[3];       /*ADC Event Interrupt Enable Control Register*/
  uint32_t GxINTFLG[3];       /*ADC Event Group Interrupt Flag Register*/
  uint32_t GxINTCR[3];        /*ADC Event Group Threshold Interrupt Control Register*/
  uint32_t EVDMACR;           /*ADC Event Group DMA Control Register*/
  uint32_t G1DMACR;           /*ADC Group1 DMA Control Register*/
  uint32_t G2DMACR;           /*ADC Group2 DMA Control Register*/
  uint32_t BNDCR;             /*ADC Results Memory Configuration Register*/
  uint32_t BNDEND;            /*ADC Results Memory Size Configuration Register*/
  uint32_t EVSAMP;            /*ADC Event Group Sampling Time Configuration Register*/
  uint32_t G1SAMP;            /*ADC Group1 Sampling Time Configuration Register()*/
  uint32_t G2SAMP;            /*ADC Group2 Sampling Time Configuration Register*/
  uint32_t EVSR;              /*ADC Event Group Status Register*/
  uint32_t G1SR;              /*ADC Group1 Status Register*/
  uint32_t G2SR;              /*ADC Group2 Status Register*/
  uint32_t GxSEL[3];          /*ADC Event Group Channel Select Register*/
  uint32_t CALR;              /*ADC Calibration and Error Offset Correction Register*/
  uint32_t SMSTATE;           /*ADC State Machine Status Register*/
  uint32_t LASTCONV;          /*ADC Channel Last Conversion Value Register*/
  tms570_pom_region_t GxBUF[3];/*ADC Event Group Results Emulation FIFO Register*/
  uint8_t reserved1 [84];
  uint32_t EVEMUBUFFER;       /*ADC Event Group Results Emulation FIFO Register*/
  uint32_t G1EMUBUFFER;       /*ADC Group1 Results Emulation FIFO Register*/
  uint32_t G2EMUBUFFER;       /*ADC Group2 Results Emulation FIFO Register*/
  uint32_t EVTDIR;            /*ADC ADEVT Pin Direction Control Register*/
  uint32_t EVTOUT;            /*ADC ADEVT Pin Output Value Control Register*/
  uint32_t EVTIN;             /*ADC ADEVT Pin Input Value Register*/
  uint32_t EVTSET;            /*ADC ADEVT Pin Set Register*/
  uint32_t EVTCLR;            /*ADC ADEVT Pin Clear Register*/
  uint32_t EVTPDR;            /*ADC ADEVT Pin Open Drain Enable Register*/
  uint32_t EVTPDIS;           /*ADC ADEVT Pin Pull Control Disable Register*/
  uint32_t EVTPSEL;           /*ADC ADEVT Pin Pull Control Select Register*/
  uint32_t EVSAMPDISEN;       /*ADC Event Group Sample Cap Discharge Control Register*/
  uint32_t G1SAMPDISEN;       /*ADC Group1 Sample Cap Discharge Control Register*/
  uint32_t G2SAMPDISEN;       /*ADC Group2 Sample Cap Discharge Control Register*/
  uint32_t MAGINTCR1;         /*ADC Magnitude Compare Interrupt Control Register 2*/
  uint32_t MAGINT1MASK;       /*ADC Magnitude Compare Mask Register 0*/
  uint32_t MAGINTCR2;         /*ADC Magnitude Compare Interrupt Control Register 2*/
  uint32_t MAGINT2MASK;       /*ADC Magnitude Compare Mask Register 0*/
  uint32_t MAGINTCR3;         /*ADC Magnitude Compare Interrupt Control Register 2*/
  uint32_t MAGINT3MASK;       /*ADC Magnitude Compare Mask Register 0*/
  uint8_t reserved2 [24];
  uint32_t MAGTHRINTENASET;   /*ADC Magnitude Compare Interrupt Enable Set Register*/
  uint32_t MAGTHRINTENACLR;   /*ADC Magnitude Compare Interrupt Enable Clear Register*/
  uint32_t MAGTHRINTFLG;      /*ADC Magnitude Compare Interrupt Flag Register*/
  uint32_t MAGTHRINTOFFSET;   /*ADC Magnitude Compare Interrupt Offset Register*/
  uint32_t GxFIFORESETCR[3];  /*ADC Event Group FIFO Reset Control Register*/
  uint32_t EVRAMWRADDR;       /*ADC Event Group RAM Write Address Register*/
  uint32_t G1RAMWRADDR;       /*ADC Group1 RAM Write Address Register*/
  uint32_t G2RAMWRADDR;       /*ADC Group2 RAM Write Address Register*/
  uint32_t PARCR;             /*ADC Parity Control Register*/
  uint32_t PARADDR;           /*ADC Parity Error Address Register*/
  uint32_t PWRUPDLYCTRL;      /*ADC Power-Up Delay Control Register*/
} tms570_adc_t;


/*-----------------------TMS570_ADCBUF0-----------------------*/
/* field: G2_EMPTY_10bit_mode - Group2 FIFO Empty. */
#define TMS570_ADC_BUF0_G2_EMPTY_10bit_mode BSP_FLD32(15)

/* field: G2_CHID_10bit_mode - Group2 Channel Id. */
#define TMS570_ADC_BUF0_G2_CHID_10bit_mode(val) BSP_FLD32(val,10, 14)
#define TMS570_ADC_BUF0_G2_CHID_10bit_mode_GET(reg) BSP_FLD32GET(reg,10, 14)
#define TMS570_ADC_BUF0_G2_CHID_10bit_mode_SET(reg,val) BSP_FLD32SET(reg, val,10, 14)

/* field: G2_DR_10bit_mode - Group2 Digital Conversion Result. */
#define TMS570_ADC_BUF0_G2_DR_10bit_mode(val) BSP_FLD32(val,0, 9)
#define TMS570_ADC_BUF0_G2_DR_10bit_mode_GET(reg) BSP_FLD32GET(reg,0, 9)
#define TMS570_ADC_BUF0_G2_DR_10bit_mode_SET(reg,val) BSP_FLD32SET(reg, val,0, 9)

/* field: G2_EMPTY_12bit_mode - Group2 FIFO Empty. */
#define TMS570_ADC_BUF0_G2_EMPTY_12bit_mode BSP_FLD32(31)

/* field: G2_CHID_12bit_mode - Group2 Channel Id. */
#define TMS570_ADC_BUF0_G2_CHID_12bit_mode(val) BSP_FLD32(val,16, 20)
#define TMS570_ADC_BUF0_G2_CHID_12bit_mode_GET(reg) BSP_FLD32GET(reg,16, 20)
#define TMS570_ADC_BUF0_G2_CHID_12bit_mode_SET(reg,val) BSP_FLD32SET(reg, val,16, 20)

/* field: G2_DR_12bit_mode - Group2 Digital Conversion Result. */
#define TMS570_ADC_BUF0_G2_DR_12bit_mode(val) BSP_FLD32(val,0, 11)
#define TMS570_ADC_BUF0_G2_DR_12bit_mode_GET(reg) BSP_FLD32GET(reg,0, 11)
#define TMS570_ADC_BUF0_G2_DR_12bit_mode_SET(reg,val) BSP_FLD32SET(reg, val,0, 11)



#endif /* LIBBSP_ARM_tms570_ADC */
