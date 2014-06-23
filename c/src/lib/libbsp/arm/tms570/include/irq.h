/**
 * @file
 *
 * @ingroup bsp_interrupt
 *
 * @brief TMS570 interrupt definitions.
 */

/*
 * Copyright (c) 2008-2012 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Obere Lagerstr. 30
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.com/license/LICENSE.
 */

#ifndef LIBBSP_ARM_TMS570_IRQ_H
#define LIBBSP_ARM_TMS570_IRQ_H

#ifndef ASM
#include <rtems.h>
#include <rtems/irq.h>
#include <rtems/irq-extension.h>
#endif

/**
 * @addtogroup bsp_interrupt
 *
 * @{
 */

#define BSP_INTERRUPT_VECTOR_MIN 0U

#define TMS570_IRQ_WDT 0U
#define TMS570_IRQ_TIMER_0 1U
#define TMS570_IRQ_TIMER_1 2U
#define TMS570_IRQ_TIMER_2 3U
#define TMS570_IRQ_TIMER_3 4U
#define TMS570_IRQ_UART_0 5U
#define TMS570_IRQ_UART_1 6U
#define TMS570_IRQ_UART_2 7U
#define TMS570_IRQ_UART_3 8U
#define TMS570_IRQ_PWM_1 9U
#define TMS570_IRQ_PLL 16U
#define TMS570_IRQ_RTC 17U
#define TMS570_IRQ_EINT_0 18U
#define TMS570_IRQ_EINT_1 19U
#define TMS570_IRQ_EINT_2 20U
#define TMS570_IRQ_EINT_3 21U
#define TMS570_IRQ_ADC_0 22U
#define TMS570_IRQ_BOD 23U
#define TMS570_IRQ_USB 24U
#define TMS570_IRQ_CAN 25U
#define TMS570_IRQ_DMA 26U
#define TMS570_IRQ_I2S 27U
#define TMS570_IRQ_SD_MMC 29U
#define TMS570_IRQ_MCPWM 30U
#define TMS570_IRQ_QEI 31U
#define TMS570_IRQ_PLL_ALT 32U
#define TMS570_IRQ_USB_ACTIVITY 33U
#define TMS570_IRQ_CAN_ACTIVITY 34U
#define TMS570_IRQ_UART_4 35U
#define TMS570_IRQ_GPIO 38U
#define TMS570_IRQ_PWM 39U
#define TMS570_IRQ_EEPROM 40U

#define BSP_INTERRUPT_VECTOR_MAX 40

#define TMS570_IRQ_PRIORITY_VALUE_MIN 0U

#define TMS570_IRQ_PRIORITY_VALUE_MAX 31U

#define TMS570_IRQ_PRIORITY_COUNT ( TMS570_IRQ_PRIORITY_VALUE_MAX + 1U )
#define TMS570_IRQ_PRIORITY_HIGHEST TMS570_IRQ_PRIORITY_VALUE_MIN
#define TMS570_IRQ_PRIORITY_LOWEST TMS570_IRQ_PRIORITY_VALUE_MAX

#ifndef ASM

/**
 * @brief Sets the priority according to the current interruption.
 *
 * @param vector   Interrupt to be attended.
 * @param priority Interrupts priority.
 */
void tms570_irq_set_priority(
  rtems_vector_number vector,
  unsigned            priority
);

/**
 * @brief Gets the priority number according to the current interruption.
 *
 * @param  vector Interrupts to be attended.
 * @return The priority number according to the current interruption.
 */
unsigned tms570_irq_get_priority( rtems_vector_number vector );

#endif /* ASM */

/** @} */

#endif /* LIBBSP_ARM_TMS570_IRQ_H */
