/**
 * @file bsp.h
 *
 * @ingroup tms570
 *
 * @brief Global BSP definitions.
 */
/*
 * Copyright (c) 2014 Premysl Houdek <kom541000@gmail.com>
 *
 * Google Summer of Code 2014 at
 * Czech Technical University in Prague
 * Zikova 1903/4
 * 166 36 Praha 6
 * Czech Republic
 *
 * Based on LPC24xx and LPC1768 BSP
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef LIBBSP_ARM_TMS570_BSP_H
#define LIBBSP_ARM_TMS570_BSP_H

#include <bspopts.h>

#define TMS570_PCLK ( TMS570_CCLK / TMS570_PCLKDIV )
#define TMS570_MPU_REGION_COUNT 8u

#define BSP_FEATURE_IRQ_EXTENSION

#ifndef ASM

#include <rtems.h>
#include <rtems/console.h>
#include <rtems/clockdrv.h>
#include <bsp/default-initial-extension.h>

#define BSP_OSCILATOR_CLOCK 8000000
#define BSP_PLL_OUT_CLOCK 160000000

/** Define operation count for Tests */
#define OPERATION_COUNT 4

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct rtems_bsdnet_ifconfig;

/**
 * @defgroup tms570 TMS570 Support
 *
 * @ingroup bsp_arm
 *
 * @brief TMS570 support package.
 *
 * @{
 */

/**
 * @brief Optimized idle task.
 *
 * This idle task sets the power mode to idle.  This causes the processor
 * clock to be stopped, while on-chip peripherals remain active.
 * Any enabled interrupt from a peripheral or an external interrupt source
 *  will cause the processor to resume execution.
 *
 * To enable the idle task use the following in the system configuration:
 *
 * @code
 * #include <bsp.h>
 *
 * #define CONFIGURE_INIT
 *
 * #define CONFIGURE_IDLE_TASK_BODY bsp_idle_thread
 *
 * #include <confdefs.h>
 * @endcode
 */
void*bsp_idle_thread( uintptr_t ignored );

#define BSP_CONSOLE_UART_BASE 0x4000C000U

/**
 * @brief Restarts the bsp with "addr" address
 * @param addr Address used to restart the bsp
 */
void bsp_restart( const void *addr );

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ASM */

#endif /* LIBBSP_ARM_TMS570_BSP_H */
