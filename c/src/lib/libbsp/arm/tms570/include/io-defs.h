/**
 * @file io-defs.h
 *
 * @ingroup tms570
 *
 * @brief Input/output module definitions.
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

#ifndef LIBBSP_ARM_TMS570_IO_DEFS_H
#define LIBBSP_ARM_TMS570_IO_DEFS_H

#include <bsp/tms570.h>
#include <bsp/common-types.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TMS570_PLL0CON 0XAAU
#define TMS570_PLL0CFG 0X55U

#define TMS570_CCLK_PRESCALER_DIVISOR 1000000U

#define TMS570_PINSEL ( &PINSEL0 )
#define TMS570_PINMODE ( &PINMODE0 )

#define TMS570_PIN_SELECT( index ) ( ( index ) >> 4U )
#define TMS570_PIN_SELECT_SHIFT( index ) ( ( ( index ) & 0xFU ) << 1U )
#define TMS570_PIN_SELECT_MASK 0x3U
#define TMS570_PIN_SELECT_MASK_SIZE 2U
#define TMS570_PIN_UART_0_TXD 2U
#define TMS570_PIN_UART_0_RXD 3U

#define TMS570_MODULE_BITS_COUNT 32U
#define TMS570_MODULE_COUNT ( TMS570_MODULE_USB + 1U )

#define TMS570_IO_PORT_COUNT 5U
#define TMS570_IO_INDEX_MAX ( TMS570_IO_PORT_COUNT *       \
                               TMS570_MODULE_BITS_COUNT )
#define TMS570_IO_INDEX_BY_PORT( port, bit ) ( ( ( port ) << 5U ) + ( bit ) )
#define TMS570_IO_PORT( index ) ( ( index ) >> 5U )
#define TMS570_IO_PORT_BIT( index ) ( ( index ) & 0x1FU )

/**
 * @brief Defines the functions according to the pin.
 *
 * Enumerated type to define the set of pin function for a io device.
 */
typedef enum {
  TMS570_PIN_FUNCTION_00,
  TMS570_PIN_FUNCTION_01,
  TMS570_PIN_FUNCTION_10,
  TMS570_PIN_FUNCTION_11,
  TMS570_PIN_FUNCTION_COUNT
}
tms570_pin_function;

/**
 * @brief Defines all type of pins.
 *
 * Enumerated type to define the set of pin type for a io device.
 */
typedef enum {
  TMS570_PIN_TYPE_DEFAULT,
  TMS570_PIN_TYPE_ADC,
  TMS570_PIN_TYPE_DAC,
  TMS570_PIN_TYPE_OPEN_DRAIN
} tms570_pin_type;

/**
 * @brief Represents each pclksel number.
 *
 * Enumerated type to define the set of values for a pcklsel.
 */
typedef enum {
  TMS570_SCB_PCLKSEL0,
  TMS570_SCB_PCLKSEL1,
  TMS570_SCB_PCLKSEL_COUNT
} tms570_scb_value_pclksel;

/**
 * @brief Defines the module entry.
 */
typedef struct {
  /**
   * @brief Power entry bit.
   */
  unsigned char power : 1;
  /**
   * @brief Clock entry bit.
   */
  unsigned char clock : 1;
  /**
   * @brief Index entry bits.
   */
  unsigned char index : 6;
} tms570_module_entry;

#define TMS570_MODULE_ENTRY( mod, pwr, clk, idx )  \
  [ mod ] = {                                       \
    .power = pwr,                                 \
    .clock = clk,                                 \
    .index = idx                                  \
  }

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_TMS570_IO_DEFS_H */
