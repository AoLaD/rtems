/**
 * @file
 *
 * @ingroup bsp_interrupt
 *
 * @brief TMS570 interrupt definitions.
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
 * by embedded brains GmbH and others
 * 
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef LIBBSP_ARM_TMS570_IRQ_H
#define LIBBSP_ARM_TMS570_IRQ_H

#ifndef ASM
#include <rtems.h>
#include <rtems/irq.h>
#include <rtems/irq-extension.h>
#endif


#define BSP_INTERRUPT_VECTOR_MIN 0U


#define BSP_INTERRUPT_VECTOR_MAX 0

#define TMS570_IRQ_PRIORITY_VALUE_MIN 0U

#define TMS570_IRQ_PRIORITY_VALUE_MAX 0U

#define TMS570_IRQ_PRIORITY_COUNT ( TMS570_IRQ_PRIORITY_VALUE_MAX + 1U )
#define TMS570_IRQ_PRIORITY_HIGHEST TMS570_IRQ_PRIORITY_VALUE_MIN
#define TMS570_IRQ_PRIORITY_LOWEST TMS570_IRQ_PRIORITY_VALUE_MAX

#ifndef ASM

void tms570_irq_set_priority(
  rtems_vector_number vector,
  unsigned            priority
);

unsigned tms570_irq_get_priority( rtems_vector_number vector );

#endif /* ASM */

/** @} */

#endif /* LIBBSP_ARM_TMS570_IRQ_H */
