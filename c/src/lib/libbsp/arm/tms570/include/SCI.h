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

#ifndef LIBBSP_ARM_tms570_SCI
#define LIBBSP_ARM_tms570_SCI

#include <bsp/utility.h>

typedef struct{
  uint32_t SCIGCR0;           /*SCI Global Control Register 0*/
  uint32_t SCIGCR1;           /*SCI Global Control Register 1*/
  uint32_t SCIGCR2;           /*SCI Global Control Register 2*/
  uint32_t SCISETINT;         /*SCI Set Interrupt Register*/
  uint32_t SCICLEARINT;       /*SCI Clear Interrupt Register*/
  uint32_t SCISETINTLVL;      /*SCI Set Interrupt Level Register*/
  uint32_t SCICLEARINTLVL;    /*SCI Clear Interrupt Level Register*/
  uint32_t SCIFLR;            /*SCI Flags Register*/
  uint32_t SCIINTVECT0;       /*SCI Interrupt Vector Offset 0*/
  uint32_t SCIINTVECT1;       /*SCI Interrupt Vector Offset 1*/
  uint32_t SCIFORMAT;         /*SCI Format Control Register*/
  uint32_t BRS;               /*Baud Rate Selection Register*/
  uint32_t SCIED;             /*Receiver Emulation Data Buffer*/
  uint32_t SCIRD;             /*Receiver Data Buffer*/
  uint32_t SCITD;             /*Transmit Data Buffer*/
  uint32_t SCIPIO0;           /*SCI Pin I/O Control Register 0*/
  uint32_t SCIPIO1;           /*SCI Pin I/O Control Register 1*/
  uint32_t SCIPIO2;           /*SCI Pin I/O Control Register 2*/
  uint32_t SCIPIO3;           /*SCI Pin I/O Control Register 3*/
  uint32_t SCIPIO4;           /*SCI Pin I/O Control Register 4*/
  uint32_t SCIPIO5;           /*SCI Pin I/O Control Register 5*/
  uint32_t SCIPIO6;           /*SCI Pin I/O Control Register 6*/
  uint32_t SCIPIO7;           /*SCI Pin I/O Control Register 7*/
  uint32_t SCIPIO8;           /*SCI Pin I/O Control Register 8*/
  uint8_t reserved1 [48];
  uint32_t IODFTCTRL;         /*Input/Output Error Enable Register*/
} tms570_sci_t;


/*---------------------TMS570_SCISCIGCR0---------------------*/
/* field: Reserved - Read returns 0. Writes have no effect. */
#define TMS570_SCI_SCIGCR0_Reserved(val) BSP_FLD32(val,1, 31)
#define TMS570_SCI_SCIGCR0_Reserved_GET(reg) BSP_FLD32GET(reg,1, 31)
#define TMS570_SCI_SCIGCR0_Reserved_SET(reg,val) BSP_FLD32SET(reg, val,1, 31)

/* field: RESET - This bit resets the SCI module. */
#define TMS570_SCI_SCIGCR0_RESET BSP_FLD32(0)


/*---------------------TMS570_SCISCIGCR1---------------------*/
/* field: TXENA - Transmit enable. */
#define TMS570_SCI_SCIGCR1_TXENA BSP_FLD32(25)

/* field: RXENA - Receive enable. RXENA allows or prevents the transfer of data from SCIRXSHF to SCIRD. */
#define TMS570_SCI_SCIGCR1_RXENA BSP_FLD32(24)

/* field: CONT - Continue on suspend. */
#define TMS570_SCI_SCIGCR1_CONT BSP_FLD32(17)

/* field: LOOP_BACK - Loopback bit. The self-checking option for the SCI can be selected with this bit. */
#define TMS570_SCI_SCIGCR1_LOOP_BACK BSP_FLD32(16)

/* field: POWERDOWN - If the POWERDOWN bit is set while the receiver is actively receiving data and the wake-up */
#define TMS570_SCI_SCIGCR1_POWERDOWN BSP_FLD32(9)

/* field: SLEEP - SCI sleep. In a multiprocessor configuration, this bit controls the receive sleep function. */
#define TMS570_SCI_SCIGCR1_SLEEP BSP_FLD32(8)

