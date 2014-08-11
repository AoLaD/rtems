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

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/param.h>
#include <sys/endian.h>
#include <sys/systm.h>
#include <sys/sockio.h>
#include <sys/mbuf.h>
#include <sys/malloc.h>
#include <sys/kernel.h>
#include <sys/module.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/rman.h>
#include <sys/bus.h>
#include <sys/socket.h>
#include <machine/bus.h>
#include <machine/intr.h>

#include <sys/kdb.h>

#include <net/if.h>
#include <net/if_arp.h>
#include <net/ethernet.h>
#include <net/if_dl.h>
#include <net/if_media.h>
#include <net/if_types.h>

#include <net/bpf.h>

#include <dev/mii/mii.h>
#include <dev/mii/miivar.h>

#include <arm/davinci/if_dvereg.h>

#include "miibus_if.h"

#define	DVE_HWDESC_ERROR	\
    (DVE_HWDESC_JABBER | DVE_HWDESC_OVERSIZE | DVE_HWDESC_OVERSIZE | 		\
    DVE_HWDESC_FRAGMENT | DVE_HWDESC_UNDERSIZED | DVE_HWDESC_OVERRUN |		\
    DVE_HWDESC_COREERROR | DVE_HWDESC_ALIGNERROR | DVE_HWDESC_NOMATCH)

struct dve_dmamap_arg {
	bus_addr_t		dve_dma_busaddr;
};

struct dve_txdesc {
	struct mbuf *		dve_txdesc_mbuf;
	bus_dmamap_t		dve_txdesc_dmamap;
};

struct dve_txchannel {
	struct dve_softc *	dve_tx_softc;
	int			dve_tx_active;
	int			dve_tx_num;
	bus_dma_tag_t		dve_tx_desc_tag;
	bus_dmamap_t		dve_tx_desc_map;
	uint32_t		dve_tx_desc_addr;
	bus_dma_tag_t		dve_tx_buf_tag;
	struct dve_hwdesc *	dve_tx_hwdesc;
	struct dve_txdesc	dve_tx_desc[DVE_TXDESC_NUM];
	int			dve_tx_prod;
	int			dve_tx_cons;
	int			dve_tx_count;
	int			dve_tx_used;
};

struct dve_rxdesc {
	struct mbuf *		dve_rxdesc_mbuf;
	bus_dmamap_t		dve_rxdesc_dmamap;
};

struct dve_rxchannel {
	struct dve_softc *	dve_rx_softc;
	int			dve_rx_active;
	int			dve_rx_num;
	bus_dma_tag_t		dve_rx_desc_tag;
	bus_dmamap_t		dve_rx_desc_map;
	uint32_t		dve_rx_desc_addr;
	bus_dma_tag_t		dve_rx_buf_tag;
	struct dve_hwdesc *	dve_rx_hwdesc;
	struct dve_rxdesc	dve_rx_desc[DVE_RXDESC_NUM];
	int			dve_rx_prod;
	int			dve_rx_cons;
	int			dve_rx_used;
};

struct dve_softc {
	struct ifnet *		dve_ifp;
	struct mtx		dve_mtx;
	device_t		dve_dev;
	device_t		dve_miibus;
	struct resource *	dve_mem_res;
	struct resource *	dve_irq_res;
	bus_space_tag_t		dve_bst;
	bus_space_handle_t	dve_bsh;
	int			dve_flags;
#define	DVE_FLAG_LINK		0x1
	struct dve_txchannel	dve_txch[DVE_TXCH_NUM];
	struct dve_rxchannel	dve_rxch[DVE_RXCH_NUM];
	uint8_t			dve_enaddr[6];
	bus_dma_tag_t		dve_parent_tag;
	void *			dve_intrhand;
	struct callout		dve_tick;
	int			dve_debug;
	int			dve_watchdog_timer;
};

static int dve_probe(device_t);
static int dve_attach(device_t);
static int dve_detach(device_t);
static int dve_miibus_readreg(device_t, int, int);
static int dve_miibus_writereg(device_t, int, int, int);
static void dve_miibus_statchg(device_t);

static void dve_init(void *);
static void dve_init_locked(void *);
static void dve_start(struct ifnet *);
static void dve_start_locked(struct ifnet *);
static void dve_stop(struct dve_softc *);
static void dve_stop_locked(struct dve_softc *);
static int dve_ioctl(struct ifnet *, u_long, caddr_t);
static void dve_intr(void *);
static void dve_txintr(struct dve_txchannel *);
static void dve_rxintr(struct dve_rxchannel *);
static void dve_tick(void *);
static void dve_watchdog(struct dve_softc *);
static void dve_set_rxmode(struct dve_softc *);

static int dve_encap(struct dve_txchannel *, struct mbuf **, int *);
static int dve_dma_alloc(struct dve_softc *);
static void dve_dmamap_cb(void *, bus_dma_segment_t *, int, int);
static void dve_mdio_init(struct dve_softc *);
static int dve_init_txch(struct dve_txchannel *, int);
static int dve_init_rxch(struct dve_rxchannel *, int);
static int dve_reset_txch(struct dve_txchannel *);
static int dve_reset_rxch(struct dve_rxchannel *);
static int dve_stop_txch(struct dve_txchannel *);
static int dve_stop_rxch(struct dve_rxchannel *);
static int dve_init_rxbuf(struct dve_rxchannel *, int);
static void dve_discard_rxbuf(struct dve_rxchannel *, int);
static int dve_ifmedia_upd(struct ifnet *);
static void dve_ifmedia_sts(struct ifnet *, struct ifmediareq *);
static void dve_stats_update(struct dve_softc *);

#define	dve_lock(_sc)		mtx_lock(&(_sc)->dve_mtx)
#define	dve_unlock(_sc)		mtx_unlock(&(_sc)->dve_mtx)
#define	dve_lock_assert(_sc)	mtx_assert(&(_sc)->dve_mtx, MA_OWNED)

#define	dve_read_mdio_4(sc, reg)		\
    bus_space_read_4(sc->dve_bst, sc->dve_bsh, DVE_MDIO_BASE + reg)
#define	dve_write_mdio_4(sc, reg, data)		\
    bus_space_write_4(sc->dve_bst, sc->dve_bsh, DVE_MDIO_BASE + reg, data)

#define	dve_read_emac_4(sc, reg)		\
    bus_space_read_4(sc->dve_bst, sc->dve_bsh, DVE_EMAC_BASE + reg)
