##
#
# @file makefile.am
#
# @brief Makefile of LibBSP for the TMS570 boards.
#

ACLOCAL_AMFLAGS = -I ../../../../aclocal

include $(top_srcdir)/../../../../automake/compile.am

include_bspdir = $(includedir)/bsp

include_bsp_ti_herculesdir = $(includedir)/bsp/ti_herc

dist_project_lib_DATA = bsp_specs

# ----------------------------
# ------  Headers
# ----------------------------

include_HEADERS = include/bsp.h

nodist_include_HEADERS = ../../shared/include/coverhd.h
nodist_include_HEADERS += include/bspopts.h

nodist_include_bsp_HEADERS = ../../shared/include/bootcard.h

include_bsp_HEADERS =
include_bsp_HEADERS += ../../shared/include/utility.h
include_bsp_HEADERS += ../../shared/include/irq-generic.h
include_bsp_HEADERS += ../../shared/include/irq-info.h
include_bsp_HEADERS += ../../shared/include/stackalloc.h
include_bsp_HEADERS += ../../shared/include/uart-output-char.h
include_bsp_HEADERS += ../shared/include/start.h
include_bsp_HEADERS += include/tms570.h
include_bsp_HEADERS += include/tms570-sci.h
include_bsp_HEADERS += include/irq.h
include_bsp_HEADERS += include/tms570-rti.h
include_bsp_HEADERS += include/tms570-vim.h
include_bsp_HEADERS += include/tms570-pom.h
include_bsp_HEADERS += include/tms570-sci-driver.h
include_bsp_HEADERS += include/system-clocks.h
include_bsp_HEADERS += include/tms570-pinmux.h

include_bsp_ti_hercules_HEADERS = include/ti_herc/reg_adc.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_ccmsr.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_crc.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_dcan.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_dcc.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_dma.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_dmm.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_efuse.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_emacc.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_emacm.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_emif.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_esm.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_flash.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_flex_ray.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_gio.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_htu.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_i2c.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_iomm.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_lin.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_mdio.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_n2het.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_pbist.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_pll.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_pmm.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_rti.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_rtp.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_sci.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_tcr.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_tcram.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_vim.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_pom.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_spi.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_stc.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_sys.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_sys2.h
include_bsp_ti_hercules_HEADERS += include/ti_herc/reg_pcr.h

include_HEADERS += ../../shared/include/tm27.h

# ----------------------------
# ------  Data
# ----------------------------

noinst_LIBRARIES = libbspstart.a

libbspstart_a_SOURCES = ../shared/start/start.S

project_lib_DATA = start.$(OBJEXT)
project_lib_DATA += startup/linkcmds

EXTRA_DIST =
EXTRA_DIST += startup/linkcmds.tms570ls3137_hdk
EXTRA_DIST += startup/linkcmds.tms570ls3137_hdk_with_loader
EXTRA_DIST += startup/linkcmds.tms570ls3137_hdk_sdram
EXTRA_DIST += startup/linkcmds.tms570ls3137_hdk_intram

# ----------------------------
# ------  LibBSP
# ----------------------------

noinst_LIBRARIES += libbsp.a

libbsp_a_SOURCES =
libbsp_a_CPPFLAGS =
libbsp_a_LIBADD =

# Shared
libbsp_a_SOURCES += ../../shared/bootcard.c
libbsp_a_SOURCES += ../../shared/bspclean.c
libbsp_a_SOURCES += ../../shared/bspgetworkarea.c
libbsp_a_SOURCES += ../../shared/bsplibc.c
libbsp_a_SOURCES += ../../shared/bsppost.c
libbsp_a_SOURCES += ../../shared/bsppredriverhook.c
libbsp_a_SOURCES += ../../shared/gnatinstallhandler.c
libbsp_a_SOURCES += ../../shared/sbrk.c
libbsp_a_SOURCES += ../../shared/src/stackalloc.c
libbsp_a_SOURCES += ../../shared/cpucounterdiff.c

# Startup
libbsp_a_SOURCES += ../shared/startup/bsp-start-memcpy.S
libbsp_a_SOURCES += ../shared/startup/bsp-start-init-registers.S
libbsp_a_SOURCES += ../../shared/bsppretaskinghook.c
libbsp_a_SOURCES += startup/bspreset.c
libbsp_a_SOURCES += startup/bspstart.c

# POM
libbsp_a_SOURCES += pom/tms570-pom.c

# IRQ
libbsp_a_SOURCES += ../../shared/src/irq-default-handler.c
libbsp_a_SOURCES += ../../shared/src/irq-generic.c
libbsp_a_SOURCES += ../../shared/src/irq-info.c
libbsp_a_SOURCES += ../../shared/src/irq-legacy.c
libbsp_a_SOURCES += ../../shared/src/irq-server.c
libbsp_a_SOURCES += ../../shared/src/irq-shell.c
libbsp_a_SOURCES += irq/irq.c

# Console
libbsp_a_SOURCES += ../../shared/console-termios.c
libbsp_a_SOURCES += console/printk-support.c
libbsp_a_SOURCES += console/tms570-sci.c

# Clock
libbsp_a_SOURCES += ../../shared/clockdrv_shell.h
libbsp_a_SOURCES += clock/clock.c
libbsp_a_SOURCES += clock/benchmark_timer.c

# RTC

# GPIO
libbsp_a_SOURCES += pinmux/pinmux.c
# Timer