/* field: SWnRST - Software reset (active low). This bit is effective in LIN and SCI modes. */
#define TMS570_SCI_SCIGCR1_SWnRST BSP_FLD32(7)

/* field: CLOCK - CLOCK */
#define TMS570_SCI_SCIGCR1_CLOCK BSP_FLD32(5)

/* field: STOP - SCI number of stop bits per frame. */
#define TMS570_SCI_SCIGCR1_STOP BSP_FLD32(4)

/* field: PARITY - SCI parity odd/even selection. If the PARITY ENA bit is set, PARITY designates odd or even parity. */
#define TMS570_SCI_SCIGCR1_PARITY BSP_FLD32(3)

/* field: PARITY_ENA - Parity enable. This bit enables or disables the parity function. */
#define TMS570_SCI_SCIGCR1_PARITY_ENA BSP_FLD32(2)

/* field: TIMING_MODE - SCI timing mode bit. */
#define TMS570_SCI_SCIGCR1_TIMING_MODE BSP_FLD32(1)

/* field: COMM_MODE - SCI communication mode bit. */
#define TMS570_SCI_SCIGCR1_COMM_MODE BSP_FLD32(0)


/*---------------------TMS570_SCISCIGCR2---------------------*/
/* field: CC - Compare checksum. LIN mode only. */
#define TMS570_SCI_SCIGCR2_CC BSP_FLD32(17)

/* field: SC - Send checksum byte. This bit is effective in LIN mode only. */
#define TMS570_SCI_SCIGCR2_SC BSP_FLD32(16)

/* field: GEN_WU - Generate wakeup signal. This bit is effective in LIN mode only. */
#define TMS570_SCI_SCIGCR2_GEN_WU BSP_FLD32(8)

/* field: POWERDOWN - Power down. This bit is effective in LIN or SCI mode. */
#define TMS570_SCI_SCIGCR2_POWERDOWN BSP_FLD32(0)


/*--------------------TMS570_SCISCISETINT--------------------*/
/* field: SET_FE_INT -  */
#define TMS570_SCI_SCISETINT_SET_FE_INT BSP_FLD32(26)

/* field: SET_OE_INT - SET OE INT */
#define TMS570_SCI_SCISETINT_SET_OE_INT BSP_FLD32(25)

/* field: SET_PE_INT - Set parity interrupt. */
#define TMS570_SCI_SCISETINT_SET_PE_INT BSP_FLD32(24)

/* field: SET_RX_DMA_ALL - SET RX DMA ALL */
#define TMS570_SCI_SCISETINT_SET_RX_DMA_ALL BSP_FLD32(18)

/* field: SET_RX_DMA - SET RX DMA */
#define TMS570_SCI_SCISETINT_SET_RX_DMA BSP_FLD32(17)

/* field: SET_TX_DMA - Set transmit DMA. To enable DMA requests for the transmitter, this bit must be set. */
#define TMS570_SCI_SCISETINT_SET_TX_DMA BSP_FLD32(16)

/* field: SET_RX_INT - SET RX INT */
#define TMS570_SCI_SCISETINT_SET_RX_INT BSP_FLD32(9)

/* field: SET_TX_INT - Set transmitter interrupt. */
#define TMS570_SCI_SCISETINT_SET_TX_INT BSP_FLD32(8)

/* field: SET_WAKEUP_INT - Set wakeup interrupt. */
#define TMS570_SCI_SCISETINT_SET_WAKEUP_INT BSP_FLD32(1)

/* field: SET_BRKDT_INT - Set breakdetect interrupt. */
#define TMS570_SCI_SCISETINT_SET_BRKDT_INT BSP_FLD32(0)


/*-------------------TMS570_SCISCICLEARINT-------------------*/
/* field: CLR_FE_INT - Clear framing-error interrupt. This bit disables the framing-error interrupt when set. */
#define TMS570_SCI_SCICLEARINT_CLR_FE_INT BSP_FLD32(26)

/* field: CLR_CE_INT - Clear overrun-error interrupt. This bit disables the SCI overrun error interrupt when set. */
#define TMS570_SCI_SCICLEARINT_CLR_CE_INT BSP_FLD32(25)