#define	dve_write_emac_4(sc, reg, data)		\
    bus_space_write_4(sc->dve_bst, sc->dve_bsh, DVE_EMAC_BASE + reg, data)

#define	dve_read_emactl_4(sc, reg)		\
    bus_space_read_4(sc->dve_bst, sc->dve_bsh, DVE_EMACTL_BASE + reg)
#define	dve_write_emactl_4(sc, reg, data)	\
    bus_space_write_4(sc->dve_bst, sc->dve_bsh, DVE_EMACTL_BASE + reg, data)

static int
dve_probe(device_t dev)
{
	device_set_desc(dev, "TI DaVinci 10/100 EMAC");
	return (BUS_PROBE_DEFAULT);
}

static int
dve_attach(device_t dev)
{
	struct dve_softc *sc = device_get_softc(dev);
	struct ifnet *ifp;
	int rid, i;

	sc->dve_dev = dev;

	/* XXX how to get proper MAC address? */
	/* semihalf: 00:26:D0:00:00:03 */
	sc->dve_enaddr[0] = 0x00;
	sc->dve_enaddr[1] = 0x26;
	sc->dve_enaddr[2] = 0xd0;
	sc->dve_enaddr[3] = 0x00;
	sc->dve_enaddr[4] = 0x00;
	sc->dve_enaddr[5] = 0x03;

	mtx_init(&sc->dve_mtx, device_get_nameunit(dev), MTX_NETWORK_LOCK,
	    MTX_DEF);

	callout_init_mtx(&sc->dve_tick, &sc->dve_mtx, 0);

	rid = 0;
	sc->dve_mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE);
	if (!sc->dve_mem_res) {
		device_printf(dev, "cannot allocate memory window\n");
		goto fail;
	}

	sc->dve_bst = rman_get_bustag(sc->dve_mem_res);
	sc->dve_bsh = rman_get_bushandle(sc->dve_mem_res);

	rid = 0;
	sc->dve_irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (!sc->dve_irq_res) {
		device_printf(dev, "cannot allocate interrupt\n");
		goto fail;
	}

	sc->dve_ifp = if_alloc(IFT_ETHER);
	if (!sc->dve_ifp) {
		device_printf(dev, "cannot allocate ifnet\n");
		goto fail;
	}

	ifp = sc->dve_ifp;

	dve_mdio_init(sc);

	if (mii_phy_probe(dev, &sc->dve_miibus, dve_ifmedia_upd, 
	    dve_ifmedia_sts)) {
		device_printf(dev, "cannot find PHY\n");
		goto fail;
	}

	if_initname(ifp, device_get_name(dev), device_get_unit(dev));
	ifp->if_softc = sc;
	ifp->if_flags = IFF_BROADCAST | IFF_SIMPLEX | IFF_MULTICAST;
	ifp->if_start = dve_start;
	ifp->if_ioctl = dve_ioctl;
	ifp->if_init = dve_init;
	IFQ_SET_MAXLEN(&ifp->if_snd, IFQ_MAXLEN);
	ifp->if_snd.ifq_drv_maxlen = IFQ_MAXLEN;
	IFQ_SET_READY(&ifp->if_snd);

	ether_ifattach(ifp, sc->dve_enaddr);

	if (bus_setup_intr(dev, sc->dve_irq_res, INTR_TYPE_NET, NULL, dve_intr,
	    sc, &sc->dve_intrhand)) {
		device_printf(dev, "cannot establish interrupt handler\n");
		ether_ifdetach(ifp);
		goto fail;
	}

	for (i = 0; i < DVE_TXCH_NUM; i++)
		sc->dve_txch[0].dve_tx_softc = sc;

	for (i = 0; i < DVE_RXCH_NUM; i++)
		sc->dve_rxch[0].dve_rx_softc = sc;

	dve_dma_alloc(sc);
	dve_init_txch(&sc->dve_txch[0], 0);
	dve_init_rxch(&sc->dve_rxch[0], 0);

	return (0);

fail:
	if (sc->dve_ifp)
		if_free(sc->dve_ifp);
	if (sc->dve_intrhand)
		bus_teardown_intr(dev, sc->dve_irq_res, sc->dve_intrhand);
	if (sc->dve_mem_res)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->dve_mem_res);
	if (sc->dve_irq_res)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->dve_irq_res);
	return (ENXIO);
}

static int
dve_detach(device_t dev)
{
	struct dve_softc *sc = device_get_softc(dev);
	dve_stop(sc);
	return (0);
}

static int
dve_miibus_readreg(device_t dev, int phy, int reg)
{
	struct dve_softc *sc = device_get_softc(dev);
	uint32_t val = 0;

	dve_write_mdio_4(sc, DVE_MDIO_USERACCESS0,
	    (phy & DVE_MDIO_PHYMASK) << DVE_MDIO_USERACCESS_PHYSHIFT |
	    (reg & DVE_MDIO_REGMASK) << DVE_MDIO_USERACCEES_REGSHIFT |
	    DVE_MDIO_USERACCESS_READ |
	    DVE_MDIO_USERACCESS_GO);

	val = dve_read_mdio_4(sc, DVE_MDIO_USERACCESS0);

	/* Wait until MDIO request is completed */
	while (val & DVE_MDIO_USERACCESS_GO) {
		val = dve_read_mdio_4(sc, DVE_MDIO_USERACCESS0);
		DELAY(10);
	}

	if (!(val & DVE_MDIO_USERACCESS_ACK))
		return (0);

	return (val & DVE_MDIO_DATAMASK);
}

static int
dve_miibus_writereg(device_t dev, int phy, int reg, int data)
{
	struct dve_softc *sc = device_get_softc(dev);
	uint32_t val = 0;

	dve_write_mdio_4(sc, DVE_MDIO_USERACCESS0,
	    (data & DVE_MDIO_DATAMASK) |
	    (phy & DVE_MDIO_PHYMASK) << DVE_MDIO_USERACCESS_PHYSHIFT |
	    (reg & DVE_MDIO_REGMASK) << DVE_MDIO_USERACCEES_REGSHIFT |
	    DVE_MDIO_USERACCESS_READ |
	    DVE_MDIO_USERACCESS_GO);

	val = dve_read_mdio_4(sc, DVE_MDIO_USERACCESS0);

	/* Wait until MDIO request is completed */
	while (val & DVE_MDIO_USERACCESS_GO) {
		val = dve_read_mdio_4(sc, DVE_MDIO_USERACCESS0);
		DELAY(10);
	}

	return (0);
}

