/**
 * @file watchdog.c
 *
 * @ingroup tms570
 *
 * @brief Watchdog controller for the mbed tms570 family boards.
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

#include <assert.h>
#include <rtems/status-checks.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/watchdog.h>
#include <bsp/io.h>

inline bool tms570_been_reset_by_watchdog( void )
{
	return 0; 
}

inline void tms570_watchdog_reset( void )
{
  
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

  return status_code;
}

rtems_status_code tms570_watchdog_config( const tms570_microseconds tcount )
{
  rtems_status_code status_code;

  return status_code;
}

rtems_status_code tms570_watchdog_config_with_interrupt(
  const tms570_wd_isr_funct interrupt,
  const tms570_microseconds tcount
)
{
  rtems_status_code status_code;

  return status_code;
}
