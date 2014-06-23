/**
 * @file timer.h
 *
 * @ingroup tms570
 *
 * @brief Timer API for the tms570 bsp.
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

#ifndef LIBBSP_ARM_TMS570_TIMER_H
#define LIBBSP_ARM_TMS570_TIMER_H

#include <bsp/timer-defs.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief resets timer counter and stops it.
 *
 * @param tnumber the device to be reseted
 * @return RTEMS_SUCCESSFUL if the timer was reseted successfuly.
 */
rtems_status_code tms570_timer_reset( tms570_timer_number tnumber );

/**
 * @brief Sets mode of the timer (timer, counter rising, counter falling
 *        or counter both edges)
 *
 * @param tnumber: the device to be setted
 * @param mode: the desired mode
 * @return RTEMS_SUCCESSFUL if the timer's mode was setted successfuly.
 */
rtems_status_code tms570_timer_set_mode(
  tms570_timer_number tnumber,
  tms570_timer_mode   mode
);

/**
 * @brief Starts the timer counter
 *
 * @param tnumber: the device to be started
 * @return RTEMS_SUCCESSFUL if the timer's was started successfuly.
 */
rtems_status_code tms570_timer_start( tms570_timer_number tnumber );

/**
 * @brief true if timer is started.
 *
 * @param tnumber: the timer number to check.
 * @param is_started: TRUE if the timer is running.
 * @return RTEMS_SUCCESSFUL if the started timer check was successfuly.
 */
rtems_status_code tms570_timer_is_started(
  tms570_timer_number tnumber,
  bool                *is_started
);

/**
 * @brief sets the resolution in microseconds of the timer
 *
 * @param tnumber: the device to be modified.
 * @param resolution: how many microseconds will mean each timer
 *                    counter unit.
 * @return RTEMS_SUCCESSFUL if the timer resolution was setted successfuly.
 */
rtems_status_code tms570_timer_set_resolution(
  tms570_timer_number tnumber,
  tms570_microseconds resolution
);

/**
 * @brief Configures the timer match
 *
 * @param tnumber: the device to be modified
 * @param match_port: which port of this timer will be setted
 * @param function: what the timer should do when match: stop timer, clear,
 *                  and/or interrupt
 * @param match_value: the value that the timer should match.
 * @return RTEMS_SUCCESSFUL if the timer was configured successfuly.
 */
rtems_status_code tms570_timer_match_config(
  tms570_timer_number   tnumber,
  tms570_match_port     match_port,
  tms570_match_function function,
  uint32_t               match_value
);

/**
 * @brief Configures the capture ports
 *
 * @param tnumber: the device to be modified
 * @param capture_port: which port of this timer will be setted
 * @param function: At which edge/s will the capture work, and
 *                  if it will interrupt
 */
rtems_status_code tms570_timer_capture_config(
  tms570_timer_number     tnumber,
  tms570_capture_port     capture_port,
  tms570_capture_function function
);

/**
 * @brief Configures the external match ports
 *
 * @param tnumber: the device to be modified
 * @param match_port: which match for this timer
 * @param function: what should do when match: set, clear toggle or nothing
 */
rtems_status_code tms570_timer_external_match_config(
  tms570_timer_number       tnumber,
  tms570_match_port         match_port,
  tms570_ext_match_function function
);

/**
 * @brief Gets the captured value
 *
 * @param tnumber: the device to be modified
 * @param capnumber: which capture port for this timer
 * @return the captured value
 */
uint32_t tms570_timer_get_capvalue(
  tms570_timer_number tnumber,
  tms570_capture_port capnumber
);

/**
 * @brief Gets the timer value
 *
 * @param tnumber: the device
 * @return the timer value
 */
uint32_t tms570_timer_get_timer_value( tms570_timer_number tnumber );

/**
 * @brief Sets the timer value
 *
 * @param tnumber: the timer to modify.
 * @param timer_value the value to set.
 */
rtems_status_code tms570_timer_set_timer_value(
  tms570_timer_number tnumber,
  uint32_t             tms570_timer_value
);

/**
 * @brief Timer generic isroutine.
 *
 * @param timernumber the number of timer.
 */
void tms570_timer_isr( void *tms570_timer_number );

/**
 * @brief Initializes timer in timer mode and resets counter but
 *        without starting it, and without any capture or
 *        match function.
 *
 * @param tnumber which timer
 * @return RTEMS_SUCCESSFUL when everything ok.
 */
rtems_status_code tms570_timer_init( tms570_timer_number tnumber );

/**
 * @brief Initializes timer in timer mode and resets counter but
 *        without starting it, and without any capture or
 *        match function.
 *
 * @param tnumber which timer to init
 * @param vector the functions to be used by the isr.
 * @return RTEMS_SUCCESSFUL when everything ok.
 */
rtems_status_code tms570_timer_init_with_interrupt(
  tms570_timer_number            tnumber,
  const tms570_isr_funct_vector *vector
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_TMS570_TIMER_H */