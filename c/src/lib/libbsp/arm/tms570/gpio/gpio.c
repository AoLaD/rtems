/**
 * @file gpio.c
 *
 * @ingroup tms570
 *
 * @brief GPIO library for the tms570 bsp.
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
#include <bsp/irq.h>
#include <bsp/io.h>
#include <bsp/gpio.h>
#include <rtems/status-checks.h>

static uint32_t                              function_vector_size = 0u;
static tms570_registered_interrupt_function function_vector[
  TMS570_RESERVED_ISR_FUNCT_SIZE ];
static bool isr_installed = false;

rtems_status_code tms570_gpio_config(
  const tms570_pin_number     pin,
  const tms570_gpio_direction dir
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( ( pin < TMS570_MAX_PORT_NUMBER ) &&
       ( dir < TMS570_GPIO_FUNCTION_COUNT ) ) {
    const tms570_gpio_ports port = TMS570_IO_PORT( pin );
    const uint32_t           pin_of_port = TMS570_IO_PORT_BIT( pin );

    tms570_pin_select( pin, TMS570_PIN_FUNCTION_00 );

    TMS570_SET_BIT( TMS570_FIO[ port ].dir, pin_of_port, dir );

    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the pin or the egde are out of range. Also,
     an invalid number is returned. */

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

  if ( statR & TMS570_PIN_BIT( pin ) ) {
    registered_isr_function.function( registered_isr_function.pin,
      TMS570_GPIO_INTERRUPT_RISING );
    is_rising = true;
  }

  /* else implies that the current interrupt is not STATR. Also,
     there is nothing to do. */

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

  if ( statF & TMS570_PIN_BIT( pin ) ) {
    registered_isr_function.function( registered_isr_function.pin,
      TMS570_GPIO_INTERRUPT_FALLING );
    is_falling = true;
  }

  /* else implies that the current interrupt is not STATF. Also,
     there is nothing to do. */

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

  switch ( port ) {
    case ( TMS570_GPIO_PORT_0 ):
      interrupt = (tms570_interrupt_control *) TMS570_IO0_INT_BASE_ADDRESS;
      break;
    case ( TMS570_GPIO_PORT_2 ):
      interrupt = (tms570_interrupt_control *) TMS570_IO2_INT_BASE_ADDRESS;
      break;
    case ( TMS570_GPIO_PORT_1 ):
    case ( TMS570_GPIO_PORT_3 ):
    case ( TMS570_GPIO_PORT_4 ):
    default:
      interrupt = NULL;
  }

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
  assert( registered_isr_function.pin < TMS570_MAX_PORT_NUMBER );

  const tms570_gpio_ports port = TMS570_IO_PORT(
    registered_isr_function.pin );
  const uint32_t pin = TMS570_IO_PORT_BIT( registered_isr_function.pin );

  tms570_interrupt_control *interrupt = tms570_get_interrupt_address( port );
  assert( interrupt != NULL );

  bool is_rising_edge = tms570_check_rising_edge_and_call( interrupt->StatR,
    registered_isr_function,
    pin );

  bool is_falling_edge = tms570_check_falling_edge_and_call( interrupt->StatF,
    registered_isr_function,
    pin );

  if ( is_rising_edge || is_falling_edge ) {
    interrupt->Clr = TMS570_PIN_BIT( pin );
  }

  /* else implies that the current interrupt is not CLR. Also,
     there is nothing to do. */
}

/**
 * @brief Checks all interrupts types.
 *
 * @param arg Interrupt to check.
 */
