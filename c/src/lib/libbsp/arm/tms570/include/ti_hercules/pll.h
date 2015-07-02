/* The header file is generated by make_header.py from PLL.json */
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
#ifndef LIBBSP_ARM_tms570_PLL
#define LIBBSP_ARM_tms570_PLL

#include <bsp/utility.h>

typedef struct{
  uint32_t PLLCTL3;           /*PLL Control 3 Register*/
  uint8_t reserved1 [108];
  uint32_t CLKSLIP;           /*PLL Clock Slip Control Register*/
  uint8_t reserved2 [7600];
  uint32_t SSWPLL1;           /*PLL Modulation Depth Measurement Control Register*/
  uint32_t SSWPLL2;           /*SSW PLL BIST Control Register 2*/
  uint32_t SSWPLL3;           /*SSW PLL BIST Control Register 3*/
  uint32_t CSDIS;             /*Clock Source Disable Register*/
  uint32_t CSDISSET;          /*Clock Source Disable Set Register*/
  uint32_t CSDISCLR;          /*Clock Source Disable Clear Register*/
  uint8_t reserved3 [24];
  uint32_t CSVSTAT;           /*Clock Source Valid Status Register*/
  uint8_t reserved4 [24];
  uint32_t PLLCTL1;           /*PLL Control 1 Register*/
  uint32_t PLLCTL2;           /*PLL Control 2 Register*/
  uint8_t reserved5 [16];
  uint32_t LPOMONCTL;         /*LPO/Clock Monitor Control Register*/
  uint32_t CLKTEST;           /*Clock Test Register*/
  uint8_t reserved6 [16];
  uint32_t GPREG1;            /*General Purpose Register*/
  uint8_t reserved7 [72];
  uint32_t GLBSTAT;           /*Global Status Register*/
} tms570_pll_t;


/*---------------------TMS570_PLLPLLCTL3---------------------*/
/* field: ODPLL2 - Internal PLL Output Divider */
#define TMS570_PLL_PLLCTL3_ODPLL2(val) BSP_FLD32(val,29, 31)
#define TMS570_PLL_PLLCTL3_ODPLL2_GET(reg) BSP_FLD32GET(reg,29, 31)
#define TMS570_PLL_PLLCTL3_ODPLL2_SET(reg,val) BSP_FLD32SET(reg, val,29, 31)

/* field: PLLDIV2 - PLL2 Output Clock Divider */
#define TMS570_PLL_PLLCTL3_PLLDIV2(val) BSP_FLD32(val,24, 28)
#define TMS570_PLL_PLLCTL3_PLLDIV2_GET(reg) BSP_FLD32GET(reg,24, 28)
#define TMS570_PLL_PLLCTL3_PLLDIV2_SET(reg,val) BSP_FLD32SET(reg, val,24, 28)

/* field: REFCLKDIV2 - Reference Clock Divider */
#define TMS570_PLL_PLLCTL3_REFCLKDIV2(val) BSP_FLD32(val,16, 21)
#define TMS570_PLL_PLLCTL3_REFCLKDIV2_GET(reg) BSP_FLD32GET(reg,16, 21)
#define TMS570_PLL_PLLCTL3_REFCLKDIV2_SET(reg,val) BSP_FLD32SET(reg, val,16, 21)

/* field: PLLMUL2 - PLL2 Multiplication Factor */
#define TMS570_PLL_PLLCTL3_PLLMUL2(val) BSP_FLD32(val,0, 15)
#define TMS570_PLL_PLLCTL3_PLLMUL2_GET(reg) BSP_FLD32GET(reg,0, 15)
#define TMS570_PLL_PLLCTL3_PLLMUL2_SET(reg,val) BSP_FLD32SET(reg, val,0, 15)


/*---------------------TMS570_PLLCLKSLIP---------------------*/
/* field: PLL1_SLIP_FILTER_COUNT - Configure the count for the filtered PLL slip. Count is on 10M clock. */
#define TMS570_PLL_CLKSLIP_PLL1_SLIP_FILTER_COUNT(val) BSP_FLD32(val,8, 13)
#define TMS570_PLL_CLKSLIP_PLL1_SLIP_FILTER_COUNT_GET(reg) BSP_FLD32GET(reg,8, 13)
#define TMS570_PLL_CLKSLIP_PLL1_SLIP_FILTER_COUNT_SET(reg,val) BSP_FLD32SET(reg, val,8, 13)

