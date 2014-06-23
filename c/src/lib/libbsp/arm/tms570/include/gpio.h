/**
 * @file gpio.h
 *
 * @ingroup tms570
 *
 * @brief API of the GPIO driver for the tms570 bsp in RTEMS.
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

#ifndef LIBBSP_ARM_TMS570_GPIO_H
#define LIBBSP_ARM_TMS570_GPIO_H

#include <bsp/tms570.h>
#include <bsp/gpio-defs.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Configures the pin as input or output GPIO.
 *
 * @param pin The pin to configure
 * @param dir Input or output.
 */
rtems_status_code tms570_gpio_config(
  tms570_pin_number     pin,
  tms570_gpio_direction dir
);

/**
 * @brief Configures the pin as input, enables interrupt for an
 * edge/s and sets isrfunct as the function to call when that
 * interrupt occurs.
 *
 * @param pin The pin to configure.
 * @param edge Which edge or edges will activate the interrupt.
 * @param isrfunct The function that is called when the interrupt occurs.
 * @return RTEMS_SUCCESSFULL if the configurations was success.
 */
rtems_status_code tms570_gpio_config_input_with_interrupt(
  tms570_pin_number              pin,
  tms570_gpio_interrupt          edge,
  tms570_gpio_interrupt_function isrfunct
);

/**
 * @brief Sets the output pin to 1.
 *
 * @param pin The pin to set
 */
rtems_status_code tms570_gpio_set_pin( tms570_pin_number pin );

/**
 * @brief Sets the output pin to 0.
 *
 * @param pin The pin to set
 */
rtems_status_code tms570_gpio_clear_pin( tms570_pin_number pin );

/**
 * @brief Sets the output pin to 0 or 1 according to value.
 *
 * @param pin The pin to set
 * @param value the value to set.
 */
rtems_status_code tms570_gpio_write_pin(
  tms570_pin_number pin,
  bool               value
);

/**
 * @brief Returns the value at the given input pin.
 *
 * @param pin The pin where to read the value.
 * @param pin_value TRUE if the pin value was getted successfuly.
 * @return RTEMS_SUCCESSFUL if the pin value was getted successfuly.
 */
rtems_status_code tms570_gpio_get_pin_value(
  tms570_pin_number pin,
  bool              *pin_value
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_TMS570_GPIO_H */
