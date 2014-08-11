/*-
 * Copyright (c) 2010 Semihalf, Jakub Klama
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef	_ARM_DAVINCI_IF_DVEREG_H
#define	_ARM_DAVINCI_IF_DVEREG_H

#define	DVE_EMACTL_BASE			0x1000
#define	DVE_EMACTL_EWCTL		0x04
#define	DVE_EMACTL_EWINTTCNT		0x08

#define	DVE_MDIO_BASE			0x4000
#define	DVE_MDIO_VERSION		0x00
#define	DVE_MDIO_CONTROL		0x04
#define	DVE_MDIO_CONTROL_IDLE		(1 << 31)
#define	DVE_MDIO_CONTROL_ENABLE		(1 << 30)
#define	DVE_MDIO_CONTROL_FAULT_ENABLE	(1 << 18)
#define	DVE_MDIO_CONTROL_FAULT		(1 << 19)
#define	DVE_MDIO_ALIVE			0x08
#define	DVE_MDIO_LINK			0x0c
#define	DVE_MDIO_LINKINTRAW		0x10
#define	DVE_MDIO_LINKINTMASKED		0x14
#define	DVE_MDIO_USERINTRAW		0x20
#define	DVE_MDIO_USERINTMASKED		0x24
#define	DVE_MDIO_USERINTMASKSET		0x28
#define	DVE_MDIO_USERINTMASKCLEAR	0x2c
#define	DVE_MDIO_USERACCESS0		0x80
#define	DVE_MDIO_USERACCESS_PHYSHIFT	16
#define	DVE_MDIO_USERACCEES_REGSHIFT	21
#define	DVE_MDIO_USERACCESS_ACK		(1 << 29)
#define	DVE_MDIO_USERACCESS_READ	(0 << 30)
#define	DVE_MDIO_USERACCESS_WRITE	(1 << 30)
#define	DVE_MDIO_USERACCESS_GO		(1 << 31)
#define	DVE_MDIO_USERPHYSEL0		0x84
#define	DVE_MDIO_USERACCESS1		0x88
#define	DVE_MDIO_USERPHYSEL1		0x8c

#define	DVE_MDIO_PHYMASK		0x1f
#define	DVE_MDIO_REGMASK		0x1f
#define	DVE_MDIO_DATAMASK		0xffff
#define	DVE_MDIO_BUS_FREQ		99000000	/* 99Mhz */
#define	DVE_MDIO_CLOCK_FREQ		2000000		/* 2Mhz */