/* field: CLR_PE_INT - Clear parity interrupt. This bit disables the parity error interrupt when set. */
#define TMS570_SCI_SCICLEARINT_CLR_PE_INT BSP_FLD32(24)

/* field: CLR_RX_DMA_ALL - Clear receive DMA all. This bit clears the receive DMA request for address frames when set. */
#define TMS570_SCI_SCICLEARINT_CLR_RX_DMA_ALL BSP_FLD32(18)

/* field: CLR_RX_DMA - Clear receive DMA request. This bit disables the receive DMA request when set. */
#define TMS570_SCI_SCICLEARINT_CLR_RX_DMA BSP_FLD32(17)

/* field: CLR_TX_DMA - CLR TX DMA */
#define TMS570_SCI_SCICLEARINT_CLR_TX_DMA BSP_FLD32(16)

/* field: CLR_RX_INT - Clear receiver interrupt. This bit disables the receiver interrupt when set. */
#define TMS570_SCI_SCICLEARINT_CLR_RX_INT BSP_FLD32(9)

/* field: CLR_TX_INT - Clear transmitter interrupt. This bit disables the transmitter interrupt when set. */
#define TMS570_SCI_SCICLEARINT_CLR_TX_INT BSP_FLD32(8)

/* field: CLR_WAKEUP_INT - Clear wakeup interrupt. This bit disables the wakeup interrupt when set. */
#define TMS570_SCI_SCICLEARINT_CLR_WAKEUP_INT BSP_FLD32(1)

/* field: CLR_BRKDT_INT - Clear breakdetect interrupt. This bit disables the break-detect interrupt when set. */
#define TMS570_SCI_SCICLEARINT_CLR_BRKDT_INT BSP_FLD32(0)


/*-------------------TMS570_SCISCISETINTLVL-------------------*/
/* field: SET_FE_INT_LVL - Set framing-error interrupt level. */
#define TMS570_SCI_SCISETINTLVL_SET_FE_INT_LVL BSP_FLD32(26)

/* field: SET_CE_INT_LVL - Set overrun-error interrupt level. */
#define TMS570_SCI_SCISETINTLVL_SET_CE_INT_LVL BSP_FLD32(25)

/* field: SET_PE_INT_LVL - Set parity error interrupt level. */
#define TMS570_SCI_SCISETINTLVL_SET_PE_INT_LVL BSP_FLD32(24)

/* field: SET_RX_DMA_ALL_LVL - Set receive DMA all interrupt levels. */
#define TMS570_SCI_SCISETINTLVL_SET_RX_DMA_ALL_LVL BSP_FLD32(18)

/* field: SET_RX_INT_LVL - Set receiver interrupt level. */
#define TMS570_SCI_SCISETINTLVL_SET_RX_INT_LVL BSP_FLD32(9)

/* field: SET_TX_INT_LVL - Set transmitter interrupt level. */
#define TMS570_SCI_SCISETINTLVL_SET_TX_INT_LVL BSP_FLD32(8)

/* field: SET_WAKEUP_INT_LVL - Set wakeup interrupt level. */
#define TMS570_SCI_SCISETINTLVL_SET_WAKEUP_INT_LVL BSP_FLD32(1)

/* field: SET_BRKDT_INT_LVL - SET BRKDT INT LVL */
#define TMS570_SCI_SCISETINTLVL_SET_BRKDT_INT_LVL BSP_FLD32(0)


/*------------------TMS570_SCISCICLEARINTLVL------------------*/
/* field: CLR_FE_INT_LVL - Clear framing-error interrupt. */
#define TMS570_SCI_SCICLEARINTLVL_CLR_FE_INT_LVL BSP_FLD32(26)

/* field: CLR_CE_INT_LVL - CLR CE INT LVL */
#define TMS570_SCI_SCICLEARINTLVL_CLR_CE_INT_LVL BSP_FLD32(25)

/* field: CLR_CE_INT_LVL - CLR CE INT LVL */
#define TMS570_SCI_SCICLEARINTLVL_CLR_CE_INT_LVL BSP_FLD32(25)

/* field: CLR_PE_INT_LVL -  */
#define TMS570_SCI_SCICLEARINTLVL_CLR_PE_INT_LVL BSP_FLD32(24)