/* field: PLL1_SLIP_FILTER_KEY - Enable the PLL filtering. */
#define TMS570_PLL_CLKSLIP_PLL1_SLIP_FILTER_KEY(val) BSP_FLD32(val,0, 3)
#define TMS570_PLL_CLKSLIP_PLL1_SLIP_FILTER_KEY_GET(reg) BSP_FLD32GET(reg,0, 3)
#define TMS570_PLL_CLKSLIP_PLL1_SLIP_FILTER_KEY_SET(reg,val) BSP_FLD32SET(reg, val,0, 3)


/*---------------------TMS570_PLLSSWPLL1---------------------*/
/* field: CAPTURE_WINDOW_INDEX - The capture counter present in the PLL wrapper will count the PLL clock edges when */
#define TMS570_PLL_SSWPLL1_CAPTURE_WINDOW_INDEX(val) BSP_FLD32(val,8, 15)
#define TMS570_PLL_SSWPLL1_CAPTURE_WINDOW_INDEX_GET(reg) BSP_FLD32GET(reg,8, 15)
#define TMS570_PLL_SSWPLL1_CAPTURE_WINDOW_INDEX_SET(reg,val) BSP_FLD32SET(reg, val,8, 15)

/* field: COUNTER_READ_READY - Counter read ready. */
#define TMS570_PLL_SSWPLL1_COUNTER_READ_READY BSP_FLD32(6)

/* field: COUNTER_RESET - Counter reset. */
#define TMS570_PLL_SSWPLL1_COUNTER_RESET BSP_FLD32(5)

/* field: COUNTER_EN - Counter enable. */
#define TMS570_PLL_SSWPLL1_COUNTER_EN BSP_FLD32(4)

/* field: TAP_COUNTER_DIS - The value in this register is used to program a particular bit in CLKOUT counter. */
#define TMS570_PLL_SSWPLL1_TAP_COUNTER_DIS(val) BSP_FLD32(val,1, 3)
#define TMS570_PLL_SSWPLL1_TAP_COUNTER_DIS_GET(reg) BSP_FLD32GET(reg,1, 3)
#define TMS570_PLL_SSWPLL1_TAP_COUNTER_DIS_SET(reg,val) BSP_FLD32SET(reg, val,1, 3)

/* field: EXT_COUNTER_EN - Modulation Depth Measurement mode */
#define TMS570_PLL_SSWPLL1_EXT_COUNTER_EN BSP_FLD32(0)


/*---------------------TMS570_PLLSSWPLL2---------------------*/
/* field: SSW_CAPTURE_COUNT - Capture count. This register returns the value of the capture count. */
#define TMS570_PLL_SSWPLL2_SSW_CAPTURE_COUNT(val) BSP_FLD32(val,0, 31)
#define TMS570_PLL_SSWPLL2_SSW_CAPTURE_COUNT_GET(reg) BSP_FLD32GET(reg,0, 31)
#define TMS570_PLL_SSWPLL2_SSW_CAPTURE_COUNT_SET(reg,val) BSP_FLD32SET(reg, val,0, 31)


/*---------------------TMS570_PLLSSWPLL3---------------------*/
/* field: SSW_CAPTURE_COUNT - Value of CLKout count register. */
#define TMS570_PLL_SSWPLL3_SSW_CAPTURE_COUNT(val) BSP_FLD32(val,0, 31)
#define TMS570_PLL_SSWPLL3_SSW_CAPTURE_COUNT_GET(reg) BSP_FLD32GET(reg,0, 31)
#define TMS570_PLL_SSWPLL3_SSW_CAPTURE_COUNT_SET(reg,val) BSP_FLD32SET(reg, val,0, 31)


/*----------------------TMS570_PLLCSDIS----------------------*/
/* field: CLKSR_7_3_OFF - Clock source[7-3] off. */
#define TMS570_PLL_CSDIS_CLKSR_7_3_OFF(val) BSP_FLD32(val,3, 7)
#define TMS570_PLL_CSDIS_CLKSR_7_3_OFF_GET(reg) BSP_FLD32GET(reg,3, 7)
#define TMS570_PLL_CSDIS_CLKSR_7_3_OFF_SET(reg,val) BSP_FLD32SET(reg, val,3, 7)

