/**
 * @file gpio.c
 *
 * @ingroup tms570
 *
 * @brief GPIO library for the tms570 bsp.
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
#include <bsp/irq.h>
#include <bsp/io.h>
#include <bsp/gpio.h>
#include <rtems/status-checks.h>

rtems_status_code tms570_gpio_config(
  const tms570_pin_number     pin,
  const tms570_gpio_direction dir
)
{
  rtems_status_code status_code;
  return status_code;
}

/**
 * @brief Check for a rising edge and call the interrupt function.
 *
 * @param statR Rising edge interrupt.
 * @param pin The pin to check.
 * @param registered_isr_function Interrupt to check.
 * @return TRUE if is a rising edge. FALSE otherwise.
 */
static bool tms570_check_rising_edge_and_call(
  const uint32_t                              statR,
  const tms570_registered_interrupt_function registered_isr_function,
  const uint32_t                              pin
)
{
  bool is_rising = false;

  return is_rising;
}

/**
 * @brief Check for a falling edge and call the interrupt function.
 *
 * @param statR Falling edge interrupt.
 * @param pin The pin to check.
 * @param registered_isr_function Interrupt to check.
 * @return TRUE if is a falling edge. FALSE otherwise.
 */
static bool tms570_check_falling_edge_and_call(
  const uint32_t                              statF,
  const tms570_registered_interrupt_function registered_isr_function,
  const uint32_t                              pin
)
{
  bool is_falling = false;

  return is_falling;
}

/**
 * @brief Returns the interrupts base address according to the current port.
 *
 * @param  port Input/Output port.
 * @return Interrupt base address.
 */
static tms570_interrupt_control*tms570_get_interrupt_address(
  const tms570_gpio_ports port )
{
  tms570_interrupt_control *interrupt;

  return interrupt;
}

/**
 * @brief Checks the type of the current interrupt.
 *
 * @param registered_isr_function Interrupt to check.
 */
static void check_for_interrupt(
  const tms570_registered_interrupt_function registered_isr_function )
{
  
}

/**
 * @brief Checks all interrupts types.
 *
 * @param arg Interrupt to check.
 */
static inline void tms570_gpio_isr( void *arg )
{
  
}

/**
 * @brief Depending of the current edge sets rising/falling interrupt.
 *
 * @param edge Current edge.
 * @param pin_of_port Pin of the port to set the interrupt.
 * @param interrupt To enable the falling o rising edge.
 */
static void tms570_set_falling_or_rising_interrupt(
  const tms570_gpio_interrupt edge,
  const uint32_t               pin_of_port,
  tms570_interrupt_control   *interrupt
)
{
  }

/**
 * @brief Registers the pin and the callbacks functions.
 *
 * @param edge Current edge.
 * @param pin The pin to configure.
 * @param isr_funct Callback function to set.
 */
static void tms570_register_pin_and_callback(
  const tms570_gpio_interrupt          edge,
  const tms570_pin_number              pin,
  const tms570_gpio_interrupt_function isr_funct
)
{
  
}

/**
 * @brief Installs the interrupt handler.
 *
 * @param edge Which edge enable.
 * @return  RTEMS_SUCCESSFUL if the installation was success.
 */
static rtems_status_code tms570_install_interrupt_handler(
  const tms570_gpio_interrupt edge )
{
  rtems_status_code status_code;
  return status_code;
}

/**
 * @brief Configures the pin as input, enables interrupt for an
 * edge/s and sets isrfunct as the function to call when that
 * interrupt occurs.
 *
 * @param pin The pin to configure.
 * @param edge Which edge or edges will activate the interrupt.
 * @param isrfunct The function that is called when the interrupt occurs.
 * @return RTEMS_SUCCESSFUL if the configuration was success.
 */
static rtems_status_code tms570_check_edge_and_set_gpio_interrupts(
  const tms570_pin_number              pin,
  const tms570_gpio_interrupt          edge,
  const tms570_gpio_interrupt_function isr_funct
)
{
  rtems_status_code status_code;
  return status_code;
}

rtems_status_code tms570_gpio_config_input_with_interrupt(
  const tms570_pin_number              pin,
  const tms570_gpio_interrupt          edge,
  const tms570_gpio_interrupt_function isr_funct
)
{
  rtems_status_code status_code;
  return status_code;
}

rtems_status_code tms570_gpio_set_pin( const tms570_pin_number pin )
{
  rtems_status_code status_code;
  return status_code;
}

rtems_status_code tms570_gpio_clear_pin( const tms570_pin_number pin )
{
  rtems_status_code status_code;
  return status_code;
}

rtems_status_code tms570_gpio_write_pin(
  const tms570_pin_number pin,
  const bool               value
)
{
  rtems_status_code status_code;
  return status_code;
}

inline rtems_status_code tms570_gpio_get_pin_value(
  const tms570_pin_number pin,
  bool                    *pin_value
)
{
  rtems_status_code status_code;
  return status_code;
}