# Benchmark Timer

# Misc
libbsp_a_SOURCES += misc/cpucounterread.c

# Watchdog

# Cache
libbsp_a_SOURCES += ../../../libcpu/shared/src/cache_manager.c
libbsp_a_SOURCES += ../../../libcpu/arm/shared/include/cache_.h
libbsp_a_CPPFLAGS += -I$(srcdir)/../../../libcpu/arm/shared/include

if TMS570_USE_HALCOGEN_STARTUP
# Use HalCoGen generated files to setup board
include_HEADERS += halcogen/include/adc.h halcogen/include/can.h
include_HEADERS += halcogen/include/crc.h halcogen/include/dcc.h halcogen/include/Device_header.h
include_HEADERS += halcogen/include/Device_TMS570LS31.h halcogen/include/Device_types.h
include_HEADERS += halcogen/include/dmm.h halcogen/include/emac.h halcogen/include/emif.h
include_HEADERS += halcogen/include/esm.h halcogen/include/fee_interface.h
include_HEADERS += halcogen/include/gio.h halcogen/include/hal_stdtypes.h
include_HEADERS += halcogen/include/het.h halcogen/include/htu.h halcogen/include/hw_emac_ctrl.h
include_HEADERS += halcogen/include/hw_emac.h halcogen/include/hw_mdio.h
include_HEADERS += halcogen/include/hw_reg_access.h halcogen/include/i2c.h halcogen/include/lin.h
include_HEADERS += halcogen/include/mdio.h halcogen/include/MemMap.h
include_HEADERS += halcogen/include/mibspi.h halcogen/include/phy_dp83640.h
include_HEADERS += halcogen/include/pinmux.h halcogen/include/pom.h

include_HEADERS += halcogen/include/reg_adc.h halcogen/include/reg_can.h
include_HEADERS += halcogen/include/reg_crc.h halcogen/include/reg_dcc.h
include_HEADERS += halcogen/include/reg_dma.h halcogen/include/reg_dmm.h
include_HEADERS += halcogen/include/reg_efc.h halcogen/include/reg_emif.h
include_HEADERS += halcogen/include/reg_esm.h halcogen/include/reg_flash.h
include_HEADERS += halcogen/include/reg_gio.h halcogen/include/reg_het.h
include_HEADERS += halcogen/include/reg_htu.h halcogen/include/reg_i2c.h
include_HEADERS += halcogen/include/reg_lin.h halcogen/include/reg_mibspi.h
include_HEADERS += halcogen/include/reg_pbist.h halcogen/include/reg_pcr.h
include_HEADERS += halcogen/include/reg_pinmux.h halcogen/include/reg_pmm.h
include_HEADERS += halcogen/include/reg_pom.h halcogen/include/reg_rti.h
include_HEADERS += halcogen/include/reg_rtp.h halcogen/include/reg_sci.h
include_HEADERS += halcogen/include/reg_spi.h halcogen/include/reg_stc.h
include_HEADERS += halcogen/include/reg_system.h halcogen/include/reg_tcram.h
include_HEADERS += halcogen/include/reg_vim.h

include_HEADERS += halcogen/include/rti.h halcogen/include/rtp.h
include_HEADERS += halcogen/include/sci.h halcogen/include/spi.h halcogen/include/std_nhet.h
include_HEADERS += halcogen/include/sys_common.h halcogen/include/sys_core.h
include_HEADERS += halcogen/include/sys_dma.h halcogen/include/sys_mpu.h
include_HEADERS += halcogen/include/sys_pcr.h halcogen/include/sys_pmm.h
include_HEADERS += halcogen/include/sys_pmu.h halcogen/include/sys_selftest.h
include_HEADERS += halcogen/include/system.h halcogen/include/sys_vim.h
include_HEADERS += halcogen/include/ti_fee_Cfg.h halcogen/include/ti_fee.h
include_HEADERS += halcogen/include/ti_fee_types.h

libbsp_a_SOURCES += halcogen/source/sys_core.S
libbsp_a_SOURCES += halcogen/source/sys_mpu.S
libbsp_a_SOURCES += halcogen/source/sys_pmu.S
libbsp_a_SOURCES += halcogen/source/emif.c
libbsp_a_SOURCES += halcogen/source/esm.c
libbsp_a_SOURCES += halcogen/source/notification.c
libbsp_a_SOURCES += halcogen/source/pinmux-halcogen.c
libbsp_a_SOURCES += halcogen/source/sci.c
libbsp_a_SOURCES += halcogen/source/sys_dma.c
libbsp_a_SOURCES += halcogen/source/sys_pcr.c
libbsp_a_SOURCES += halcogen/source/sys_phantom.c
libbsp_a_SOURCES += halcogen/source/sys_pmm.c
libbsp_a_SOURCES += halcogen/source/sys_selftest.c
libbsp_a_SOURCES += halcogen/source/sys_startup.c
libbsp_a_SOURCES += halcogen/source/system.c
libbsp_a_SOURCES += halcogen/source/sys_vim.c

# Start hooks
libbsp_a_SOURCES += halcogen/bspstarthooks-halcogen.c
else
# Start hooks
libbsp_a_SOURCES += startup/bspstarthooks.c
endif

# ----------------------------
# ------  Special Rules
# ----------------------------

DISTCLEANFILES = include/bspopts.h

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../../automake/local.am