/* field: CLKSR_1_0_OFF - Clock source[1-0] off. */
#define TMS570_PLL_CSDIS_CLKSR_1_0_OFF(val) BSP_FLD32(val,0, 1)
#define TMS570_PLL_CSDIS_CLKSR_1_0_OFF_GET(reg) BSP_FLD32GET(reg,0, 1)
#define TMS570_PLL_CSDIS_CLKSR_1_0_OFF_SET(reg,val) BSP_FLD32SET(reg, val,0, 1)


/*---------------------TMS570_PLLCSDISSET---------------------*/
/* field: SETCLKSR_7_3_OFF - Set clock source[7-3] to the disabled state. */
#define TMS570_PLL_CSDISSET_SETCLKSR_7_3_OFF(val) BSP_FLD32(val,3, 7)
#define TMS570_PLL_CSDISSET_SETCLKSR_7_3_OFF_GET(reg) BSP_FLD32GET(reg,3, 7)
#define TMS570_PLL_CSDISSET_SETCLKSR_7_3_OFF_SET(reg,val) BSP_FLD32SET(reg, val,3, 7)

/* field: SETCLKSR_1_0_OFF - Set clock source[1-0] to the disabled state. */
#define TMS570_PLL_CSDISSET_SETCLKSR_1_0_OFF(val) BSP_FLD32(val,0, 1)
#define TMS570_PLL_CSDISSET_SETCLKSR_1_0_OFF_GET(reg) BSP_FLD32GET(reg,0, 1)
#define TMS570_PLL_CSDISSET_SETCLKSR_1_0_OFF_SET(reg,val) BSP_FLD32SET(reg, val,0, 1)


/*---------------------TMS570_PLLCSDISCLR---------------------*/
/* field: CLRCLKSR_7_3_OFF - Enables clock source[7-3]. */
#define TMS570_PLL_CSDISCLR_CLRCLKSR_7_3_OFF(val) BSP_FLD32(val,3, 7)
#define TMS570_PLL_CSDISCLR_CLRCLKSR_7_3_OFF_GET(reg) BSP_FLD32GET(reg,3, 7)
#define TMS570_PLL_CSDISCLR_CLRCLKSR_7_3_OFF_SET(reg,val) BSP_FLD32SET(reg, val,3, 7)

/* field: CLRCLKSR_1_0_OFF - Enables clock source[1-0]. */
#define TMS570_PLL_CSDISCLR_CLRCLKSR_1_0_OFF(val) BSP_FLD32(val,0, 1)
#define TMS570_PLL_CSDISCLR_CLRCLKSR_1_0_OFF_GET(reg) BSP_FLD32GET(reg,0, 1)
#define TMS570_PLL_CSDISCLR_CLRCLKSR_1_0_OFF_SET(reg,val) BSP_FLD32SET(reg, val,0, 1)


/*---------------------TMS570_PLLCSVSTAT---------------------*/
/* field: CLKSR_7_3V - Clock source[7-0] valid. */
#define TMS570_PLL_CSVSTAT_CLKSR_7_3V(val) BSP_FLD32(val,3, 7)
#define TMS570_PLL_CSVSTAT_CLKSR_7_3V_GET(reg) BSP_FLD32GET(reg,3, 7)
#define TMS570_PLL_CSVSTAT_CLKSR_7_3V_SET(reg,val) BSP_FLD32SET(reg, val,3, 7)

/* field: CLKSR_1_0V - Clock source[1-0] valid. */
#define TMS570_PLL_CSVSTAT_CLKSR_1_0V(val) BSP_FLD32(val,0, 1)
#define TMS570_PLL_CSVSTAT_CLKSR_1_0V_GET(reg) BSP_FLD32GET(reg,0, 1)
#define TMS570_PLL_CSVSTAT_CLKSR_1_0V_SET(reg,val) BSP_FLD32SET(reg, val,0, 1)


/*---------------------TMS570_PLLPLLCTL1---------------------*/
/* field: ROS - Reset on PLL Slip */
#define TMS570_PLL_PLLCTL1_ROS BSP_FLD32(31)