/* field: CLR_RX_DMA_ALL_LVL - Clear receive DMA interrupt level. */
#define TMS570_SCI_SCICLEARINTLVL_CLR_RX_DMA_ALL_LVL BSP_FLD32(18)

/* field: CLR_RX_INT_LVL - Clear receiver interrupt. */
#define TMS570_SCI_SCICLEARINTLVL_CLR_RX_INT_LVL BSP_FLD32(9)

/* field: 8 - CLR TX INT LVL Clear transmitter interrupt. */
#define TMS570_SCI_SCICLEARINTLVL_8 BSP_FLD32(8)

/* field: CLR_WAKEUP_INT_LVL - Clear wakeup interrupt. */
#define TMS570_SCI_SCICLEARINTLVL_CLR_WAKEUP_INT_LVL BSP_FLD32(1)

/* field: CLR_BRKDT_INT_LVL - Clear breakdetect interrupt. */
#define TMS570_SCI_SCICLEARINTLVL_CLR_BRKDT_INT_LVL BSP_FLD32(0)


/*----------------------TMS570_SCISCIFLR----------------------*/
/* field: FE - Framing error flag. This bit is effective in LIN or SCI-compatible mode. */
#define TMS570_SCI_SCIFLR_FE BSP_FLD32(26)

/* field: OE - Overrun error flag. */
#define TMS570_SCI_SCIFLR_OE BSP_FLD32(25)

/* field: PE - Parity error flag. This bit is set when a parity error is detected in the received data. */
#define TMS570_SCI_SCIFLR_PE BSP_FLD32(24)

/* field: RXWAKE - Receiver wakeup detect flag. */
#define TMS570_SCI_SCIFLR_RXWAKE BSP_FLD32(12)

/* field: TX_EMPTY - Transmitter empty flag. */
#define TMS570_SCI_SCIFLR_TX_EMPTY BSP_FLD32(11)

/* field: TXWAKE - Transmitter wakeup method select. */
#define TMS570_SCI_SCIFLR_TXWAKE BSP_FLD32(10)

/* field: RXRDY - Receiver ready flag. */
#define TMS570_SCI_SCIFLR_RXRDY BSP_FLD32(9)

/* field: TXRDY - Transmitter buffer register ready flag. */
#define TMS570_SCI_SCIFLR_TXRDY BSP_FLD32(8)

/* field: BUSY - Bus busy flag. TThis bit indicates whether the receiver is in the process of receiving a frame. */
#define TMS570_SCI_SCIFLR_BUSY BSP_FLD32(3)

/* field: IDLE - SCI receiver in idle state. */
#define TMS570_SCI_SCIFLR_IDLE BSP_FLD32(2)

/* field: WAKEUP - Wakeup flag. */
#define TMS570_SCI_SCIFLR_WAKEUP BSP_FLD32(1)

/* field: BRKDT - SCI break-detect flag. This bit is set when the SCI detects a break condition on the LINRX pin. */
#define TMS570_SCI_SCIFLR_BRKDT BSP_FLD32(0)


/*-------------------TMS570_SCISCIINTVECT0-------------------*/
/* field: INVECT0 - Interrupt vector offset for INT0. This register indicates the offset for interrupt line INT0. */
#define TMS570_SCI_SCIINTVECT0_INVECT0(val) BSP_FLD32(val,0, 3)
#define TMS570_SCI_SCIINTVECT0_INVECT0_GET(reg) BSP_FLD32GET(reg,0, 3)
#define TMS570_SCI_SCIINTVECT0_INVECT0_SET(reg,val) BSP_FLD32SET(reg, val,0, 3)


/*-------------------TMS570_SCISCIINTVECT1-------------------*/
/* field: INVECT1 - Interrupt vector offset for INT1. This register indicates the offset for interrupt line INT1. */
#define TMS570_SCI_SCIINTVECT1_INVECT1(val) BSP_FLD32(val,0, 3)
#define TMS570_SCI_SCIINTVECT1_INVECT1_GET(reg) BSP_FLD32GET(reg,0, 3)
#define TMS570_SCI_SCIINTVECT1_INVECT1_SET(reg,val) BSP_FLD32SET(reg, val,0, 3)