static void
dve_miibus_statchg(device_t dev)
{
	struct dve_softc *sc = device_get_softc(dev);
	struct mii_data *mii = device_get_softc(sc->dve_miibus);

	if ((mii->mii_media_status & IFM_ACTIVE) &&
	    (mii->mii_media_status & IFM_AVALID))
		sc->dve_flags |= DVE_FLAG_LINK;
	else
		sc->dve_flags &= ~DVE_FLAG_LINK;
}

static void
dve_init(void *arg)
{
	struct dve_softc *sc = (struct dve_softc *)arg;

	dve_lock(sc);
	dve_init_locked(arg);
	dve_unlock(sc);
}

static void
dve_init_locked(void *arg)
{
	struct dve_softc *sc = (struct dve_softc *)arg;
	struct ifnet *ifp = sc->dve_ifp;
	uint32_t machi, maclo;
	int i;

	dve_lock_assert(sc);

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	dve_write_emac_4(sc, DVE_EMAC_SOFTRESET, 1);

	while (dve_read_emac_4(sc, DVE_EMAC_SOFTRESET))
		DELAY(10);

	dve_write_emactl_4(sc, DVE_EMACTL_EWCTL, 0);
	DELAY(50);

	dve_write_emac_4(sc, DVE_EMAC_TXCONTROL, 0x01);
	dve_write_emac_4(sc, DVE_EMAC_RXCONTROL, 0x01);
	dve_write_emac_4(sc, DVE_EMAC_MACINDEX, 0);

	machi =
	    sc->dve_enaddr[3] << 24 |
	    sc->dve_enaddr[2] << 16 |
	    sc->dve_enaddr[1] << 8 |
	    sc->dve_enaddr[0];
	maclo =
	    sc->dve_enaddr[5] << 8 |
	    sc->dve_enaddr[4];

	dve_write_emac_4(sc, DVE_EMAC_MACADDRHI, machi);
	dve_write_emac_4(sc, DVE_EMAC_MACADDRLO, maclo);
	dve_write_emac_4(sc, DVE_EMAC_MACSRCADDRHI, machi);
	dve_write_emac_4(sc, DVE_EMAC_MACSRCADDRLO, maclo);
	dve_write_emac_4(sc, DVE_EMAC_MACHASH1, 0);
	dve_write_emac_4(sc, DVE_EMAC_MACHASH2, 0);

	/* Initialize TX DMA head pointers to 0 */
	for (i = 0; i < DVE_TXCH_NUM; i++)
		dve_write_emac_4(sc, DVE_EMAC_TXnHDP(i), 0);

	/* Same with RX DMX head pointers */
	for (i = 0; i < DVE_TXCH_NUM; i++)
		dve_write_emac_4(sc, DVE_EMAC_RXnHDP(i), 0);

	dve_write_emac_4(sc, DVE_EMAC_RXMAXLEN, DVE_EMAC_MAX_PKTSIZE);
	dve_write_emac_4(sc, DVE_EMAC_RXBUFFEROFFSET, 0);

	/* Mask all TX/RX channel interrupts for now */
	dve_write_emac_4(sc, DVE_EMAC_TXINTMASKCLEAR, ~0L);
	dve_write_emac_4(sc, DVE_EMAC_RXINTMASKCLEAR, ~0L);

	/* Enable host error interrupt */
	dve_write_emac_4(sc, DVE_EMAC_MACINTMASKSET, 0x2);

	/* Initialize RX 0 and TX 0 channels */
	dve_reset_txch(&sc->dve_txch[0]);
	dve_reset_rxch(&sc->dve_rxch[0]);

	dve_write_emactl_4(sc, DVE_EMACTL_EWCTL, 0x1);
	dve_write_emac_4(sc, DVE_EMAC_MACCONTROL, (1 << 0) | (1 << 5));

	dve_set_rxmode(sc);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	callout_reset(&sc->dve_tick, hz, dve_tick, sc);
}

static void
dve_start(struct ifnet *ifp)
{
	struct dve_softc *sc = ifp->if_softc;
	dve_lock(sc);
	dve_start_locked(ifp);
	dve_unlock(sc);
}

static void
dve_start_locked(struct ifnet *ifp)
{
	struct dve_softc *sc = ifp->if_softc;
	struct dve_txchannel *txch;
	struct mbuf *m_head;
	int encap = 0, txused = 0;

	dve_lock_assert(sc);

	/* We use only TX channel 0 */
	txch = &sc->dve_txch[0];

	if (txch->dve_tx_used >= DVE_TXDESC_NUM-1) {
		device_printf(sc->dve_dev, 
		    "WARNING: TX descriptors exhausted!\n");
		return;
	}

	while (!IFQ_DRV_IS_EMPTY(&ifp->if_snd) 
	    && txch->dve_tx_used < DVE_TXDESC_NUM-1) {
		/* Dequeue first packet */
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m_head);
		if (!m_head)
			break;

		if (dve_encap(txch, &m_head, &txused)) {
			if (m_head == NULL)
				break;
			
			IFQ_DRV_PREPEND(&ifp->if_snd, m_head);
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}

		ETHER_BPF_MTAP(ifp, m_head);
		encap++;
	}

	/*
	 * Submit new descriptor list if
	 * a) at least one packet was dequeued,
	 * b) there is no another transfer already active
	 */
	if (encap && (txch->dve_tx_used - txused) == 0) {
		dve_write_emac_4(sc, DVE_EMAC_TXnHDP(0),
		    txch->dve_tx_desc_addr + 
		    DVE_TXDESC_OFFSET(txch->dve_tx_cons));

		sc->dve_watchdog_timer = 5;
	}
}

static void
dve_stop(struct dve_softc *sc)
{
	dve_lock(sc);
	dve_stop_locked(sc);
	dve_unlock(sc);
}

static void
dve_stop_locked(struct dve_softc *sc)
{
	dve_lock(sc);

	/* Disable callout */
	callout_stop(&sc->dve_tick);

	/* We use only TX/RX channel 0 */
	dve_stop_txch(&sc->dve_txch[0]);
	dve_stop_rxch(&sc->dve_rxch[0]);

	/* Disable all host interrupts */
	dve_write_emac_4(sc, DVE_EMAC_MACINTMASKCLEAR, ~0);
	dve_write_emactl_4(sc, DVE_EMACTL_EWCTL, 0);

	/* Disable interface */
	sc->dve_ifp->if_drv_flags &= ~IFF_DRV_RUNNING;

	dve_unlock(sc);
}