/* field: MASK_SLIP - Mask detection of PLL slip */
#define TMS570_PLL_PLLCTL1_MASK_SLIP(val) BSP_FLD32(val,29, 30)
#define TMS570_PLL_PLLCTL1_MASK_SLIP_GET(reg) BSP_FLD32GET(reg,29, 30)
#define TMS570_PLL_PLLCTL1_MASK_SLIP_SET(reg,val) BSP_FLD32SET(reg, val,29, 30)

/* field: PLLDIV - PLL Output Clock Divider */
#define TMS570_PLL_PLLCTL1_PLLDIV(val) BSP_FLD32(val,24, 28)
#define TMS570_PLL_PLLCTL1_PLLDIV_GET(reg) BSP_FLD32GET(reg,24, 28)
#define TMS570_PLL_PLLCTL1_PLLDIV_SET(reg,val) BSP_FLD32SET(reg, val,24, 28)

/* field: ROF - Reset on Oscillator Fail */
#define TMS570_PLL_PLLCTL1_ROF BSP_FLD32(23)

/* field: REFCLKDIV - Reference Clock Divider */
#define TMS570_PLL_PLLCTL1_REFCLKDIV(val) BSP_FLD32(val,16, 21)
#define TMS570_PLL_PLLCTL1_REFCLKDIV_GET(reg) BSP_FLD32GET(reg,16, 21)
#define TMS570_PLL_PLLCTL1_REFCLKDIV_SET(reg,val) BSP_FLD32SET(reg, val,16, 21)

/* field: PLLMUL - PLL Multiplication Factor */
#define TMS570_PLL_PLLCTL1_PLLMUL(val) BSP_FLD32(val,0, 15)
#define TMS570_PLL_PLLCTL1_PLLMUL_GET(reg) BSP_FLD32GET(reg,0, 15)
#define TMS570_PLL_PLLCTL1_PLLMUL_SET(reg,val) BSP_FLD32SET(reg, val,0, 15)


/*---------------------TMS570_PLLPLLCTL2---------------------*/
/* field: FMENA - Frequency Modulation Enable. */
#define TMS570_PLL_PLLCTL2_FMENA BSP_FLD32(31)

/* field: SPREADINGRATE - NS = SPREADINGRATE + 1 */
#define TMS570_PLL_PLLCTL2_SPREADINGRATE(val) BSP_FLD32(val,22, 30)
#define TMS570_PLL_PLLCTL2_SPREADINGRATE_GET(reg) BSP_FLD32GET(reg,22, 30)
#define TMS570_PLL_PLLCTL2_SPREADINGRATE_SET(reg,val) BSP_FLD32SET(reg, val,22, 30)

/* field: MULMOD - Multiplier Correction when Frequency Modulation is enabled. */
#define TMS570_PLL_PLLCTL2_MULMOD(val) BSP_FLD32(val,12, 20)
#define TMS570_PLL_PLLCTL2_MULMOD_GET(reg) BSP_FLD32GET(reg,12, 20)
#define TMS570_PLL_PLLCTL2_MULMOD_SET(reg,val) BSP_FLD32SET(reg, val,12, 20)

/* field: ODPLL - Internal PLL Output Divider. */
#define TMS570_PLL_PLLCTL2_ODPLL(val) BSP_FLD32(val,9, 11)
#define TMS570_PLL_PLLCTL2_ODPLL_GET(reg) BSP_FLD32GET(reg,9, 11)
#define TMS570_PLL_PLLCTL2_ODPLL_SET(reg,val) BSP_FLD32SET(reg, val,9, 11)

/* field: SPR_AMOUNT - Spreading Amount. */
#define TMS570_PLL_PLLCTL2_SPR_AMOUNT(val) BSP_FLD32(val,0, 8)
#define TMS570_PLL_PLLCTL2_SPR_AMOUNT_GET(reg) BSP_FLD32GET(reg,0, 8)
#define TMS570_PLL_PLLCTL2_SPR_AMOUNT_SET(reg,val) BSP_FLD32SET(reg, val,0, 8)


/*--------------------TMS570_PLLLPOMONCTL--------------------*/
/* field: BIAS_ENABLE - Bias enable. */
#define TMS570_PLL_LPOMONCTL_BIAS_ENABLE BSP_FLD32(24)

/* field: OSCFRQCONFIGCNT - Configures the counter based on OSC frequency. */
#define TMS570_PLL_LPOMONCTL_OSCFRQCONFIGCNT BSP_FLD32(16)

