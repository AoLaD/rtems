/**
 * @file common-types.h
 *
 * @ingroup tms570
 *
 * @brief Definitions types used by some devices in common.
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

#ifndef LIBBSP_ARM_TMS570_COMMON_TYPES_H
#define LIBBSP_ARM_TMS570_COMMON_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief A pin of the board.
 */
typedef uint32_t tms570_pin_number;

/**
 * @brief Microseconds representation.
 */
typedef uint32_t tms570_microseconds;

/**
 * @brief tms570 module representation.
 *
 * Enumerated type to define the set of modules for a tms570 board.
 */
typedef enum {
  TMS570_MODULE_WD,
  TMS570_MODULE_ADC,
  TMS570_MODULE_CAN_0,
  TMS570_MODULE_CAN_1,
  TMS570_MODULE_DAC,
  TMS570_MODULE_GPDMA,
  TMS570_MODULE_GPIO,
  TMS570_MODULE_I2S,
  TMS570_MODULE_MCI,
  TMS570_MODULE_MCPWM,
  TMS570_MODULE_PCB,
  TMS570_MODULE_PWM_0,
  TMS570_MODULE_PWM_1,
  TMS570_MODULE_QEI,
  TMS570_MODULE_RTC,
  TMS570_MODULE_SYSCON,
  TMS570_MODULE_TIMER_0,
  TMS570_MODULE_TIMER_1,
  TMS570_MODULE_TIMER_2,
  TMS570_MODULE_TIMER_3,
  TMS570_MODULE_UART_0,
  TMS570_MODULE_UART_1,
  TMS570_MODULE_UART_2,
  TMS570_MODULE_UART_3,
  TMS570_MODULE_USB
} tms570_module;

/**
 * @brief Defines all the clock modules.
 *
 * Enumerated type to define the set of clock modules for a tms570 board.
 */
typedef enum {
  TMS570_MODULE_PCLK_DEFAULT = 0x4U,
  TMS570_MODULE_CCLK = 0x1U,
  TMS570_MODULE_CCLK_2 = 0x2U,
  TMS570_MODULE_CCLK_4 = 0x0U,
  TMS570_MODULE_CCLK_6 = 0x3U,
  TMS570_MODULE_CCLK_8 = 0x3U
} tms570_module_clock;

/**
 * @brief Fast Input/Output registers representation.
 */
typedef struct {
  /**
   * @brief Direction control register.
   */
  uint32_t dir;
  uint32_t reserved[ 3U ];
  /**
   * @brief Mask register for port.
   */
  uint32_t mask;
  /**
   * @brief Pinvalue register using 'mask'.
   */
  uint32_t pin;
  /**
   * @brief Output Set register using 'mask'.
   */
  uint32_t set;
  /**
   * @brief Output Clear register using 'maks'.
   */
  uint32_t clr;
} tms570_fio;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_ARM_TMS570_COMMON_TYPES_H */