/* The header file is generated by make_header.py from TCR.json */
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
#ifndef LIBBSP_ARM_tms570_TCR
#define LIBBSP_ARM_tms570_TCR

#include <bsp/utility.h>

typedef struct{
  uint32_t TCR[128];          /*Transfer Configuration RAM*/
  uint32_t TCR_Parity[128];   /*TCR Parity Test Mode*/
} tms570_tcr_t;


/*-----------------------TMS570_TCRTCR-----------------------*/
/* field: STXR - Set Transmit Request. */
#define TMS570_TCR_TCR_STXR BSP_FLD32(18)

/* field: THTSM - Transfer Header to System Memory. */
#define TMS570_TCR_TCR_THTSM BSP_FLD32(17)

/* field: TPTSM - Transfer Payload to System Memory. */
#define TMS570_TCR_TCR_TPTSM BSP_FLD32(16)

/* field: THTCC - Transfer Header to Communication Controller. */
#define TMS570_TCR_TCR_THTCC BSP_FLD32(15)

/* field: TPTCC - Transfer Payload to Communication Controller. */
#define TMS570_TCR_TCR_TPTCC BSP_FLD32(14)

/* field: TSO - Transfer Start Offset. */
#define TMS570_TCR_TCR_TSO(val) BSP_FLD32(val,0, 13)
#define TMS570_TCR_TCR_TSO_GET(reg) BSP_FLD32GET(reg,0, 13)
#define TMS570_TCR_TCR_TSO_SET(reg,val) BSP_FLD32SET(reg, val,0, 13)


/*--------------------TMS570_TCRTCR_Parity--------------------*/
/* field: PAB2 - Parity Bit for TCRx Byte 2. Parity information for byte 2 of TCRx(18-16). */
#define TMS570_TCR_TCR_Parity_PAB2 BSP_FLD32(16)

/* field: PAB1 - Parity Bit for TCRx Byte 1. Parity information for byte 1 of TCRx(15:8). */
#define TMS570_TCR_TCR_Parity_PAB1 BSP_FLD32(8)

/* field: PAB0 - Parity Bit for Byte 0. */
#define TMS570_TCR_TCR_Parity_PAB0 BSP_FLD32(0)



#endif /* LIBBSP_ARM_tms570_TCR */