static inline void tms570_gpio_isr( void *arg )
{
  unsigned int i;

  for ( i = 0; i < function_vector_size; ++i ) {
    check_for_interrupt( function_vector[ i ] );
  }
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
  if ( edge & TMS570_GPIO_INTERRUPT_RISING ) {
    TMS570_SET_BIT( interrupt->EnR, pin_of_port, TMS570_INT_ENABLE );
  }

  /* else implies that it should not install the interrupt for a RISING edge.
      Also, there is nothing to do. */

  if ( edge & TMS570_GPIO_INTERRUPT_FALLING ) {
    TMS570_SET_BIT( interrupt->EnF, pin_of_port, TMS570_INT_ENABLE );
  }

  /* else implies that it should not install the interrupt for a FALLING edge.
      Also, there is nothing to do. */
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
  if ( edge ) {
    assert( function_vector_size < TMS570_RESERVED_ISR_FUNCT_SIZE );
    function_vector[ function_vector_size ].function = isr_funct;
    function_vector[ function_vector_size ].pin = pin;
    ++function_vector_size;
  }

  /* else implies that the current interrupt is DISABLED or BOTH. Also,
     there is nothing to do. */
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
  rtems_status_code status_code = RTEMS_SUCCESSFUL;

  if ( !isr_installed && edge ) {
    status_code = rtems_interrupt_handler_install( TMS570_IRQ_EINT_3,
      "gpio_interrupt",
      RTEMS_INTERRUPT_UNIQUE,
      tms570_gpio_isr,
      NULL );
    isr_installed = true;
  }

  /* else implies that the interrupts have been previously installed. Also,
     there is nothing to do. */

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
  rtems_status_code status_code = RTEMS_SUCCESSFUL;

  const tms570_gpio_ports port = TMS570_IO_PORT( pin );
  const uint32_t           pin_of_port = TMS570_IO_PORT_BIT( pin );

  tms570_interrupt_control *interrupt = tms570_get_interrupt_address( port );

  assert( interrupt != NULL );

  tms570_gpio_config( pin, TMS570_GPIO_FUNCTION_INPUT );

  tms570_set_falling_or_rising_interrupt( edge, pin_of_port, interrupt );

  tms570_register_pin_and_callback( edge, pin, isr_funct );

  status_code = tms570_install_interrupt_handler( edge );

  return status_code;
}

rtems_status_code tms570_gpio_config_input_with_interrupt(
  const tms570_pin_number              pin,
  const tms570_gpio_interrupt          edge,
  const tms570_gpio_interrupt_function isr_funct
)
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( ( pin < TMS570_MAX_PORT_NUMBER )
       && ( edge < TMS570_GPIO_INTERRUPT_COUNT ) ) {
    status_code = tms570_check_edge_and_set_gpio_interrupts( pin,
      edge,
      isr_funct );
  }

  /* else implies that the pin or the egde are out of range. Also,
     an invalid number is returned. */

  return status_code;
}

rtems_status_code tms570_gpio_set_pin( const tms570_pin_number pin )
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( pin < TMS570_MAX_PORT_NUMBER ) {
    const tms570_gpio_ports port = TMS570_IO_PORT( pin );
    const uint32_t           pin_of_port = TMS570_IO_PORT_BIT( pin );

    TMS570_FIO[ port ].set = TMS570_PIN_BIT( pin_of_port );

    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the pin or the egde are out of range. Also,
     an invalid number is returned. */

  return status_code;
}

rtems_status_code tms570_gpio_clear_pin( const tms570_pin_number pin )
{
  rtems_status_code status_code = RTEMS_INVALID_NUMBER;

  if ( pin < TMS570_MAX_PORT_NUMBER ) {
    const tms570_gpio_ports port = TMS570_IO_PORT( pin );
    const uint32_t           pin_of_port = TMS570_IO_PORT_BIT( pin );

    TMS570_FIO[ port ].clr = TMS570_PIN_BIT( pin_of_port );

    status_code = RTEMS_SUCCESSFUL;
  }

  /* else implies that the pin or the egde are out of range. Also,
     an invalid number is returned. */

  return status_code;
}

rtems_status_code tms570_gpio_write_pin(
  const tms570_pin_number pin,
  const bool               value
)
{
  rtems_status_code status_code;

  if ( value ) {
    status_code = tms570_gpio_set_pin( pin );
  } else {
    status_code = tms570_gpio_clear_pin( pin );
  }

  return status_code;
}

inline rtems_status_code tms570_gpio_get_pin_value(
  const tms570_pin_number pin,
  bool                    *pin_value
)
{
  assert( pin < TMS570_MAX_PORT_NUMBER );

  rtems_status_code status_code = RTEMS_SUCCESSFUL;

  const tms570_gpio_ports port = TMS570_IO_PORT( pin );
  const uint32_t           pin_of_port = TMS570_IO_PORT_BIT( pin );
  *pin_value = ( TMS570_FIO[ port ].pin & TMS570_PIN_BIT( pin_of_port ) );

  return status_code;
}
