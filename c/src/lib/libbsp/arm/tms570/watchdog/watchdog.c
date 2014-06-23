/**
 * @file watchdog.c
 *
 * @ingroup tms570
 *
 * @brief Watchdog controller for the mbed tms570 family boards.
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

#include <assert.h>
#include <rtems/status-checks.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/watchdog.h>
#include <bsp/io.h>

inline bool tms570_been_reset_by_watchdog( void )
{
  return ( ( TMS570_WDMOD & TMS570_WWDT_MOD_WDTOF ) ==
           TMS570_WWDT_MOD_WDTOF );
}

inline void tms570_watchdog_reset( void )
{
  TMS570_WDFEED = TMS570_WDFEED_CON;
  TMS570_WDFEED = TMS570_WDFEED_CFG;
}

/**
 * @brief Enables the watchdog module, sets wd clock and wd timer.
 *
 * @param  tcount Timer's out value.
 * @return RTEMS_SUCCESSFUL if the configuration was done successfully.
 */
static inline rtems_status_code enable_module_and_set_clocksel(
  const tms570_microseconds tcount )
{
  rtems_status_code status_code;

  /* Sets clock. */
  TMS570_WDCLKSEL = TMS570_WWDT_CLKSEL_WDSEL_PCLK;

  /* Enables the watchdog module.  */
  status_code = tms570_module_enable( TMS570_MODULE_WD,
    TMS570_MODULE_PCLK_DEFAULT );
  RTEMS_CHECK_SC( status_code, "Enabling the watchdog module." );

  /* Set the watchdog timer constant value. */
  TMS570_WDTC = ( TMS570_CCLK / TMS570_WD_PRESCALER_DIVISOR ) * tcount;

  return status_code;
}

rtems_status_code tms570_watchdog_config( const tms570_microseconds tcount )
{
  rtems_status_code status_code = enable_module_and_set_clocksel( tcount );

  /* Setup the Watchdog timer operating mode in WDMOD register. */
  TMS570_WDMOD = TMS570_WWDT_MOD_WDEN | TMS570_WWDT_MOD_WDRESET;

  /* Enable the Watchdog by writing 0xAA followed by 0x55 to the
      WDFEED register. */
  tms570_watchdog_reset();

  return status_code;
}

rtems_status_code tms570_watchdog_config_with_interrupt(
  const tms570_wd_isr_funct interrupt,
  const tms570_microseconds tcount
)
{
  rtems_status_code status_code = enable_module_and_set_clocksel( tcount );

  /* Setup the Watchdog timer operating mode in WDMOD register. */
  TMS570_WDMOD = TMS570_WWDT_MOD_WDEN | TMS570_WWDT_MOD_WDINT;

  status_code = rtems_interrupt_handler_install(
    TMS570_WD_INTERRUPT_VECTOR_NUMBER,
    "watchdog_interrupt",
    RTEMS_INTERRUPT_UNIQUE,
    interrupt,
    NULL );

  /* Enable the Watchdog by writing 0xAA followed by 0x55 to the
      WDFEED register. */
  tms570_watchdog_reset();

  return status_code;
}