static int
dve_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct dve_softc *sc = ifp->if_softc;
	struct mii_data *mii = device_get_softc(sc->dve_miibus);
	struct ifreq *ifr = (struct ifreq *)data;
	int error = 0;

	switch (cmd) {
	case SIOCSIFFLAGS:
		dve_lock(sc);
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				dve_set_rxmode(sc);
			else
				dve_init_locked(sc);
		} else
			dve_stop(sc);
		dve_unlock(sc);
		break;
	case SIOCGIFMEDIA:
	case SIOCSIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, cmd);
		break;
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}

static void
dve_intr(void *arg)
{
	struct dve_softc *sc = (struct dve_softc *)arg;
	uint32_t macint;
	uint32_t macstatus;
	int i;

	dve_lock(sc);

	while ((macint = dve_read_emac_4(sc, DVE_EMAC_MACINTVECTOR))) {
		/*
		 * Host error pending, chip reset needed to continue operation
		 */
		if (macint & DVE_EMAC_MACINTVECTOR_HOSTPEND) {
			macstatus = dve_read_emac_4(sc, DVE_EMAC_MACSTATUS);
			device_printf(sc->dve_dev, "hardware error tx:%d/rx:%d "
			    "on channel tx:%d/rx:%d\n",
			    (macstatus >> 20) & 0xf, (macstatus >> 12) & 0xf,
			    (macstatus >> 16) & 0x7, (macstatus >> 8) & 0xf);

			device_printf(sc->dve_dev, "resetting chip...\n");
			sc->dve_ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
			dve_init(sc);
			return;
		}

		/*
		 * Statistics interrupt pending
		 */
		if (macint & DVE_EMAC_MACINTVECTOR_STATPEND)
			panic("dve: unwanted statistics interrupt pending");

		/*
		 * TX channel [0..DVE_TXCH_NUM] interrupt pending
		 */
		for (i = 0; i < DVE_TXCH_NUM; i++) {
			if (macint & (1 << (DVE_EMAC_MACINTVECTOR_TXPENDSHIFT + i))) {
				if (!sc->dve_txch[i].dve_tx_active)
					panic("dve: spurious interrupt from "
					      "inactive TX channel!\n");

				dve_txintr(&sc->dve_txch[i]);
			}
		}

		/*
		 * RX channel [0..DVE_RXCHNUM] interrupt pending
		 */
		for (i = 0; i < DVE_RXCH_NUM; i++) {
			if (macint & (1 << (DVE_EMAC_MACINTVECTOR_RXPENDSHIFT + i))) {
				if (!sc->dve_rxch[i].dve_rx_active)
					panic("dve: spurious interrupt from "
					      "inactive RX channel!\n");

				dve_rxintr(&sc->dve_rxch[i]);
			}
		}
	}

	dve_unlock(sc);
}

