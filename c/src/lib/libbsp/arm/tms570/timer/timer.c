/**
 * @file timer.c
 *
 * @ingroup tms570
 *
 * @brief Timer controller for the mbed tms570ls3137 board.
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


#include <stdio.h>
#include <rtems/status-checks.h>
#include <bsp.h>
#include <bsp/irq.h>
#include <bsp/io.h>
#include <bsp/timer.h>
/*
const tms570_timer timers[ TMS570_TIMER_COUNT ] =
{
  {
    .device = (tms570_timer_device *) TMS570_TMR2_BASE_ADDR,
    .module = TMS570_MODULE_TIMER_2,
    .pinselcap = TMS570_TIMER2_CAPTURE_PORTS,
    .pinselemat = TMS570_TIMER2_EMATCH_PORTS,
  },
  {
    .device = (tms570_timer_device *) TMS570_TMR3_BASE_ADDR,
    .module = TMS570_MODULE_TIMER_3,
    .pinselcap = TMS570_TIMER3_CAPTURE_PORTS,
    .pinselemat = TMS570_TIMER3_EMATCH_PORTS,
  }
};*/
/*
tms570_timer_functions functions_vector[ TMS570_TIMER_COUNT ] =
{
  {
    .funct_vector = NULL
  },
  {
    .funct_vector = NULL
  },
  {
    .funct_vector = NULL
  },
  {
    .funct_vector = NULL
  }
};
*/
/**
 * @brief Calls the corresponding interrupt function and pass the timer
 *        as parameter.
 *
 * @param  timer The specific device.
 * @param  interruptnumber Interrupt number.
 */
static inline void tms570_call_desired_isr(
  const tms570_timer_number number,
  const tms570_isr_function interruptfunction
)
{
  
}

/**
 * @brief Gets true if the selected interrupt is pending
 *
 * @param number: the number of the timer.
 * @param interrupt: the interrupt we are checking for.
 * @return TRUE if the interrupt is pending.
 */
static inline bool tms570_timer_interrupt_is_pending(
  const tms570_timer_number tnumber,
  const tms570_isr_function function
)
{
  return 0;
}

/**
 * @brief Resets interrupt status for the selected interrupt
 *
 * @param tnumber: the number of the timer
 * @param interrupt: the interrupt we are resetting
 */
static inline void tms570_timer_reset_interrupt(
  const tms570_timer_number tnumber,
  const tms570_isr_function function
)
{

}

inline rtems_status_code tms570_timer_reset(
  const tms570_timer_number tnumber )
{
  rtems_status_code status_code;
  return status_code;
}

inline rtems_status_code tms570_timer_set_mode(
  const tms570_timer_number tnumber,
  const tms570_timer_mode   mode
)
{
  rtems_status_code status_code;
  return status_code;
}

inline rtems_status_code tms570_timer_start(
  const tms570_timer_number tnumber )
{
  rtems_status_code status_code;
  return status_code;
}

inline rtems_status_code tms570_timer_is_started(
  const tms570_timer_number tnumber,
  bool                      *is_started
)
{
  rtems_status_code status_code;
  return status_code;
}

inline rtems_status_code tms570_timer_set_resolution(
  const tms570_timer_number tnumber,
  const tms570_microseconds resolution
)
{
  rtems_status_code status_code;
  return status_code;
}

rtems_status_code tms570_timer_match_config(
  const tms570_timer_number   tnumber,
  const tms570_match_port     match_port,
  const tms570_match_function function,
  const uint32_t               match_value
)
{
  rtems_status_code status_code;
  return status_code;
}

inline rtems_status_code tms570_timer_capture_config(
  const tms570_timer_number     tnumber,
  const tms570_capture_port     capture_port,
  const tms570_capture_function function
)
{
  rtems_status_code status_code;
  return status_code;
}

inline rtems_status_code tms570_timer_external_match_config(
  const tms570_timer_number       number,
  const tms570_match_port         match_port,
  const tms570_ext_match_function function
)
{
  rtems_status_code status_code;
  return status_code;
}

inline uint32_t tms570_timer_get_capvalue(
  const tms570_timer_number number,
  const tms570_capture_port capture_port
)
{
  return 0;
}

inline uint32_t tms570_timer_get_timer_value(
  const tms570_timer_number tnumber )
{
  return 0;
}

inline rtems_status_code tms570_timer_set_timer_value(
  const tms570_timer_number tnumber,
  const uint32_t             timer_value
)
{
  rtems_status_code status_code;
  return status_code;
}

void tms570_timer_isr( void *arg )
{
  
}

rtems_status_code tms570_timer_init( const tms570_timer_number tnumber )
{
  rtems_status_code status_code;
  return status_code;
}

rtems_status_code tms570_timer_init_with_interrupt(
  const tms570_timer_number            tnumber,
  const tms570_isr_funct_vector *const vector
)
{
  rtems_status_code status_code;
  return status_code;
}
