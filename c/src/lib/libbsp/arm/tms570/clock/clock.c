/**
 * @file clock.c
 *
 * @ingroup tms570
 *
 * @brief clock functions definitions.
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
 * by embedded brains GmbH and others
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#include <stdlib.h>

#include <rtems.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/tms570-rti.h>
#include <rtems/counter.h>
#include <rtems/timecounter.h>

static struct timecounter tms570_rti_tc;

static uint32_t tms570_rti_get_timecount(struct timecounter *tc)
{
  return TMS570_RTI.CNT[0].FRCx;
}

/**
 *  @brief Initialize the HW peripheral for clock driver
 *
 *  Clock driver is implemented by RTI module
 *
 * @retval Void
 */
static void tms570_clock_driver_support_initialize_hardware( void )
{

  uint32_t microsec_per_tick = rtems_configuration_get_microseconds_per_tick();
  uint32_t tc_frequency = 1000000;
  uint32_t tc_prescaller;

  rtems_counter_initialize_converter(BSP_PLL_OUT_CLOCK);

  tc_prescaller = (BSP_PLL_OUT_CLOCK + tc_frequency) / (tc_frequency * 2);
  tc_frequency = (BSP_PLL_OUT_CLOCK + tc_prescaller) / (tc_prescaller * 2);

  /* Hardware specific initialize */
  TMS570_RTI.GCTRL = 0;
  TMS570_RTI.CNT[0].CPUCx = tc_prescaller; /* prescaler */
  TMS570_RTI.TBCTRL = 2;
  TMS570_RTI.CAPCTRL = 0;
  TMS570_RTI.COMPCTRL = 0;
  /* set counter to zero */
  TMS570_RTI.CNT[0].UCx = 0;
  TMS570_RTI.CNT[0].FRCx = 0;
  /* clear interrupts*/
  TMS570_RTI.CLEARINTENA = 0x00070f0f;
  TMS570_RTI.INTFLAG = 0x0007000f;
  /* set timer */
  TMS570_RTI.CMP[0].COMPx = TMS570_RTI.CNT[0].FRCx + microsec_per_tick;
  TMS570_RTI.COMP0CLR = TMS570_RTI.CMP[0].COMPx + microsec_per_tick / 2;
  TMS570_RTI.CMP[0].UDCPx = microsec_per_tick;
  /* enable interupt */
  TMS570_RTI.SETINTENA = 0x1;
  /* enable timer */
  TMS570_RTI.GCTRL = 1;
  /* set timecounter */
  tms570_rti_tc.tc_get_timecount = tms570_rti_get_timecount;
  tms570_rti_tc.tc_counter_mask = 0xffffffff;
  tms570_rti_tc.tc_frequency = tc_frequency;
  tms570_rti_tc.tc_quality = RTEMS_TIMECOUNTER_QUALITY_CLOCK_DRIVER;
  rtems_timecounter_install(&tms570_rti_tc);
}

/**
 * @brief Clears interrupt source
 *
 * @retval Void
 */
static void tms570_clock_driver_support_at_tick( void )
{
  TMS570_RTI.INTFLAG = 0x00000001;
}

/**
 * @brief registers RTI interrupt handler
 *
 * @param[in] Clock_isr new ISR handler
 * @param[in] Old_ticker old ISR handler (unused and type broken)
 *
 * @retval Void
 */
static void tms570_clock_driver_support_install_isr(
  rtems_isr_entry Clock_isr
)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;

  sc = rtems_interrupt_handler_install(
    TMS570_IRQ_TIMER_0,
    "Clock",
    RTEMS_INTERRUPT_UNIQUE,
    (rtems_interrupt_handler) Clock_isr,
    NULL
  );
  if ( sc != RTEMS_SUCCESSFUL ) {
    rtems_fatal_error_occurred(0xdeadbeef);
  }
}

/**
 * @brief disables RTI interrupt
 *
 * Called when closing clock driver
 *
 * @retval Void
 */
static void tms570_clock_driver_support_shutdown_hardware( void )
{
  /* turn off the timer interrupts */
  TMS570_RTI.CLEARINTENA = 0x20000;
}

#define Clock_driver_support_initialize_hardware \
                        tms570_clock_driver_support_initialize_hardware
#define Clock_driver_support_at_tick \
                        tms570_clock_driver_support_at_tick
#define Clock_driver_support_initialize_hardware \
                        tms570_clock_driver_support_initialize_hardware
#define Clock_driver_support_shutdown_hardware \
                        tms570_clock_driver_support_shutdown_hardware

#define Clock_driver_support_install_isr(Clock_isr, Old_ticker ) \
              tms570_clock_driver_support_install_isr( Clock_isr )

void Clock_isr(void *arg); /* to supress warning */

#include "../../../shared/clockdrv_shell.h"
