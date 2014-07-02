/**
 * @file io.c
 *
 * @ingroup tms570
 *
 * @brief Input/output module methods.
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


#include <rtems/status-checks.h>
#include <bsp.h>
#include <bsp/io.h>
#include <bsp/start.h>
#include <bsp/system-clocks.h>
/**
 * @brief Modules table according to the TMS570
 */

/*static const tms570_module_entry tms570_module_table[] = {
  TMS570_MODULE_ENTRY( TMS570_MODULE_SCPI0, 0, 0, 0 ),  
};
*/
inline void tms570_pin_select(
  const uint32_t             pin,
  const tms570_pin_function function
)
{
}

/**
 * @brief Checks if the module has power.
 *
 * @param has_power Power.
 * @param index Index to shift.
 * @param turn_on Turn on/off the power.
 * @param level Interrupts value.
 */
static rtems_status_code check_power(
  const bool            has_power,
  const unsigned        index,
  const bool            turn_on,
  rtems_interrupt_level level
)
{
  rtems_status_code status_code;
  return status_code;
}

/**
 * @brief Sets the correct value according to the specific peripheral clock.
 *
 * @param  is_first_pclksel Represents the first pclksel.
 * @param  clock The clock to set for this module.
 * @param  clock_shift Value to clock shift.
 */
static inline void set_pclksel_value(
  const uint32_t             pclksel,
  const tms570_module_clock clock,
  const unsigned             clock_shift
)
{
  
}

/**
 * @brief Checks if the module has clock.
 *
 * @param has_clock Clock.
 * @param index Index to shift.
 * @param clock The clock to set for this module.
 * @param level Interrupts value.
 */
static rtems_status_code check_clock(
  const bool                 has_clock,
  const unsigned             index,
  const tms570_module_clock clock,
  rtems_interrupt_level      level
)
{
  rtems_status_code status_code;
  return status_code;
}

/**
 * @brief Checks the usb module.
 *
 * @return RTEMS_SUCCESFUL if the usb module is correct.
 */
static rtems_status_code check_usb_module( void )
{
  rtems_status_code status_code;
  return status_code;
}

/**
 * @brief Enables the current module.
 *
 * @param  module  Current module to enable/disable.
 * @param  clock The clock to set for this module.
 * @param enable TRUE if the module is enable.
 * @return RTEMS_SUCCESSFULL if the module was enabled successfully.
 */
static rtems_status_code enable_disable_module(
  const tms570_module       module,
  const tms570_module_clock clock,
  const bool                 enable
)
{
  rtems_status_code     status_code;
  return status_code;
}

/**
 * @brief Enables the module power and clock.
 *
 * @param  module Device to enable.
 * @param  clock  The clock to set for this module.
 * @param  enable Enable or disable the module.
 * @return RTEMS_SUCCESSFULL if the module was enabled succesfully.
 */
static rtems_status_code tms570_module_do_enable(
  const tms570_module module,
  tms570_module_clock clock,
  const bool           enable
)
{
  rtems_status_code status_code;
  return status_code;
}

inline rtems_status_code tms570_module_enable(
  const tms570_module module,
  tms570_module_clock clock
)
{
  return tms570_module_do_enable( module, clock, true );
}

inline rtems_status_code tms570_module_disable( const tms570_module module )
{
  return tms570_module_do_enable( module,
    TMS570_MODULE_PCLK_DEFAULT,
    false );
}

bool tms570_module_is_enabled( const tms570_module module )
{
  
  return 0;
}
