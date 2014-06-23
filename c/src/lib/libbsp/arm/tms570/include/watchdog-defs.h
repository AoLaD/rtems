/**
 * @file watchdog-defs.h
 *
 * @ingroup tms570
 *
 * @brief API definitions of the Watchdog driver for the tms570 bsp in RTEMS.
 */

/*
 * Copyright (c) 2014 Taller Technologies.
 *
 * @author  Boretto Martin    (martin.boretto@tallertechnologies.com)
 * @author  Diaz Marcos (marcos.diaz@tallertechnologies.com)
 * @author  Lenarduzzi Federico  (federico.lenarduzzi@tallertechnologies.com)
 * @author  Daniel Chicco  (daniel.chicco@tallertechnologies.com)
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#ifndef LIBBSP_ARM_TMS570_WATCHDOG_DEFS_H
#define LIBBSP_ARM_TMS570_WATCHDOG_DEFS_H

#include <rtems/score/cpu.h>
#include <bsp.h>
#include <bspopts.h>
#include <bsp/utility.h>
#include <bsp/irq.h>
#include <bsp/common-types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TMS570_WDMOD_BASE 0x40000000U
#define TMS570_WDFEED_CON 0XAAU
#define TMS570_WDFEED_CFG 0X55U
#define TMS570_WD_PRESCALER_DIVISOR 4000000U
#define TMS570_WWDT_MOD_WDEN BSP_BIT32( 0 )
#define TMS570_WWDT_MOD_WDRESET BSP_BIT32( 1 )
#define TMS570_WWDT_MOD_WDTOF BSP_BIT32( 2 )
#define TMS570_WWDT_MOD_WDINT BSP_BIT32( 3 )
#define TMS570_WWDT_CLKSEL_WDSEL_IRC 0x0U
#define TMS570_WWDT_CLKSEL_WDSEL_PCLK 0x1U
#define TMS570_WWDT_CLKSEL_WDSEL_RTC 0x2U
#define TMS570_WD_INTERRUPT_VECTOR_NUMBER 0U
#define TMS570_WDMOD ( *(volatile uint32_t *) ( TMS570_WDMOD_BASE + 0x00U ) )
#define TMS570_WDTC ( *(volatile uint32_t *) ( TMS570_WDMOD_BASE + 0x04U ) )
#define TMS570_WDFEED ( *(volatile uint32_t *) ( TMS570_WDMOD_BASE + \
                                                  0x08U ) )
#define TMS570_WDTV ( *(volatile uint32_t *) ( TMS570_WDMOD_BASE + 0x0CU ) )
#define TMS570_WDCLKSEL ( *(volatile uint32_t *) ( TMS570_WDMOD_BASE + \
                                                    0x10U ) )

/**
 * @brief A function that attends an interruption for a watchdog.
 */
typedef rtems_interrupt_handler tms570_wd_isr_funct;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* LIBBSP_ARM_TMS570_WATCHDOG_DEFS_H */