#define	DVE_EMAC_BASE			0x0
#define	DVE_EMAC_TXIDVER		0x00
#define	DVE_EMAC_TXCONTROL		0x04
#define	DVE_EMAC_TXTEARDOWN		0x08
#define	DVE_EMAC_RXIDVER		0x10
#define	DVE_EMAC_RXCONTROL		0x14
#define	DVE_EMAC_RXTEARDOWN		0x18
#define	DVE_EMAC_TXINTSTATRAW		0x80
#define	DVE_EMAC_TXINTSTATMASKED	0x84
#define	DVE_EMAC_TXINTMASKSET		0x88
#define	DVE_EMAC_TXINTMASKCLEAR		0x8c
#define	DVE_EMAC_MACINTVECTOR		0x90
#define	DVE_EMAC_MACINTVECTOR_HOSTPEND	(1 << 17)
#define	DVE_EMAC_MACINTVECTOR_STATPEND	(1 << 16)
#define	DVE_EMAC_MACINTVECTOR_TXPENDSHIFT	0
#define	DVE_EMAC_MACINTVECTOR_RXPENDSHIFT	8
#define	DVE_EMAC_RXINTSTATRAW		0xa0
#define	DVE_EMAC_RXINTSTATMASKED	0xa4
#define	DVE_EMAC_RXINTMASKSET		0xa8
#define	DVE_EMAC_RXINTMASKCLEAR		0xac
#define	DVE_EMAC_MACINTSTATRAW		0xb0
#define	DVE_EMAC_MACINTSTATMASKED	0xb4
#define	DVE_EMAC_MACINTMASKSET		0xb8
#define	DVE_EMAC_MACINTMASKCLEAR	0xbc
#define	DVE_EMAC_RXMBPENABLE		0x100
#define	DVE_EMAC_RXMBPENABLE_RXMULTCHMASK	0x7
#define	DVE_EMAC_RXMBPENABLE_RXMULTCHSHIFT	0
#define	DVE_EMAC_RXMBPENABLE_RXMULTEN		(1 << 5)
#define	DVE_EMAC_RXMBPENABLE_RXBROADCHMASK	0x7
#define	DVE_EMAC_RXMBPENABLE_RXBROADCHSHIFT	8
#define	DVE_EMAC_RXMBPENABLE_RXBROADEN		(1 << 13)
#define	DVE_EMAC_RXMBPENABLE_RXPROMCHMASK	0x7
#define	DVE_EMAC_RXMBPENABLE_RXPROMCHSHIFT	16
#define	DVE_EMAC_RXMBPENABLE_RXCAFEN		(1 << 21)
#define	DVE_EMAC_RXMBPENABLE_RXCEFEN		(1 << 22)
#define	DVE_EMAC_RXMBPENABLE_RXCSFEN		(1 << 23)
#define	DVE_EMAC_RXMBPENABLE_RXCMFEN		(1 << 24)
#define	DVE_EMAC_RXMBPENABLE_RXNOCHAIN		(1 << 28)
#define	DVE_EMAC_RXMBPENABLE_RXQOSEN		(1 << 29)
#define	DVE_EMAC_RXMBPENABLE_RXPASSCRC		(1 << 30)
#define	DVE_EMAC_RXUNICASTSET		0x104
#define	DVE_EMAC_RXUNICASTCLEAR		0x108
#define	DVE_EMAC_RXMAXLEN		0x10c
#define	DVE_EMAC_RXBUFFEROFFSET		0x110
#define	DVE_EMAC_RXFILTERLOWTHRESH	0x114
#define	DVE_EMAC_RX0FLOWTHRESH		0x120
#define	DVE_EMAC_RX1FLOWTHRESH		0x124
#define	DVE_EMAC_RX2FLOWTHRESH		0x128
#define	DVE_EMAC_RX3FLOWTHRESH		0x12c
#define	DVE_EMAC_RX4FLOWTHRESH		0x130
#define	DVE_EMAC_RX5FLOWTHRESH		0x134
#define	DVE_EMAC_RX6FLOWTHRESH		0x138
#define	DVE_EMAC_RX7FLOWTHRESH		0x13c
#define	DVE_EMAC_RX0FREEBUFFER		0x140
#define	DVE_EMAC_RX1FREEBUFFER		0x144
#define	DVE_EMAC_RX2FREEBUFFER		0x148
#define	DVE_EMAC_RX3FREEBUFFER		0x14c
#define	DVE_EMAC_RX4FREEBUFFER		0x150
#define	DVE_EMAC_RX5FREEBUFFER		0x154
#define	DVE_EMAC_RX6FREEBUFFER		0x158
#define	DVE_EMAC_RX7FREEBUFFER		0x15c
#define	DVE_EMAC_MACCONTROL		0x160
#define	DVE_EMAC_MACSTATUS		0x164
#define	DVE_EMAC_EMCONTROL		0x168
#define	DVE_EMAC_FIFOCONTROL		0x16c
#define	DVE_EMAC_MACCONFIG		0x170
#define	DVE_EMAC_SOFTRESET		0x174
#define	DVE_EMAC_MACSRCADDRLO		0x1d0
#define	DVE_EMAC_MACSRCADDRHI		0x1d4
#define	DVE_EMAC_MACHASH1		0x1d8
#define	DVE_EMAC_MACHASH2		0x1dc
#define	DVE_EMAC_BOFFTEST		0x1e0
#define	DVE_EMAC_TPACETEST		0x1e4
#define	DVE_EMAC_RXPAUSE		0x1e8
#define	DVE_EMAC_TXPAUSE		0x1ec
#define	DVE_EMAC_STATSBASE		0x200
#define	DVE_EMAC_MACADDRLO		0x500
#define	DVE_EMAC_MACADDRHI		0x504
#define	DVE_EMAC_MACINDEX		0x508
#define	DVE_EMAC_TX0HDP			0x600
#define	DVE_EMAC_TXnHDP(_n)		(DVE_EMAC_TX0HDP + (_n * 4))
#define	DVE_EMAC_TX1HDP			0x604
#define	DVE_EMAC_TX2HDP			0x608
#define	DVE_EMAC_TX3HDP			0x60c
#define	DVE_EMAC_TX4HDP			0x610
#define	DVE_EMAC_TX5HDP			0x614
#define	DVE_EMAC_TX6HDP			0x618
#define	DVE_EMAC_TX7HDP			0x61c
#define	DVE_EMAC_RX0HDP			0x620
#define	DVE_EMAC_RXnHDP(_n)		(DVE_EMAC_RX0HDP + (_n * 4))
#define	DVE_EMAC_RX1HDP			0x624
#define	DVE_EMAC_RX2HDP			0x628
#define	DVE_EMAC_RX3HDP			0x62c
#define	DVE_EMAC_RX4HDP			0x630
#define	DVE_EMAC_RX5HDP			0x634
#define	DVE_EMAC_RX6HDP			0x638
#define	DVE_EMAC_RX7HDP			0x63c
#define	DVE_EMAC_TX0CP			0x640
#define	DVE_EMAC_TXnCP(_n)		(DVE_EMAC_TX0CP + (_n * 4))
#define	DVE_EMAC_TX1CP			0x644
#define	DVE_EMAC_TX2CP			0x648
#define	DVE_EMAC_TX3CP			0x64c
#define	DVE_EMAC_TX4CP			0x650
#define	DVE_EMAC_TX5CP			0x654
#define	DVE_EMAC_TX6CP			0x658
#define	DVE_EMAC_TX7CP			0x65c
#define	DVE_EMAC_RX0CP			0x660
#define	DVE_EMAC_RXnCP(_n)		(DVE_EMAC_RX0CP + (_n * 4))
#define	DVE_EMAC_RX1CP			0x664
#define	DVE_EMAC_RX2CP			0x668
#define	DVE_EMAC_RX3CP			0x66c
#define	DVE_EMAC_RX4CP			0x670
#define	DVE_EMAC_RX5CP			0x674
#define	DVE_EMAC_RX6CP			0x678
#define	DVE_EMAC_RX7CP			0x67c