/* field: HFTRIM - High frequency oscillator trim value. */
#define TMS570_PLL_LPOMONCTL_HFTRIM(val) BSP_FLD32(val,8, 12)
#define TMS570_PLL_LPOMONCTL_HFTRIM_GET(reg) BSP_FLD32GET(reg,8, 12)
#define TMS570_PLL_LPOMONCTL_HFTRIM_SET(reg,val) BSP_FLD32SET(reg, val,8, 12)


/*---------------------TMS570_PLLCLKTEST---------------------*/
/* field: ALTLIMPCLOCKENABLE - This bit selects a clock driven by the GIOB[0] pin as an alternate limp clock to the clock */
#define TMS570_PLL_CLKTEST_ALTLIMPCLOCKENABLE BSP_FLD32(26)

/* field: RANGEDETCTRL - Range detection control. */
#define TMS570_PLL_CLKTEST_RANGEDETCTRL BSP_FLD32(25)

/* field: RANGEDETENASSEL - Selects range detection enable. This bit resets asynchronously on power on reset. */
#define TMS570_PLL_CLKTEST_RANGEDETENASSEL BSP_FLD32(24)

/* field: CLK_TEST_EN - Clock test enable. This bit enables the clock going to the ECLK pin. */
#define TMS570_PLL_CLKTEST_CLK_TEST_EN(val) BSP_FLD32(val,16, 19)
#define TMS570_PLL_CLKTEST_CLK_TEST_EN_GET(reg) BSP_FLD32GET(reg,16, 19)
#define TMS570_PLL_CLKTEST_CLK_TEST_EN_SET(reg,val) BSP_FLD32SET(reg, val,16, 19)


/*----------------------TMS570_PLLGPREG1----------------------*/
/* field: EMIF_FUNC - Enable EMIF functions to be output. */
#define TMS570_PLL_GPREG1_EMIF_FUNC BSP_FLD32(31)

/* field: PLL1_FBSLIP_FILTER__COUNT - FBSLIP down counter programmed value. */
#define TMS570_PLL_GPREG1_PLL1_FBSLIP_FILTER__COUNT(val) BSP_FLD32(val,20, 25)
#define TMS570_PLL_GPREG1_PLL1_FBSLIP_FILTER__COUNT_GET(reg) BSP_FLD32GET(reg,20, 25)
#define TMS570_PLL_GPREG1_PLL1_FBSLIP_FILTER__COUNT_SET(reg,val) BSP_FLD32SET(reg, val,20, 25)

/* field: PLL1_RFSLIP_FILTER__KEY - Configures the system response when a FBSLIP is indicated by the */
#define TMS570_PLL_GPREG1_PLL1_RFSLIP_FILTER__KEY(val) BSP_FLD32(val,16, 19)
#define TMS570_PLL_GPREG1_PLL1_RFSLIP_FILTER__KEY_GET(reg) BSP_FLD32GET(reg,16, 19)
#define TMS570_PLL_GPREG1_PLL1_RFSLIP_FILTER__KEY_SET(reg,val) BSP_FLD32SET(reg, val,16, 19)

/* field: OUTPUT_BUFFER_LOW_EMI_MODE - Control field for the low-EMI mode of output buffers for */
#define TMS570_PLL_GPREG1_OUTPUT_BUFFER_LOW_EMI_MODE(val) BSP_FLD32(val,0, 15)
#define TMS570_PLL_GPREG1_OUTPUT_BUFFER_LOW_EMI_MODE_GET(reg) BSP_FLD32GET(reg,0, 15)
#define TMS570_PLL_GPREG1_OUTPUT_BUFFER_LOW_EMI_MODE_SET(reg,val) BSP_FLD32SET(reg, val,0, 15)


/*---------------------TMS570_PLLGLBSTAT---------------------*/
/* field: FBSLIP - PLL over cycle slip detection. */
#define TMS570_PLL_GLBSTAT_FBSLIP BSP_FLD32(9)

/* field: RFSLIP - PLL under cycle slip detection. */
#define TMS570_PLL_GLBSTAT_RFSLIP BSP_FLD32(8)

/* field: OSCFAIL - Oscillator fail flag bit. */
#define TMS570_PLL_GLBSTAT_OSCFAIL BSP_FLD32(0)



#endif /* LIBBSP_ARM_tms570_PLL */