static void
dve_txintr(struct dve_txchannel *txch)
{
	struct dve_softc *sc = txch->dve_tx_softc;
	struct dve_txdesc *txd;
	struct dve_hwdesc *hwd;
	int prod, cons, processed = 0;
	uint32_t flags;

	bus_dmamap_sync(txch->dve_tx_desc_tag, txch->dve_tx_desc_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	cons = txch->dve_tx_cons;
	prod = txch->dve_tx_prod;

	for (; cons != prod; DVE_INC(cons, DVE_TXDESC_NUM)) {
		txd = &txch->dve_tx_desc[cons];
		hwd = &txch->dve_tx_hwdesc[cons];
		flags = hwd->hw_flagslen;

		if (flags & DVE_HWDESC_OWNER)
			break;

		processed++;

		/* Update TX completion pointer register */
		dve_write_emac_4(sc, DVE_EMAC_TXnCP(txch->dve_tx_num),
		    txch->dve_tx_desc_addr + DVE_TXDESC_OFFSET(cons));

		if (flags & DVE_HWDESC_SOP) {
			/* Unload DMA map and so on */
			bus_dmamap_sync(txch->dve_tx_buf_tag,
			    txd->dve_txdesc_dmamap, BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(txch->dve_tx_buf_tag,
			    txd->dve_txdesc_dmamap);
			
			if (txd->dve_txdesc_mbuf) {
				m_freem(txd->dve_txdesc_mbuf);
				txd->dve_txdesc_mbuf = NULL;
			}
		}

		/* End of queue, check if misqueued packets are waiting */
		if ((flags & DVE_HWDESC_EOQ) && hwd->hw_next) {
			hwd->hw_flagslen &= ~DVE_HWDESC_EOQ;
			dve_write_emac_4(sc, DVE_EMAC_TXnHDP(txch->dve_tx_num),
			    txch->dve_tx_desc_addr +
			    DVE_TXDESC_OFFSET(DVE_NEXT(cons, DVE_TXDESC_NUM)));
			
			DVE_INC(cons, DVE_TXDESC_NUM);
			break;
		}
	}

	if (processed)
		sc->dve_ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	txch->dve_tx_used -= processed;
	txch->dve_tx_cons = cons;

	if (!txch->dve_tx_used)
		sc->dve_watchdog_timer = 0;
}

static void
dve_rxintr(struct dve_rxchannel *rxch)
{
	struct dve_softc *sc = rxch->dve_rx_softc;
	struct ifnet *ifp = sc->dve_ifp;
	struct dve_rxdesc *rxd;
	struct dve_hwdesc *hwd;
	struct mbuf *m;
	int cons, length, flags, processed = 0;

	dve_lock_assert(sc);

	bus_dmamap_sync(rxch->dve_rx_desc_tag, rxch->dve_rx_desc_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	cons = rxch->dve_rx_cons;

	for (;;) {
		rxd = &rxch->dve_rx_desc[cons];
		hwd = &rxch->dve_rx_hwdesc[cons];
		flags = hwd->hw_flagslen;
		m = rxd->dve_rxdesc_mbuf;

		length = flags & 0xffff;

		m->m_pkthdr.rcvif = ifp;

		if (flags & DVE_HWDESC_EOQ) {
			/*
			 * We've ran out of RX descriptors
			 */
			dve_init_rxbuf(rxch, cons);
			DVE_INC(cons, DVE_RXDESC_NUM);
			dve_write_emac_4(sc, DVE_EMAC_RXnHDP(rxch->dve_rx_num),
			    rxch->dve_rx_desc_addr + DVE_RXDESC_OFFSET(cons));

			break;
		}

		if (flags & DVE_HWDESC_OWNER) {
			/*
			 * It's still our descriptor, so it wasn't processed
			 * by EMAC
			 */
			break;
		}

		processed++;

		if (length == 0) {
			device_printf(sc->dve_dev, 
			    "WARNING: zero length packet?\n");
		}

		if (flags & DVE_HWDESC_ERROR) {
			/* Errorneous frame */
			dve_discard_rxbuf(rxch, cons);
			dve_init_rxbuf(rxch, cons);
			DVE_INC(cons, DVE_RXDESC_NUM);
			continue;
		}

		bus_dmamap_sync(rxch->dve_rx_desc_tag, rxch->dve_rx_desc_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

		dve_write_emac_4(sc, DVE_EMAC_RXnCP(rxch->dve_rx_num),
		    rxch->dve_rx_desc_addr + DVE_RXDESC_OFFSET(cons));

		bus_dmamap_sync(rxch->dve_rx_desc_tag, rxch->dve_rx_desc_map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

		/* Fix alignment */
		m->m_data += 2;

		dve_unlock(sc);
		(*ifp->if_input)(ifp, m);
		dve_lock(sc);

		dve_init_rxbuf(rxch, cons);
		DVE_INC(cons, DVE_RXDESC_NUM);
	}

	bus_dmamap_sync(rxch->dve_rx_desc_tag, rxch->dve_rx_desc_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	rxch->dve_rx_cons = cons;
}

static void
dve_tick(void *arg)
{
	struct dve_softc *sc = (struct dve_softc *)arg;
	struct mii_data *mii = device_get_softc(sc->dve_miibus);

	dve_lock_assert(sc);

	mii_tick(mii);
	dve_stats_update(sc);
	dve_watchdog(sc);

	callout_reset(&sc->dve_tick, hz, dve_tick, sc);
}

static void
dve_watchdog(struct dve_softc *sc)
{
	struct ifnet *ifp = sc->dve_ifp;

	dve_lock_assert(sc);

	if (!sc->dve_watchdog_timer || sc->dve_watchdog_timer--)
		return;

	/* Chip has stopped responding */
	device_printf(sc->dve_dev, "WARNING: TX timeout, resetting chip\n");
	dve_stop_locked(sc);
	dve_init_locked(sc);

	/* Flush packets from send queue */
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		dve_start_locked(ifp);
}

static void
dve_set_rxmode(struct dve_softc *sc)
{
	struct ifnet *ifp = sc->dve_ifp;
	uint32_t rxmbpenable = dve_read_emac_4(sc, DVE_EMAC_RXMBPENABLE);

	dve_lock_assert(sc);

	if (ifp->if_flags & IFF_PROMISC)
		rxmbpenable |= DVE_EMAC_RXMBPENABLE_RXCAFEN;
	else
		rxmbpenable &= ~DVE_EMAC_RXMBPENABLE_RXCAFEN;

	if (ifp->if_flags & IFF_BROADCAST)
		rxmbpenable |= DVE_EMAC_RXMBPENABLE_RXBROADEN;
	else
		rxmbpenable &= ~DVE_EMAC_RXMBPENABLE_RXBROADEN;

	dve_write_emac_4(sc, DVE_EMAC_RXMBPENABLE, rxmbpenable);
}

static int
dve_encap(struct dve_txchannel *txch, struct mbuf **m_head, int *txused)
{
	struct dve_softc *sc = txch->dve_tx_softc;
	struct dve_txdesc *txd;
	struct dve_hwdesc *hwd;
	struct mbuf *m;
	bus_dma_segment_t segs[DVE_MAXFRAGS];
	int error, nsegs, i, prod, length, padlen;

	dve_lock_assert(sc);
	M_ASSERTPKTHDR((*m_head));

	prod = txch->dve_tx_prod;
	txd = &txch->dve_tx_desc[prod];

	if ((*m_head)->m_pkthdr.len < DVE_EMAC_MIN_PKTSIZE) {
		/* We need to pad frame to at least 64 bytes */
		m = *m_head;
		padlen = DVE_EMAC_MIN_PKTSIZE - m->m_pkthdr.len;

		if (!M_WRITABLE(m)) {
			/* Get a writable copy. */
			m = m_dup(*m_head, M_DONTWAIT);
			m_freem(*m_head);
			if (!m) {
				*m_head = NULL;
				return (ENOBUFS);
			}
		}

		if (m->m_next != NULL || M_TRAILINGSPACE(m) < padlen) {
			m = m_defrag(m, M_DONTWAIT);
			if (!m) {
				m_freem(*m_head);
				*m_head = NULL;
				return (ENOBUFS);
			}
		}

		/*
		 * Manually pad short frames, and zero the pad space
		 * to avoid leaking data.
		 */
		bzero(mtod(m, char *) + m->m_pkthdr.len, padlen);
		m->m_pkthdr.len += padlen;
		m->m_len = m->m_pkthdr.len;
		*m_head = m;
	}

	error = bus_dmamap_load_mbuf_sg(txch->dve_tx_buf_tag,
	    txd->dve_txdesc_dmamap, *m_head, segs, &nsegs, BUS_DMA_NOWAIT);

	bus_dmamap_sync(txch->dve_tx_buf_tag, txd->dve_txdesc_dmamap,
	    BUS_DMASYNC_PREREAD);
	bus_dmamap_sync(txch->dve_tx_desc_tag, txch->dve_tx_desc_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	if (error)
		return (error);

	if (nsegs == 0) {
		m_freem(*m_head);
		*m_head = NULL;
		return (EIO);
	}

	txd->dve_txdesc_mbuf = *m_head;
	length = (*m_head)->m_pkthdr.len;

	if ((txch->dve_tx_used + nsegs) > DVE_TXDESC_NUM-1) {
		bus_dmamap_unload(txch->dve_tx_buf_tag, txd->dve_txdesc_dmamap);
		device_printf(sc->dve_dev, "WARNING: tx descriptors exhausted\n");
		return (ENOBUFS);
	}

	for (i = 0; i < nsegs; i++) {
		hwd = &txch->dve_tx_hwdesc[prod];
		hwd->hw_next = txch->dve_tx_desc_addr +
		    DVE_TXDESC_OFFSET(DVE_NEXT(prod, DVE_TXDESC_NUM));
		
		hwd->hw_buffer = segs[i].ds_addr;
		hwd->hw_offlen = segs[i].ds_len & 0xffff;
		hwd->hw_flagslen = length & 0xffff;

		if (i == 0)
			hwd->hw_flagslen |= DVE_HWDESC_SOP | DVE_HWDESC_OWNER;

		if (i == nsegs - 1) {
			hwd->hw_flagslen |= DVE_HWDESC_EOP;
			hwd->hw_next = 0;
		}

		DVE_INC(prod, DVE_TXDESC_NUM);
	}

	hwd = &txch->dve_tx_hwdesc[DVE_PREV(txch->dve_tx_prod, DVE_TXDESC_NUM)];
	hwd->hw_next = txch->dve_tx_desc_addr + DVE_TXDESC_OFFSET(txch->dve_tx_prod);

	bus_dmamap_sync(txch->dve_tx_desc_tag, txch->dve_tx_desc_map, 
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	*txused = nsegs;
	txch->dve_tx_used += nsegs;
	txch->dve_tx_prod = prod;

	return (0);
}

static int
dve_dma_alloc(struct dve_softc *sc)
{
	int error;

	/* Parent DMA tag */
	error = bus_dma_tag_create(
	    bus_get_dma_tag(sc->dve_dev),	/* parent tag */
	    1, 0,				/* alignment, boundary */
	    BUS_SPACE_MAXADDR_32BIT,		/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filtarg */
	    BUS_SPACE_MAXSIZE_32BIT, 0,		/* maxsize, nsegments */
	    BUS_SPACE_MAXSIZE_32BIT, 0,		/* maxsegsize, flags */
	    NULL, NULL,				/* lockfunc, lockarg */
	    &sc->dve_parent_tag);

	if (error) {
		device_printf(sc->dve_dev, "cannot create parent DMA tag\n");
		return (error);
	}

	return (0);
}

static void
dve_dmamap_cb(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct dve_dmamap_arg *ctx;

	if (error)
		return;

	ctx = (struct dve_dmamap_arg *)arg;
	ctx->dve_dma_busaddr = segs[0].ds_addr;
}

static void
dve_mdio_init(struct dve_softc *sc)
{
	uint8_t clkdiv = (DVE_MDIO_BUS_FREQ / DVE_MDIO_CLOCK_FREQ) - 1;

	dve_write_mdio_4(sc, DVE_MDIO_CONTROL, (clkdiv & 0xff) |
	    DVE_MDIO_CONTROL_ENABLE |
	    DVE_MDIO_CONTROL_FAULT |
	    DVE_MDIO_CONTROL_FAULT_ENABLE);

	while (dve_read_mdio_4(sc, DVE_MDIO_CONTROL) & DVE_MDIO_CONTROL_IDLE)
		DELAY(10);
}

static int
dve_init_txch(struct dve_txchannel *txch, int num)
{
	struct dve_softc *sc = txch->dve_tx_softc;
	struct dve_txdesc *txd;
	struct dve_dmamap_arg ctx;
	int i, error;

	ctx.dve_dma_busaddr = 0;
	txch->dve_tx_num = num;
	txch->dve_tx_prod = txch->dve_tx_cons = 0;

	/* TX descriptors tag */
	error = bus_dma_tag_create(
	    sc->dve_parent_tag,			/* parent tag */
	    4, 0,				/* alignment, boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filtarg */
	    DVE_TXDESC_SIZE, 1,			/* maxsize, nsegments */
	    DVE_TXDESC_SIZE, 0,			/* maxsegsize, flags */
	    NULL, NULL,				/* lockfunc, lockarg */
	    &txch->dve_tx_desc_tag);

	if (error) {
		device_printf(sc->dve_dev, 
		    "cannot create TX channel descriptors DMA tag\n");
		return (error);
	}

	/* TX buffers tag */
	error = bus_dma_tag_create(
	    sc->dve_parent_tag,			/* parent tag */
	    4, 0,				/* alignment, boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filtarg */
	    MCLBYTES * DVE_TXDESC_NUM,		/* maxsize */
	    DVE_TXDESC_NUM,			/* nsegments */
	    MCLBYTES, 0,			/* maxsegsize, flags */
	    NULL, NULL,				/* lockfunc, lockarg */
	    &txch->dve_tx_buf_tag);

	if (error) {
		device_printf(sc->dve_dev, 
		    "cannot create TX channel buffers DMA tag\n");
		return (error);
	}

	/* Allocate DMA memory for TX descriptors */
	error = bus_dmamem_alloc(txch->dve_tx_desc_tag, 
	    (void **)&txch->dve_tx_hwdesc, BUS_DMA_WAITOK | BUS_DMA_COHERENT |
	    BUS_DMA_ZERO, &txch->dve_tx_desc_map);

	error = bus_dmamap_load(txch->dve_tx_desc_tag, txch->dve_tx_desc_map,
	    txch->dve_tx_hwdesc, DVE_TXDESC_SIZE, dve_dmamap_cb, &ctx, 0);

	txch->dve_tx_desc_addr = ctx.dve_dma_busaddr;

	/* Initialize TX descriptors */
	for (i = 0; i < DVE_TXDESC_NUM; i++) {
		txd = &txch->dve_tx_desc[i];
		txd->dve_txdesc_mbuf = NULL;
		txd->dve_txdesc_dmamap = NULL;
		error = bus_dmamap_create(txch->dve_tx_buf_tag, 0,
		    &txd->dve_txdesc_dmamap);
		if (error) {
			device_printf(sc->dve_dev, "can't create TX DMA map\n");
			return (error);
		}
	}

	return (0);
}

static int
dve_init_rxch(struct dve_rxchannel *rxch, int num)
{
	struct dve_softc *sc = rxch->dve_rx_softc;
	struct dve_rxdesc *rxd;
	struct dve_dmamap_arg ctx;
	int error, i;

	ctx.dve_dma_busaddr = 0;
	rxch->dve_rx_active = 1;
	rxch->dve_rx_prod = rxch->dve_rx_cons = 0;

	/* RX descriptors tag */
	error = bus_dma_tag_create(
	    sc->dve_parent_tag,			/* parent tag */
	    4, 0,				/* alignment, boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filtarg */
	    DVE_RXDESC_SIZE, 1,			/* maxsize, nsegments */
	    DVE_RXDESC_SIZE, 0,			/* maxsegsize, flags */
	    NULL, NULL,				/* lockfunc, lockarg */
	    &rxch->dve_rx_desc_tag);

	/* RX buffers tag */
	error = bus_dma_tag_create(
	    sc->dve_parent_tag,			/* parent tag */
	    4, 0,				/* alignment, boundary */
	    BUS_SPACE_MAXADDR,			/* lowaddr */
	    BUS_SPACE_MAXADDR,			/* highaddr */
	    NULL, NULL,				/* filter, filtarg */
	    MCLBYTES * DVE_RXDESC_NUM,		/* maxsize */
	    DVE_RXDESC_NUM,			/* nsegments */
	    MCLBYTES, 0,			/* maxsegsize, flags */
	    NULL, NULL,				/* lockfunc, lockarg */
	    &rxch->dve_rx_buf_tag);

	if (error) {
		device_printf(sc->dve_dev, 
		    "cannot create RX channel buffers DMA tag\n");
		return (error);
	}

	/* Allocate DMA memory for RX descriptors */
	error = bus_dmamem_alloc(rxch->dve_rx_desc_tag, 
	    (void **)&rxch->dve_rx_hwdesc, BUS_DMA_WAITOK | BUS_DMA_COHERENT |
	    BUS_DMA_ZERO, &rxch->dve_rx_desc_map);

	error = bus_dmamap_load(rxch->dve_rx_desc_tag, rxch->dve_rx_desc_map,
	    rxch->dve_rx_hwdesc, DVE_RXDESC_SIZE, dve_dmamap_cb, &ctx, 0);

	rxch->dve_rx_desc_addr = ctx.dve_dma_busaddr;

	/* Initialize RX descriptors */
	for (i = 0; i < DVE_RXDESC_NUM; i++) {
		rxd = &rxch->dve_rx_desc[i];
		rxd->dve_rxdesc_mbuf = NULL;
		rxd->dve_rxdesc_dmamap = NULL;
		error = bus_dmamap_create(rxch->dve_rx_buf_tag, 0,
		    &rxd->dve_rxdesc_dmamap);
		if (error) {
			device_printf(sc->dve_dev, "can't create RX DMA map\n");
			return (error);
		}
	}

	return (0);
}

static int
dve_reset_txch(struct dve_txchannel *txch)
{
	struct dve_softc *sc = txch->dve_tx_softc;
	struct dve_txdesc *txd;
	struct dve_hwdesc *hwd;
	uint32_t reg;
	int i;

	txch->dve_tx_used = 0;
	txch->dve_tx_prod = txch->dve_tx_cons = 0;

	/* Initialize TX descriptors */
	for (i = 0; i < DVE_TXDESC_NUM; i++) {
		txd = &txch->dve_tx_desc[i];
		hwd = &txch->dve_tx_hwdesc[i];
		txd->dve_txdesc_mbuf = NULL;
		hwd->hw_flagslen = DVE_HWDESC_OWNER;
	}

	/* Enable TX interrupt for this channel */
	reg = dve_read_emac_4(sc, DVE_EMAC_TXINTMASKSET);
	reg |= (1 << txch->dve_tx_num);
	dve_write_emac_4(sc, DVE_EMAC_TXINTMASKSET, reg);

	/* Mark channel as active */
	txch->dve_tx_active = 1;

	return (0);
}

static int
dve_reset_rxch(struct dve_rxchannel *rxch)
{
	struct dve_softc *sc = rxch->dve_rx_softc;
	struct dve_rxdesc *rxd;
	uint32_t reg;
	int i;

	rxch->dve_rx_used = 0;
	rxch->dve_rx_prod = rxch->dve_rx_cons = 0;

	/* Initialize RX buffers */
	for (i = 0; i < DVE_RXDESC_NUM; i++) {
		rxd = &rxch->dve_rx_desc[i];
		rxd->dve_rxdesc_mbuf = NULL;
		dve_init_rxbuf(rxch, i);
	}

	/* Enable RX unicast and broadcast */
	reg = dve_read_emac_4(sc, DVE_EMAC_RXUNICASTSET);
	reg |= (1 << rxch->dve_rx_num);
	dve_write_emac_4(sc, DVE_EMAC_RXUNICASTSET, reg);

	/*
	 * Set this channel to be receiver of broadcast|multicast|promisc
	 * frames.  WARNING: this code assumes that there is no other RX
	 * channel active right now.
	 */
	reg = dve_read_emac_4(sc, DVE_EMAC_RXMBPENABLE);
	reg |= (rxch->dve_rx_num << DVE_EMAC_RXMBPENABLE_RXMULTCHSHIFT) |
	    (rxch->dve_rx_num << DVE_EMAC_RXMBPENABLE_RXBROADCHSHIFT) |
	    (rxch->dve_rx_num << DVE_EMAC_RXMBPENABLE_RXPROMCHSHIFT);
	dve_write_emac_4(sc, DVE_EMAC_RXMBPENABLE, reg);

	/* Enable RX interrupt for this channel */
	reg = dve_read_emac_4(sc, DVE_EMAC_RXINTMASKSET);
	reg |= (1 << rxch->dve_rx_num);
	dve_write_emac_4(sc, DVE_EMAC_RXINTMASKSET, reg);

#if 0
	/* Set RX buffer offset to 2 to avoid unaligned faults in TCP/IP stack */
	dve_write_emac_4(sc, DVE_EMAC_RXBUFFEROFFSET, 2);
#endif

	/* Mark channel as active */
	rxch->dve_rx_active = 1;

	/* Supply RX descriptor head pointer to start */
	dve_write_emac_4(sc, DVE_EMAC_RXnHDP(rxch->dve_rx_num),
	    rxch->dve_rx_desc_addr);

	return (0);
}

static int
dve_stop_txch(struct dve_txchannel *txch)
{
	struct dve_softc *sc = txch->dve_tx_softc;

	/* Init TX channel teardown and disable interrupts */
	dve_write_emac_4(sc, DVE_EMAC_TXINTMASKCLEAR, 1 << txch->dve_tx_num);
	dve_write_emac_4(sc, DVE_EMAC_TXTEARDOWN, txch->dve_tx_num);

	/* Wait for teardown to complete */
	while (dve_read_emac_4(sc, DVE_EMAC_TXnCP(txch->dve_tx_num)) != 0xfffffffc)
		DELAY(100);

	/* Acknowledge */
	dve_write_emac_4(sc, DVE_EMAC_TXnCP(txch->dve_tx_num), 0xfffffffc);

	/* Mark channel as inactive */
	txch->dve_tx_active = 0;

	return (0);
}

static int
dve_stop_rxch(struct dve_rxchannel *rxch)
{
	struct dve_softc *sc = rxch->dve_rx_softc;
	int i;

	/* Init RX channel teardown and disable interrupts */
	dve_write_emac_4(sc, DVE_EMAC_RXINTMASKCLEAR, 1 << rxch->dve_rx_num);
	dve_write_emac_4(sc, DVE_EMAC_RXTEARDOWN, rxch->dve_rx_num);

	/* Wait for teardown to complete */
	while (dve_read_emac_4(sc, DVE_EMAC_RXnCP(rxch->dve_rx_num)) != 0xfffffffc)
		DELAY(100);

	/* Acknowledge */
	dve_write_emac_4(sc, DVE_EMAC_RXnCP(rxch->dve_rx_num), 0xfffffffc);

	/* Disable RX */
	dve_write_emac_4(sc, DVE_EMAC_RXUNICASTCLEAR, 1 << rxch->dve_rx_num);

	/* Free RX buffers */
	for (i = 0; i < DVE_TXDESC_NUM; i++)
		dve_discard_rxbuf(rxch, i);

	/* Mark channel as inactive */
	rxch->dve_rx_active = 0;

	return (0);
}

static int
dve_init_rxbuf(struct dve_rxchannel *rxch, int n)
{
	struct dve_rxdesc *rxd;
	struct dve_hwdesc *hwd;
	struct mbuf *m;
	bus_dma_segment_t segs[1];
	int nsegs;

	rxd = &rxch->dve_rx_desc[n];
	hwd = &rxch->dve_rx_hwdesc[n];
	m = m_getcl(M_DONTWAIT, MT_DATA, M_PKTHDR);

	if (!m) {
		device_printf(rxch->dve_rx_softc->dve_dev, 
		    "WARNING: mbufs exhausted!\n");
		return (ENOBUFS);
	}

	m->m_len = m->m_pkthdr.len = MCLBYTES;

	bus_dmamap_unload(rxch->dve_rx_buf_tag, rxd->dve_rxdesc_dmamap);

	if (bus_dmamap_load_mbuf_sg(rxch->dve_rx_buf_tag, 
	    rxd->dve_rxdesc_dmamap, m, segs, &nsegs, 0)) {
		m_freem(m);
		return (ENOBUFS);
	}

	bus_dmamap_sync(rxch->dve_rx_buf_tag, rxd->dve_rxdesc_dmamap, 
	    BUS_DMASYNC_PREREAD);

	rxd->dve_rxdesc_mbuf = m;
	hwd->hw_next = 0;
	hwd->hw_buffer = segs[0].ds_addr + 2;
	hwd->hw_offlen = (segs[0].ds_len & 0xffff);
	hwd->hw_flagslen = DVE_HWDESC_OWNER;

	hwd = &rxch->dve_rx_hwdesc[DVE_PREV(n, DVE_RXDESC_NUM)];
	hwd->hw_next = rxch->dve_rx_desc_addr + DVE_RXDESC_OFFSET(n);
	hwd->hw_flagslen &= ~DVE_HWDESC_EOQ;

	return (0);
}

static void
dve_discard_rxbuf(struct dve_rxchannel *rxch, int n)
{
	struct dve_rxdesc *rxd;
	struct dve_hwdesc *hwd;

	rxd = &rxch->dve_rx_desc[n];
	hwd = &rxch->dve_rx_hwdesc[n];

	bus_dmamap_unload(rxch->dve_rx_buf_tag, rxd->dve_rxdesc_dmamap);

	hwd->hw_flagslen = 0;

	if (rxd->dve_rxdesc_mbuf) {
		m_freem(rxd->dve_rxdesc_mbuf); 
		rxd->dve_rxdesc_mbuf = NULL;
	}
}

static int
dve_ifmedia_upd(struct ifnet *ifp)
{
	return (0);
}

static void
dve_ifmedia_sts(struct ifnet *ifp, struct ifmediareq *ifmr)
{
	struct dve_softc *sc = ifp->if_softc;
	struct mii_data *mii = device_get_softc(sc->dve_miibus);

	dve_lock(sc);
	mii_pollstat(mii);
	ifmr->ifm_active = mii->mii_media_active;
	ifmr->ifm_status = mii->mii_media_status;
	dve_unlock(sc);
}

static void
dve_stats_update(struct dve_softc *sc)
{
	struct ifnet *ifp = sc->dve_ifp;
	struct dve_hwstats stats;
	int i;

	/* Read stats from device to struct dve_hwstats */
	bus_space_read_region_4(sc->dve_bst, sc->dve_bsh, DVE_EMAC_STATSBASE,
	    (uint32_t *)&stats, sizeof(struct dve_hwstats) / 4);

	/* Update ifnet counters */
	ifp->if_opackets += stats.tx_good_frames;
	ifp->if_collisions += stats.tx_collisions;
	ifp->if_oerrors += stats.tx_deferred +
	    stats.tx_single_collision +
	    stats.tx_multiple_collision +
	    stats.tx_excessive_collision +
	    stats.tx_late_collision +
	    stats.tx_underrun_errors +
	    stats.tx_carrier_errors;

	ifp->if_ipackets = stats.rx_good_frames;
	ifp->if_ierrors = stats.rx_crc_errors +
	    stats.rx_align_errors +
	    stats.rx_oversized_errors +
	    stats.rx_jabber_errors +
	    stats.rx_undersized_errors +
	    stats.rx_frame_fragment_errors;

	/* Clear stats */
	for (i = 0; i < sizeof(struct dve_hwstats); i+=4)
		dve_write_emac_4(sc, DVE_EMAC_STATSBASE + i, 0);
}

static device_method_t dve_methods[] = {
	/* Device interface */
	DEVMETHOD(device_probe,		dve_probe),
	DEVMETHOD(device_attach,	dve_attach),
	DEVMETHOD(device_detach,	dve_detach),

	/* Bus interface */
	DEVMETHOD(bus_print_child,	bus_generic_print_child),

	/* MII interface */
	DEVMETHOD(miibus_readreg,	dve_miibus_readreg),
	DEVMETHOD(miibus_writereg,	dve_miibus_writereg),
	DEVMETHOD(miibus_statchg,	dve_miibus_statchg),
	{ 0, 0 }
};

static driver_t dve_driver = {
	"dve",
	dve_methods,
	sizeof(struct dve_softc)
};

static devclass_t dve_devclass;

DRIVER_MODULE(dve, obio, dve_driver, dve_devclass, 0, 0);
DRIVER_MODULE(miibus, dve, miibus_driver, miibus_devclass, 0, 0);
MODULE_DEPEND(dve, obio, 1, 1, 1);
MODULE_DEPEND(dve, miibus, 1, 1, 1);
MODULE_DEPEND(dve, ether, 1, 1, 1);