/*--------------------TMS570_SCISCIFORMAT--------------------*/
/* field: CHAR - Character length control bits. These bits set the SCI character length from 1 to 8 bits. */
#define TMS570_SCI_SCIFORMAT_CHAR(val) BSP_FLD32(val,0, 2)
#define TMS570_SCI_SCIFORMAT_CHAR_GET(reg) BSP_FLD32GET(reg,0, 2)
#define TMS570_SCI_SCIFORMAT_CHAR_SET(reg,val) BSP_FLD32SET(reg, val,0, 2)


/*-----------------------TMS570_SCIBRS-----------------------*/
/* field: BAUD - SCI 24-bit baud selection. */
#define TMS570_SCI_BRS_BAUD(val) BSP_FLD32(val,0, 23)
#define TMS570_SCI_BRS_BAUD_GET(reg) BSP_FLD32GET(reg,0, 23)
#define TMS570_SCI_BRS_BAUD_SET(reg,val) BSP_FLD32SET(reg, val,0, 23)


/*----------------------TMS570_SCISCIED----------------------*/
/* field: ED - Emulator data. Reading SCIED[7:0] does not clear the RXRDY flag, unlike reading SCIRD. */
#define TMS570_SCI_SCIED_ED(val) BSP_FLD32(val,0, 7)
#define TMS570_SCI_SCIED_ED_GET(reg) BSP_FLD32GET(reg,0, 7)
#define TMS570_SCI_SCIED_ED_SET(reg,val) BSP_FLD32SET(reg, val,0, 7)


/*----------------------TMS570_SCISCIRD----------------------*/
/* field: RD - Receiver data. */
#define TMS570_SCI_SCIRD_RD(val) BSP_FLD32(val,0, 7)
#define TMS570_SCI_SCIRD_RD_GET(reg) BSP_FLD32GET(reg,0, 7)
#define TMS570_SCI_SCIRD_RD_SET(reg,val) BSP_FLD32SET(reg, val,0, 7)


/*----------------------TMS570_SCISCITD----------------------*/
/* field: TD - Transmit data. Data to be transmitted is written to the SCITD register. */
#define TMS570_SCI_SCITD_TD(val) BSP_FLD32(val,0, 7)
#define TMS570_SCI_SCITD_TD_GET(reg) BSP_FLD32GET(reg,0, 7)
#define TMS570_SCI_SCITD_TD_SET(reg,val) BSP_FLD32SET(reg, val,0, 7)


/*---------------------TMS570_SCISCIPIO0---------------------*/
/* field: TX_FUNC - Transfer function. This bit defines the function of pin SCITX. */
#define TMS570_SCI_SCIPIO0_TX_FUNC BSP_FLD32(2)

/* field: RX_FUNC - Receive function.This bit defines the function of pin SCIRX. */
#define TMS570_SCI_SCIPIO0_RX_FUNC BSP_FLD32(1)


/*---------------------TMS570_SCISCIPIO1---------------------*/
/* field: TX_DIR - Transmit pin direction. */
#define TMS570_SCI_SCIPIO1_TX_DIR BSP_FLD32(2)

/* field: RX_DIR - Receive pin direction. */
#define TMS570_SCI_SCIPIO1_RX_DIR BSP_FLD32(1)


/*---------------------TMS570_SCISCIPIO2---------------------*/
/* field: TX_IN - Transmit pin in. This bit contains the current value on the SCITX pin. */
#define TMS570_SCI_SCIPIO2_TX_IN BSP_FLD32(2)

/* field: RX_IN - Receive pin in. This bit contains the current value on the SCIRX pin. */
#define TMS570_SCI_SCIPIO2_RX_IN BSP_FLD32(1)


/*---------------------TMS570_SCISCIPIO3---------------------*/
/* field: TX_OUT - Transmit pin out. */
#define TMS570_SCI_SCIPIO3_TX_OUT BSP_FLD32(2)

/* field: RX_OUT - Receive pin out. */
#define TMS570_SCI_SCIPIO3_RX_OUT BSP_FLD32(1)


/*---------------------TMS570_SCISCIPIO4---------------------*/
/* field: TX_SET - Transmit pin set. */
#define TMS570_SCI_SCIPIO4_TX_SET BSP_FLD32(2)