#define	DVE_TXCH_NUM			8
#define	DVE_RXCH_NUM			8
#define	DVE_TXDESC_NUM			128
#define	DVE_RXDESC_NUM			128
#define	DVE_TXDESC_SIZE			(DVE_TXDESC_NUM * sizeof(struct dve_hwdesc))
#define	DVE_RXDESC_SIZE			(DVE_RXDESC_NUM * sizeof(struct dve_hwdesc))
#define	DVE_TXDESC_OFFSET(_n)		(_n * sizeof(struct dve_hwdesc))
#define	DVE_RXDESC_OFFSET(_n)		(_n * sizeof(struct dve_hwdesc))
#define	DVE_MAXFRAGS			8
#define	DVE_INC(x, y)			(x) = ((x) == ((y)-1)) ? 0 : (x)+1
#define	DVE_NEXT(x, y)			(((x) == ((y)-1)) ? 0 : (x+1))
#define	DVE_PREV(x, y)			(((x) == 0) ? (y-1) : (x-1))

#define	DVE_EMAC_MAX_PKTSIZE		1536
#define	DVE_EMAC_MIN_PKTSIZE		60

struct dve_hwdesc {
	uint32_t	hw_next;
	uint32_t	hw_buffer;
	uint32_t	hw_offlen;
	uint32_t	hw_flagslen;
#define	DVE_HWDESC_OWNER	(1 << 29)
#define	DVE_HWDESC_SOP		(1 << 31)
#define	DVE_HWDESC_EOP		(1 << 30)
#define	DVE_HWDESC_EOQ		(1 << 28)
#define	DVE_HWDESC_TDOWNCMPLT	(1 << 27)
#define	DVE_HWDESC_PASSCRC	(1 << 26)
#define	DVE_HWDESC_JABBER	(1 << 25)
#define	DVE_HWDESC_OVERSIZE	(1 << 24)
#define	DVE_HWDESC_FRAGMENT	(1 << 23)
#define	DVE_HWDESC_UNDERSIZED	(1 << 22)
#define	DVE_HWDESC_CONTROL	(1 << 21)
#define	DVE_HWDESC_OVERRUN	(1 << 20)
#define	DVE_HWDESC_COREERROR	(1 << 19)
#define	DVE_HWDESC_ALIGNERROR	(1 << 18)
#define	DVE_HWDESC_CRCERROR	(1 << 17)
#define	DVE_HWDESC_NOMATCH	(1 << 16)
};

struct dve_hwstats {
	uint32_t	rx_good_frames;
	uint32_t	rx_bcast_frames;
	uint32_t	rx_mcast_frames;
	uint32_t	rx_pause_frames;
	uint32_t	rx_crc_errors;
	uint32_t	rx_align_errors;
	uint32_t	rx_oversized_errors;
	uint32_t	rx_jabber_errors;
	uint32_t	rx_undersized_errors;
	uint32_t	rx_frame_fragment_errors;
	uint32_t	rx_filtered;
	uint32_t	rx_qos_filtered;
	uint32_t	rx_octets;
	uint32_t	tx_good_frames;
	uint32_t	tx_bcast_frames;
	uint32_t	tx_mcast_frames;
	uint32_t	tx_pause_frames;
	uint32_t	tx_deferred;
	uint32_t	tx_collisions;
	uint32_t	tx_single_collision;
	uint32_t	tx_multiple_collision;
	uint32_t	tx_excessive_collision;
	uint32_t	tx_late_collision;
	uint32_t	tx_underrun_errors;
	uint32_t	tx_carrier_errors;
	uint32_t	tx_octets;
	uint32_t	frames64;
	uint32_t	frames65t127;
	uint32_t	frames128t255;
	uint32_t	frames256t511;
	uint32_t	frames512t1023;
	uint32_t	frames1024tup;
	uint32_t	netoctets;
	uint32_t	rx_sof_overruns;
	uint32_t	rx_mof_overruns;
	uint32_t	rx_dma_overruns;
};

#endif	/* _ARM_DAVINCI_IF_DVEREG_H */