/* field: RX_SET - Receive pin set. */
#define TMS570_SCI_SCIPIO4_RX_SET BSP_FLD32(1)


/*---------------------TMS570_SCISCIPIO5---------------------*/
/* field: TX_CLR - Transmit pin clear. */
#define TMS570_SCI_SCIPIO5_TX_CLR BSP_FLD32(2)

/* field: RX_CLR - Receive pin clear. */
#define TMS570_SCI_SCIPIO5_RX_CLR BSP_FLD32(1)


/*---------------------TMS570_SCISCIPIO6---------------------*/
/* field: TX_PDR - Transmit pin open drain enable. */
#define TMS570_SCI_SCIPIO6_TX_PDR BSP_FLD32(2)

/* field: RX_PDR - Receive pin open drain enable. */
#define TMS570_SCI_SCIPIO6_RX_PDR BSP_FLD32(1)


/*---------------------TMS570_SCISCIPIO7---------------------*/
/* field: TX_PD - Transmit pin pull control disable. This bit disables pull control capability on the input pin SCITX. */
#define TMS570_SCI_SCIPIO7_TX_PD BSP_FLD32(2)

/* field: RX_PD - Receive pin pull control disable. This bit disables pull control capability on the input pin SCIRX. */
#define TMS570_SCI_SCIPIO7_RX_PD BSP_FLD32(1)


/*---------------------TMS570_SCISCIPIO8---------------------*/
/* field: TX_PSL - TX pin pull select. This bit selects pull type in the input pin SCITX. */
#define TMS570_SCI_SCIPIO8_TX_PSL BSP_FLD32(2)

/* field: RX_PSL - RX pin pull select. This bit selects pull type in the input pin SCIRX. */
#define TMS570_SCI_SCIPIO8_RX_PSL BSP_FLD32(1)


/*--------------------TMS570_SCIIODFTCTRL--------------------*/
/* field: FEN - Frame error enable. This bit is used to create a frame error. */
#define TMS570_SCI_IODFTCTRL_FEN BSP_FLD32(26)

/* field: PEN - Parity error enable. This bit is used to create a parity error. */
#define TMS570_SCI_IODFTCTRL_PEN BSP_FLD32(25)

/* field: BRKD_TENA - Break detect error enable. This bit is used to create a BRKDT error. */
#define TMS570_SCI_IODFTCTRL_BRKD_TENA BSP_FLD32(24)

/* field: PIN_SAMPLE_MASK - Pin sample mask. */
#define TMS570_SCI_IODFTCTRL_PIN_SAMPLE_MASK(val) BSP_FLD32(val,19, 20)
#define TMS570_SCI_IODFTCTRL_PIN_SAMPLE_MASK_GET(reg) BSP_FLD32GET(reg,19, 20)
#define TMS570_SCI_IODFTCTRL_PIN_SAMPLE_MASK_SET(reg,val) BSP_FLD32SET(reg, val,19, 20)

/* field: TX_SHIFT - Transmit shift. */
#define TMS570_SCI_IODFTCTRL_TX_SHIFT(val) BSP_FLD32(val,16, 18)
#define TMS570_SCI_IODFTCTRL_TX_SHIFT_GET(reg) BSP_FLD32GET(reg,16, 18)
#define TMS570_SCI_IODFTCTRL_TX_SHIFT_SET(reg,val) BSP_FLD32SET(reg, val,16, 18)

/* field: IODFTENA - IODFT enable key. Write access permitted in Privilege mode only. */
#define TMS570_SCI_IODFTCTRL_IODFTENA(val) BSP_FLD32(val,8, 11)
#define TMS570_SCI_IODFTCTRL_IODFTENA_GET(reg) BSP_FLD32GET(reg,8, 11)
#define TMS570_SCI_IODFTCTRL_IODFTENA_SET(reg,val) BSP_FLD32SET(reg, val,8, 11)

/* field: LPBENA - Module loopback enable. Write access permitted in Privilege mode only. */
#define TMS570_SCI_IODFTCTRL_LPBENA BSP_FLD32(1)

/* field: RXPENA - Module analog loopback through receive pin enable. */
#define TMS570_SCI_IODFTCTRL_RXPENA BSP_FLD32(0)



#endif /* LIBBSP_ARM_tms570_SCI */
